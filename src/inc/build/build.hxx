#pragma once
#include "inc/source_info.h"

namespace g::build {
namespace internal {
void Build(g::SourceInfo& sourceInfo) {
    sourceInfo.buildId = uuid::CommitId();
}
} // end internal namespace

struct _Build_fn {
    bool operator()(const std::string& jobName, g::SourceInfo& sourceInfo) const {
        CoutItem(jobName + "信息:");
        CoutSourceInfo(sourceInfo);

        internal::Build(sourceInfo);
        CoutItem(jobName + "后信息:");
        CoutSourceInfo(sourceInfo);

        return true;
    }
};
} // end g::build namespace
