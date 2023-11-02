#include "graphics/image_desc.h"

#include <array>

std::array<image_desc, IMG_SIZE> g_image_desc;
 
void set_image_desc(e_image_id t, int pack, int id, int offset) {
    if (t >= IMG_SIZE) {
        return;
    }

    g_image_desc[t] = {pack, id, offset};
}

image_desc get_image_desc(e_image_id t) {
    if (t >= IMG_SIZE) {
        return {0, 0, 0};
    }

    return g_image_desc[t];
}
