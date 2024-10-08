﻿#pragma once
#include "banner/banner.hxx"
#include "ctime/ctime.hxx"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>

using OptString = std::optional<std::string>;

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

template<typename _Banner, typename _TitleBanner>
void
TitleBanner(const _Banner& banner, const _TitleBanner& titleBanner
    , const std::string_view& tag
    , const std::string& name, std::size_t no, std::size_t cnt) {
    std::stringstream ss;
    ss << banner << std::endl
        << titleBanner << tag << "[" << no << "/" << cnt
        << "]: " << name << std::endl;

    std::cout << ss.str();
}

inline
std::ostream&
Item(const std::string& item) {
    return std::cout << itemBanner
        << item << std::endl;
}

inline
void
Stage(const std::string& stageName, std::size_t no, std::size_t cnt) {
    TitleBanner(h1, titleBannerStage, "阶段", stageName, no, cnt);
}

inline
void
Job(const std::string& jobName, std::size_t no, std::size_t cnt) {
    TitleBanner(h2, titleBannerJob, "任务", jobName, no, cnt);
    Item("正在进行" + jobName + "...");
}

inline
void CoutJobStatus(const std::string& jobName, bool status, const OptString& msg) {
    std::cout << std::endl
        << g::itemBannerStatus << "执行状态: " << jobName
        << (status ? " 成功" : " 失败") << std::endl;
}

void CoutMetrics(const std::string& tagName
    , const std::chrono::time_point<std::chrono::steady_clock>& start
) {
    std::cout << g::itemBannerMetrics << "耗时: " << tagName
        << " " << g::ctime::FriendlyDuration(start)
        << std::endl;
}

} // end g::cout namespace