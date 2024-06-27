#pragma once

#include "core/xstring.h"

struct id_anim_t {
    static const xstring base;
    static const xstring preview;
    static const xstring work;
    static const xstring none;
};

const id_anim_t &animkeys();