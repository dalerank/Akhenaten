#include "city_overlay.h"

#include "game/state.h"
#include "grid/building.h"

#include "overlays/city_overlay_education.h"
#include "overlays/city_overlay_entertainment.h"
#include "overlays/city_overlay_health.h"
#include "overlays/city_overlay_other.h"
#include "overlays/city_overlay_religion.h"
#include "overlays/city_overlay_risks.h"
#include "overlays/city_overlay_criminal.h"
#include "overlays/city_overlay_fertility.h"
#include "overlays/city_overlay_desirability.h"
#include "overlays/city_overlay_bazaar_access.h"
#include "overlays/city_overlay_fire.h"
#include "overlays/city_overlay_routing.h"
#include "overlays/city_overlay_physician.h"
#include "overlays/city_overlay_apothecary.h"
#include "overlays/city_overlay_dentist.h"

const city_overlay* g_city_overlay = 0;

static const city_overlay* set_city_overlay(void) {
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
    case OVERLAY_APOTHECARY:
        return city_overlay_for_apothecary();
    case OVERLAY_DENTIST:
        return city_overlay_for_dentist();
    case OVERLAY_PHYSICIAN:
        return city_overlay_for_physician();
    case OVERLAY_MORTUARY:
        return city_overlay_for_mortuary();
    case OVERLAY_RELIGION:
        return city_overlay_for_religion();
    case OVERLAY_RELIGION_OSIRIS:
        return city_overlay_for_religion_osiris();
    case OVERLAY_RELIGION_RA:
        return city_overlay_for_religion_ra();
    case OVERLAY_RELIGION_PTAH:
        return city_overlay_for_religion_ptah();
    case OVERLAY_RELIGION_SETH:
        return city_overlay_for_religion_seth();
    case OVERLAY_RELIGION_BAST:
        return city_overlay_for_religion_bast();
    case OVERLAY_TAX_INCOME:
        return city_overlay_for_tax_income();
    case OVERLAY_FOOD_STOCKS:
        return city_overlay_for_food_stocks();
    case OVERLAY_WATER:
        return city_overlay_for_water();
    case OVERLAY_DESIRABILITY:
        return city_overlay_for_desirability();
    case OVERLAY_FERTILITY:
        return city_overlay_for_fertility();
    case OVERLAY_BAZAAR_ACCESS:
        return city_overlay_for_bazaar_access();
    case OVERLAY_ROUTING:
        return city_overlay_for_routing();
    default:
        return 0;
    }
}

const city_overlay* get_city_overlay(void) {
    return g_city_overlay;
}

bool select_city_overlay() {
    if (!g_city_overlay || g_city_overlay->type != game_state_overlay())
        g_city_overlay = set_city_overlay();

    return g_city_overlay != 0;
}

int widget_city_overlay_get_tooltip_text(tooltip_context* c, int grid_offset) {
    int overlay_type = g_city_overlay->type;
    int building_id = map_building_at(grid_offset);
    if (g_city_overlay->get_tooltip_for_building && !building_id) {
        return 0;
    }

    int overlay_requires_house = (overlay_type != OVERLAY_WATER) && (overlay_type != OVERLAY_FIRE)
                                 && (overlay_type != OVERLAY_DAMAGE) && (overlay_type != OVERLAY_NATIVE)
                                 && (overlay_type != OVERLAY_DESIRABILITY);
    building* b = building_get(building_id);
    if (overlay_requires_house && !b->house_size) {
        return 0;
    }

    if (g_city_overlay->get_tooltip_for_building) {
        return g_city_overlay->get_tooltip_for_building(c, b);
    } else if (g_city_overlay->get_tooltip_for_grid_offset) {
        return g_city_overlay->get_tooltip_for_grid_offset(c, grid_offset);
    }

    return 0;
}