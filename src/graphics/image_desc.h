#pragma once

#include <cstdint>
#include "core/xstring.h"

struct image_desc {
    int16_t pack = 0;
    int16_t id = 0;
    int16_t offset = 0;
    xstring path;

    int tid();
    inline image_desc resolve() { tid(); return *this; }

    static image_desc resolve(const xstring &image) {
        image_desc r;
        r.path = image;
        return r.resolve();
    }

    image_desc operator+(int16_t v) const { return {pack, id, int16_t(offset + v)}; }
    bool valid() const { return pack || id || offset; }
};