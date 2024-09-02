#pragma once
#include "source_info.h"

namespace g::build {
bool
Check(const std::string& jobName
    , const g::SourceInfo& sourceInfo
) {
    cout::Item(jobName + "信息:");
    CoutSourceInfo(sourceInfo);

    return true;
}
} // end g::build namespace
