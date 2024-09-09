#pragma once
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace g::ctime {
namespace internal {
template<typename TimeUnit>
bool MicroSecondsAS(
    const char* fmtTime
    , const std::chrono::microseconds& micros
    , std::string& humanDuration
) {
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    const auto micros_as_double = static_cast<double>(micros.count());
    if (duration_cast<TimeUnit>(micros) > TimeUnit()) {
        char buffer[16] = { 0 };

        const auto t = micros_as_double / duration_cast<microseconds>(TimeUnit(1)).count();
        std::snprintf(buffer, sizeof buffer, fmtTime, t);
        humanDuration = buffer;

        return true;
    }

    return false;
}

} // end internal namespace

std::string
Now() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Z %F %T");

    return ss.str();
}

std::string
FriendlyDuration(const std::chrono::nanoseconds& nanos) {
    namespace sc = std::chrono;

    const auto micros = std::chrono::duration_cast<sc::microseconds>(nanos);
    std::string humanDuration{};
    if (internal::MicroSecondsAS<sc::hours>("%.4gh", micros, humanDuration))
        return humanDuration;
    if (internal::MicroSecondsAS<sc::minutes>("%.4gmin", micros, humanDuration))
        return humanDuration;
    if (internal::MicroSecondsAS<sc::seconds>("%.4gs", micros, humanDuration))
        return humanDuration;
    if (internal::MicroSecondsAS<sc::milliseconds>("%.4gms", micros, humanDuration))
        return humanDuration;
    if (internal::MicroSecondsAS<sc::microseconds>("%.4gus", micros, humanDuration))
        return humanDuration;

    return { "小于 1us" };
}

inline
auto FriendlyDuration(const std::chrono::steady_clock::time_point& start) {
    return FriendlyDuration(std::chrono::steady_clock::now() - start);
}

} // end g::ctime namespace