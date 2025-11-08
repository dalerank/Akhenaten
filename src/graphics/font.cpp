#include "font.h"

#include "core/encoding/trad_chinese.h"
#include "image.h"
#include "js/js_game.h"
#include "graphics/imagepak_holder.h"
#include "platform/renderer.h"
#include "content/atlas_packer.h"
#include "graphics/fontgen/Atlas.hpp"
#include "graphics/fontgen/Charset.hpp"
#include "graphics/fontgen/Font.hpp"
#include "game/game_config.h"

image_packer font_packer;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_external_fonts) {
    font_atlas_regenerate();
}

const e_font_tokens_t ANK_CONFIG_ENUM(e_font_tokens);

static int image_y_offset_none(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_default(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_eastern(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_normal_small_plain(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_normal_colored(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_large_plain(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_large_black(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_large_brown(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_cyrillic_small_black(const uint8_t *c, int image_height, int line_height);
static int image_y_offset_korean(const uint8_t *c, int image_height, int line_height);

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

static const int CHAR_TO_FONT_IMAGE_EASTERN[] = {
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x01, 0x01, 0x01, 0x00, 0x00, 0x20, 0x44, 0x6E, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x00, 0x00, 0x41,
  0x00, 0x4A, 0x43, 0x44, 0x42, 0x46, 0x4E, 0x45, 0x4F, 0x4D, 0x3E, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
  0x3D, 0x48, 0x49, 0x00, 0x47, 0x00, 0x4B, 0x00, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x00, 0x63, 0x00, 0x00,
  0x50, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
  0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x61, 0x56, 0x54, 0x51,
  0x53, 0x01, 0x67, 0x81, 0x55, 0x57, 0x59, 0x6F, 0x5D, 0x69, 0x70, 0x6A, 0x67, 0x6D, 0x60, 0x5D, 0x5F, 0x64, 0x63,
  0x19, 0x7B, 0x6B, 0x00, 0x57, 0x00, 0x00, 0x58, 0x52, 0x7F, 0x5E, 0x6C, 0x66, 0x69, 0x01, 0x0F, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x71, 0x82, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x59, 0x72, 0x70, 0x71, 0x71, 0x69, 0x83, 0x6A, 0x65, 0x74, 0x6A, 0x6B, 0x73, 0x77, 0x75, 0x76, 0x76, 0x00,
  0x6D, 0x7A, 0x6E, 0x79, 0x79, 0x7B, 0x00, 0x84, 0x7E, 0x7C, 0x7D, 0x6B, 0x33, 0x00, 0x68, 0x53, 0x52, 0x54, 0x51,
  0x51, 0x85, 0x52, 0x65, 0x57, 0x56, 0x53, 0x55, 0x5B, 0x5A, 0x5C, 0x59, 0x00, 0x55, 0x5F, 0x56, 0x60, 0x60, 0x5D,
  0x00, 0x86, 0x63, 0x62, 0x64, 0x61, 0x19, 0x00, 0x19,
};

static const int CHAR_TO_FONT_IMAGE_CYRILLIC[] = {
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x01, 0x01, 0x01, 0x00, 0x00, 0x20, 0x44, 0x6E, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x00, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x00, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
  0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
  0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82,
  0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95,
  0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E,
};

static const font_definition DEFINITIONS_DEFAULT[]
  = {{FONT_SMALL_PLAIN, 0, 0, 6, 1, 11, image_y_offset_default},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_default},
     {FONT_NORMAL_BLUE, 536, 0, 8, 1, 11, image_y_offset_default},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, 0, 8, 0, 23, image_y_offset_default},
     {FONT_LARGE_BLACK_ON_DARK, 804, 0, 8, 0, 23, image_y_offset_default},
     {FONT_SMALL_OUTLINED, 938, 0, 2, -1, 11, image_y_offset_default},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_default},
     {FONT_SMALL_SHADED, 1206, 0, 6, 2, 11, image_y_offset_default}};

static const font_definition DEFINITIONS_EASTERN[]
  = {{FONT_SMALL_PLAIN, 0, 0, 6, 1, 11, image_y_offset_eastern},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_eastern},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_eastern},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_eastern},
     {FONT_NORMAL_BLUE, 536, 0, 8, 1, 23, image_y_offset_eastern},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, 0, 8, 0, 23, image_y_offset_eastern},
     {FONT_LARGE_BLACK_ON_DARK, 804, 0, 8, 0, 24, image_y_offset_eastern},
     {FONT_SMALL_OUTLINED, 938, 0, 4, 1, 9, image_y_offset_eastern},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_eastern},
     {FONT_SMALL_SHADED, 1206, 0, 6, 0, 11, image_y_offset_eastern}};

