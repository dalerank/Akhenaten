#include "figure/figure.h"

#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "graphics/animation.h"
#include "core/stable_array.h"
#include "core/profiler.h"

#include "js/js_game.h"

static const int CORPSE_IMAGE_OFFSETS[128] = {
    0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static const int MISSILE_LAUNCHER_OFFSETS[128] = {
    0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void cc_coords_to_pixel_offset(int cross_country_x, int cross_country_y, int* pixel_x, int* pixel_y) {
    int dir = city_view_orientation();
    if (dir == DIR_0_TOP_RIGHT || dir == DIR_4_BOTTOM_LEFT) {
        int base_pixel_x = 2 * cross_country_x - 2 * cross_country_y;
        int base_pixel_y = cross_country_x + cross_country_y;
        *pixel_x = dir == DIR_0_TOP_RIGHT ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_0_TOP_RIGHT ? base_pixel_y : -base_pixel_y;
    } else {
        int base_pixel_x = 2 * cross_country_x + 2 * cross_country_y;
        int base_pixel_y = cross_country_x - cross_country_y;
        *pixel_x = dir == DIR_2_BOTTOM_RIGHT ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_6_TOP_LEFT ? base_pixel_y : -base_pixel_y;
    }
}

vec2i figure::tile_pixel_coords() {
    int x;
    int y;
    if (!use_cross_country) {
        // todo? too complicated...
        //        cc_coords_to_pixel_offset((cc_coords.x - 15) % 15, (cc_coords.y) % 15, &x, &y);
        int prg_r = progress_on_tile > 7 ? progress_on_tile - 15 : progress_on_tile;
        int prg_x = 2 * (prg_r);
        int prg_y = (prg_r);
        switch ((8 + direction - city_view_orientation()) % 8) {
        case 0: return {prg_x, -prg_y};
        case 1: return {2 * prg_x, 0};
        case 2: return {prg_x, prg_y};
        case 3: return {0, 2 * prg_y};
        case 4: return {-prg_x, prg_y};
        case 5: return {-2 * prg_x, 0};
        case 6: return {-prg_x, -prg_y};
        case 7: return {0, -2 * prg_y};
        }
    } else {
        cc_coords_to_pixel_offset(cc_coords.x % 15, cc_coords.y % 15, &x, &y);
    }

    return {x, y};
}

void figure::image_set_animation(const xstring &anim) {
    image_set_animation(dcast()->anim(anim));
}

void figure::image_set_animation(const animation_t &anim) {
    if (anim.pack > 0 || anim.id > 0) {
        this->animctx = anim;
        return;
    }
}

void figure::image_set_animation(int collection, int group, int offset, int max_frames, int duration, bool loop) {
    animctx.base = image_id_from_group(collection, group);
    animctx.offset = offset;
    animctx.max_frames = max_frames;
    animctx.frame_duration = std::max(1, duration);
    animctx.loop = loop;
}

void figure::figure_image_update(bool refresh_only) {
    OZZY_PROFILER_FUNCTION();
    if (!animctx.valid()) {
        return;
    }

    animctx.update(refresh_only);

    dcast()->main_image_update();
    dcast()->cart_image_update();
}

int figure::figure_image_corpse_offset() {
    int type_offset = 96;
    switch (type) {
    default:
        ; // nothing
        break;

    case FIGURE_BIRDS:
        type_offset = 104;
        break;
    case FIGURE_INDIGENOUS_NATIVE:
        type_offset = 441;
        break;
    case FIGURE_JAVELIN:
    case FIGURE_FCHARIOTEER:
        type_offset = 144;
        break;
    case FIGURE_ENEMY_EGYPTIAN_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_FAST_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD:
        type_offset = 593;
        break;
    case FIGURE_ENEMY_EGYPTIAN_ELEPHANT:
        type_offset = 705;
        break;
    case FIGURE_ENEMY_EGYPTIAN_CAMEL:
    case FIGURE_ENEMY_EGYPTIAN_CHARIOT:
    case FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER:
    case FIGURE_ENEMY_EGYPTIAN_AXE:
        type_offset = 745;
        break;
    case FIGURE_ENEMY_EGYPTIAN_SPEAR:
        type_offset = 641;
        break;
    //case FIGURE_ENEMY_EGYPTIAN_FAST_SPEAR:
    //    formation* m = formation_get(formation_id);
    //    if (m->enemy_type == ENEMY_0_BARBARIAN)
    //        type_offset = 441;
    //    else if (m->enemy_type == ENEMY_1_ASSYRIAN)
    //        type_offset = 641;
    //    else if (m->enemy_type == ENEMY_4_HITTITE)
    //        type_offset = 593;
    //    break;
    }
    return CORPSE_IMAGE_OFFSETS[wait_ticks / 2];// +type_offset;
}

int figure::figure_image_missile_launcher_offset() {
    return MISSILE_LAUNCHER_OFFSETS[attack_image_offset / 2];
}
int figure::figure_image_direction() {
    int dir = direction - city_view_orientation();
    if (dir < 0) {
        dir += 8;
    }
    return dir;
}

int figure::figure_image_normalize_direction(int direction) {
    int normalized_direction = direction - city_view_orientation();
    if (normalized_direction < 0)
        normalized_direction += 8;

    return normalized_direction;
}
