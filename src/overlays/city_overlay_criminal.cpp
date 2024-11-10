#include "city_overlay_criminal.h"

#include "building/model.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "game/state.h"


city_overlay_crime g_city_overlay_crime;

city_overlay* city_overlay_for_crime() {
    return &g_city_overlay_crime;
}

int city_overlay_crime::get_column_height(const building* b) const {
    if (b->house_size && b->house_population > 0) {
        int crime = b->house_criminal_active;
        return crime / 10;
    }
    return NO_COLUMN;
}

xstring city_overlay_crime::get_tooltip_for_building(tooltip_context* c, const building* b) const {
    if (b->house_population <= 0) {
        return ui::str(66, 63);
    }

    if (b->house_criminal_active >= 80)
        return ui::str(66, 63);
    else if (b->house_criminal_active >= 60)
        return ui::str(66, 62);
    else if (b->house_criminal_active >= 40)
        return ui::str(66, 61);
    else if (b->house_criminal_active >= 30)
        return ui::str(66, 60);
    else if (b->house_criminal_active >= 20)
        return ui::str(66, 59);
    else {
        return ui::str(66, 58);
    }
}
