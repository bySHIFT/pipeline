#pragma once
#include <numeric>
#include <random>
#include <utility>

namespace g::uuid {
auto
randomGen() {
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(0, 0X0F);

    return std::make_pair(dis, gen);
}

// 生成伪UUID
//   AC36A098-7A2A-4CF8-A68C-96E668BAEFE4
std::string
UUID() {
    const std::vector<int> parts{ 8, 4, 4, 4, 12 };
    const auto SIZE = std::accumulate(parts.begin(), parts.end(), 0)
        + parts.size() - 1;

    auto [dis, gen] = randomGen();
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

    auto [dis, gen] = randomGen();
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
} // end g::uuid namespace
