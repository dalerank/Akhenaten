#include "city_overlay_fire.h"

#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

city_overlay_fire g_city_overlay_fire;

city_overlay* city_overlay_for_fire() {
    return &g_city_overlay_fire;
}

city_overlay_fire::city_overlay_fire() {
    type = OVERLAY_FIRE;
    column_type = COLUMN_TYPE_RISK;
}

int city_overlay_fire::get_column_height(const building *b) const {
    auto model = model_get_building(b->type);

    if (b->prev_part_building_id || b->fire_proof)
        return NO_COLUMN;

    if (b->type == BUILDING_HOUSE_VACANT_LOT || b->type == BUILDING_GARDENS
        || b->type == BUILDING_BANDSTAND || b->type == BUILDING_BOOTH) {
        return NO_COLUMN;
    }

    return b->fire_risk / 100;
}

xstring city_overlay_fire::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    auto main = const_cast<building*>(b)->main();
    if (main->fire_risk <= 0)
        return ui::str(66, 46);
    else if (main->fire_risk <= 200)
        return ui::str(66, 47);
    else if (main->fire_risk <= 400)
        return ui::str(66, 48);
    else if (main->fire_risk <= 600)
        return ui::str(66, 49);
    else if (main->fire_risk <= 800)
        return ui::str(66, 50);
    else
        return ui::str(66, 51);
}
