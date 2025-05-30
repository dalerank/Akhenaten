#include "building.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<xstring, metainfo> g_building_metainfo;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_building_info) {
    g_config_arch.r_array("building_info", [] (archive arch) {
        const char *type = arch.r_string("type");
        auto &meta = g_building_metainfo[type];
        meta.help_id = arch.r_int("help_id");
        meta.text_id = arch.r_int("text_id");
    });
}

const metainfo &building::get_info(const xstring type) {
    return g_building_metainfo[type];
}
