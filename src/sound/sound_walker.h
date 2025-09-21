#pragma once

#include "core/archive.h"

struct figure_sound_t {
    xstring key;
    xstring sound;
    int group;
    int text;
    xstring phrase_key;
    bool operator==(const figure_sound_t &other) const noexcept { return key == other.key; }
    bool operator!=(const figure_sound_t &other) const noexcept { return key != other.key; }
    bool operator<(const figure_sound_t &other) const noexcept { return key < other.key; }
};

template<>
struct std::hash<figure_sound_t> {
    std::size_t operator()(const figure_sound_t &k) const noexcept {
        return (size_t)k.key._get();
    }
};
ANK_CONFIG_STRUCT(figure_sound_t, key, sound)

struct figure_sounds_t {
    std::unordered_set<figure_sound_t> sounds;

    void load(archive arch, pcstr section = "sounds");

    const figure_sound_t &operator[](xstring key) const {
        static figure_sound_t dummy{ "", "", 0, 0, "#undefined_phrase" };

        auto it = sounds.find({ key });
        return (it == sounds.end()) ? dummy : *it;
    }
};

namespace snd {
    xstring get_walker_reaction(xstring reaction);
}