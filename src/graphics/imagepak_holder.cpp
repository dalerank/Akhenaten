#include "imagepak_holder.h"

#include "js/js_game.h"

imagepak_holder_t *g_image_data = nullptr;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_imagepaks_config) {
    if (g_image_data->common_inited) {
        return;
    }

    g_config_arch.r_array("imagepaks", [] (archive arch) {
        int id = arch.r_int("id");
        imagepak_handle &config = g_image_data->pak_list[id];
        config.id = id;
        config.name = arch.r_string("name");
        config.index = arch.r_int("index");
        config.system = arch.r_bool("system");
        config.custom = arch.r_bool("custom");
        config.delayed = arch.r_bool("delayed", false);
    });

    g_image_data->image_cache.resize(65 * 1024, nullptr);
    g_image_data->common_inited = true;
}

void image_data_init() {
    g_image_data = new imagepak_holder_t;
}
