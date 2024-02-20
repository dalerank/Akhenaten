#pragma once

#include "core/archive.h"
#include "graphics/image_desc.h"

#include <vector>

struct animation_t {
    bstring64 id;
    vec2i pos;
    e_image_id base_id = IMG_NONE;
    e_image_id anim_id = IMG_NONE;
    int max_frames;
    int duration;

    void load(archive arch);
};

struct animations_t {
    std::vector<animation_t> data;

    void load(archive arch, pcstr section = "animations");

    const animation_t &operator[](pcstr key) const {
        static animation_t dummy;
        auto it = std::find_if(data.begin(), data.end(), [key] (auto &it) { return it.id.equals(key); });
        return (it == data.end()) ? dummy : *it;
    }
};
