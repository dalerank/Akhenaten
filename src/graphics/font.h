#pragma once

#include "core/encoding.h"
#include "core/tokenum.h"
#include "content/dir.h"

#include <stdint.h>
#include <unordered_map>
#include <array>

enum e_font {
    FONT_SMALL_PLAIN,
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

using e_font_tokens_t = token_holder<e_font, FONT_SMALL_PLAIN, FONT_TYPES_MAX>;
extern const e_font_tokens_t e_font_tokens;

using fonts_vec = std::array<e_font, 2>;

struct font_glyph {
    uint32_t code; // code point
    int imagid; // texture
    vec2i bearing;
    int advance; // horizontal advance to next character
};

using multibyte_map_t = std::unordered_map<uint32_t, font_glyph>;
using font_mbsybols_t = std::array<multibyte_map_t, FONT_TYPES_MAX>;

struct font_definition {
    e_font font;
    int image_offset;
    int multibyte_image_offset;
    int space_width;
    int letter_spacing;
    int line_height;

    /**
     * Returns the height offset for the specified character
     * @param c Character
     * @param image_height Height of the letter image
     * @param line_height Line height for the font
     * @return Offset to subtract from y coordinate
     */
    int (*image_y_offset)(const uint8_t *c, int image_height, int line_height);
};

/**
 * Gets the font definition for the specified font
 * @param font Font
 * @return Font definition
 */
const font_definition* font_definition_for(e_font font);

/**
 * Checks whether the font has a glyph for the passed character
 * @param character Character to check
 * @return Boolean true if this character can be drawn on the screen, false otherwise
 */
int font_can_display(const uint8_t* character);

/**
 * Gets the letter ID for the specified character and font
 * @param def Font definition
 * @param str Character string
 * @param num_bytes Out: number of bytes consumed by letter
 * @return Letter ID to feed into image_letter(), or -1 if c is no letter
 */
font_glyph font_letter_id(const font_definition* def, const uint8_t* str, int* num_bytes);
bool font_has_letter(const font_definition *def, const uint8_t *str);
void font_set_letter_id(e_font font, uint32_t character, int imgid, vec2i bearing, int advance = 0);

void font_atlas_regenerate();

const font_mbsybols_t &font_get_symbols();