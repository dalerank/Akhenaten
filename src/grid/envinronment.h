#pragma once

#include "core/archive.h"

struct vegetation_opt {
    int8_t random_max;
    int8_t random_min;
};

ANK_CONFIG_STRUCT(vegetation_opt, random_max, random_min);