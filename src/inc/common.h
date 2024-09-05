#pragma once
#include "cout/cout.hxx"
#include "ctime/ctime.hxx"
#include "random/random.hxx"
#include "scope_exit/scope_exit.hxx"

#include <chrono>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using VecString = std::vector<std::string>;

template <class _Ty, class... _Types>
constexpr bool IsAnyOf = // true if and only if _Ty is in _Types
    std::disjunction_v<std::is_same<_Ty, _Types>...>;

template<std::ranges::input_range _Rng, typename _Func, typename... _Args>
    requires std::invocable<_Func, _Args..., std::ranges::range_reference_t<_Rng>>
auto
RngForEach(_Rng&& range, _Func&& func, _Args&&... args) {
    return std::ranges::for_each(range, [&](auto&& item) {
        return std::invoke(std::forward<_Func>(func), std::forward<_Args>(args)..., item); });
}
