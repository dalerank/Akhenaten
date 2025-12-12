#include "imagepak_holder.h"

#include "js/js_game.h"

imagepak_holder_t *g_image_data = nullptr;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_imagepaks_config) {
    if (g_image_data->common_inited) {
        return;
    }

    g_config_arch.r("imagepaks", g_image_data->pak_list);

    for (auto &pak : g_image_data->pak_list) {
        bstring256 pak_name = pak.name.c_str();
        pak.name = pak_name.tolower();
    }

    g_image_data->image_cache.resize(65 * 1024, nullptr);
    g_image_data->common_inited = true;
}

void image_data_init() {
    g_image_data = new imagepak_holder_t;
}
