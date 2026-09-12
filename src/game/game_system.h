#pragma once

#include "core/variant.h"
#include "core/profiler.h"
#include "js/js_game.h"

struct game_system {
    void emit(const bstring128& esname_str, const bvariant_map& args);
    void emit(const bstring128& esname_str);

    template <typename T>
    inline void emit(const T& ev, const bstring128& esname_str) {
        OZZY_PROFILER_SECTION(_, esname_str.c_str());

        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        emit(esname_str, *js_j);
    }

};

#define ANK_ESID(es) static pcstr esid() { return #es; }; static bstring128 esid(pcstr id) { return js_helpers::es_hash_str(#es, id); };