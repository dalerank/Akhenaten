#include "image.h"

#include "core/buffer.h"
#include "core/file.h"
#include "core/io.h"
#include "core/log.h"
#include "core/mods.h"
#include "core/game_environment.h"

#include <stdlib.h>
#include <string.h>

#define ENTRY_SIZE 64
#define NAME_SIZE 32

#define SCRATCH_DATA_SIZE 12100000

enum {
    NO_EXTRA_FONT = 0,
    FULL_CHARSET_IN_FONT = 1,
    MULTIBYTE_IN_FONT = 2
};

typedef struct font_files_collection {
    const char CYRILLIC_FONTS_555[NAME_SIZE];
    const char CYRILLIC_FONTS_SG2[NAME_SIZE];
    const char TRAD_CHINESE_FONTS_555[NAME_SIZE];
    const char KOREAN_FONTS_555[NAME_SIZE];
} font_files_collection;
font_files_collection ffcs[] = {
        {
                "C3_fonts.sg2",
                "C3_fonts.555",
                "rome.555",
                "korean.555",
        },
        {
                "",
                "",
                "",
                ""
        }
};

struct graphics_files_collection {
    const char C3_MAIN_GRAPHICS_555[3][NAME_SIZE];
    const char C3_MAIN_GRAPHICS_SG2[3][NAME_SIZE];
    const char C3_EDITOR_GRAPHICS_555[3][NAME_SIZE];
    const char C3_EDITOR_GRAPHICS_SG2[3][NAME_SIZE];
    const char C3_EMPIRE_555[NAME_SIZE];
    const char C3_ENEMY_GRAPHICS_555[20][NAME_SIZE];
    const char C3_ENEMY_GRAPHICS_SG2[20][NAME_SIZE];
    const char PH_MAIN_GRAPHICS_555[NAME_SIZE];
    const char PH_MAIN_GRAPHICS_SG3[NAME_SIZE];
    const char PH_EDITOR_GRAPHICS_555[NAME_SIZE];
    const char PH_EDITOR_GRAPHICS_SG3[NAME_SIZE];
    const char PH_EMPIRE_555[NAME_SIZE];

} gfc = {
        {
                "c3.555",
                "c3_north.555",
                "c3_south.555"
        },
        {
                "c3.sg2",
                "c3_north.sg2",
                "c3_south.sg2"
        },
        {
                "c3map.555",
                "c3map_north.555",
                "c3map_south.555"
        },
        {
                "c3map.sg2",
                "c3map_north.sg2",
                "c3map_south.sg2"
        },
        "The_empire.555",
        {
                "goths.555",
                "Etruscan.555",
                "Etruscan.555",
                "carthage.555",
                "Greek.555",
                "Greek.555",
                "egyptians.555",
                "Persians.555",
                "Phoenician.555",
                "celts.555",
                "celts.555",
                "celts.555",
                "Gaul.555",
                "Gaul.555",
                "goths.555",
                "goths.555",
                "goths.555",
                "Phoenician.555",
                "North African.555",
                "Phoenician.555",
        },
        {
                "goths.sg2",
                "Etruscan.sg2",
                "Etruscan.sg2",
                "carthage.sg2",
                "Greek.sg2",
                "Greek.sg2",
                "egyptians.sg2",
                "Persians.sg2",
                "Phoenician.sg2",
                "celts.sg2",
                "celts.sg2",
                "celts.sg2",
                "Gaul.sg2",
                "Gaul.sg2",
                "goths.sg2",
                "goths.sg2",
                "goths.sg2",
                "Phoenician.sg2",
                "North African.sg2",
                "Phoenician.sg2",
        },
        "data//Pharaoh_General.555",
        "data//Pharaoh_General.sg3",
        "",
        "",
        "data//Empire.555"
};

static const image DUMMY_IMAGE;

static struct {
    int current_climate;
    int is_editor;
    int fonts_enabled;
    int font_base_offset;

//    int main_entries_num;
//    int enemy_entries_num;

    imagepak main;
    imagepak ph_unloaded;
    imagepak ph_terrain;
    imagepak enemy;
    imagepak empire;
    imagepak font;


//    uint16_t *group_image_ids;
//    char bmp_names[100][200];
//    image main[10000];
//    image enemy[1000];
//    image *font;
//    color_t *main_data;
//    color_t *enemy_data;
//    color_t *empire_bmp;
//    color_t *font_data;

