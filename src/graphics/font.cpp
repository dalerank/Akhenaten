#include "font.h"

#include "core/encoding/trad_chinese.h"
#include "image.h"
#include "js/js_game.h"

void ANK_REGISTER_CONFIG_ITERATOR(config_load_external_fonts) {
    font_reload_external_symbols();
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
    const uint16_t code = *(uint16_t *)str;
    auto it = mbmap.find(code);
    return (it != mbmap.end());
}

font_glyph font_letter_id(const font_definition* def, const uint8_t* str, int* num_bytes) {
    auto& data = g_font_data;
    if (*str >= 0x80) {
        *num_bytes = 2;
        const auto &mbmap = data.mbsymbols[def->font];
        const uint16_t code = *(uint16_t *)str;
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

void font_reload_external_symbols() {
    g_config_arch.r_array("external_font_symbols", [] (archive arch) {
        pcstr symbol = arch.r_string("symbol");
        int pack = arch.r_int("pack");
        int id = arch.r_int("id");
        int offset = arch.r_int("offset");
        vec2i bearing = arch.r_vec2i("bearing");
        if (!symbol || !*symbol) {
            return;
        }

        e_font font = arch.r_type<e_font>("font");
        const size_t symbol_len = strlen(symbol);
        uint32_t symdec = 0;
        switch (symbol_len) {
        case 1: // single byte
            symdec = *(uint8_t *)symbol; // skip first byte
            break;
        case 2: // two bytes
            symdec = *(uint16_t *)symbol; // skip first two bytes
            break;
        case 4:
            symdec = *(uint32_t *)symbol;
        default:
            break;
        }

        int image_id = image_id_from_group(pack, id) + offset;
        font_set_letter_id(font, symdec, image_id, bearing);
    });
}

const font_mbsybols_t &font_get_symbols() {
    return g_font_data.mbsymbols;
}
