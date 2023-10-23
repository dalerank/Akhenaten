#include "graphics/image_desc.h"

#include <array>

std::array<image_desc_t, IMG_SIZE> g_image_desc;
 
void set_image_desc(e_image_type t, int pack, int id) {
    if (t >= IMG_SIZE) {
        return;
    }

    g_image_desc[t] = {pack, id};
}

image_desc_t get_image_desc(e_image_type t) {
    if (t >= IMG_SIZE) {
        return {0, 0};
    }

    return g_image_desc[t];
}
