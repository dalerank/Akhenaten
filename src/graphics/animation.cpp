#include "graphics/animation.h"

#include "js/js_game.h"

void animation_t::load(archive arch) {
    pos = arch.r_vec2i("pos");
    base_id = (e_image_id)arch.r_int("base_id");
    anim_id = (e_image_id)arch.r_int("anim_id");
    max_frames = arch.r_int("max_frames");
    duration = arch.r_int("duration");
}

void animations_t::load(archive arch, pcstr section) {
    data.clear();
    arch.r_objects(section, [this](pcstr key, archive anim_arch) {
        data.push_back({});
        data.back().id = key;
        data.back().load(anim_arch);
    });
}