#pragma once
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
template<std::size_t COUNT, char CH = '='>
struct _Banner_fn {
    friend std::ostream& operator<<(std::ostream& os, const _Banner_fn& banner) {
        return os << std::string(COUNT, CH);
    }
};

inline constexpr _Banner_fn<80> h1;
inline constexpr _Banner_fn<60> h2;
inline constexpr _Banner_fn<40> h3;
inline constexpr _Banner_fn<4, '*'> titleBanner;

template<typename _Banner>
void CoutBanner(const _Banner& banner, const std::string_view& tag
    , const std::string& name, std::size_t no, std::size_t cnt) {
    std::stringstream ss;
    ss << banner << std::endl
        << titleBanner << tag << "[" << no << "/" << cnt
        << "]: " << name << std::endl;

    std::cout << ss.str();

}

void CoutStage(const std::string& stageName, std::size_t no, std::size_t cnt) {
    CoutBanner(h1, "阶段", stageName, no, cnt);
}

void CoutJob(const std::string& jobName, std::size_t no, std::size_t cnt) {
    CoutBanner(h2, "任务", jobName, no, cnt);
}
}