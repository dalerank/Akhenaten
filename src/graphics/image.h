#ifndef GRAPHICS_IMAGE_H
#define GRAPHICS_IMAGE_H

#include "SDL_render.h"
#include "core/encoding.h"
#include "graphics/color.h"

#define IMAGE_FONT_MULTIBYTE_OFFSET 10000
#define IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS 2188
#define IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS 2130
#define IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS 2350

#define IMAGE_ATLAS_BIT_OFFSET 28
#define IMAGE_ATLAS_BIT_MASK 0x0fffffff

enum {
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

//typedef struct image;
struct atlas_data_t {
    SDL_Texture *texture = nullptr;
//    std::vector<image*> images;
    color_t *TEMP_PIXEL_BUFFER = nullptr;
    int bmp_size;
    int width;
    int height;
};

struct image_t {
    char *pak_name;
    struct {
        char *name;
        int group_id;
        int entry_index;
    } bmp;
    int sgx_index;
    int sgx_data_offset;
    int data_length;
    int uncompressed_length;
    int unk00; //
    int offset_mirror;
    image_t *mirrored_img = nullptr;
    //
    int width;
    int height;
    int unk01; //
    int unk02; //
    int unk03; //
    struct {
        int num_sprites;
        int unk04; //
        int sprite_x_offset;
        int sprite_y_offset;
        int unk05; //
        int unk06; //
        int unk07; //
        int unk08; //
        int unk09; //
        bool can_reverse;
        int unk10; //
        int speed_id;
    } animation;
    int type;
    bool is_fully_compressed;
    bool is_external;
    bool has_isometric_top;
    int isometric_box_height;
    int unk11; //
    int unk12; //
    int unk13; //
    // (anim speed id)
    int unk14; //
    int unk15; //
    int unk16; //
    int unk17; //
    int unk18; //

    int unk19; //
    int unk20; //

    struct {
        int index;
        int x_offset;
        int y_offset;
        atlas_data_t *p_atlas = nullptr;
    } atlas;

    color_t *TEMP_PIXEL_DATA = nullptr;

    const int isometric_size() const;
    const int isometric_top_height() const;
    const int isometric_3d_height() const;
};

extern int terrain_ph_offset;

void image_data_init();
bool image_load_paks();
bool image_set_font_pak(encoding_type encoding);
bool image_set_enemy_pak(int enemy_id);
bool image_set_temple_complex_pak(int temple_id);
bool image_set_monument_pak(int monument_id);

int image_id_from_group(int collection, int group, int pak_cache_idx = -1);

const image_t *image_get(int id, int mode = 0);
const image_t *image_letter(int letter_id);
const image_t *image_get_enemy(int id);

#endif // GRAPHICS_IMAGE_H
