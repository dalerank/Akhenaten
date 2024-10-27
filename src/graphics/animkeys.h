#pragma once

#include "core/xstring.h"

struct id_anim_t {
    static const xstring base;
    static const xstring base_work;
    static const xstring fancy;
    static const xstring fancy_work;
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
    static const xstring back;
    static const xstring bubbles;
    static const xstring point;
    static const xstring work_n;
    static const xstring work_w;
    static const xstring work_s;
    static const xstring work_e;
    static const xstring wait_n;
    static const xstring wait_w;
    static const xstring wait_s;
    static const xstring wait_e;
    static const xstring eating;
    static const xstring idle;
    static const xstring attack;
    static const xstring farmland;
    static const xstring square;
    static const xstring juggler;
    static const xstring barley;
    static const xstring wood;
};

const id_anim_t &animkeys();