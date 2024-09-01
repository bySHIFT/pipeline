#pragma once
#include <iostream>
#include <string>

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
inline constexpr _Banner_fn<4> itemBanner;
} // end g namespace