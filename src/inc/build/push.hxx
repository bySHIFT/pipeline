#pragma once
#include "source_info.h"

namespace g::build {
namespace internal {
void Push(g::SourceInfo& sourceInfo) {
    auto PushId = [] { return uuid::CommitId(); };

    sourceInfo.pushId = PushId();
}
} // end internal namespace

bool
Push(const std::string& jobName
    , g::SourceInfo& sourceInfo
) {
    internal::Push(sourceInfo);
    cout::Item(jobName + "后信息:");
    CoutSourceInfo(sourceInfo);

    return true;
}
} // end g::build namespace
