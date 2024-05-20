#include "building_guild_carpenters.h"

#include "js/js_game.h"

buildings::model_t<building_carpenters_guild> guild_carpenters_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_guild_carpenters);
void config_load_building_guild_carpenters() {
    guild_carpenters_m.load();
}