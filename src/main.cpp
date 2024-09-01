#include "inc/build/all.h"
#include "inc/deploy/all.h"
#include "inc/test/all.h"

class Stage {
public:
    using TypeJobOperator = std::function<bool()>;
    using TypeNamedJobOperator = std::pair<std::string, TypeJobOperator>;
    using TypeJobNamedOperators = std::vector<TypeNamedJobOperator>;

    explicit Stage(const std::string& stageName) : stageName{ stageName } {
    }

    template<typename _Callable, typename... _Args>
        requires std::invocable<_Callable&, _Args...>
            && IsAnyOf<std::invoke_result_t<_Callable&, _Args...>, bool, void>
    decltype(auto) Job(const std::string& jobName
        , _Callable&& obj, _Args&&... args
    ) {
        if constexpr (std::is_same_v<std::invoke_result_t<_Callable&, _Args...>, bool>) {
            jobOperators.emplace_back(jobName, [&]() {
                return std::invoke(std::forward<_Callable>(obj)
                    , std::forward<_Args>(args)...); });
        } else {
            jobOperators.emplace_back(jobName, [&]() {
                std::invoke(std::forward<_Callable>(obj)
                    , std::forward<_Args>(args)...); });
            return true;
        }

        return *this;
    }

    bool operator()(std::size_t noStage, std::size_t cntStages) const {
        endl(std::cout);
        g::CoutStage(stageName, noStage, cntStages);

        const auto cnt = jobOperators.size();
        std::size_t idx = 0;
        for (const auto& job : jobOperators) {
            g::CoutJob(job.first, ++idx, cnt);
            if (!job.second())
                return false;
        }
        return true;
    }

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
        const auto cnt = stages.size();
        std::size_t idx = 0;
        for (auto& stage : stages)
            if (!stage(++idx, cnt))
                return false;

        return true;
    }

private:
    g::SourceInfo sourceInfo{};
    TypeStages stages{};
};

inline constexpr g::build::_Build_fn Build;
inline constexpr g::build::_Check_fn Check;
inline constexpr g::build::_Pull_fn Pull;
inline constexpr g::build::_Push_fn Push;
inline constexpr g::deploy::_Deploy_fn Deploy;
inline constexpr g::test::_Test_fn Test;

int main() {
    if (g::SourceInfo srcInfo{ .branchName = "release_v1.0" };
        Pipeline{}
        .Stages(Stage{ "构建" }
            .Job("获取编译代码", Pull, srcInfo)
            .Job("代码静态分析", Check, srcInfo)
            .Job("代码构建", Build, srcInfo)
            .Job("推送构建结果", Push, srcInfo))
        .Stages(Stage{ "测试" }
            .Job("测试工程: X-59", Test, 2021, "X-59: QueSST 洛克希德·马丁", srcInfo)
            .Job("测试工程: CH-47", Test, 1956, "CH-47: Chinook 波音", srcInfo))
        .Stages(Stage{ "部署" }
            .Job("部署环境: 北京", Deploy, "清华大学", srcInfo)
            .Job("部署环境: 上海", Deploy, "复旦大学", srcInfo)
            .Job("部署环境: 深圳", Deploy, "深圳大学", srcInfo))

        .Run())
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
