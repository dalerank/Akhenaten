#include "building/building_animation.h"

#include "grid/water_supply.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "game/game.h"
#include "grid/sprite.h"

int generic_sprite_offset(int grid_offset, int max_frames, int anim_speed) {
    //    const image *img = image_get(image_id);
    //    if (!max_frames)
    //        max_frames = img->animation.num_sprites;
    //    int anim_speed = img->animation.speed_id;
    if (!game.animation_should_advance(anim_speed))
        return map_sprite_animation_at(grid_offset) & 0x7f;

    // advance animation
    int new_sprite = 0;
    //    bool is_reverse = false;
    //    if (img->animation.can_reverse) {
    //        if (map_sprite_animation_at(grid_offset) & 0x80)
    //            is_reverse = true;
    //
    //        int current_sprite = map_sprite_animation_at(grid_offset) & 0x7f;
    //        if (is_reverse) {
    //            new_sprite = current_sprite - 1;
    //            if (new_sprite < 1) {
    //                new_sprite = 1;
    //                is_reverse = false;
    //            }
    //        } else {
    //            new_sprite = current_sprite + 1;
    //            if (new_sprite > max_frames) {
    //                new_sprite = max_frames;
    //                is_reverse = true;
    //            }
    //        }
    //    } else // Absolutely normal case
    new_sprite = map_sprite_animation_at(grid_offset) + 1;
    if (new_sprite > max_frames)
        new_sprite = 1;

    map_sprite_animation_set(grid_offset, new_sprite);
    return new_sprite;
}

int building::animation_offset(int image_id, int grid_offset, int max_frames, int duration) {
    if (building_is_workshop(type) && (!workshop_has_resources() || num_workers <= 0)) {
        return 0;
    }

    if (!dcast()->can_play_animation()) {
        return 0;
    }

    const image_t* img = image_get(image_id);
    if (!max_frames) {
        max_frames = img->animation.num_sprites;
    }

    int anim_speed = dcast()->animation_speed(img->animation.speed_id);

    if (!game.animation_should_advance(anim_speed)) {
        return map_sprite_animation_at(grid_offset) & 0x7f;
    }

    // advance animation
    int new_sprite = 0;
    bool is_reverse = false;
    if (img->animation.can_reverse) {
        if (map_sprite_animation_at(grid_offset) & 0x80)
            is_reverse = true;

        int current_sprite = map_sprite_animation_at(grid_offset) & 0x7f;
        if (is_reverse) {
            new_sprite = current_sprite - 1;
            if (new_sprite < 1) {
                new_sprite = 1;
                is_reverse = false;
            }
        } else {
            new_sprite = current_sprite + 1;
            if (new_sprite > max_frames) {
                new_sprite = max_frames;
                is_reverse = true;
            }
        }
    } else {
        // Absolutely normal case
        new_sprite = map_sprite_animation_at(grid_offset) + 1;
        if (new_sprite > max_frames) {
            new_sprite = 1;
        }
    }

    map_sprite_animation_set(grid_offset, is_reverse ? new_sprite | 0x80 : new_sprite);
    return new_sprite;
}