#pragma once
#include "inc/source_info.h"

namespace g::build {
namespace internal {
void Push(g::SourceInfo& sourceInfo) {
    auto PushId = [] { return uuid::CommitId(); };

    sourceInfo.pushId = PushId();
}
} // end internal namespace

struct _Push_fn {
    bool operator()(const std::string& jobName, g::SourceInfo& sourceInfo) const {
        internal::Push(sourceInfo);
        CoutItem(jobName + "后信息:");
        CoutSourceInfo(sourceInfo);

        return true;
    }
};
} // end g::build namespace
