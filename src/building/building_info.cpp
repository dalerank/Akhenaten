#include "building.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<std::string, building::metainfo> g_building_metainfo;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_info);
void config_load_building_info(archive arch) {
    arch.load_global_array("building_info", [] (archive arch) {
        const char *type = arch.read_string("type");
        auto &meta = g_building_metainfo[type];
        meta.help_id = arch.read_integer("help_id");
        meta.text_id = arch.read_integer("text_id");
    });
}

building::metainfo &building::get_info(pcstr type) {
    return g_building_metainfo[type];
}