    uint8_t *tmp_data;
} data = {
        .current_climate = -1,
        .main = {0},
        .enemy = {0},
        .empire = {0},
        .font = {0},
        .ph_unloaded = {0},
        .ph_terrain = {0}
};

static color_t to_32_bit(uint16_t c)
{
    return ALPHA_OPAQUE |
           ((c & 0x7c00) << 9) | ((c & 0x7000) << 4) |
           ((c & 0x3e0) << 6)  | ((c & 0x380) << 1) |
           ((c & 0x1f) << 3)   | ((c & 0x1c) >> 2);
}

//static void image_build_from_sgx_index(buffer *buf, image *images, int size, char bmp_names[][200])
//{
//    for (int i = 0; i < size; i++) {
//        // fill in
//        images[i].draw.offset = buffer_read_i32(buf);
//        images[i].draw.data_length = buffer_read_i32(buf);
//        images[i].draw.uncompressed_length = buffer_read_i32(buf);
//        buffer_skip(buf, 8);
//        images[i].width = buffer_read_u16(buf);
//        images[i].height = buffer_read_u16(buf);
//        buffer_skip(buf, 6);
//        images[i].num_animation_sprites = buffer_read_u16(buf);
//        buffer_skip(buf, 2);
//        images[i].sprite_offset_x = buffer_read_i16(buf);
//        images[i].sprite_offset_y = buffer_read_i16(buf);
//        buffer_skip(buf, 10);
//        images[i].animation_can_reverse = buffer_read_i8(buf);
//        buffer_skip(buf, 1);
//        images[i].draw.type = buffer_read_u8(buf);
//        images[i].draw.is_fully_compressed = buffer_read_i8(buf);
//        images[i].draw.is_external = buffer_read_i8(buf);
//        images[i].draw.has_compressed_part = buffer_read_i8(buf);
//        buffer_skip(buf, 2);
////    images[i].draw.bitmap_id = buffer_read_u8(buf);
//        int bitmap_id = buffer_read_u8(buf);
//        if (bmp_names)
//            strncpy(images[i].draw.bitmap_name, bmp_names[bitmap_id], 200);
//        buffer_skip(buf, 1);
//        images[i].animation_speed_id = buffer_read_u8(buf);
//        buffer_skip(buf, 5);
//    }
//
//    // prepare_index
//    int offset = 4;
//    for (int i = 1; i < size; i++) {
//        image *img = &images[i];
//        if (img->draw.is_external) {
//            if (!img->draw.offset) {
//                img->draw.offset = 1;
//            }
//        } else {
//            img->draw.offset = offset;
//            offset += img->draw.data_length;
//        }
//    }
//}

static int convert_uncompressed(buffer *buf, int buf_length, color_t *dst)
{
    for (int i = 0; i < buf_length; i += 2) {
        *dst = to_32_bit(buffer_read_u16(buf));
        dst++;
    }
    return buf_length / 2;
}
static int convert_compressed(buffer *buf, int buf_length, color_t *dst)
{
    int dst_length = 0;
    while (buf_length > 0) {
        int control = buffer_read_u8(buf);
        if (control == 255) {
            // next byte = transparent pixels to skip
            *dst++ = 255;
            *dst++ = buffer_read_u8(buf);
            dst_length += 2;
            buf_length -= 2;
        } else {
            // control = number of concrete pixels
            *dst++ = control;
            for (int i = 0; i < control; i++) {
                *dst++ = to_32_bit(buffer_read_u16(buf));
            }
            dst_length += control + 1;
            buf_length -= control * 2 + 1;
        }
    }
    return dst_length;
}
static void convert_images(image *images, int size, buffer *buf, color_t *dst)
{
    color_t *start_dst = dst;
    dst++; // make sure img->offset > 0
    for (int i = 0; i < size; i++) {
        image *img = &images[i];
        if (img->draw.is_external) {
            continue;
        }
        buffer_set(buf, img->draw.offset);
        int img_offset = (int) (dst - start_dst);
        if (img->draw.is_fully_compressed) {
            dst += convert_compressed(buf, img->draw.data_length, dst);
        } else if (img->draw.has_compressed_part) { // isometric tile
            dst += convert_uncompressed(buf, img->draw.uncompressed_length, dst);
            dst += convert_compressed(buf, img->draw.data_length - img->draw.uncompressed_length, dst);
        } else {
            dst += convert_uncompressed(buf, img->draw.data_length, dst);
        }
        img->draw.offset = img_offset;
        img->draw.uncompressed_length /= 2;
    }
}

