#pragma once

#include "core/archive.h"
#include "core/xstring.h"
#include "content/vfs.h"

struct figure_sound_t {
    xstring id;
    xstring fname;
    textid phrase;
    xstring phrase_key;

    void load(archive arch);
};

struct figure_sounds_t {
    std::vector<figure_sound_t> data;

    void load(archive arch, pcstr section = "sounds");

    const figure_sound_t &operator[](xstring key) const {
        static figure_sound_t dummy{ "", "", {0, 0}, "#undefined_phrase" };

        auto it = std::find_if(data.begin(), data.end(), [key] (auto &it) { return it.id == key; });
        return (it == data.end()) ? dummy : *it;
    }
};

namespace snd {
    xstring get_walker_reaction(xstring reaction);
}