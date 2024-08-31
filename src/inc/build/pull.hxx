#pragma once
#include "inc/source_info.h"

namespace g::build {
struct _Pull_fn {
    bool operator()(g::SourceInfo& sourceInfo) const {
        return false;
    }
};
} // end g::build namespace