//static void load_empire(void)
//{
//    int size = 0;
//    switch (GAME_ENV) {
//        case ENGINE_ENV_C3:
//            size = io_read_file_into_buffer(gfc.C3_EMPIRE_555, MAY_BE_LOCALIZED, data.tmp_data, 8000000);
//            if (size != 4000000) {
//                log_error("unable to load empire data", gfc.C3_EMPIRE_555, 0);
//                return;
//            }
//            break;
//
//        case ENGINE_ENV_PHARAOH:
//            size = io_read_file_into_buffer(gfc.PH_EMPIRE_555, MAY_BE_LOCALIZED, data.tmp_data, 7758436);
//            if (size != 3879218) {
//                log_error("unable to load empire data", gfc.PH_EMPIRE_555, 0);
//                return;
//            }
//            break;
//    }
//    buffer buf;
//    buffer_init(&buf, data.tmp_data, size);
//    convert_uncompressed(&buf, size, data.empire_bmp);
//}

//#define MAIN_INDEX_SIZE 660680

static const color_t *load_external_data(int image_id)
{
    // load up
    image *img = &data.main.images[image_id];
    char filename[FILE_NAME_MAX] = "555/";
    strcpy(&filename[4], img->draw.bitmap_name);
    file_change_extension(filename, "555");
    int size = io_read_file_part_into_buffer(
            &filename[4], MAY_BE_LOCALIZED, data.tmp_data,
            img->draw.data_length, img->draw.offset - 1
    );
    if (!size) {
        // try in 555 dir
        size = io_read_file_part_into_buffer(
                filename, MAY_BE_LOCALIZED, data.tmp_data,
                img->draw.data_length, img->draw.offset - 1
        );
        if (!size) {
            log_error("unable to load external image", img->draw.bitmap_name, image_id);
            return NULL;
        }
    }
    buffer buf;
    buffer_init(&buf, data.tmp_data, size);
    color_t *dst = (color_t*) &data.tmp_data[4000000];
    // NB: isometric images are never external
    if (img->draw.is_fully_compressed) {
        convert_compressed(&buf, img->draw.data_length, dst);
    } else {
        convert_uncompressed(&buf, img->draw.data_length, dst);
    }
    return dst;
}

int image_init(void)
{
    data.tmp_data = (uint8_t *) malloc(SCRATCH_DATA_SIZE);
//    data.main = {0};
//    data.enemy = {0};
//    data.empire = {0};
//    data.font = {0};
//    data.ph_unloaded = {0};
//    data.ph_terrain = {0};
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
//            data.enemy_data = (color_t *) malloc(2400000);
//            data.main_entries_num = 10000;
//            data.enemy_entries_num = 801;
//            data.main_data = (color_t *) malloc(30000000);
//            data.empire_bmp = (color_t *) malloc(8000000);
            break;
        case ENGINE_ENV_PHARAOH:
//            data.enemy_data = (color_t *) malloc(2400000);
//            data.main_entries_num = 10000;
//            data.enemy_entries_num = 801;
//            data.main_data = (color_t *) malloc(30000000);
//            data.empire_bmp = (color_t *) malloc(7758436);
            break;
    }

