#pragma once

#include <cstdint>

struct image_desc {
    int pack = 0;
    int id = 0;
    int offset = 0;

    image_desc operator+(int v) const { return {pack, id, offset + v}; }
};
