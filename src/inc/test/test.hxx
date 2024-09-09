#pragma once
#include "source_info.h"


namespace g::test {
bool
Test(const std::string& jobName, std::size_t projectId
    , const std::string_view& description
    , const OptString& pushId
) {
    ElapsedSecondsDummyJob(20, 12);

    return true;
}
} // end g::build namespace