//    if (!data.main_data || !data.enemy_data || !data.tmp_data) { // || !data.empire_bmp
//        free(data.main_data);
////        free(data.empire_bmp);
//        free(data.enemy_data);
//        free(data.tmp_data);
//        return 0;
//    }
    return 1;
}
int image_id_from_group(int group)
{
    if (group < data.main.entries_num)
        return data.main.group_image_ids[group];
    else {
        return 0; // todo: pharaoh indexing
    }
}
const image *image_get(int id)
{
    if (id >= 0 && id < data.main.entries_num) { // MAIN_ENTRIES
        return &data.main.images[id]; // todo: pharaoh indexing
    } else if (id >= data.main.entries_num && id < data.main.entries_num + MAX_MODDED_IMAGES) {
        return mods_get_image(id);
    } else {
        return NULL;
    }
}
const color_t *image_data(int id)
{
    if (id < 0 || id >= data.main.entries_num) { // outside normal range, check for modded image
        if (id < data.main.entries_num + MAX_MODDED_IMAGES) { // todo: pharaoh indexing
            return mods_get_image_data(id);
        }
        return NULL;
    }
    if (!data.main.images[id].draw.is_external) {
        return &data.main.data[data.main.images[id].draw.offset];
//    } else if (id == image_id_from_group(GROUP_EMPIRE_MAP)) {
//        return data.empire_bmp;
    } else {
        return load_external_data(id);
    }
}
const image *image_letter(int letter_id)
{
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT) {
        return &data.font.images[data.font_base_offset + letter_id];
    } else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return &data.font.images[data.font_base_offset + letter_id - IMAGE_FONT_MULTIBYTE_OFFSET];
    } else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        return &data.main.images[image_id_from_group(GROUP_FONT) + letter_id];
    } else {
        return &DUMMY_IMAGE;
    }
}
const image *image_get_enemy(int id)
{
    if (id >= 0 && id < &data.enemy.entries_num) {
        return &data.enemy.images[id];
    } else {
        return NULL;
    }
}
const color_t *image_data_letter(int letter_id)
{
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT) {
        return &data.font.data[image_letter(letter_id)->draw.offset];
    } else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return &data.font.data[image_letter(letter_id)->draw.offset];
    } else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        return &data.main.data[image_letter(letter_id)->draw.offset];
    } else {
        return NULL;
    }
}
const color_t *image_data_enemy(int id)
{
    if (data.enemy.images[id].draw.offset > 0) {
        return &data.enemy.data[data.enemy.images[id].draw.offset];
    }
    return NULL;
}

//#define HEADER_SIZE 20680

