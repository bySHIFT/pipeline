#pragma once
#include "common.hxx"

namespace g::build {
namespace internal {
void Build(g::SourceInfo& sourceInfo) {
    sourceInfo.buildId = random::CommitId();
}
} // end internal namespace

bool
Build(const std::string& jobName
    , g::SourceInfo& sourceInfo
) {
    internal::Build(sourceInfo);
    return internal::BuildPostActions(jobName, sourceInfo);
}
} // end g::build namespace
