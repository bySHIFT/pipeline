#pragma once
#include "source_info.h"

namespace g::build {
namespace internal {
void Build(g::SourceInfo& sourceInfo) {
    sourceInfo.buildId = uuid::CommitId();
}
} // end internal namespace

bool
Build(const std::string& jobName
    , g::SourceInfo& sourceInfo
) {
#if 0
    cout::Item(jobName + "信息:");
    CoutSourceInfo(sourceInfo);
#endif

    internal::Build(sourceInfo);
    cout::Item(jobName + "后信息:");
    CoutSourceInfo(sourceInfo);

    return true;
}
} // end g::build namespace
