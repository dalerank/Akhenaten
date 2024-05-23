#pragma once

#include "core/archive.h"
#include "graphics/image_desc.h"

#include <vector>

struct animation_t {
    bstring64 id;
    vec2i pos;
    e_image_id base_id = IMG_NONE;
    e_image_id anim_id = IMG_NONE;
    int pack;
    int iid;
    int offset;
    int max_frames;
    int duration;
    bool can_reverse;

    void load(archive arch);
    int first_img() const;
};

struct animation_context {
    int base;
    int offset;
    vec2i pos;
    uint8_t frame_duration;
    uint8_t max_frames;
    uint8_t frame;
    bool can_reverse;
    bool is_reverse = false;

    void update(bool refresh_only);
    inline bool valid() const { return base > 0; }
    inline int current_frame() const { return std::clamp<int>(frame / frame_duration, 0, max_frames); }
    inline int start() const { return base + offset; }
};

struct animations_t {
    std::vector<animation_t> data;

    void load(archive arch, pcstr section = "animations");

    const animation_t &operator[](pcstr key) const {
        static animation_t dummy;
        if (data.empty()) {
            return dummy;
        }
        auto it = std::find_if(data.begin(), data.end(), [key] (auto &it) { return it.id.equals(key); });
        return (it == data.end()) ? dummy : *it;
    }
};
