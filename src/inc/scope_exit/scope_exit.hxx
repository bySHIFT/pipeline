#pragma once
#include <ranges>

namespace g::scope_exit {
struct _Scope_exit_fn {
    template <class _Fty, class... _ArgTypes>
        requires std::invocable<_Fty&, _ArgTypes...>
    auto operator() (_Fty&& _Fnarg, _ArgTypes&&... _Args) const {
        int sentinel{};
        auto deleter = [&](int*) { std::forward<_Fty>(_Fnarg)(std::forward<_ArgTypes>(_Args)...); };
        return std::move(std::unique_ptr<int, decltype(deleter)>(&sentinel, deleter));
    }
};

inline constexpr _Scope_exit_fn scope_exit{};
} // end g::scope_exit namespace

#define __g_CONCATX(x, y)  x##y
#define __g_CONCAT(x, y)   __g_CONCATX(x, y)
#define __g_UNIQUE(x)      __g_CONCAT(__##x##__line_, __LINE__)
#define __g_UNIQUE_UNNAMED __g_UNIQUE(unnamed)

#define __g_Unnamed_ScopeExit(...) auto __g_UNIQUE_UNNAMED = g::scope_exit::scope_exit(__VA_ARGS__)
