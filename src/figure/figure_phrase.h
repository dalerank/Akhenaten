#pragma once

#include "core/bstring.h"
#include "figure/figure_type.h"

using sound_key = bstring64;

struct figure_phrase_t {
    e_figure_type type;
    sound_key prefix;
};

struct sound_key_state {
    sound_key prefix;
    bool valid;
};