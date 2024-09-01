#pragma once
#include "inc/source_info.h"

namespace g::build {
struct _Build_fn {
    bool operator()(g::SourceInfo& sourceInfo) const {
        return true;
    }
};
} // end g::build namespace
