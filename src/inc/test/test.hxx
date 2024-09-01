#pragma once
#include "inc/source_info.h"


namespace g::test {
struct _Test_fn {
    bool operator()(const std::string& jobName, std::size_t projectId
        , const std::string_view& description
        , const OptString& pushId
        ) const {
        return true;
    }
};
} // end g::build namespace
