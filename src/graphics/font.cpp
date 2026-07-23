#include "font.h"

#include "core/encoding/trad_chinese.h"
#include "core/log.h"
#include "image.h"
#include "js/js_game.h"
#include "graphics/imagepak_holder.h"
#include "platform/renderer.h"
#include "content/atlas_packer.h"
#include "content/vfs.h"
#include "game/game_config.h"
#include "game/game.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "window/autoconfig_window.h"
#include "core/app.h"

#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

void ANK_REGISTER_CONFIG_ITERATOR(config_load_external_fonts) {
    font_atlas_regenerate();
}

ANK_CONFIG_STRUCT(font_config, type, size, bold, color, shadow_offset, line_height)
const e_font_tokens_t ANK_CONFIG_ENUM(e_font_tokens);

static int image_y_offset_none(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_default(const uint8_t *c, int image_height, int line_height);

uint32_t base_color_for_font(e_font font) {
    if (font == FONT_SMALL_PLAIN || font == FONT_SMALL_OUTLINED || font == FONT_SMALL_SHADED)
        return COLOR_FONT_PLAIN;
    return COLOR_MASK_NONE;
}

static const int CHAR_TO_FONT_IMAGE_DEFAULT[] = {
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x00, 0x00, 0x41,
  0x00, 0x4A, 0x43, 0x44, 0x42, 0x46, 0x4E, 0x45, 0x4F, 0x4D, 0x3E, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
  0x3D, 0x48, 0x49, 0x00, 0x47, 0x00, 0x4B, 0x00, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x00, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
  0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x72, 0x70, 0x71, 0x71, 0x69, 0x83, 0x6D, 0x65, 0x74, 0x6A, 0x73, 0x73, 0x77, 0x75, 0x76, 0x76, 0x00,
  0x6C, 0x7A, 0x78, 0x79, 0x79, 0x7B, 0x00, 0x84, 0x7E, 0x7C, 0x7D, 0x6B, 0x33, 0x00, 0x68, 0x53, 0x52, 0x54, 0x51,
  0x51, 0x85, 0x67, 0x65, 0x57, 0x56, 0x58, 0x55, 0x5B, 0x5A, 0x5C, 0x59, 0x00, 0x66, 0x5F, 0x5E, 0x60, 0x60, 0x5D,
  0x00, 0x86, 0x63, 0x62, 0x64, 0x61, 0x19, 0x00, 0x19,
};

static const std::array<font_definition, FONT_TYPES_MAX> DEFINITIONS_DEFAULT = { {
     {FONT_SMALL_PLAIN, 0, 0, 6, 1, 11, image_y_offset_default},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_BLUE, 536, 0, 8, 1, 11, image_y_offset_default},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, 0, 8, 0, 23, image_y_offset_default},
     {FONT_LARGE_BLACK_ON_DARK, 804, 0, 8, 0, 23, image_y_offset_default},
     {FONT_SMALL_OUTLINED, 938, 0, 2, -1, 11, image_y_offset_default},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_default},
     {FONT_SMALL_SHADED, 1206, 0, 6, 2, 11, image_y_offset_default}
} };

enum E_MULTIBYTE {
    MULTIBYTE_NONE = 0,
    MULTIBYTE_TRADITIONAL_CHINESE = 1,
    MULTIBYTE_SIMPLIFIED_CHINESE = 2,
    MULTIBYTE_KOREAN = 3,
};

struct font_data_t {
    const int* font_mapping = CHAR_TO_FONT_IMAGE_DEFAULT;
    std::array<font_definition, FONT_TYPES_MAX> font_definitions = DEFINITIONS_DEFAULT;
    font_mbsybols_t mbsymbols;
    std::set<uint32_t> missing_glyphs;
    bool use_utf_font = false;
    bool force_utf_font = false; // set when Pharaoh_Fonts.sg3 is unavailable
    bool needs_regeneration = false;
    bool use_internal_only = false;
    fn_fill_font_packer_t fill_font_packer = nullptr;
};

font_data_t g_font_data;

static int image_y_offset_none(const uint8_t *c, int image_height, int line_height) {
    int offset = image_height - line_height;
    if ((offset < 0 || *c < 0x80) && !g_font_data.use_utf_font) {
        offset = 0;
    }

    return offset;
}

static int image_y_offset_default(const uint8_t *c, int image_height, int line_height) {
    int offset = image_height - line_height;
    if (offset < 0) {
        offset = 0;
    }

    if ((*c < 0x80 || *c == 0xE7) && !g_font_data.use_utf_font) {
        offset = 0;
    }

    if ((*c > 0x80) || g_font_data.use_utf_font) {
        offset = -line_height;
    }

    return offset;
}