int image_load_555(imagepak *pak, const char *filename_555, const char *filename_sgx)
{
    // prepare sgx data
    // int ENEMY_INDEX_SIZE = 51264 //// 64 * 801;
    if (!io_read_file_into_buffer(filename_sgx, MAY_BE_LOCALIZED, data.tmp_data, SCRATCH_DATA_SIZE)) //int MAIN_INDEX_SIZE = 660680;
        return 0;
    int HEADER_SIZE = 20680;
    buffer buf;
    buffer_init(&buf, data.tmp_data, HEADER_SIZE);

    // read header
    uint32_t header_data[10];
    buffer_read_raw(&buf, header_data, sizeof(uint32_t) * 10);

    // allocate arrays
    int prev_pak_size = pak->entries_num;
    pak->entries_num = (int)header_data[3];
    if (prev_pak_size == 0) { // new pak! allocate memory!
        pak->images = (image *)malloc(sizeof(image) * pak->entries_num);
        pak->data = (color_t *)malloc(30000000);
        pak->group_image_ids = malloc(300 * sizeof(uint16_t)); // 300 entries is hardcoded? (total list is always 600 bytes)
    } else if (prev_pak_size != pak->entries_num) { // not new, but different! resize memory!
        realloc(pak->images, sizeof(image) * pak->entries_num);
        realloc(pak->data, 30000000);
    }

    buffer_skip(&buf, 40); // skip remaining 40 bytes
    for (int i = 0; i < 300; i++) // go over every "group" and load in the corresponding image index from the file
        pak->group_image_ids[i] = buffer_read_u16(&buf);

    int num_bmp_names = (int)header_data[5];
    char bmp_names[num_bmp_names][200];
    buffer_read_raw(&buf, bmp_names, 200 * num_bmp_names); // every line is 200 chars - 97 entries in the original c3.sg2 header (100 for good measure) and 18 in Pharaoh_General.sg3

    // move on to the rest of the content
    buffer_init(&buf, &data.tmp_data[HEADER_SIZE], ENTRY_SIZE * pak->entries_num);

    // fill in image data
    for (int i = 0; i < pak->entries_num; i++) {
        pak->images[i].draw.offset = buffer_read_i32(&buf);
        pak->images[i].draw.data_length = buffer_read_i32(&buf);
        pak->images[i].draw.uncompressed_length = buffer_read_i32(&buf);
        buffer_skip(&buf, 8);
        pak->images[i].width = buffer_read_u16(&buf);
        pak->images[i].height = buffer_read_u16(&buf);
        buffer_skip(&buf, 6);
        pak->images[i].num_animation_sprites = buffer_read_u16(&buf);
        buffer_skip(&buf, 2);
        pak->images[i].sprite_offset_x = buffer_read_i16(&buf);
        pak->images[i].sprite_offset_y = buffer_read_i16(&buf);
        buffer_skip(&buf, 10);
        pak->images[i].animation_can_reverse = buffer_read_i8(&buf);
        buffer_skip(&buf, 1);
        pak->images[i].draw.type = buffer_read_u8(&buf);
        pak->images[i].draw.is_fully_compressed = buffer_read_i8(&buf);
        pak->images[i].draw.is_external = buffer_read_i8(&buf);
        pak->images[i].draw.has_compressed_part = buffer_read_i8(&buf);
        buffer_skip(&buf, 2);
        int bitmap_id = buffer_read_u8(&buf);
        if (bmp_names)
            strncpy(pak->images[i].draw.bitmap_name, bmp_names[bitmap_id], 200);
        buffer_skip(&buf, 1);
        pak->images[i].animation_speed_id = buffer_read_u8(&buf);
        buffer_skip(&buf, 5);
    }

    // fill in bmp offset data
    int offset = 4;
    for (int i = 1; i < pak->entries_num; i++) {
        image *img = &pak->images[i];
        if (img->draw.is_external) {
            if (!img->draw.offset) {
                img->draw.offset = 1;
            }
        } else {
            img->draw.offset = offset;
            offset += img->draw.data_length;
        }
    }

    // prepare bitmap data
    int data_size = io_read_file_into_buffer(filename_555, MAY_BE_LOCALIZED, data.tmp_data, SCRATCH_DATA_SIZE);
    if (!data_size)
        return 0;
    buffer_init(&buf, data.tmp_data, data_size);
    convert_images(pak->images, pak->entries_num, &buf, pak->data);

    return 1;
}
int image_load_main(int climate_id, int is_editor, int force_reload)
{
    if (climate_id == data.current_climate && is_editor == data.is_editor && !force_reload)
        return 1;

    // get correct filename depending on game environment and read into tmp_data buffer
    const char *filename_555;
    const char *filename_sgx;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            filename_555 = is_editor ? gfc.C3_EDITOR_GRAPHICS_555[climate_id] : gfc.C3_MAIN_GRAPHICS_555[climate_id];
            filename_sgx = is_editor ? gfc.C3_EDITOR_GRAPHICS_SG2[climate_id] : gfc.C3_MAIN_GRAPHICS_SG2[climate_id];
            break;
        case ENGINE_ENV_PHARAOH:
            filename_555 = is_editor ? gfc.PH_EDITOR_GRAPHICS_555 : gfc.PH_MAIN_GRAPHICS_555;
            filename_sgx = is_editor ? gfc.PH_EDITOR_GRAPHICS_SG3 : gfc.PH_MAIN_GRAPHICS_SG3;
            break;
    }

    image_load_555(&data.main, filename_555, filename_sgx);

    data.current_climate = climate_id;
    data.is_editor = is_editor;

    return 1;
}
int image_load_fonts(encoding_type encoding)
{
    if (encoding == ENCODING_CYRILLIC) {
        return 0;
    } else if (encoding == ENCODING_TRADITIONAL_CHINESE) {
        return 0;
    } else if (encoding == ENCODING_SIMPLIFIED_CHINESE) {
        return 0;
    } else if (encoding == ENCODING_KOREAN) {
        return 0;
    } else {
//        free(data.font);
//        free(data.font_data);
//        data.font = 0;
//        data.font_data = 0;
        data.fonts_enabled = NO_EXTRA_FONT;
        return 1;
    }
}
int image_load_enemy(int enemy_id)
{
    const char *filename_555;
    const char *filename_sgx;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            filename_555 = gfc.C3_ENEMY_GRAPHICS_555[enemy_id];
            filename_sgx = gfc.C3_ENEMY_GRAPHICS_SG2[enemy_id];
            break;
    }

//    int ENEMY_INDEX_SIZE = ENTRY_SIZE * 801;
//    if (io_read_file_part_into_buffer(filename_idx, MAY_BE_LOCALIZED, data.tmp_data, ENEMY_INDEX_SIZE, 20680) != ENEMY_INDEX_SIZE)
//        return 0;
//
//    buffer buf;
//    buffer_init(&buf, data.tmp_data, ENEMY_INDEX_SIZE);
//    image_build_from_sgx_index(&buf, data.enemy, 801, 0);
//
//    int data_size = io_read_file_into_buffer(filename_bmp, MAY_BE_LOCALIZED, data.tmp_data, SCRATCH_DATA_SIZE);
//    if (!data_size) {
//        return 0;
//    }
//    buffer_init(&buf, data.tmp_data, data_size);
//    convert_images(data.enemy, 801, &buf, data.enemy_data);

    image_load_555(&data.enemy, filename_555, filename_sgx);

    return 1;
}

int get_main_entries_num(void)
{
    return data.main.entries_num;
}