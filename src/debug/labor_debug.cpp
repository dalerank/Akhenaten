#include "core/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/building_entertainment.h"
#include "building/building_farm.h"
#include "city/city_labor.h"
#include "grid/building.h"
#include "grid/floodplain.h"
#include "grid/property.h"

static void draw_labor_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);
    if (!b_id || !b || !map_property_is_draw_tile(grid_offset))
        return;
    if (b->labor_category == LABOR_CATEGORY_NONE && !b->is_floodplain_farm())
        return;

    char str[64];
    const int y = pixel.y;
    const int x0 = pixel.x + 8;
    const int x1 = x0 + 30;

    if (b->labor_category != category_for_building(b))
        debug_text(ctx, str, x0, y + 10, 10, "!!", b->labor_category, COLOR_RED);
    else
        debug_text(ctx, str, x0, y + 10, 0, "", b->labor_category, COLOR_WHITE);

    debug_text(ctx, str, x1, y + 10, 0, "", b->houses_covered, COLOR_LIGHT_RED);
    debug_text(ctx, str, x0, y + 20, 0, "", b->num_workers, COLOR_LIGHT_BLUE);
    debug_text(ctx, str, x1 - 10, y + 20, 4, ":", b->worker_percentage(), COLOR_LIGHT_BLUE);

    if (b->is_farm()) {
        const auto farm = b->dcast_farm();
        debug_text(ctx, str, x1 + 40, y + 20, 40, "fert.", map_get_fertility_for_farm(b->tile.grid_offset()), COLOR_FONT_ORANGE_LIGHT);
        debug_text(ctx, str, x0, y + 30, 0, "", b->progress, COLOR_GREEN);
        debug_text(ctx, str, x1 + 10, y + 30, 4, ":", b->progress / 20, COLOR_GREEN);
        debug_text(ctx, str, x1 + 40, y + 30, 40, "exp.", farm->expected_produce(), COLOR_GREEN);
        if (b->is_floodplain_farm()) {
            auto &d = b->dcast_farm()->runtime_data();
            debug_text(ctx, str, x0, y + 40, 0, "", d.labor_state, COLOR_WHITE);
            debug_text(ctx, str, x1, y + 40, 0, "", d.labor_days_left, COLOR_WHITE);
        }
    }

    auto ent = b->dcast_entertainment();
    if (ent) {
        auto &d = ent->runtime_data();
        debug_text(ctx, str, x0, y + 30, 0, "", d.juggler_visited, COLOR_GREEN);
        debug_text(ctx, str, x1, y + 30, 0, "", d.musician_visited, COLOR_GREEN);
        debug_text(ctx, str, x0, y + 40, 0, "", d.dancer_visited, COLOR_GREEN);
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_labor_debug) {
    g_debug.add_tile_render_handler("labor", draw_labor_tile);
}
