#include "city_overlay_religion.h"

#include "city/constants.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"
#include "building/building_house.h"

#include <algorithm>
#include <array>

static void add_god(tooltip_context* c, int god_id) {
    int index = c->num_extra_values;
    c->extra_value_text_groups[index] = 59;
    c->extra_value_text_ids[index] = 11 + god_id;
    c->num_extra_values++;
}

city_overlay_religion g_city_overlay_religion;

city_overlay_religion_osiris g_city_overlay_religion_osiris;
city_overlay_religion_ra g_city_overlay_religion_ra;
city_overlay_religion_ptah g_city_overlay_religion_ptah;
city_overlay_religion_seth g_city_overlay_religion_seth;
city_overlay_religion_bast g_city_overlay_religion_bast;

int city_overlay_religion::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (house->house_population() > 0 && housed.num_gods)
                ? housed.num_gods * 17 / 10
                : COLUMN_TYPE_NONE;
}

xstring city_overlay_religion::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 18);
    }

    auto &housed = house->runtime_data();
    if (housed.num_gods < 5) {
        if (housed.temple_osiris)
            add_god(c, GOD_OSIRIS);

        if (housed.temple_ra)
            add_god(c, GOD_RA);

        if (housed.temple_ptah)
            add_god(c, GOD_PTAH);

        if (housed.temple_seth)
            add_god(c, GOD_SETH);

        if (housed.temple_bast)
            add_god(c, GOD_BAST);
    }

    if (housed.num_gods <= 0) {
        return ui::str(66, 12);
    } else if (housed.num_gods == 1) {
        return ui::str(66, 13);
    } else if (housed.num_gods == 2) {
        return ui::str(66, 14);
    } else if (housed.num_gods == 3) {
        return ui::str(66, 15);
    } else if (housed.num_gods == 4) {
        return ui::str(66, 16);
    } else if (housed.num_gods == 5) {
        return ui::str(66, 17);
    } else {
        return ui::str(66, 18); // >5 gods, shouldn't happen...
    }
}
