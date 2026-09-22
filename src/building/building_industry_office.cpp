#include "building_industry_office.h"

#include "building/construction/build_planner.h"
#include "game/game_config.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_industry_office);

namespace {
constexpr int k_size = 2;

int placeholder_tile_image() {
    return image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED);
}
} // namespace

bool building_industry_office::is_management_active() const {
    if (!game_features::gameplay_enhanced_industry_office.to_bool()) {
        return false;
    }
    if (base.state != BUILDING_STATE_VALID) {
        return false;
    }
    if (base.num_workers <= 0) {
        return false;
    }
    return stored_amount(RESOURCE_PAPYRUS) > 0;
}

int building_industry_office::management_radius() const {
    const int r = current_params().management_radius;
    return r > 0 ? r : 7;
}

bool building_industry_office::add_resource(e_resource resource, int amount, figure_id fid) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_PAPYRUS, amount);
    return true;
}

void building_industry_office::on_place_update_tiles(int orientation, int variant) {
    map_building_tiles_add(id(), tile(), k_size, placeholder_tile_image(), TERRAIN_BUILDING);
}

void building_industry_office::update_graphic() {
    map_building_tiles_add(id(), tile(), k_size, placeholder_tile_image(), TERRAIN_BUILDING);
    building_impl::update_graphic();
}

void building_industry_office::draw_placeholder(painter &ctx, color color_mask) const {
    const color mask = color_mask ? color_mask : COLOR_MASK_GREEN;
    for (int dy = 0; dy < k_size; dy++) {
        for (int dx = 0; dx < k_size; dx++) {
            tile2i t = tile().shifted(dx, dy);
            vec2i px = g_camera.lookup_tile_to_pixel(t);
            build_planner::draw_flat_tile(ctx, px, mask);
        }
    }

    vec2i label = g_camera.lookup_tile_to_pixel(tile());
    text_draw_centered("OFFICE", label.x - 40, label.y - 8, 80, FONT_SMALL_PLAIN, COLOR_WHITE);
}

bool building_industry_office::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    const color draw_mask = mask ? mask : COLOR_MASK_GREEN;
    build_planner::draw_flat_tile(ctx, pixel, draw_mask);
    return true;
}

bool building_industry_office::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_placeholder(ctx, color_mask);
    return true;
}
