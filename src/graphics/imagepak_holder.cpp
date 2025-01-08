#include "imagepak_holder.h"

#include "js/js_game.h"

imagepak_holder_t *g_image_data = nullptr;

ANK_REGISTER_CONFIG_ITERATOR(config_load_imagepaks_config);
void config_load_imagepaks_config() {
    if (g_image_data->common_inited) {
        return;
    }
    g_config_arch.r_array("imagepaks", [] (archive arch) {
        imagepak_handle config;
        config.id = arch.r_int("id");
        config.name = arch.r_string("name");
        config.index = arch.r_int("index");
        config.system = arch.r_bool("system");
        config.custom = arch.r_bool("custom");
        g_image_data->common[config.id] = config;
    });
    g_image_data->common_inited = true;
}

void image_data_init() {
    g_image_data = new imagepak_holder_t;
}