#pragma once
#include "source_info.h"

namespace g::build {
namespace internal {
void Pull(g::SourceInfo& sourceInfo) {
    sourceInfo.commitId = uuid::CommitId();
    sourceInfo.date =
#if 0
        std::format("{}", std::chrono::system_clock::now());
#else
        ctime::Now();
#endif
}
} // end internal namespace

bool
Pull(const std::string& jobName
    , g::SourceInfo& sourceInfo
) {
    if (!sourceInfo.branchName)
        return false;

    cout::Item(jobName + "分支: " + *sourceInfo.branchName);
    internal::Pull(sourceInfo);
    cout::Item(jobName + "分支后信息:");
    CoutSourceInfo(sourceInfo);

    return true;
}
} // end g::build namespace
