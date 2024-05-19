#include "building_gatehouse.h"

#include "js/js_game.h"
#include "city/labor.h"

buildings::model_t<building_brick_gatehouse> brick_gatehouse_m;
buildings::model_t<building_mud_gatehouse> mud_gatehouse_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_raw_materials);
void config_load_building_raw_materials() {
    brick_gatehouse_m.load();
    mud_gatehouse_m.load();
}

void building_gatehouse::on_create(int orientation) {
    base.subtype.orientation = orientation;
}
