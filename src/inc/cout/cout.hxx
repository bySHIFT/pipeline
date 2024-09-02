#pragma once
#include "banner/banner.hxx"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>

namespace g::cout {
template<std::ranges::input_range _Rng>
decltype(auto)
Ranges(_Rng&& rng) {
    std::stringstream ss;
    ss << '[';

    if (!std::empty(rng)) {
        ss << *(std::begin(rng));
        std::ranges::for_each(std::next(std::begin(rng)), std::end(rng)
            , [&ss](auto&& item) { ss << ", " << item; });
    }

    ss<< ']' << std::endl;
    return std::cout << ss.str();
}

template<typename _Banner>
void
Banner(const _Banner& banner, const std::string_view& tag
    , const std::string& name, std::size_t no, std::size_t cnt) {
    std::stringstream ss;
    ss << banner << std::endl
        << titleBanner << tag << "[" << no << "/" << cnt
        << "]: " << name << std::endl;

    std::cout << ss.str();

}

inline
void
Stage(const std::string& stageName, std::size_t no, std::size_t cnt) {
    Banner(h1, "阶段", stageName, no, cnt);
}

inline
void
Job(const std::string& jobName, std::size_t no, std::size_t cnt) {
    Banner(h2, "任务", jobName, no, cnt);
}

inline
std::ostream&
Item(const std::string& item) {
    return std::cout << itemBanner
        << item << std::endl;
}
} // end g::cout namespace