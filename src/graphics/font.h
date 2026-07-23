#pragma once

#include "core/encoding.h"
#include "core/tokenum.h"
#include "font_common.h"
#include "content/dir.h"

#include <stdint.h>
#include <unordered_map>
#include <array>

using e_font_tokens_t = token_holder<e_font, FONT_SMALL_PLAIN, FONT_TYPES_MAX>;
extern const e_font_tokens_t e_font_tokens;

using fonts_vec = std::array<e_font, 2>;

struct font_glyph {
    uint32_t code; // code point
    int imagid; // texture
    vec2i bearing;
};

using multibyte_map_t = std::unordered_map<uint32_t, font_glyph>;
using font_mbsybols_t = std::array<multibyte_map_t, FONT_TYPES_MAX>;

struct image_packer;
struct imagepak_handle;

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
font_definition* font_definition_ref(e_font font);

/**
 * Checks whether the font has a glyph for the passed character
 * @param character Character to check
 * @return Boolean true if this character can be drawn on the screen, false otherwise
 */
bool font_can_display(const uint8_t* character);

/**
 * Gets the letter ID for the specified character and font
 * @param def Font definition
 * @param str Character string
 * @param num_bytes Out: number of bytes consumed by letter
 * @return Letter ID to feed into image_letter(), or -1 if c is no letter
 */
font_glyph font_letter_id(const font_definition* def, const uint8_t* str, int* num_bytes);
bool font_has_letter(const font_definition *def, const uint8_t *str);
void font_set_letter_id(e_font font, uint32_t character, int imgid, vec2i bearing);

bool fill_font_packer_internal_only(image_packer& font_packer,
                                    imagepak_handle font_pack,
                                    const font_configs_t &font_configs,
                                    const font_utf8_symbols_t &utf8_symbols,
                                    vfs::path symbols_font,
                                    int &cp_index);

bool fill_font_packer_android(image_packer& font_packer,
                              imagepak_handle font_pack,
                              const font_configs_t &font_configs,
                              const font_utf8_symbols_t &utf8_symbols,
                              vfs::path symbols_font,
                              int &cp_index);

bool fill_font_packer_pc(image_packer& font_packer,
                         imagepak_handle font_pack,
                         const font_configs_t &font_configs,
                         const font_utf8_symbols_t &utf8_symbols,
                         vfs::path symbols_font,
                         int &cp_index);


void font_atlas_regenerate();
void font_add_missing_glyph(uint32_t codepoint);
uint32_t base_color_for_font(e_font font);

void font_enable_sg3_fallback();

bool font_need_regeneration();

const font_mbsybols_t &font_get_symbols();