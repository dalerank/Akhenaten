#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include <SDL_render.h>
#include <vector>
#include "core/encoding.h"
#include "core/image_group.h"
#include "graphics/color.h"

#define IMAGE_FONT_MULTIBYTE_OFFSET 10000
#define IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS 2188
#define IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS 2130
#define IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS 2350

#define IMAGE_ATLAS_BIT_OFFSET 28
#define IMAGE_ATLAS_BIT_MASK 0x0fffffff

enum {
    IMAGE_TYPE_WITH_TRANSPARENCY = 0,
    IMAGE_TYPE_ISOMETRIC = 30,
    IMAGE_TYPE_MOD = 40
};

/**
 * @file
 * Image functions
 */

/**
 * Image metadata
 */

typedef struct image;

typedef struct {
    SDL_Texture *texture;
    int num_images;
    std::vector<image*> images;
    color_t *raw_buffer;
    int raw_size;
    int width;
    int height;
} atlas_data_t;

struct image {
    int width;
    int height;
    struct {
        int num_sprites;
        int sprite_x_offset;
        int sprite_y_offset;
        bool can_reverse;
        int speed_id;
//        int start_offset;
    } animation;
    struct {
        int bitflags;
        int index;
        int x_offset;
        int y_offset;
        atlas_data_t *p_atlas;
//        int raw_buffer_size;
//        SDL_Texture *texture = nullptr;
    } atlas;

    int offset_mirror;
    struct {
        int type;
        bool is_fully_compressed;
        bool is_external;
        int top_height;
        char *bitmap_name;
        int bmp_index;
        color_t *data;
        int sg3_offset;
        int data_length;
        int uncompressed_length;
    } draw;
};

typedef struct {
    int width;
    int height;
} texture_size_t;

class imagepak {
//    const char *name;
    int entries_num;
    int groups_num;
    uint32_t header_data[10];
    uint16_t *group_image_ids;
    std::vector<image> images_array;
//    image *images;
//    color_t *image_data;

    bool load_pak(const char *filename_partial, int starting_index);

public:
    std::vector<atlas_data_t> atlas_pages;

    int id_shift_overall = 0;

    imagepak(const char *filename_partial, int starting_index);
    ~imagepak();

    int get_entry_count();
    int get_id(int group);
    const image *get_image(int id, bool relative = false);
};

extern int terrain_ph_offset;

void image_data_init();

bool image_load_main_paks(int climate_id, int is_editor, int force_reload);
bool image_set_font_pak(encoding_type encoding);
bool image_set_enemy_pak(int enemy_id);

int image_id_from_group(int collection, int group, int pak_cache_idx = -1);

const image *image_get(int id, int mode = 0);
const image *image_letter(int letter_id);
const image *image_get_enemy(int id);
const color_t *image_data(int id);
const color_t *image_data_letter(int letter_id);
const color_t *image_data_enemy(int id);

#endif // CORE_IMAGE_H
