#pragma once

#include <cstdint>

enum e_img : uint16_t {
    IMG_NONE = 0,
    IMG_IMMIGRANT = 1,
    IMG_IMMIGRANT_DEATH = 2,
    IMG_EMIGRANT = 3,
    IMG_EMIGRANT_DEATH = 4,
    IMG_HOMELESS = 5,
    IMG_HOMELESS_DEATH = 6,
    IMG_FISHIHG_WHARF_ANIM = 7,
    IMG_CARTPUSHER = 8,
    IMG_CARTPUSHER_DEATH = 9,
    IMG_FISHING_BOAT = 10,
    IMG_FISHING_BOAT_WORK = 11,
    IMG_FISHING_BOAT_DEATH = 13,
    IMG_FISHING_BOAT_IDLE = 14,
    IMG_FLOTSAM = 15,

    IMG_SIZE
};

struct image_desc_t {
    int pack = 0;
    int id = 0;
};

void set_image_desc(e_img t, int pack, int id);
image_desc_t get_image_desc(e_img t);