static const font_definition DEFINITIONS_CYRILLIC[]
  = {{FONT_SMALL_PLAIN, 0, 0, 6, 1, 11, image_y_offset_cyrillic_normal_small_plain},
     {FONT_NORMAL_BLACK_ON_LIGHT, 158, 0, 6, 0, 11, image_y_offset_cyrillic_normal_colored},
     {FONT_NORMAL_WHITE_ON_DARK, 316, 0, 6, 0, 11, image_y_offset_cyrillic_normal_colored},
     {FONT_NORMAL_YELLOW, 474, 0, 6, 0, 11, image_y_offset_cyrillic_normal_colored},
     {FONT_NORMAL_BLUE, 632, 0, 8, 1, 23, image_y_offset_cyrillic_large_plain},
     {FONT_LARGE_BLACK_ON_LIGHT, 790, 0, 8, 0, 23, image_y_offset_cyrillic_large_black},
     {FONT_LARGE_BLACK_ON_DARK, 948, 0, 8, 0, 24, image_y_offset_cyrillic_large_brown},
     {FONT_SMALL_OUTLINED, 1106, 0, 4, 1, 9, image_y_offset_cyrillic_normal_small_plain},
     {FONT_NORMAL_BLACK_ON_DARK, 1264, 0, 6, 0, 11, image_y_offset_cyrillic_normal_colored},
     {FONT_SMALL_SHADED, 1422, 0, 6, 0, 11, image_y_offset_cyrillic_small_black}};

static const font_definition DEFINITIONS_TRADITIONAL_CHINESE[]
  = {{FONT_SMALL_PLAIN, 0, IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS, 6, 1, 11, image_y_offset_none},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_BLUE, 536, IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS * 2, 8, 1, 23, image_y_offset_none},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS * 2, 8, 0, 23, image_y_offset_none},
     {FONT_LARGE_BLACK_ON_DARK, 804, IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS * 2, 8, 0, 24, image_y_offset_none},
     {FONT_SMALL_OUTLINED, 938, 0, 4, 1, 9, image_y_offset_none},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_none},
     {FONT_SMALL_SHADED, 1206, 0, 6, 0, 11, image_y_offset_none}};

static const font_definition DEFINITIONS_SIMPLIFIED_CHINESE[]
  = {{FONT_SMALL_PLAIN, 0, IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS, 6, 1, 11, image_y_offset_none},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_none},
     {FONT_NORMAL_BLUE, 536, IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS * 2, 8, 1, 23, image_y_offset_none},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS * 2, 8, 0, 23, image_y_offset_none},
     {FONT_LARGE_BLACK_ON_DARK, 804, IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS * 2, 8, 0, 24, image_y_offset_none},
     {FONT_SMALL_OUTLINED, 938, 0, 4, 1, 9, image_y_offset_none},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_none},
     {FONT_SMALL_SHADED, 1206, 0, 6, 0, 11, image_y_offset_none}};

static const font_definition DEFINITIONS_KOREAN[]
  = {{FONT_SMALL_PLAIN, 0, IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS * 1, 6, 1, 11, image_y_offset_korean},
     {FONT_NORMAL_BLACK_ON_LIGHT, 134, 0, 6, 0, 11, image_y_offset_korean},
     {FONT_NORMAL_WHITE_ON_DARK, 268, 0, 6, 0, 11, image_y_offset_korean},
     {FONT_NORMAL_YELLOW, 402, 0, 6, 0, 11, image_y_offset_korean},
     {FONT_NORMAL_BLUE, 536, IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS * 2, 8, 1, 23, image_y_offset_korean},
     {FONT_LARGE_BLACK_ON_LIGHT, 670, IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS * 2, 8, 0, 23, image_y_offset_korean},
     {FONT_LARGE_BLACK_ON_DARK, 804, IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS * 2, 8, 0, 24, image_y_offset_korean},
     {FONT_SMALL_OUTLINED, 938, 0, 4, 1, 9, image_y_offset_korean},
     {FONT_NORMAL_BLACK_ON_DARK, 1072, 0, 6, 0, 11, image_y_offset_korean},
     {FONT_SMALL_SHADED, 1206, 0, 6, 0, 11, image_y_offset_korean}};