// Helper function to decode UTF-8 sequence to Unicode codepoint
static uint32_t utf8_decode(const uint8_t* str, int* out_bytes) {
    if (str[0] < 0x80) {
        // 1-byte sequence (ASCII)
        *out_bytes = 1;
        return str[0];
    } else if ((str[0] & 0xE0) == 0xC0) {
        // 2-byte sequence
        *out_bytes = 2;
        return ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);
    } else if ((str[0] & 0xF0) == 0xE0) {
        // 3-byte sequence
        *out_bytes = 3;
        return ((str[0] & 0x0F) << 12) |
               ((str[1] & 0x3F) << 6) |
               (str[2] & 0x3F);
    } else if ((str[0] & 0xF8) == 0xF0) {
        // 4-byte sequence
        *out_bytes = 4;
        return ((str[0] & 0x07) << 18) |
               ((str[1] & 0x3F) << 12) |
               ((str[2] & 0x3F) << 6) |
               (str[3] & 0x3F);
    }

    // Invalid UTF-8 sequence
    *out_bytes = 1;
    return 0xFFFD; // Unicode replacement character
}

const font_definition* font_definition_for(e_font font) {
    auto& data = g_font_data;
    if (font < 0 || font >= FONT_TYPES_MAX) {
        font = FONT_NORMAL_BLACK_ON_LIGHT;
    }
    return &data.font_definitions[font];
}

font_definition *font_definition_ref(e_font font) {
    auto &data = g_font_data;
    if (font < 0 || font >= FONT_TYPES_MAX) {
        font = FONT_NORMAL_BLACK_ON_LIGHT;
    }
    return &data.font_definitions[font];
}

bool font_can_display(const uint8_t* character) {
    auto& data = g_font_data;
    int dummy;
    const auto glyph = font_letter_id(&data.font_definitions[FONT_NORMAL_BLACK_ON_LIGHT], character, &dummy);
    return glyph.imagid >= 0;
}

bool font_has_letter(const font_definition *def, const uint8_t *str) {
    auto &data = g_font_data;
    const auto &mbmap = data.mbsymbols[def->font];
    int num_bytes = 0;
    const uint32_t code = utf8_decode(str, &num_bytes);
    auto it = mbmap.find(code);
    return (it != mbmap.end());
}

font_glyph font_letter_id(const font_definition* def, const uint8_t* str, int* num_bytes) {
    auto& data = g_font_data;

    if (data.use_internal_only) {
        const auto &mbmap = data.mbsymbols[def->font];
        const uint32_t code = utf8_decode(str, num_bytes);
        auto it = mbmap.find(code);
        if (it != mbmap.end()) {
            return it->second;
        }

        font_add_missing_glyph(code);
    } else if (*str >= 0x80 || data.use_utf_font) {
        const auto &mbmap = data.mbsymbols[def->font];
        const uint32_t code = utf8_decode(str, num_bytes);
        auto it = mbmap.find(code);
        if (it != mbmap.end()) {
            return it->second;
        }

        // Add missing glyph for later regeneration
        font_add_missing_glyph(code);
    } else {
        *num_bytes = 1;
        if (!data.font_mapping[*str]) {
            return { 0xffffffff, -1 };
        }

        font_glyph r;
        r.code = *str;
        r.imagid = data.font_mapping[*str] + def->image_offset - 1;

        return r;
    }

    return { 0xffffffff, -1 };
}

void font_set_letter_id(e_font font, uint32_t character, int imgid, vec2i bearing) {
    auto &data = g_font_data;
    auto &mbmap = data.mbsymbols[font];
    mbmap[character] = { character, imgid, bearing };
}

const font_mbsybols_t &font_get_symbols() {
    return g_font_data.mbsymbols;
}

