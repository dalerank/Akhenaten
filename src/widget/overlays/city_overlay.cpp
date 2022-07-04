#include <game/state.h>
#include <grid/building.h>
#include "city_overlay.h"

#include "widget/overlays/city_overlay_risks.h"
#include "widget/overlays/city_overlay_health.h"
#include "widget/overlays/city_overlay_education.h"
#include "widget/overlays/city_overlay_entertainment.h"
#include "widget/overlays/city_overlay_other.h"

static const city_overlay *overlay = 0;

static const city_overlay *set_city_overlay(void) {
    switch (game_state_overlay()) {
        case OVERLAY_FIRE:
            return city_overlay_for_fire();
        case OVERLAY_CRIME:
            return city_overlay_for_crime();
        case OVERLAY_DAMAGE:
            return city_overlay_for_damage();
        case OVERLAY_PROBLEMS:
            return city_overlay_for_problems();
        case OVERLAY_NATIVE:
            return city_overlay_for_native();
        case OVERLAY_ENTERTAINMENT:
            return city_overlay_for_entertainment();
        case OVERLAY_THEATER:
            return city_overlay_for_theater();
        case OVERLAY_AMPHITHEATER:
            return city_overlay_for_amphitheater();
        case OVERLAY_COLOSSEUM:
            return city_overlay_for_colosseum();
        case OVERLAY_HIPPODROME:
            return city_overlay_for_hippodrome();
        case OVERLAY_EDUCATION:
            return city_overlay_for_education();
        case OVERLAY_SCHOOL:
            return city_overlay_for_school();
        case OVERLAY_LIBRARY:
            return city_overlay_for_library();
        case OVERLAY_ACADEMY:
            return city_overlay_for_academy();
        case OVERLAY_BARBER:
            return city_overlay_for_barber();
        case OVERLAY_BATHHOUSE:
            return city_overlay_for_bathhouse();
        case OVERLAY_CLINIC:
            return city_overlay_for_clinic();
        case OVERLAY_HOSPITAL:
            return city_overlay_for_hospital();
        case OVERLAY_RELIGION:
            return city_overlay_for_religion();
        case OVERLAY_TAX_INCOME:
            return city_overlay_for_tax_income();
        case OVERLAY_FOOD_STOCKS:
            return city_overlay_for_food_stocks();
        case OVERLAY_WATER:
            return city_overlay_for_water();
        case OVERLAY_DESIRABILITY:
            return city_overlay_for_desirability();
        default:
            return 0;
    }
}
const city_overlay *get_city_overlay(void) {
    return overlay;
}
bool select_city_overlay(void) {
    if (!overlay || overlay->type != game_state_overlay())
        overlay = set_city_overlay();
    return overlay != 0;
}

int widget_city_overlay_get_tooltip_text(tooltip_context *c, int grid_offset) {
    int overlay_type = overlay->type;
    int building_id = map_building_at(grid_offset);
    if (overlay->get_tooltip_for_building && !building_id)
        return 0;

    int overlay_requires_house =
            overlay_type != OVERLAY_WATER && overlay_type != OVERLAY_FIRE &&
            overlay_type != OVERLAY_DAMAGE && overlay_type != OVERLAY_NATIVE && overlay_type != OVERLAY_DESIRABILITY;
    building *b = building_get(building_id);
    if (overlay_requires_house && !b->house_size)
        return 0;

    if (overlay->get_tooltip_for_building)
        return overlay->get_tooltip_for_building(c, b);
    else if (overlay->get_tooltip_for_grid_offset)
        return overlay->get_tooltip_for_grid_offset(c, grid_offset);

    return 0;
}