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
}

int city_overlay_bazaar_access::get_column_height(const building *b) const {
    if (b->house_population <= 0) {
        return NO_COLUMN;
    }

    return std::clamp<int>(b->data.house.bazaar_access / 10, 0, 8);
}

xstring city_overlay_bazaar_access::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (building_is_farm(b->type)) {
        map_point tile = b->tile;
        int fertility = map_get_fertility_for_farm(tile.grid_offset());
        if (fertility > 80)
            return ui::str(66, 63);
        else if (fertility > 60)
            return ui::str(66, 62);
        else if (fertility > 40)
            return ui::str(66, 61);
        else if (fertility > 20)
            return ui::str(66, 60);
        else if (fertility > 10)
            return ui::str(66, 59);
        else {
            return ui::str(66, 58);
        }
    }
    return ui::str(66, 58);
}
