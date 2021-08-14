#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include "core/encoding.h"
#include "core/image_group.h"
#include "graphics/color.h"

#define IMAGE_FONT_MULTIBYTE_OFFSET 10000
#define IMAGE_FONT_MULTIBYTE_TRAD_CHINESE_MAX_CHARS 2188
#define IMAGE_FONT_MULTIBYTE_SIMP_CHINESE_MAX_CHARS 2130
#define IMAGE_FONT_MULTIBYTE_KOREAN_MAX_CHARS 2350

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
typedef struct {
    int width;
    int height;
    int num_animation_sprites;
    int sprite_offset_x;
    int sprite_offset_y;
    int animation_can_reverse;
    int animation_speed_id;
    int offset_mirror;
    struct {
        int type;
        int is_fully_compressed;
        int is_external;
        int has_compressed_part;
        char bitmap_name[200];
        int bmp_index;
        color_t *data;
        int offset;
        int data_length;
        int uncompressed_length;
    } draw;
} image;

class imagepak {
    bool initialized;
    const char *name;
    int entries_num;
    int groups_num;
    uint32_t header_data[10];
    uint16_t *group_image_ids;
    image *images;
    color_t *data;

    bool check_initialized();

public:
    int id_shift_overall = 0;

    imagepak();

    int load_555(const char *filename_555, const char *filename_sgx, int shift = 0);

    int get_entry_count();
    int get_id(int group);
    const image *get_image(int id, bool relative = false);
};

extern int terrain_ph_offset;

int image_load_main(int climate_id, int is_editor, int force_reload);
int image_load_fonts(encoding_type encoding);
int image_load_enemy(int enemy_id);

int image_id_from_group(int collectiion, int group);

const image *image_get(int id, int mode = 0);
const image *image_letter(int letter_id);
const image *image_get_enemy(int id);
const color_t *image_data(int id);
const color_t *image_data_letter(int letter_id);
const color_t *image_data_enemy(int id);

#endif // CORE_IMAGE_H
