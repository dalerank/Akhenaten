#include "city_overlay_damage.h"

#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"


city_overlay_damage g_city_overlay_damage;

city_overlay* city_overlay_for_damage() {
    return &g_city_overlay_damage;
}

int city_overlay_damage::get_column_height(const building *b) const {
    auto model = model_get_building(b->type);
    if (b->prev_part_building_id || !model->damage_risk)
        return COLUMN_TYPE_NONE;
    return b->damage_risk / 100;
}

xstring city_overlay_damage::get_tooltip_for_building(tooltip_context *c, const building *b) const {
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
