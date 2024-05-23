#include "graphics/animation.h"

#include "js/js_game.h"
#include "graphics/image_desc.h"
#include "graphics/image.h"

void animation_t::load(archive arch) {
    pos = arch.r_vec2i("pos");
    base_id = (e_image_id)arch.r_int("base_id");
    anim_id = (e_image_id)arch.r_int("anim_id");
    pack = arch.r_int("pack");
    iid = arch.r_int("id");
    offset = arch.r_int("offset");
    max_frames = arch.r_int("max_frames");
    duration = arch.r_int("duration");
}

int animation_t::first_img() const {
    int image_id = 0;
    if (anim_id) {
        image_id = image_group(anim_id);
    } else {
        image_id = image_id_from_group(pack, iid) + offset;
    }
    
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

void animation_context::update(bool refresh_only) {
    frame += refresh_only ? 0 : 1;

    if (frame >= max_frames * frame_duration) {
        frame = 0;
    }
}
