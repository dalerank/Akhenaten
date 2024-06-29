#pragma once

#include "core/xstring.h"

struct id_anim_t {
    static const xstring base;
    static const xstring preview;
    static const xstring work;
    static const xstring none;
    static const xstring poof;
    static const xstring walk;
    static const xstring death;
    static const xstring swim;
};

const id_anim_t &animkeys();