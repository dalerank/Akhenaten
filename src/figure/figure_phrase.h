#pragma once

#include "core/xstring.h"
#include "figure/figure_type.h"

using sound_key = xstring;

struct figure_phrase_t {
    e_figure_type type;
    sound_key prefix;
};

struct sound_key_state {
    sound_key prefix;
    bool valid;
};