#include "building/building_fort.h"

#include "building/rotation.h"
#include "figure/formation.h"
#include "widget/city/building_ghost.h"
#include "city/finance.h"
#include "building/properties.h"
#include "graphics/view/view.h"
#include "grid/grid.h"

#include "graphics/animation.h"
#include "js/js_game.h"
#include "city/labor.h"

constexpr int MAX_TILES = 25;

namespace model {

struct fort_t {
    static constexpr e_building_type type = BUILDING_COURTHOUSE;
    e_labor_category labor_category;
    animations_t anim;
    struct {
        vec2i main_view_offset[4];
        vec2i ground_view_offset[4];
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
            model::fort.ghost.main_view_offset[0] = ghost_arch.r_vec2i("main_N");
            model::fort.ghost.main_view_offset[1] = ghost_arch.r_vec2i("main_W");
            model::fort.ghost.main_view_offset[2] = ghost_arch.r_vec2i("main_S");
            model::fort.ghost.main_view_offset[3] = ghost_arch.r_vec2i("main_E");
            model::fort.ghost.ground_view_offset[0] = ghost_arch.r_vec2i("ground_N");
            model::fort.ghost.ground_view_offset[1] = ghost_arch.r_vec2i("ground_W");
            model::fort.ghost.ground_view_offset[2] = ghost_arch.r_vec2i("ground_S");
            model::fort.ghost.ground_view_offset[3] = ghost_arch.r_vec2i("ground_E");
        });
    });

    city_labor_set_category(model::fort);
}

static const int FORT_GROUND_GRID_OFFSETS_PH[4][4] = {
    {GRID_OFFSET(3, -1), GRID_OFFSET(4, -1), GRID_OFFSET(4, 0), GRID_OFFSET(3, 0)},
    {GRID_OFFSET(-1, -4), GRID_OFFSET(0, -4), GRID_OFFSET(0, -3), GRID_OFFSET(-1, -3)},
    {GRID_OFFSET(-4, 0), GRID_OFFSET(-3, 0), GRID_OFFSET(-3, 1), GRID_OFFSET(-4, 1)},
    {GRID_OFFSET(0, 3), GRID_OFFSET(1, 3), GRID_OFFSET(1, 4), GRID_OFFSET(0, 4)}
};

void draw_fort_ghost(painter &ctx, e_building_type build_type, tile2i &tile, vec2i pixel) {
    bool fully_blocked = false;
    bool blocked = false;
    if (formation_get_num_forts_cached() >= formation_get_max_forts() || city_finance_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    int num_tiles_fort = building_properties_for_type(BUILDING_FORT_ARCHERS)->size;
    num_tiles_fort *= num_tiles_fort;
    int num_tiles_ground = building_properties_for_type(BUILDING_FORT_GROUND)->size;
    num_tiles_ground *= num_tiles_ground;

    //    int grid_offset_fort = tile->grid_offset;
    int global_rotation = building_rotation_global_rotation();
    int grid_offset_ground = tile.grid_offset() + FORT_GROUND_GRID_OFFSETS_PH[global_rotation][city_view_orientation() / 2];

    int blocked_tiles_fort[MAX_TILES];
    int blocked_tiles_ground[MAX_TILES];

    blocked += is_blocked_for_building(tile.grid_offset(), num_tiles_fort, blocked_tiles_fort);
    blocked += is_blocked_for_building(grid_offset_ground, num_tiles_ground, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i main = pixel + model::fort.ghost.main_view_offset[orientation_index];
    vec2i ground = pixel + model::fort.ghost.ground_view_offset[orientation_index];

    if (blocked) {
        draw_partially_blocked(ctx, pixel, fully_blocked, num_tiles_fort, blocked_tiles_fort);
        draw_partially_blocked(ctx, ground, fully_blocked, num_tiles_ground, blocked_tiles_ground);
    } else {
        int image_id = image_id_from_group(GROUP_BUILDING_FORT);
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            draw_building_ghost(ctx, image_id, main);
            draw_building_ghost(ctx, image_id + 1, ground);
        } else {
            // draw ground first, then fort
            draw_building_ghost(ctx, image_id + 1, ground);
            draw_building_ghost(ctx, image_id, main);
        }
    }
}