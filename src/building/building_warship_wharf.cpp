#include "building_warship_wharf.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/water.h"

buildings::model_t<building_warship_wharf> warship_wharf_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_warship_wharf);
void config_load_building_warship_wharf() {
    warship_wharf_m.load();
}