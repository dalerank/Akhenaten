#pragma once

#include "SDL_render.h"
#include "core/encoding.h"
#include "core/xstring.h"
#include "core/vec2i.h"
#include "graphics/color.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"

#define IMAGE_FONT_MULTIBYTE_OFFSET 10000
#define IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS 2188
#define IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS 2130
#define IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS 2350

#define IMAGE_ATLAS_BIT_OFFSET 28
#define IMAGE_ATLAS_BIT_MASK 0x0fffffff

enum e_image_type {
    IMAGE_TYPE_WITH_TRANSPARENCY = 0,
    IMAGE_TYPE_FULLY_OPAQUE = 1,
    IMAGE_TYPE_16x16 = 10,
    IMAGE_TYPE_24x24 = 12,
    IMAGE_TYPE_32x32 = 13, // only used in system.bmp
    IMAGE_TYPE_PLAIN_FONT = 20,
    IMAGE_TYPE_ISOMETRIC = 30,
    IMAGE_TYPE_MOD = 40
};

#define TILE_WIDTH_PIXELS 60
#define TILE_HEIGHT_PIXELS 30
#define HALF_TILE_WIDTH_PIXELS 30
#define HALF_TILE_HEIGHT_PIXELS 15

// typedef struct image;
struct atlas_data_t {
    SDL_Texture* texture = nullptr;
    struct {
        color *pixel_buffer = nullptr;
    } temp;

    int bmp_size;
    int width;
    int height;
};

struct image_t {
    xstring pak_name;
    struct {
        xstring name;
        uint8_t group_id;
        int entry_index;
    } bmp;
    int sgx_index;
    int rect_index;
    int sgx_data_offset;
    int data_length;
    int uncompressed_length;
    int unk00; //
    int offset_mirror = 0;
    int start_index;
    image_t* mirrored_img = nullptr;
    image_t* isometric_top = nullptr;
    image_t *isometric_base = nullptr;
    bool is_isometric_foot = false;
    bool is_isometric_top = false;
    //
    short width;
    short height;
    short unk01; //
    short unk02; //
    short unk03; //
    struct {
        uint16_t num_sprites;
        int16_t unk04; //
        vec2i sprite_offset;
        int16_t unk05; //
        int16_t unk06; //
        int16_t unk07; //
        int16_t unk08; //
        int16_t unk09; //
        bool can_reverse;
        int8_t unk10; //
        uint8_t speed_id;
    } animation;
    uint8_t type;
    bool is_fully_compressed;
    bool is_external;
    bool has_isometric_top;
    int isometric_box_height;
    int8_t unk11; //
    int8_t unk12; //
    int8_t unk13; //
    // (anim speed id)
    int8_t unk14; //
    int8_t unk15; //
    int8_t unk16; //
    int8_t unk17; //
    int8_t unk18; //

    int unk19; //
    int unk20; //

    struct {
        int index;
        vec2i offset;
        atlas_data_t* p_atlas = nullptr;
    } atlas;

    struct {
        uint8_t animate = 0;
        uint8_t max_frame = 0;
        uint8_t frame_tick = 0;
        uint16_t frame = 0;
    } debug;

    struct {
        color* pixel_data;
        void* surface;
        uint32_t symdeck;
        int8_t bearing_x;
        int8_t bearing_y;
    } temp;

    inline vec2i size() const { return {width, height}; }
    const int isometric_size() const;
    const int isometric_top_height() const;
    const int isometric_3d_height() const;
};

extern int terrain_ph_offset;

bool image_data_fonts_ready();
bool image_data_render_on_new_loadpacks();
bool image_load_paks();

int image_id_resource_icon(int resource);
int image_group(image_desc desc);
int image_id_from_group(int collection, int group);

const image_t* image_get(int id);
const image_t *image_get(int pak, int id, int offset = 0);
const image_t *image_get(image_desc desc);

const image_t* image_letter(int letter_id);
const image_t* image_get_enemy(int type, int id);
const image_t *image_next_close_get(image_desc desc, bool &last, int &last_index);

int image_copy_to_atlas(const image_t &img);

inline color image_to_32_bit(uint16_t c) {
    return ALPHA_OPAQUE | ((c & 0x7c00) << 9) | ((c & 0x7000) << 4) | ((c & 0x3e0) << 6) | ((c & 0x380) << 1) | ((c & 0x1f) << 3) | ((c & 0x1c) >> 2);
}

inline color image_to_argb(uint32_t c) {
    return (((c >> 24) & 0xff) << 24) | (((c & 0xff) << 16) | (((c >> 8) & 0xff) << 8) | ((c >> 16) & 0xff));
}
