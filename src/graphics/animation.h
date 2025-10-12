#pragma once

#include "core/archive.h"
#include "graphics/image_desc.h"
#include "graphics/animkeys.h"
#include "core/system_time.h"

struct animation_timer {
    time_millis last_update;
    bool should_update;
};

struct animation_t {
    xstring key;
    vec2i pos;
    int pack;
    int id;
    int offset;
    int max_frames;
    int duration;
    int start_frame;
    int hashtime = 0;
    uint32_t flags;
    bool can_reverse;
    bool loop = true;
    bool reverse = false;

    static int global_hashtime;

    bool archive_load(archive arch);
    image_desc to_desc() const { return { pack, id, offset }; }
    int first_img() const;
};
ANK_CONFIG_STRUCT(animation_t, pos, pack, id, offset, max_frames, duration, start_frame, can_reverse, reverse)

struct animation_context {
    xstring key;
    int base;
    int offset;
    int hashtime = -1;
    vec2i pos;
    uint8_t frame_duration = 1;
    uint16_t max_frames;
    uint16_t sframe;
    uint16_t frame;
    uint32_t flags;
    bool can_reverse;
    bool loop = true;
    bool is_reverse = false;
    bool was_finished = false;
    bool tick_updated = false;

    void setup(const animation_t &anim);
    void update(bool refresh_only);
    inline bool valid() const { return base > 0; }
    inline int current_frame() const { return std::clamp<int>(frame / frame_duration, 0, max_frames); }
    inline int start_frame() const { return base + offset; }
    inline void restart() { was_finished = false; frame = sframe; }
    inline bool finished() const {
        if (was_finished) return true;
        
        const int cframe = current_frame();
        if (is_reverse) {
            return cframe == 0;
        }
        
        return cframe >= max_frames;
    }

    animation_context& operator=(const animation_t &anim) { setup(anim); return *this; }
};

struct animations_t {
    std::unordered_map<xstring, animation_t> data;
    static animation_t dummy;

    const animation_t &operator[](const xstring &key) const {
        if (data.empty()) {
            return dummy;
        }
        auto it = data.find(key);
        return (it == data.end()) ? dummy : it->second;
    }
};

template<> inline void archive::r<animations_t>(pcstr name, animations_t &v) { r(name, v.data);  }