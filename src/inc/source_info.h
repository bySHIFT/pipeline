#pragma once
#include "common.h"

namespace g {
struct SourceInfo {
    OptString branchName{};
    OptString commitId{};
    OptString date{};
};
} // end g namespace