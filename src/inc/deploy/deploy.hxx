#pragma once
#include "source_info.h"


namespace g::deploy {
bool
Deploy(const std::string& jobName, const std::string_view& description
    , const OptString& pushId
) {
    ElapsedSecondsDummyJob(5, 4);

    return true;
}
} // end g::build namespace
