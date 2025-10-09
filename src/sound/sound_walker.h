#pragma once

#include "core/archive.h"

struct figure_sound_t {
    xstring key;
    xstring sound;
    int group;
    int text;
    xstring phrase_key;
};
ANK_CONFIG_STRUCT(figure_sound_t, key, sound)

using figure_sounds_map = std::unordered_map<xstring, figure_sound_t>;
struct figure_sounds_t {
    figure_sounds_map data;

    const figure_sound_t &operator[](const xstring& key) const {
        static figure_sound_t dummy{ "", "", 0, 0, "#undefined_phrase" };

        auto it = data.find( key );
        return (it == data.end()) ? dummy : it->second;
    }
};

template<> inline void archive::r<figure_sounds_t>(pcstr name, figure_sounds_t &v) { r(name, v.data); }

namespace snd {
    xstring get_walker_reaction(xstring reaction);
}