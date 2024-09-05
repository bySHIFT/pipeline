#pragma once
#include "common.hxx"

namespace g::build {
bool
Check(const std::string& jobName
    , const g::SourceInfo& sourceInfo
) {
    return internal::BuildPostActions(jobName, sourceInfo);
}
} // end g::build namespace
