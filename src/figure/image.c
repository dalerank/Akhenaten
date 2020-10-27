#include "image.h"

#include "city/view.h"

static const int CORPSE_IMAGE_OFFSETS[128] = {
        0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static const int MISSILE_LAUNCHER_OFFSETS[128] = {
        0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const int CART_OFFSETS_X[] = {17, 22, 17, 0, -17, -22, -17, 0};
static const int CART_OFFSETS_Y[] = {-7, -1, 7, 11, 6, -1, -7, -12};

#include "core/image.h"
#include "game/resource.h"

void figure::image_set_animation(int group, int offset, int max_frames, int duration) {
    anim_base = image_id_from_group(group);
    anim_offset = offset;
    anim_max_frames = max_frames;
    if (duration <= 0)
        duration = 1;
    anim_frame_duration = duration;
}
void figure::figure_image_update() {
    // advance animation frame
    anim_frame++;
    if (anim_frame >= anim_max_frames * anim_frame_duration)
        anim_frame = 0;

    switch (type) {
        case FIGURE_JAVELIN:
        case FIGURE_ARROW:
        case FIGURE_HUNTER_ARROW: {
            int dir = (16 + direction - 2 * city_view_orientation()) % 16;
            sprite_image_id = anim_base + 16 + dir;
            break;
        }
        default:
            // play death animation if it's dying, otherwise always follow the same pattern - offsets are set during action logic
            if (state == FIGURE_STATE_DYING)
                sprite_image_id = anim_base + figure_image_corpse_offset();
            else {
                int effective_frame = anim_frame / anim_frame_duration;
                sprite_image_id = anim_base + anim_offset + figure_image_direction() + 8 * effective_frame;
            }

            // null images
            if (anim_base <= 0)
                sprite_image_id = image_id_from_group(GROUP_SYSTEM_GRAPHICS) + 3;
            break;
    }
}
//int testcart = 0;
void figure::cart_update_image() {

    // determine cart sprite
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART);
        if (loads_counter > 0) {
            short amount_offset = 2;
            if (loads_counter <= 2)
                amount_offset = 0;
            else if (loads_counter <= 4)
                amount_offset = 1;
//            amount_offset = testcart;
//            testcart++; if (testcart >= 3) testcart = 0;
            cart_image_id += 8 + 24 * (resource_id - 1) + 8 * amount_offset;

            // adjust sprite for sled resources (blocks/chariots/etc.)
            short res_single_load[] = {12, 24, 25, 26, 27, 28, 30, 35, 999};
            for (int i = 0; res_single_load[i] < 999; i++)
                if (resource_id > res_single_load[i])
                    cart_image_id -= 16;
        }
    } else {
        if (loads_counter == 1) {
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + 8 * resource_id - 8 +
                            resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
        } else {
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART) + 8 * resource_id;
            cart_image_id += resource_image_offset(resource_id, RESOURCE_IMAGE_CART);
        }
    }

    int dir = figure_image_normalize_direction( direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + figure_image_corpse_offset() + 96;
        cart_image_id = 0;
    } else
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + dir + 8 * anim_frame;
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
//        if (loads_counter >= 8)
//            y_offset_cart -= 40;
    }
}
int figure::figure_image_corpse_offset() {
    int type_offset = 96;
    switch (type) {
        case FIGURE_SHEEP:
            type_offset = 104; break;
        case FIGURE_INDIGENOUS_NATIVE:
            type_offset = 441; break;
        case FIGURE_TOWER_SENTRY:
            type_offset = 136; break;
        case FIGURE_JAVELIN:
        case FIGURE_FORT_MOUNTED:
            type_offset = 144; break;
        case FIGURE_FORT_LEGIONARY:
        case FIGURE_ENEMY_CAESAR_LEGIONARY:
            type_offset = 152; break;
        case FIGURE_ENEMY44_SWORD:
        case FIGURE_ENEMY45_SWORD:
        case FIGURE_ENEMY50_SWORD:
            type_offset = 593; break;
        case FIGURE_ENEMY47_ELEPHANT:
            type_offset = 705; break;
        case FIGURE_ENEMY46_CAMEL:
        case FIGURE_ENEMY48_CHARIOT:
        case FIGURE_ENEMY52_MOUNTED_ARCHER:
        case FIGURE_ENEMY53_AXE:
            type_offset = 745; break;
        case FIGURE_ENEMY51_SPEAR:
            type_offset = 641; break;
        case FIGURE_ENEMY49_FAST_SWORD:
            formation *m = formation_get(formation_id);
            if (m->enemy_type == ENEMY_0_BARBARIAN)
                type_offset = 441;
            else if (m->enemy_type == ENEMY_1_NUMIDIAN)
                type_offset = 641;
            else if (m->enemy_type == ENEMY_4_GOTH)
                type_offset = 593;
            break;
    }
    return CORPSE_IMAGE_OFFSETS[wait_ticks / 2] + type_offset;
}
void figure::figure_image_set_cart_offset(int direction) {
    x_offset_cart = CART_OFFSETS_X[direction];
    y_offset_cart = CART_OFFSETS_Y[direction];
}
int figure::figure_image_missile_launcher_offset() {
    return MISSILE_LAUNCHER_OFFSETS[attack_image_offset / 2];
}
int figure::figure_image_direction() {
    int dir = direction - city_view_orientation();
    if (dir < 0)
        dir += 8;
    return dir;
}

int figure_image_normalize_direction(int direction) {
    int normalized_direction = direction - city_view_orientation();
    if (normalized_direction < 0)
        normalized_direction += 8;

    return normalized_direction;
}
