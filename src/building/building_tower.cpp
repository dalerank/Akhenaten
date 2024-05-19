#include "building_tower.h"

#include "js/js_game.h"
#include "city/labor.h"

buildings::model_t<building_brick_tower> brick_tower_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_tower);
void config_load_building_tower() {
    brick_tower_m.load();
}
