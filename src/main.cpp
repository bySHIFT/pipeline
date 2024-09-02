#include "inc/build/all.h"
#include "inc/deploy/all.h"
#include "inc/test/all.h"

class Stage {
public:
    using TypeJobOperator = std::function<bool(const std::string& /*jobName*/)>;
    using TypeNamedJobOperator = std::pair<std::string, TypeJobOperator>;
    using TypeJobNamedOperators = std::vector<TypeNamedJobOperator>;

    explicit Stage(const std::string& stageName) : stageName{ stageName } {
    }

    template<typename _Callable, typename... _Args>
        requires std::invocable<_Callable&, const std::string&, _Args...>
            && IsAnyOf<std::invoke_result_t<_Callable&, const std::string&/*jobName*/, _Args...>
                , void, bool>
    decltype(auto) Job(const std::string& jobName
        , _Callable&& obj, _Args&&... args
    ) {
        if constexpr (std::is_same_v<std::invoke_result_t<_Callable&
            , const std::string&/*jobName*/, _Args...>, bool>) {
            jobOperators.emplace_back(jobName, [&](const std::string& jobName) {
                return std::invoke(std::forward<_Callable>(obj), jobName
                    , std::forward<_Args>(args)...); });
        } else {
            jobOperators.emplace_back(jobName, [&](const std::string& jobName) {
                std::invoke(std::forward<_Callable>(obj), jobName
                    , std::forward<_Args>(args)...);
                return true; });
        }

        return *this;
    }

    bool operator()(std::size_t noStage, std::size_t cntStages) const {
        endl(std::cout);
        g::cout::Stage(stageName, noStage, cntStages);

        const auto cnt = jobOperators.size();
        std::size_t idx = 0;
        for (const auto& job : jobOperators) {
            g::cout::Job(job.first, ++idx, cnt);
            if (!job.second(job.first))
                return false;
        }
        return true;
    }

    inline const std::string& StageName() const { return stageName; }

private:
    std::string stageName{};
    TypeJobNamedOperators jobOperators{};
};

class Pipeline {
public:
    using TypeStages = std::vector<Stage>;

    decltype(auto) Stages(const Stage& stage) {
        stages.push_back(stage);
        return *this;
    }

    [[nodiscard]]
    bool Run() const {
        coutStageNames();

        const auto cnt = stages.size();
        std::size_t idx = 0;
        for (auto& stage : stages)
            if (!stage(++idx, cnt))
                return false;

        return true;
    }

private:
    void coutStageNames() const {
        std::cout << g::h1 << std::endl
            << g::itemBanner << "一次构建流程: ";
        VecString names{};
        RngForEach(stages, [](VecString& nameStages, auto&& stage) {
            nameStages.emplace_back(stage.StageName()); }, names);

        g::cout::Ranges(names);
    }

    g::SourceInfo sourceInfo{};
    TypeStages stages{};
};

int main() {
    if (g::SourceInfo srcInfo{ .branchName = "release_v1.0" };
        Pipeline{}
        .Stages(Stage{ "说明" }.Job("一次构建说明"
            , [](auto&& jobName, auto&& branchName) {
                g::cout::Item(jobName + "构建版本: " + branchName); }, *srcInfo.branchName))
        .Stages(Stage{ "构建" }
            .Job("获取编译代码", g::build::Pull, srcInfo)
            .Job("代码静态分析", g::build::Check, srcInfo)
            .Job("代码构建", g::build::Build, srcInfo)
            .Job("推送构建结果", g::build::Push, srcInfo))
        .Stages(Stage{ "测试" }
            .Job("测试工程: X-59", g::test::Test, 2021, "X-59: QueSST 洛克希德·马丁", srcInfo.pushId)
            .Job("测试工程: CH-47", g::test::Test, 1956, "CH-47: Chinook 波音", srcInfo.pushId))
        .Stages(Stage{ "部署" }
            .Job("部署环境: 北京", g::deploy::Deploy, "清华大学", srcInfo.pushId)
            .Job("部署环境: 上海", g::deploy::Deploy, "复旦大学", srcInfo.pushId)
            .Job("部署环境: 深圳", g::deploy::Deploy, "深圳大学", srcInfo.pushId))

        .Run())
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
