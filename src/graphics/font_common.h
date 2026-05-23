#pragma once

#include "graphics/font.h"
#include "graphics/imagepak_holder.h"
#include "content/atlas_packer.h"
#include "content/vfs.h"
#include "core/stable_array.h"
#include "core/svector.h"

#include <cstdint>
#include <functional>

enum e_font {
    FONT_SMALL_PLAIN = 0,
    FONT_NORMAL_BLACK_ON_LIGHT,
    FONT_NORMAL_WHITE_ON_DARK,
    FONT_NORMAL_YELLOW, // Yellow font for Pharaoh
    FONT_NORMAL_BLUE,   // Blue font for Pharaoh
    FONT_LARGE_BLACK_ON_LIGHT,
    FONT_LARGE_BLACK_ON_DARK,
    FONT_SMALL_OUTLINED,
    FONT_NORMAL_BLACK_ON_DARK,
    FONT_SMALL_SHADED,
    FONT_TYPES_MAX,
    FONT_INVALID = 0xff
};

struct font_config {
    e_font type;
    uint32_t color;
    bool bold;
    int8_t shadow_offset;
    uint8_t size;
    uint8_t line_height;
};

template<>
struct stable_array_max_elements<font_config> {
    enum { max_elements = FONT_TYPES_MAX };
};

template<>
struct std::hash<font_config> {
    [[nodiscard]] size_t operator()(const font_config &f) const noexcept {
        return f.type;
    }
};

using font_configs_t = stable_array<font_config>;
using font_utf8_symbols_t = svector<uint32_t, 1024>;

using fn_fill_font_packer_t = bool (*)(image_packer&,
                                       imagepak_handle,
                                       const font_configs_t &,
                                       const font_utf8_symbols_t &,
                                       vfs::path,
                                       int &);
