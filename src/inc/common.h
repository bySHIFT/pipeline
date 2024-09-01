#pragma once
#include "banner/banner.hxx"
#include "uuid/uuid.hxx"

#include <chrono>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using OptString = std::optional<std::string>;

template <class _Ty, class... _Types>
constexpr bool IsAnyOf = // true if and only if _Ty is in _Types
    std::disjunction_v<std::is_same<_Ty, _Types>...>;

namespace g {
template<typename _Banner>
void CoutBanner(const _Banner& banner, const std::string_view& tag
    , const std::string& name, std::size_t no, std::size_t cnt) {
    std::stringstream ss;
    ss << banner << std::endl
        << titleBanner << tag << "[" << no << "/" << cnt
        << "]: " << name << std::endl;

    std::cout << ss.str();

}

inline
void CoutStage(const std::string& stageName, std::size_t no, std::size_t cnt) {
    CoutBanner(h1, "阶段", stageName, no, cnt);
}

inline
void CoutJob(const std::string& jobName, std::size_t no, std::size_t cnt) {
    CoutBanner(h2, "任务", jobName, no, cnt);
}

inline
std::ostream& CoutItem(const std::string& item) {
    return std::cout << itemBanner
        << item << std::endl;
}
}