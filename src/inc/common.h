#pragma once
#include "cout/cout.hxx"
#include "random/random.hxx"
#include "scope_exit/scope_exit.hxx"

#include <functional>
#include <future>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
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

void
ElapsedSecondsDummyJob(std::uint8_t max, std::uint8_t min = 0) {
    using namespace std::chrono_literals;

    g::cout::Item("可能的耗时时间在[" + std::to_string(min) + ", " + std::to_string(max) + "], 单位: 秒");
    auto [dis, gen] = g::random::RandomGen(min, max);
    const auto elapsed = dis(gen);
    auto job = std::async(std::launch::async
        , [](auto&& seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }
        , elapsed);

    std::future_status status{};
    do {
        status = job.wait_for(1s);
        if (std::future_status::timeout == status)
            std::cout << '.';
        else if (std::future_status::ready == status)
            endl(std::cout);
    } while (std::future_status::ready != status);

    job.get();
}