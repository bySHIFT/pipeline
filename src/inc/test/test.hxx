#pragma once
#include "inc/source_info.h"


namespace g::test {
struct _Test_fn {
    bool operator()(std::size_t projectId
        , const std::string_view& description
        , const g::SourceInfo& sourceInfo
        ) const {
        return false;
    }
};
} // end g::build namespace
