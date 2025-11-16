#include "city_overlay_damage.h"

#include "game/state.h"
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

    if (!b->damage_risk && b->damage_risk <= 0) {
        return COLUMN_TYPE_NONE;
    }

    return b->damage_risk / 100;
}

void city_overlay_damage::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    city_overlay::draw_custom_top(pixel, tile, ctx);

    if (debug_render_mode() == e_debug_render_overlay_add) {
        building *b = building_at(tile);
        if (b->id) {
            auto house = b->dcast_house();
            bstring32 text;
            text.printf("%d", b->damage_risk);
            debug_text_a(ctx, text, pixel.x + 15, pixel.y + 15, 0, text, COLOR_LIGHT_BLUE);
        }
    }
}

xstring city_overlay_damage::get_tooltip_for_building(tooltip_context *c, const building *b) {
    if (b->damage_risk <= 0)
        return ui::str(66, 52);
    else if (b->damage_risk <= 40)
        return ui::str(66, 53);
    else if (b->damage_risk <= 80)
        return ui::str(66, 54);
    else if (b->damage_risk <= 120)
        return ui::str(66, 55);
    else if (b->damage_risk <= 160)
        return ui::str(66, 56);
    else {
        return ui::str(66, 57);
    }
}
