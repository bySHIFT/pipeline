#pragma once
#include "inc/source_info.h"


namespace g::deploy {
struct _Deploy_fn {
    bool operator()(const std::string& jobName, const std::string_view& description
        , const OptString& pushId
        ) const {
        return true;
    }
};
} // end g::build namespace
