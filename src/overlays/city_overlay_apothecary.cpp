#include "city_overlay.h"

#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "building/building_house.h"
#include "figure/figure.h"

struct city_overlay_apothecary : public city_overlay_t<OVERLAY_APOTHECARY> {
    virtual int get_column_height(const building *b) const override;
    virtual void get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip) override;
};

city_overlay_apothecary g_city_overlay_apothecary;

void city_overlay_apothecary::get_tooltip_for_building(tooltip_context* c, const building* b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 34);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.apothecary <= 0) {
        tooltip = ui::str(66, 31);
        return;
        }
    else if (housed.apothecary >= 80) {
        tooltip = ui::str(66, 32);
        return;
        }
    else if (housed.apothecary < 20) {
        tooltip = ui::str(66, 33);
        return;
        }
    else {
        tooltip = ui::str(66, 34);
        return;
    }
}

int city_overlay_apothecary::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return house->house_population() > 0
                ? housed.apothecary / 10 
                : COLUMN_TYPE_NONE;
}
