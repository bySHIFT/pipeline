#pragma once
#include "common.hxx"

namespace g::build {
bool
Check(const std::string& jobName
    , const g::SourceInfo& sourceInfo
) {
    ElapsedSecondsDummyJob(10, 7);

    return internal::BuildPostActions(jobName, sourceInfo);
}
} // end g::build namespace
