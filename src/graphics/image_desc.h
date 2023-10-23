#pragma once

#include <cstdint>

enum e_image_type : uint16_t {
    IMG_NONE = 0,
    IMG_IMMIGRANT = 1,

    IMG_SIZE
};

struct image_desc_t {
    int pack = 0;
    int id = 0;
};

void set_image_desc(e_image_type t, int pack, int id);
image_desc_t get_image_desc(e_image_type t);