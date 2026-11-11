#pragma once

#include <cstdint>
#include "core/xstring.h"

// Result of an image lookup whose pack or group is not available (no Pharaoh art). Never 0: the
// simulation reads 0 in map_image as "no image assigned yet" (OG map_grids.images[offset] != 0), so
// missing art must still look assigned. Never a real id: real ids are >= 0.
constexpr int IMAGE_ID_MISSING = -1;

// base + offset, keeping a missing base missing instead of turning it into a real-looking id.
inline int image_offset(int base, int offset) {
    return base < 0 ? IMAGE_ID_MISSING : base + offset;
}

struct image_desc {
    mutable int16_t pack = 0;
    mutable int16_t id = 0;
    mutable int16_t offset = 0;
    xstring path;

    int tid() const;
    inline image_desc resolve() { tid(); return *this; }

    static image_desc resolve(const xstring &image) {
        image_desc r;
        r.path = image;
        return r.resolve();
    }

    image_desc operator+(int16_t v) const { return {pack, id, int16_t(offset + v)}; }
    bool valid() const { return pack || id || offset || !path.empty(); }
};