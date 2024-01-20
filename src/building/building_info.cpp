#include "building.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<std::string, building::metainfo> g_building_metainfo;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_info);
void config_load_building_info() {
    g_config_arch.r_array("building_info", [] (archive arch) {
        const char *type = arch.r_string("type");
        auto &meta = g_building_metainfo[type];
        meta.help_id = arch.r_int("help_id");
        meta.text_id = arch.r_int("text_id");
    });
}

building::metainfo &building::get_info(pcstr type) {
    return g_building_metainfo[type];
}
