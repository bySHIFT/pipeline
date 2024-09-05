#pragma once
#include "source_info.h"

namespace g::build {
namespace internal {
bool
BuildPostActions(const std::string& jobName
    , const g::SourceInfo& sourceInfo) {
    cout::Item(jobName + "信息:");
    CoutSourceInfo(sourceInfo);

    return random::DummyStatus();
}
} // end internal namespace
} // end g::build namespace