enum E_MULTIBYTE {
    MULTIBYTE_NONE = 0,
    MULTIBYTE_TRADITIONAL_CHINESE = 1,
    MULTIBYTE_SIMPLIFIED_CHINESE = 2,
    MULTIBYTE_KOREAN = 3,
};

struct font_data_t {
    const int* font_mapping = CHAR_TO_FONT_IMAGE_DEFAULT;
    const font_definition* font_definitions = DEFINITIONS_DEFAULT;
    font_mbsybols_t mbsymbols;
};

font_data_t g_font_data;

static int image_y_offset_none(const uint8_t *c, int image_height, int line_height) {
    int offset = image_height - line_height;
    if (offset < 0 || *c < 0x80)
        offset = 0;

    return offset;
}

static int image_y_offset_default(const uint8_t *c, int image_height, int line_height) {
    int offset = image_height - line_height;
    if (offset < 0)
        offset = 0;

    if (*c < 0x80 || *c == 0xE7) {
        offset = 0;
    }

    if (*c > 0x80) {
        offset = -line_height;
    }

    return offset;
}

static int image_y_offset_eastern(const uint8_t *c, int image_height, int line_height) {
    int offset = image_height - line_height;
    if (offset < 0)
        offset = 0;

    if (*c < 0x80 || *c == 0xEA || *c == 0xB9 || *c == 0xA5 || *c == 0xCA)
        offset = 0;

    return offset;
}

static int image_y_offset_cyrillic_normal_small_plain(const uint8_t *c, int image_height, int line_height) {
    switch (*c) {
    case 36:
        return 1;
    case 201:
        return 3;
    case 225:
        return 1;
    default:
        return 0;
    }
}

static int image_y_offset_cyrillic_normal_colored(const uint8_t *c, int image_height, int line_height) {
    return *c == 201 ? 3 : 0;
}

static int image_y_offset_cyrillic_large_plain(const uint8_t *c, int image_height, int line_height) {
    switch (*c) {
    case 36:
        return 2;
    case 201:
        return 7;
    case 35:
    case 42:
    case 47:
    case 64:
    case 92:
    case 98:
    case 100:
    case 102:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 124:
    case 225:
    case 244:
        return 1;
    default:
        return 0;
    }
}

static int image_y_offset_cyrillic_large_black(const uint8_t *c, int image_height, int line_height) {
    switch (*c) {
    case 36:
        return 2;
    case 201:
        return 7;
    case 35:
    case 40:
    case 41:
    case 42:
    case 47:
    case 64:
    case 92:
    case 98:
    case 100:
    case 102:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 123:
    case 124:
    case 125:
    case 225:
    case 244:
        return 1;
    default:
        return 0;
    }
}

static int image_y_offset_cyrillic_large_brown(const uint8_t *c, int image_height, int line_height) {
    switch (*c) {
    case 36:
        return 2;
    case 201:
        return 7;
    case 40:
    case 41:
    case 42:
    case 47:
    case 64:
    case 92:
    case 96:
    case 98:
    case 100:
    case 102:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 123:
    case 124:
    case 125:
    case 225:
    case 244:
        return 1;
    default:
        return 0;
    }
}

static int image_y_offset_cyrillic_small_black(const uint8_t *c, int image_height, int line_height) {
    switch (*c) {
    case 36:
    case 40:
    case 41:
    case 42:
    case 47:
    case 64:
    case 92:
    case 98:
    case 100:
    case 102:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 123:
    case 124:
    case 125:
    case 225:
    case 244:
        return 1;
    case 201:
        return 4;
    default:
        return 0;
    }
}

