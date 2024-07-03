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
    static const xstring fight;
    static const xstring hunt;
    static const xstring pack;
    static const xstring unpack;
    static const xstring move_pack;
    static const xstring fight_fire;
};

const id_anim_t &animkeys();