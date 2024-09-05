#pragma once
#include "common.hxx"

namespace g::build {
namespace internal {
void Pull(g::SourceInfo& sourceInfo) {
    sourceInfo.commitId = random::CommitId();
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

    internal::Pull(sourceInfo);
    return internal::BuildPostActions(jobName, sourceInfo);
}
} // end g::build namespace