void font_atlas_regenerate() {
    image_packer font_packer;
    auto &font_pack = g_image_data->pak_list[PACK_CUSTOM_FONT];

    if (!font_pack.handle) {
        return;
    }

#ifdef __EMSCRIPTEN__
    // On Emscripten do not load custom TTF fonts; use built-in Pharaoh_Fonts only
    g_font_data.use_utf_font = false;
    g_font_data.needs_regeneration = false;
    return;
#endif

    vfs::path symbols_font;
    svector<uint32_t, 1024> utf8_symbols;
    xstring locale_short = game_features::gameopt_language.to_string();
    if (!locale_short) {
        locale_short = "en";
    }

    font_configs_t font_configs;
    bool font_bold = false;

    g_config_arch.r_array("game_languages", [&] (archive arch) {
        xstring lang_current = arch.r_string("lang");
        if (lang_current != locale_short) {
            return;
        }

        xstring symbols = arch.r_string("symbols");
        if (symbols.empty()) {
            return;
        }

        arch.r("font_configs", font_configs);
        symbols_font = arch.r_string("font");

        svector<bstring32, 1024> data_str;
        string_to_array_t(data_str, symbols.c_str(), ',');

        svector<uint64_t, 1024> data;
        for (const auto& x: data_str) {
            char sym[8] = { 0 };
            memcpy(sym, (uint32_t *)x.c_str(), 4);
            data.push_back( *(uint64_t*)sym );
        }

        for (const auto &sym : data) {
            uint8_t symbol_len = strlen((pcstr)&sym);
            uint32_t symdec = 0;
            switch (symbol_len) {
            case 1: // single byte
                symdec = *(uint8_t *)&sym;
                break;
            case 2: { // two bytes - UTF-8 decoding for 2-byte sequences
                    uint8_t* symdata = (uint8_t*)&sym;
                    symdec = ((symdata[0] & 0x1F) << 6) | (symdata[1] & 0x3F);
                }
                break;
            case 3: { // three bytes (most common for non-ASCII)
                    // UTF-8 decoding for 3-byte sequences
                    uint8_t* symdata = (uint8_t*)&sym;
                    symdec = ((symdata[0] & 0x0F) << 12) |
                             ((symdata[1] & 0x3F) << 6) |
                             (symdata[2] & 0x3F);
                }
                break;
            case 4: { // four bytes - UTF-8 decoding for 4-byte sequences
                    uint8_t* symdata = (uint8_t*)&sym;
                    symdec = ((symdata[0] & 0x07) << 18) |
                             ((symdata[1] & 0x3F) << 12) |
                             ((symdata[2] & 0x3F) << 6) |
                             (symdata[3] & 0x3F);
                }
                break;
            default:
                return;
            }
            utf8_symbols.push_back(symdec);
        }
    });

    g_font_data.use_utf_font = (locale_short != "en") || g_font_data.force_utf_font;
    if (!g_args.get_custom_font().empty() && !g_font_data.use_utf_font) {
        g_font_data.use_utf_font = true;
    }

    // Add basic latin characters (ASCII 32-126) to ensure they are always generated from the TTF font
    // This ensures visual consistency between latin and UTF-8 characters
    for (uint32_t codepoint = 0; codepoint <= 126; ++codepoint) {
        utf8_symbols.push_back(codepoint);
    }

    // Add missing glyphs to the list
    for (uint32_t missing_codepoint : g_font_data.missing_glyphs) {
        utf8_symbols.push_back(missing_codepoint);
    }

    std::sort(utf8_symbols.begin(), utf8_symbols.end());
    utf8_symbols.erase(std::unique(utf8_symbols.begin(), utf8_symbols.end()), utf8_symbols.end());

    if (utf8_symbols.empty()) {
        return;
    }

    // Reset font pack
    font_pack.handle->cleanup_and_destroy();
    font_pack.handle->images_array.clear();

    // Initialize packer
    vec2i max_texture_sizes = g_render.get_max_image_size();
    font_packer.init(utf8_symbols.size() * font_configs.size(), max_texture_sizes);

    int cp_index = 0;
    if (!g_args.get_custom_font().empty()) {
        symbols_font = g_args.get_custom_font().c_str();
    }

    if (!g_font_data.fill_font_packer(font_packer, font_pack, font_configs, utf8_symbols, symbols_font, cp_index)) {
        // TTF missing or unreadable (common for incomplete installs) — use embedded 5x7.
        logs::warn("font: TTF fill failed (%s) — using embedded GLCD fallback", symbols_font.c_str());
        cp_index = 0;
        font_pack.handle->images_array.clear();
        if (!fill_font_packer_internal_only(font_packer, font_pack, font_configs, utf8_symbols, symbols_font, cp_index)) {
            g_font_data.needs_regeneration = false;
            return;
        }
    }

    // Pack images into atlas
    font_packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
    font_packer.options.reduce_image_size = 1;
    font_packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

    image_packer_pack(font_packer);

    // Create atlas pages
    font_pack.handle->atlas_pages.reserve(font_packer.result.pages_needed);
    for (uint32_t i = 0; i < font_packer.result.pages_needed; ++i) {
        atlas_data_t atlas_data;
        atlas_data.width = i == font_packer.result.pages_needed - 1 ? font_packer.result.last_image_width : max_texture_sizes.x;
        atlas_data.height = i == font_packer.result.pages_needed - 1 ? font_packer.result.last_image_height : max_texture_sizes.y;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.temp.pixel_buffer = new color[atlas_data.bmp_size];
        memset(atlas_data.temp.pixel_buffer, 0, atlas_data.bmp_size * sizeof(uint32_t));
        atlas_data.texture = nullptr;
        font_pack.handle->atlas_pages.push_back(atlas_data);
    }

    // Finish filling in image and atlas information.
    // No magic upper bound here: the real safety check is `image_id < 0xffff`
    // below, which keeps the font pak inside its reserved index range.
    for (int i = 0; i < font_pack.handle->images_array.size(); i++) {
        image_t &img = font_pack.handle->images_array.at(i);

        image_packer_rect &rect = font_packer.rects[i];
        img.atlas.index = rect.output.image_index;
        atlas_data_t *p_data = &font_pack.handle->atlas_pages.at(img.atlas.index);
        img.atlas.p_atlas = p_data;
        img.atlas.offset = rect.output.pos;

        // Load and convert image bitmap data
        image_copy_to_atlas(img);

        int image_id = font_pack.handle->global_image_index_offset + i;
        assert(image_id < 0xffff);
        imagepak::update_max_imgid(image_id);

        font_set_letter_id((e_font)img.temp.font_type, img.temp.symdeck, image_id, { img.temp.bearing_x, img.temp.bearing_y });
    }

    // Create textures from atlas data
    for (int i = 0; i < font_pack.handle->atlas_pages.size(); ++i) {
        atlas_data_t &atlas_data = font_pack.handle->atlas_pages.at(i);
        atlas_data.texture = g_render.create_texture_from_buffer(atlas_data.temp.pixel_buffer, atlas_data.width, atlas_data.height);
        assert(atlas_data.texture != nullptr);

        // Delete temp data buffer in the atlas
        delete atlas_data.temp.pixel_buffer;
        atlas_data.temp.pixel_buffer = nullptr;
    }

    // Remove pointers to raw data buffer in the images
    for (int i = 0; i < font_pack.handle->images_array.size(); ++i) {
        image_t &img = font_pack.handle->images_array.at(i);
        SDL_FreeSurface((SDL_Surface *)img.temp.surface);
        img.temp.surface = nullptr;
    }

    font_pack.handle->entries_num = font_pack.handle->images_array.size();
    font_pack.entries_num = font_pack.handle->entries_num;
    image_packer_reset(font_packer);

    g_font_data.needs_regeneration = false;
}

