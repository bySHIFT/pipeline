#pragma once
#include "common.hxx"

namespace g::build {
namespace internal {
void Push(g::SourceInfo& sourceInfo) {
    auto PushId = [] { return random::CommitId(); };

    sourceInfo.pushId = PushId();
}
} // end internal namespace

bool
Push(const std::string& jobName
    , g::SourceInfo& sourceInfo
) {
    internal::Push(sourceInfo);
    return internal::BuildPostActions(jobName, sourceInfo);
}
} // end g::build namespace
