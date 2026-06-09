#include "city_overlay_damage.h"

#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

#include "dev/debug.h"
#include "city/city_buildings.h"

city_overlay_damage g_city_overlay_damage;

int city_overlay_damage::get_column_height(const building *b) const {
    if (b->prev_part_building_id) {
        return COLUMN_TYPE_NONE;
    }

    if (!b->collapse_risk && b->collapse_risk <= 0) {
        return COLUMN_TYPE_NONE;
    }

    return b->collapse_risk / 100;
}

void city_overlay_damage::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    city_overlay::draw_custom_top(pixel, tile, ctx);

    if (debug_render_mode() == e_debug_render_overlay_add) {
        building *b = building_at(tile);
        if (b->id) {
            auto house = b->dcast_house();
            bstring32 text;
            text.printf("%d", b->collapse_risk);
            debug_text_a(ctx, text, pixel.x + 15, pixel.y + 15, 0, text, COLOR_LIGHT_BLUE);
        }
    }
}

void city_overlay_damage::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    if (b->collapse_risk <= 0) {
        tooltip = ui::str(66, 52);
        return;
        }
    else if (b->collapse_risk <= 40) {
        tooltip = ui::str(66, 53);
        return;
        }
    else if (b->collapse_risk <= 80) {
        tooltip = ui::str(66, 54);
        return;
        }
    else if (b->collapse_risk <= 120) {
        tooltip = ui::str(66, 55);
        return;
        }
    else if (b->collapse_risk <= 160) {
        tooltip = ui::str(66, 56);
        return;
        }
    else {
        tooltip = ui::str(66, 57);
        return;
    }
}
