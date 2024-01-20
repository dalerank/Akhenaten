#include "graphics/image_desc.h"

#include <array>

#include "js/js_game.h"

std::array<image_desc, IMG_SIZE> g_image_desc;

ANK_REGISTER_CONFIG_ITERATOR(config_load_images_info);
void config_load_images_info() {
    g_config_arch.r_array("images", [] (archive arch) {
        int type = arch.r_int("img");
        int pack = arch.r_int("pack");
        int id = arch.r_int("id");
        int offset = arch.r_int("offset");

        if (type >= IMG_SIZE) {
            return;
        }

        g_image_desc[type] = {pack, id, offset};
    });
}

void set_image_desc(int type, int pack, int id, int offset) {
    g_image_desc[type] = {pack, id, offset};
}

image_desc get_image_desc(e_image_id t) {
    if (t >= IMG_SIZE) {
        return {0, 0, 0};
    }

    return g_image_desc[t];
}
