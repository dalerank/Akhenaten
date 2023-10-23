#pragma once

#include <cstdint>

enum e_image_type : uint16_t {
    IMAGE_NONE = 0,
    IMAGE_IMMIGRANT = 1,

    IMAGE_SIZE
};

struct image_desc_t {
    int collection = 0;
    int id = 0;
};

void set_image_desc(e_image_type t, int collection, int id);
image_desc_t image_desc(e_image_type t);