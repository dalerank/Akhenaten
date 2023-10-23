#include "graphics/image_desc.h"

#include <array>

std::array<image_desc_t, IMAGE_SIZE> g_image_desc;
 
void set_image_desc(e_image_type t, int collection, int id) {
    if (t >= IMAGE_SIZE) {
        return;
    }

    g_image_desc[t] = {collection, id};
}

image_desc_t image_desc(e_image_type t) {
    if (t >= IMAGE_SIZE) {
        return {0, 0};
    }

    return g_image_desc[t];
}
