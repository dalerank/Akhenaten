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
};

city_overlay_apothecary g_city_overlay_apothecary;

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