void font_enable_sg3_fallback() {
    logs::warn("font: Pharaoh_Fonts.sg3 unavailable — enabling custom font fallback");
    g_font_data.force_utf_font = true;
    g_font_data.use_utf_font = true;
    font_atlas_regenerate();
    if (g_image_data) {
        // Treat custom atlas as the active font pack for readiness checks.
        g_image_data->fonts_loaded = !g_font_data.mbsymbols[FONT_SMALL_PLAIN].empty();
    }
}

void font_add_missing_glyph(uint32_t codepoint) {
    auto& data = g_font_data;

    // Don't add if it's a control character or already exists
    if (codepoint < 32 || codepoint == 0xFFFD) {
        return;
    }

    // Check if already in any font
    auto it = std::find(data.missing_glyphs.begin(), data.missing_glyphs.end(), codepoint);
    if (it != data.missing_glyphs.end()) {
        return;
    }

    // Add to missing glyphs set
    if (data.missing_glyphs.insert(codepoint).second) {
        data.needs_regeneration = true;
    }
}

bool font_need_regeneration() {
    return g_font_data.needs_regeneration;
}

void ANK_REGISTER_APPLICATION_MODULE(font_module) {
    g_font_data.use_internal_only = g_args.no_resource();

    if (g_font_data.use_internal_only) {
        g_font_data.fill_font_packer = fill_font_packer_internal_only;
    } else if (platform.is_android()) {
        g_font_data.fill_font_packer = fill_font_packer_android;
    } else {
        g_font_data.fill_font_packer = fill_font_packer_pc;
    }

    game.add_frame_serial_part_handler([]() {
        if (game.system_language_changed || font_need_regeneration()) {
            game.system_language_changed = false;
            font_atlas_regenerate();
            autoconfig_window::refresh_all();
        }
    });
}