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

city_overlay_damage::city_overlay_damage() {
    type = OVERLAY_DAMAGE;
    column_type = COLUMN_TYPE_RISK;
}

int city_overlay_damage::get_column_height(const building *b) const {
    auto model = model_get_building(b->type);
    if (b->prev_part_building_id || !model->damage_risk)
        return NO_COLUMN;
    return b->damage_risk / 100;
}

int city_overlay_damage::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->damage_risk <= 0)
        return 52;
    else if (b->damage_risk <= 40)
        return 53;
    else if (b->damage_risk <= 80)
        return 54;
    else if (b->damage_risk <= 120)
        return 55;
    else if (b->damage_risk <= 160)
        return 56;
    else {
        return 57;
    }
}
