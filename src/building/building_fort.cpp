#include "building/building_fort.h"

#include "building/rotation.h"
#include "figure/formation.h"
#include "widget/city/building_ghost.h"
#include "city/finance.h"
#include "building/properties.h"
#include "graphics/view/view.h"
#include "graphics/view/lookup.h"
#include "grid/grid.h"

#include "graphics/animation.h"
#include "js/js_game.h"
#include "city/labor.h"

namespace model {

struct fort_t {
    static constexpr e_building_type type = BUILDING_COURTHOUSE;
    e_labor_category labor_category;
    animations_t anim;
    struct {
        std::vector<vec2i> main_view_offset;
        std::vector<vec2i> ground_view_offset;
        std::vector<vec2i> ground_check_offset;
    } ghost;
};

fort_t fort;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_fort);
void config_load_building_fort() {
    g_config_arch.r_section("building_fort", [] (archive arch) {
        model::fort.labor_category = arch.r_type<e_labor_category>("labor_category");
        model::fort.anim.load(arch);

        arch.r_section("ghost", [] (archive ghost_arch) {
            model::fort.ghost.main_view_offset = ghost_arch.r_array_vec2i("main");
            model::fort.ghost.ground_view_offset = ghost_arch.r_array_vec2i("ground");
            model::fort.ghost.ground_check_offset = ghost_arch.r_array_vec2i("ground_check");
        });
    });

    city_labor_set_category(model::fort);
}

void draw_partially_blocked(painter &ctx, int fully_blocked, const std::vector<blocked_tile> &blocked_tiles) {
    for (auto &tile: blocked_tiles) {
        vec2i pixel = tile_to_pixel(tile.tile);
        draw_flat_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
    }
}

void draw_fort_ghost(painter &ctx, e_building_type build_type, tile2i &tile, vec2i pixel) {
    bool fully_blocked = false;
    bool blocked = false;
    if (formation_get_num_forts_cached() >= formation_get_max_forts() || city_finance_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    int fort_size = building_properties_for_type(BUILDING_FORT_ARCHERS)->size;
    int ground_size = building_properties_for_type(BUILDING_FORT_GROUND)->size;

    //    int grid_offset_fort = tile->grid_offset;
    int global_rotation = building_rotation_global_rotation();
    vec2i tile_ground_offset = model::fort.ghost.ground_check_offset[global_rotation * 4 + (city_view_orientation() / 2)];
    tile2i tile_ground = tile.shifted(tile_ground_offset.x, tile_ground_offset.y);

    std::vector<blocked_tile> blocked_tiles_fort;
    std::vector<blocked_tile> blocked_tiles_ground;

    blocked += is_blocked_for_building(tile, fort_size, blocked_tiles_fort);
    blocked += is_blocked_for_building(tile_ground, ground_size, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i main_pixel = pixel + model::fort.ghost.main_view_offset[orientation_index];
    vec2i ground_pixel = pixel + model::fort.ghost.ground_view_offset[orientation_index];

    if (blocked) {
        draw_partially_blocked(ctx, fully_blocked, blocked_tiles_fort);
        draw_partially_blocked(ctx, fully_blocked, blocked_tiles_ground);
    } else {
        int image_id = image_id_from_group(GROUP_BUILDING_FORT);
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