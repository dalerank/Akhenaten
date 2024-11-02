#include "building_workshop.h"

#include "building/count.h"
#include "js/js_game.h"
#include "city/labor.h"

buildings::model_t<building_lamp_workshop> lamp_workshop_m;
buildings::model_t<building_paint_workshop> paint_workshop_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_lamp_workshop);
void config_load_building_lamp_workshop() {
    lamp_workshop_m.load();
    paint_workshop_m.load();
}

void building_lamp_workshop::on_create(int orientation) {
    base.first_material_id = RESOURCE_OIL;
    base.second_material_id = RESOURCE_TIMBER;
}

void building_lamp_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_LAMPS, num_workers() > 0);
}

void building_paint_workshop::on_create(int orientation) {
    base.first_material_id = RESOURCE_OIL;
}

void building_paint_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_PAINT, num_workers() > 0);
}
