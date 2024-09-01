#pragma once
#include "common.h"

namespace g {
struct SourceInfo {
    OptString branchName{};
    OptString commitId{};
    OptString date{};
};

std::ostream& CoutSourceInfo(const SourceInfo& sourceInfo) {
    constexpr _Banner_fn<2, ' '> Space{};
    auto fnString = [](const std::string_view& tag, const OptString& opt) {
        std::stringstream ss;
        ss << tag << ": " << (opt ? *opt : "未设定") << std::endl;

        return ss.str();
        };

    std::stringstream ss;

    ss << Space << fnString("分支信息", sourceInfo.branchName);
    ss << Space << fnString("提交标识", sourceInfo.commitId);
    ss << Space << fnString("提交日期", sourceInfo.date);

    return std::cout << ss.str();
}
} // end g namespace