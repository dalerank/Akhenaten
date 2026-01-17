#include "graphics/animation.h"

#include "js/js_game.h"

#include "graphics/image_desc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"

int animation_t::global_hashtime = 0;
animation_t animations_t::dummy;

bool animation_t::archive_load(archive arch) {
    duration = std::max<int16_t>(1, duration);
    loop = arch.r_bool("loop", true);
    hashtime = global_hashtime;
    bool internal_offset = arch.r_bool("internal_offset", false);
    flags = (internal_offset ? ImgFlag_InternalOffset : 0);
    return true;
}

int animation_t::first_img() const {
    if (cached_imgid > 0) {
        return cached_imgid;
    }

    if (!path.empty()) {
        image_desc desc = image_desc_from_name(path);
        cached_imgid = desc.tid();
        return cached_imgid;
    }

    cached_imgid = image_id_from_group(pack, id) + offset;
    return cached_imgid;
}

void animation_context::setup(const animation_t &anim) {
    if (key == anim.key && hashtime == anim.hashtime) {
        return;
    }

    key = anim.key;
    base = image_id_from_group(anim.pack, anim.id);
    offset = anim.offset;
    max_frames = anim.max_frames;
    frame_duration = std::max<int16_t>(1, anim.duration);
    pos = anim.pos;
    loop = anim.loop;
    was_finished = false;
    sframe = anim.start_frame;
    frame = anim.start_frame;
    is_reverse = anim.reverse;
    can_reverse = is_reverse || anim.can_reverse;
    hashtime = anim.hashtime;
    flags = anim.flags;
}

void animation_context::update(bool refresh_only) {
    if (was_finished) {
        tick_updated = true;
        return;
    }

    if (!can_reverse) {
        frame += refresh_only ? 0 : 1;
        if (frame >= max_frames * frame_duration) {
            was_finished = !loop;
            frame = loop ? 0 : (max_frames * frame_duration - 1);
            if (on_finished_cb) {
                on_finished_cb();
                on_finished_cb = nullptr;
            }
        }
        tick_updated = true;
        return;
    } 

    if (is_reverse) {
        frame -= refresh_only ? 0 : 1;
        if (frame < 1) {
            frame = 0;
            is_reverse = false;
            was_finished = !loop;
        }
        tick_updated = true;
        return;
    } 

    frame += refresh_only ? 0 : 1;
    if (frame >= (max_frames + 1) * frame_duration) {
        frame = max_frames * frame_duration;
        is_reverse = true;
    }
    tick_updated = true;
}

void animations_t::initialize() {
    auto it = data.find("_pack");
    if (it == data.end()) {
        return;
    }

    const animation_t& defanim = it->second;
    for (auto &anim : data) {
        if (anim.second.pack == 0) {
            anim.second.pack = defanim.pack;
        }

        if (!anim.second.path.empty()) {
            anim.second.pack = 0;
            anim.second.id = 0;
            anim.second.offset = 0;
        }
    }
}
