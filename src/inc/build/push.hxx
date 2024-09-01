#pragma once
#include "inc/source_info.h"

namespace g::build {
struct _Push_fn {
    bool operator()(const g::SourceInfo& sourceInfo) const {
        return true;
    }
};
} // end g::build namespace
