#pragma once

#include "core/bstring.h"
#include "figure/type.h"

using sound_key = bstring64;

struct e_figure_sound {
    e_figure_type type;
    sound_key prefix;
};