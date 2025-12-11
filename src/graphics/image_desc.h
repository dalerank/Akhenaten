#pragma once

#include <cstdint>
#include "core/xstring.h"

struct image_desc {
    int pack = 0;
    int id = 0;
    int offset = 0;
    xstring path;

    int tid() const;

    image_desc operator+(int v) const { return {pack, id, offset + v}; }
    bool valid() const { return pack || id || offset; }
};