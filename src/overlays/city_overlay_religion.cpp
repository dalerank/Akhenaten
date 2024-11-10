#include "city_overlay_religion.h"

#include "city/constants.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

#include <algorithm>
#include <array>

static void add_god(tooltip_context* c, int god_id) {
    int index = c->num_extra_values;
    c->extra_value_text_groups[index] = 59;
    c->extra_value_text_ids[index] = 11 + god_id;
    c->num_extra_values++;
}

city_overlay_religion g_city_overlay_religion;
city_overlay* city_overlay_for_religion() {
    return &g_city_overlay_religion;
}

city_overlay_religion_osiris g_city_overlay_religion_osiris;
city_overlay_religion_ra g_city_overlay_religion_ra;
city_overlay_religion_ptah g_city_overlay_religion_ptah;
city_overlay_religion_seth g_city_overlay_religion_seth;
city_overlay_religion_bast g_city_overlay_religion_bast;

city_overlay* city_overlay_for_religion_osiris() {
    return &g_city_overlay_religion_osiris;
}

city_overlay* city_overlay_for_religion_ra() {
    return &g_city_overlay_religion_ra;
}

city_overlay* city_overlay_for_religion_ptah() {
    return &g_city_overlay_religion_ptah;
}

city_overlay* city_overlay_for_religion_seth() {
    return &g_city_overlay_religion_seth;
}

city_overlay* city_overlay_for_religion_bast() {
    return &g_city_overlay_religion_bast;
}

city_overlay_religion::city_overlay_religion() {
    type = OVERLAY_RELIGION;
}

int city_overlay_religion::get_column_height(const building *b) const {
    return b->house_size && b->data.house.num_gods
                ? b->data.house.num_gods * 17 / 10
                : NO_COLUMN;
}

xstring city_overlay_religion::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.num_gods < 5) {
        if (b->data.house.temple_osiris)
            add_god(c, GOD_OSIRIS);

        if (b->data.house.temple_ra)
            add_god(c, GOD_RA);

        if (b->data.house.temple_ptah)
            add_god(c, GOD_PTAH);

        if (b->data.house.temple_seth)
            add_god(c, GOD_SETH);

        if (b->data.house.temple_bast)
            add_god(c, GOD_BAST);
    }

    if (b->data.house.num_gods <= 0) {
        return ui::str(66, 12);
    } else if (b->data.house.num_gods == 1) {
        return ui::str(66, 13);
    } else if (b->data.house.num_gods == 2) {
        return ui::str(66, 14);
    } else if (b->data.house.num_gods == 3) {
        return ui::str(66, 15);
    } else if (b->data.house.num_gods == 4) {
        return ui::str(66, 16);
    } else if (b->data.house.num_gods == 5) {
        return ui::str(66, 17);
    } else {
        return ui::str(66, 18); // >5 gods, shouldn't happen...
    }
}

int city_overlay_religion_god::get_column_height(const building *b) const {
    if (!b->house_size) {
        return NO_COLUMN;
    }

    int value = 0;
    switch (_god) {
    case GOD_OSIRIS: value = b->data.house.temple_osiris; break;
    case GOD_RA: value = b->data.house.temple_ra; break;
    case GOD_PTAH: value = b->data.house.temple_ptah; break;
    case GOD_SETH: value = b->data.house.temple_seth; break;
    case GOD_BAST: value = b->data.house.temple_bast; break;
    }

    return value / 10;
}