static int image_y_offset_korean(const uint8_t *c, int image_height, int line_height) {
    if (*c < 0x80)
        return 0;

    if (line_height == 11) {
        if (image_height == 12)
            return 0;
        else if (image_height == 15)
            return 3;
    }
    return image_height - line_height;
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
    return &data.font_definitions[font];
}

int font_can_display(const uint8_t* character) {
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
    if (*str >= 0x80) {
        const auto &mbmap = data.mbsymbols[def->font];
        const uint32_t code = utf8_decode(str, num_bytes);
        auto it = mbmap.find(code);
        if (it != mbmap.end()) {
            return it->second;
        }
        //if (data.multibyte == MULTIBYTE_TRADITIONAL_CHINESE) {
        //    int char_id = (str[0] & 0x7f) | ((str[1] & 0x7f) << 7);
        //    if (char_id >= IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS) {
        //        // lookup in table
        //        int big5_encoded = str[0] << 8 | str[1];
        //        char_id = encoding_trad_chinese_big5_to_image_id(big5_encoded);
        //        if (char_id < 0 || char_id >= IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS)
        //            return -1;
        //    }
        //    return IMAGE_FONT_MULTIBYTE_OFFSET + def->multibyte_image_offset + char_id;
        //} else if (data.multibyte == MULTIBYTE_SIMPLIFIED_CHINESE) {
        //    int char_id = (str[0] & 0x7f) | ((str[1] & 0x7f) << 7);
        //    if (char_id >= IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS)
        //        return -1;
        //
        //    return IMAGE_FONT_MULTIBYTE_OFFSET + def->multibyte_image_offset + char_id;
        //} else if (data.multibyte == MULTIBYTE_KOREAN) {
        //    int b0 = str[0] - 0xb0;
        //    int b1 = str[1] - 0xa1;
        //    int char_id = b0 * 94 + b1;
        //    if (b0 < 0 || b1 < 0 || char_id < 0 || char_id >= IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS)
        //        return -1;
        //
        //    return IMAGE_FONT_MULTIBYTE_OFFSET + def->multibyte_image_offset + char_id;
        //} else {
        //    return -1;
        //}
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

// Font size mapping for different font types
static int get_font_size(e_font font) {
    switch (font) {
    case FONT_SMALL_PLAIN:
    case FONT_SMALL_OUTLINED:
    case FONT_SMALL_SHADED:
        return 10;

    case FONT_NORMAL_BLACK_ON_LIGHT:
    case FONT_NORMAL_WHITE_ON_DARK:
    case FONT_NORMAL_YELLOW:
    case FONT_NORMAL_BLUE:
    case FONT_NORMAL_BLACK_ON_DARK:
        return 14;

    case FONT_LARGE_BLACK_ON_LIGHT:
    case FONT_LARGE_BLACK_ON_DARK:
        return 18;

    default:
        return 14;
    }
}

void font_atlas_regenerate() {
    auto &font_pack = g_image_data->pak_list[PACK_CUSTOM_FONT];

    if (!font_pack.handle) {
        return;
    }

    vfs::path symbols_font;
    svector<uint32_t, 1024> utf8_symbols;
    xstring locale_short = game_features::gameopt_language.to_string();

    g_config_arch.r_array("game_languages", [&] (archive arch) {
        xstring lang_current = arch.r_string("lang");
        if (lang_current != locale_short) {
            return;
        }

        pcstr symbols = arch.r_string("symbols");
        if (!symbols || !*symbols) {
            return;
        }

        symbols_font = arch.r_string("font");

        svector<bstring32, 1024> data_str;
        string_to_array_t(data_str, symbols, ',');
        
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

    if (utf8_symbols.empty()) {
        return;
    }

    // Reset font pack
    font_pack.handle->cleanup_and_destroy();
    font_pack.handle->images_array.clear();

    // Initialize packer
    vec2i max_texture_sizes = graphics_renderer()->get_max_image_size();
    font_packer.init(utf8_symbols.size(), max_texture_sizes);

    // Generate atlas for each symbol
    int cp_index = 0;
    for (const auto &codepoint : utf8_symbols) {
        Trex::Charset charset;
        charset.AddCodepoint(codepoint);

        int font_size = get_font_size(FONT_SMALL_PLAIN);
        uint8_t colors[] = { 0, 0, 0, 255 };
        Trex::Atlas atlas(symbols_font.c_str(), font_size, charset, Trex::RenderMode::COLOR, 1, false, colors);

        const auto &bitmap = atlas.GetBitmap();

        // Create image for this symbol
        image_t img;
        img.pak_name = font_pack.handle->name;
        img.sgx_index = cp_index;
        img.data_length = -1;
        img.uncompressed_length = -1;
        img.unk00 = -1;
        img.start_index = font_pack.handle->global_image_index_offset;
        img.offset_mirror = 0;

        uint32_t Rmask = 0x000000FF;
        uint32_t Gmask = 0x0000FF00;
        uint32_t Bmask = 0x00FF0000;
        uint32_t Amask = 0xFF000000;

        SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap.Width(), bitmap.Height(), 32, Rmask, Gmask, Bmask, Amask);
        if (surface) {
            size_t byteToCopy = bitmap.Width() * bitmap.Height() * 4;
            memcpy(surface->pixels, bitmap.Data().data(), byteToCopy);
        }

        img.width = surface ? surface->w : 0;
        img.height = surface ? surface->h : 0;
        img.temp.surface = (void *)surface;
        img.temp.bearing_x = atlas.GetGlyphs().GetGlyphByIndex(0).bearingX;
        img.temp.bearing_y = atlas.GetGlyphs().GetGlyphByIndex(0).bearingY;
        img.temp.symdeck = codepoint;

        img.unk01 = -1;
        img.unk02 = -1;
        img.unk03 = -1;
        img.animation.num_sprites = -1;
        img.animation.unk04 = -1;
        img.animation.sprite_offset = { -1, -1 };
        img.animation.unk05 = -1;
        img.animation.unk06 = -1;
        img.animation.unk07 = -1;
        img.animation.unk08 = -1;
        img.animation.unk09 = -1;
        img.animation.can_reverse = false;
        img.animation.unk10 = -1;
        img.type = -1;
        img.is_fully_compressed = false;
        img.is_external = false;
        img.has_isometric_top = false;
        img.unk11 = -1;
        img.unk12 = -1;
        img.bmp.group_id = 0;
        img.bmp.name = "custom_font";
        img.bmp.entry_index = 0;
        img.unk13 = -1;
        img.animation.speed_id = 1;
        img.unk14 = -1;
        img.unk15 = -1;
        img.unk16 = -1;
        img.unk17 = -1;
        img.unk18 = -1;
        img.unk19 = -1;
        img.unk20 = -1;

        image_packer_rect *rect = &font_packer.rects[cp_index];
        rect->input.width = img.width;
        rect->input.height = img.height;

        font_pack.handle->images_array.push_back(img);
        cp_index++;
    }

    // Pack images into atlas
    font_packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
    font_packer.options.reduce_image_size = 1;
    font_packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

    image_packer_pack(&font_packer);

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

    // Finish filling in image and atlas information
    for (int i = 0; i < utf8_symbols.size(); i++) {
        image_t &img = font_pack.handle->images_array.at(i);

        image_packer_rect &rect = font_packer.rects[i];
        img.atlas.index = rect.output.image_index;
        atlas_data_t *p_data = &font_pack.handle->atlas_pages.at(img.atlas.index);
        img.atlas.p_atlas = p_data;
        img.atlas.offset = rect.output.pos;

        // Load and convert image bitmap data
        image_copy_to_atlas(img);

        int image_id = font_pack.handle->global_image_index_offset + i;
        font_set_letter_id(FONT_SMALL_PLAIN, img.temp.symdeck, image_id, { img.temp.bearing_x, img.temp.bearing_y });
    }

    // Create textures from atlas data
    for (int i = 0; i < font_pack.handle->atlas_pages.size(); ++i) {
        atlas_data_t &atlas_data = font_pack.handle->atlas_pages.at(i);
        atlas_data.texture = graphics_renderer()->create_texture_from_buffer(atlas_data.temp.pixel_buffer, atlas_data.width, atlas_data.height);
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

    image_packer_reset(font_packer);
}