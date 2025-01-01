#pragma once

#include "core/archive.h"
#include "graphics/image_desc.h"
#include "graphics/animkeys.h"
#include "core/system_time.h"

#include <vector>

struct animation_timer {
    time_millis last_update;
    bool should_update;
};

struct animation_t {
    xstring id;
    vec2i pos;
    int pack;
    int iid;
    int offset;
    int max_frames;
    int duration;
    int start_frame;
    int hashtime = 0;
    bool can_reverse;
    bool loop = true;
    bool reverse = false;

    static int global_hashtime;

    void load(archive arch);
    int first_img() const;
};

struct animation_context {
    xstring id;
    int base;
    int offset;
    int hashtime = -1;
    vec2i pos;
    uint8_t frame_duration = 1;
    uint16_t max_frames;
    uint16_t frame;
    bool can_reverse;
    bool loop = true;
    bool is_reverse = false;
    bool was_finished = false;
    bool tick_updated = false;

    void setup(const animation_t &anim);
    void update(bool refresh_only);
    inline bool valid() const { return base > 0; }
    inline int current_frame() const { return std::clamp<int>(frame / frame_duration, 0, max_frames); }
    inline int start() const { return base + offset; }
    inline bool finished() const { return was_finished || current_frame() >= max_frames; }
};

struct animations_t {
    std::vector<animation_t> data;

    void load(archive arch, pcstr section = "animations");

    const animation_t &operator[](const xstring &key) const {
        static animation_t dummy;
        if (data.empty()) {
            return dummy;
        }
        auto it = std::find_if(data.begin(), data.end(), [key] (auto &it) { return it.id == key; });
        return (it == data.end()) ? dummy : *it;
    }
};
