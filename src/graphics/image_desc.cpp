#include "graphics/image_desc.h"

#include <array>

#include "js/js_game.h"

std::array<image_desc, IMG_SIZE> g_image_desc;

ANK_REGISTER_CONFIG_ITERATOR(config_load_images_info);
void config_load_images_info(archive arch) {
    arch.load_global_array("images", [] (archive arch) {
        int type = arch.read_integer("img");
        int pack = arch.read_integer("pack");
        int id = arch.read_integer("id");
        int offset = arch.read_integer("offset");

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
