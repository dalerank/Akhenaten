#pragma once

#include "core/archive.h"
#include "core/xstring.h"
#include "content/vfs.h"

struct figure_sound_t {
    bstring64 id;
    bstring64 fname;
    int group;
    int text;
    xstring phrase;

    void load(archive arch);
};

struct figure_sounds_t {
    std::vector<figure_sound_t> data;

    void load(archive arch, pcstr section = "sounds");

    const figure_sound_t &operator[](pcstr key) const {
        static figure_sound_t dummy;
        auto it = std::find_if(data.begin(), data.end(), [key] (auto &it) { return it.id.equals(key); });
        return (it == data.end()) ? dummy : *it;
    }
};

namespace snd {
    bstring64 get_walker_reaction(pcstr reaction);
}