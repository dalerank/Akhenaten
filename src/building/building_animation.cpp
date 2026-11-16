#include "building/building.h"

#include "building/building_impl.h"
#include "graphics/image.h"
#include "grid/image.h"

#include <algorithm>

const animation_context* building::sprite_anim(int sprite_id) const {
    if (sprite_id <= 0) {
        return nullptr;
    }
    for (const auto& a : sprite_anims) {
        if (a.base == sprite_id && a.valid()) {
            return &a;
        }
    }
    return nullptr;
}

void building_impl::register_sprite_anim(int sprite_id, int max_frames, int duration) {
    const image_t* img = sprite_id > 0 ? image_get(sprite_id) : nullptr;
    if (!img) {
        return;
    }

    auto& slots = base.sprite_anims;
    for (int i = 0; i < (int)slots.size(); ++i) {
        if (slots[i].base == sprite_id) {
            base.sprite_anims_seen |= (1 << i);
            return;
        }
    }

    const int frames = max_frames ? max_frames : img->animation.num_sprites;
    if (frames <= 0) {
        return;
    }
    for (int i = 0; i < (int)slots.size(); ++i) {
        if (slots[i].base > 0 || (base.sprite_anims_seen & (1 << i))) {
            continue;
        }
        animation_context& a = slots[i];
        a = animation_context{};
        a.base = sprite_id;
        a.offset = 1;
        a.max_frames = (uint16_t)frames;
        a.frame_duration = (uint8_t)std::clamp(duration > 0 ? duration : (int)img->animation.speed_id, 1, 255);
        a.can_reverse = img->animation.can_reverse;
        a.loop = true;
        a.frame = 0;
        base.sprite_anims_seen |= (1 << i);
        return;
    }
}

void building_impl::update_sprite_anims() {
    if (!current_params().flags.draw_normal_anim && !base.anim.key) {
        register_sprite_anim(map_image_at(base.tile), 0, 0);
    }
}

void building_impl::tick_sprite_anims(bool refresh_only) {
    base.sprite_anims_seen = 0;
    update_sprite_anims();
    for (int i = 0; i < (int)base.sprite_anims.size(); ++i) {
        animation_context& a = base.sprite_anims[i];
        if (!(base.sprite_anims_seen & (1 << i))) {
            a.base = 0;
        } else if (base.play_animation) {
            a.update(refresh_only);
        }
    }
}
