#pragma once
#include "inc/source_info.h"

namespace g::build {
namespace internal {
void Pull(g::SourceInfo& sourceInfo) {
    sourceInfo.commitId = uuid::CommitId();
    sourceInfo.date = std::format("{}", std::chrono::system_clock::now());
}
} // end internal namespace

struct _Pull_fn {
    bool operator()(const std::string& jobName, g::SourceInfo& sourceInfo) const {
        if (!sourceInfo.branchName)
            return false;

        CoutItem(jobName + "分支: " + *sourceInfo.branchName);
        internal::Pull(sourceInfo);
        CoutItem(jobName + "分支后信息:");
        CoutSourceInfo(sourceInfo);

        return true;
    }
};
} // end g::build namespace
