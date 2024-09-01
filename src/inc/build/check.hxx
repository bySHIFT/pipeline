#pragma once
#include "inc/source_info.h"

namespace g::build {
struct _Check_fn {
    bool operator()(const std::string& jobName, const g::SourceInfo& sourceInfo) const {
        CoutItem(jobName + "信息:");
        CoutSourceInfo(sourceInfo);

        return true;
    }
};
} // end g::build namespace
