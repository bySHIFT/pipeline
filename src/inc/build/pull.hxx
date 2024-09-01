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
    bool operator()(g::SourceInfo& sourceInfo) const {
        if (!sourceInfo.branchName)
            return false;

        CoutItem("构建指定分支: " + *sourceInfo.branchName);
        internal::Pull(sourceInfo);
        CoutItem("获取指定分支后信息:");
        CoutSourceInfo(sourceInfo);

        return true;
    }
};
} // end g::build namespace
