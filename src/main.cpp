#include "inc/build/all.h"
#include "inc/test/all.h"

class Jobs {
public:
    explicit Jobs(const std::string& jobName) : name{ jobName } {
    }

    template<typename _Callable, typename... _Args>
    decltype(auto) Job(_Callable&& obj
        , _Args&&... args
    ) {
        return *this;
    }


private:
    std::string name{};
};

class Pipeline {
public:
    explicit Pipeline(const std::string& branch) {
        sourceInfo.branchName = branch;
    }

    decltype(auto) Stages(const Jobs& jobs) {
        return *this;
    }

    [[nodiscard]]
    bool Run() {
        return false;
    }

private:
    g::SourceInfo sourceInfo{};
};

inline constexpr g::build::_Pull_fn Pull{};
inline constexpr g::test::_Test_fn Test{};
int main() {
    if (Pipeline{ "release_v1.0" }
        .Stages(Jobs{ "building" }.Job(Pull))
        .Stages(Jobs{ "testing" }
            .Job(Test, 2021, "X-59: QueSST 洛克希德·马丁")
            .Job(Test, 1956, "CH-47: Chinook 波音"))

        .Run())
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
