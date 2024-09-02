#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace g::ctime {
std::string
Now() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Z %F %T");

    return ss.str();
}
} // end g::ctime namespace