#pragma once

#include "core/xstring.h"
#include "figure/figure_type.h"

using sound_key = xstring;

struct sound_key_state {
    sound_key prefix;
    bool valid;
};