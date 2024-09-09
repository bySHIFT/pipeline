#pragma once
#include <numeric>
#include <random>
#include <utility>

namespace g::random {
template<class _Ty = int>
auto
RandomGen(_Ty min, _Ty max) {
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(min, max);

    return std::make_pair(dis, gen);
}

inline
auto
HexRandomGen() {
    return RandomGen<char>(0, 0X0F);
}

// 生成伪UUID
//   AC36A098-7A2A-4CF8-A68C-96E668BAEFE4
std::string
UUID() {
    const std::vector<int> parts{ 8, 4, 4, 4, 12 };
    const auto SIZE = std::accumulate(parts.begin(), parts.end(), 0)
        + parts.size() - 1;

    auto [dis, gen] = HexRandomGen();
    std::string container(SIZE, '-');
    for (auto i = 0; i < parts.size(); ++i) {
        const auto offset = std::accumulate(parts.begin(), parts.begin() + i, 0) + i;
        for (auto j = 0; j < parts[i]; ++j) {
            const auto num = dis(gen);
            if (num < 10) container[j + offset] = static_cast<char>('0' + num);
            else container[j + offset] = static_cast<char>('A' + (num - 10));
        }
    }

    return container;
}

// 生成伪CommitId
//   a8da2669
std::string
CommitId() {
    constexpr std::size_t SIZE{ 8 };

    auto [dis, gen] = HexRandomGen();
    std::string container(SIZE, '-');
    for (auto j = 0; j < SIZE; ++j) {
        const auto num = dis(gen);
        if (num < 10)
            container[j] = static_cast<char>('0' + num);
        else
            container[j] = static_cast<char>('a' + (num - 10));
    }

    return container;
}

bool
DummyStatus(std::uint8_t ratioSuccessful = 98) {
    constexpr std::uint8_t MaxRatioSuccessful = 100;
    if (ratioSuccessful > MaxRatioSuccessful)
        ratioSuccessful = MaxRatioSuccessful;

    auto [dis, gen] = RandomGen<std::uint8_t>(0, 100);
    if (const auto current = dis(gen); current >= (MaxRatioSuccessful - ratioSuccessful))
        return true;

    return false;
}
} // end g::random namespace
