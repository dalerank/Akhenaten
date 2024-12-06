#include "building/building_fort.h"

#include "building/rotation.h"
#include "building/count.h"
#include "figure/formation.h"
#include "figure/formation_legion.h"
#include "widget/city/building_ghost.h"
#include "widget/city/ornaments.h"
#include "window/building/common.h"
#include "city/city.h"
#include "city/warnings.h"
#include "graphics/view/view.h"
#include "graphics/view/lookup.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/building_tiles.h"
#include "grid/building.h"

#include "graphics/animation.h"
#include "js/js_game.h"
#include "city/labor.h"
#include "game/undo.h"

struct fort_ghost {
    std::vector<vec2i> main_view_offset;
    std::vector<vec2i> ground_view_offset;
    std::vector<vec2i> ground_check_offset;
} fort_ghost_m;

buildings::model_t<building_fort_charioteers> fort_charioteers_m;
buildings::model_t<building_fort_archers> fort_archers_m;
buildings::model_t<building_fort_infantry> fort_infantry_m;
buildings::model_t<building_fort_ground> fort_ground_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_fort);
void config_load_building_fort() {
    fort_charioteers_m.load();
    fort_archers_m.load();
    fort_infantry_m.load();
    fort_ground_m.load();

    g_config_arch.r_section("building_fort", [] (archive arch) {
        arch.r_section("ghost", [] (archive ghost_arch) {
            fort_ghost_m.main_view_offset = ghost_arch.r_array_vec2i("main");
            fort_ghost_m.ground_view_offset = ghost_arch.r_array_vec2i("ground");
            fort_ghost_m.ground_check_offset = ghost_arch.r_array_vec2i("ground_check");
        });
    });
}

void draw_partially_blocked(painter &ctx, int fully_blocked, const std::vector<blocked_tile> &blocked_tiles) {
    for (auto &tile: blocked_tiles) {
        vec2i pixel = tile_to_pixel(tile.tile);
        draw_flat_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
    }
}

void building_fort::window_info_background(object_info &c) {
    c.help_id = 87;
    window_building_play_sound(&c, "Wavs/fort.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(89, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    int text_id = formation_get(c.formation_id)->cursed_by_mars ? 1 : 2;
    window_building_draw_description_at(c, 16 * c.bgsize.y - 158, 89, text_id);
}

void building_fort::on_place_update_tiles(int orientation, int variant) {
    base.prev_part_building_id = 0;
    int image_id = params().anim["base"].first_img();
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);

    if (type() == BUILDING_FORT_CHARIOTEERS) {
        base.subtype.fort_figure_type = FIGURE_FCHARIOTEER;
    } else if (type() == BUILDING_FORT_ARCHERS) {
        base.subtype.fort_figure_type = FIGURE_ARCHER;
    } else if (type() == BUILDING_FORT_INFANTRY) {
        base.subtype.fort_figure_type = FIGURE_INFANTRY;
    }

    // create parade ground
    const int offsets_x[] = {3, -1, -4, 0};
    const int offsets_y[] = {-1, -4, 0, 3};
    int global_rotation = building_rotation_global_rotation();
    building* ground = building_create(BUILDING_FORT_GROUND, tile().shifted(offsets_x[global_rotation], offsets_y[global_rotation]), 0);
    game_undo_add_building(ground);
    ground->prev_part_building_id = id();
    base.next_part_building_id = ground->id;
    ground->next_part_building_id = 0;
    tile2i fort_tile_add = tile().shifted(offsets_x[global_rotation], offsets_y[global_rotation]);

    int ground_id = params().anim["ground"].first_img();
    map_building_tiles_add(ground->id, fort_tile_add, 4, ground_id, TERRAIN_BUILDING);

    base.formation_id = formation_legion_create_for_fort(&base);
    ground->formation_id = base.formation_id;
}

void building_fort::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }
    
    if (building_count_active(BUILDING_RECRUITER) <= 0) {
        building_construction_warning_show(WARNING_BUILD_BARRACKS);
    }
}

bool building_fort::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (map_property_is_draw_tile(tile.grid_offset())) {
        int mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;
        const auto &anim = params().anim["picture"];
        ImageDraw::img_generic(ctx, anim.first_img(), point + anim.pos, mask);
    }

    return true;
}

void building_fort::highlight_waypoints() {
    map_clear_highlights();
}

void building_fort::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    bool fully_blocked = false;
    bool blocked = false;
    if (formation_get_num_forts_cached() >= formation_get_max_forts() || city_finance_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    int fort_size = building_impl::params(BUILDING_FORT_ARCHERS).building_size;
    int ground_size = building_impl::params(BUILDING_FORT_GROUND).building_size;
    int global_rotation = building_rotation_global_rotation();

    vec2i tile_ground_offset = fort_ghost_m.ground_check_offset[global_rotation * 4 + (city_view_orientation() / 2)];
    tile2i tile_ground = tile.shifted(tile_ground_offset.x, tile_ground_offset.y);

    std::vector<blocked_tile> blocked_tiles_fort;
    std::vector<blocked_tile> blocked_tiles_ground;

    blocked += is_blocked_for_building(tile, fort_size, blocked_tiles_fort);
    blocked += is_blocked_for_building(tile_ground, ground_size, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i main_pixel = pixel + fort_ghost_m.main_view_offset[orientation_index];
    vec2i ground_pixel = pixel + fort_ghost_m.ground_view_offset[orientation_index];

    if (blocked) {
        draw_partially_blocked(ctx, fully_blocked, blocked_tiles_fort);
        draw_partially_blocked(ctx, fully_blocked, blocked_tiles_ground);
    } else {
        int image_id = fort_infantry_m.anim["base"].first_img();
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            draw_building_ghost(ctx, image_id, main_pixel);
            draw_building_ghost(ctx, image_id + 1, ground_pixel);
        } else {
            // draw ground first, then fort
            draw_building_ghost(ctx, image_id + 1, ground_pixel);
            draw_building_ghost(ctx, image_id, main_pixel);
        }
    }
}

void building_fort::spawn_figure() {
    formation_legion_update_recruit_status(&base);
}
