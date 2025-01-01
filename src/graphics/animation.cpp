#include "graphics/animation.h"

#include "js/js_game.h"

#include "graphics/image_desc.h"
#include "graphics/image.h"

int animation_t::global_hashtime = 0;

void animation_t::load(archive arch) {
    pos = arch.r_vec2i("pos");
    pack = arch.r_int("pack");
    iid = arch.r_int("id");
    offset = arch.r_int("offset");
    max_frames = arch.r_int("max_frames");
    duration = arch.r_int("duration", 1);
    can_reverse = arch.r_bool("can_reverse");
    loop = arch.r_bool("loop", true);
    start_frame = arch.r_int("start_frame", 0);
    reverse = arch.r_bool("reverse", false);
    hashtime = global_hashtime;
}

int animation_t::first_img() const {
    int image_id = image_id_from_group(pack, iid) + offset;   
    return image_id;
}

void animations_t::load(archive arch, pcstr section) {
    data.clear();
    arch.r_objects(section, [this](pcstr key, archive anim_arch) {
        data.push_back({});
        data.back().id = key;
        data.back().load(anim_arch);
    });
}

void animation_context::setup(const animation_t &anim) {
    if (id == anim.id && hashtime == anim.hashtime) {
        return;
    }

    id = anim.id;
    base = image_id_from_group(anim.pack, anim.iid);
    offset = anim.offset;
    max_frames = anim.max_frames;
    frame_duration = std::max(1, anim.duration);
    pos = anim.pos;
    loop = anim.loop;
    was_finished = false;
    frame = anim.start_frame;
    is_reverse = anim.reverse;
    can_reverse = is_reverse || anim.can_reverse;
    hashtime = anim.hashtime;
}

void animation_context::update(bool refresh_only) {
    if (!can_reverse) {
        frame += refresh_only ? 0 : 1;
        if (frame >= max_frames * frame_duration) {
            was_finished = !loop;
            frame = loop ? 0 : (max_frames * frame_duration - 1);
        }
    } else {
        if (is_reverse) {
            frame -= refresh_only ? 0 : 1;
            if (frame < 1) {
                frame = 0;
                is_reverse = false;
                was_finished = !loop;
            }
        } else {
            frame += refresh_only ? 0 : 1;
            if (frame >= (max_frames+1) * frame_duration) {
                frame = max_frames * frame_duration;
                is_reverse = true;
            }
        }
    }
    tick_updated = true;
}
