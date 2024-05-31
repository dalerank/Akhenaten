#include "city_overlay_bazaar_access.h"

#include "grid/floodplain.h"
#include "building/model.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "grid/point.h"
#include "game/state.h"

city_overlay_bazaar_access g_city_overlay_bazaar_access;

city_overlay* city_overlay_for_bazaar_access() {
    return &g_city_overlay_bazaar_access;
}

city_overlay_bazaar_access::city_overlay_bazaar_access() {
    type = OVERLAY_BAZAAR_ACCESS;
    column_type = COLUMN_TYPE_POSITIVE;
}

bool city_overlay_bazaar_access::show_figure(const figure *f) const {
    return f->type == FIGURE_MARKET_BUYER || f->type == FIGURE_MARKET_TRADER;
}

inline void city_overlay_bazaar_access::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    if (map_building_at(grid_offset)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

int city_overlay_bazaar_access::get_column_height(const building *b) const {
    if (b->house_population <= 0) {
        return NO_COLUMN;
    }

    return std::clamp<int>(b->data.house.bazaar_access / 10, 0, 8);
}

int city_overlay_bazaar_access::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (building_is_farm(b->type)) {
        map_point tile = b->tile;
        int fertility = map_get_fertility_for_farm(tile.grid_offset());
        if (fertility > 80)
            return 63;
        else if (fertility > 60)
            return 62;
        else if (fertility > 40)
            return 61;
        else if (fertility > 20)
            return 60;
        else if (fertility > 10)
            return 59;
        else {
            return 58;
        }
    }
    return 58;
}

bool city_overlay_bazaar_access::show_building(const building *b) const {
    return b->type == BUILDING_BAZAAR;
}
