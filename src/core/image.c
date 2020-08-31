#include "image.h"

#include "SDL.h"

#include "core/buffer.h"
#include "core/file.h"
#include "core/io.h"
#include "core/log.h"
#include "core/mods.h"
#include "core/game_environment.h"
#include "core/table_translation.h"

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
    const char C3_MAIN_555[3][NAME_SIZE];
    const char C3_MAIN_SG2[3][NAME_SIZE];
    const char C3_EDITOR_555[3][NAME_SIZE];
    const char C3_EDITOR_SG2[3][NAME_SIZE];
    const char C3_EMPIRE_555[NAME_SIZE];
    const char C3_ENEMY_555[20][NAME_SIZE];
    const char C3_ENEMY_SG2[20][NAME_SIZE];
    const char PH_MAIN_555[NAME_SIZE];
    const char PH_MAIN_SG3[NAME_SIZE];
    const char PH_UNLOADED_555[NAME_SIZE];
    const char PH_UNLOADED_SG3[NAME_SIZE];
    const char PH_TERRAIN_555[NAME_SIZE];
    const char PH_TERRAIN_SG3[NAME_SIZE];
    const char PH_FONTS_555[NAME_SIZE];
    const char PH_FONTS_SG3[NAME_SIZE];
    const char PH_EDITOR_GRAPHICS_555[NAME_SIZE];
    const char PH_EDITOR_GRAPHICS_SG3[NAME_SIZE];
    const char PH_EMPIRE_555[NAME_SIZE];
    const char PH_ENEMY_555[20][NAME_SIZE];
    const char PH_ENEMY_SG2[20][NAME_SIZE];

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
        "data/Pharaoh_General.555",
        "data/Pharaoh_General.sg3",
        "data/Pharaoh_Unloaded.555",
        "data/Pharaoh_Unloaded.sg3",
        "data/Pharaoh_Terrain.555",
        "data/Pharaoh_Terrain.sg3",
        "data/Pharaoh_Fonts.555",
        "data/Pharaoh_Fonts.sg3",
        "",
        "",
        "data/Empire.555",
        {
                "data/Assyrian.555",
                "data/Egyptian.555",
                "data/Canaanite.555",
                "data/Enemy_1.555",
                "data/Hittite.555",
                "data/Hyksos.555",
                "data/Kushite.555",
                "data/Libian.555",
                "data/Mitani.555",
                "data/Nubian.555",
                "data/Persian.555",
                "data/Phoenician.555",
                "data/Roman.555",
                "data/SeaPeople.555"
        },
        {
                "data/Assyrian.sg3",
                "data/Egyptian.sg3",
                "data/Canaanite.sg3",
                "data/Enemy_1.sg3",
                "data/Hittite.sg3",
                "data/Hyksos.sg3",
                "data/Kushite.sg3",
                "data/Libian.sg3",
                "data/Mitani.sg3",
                "data/Nubian.sg3",
                "data/Persian.sg3",
                "data/Phoenician.sg3",
                "data/Roman.sg3",
                "data/SeaPeople.sg3"
        }
};

static const image DUMMY_IMAGE;

static struct {
    int current_climate;
    int is_editor;
    int fonts_enabled;
    int font_base_offset;

    imagepak main;
    imagepak ph_unloaded;
    imagepak ph_terrain;
    imagepak ph_fonts;
    imagepak enemy;
    imagepak empire;
    imagepak font;

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
static const color_t *load_external_data(image *img)
{
    char filename[FILE_NAME_MAX];
    int size = 0;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            strcpy(&filename[0], "555/");
            strcpy(&filename[4], img->draw.bitmap_name);
            file_change_extension(filename, "555");
            size = io_read_file_part_into_buffer(
                    &filename[4], MAY_BE_LOCALIZED, data.tmp_data,
                    img->draw.data_length, img->draw.offset - 1
            );
            break;
        case ENGINE_ENV_PHARAOH:
            strcpy(&filename[0], "Data/");
            strcpy(&filename[5], img->draw.bitmap_name);
            file_change_extension(filename, "555");
            size = io_read_file_part_into_buffer(
                    &filename[5], MAY_BE_LOCALIZED, data.tmp_data,
                    img->draw.data_length, img->draw.offset - 1
            );
            break;
    }
    if (!size) {
        // try in 555 dir
        size = io_read_file_part_into_buffer(
                filename, MAY_BE_LOCALIZED, data.tmp_data,
                img->draw.data_length, img->draw.offset - 1
        );
        if (!size) {
            log_error("unable to load external image", img->draw.bitmap_name, 0);
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

#include "assert.h"

int image_init(void)
{
    data.tmp_data = (uint8_t *) malloc(SCRATCH_DATA_SIZE);
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            break;
        case ENGINE_ENV_PHARAOH:
            break;
    }
    return 1;
}
int image_groupid_translation(int table[], int group)
{
    if (group == 246)
    {
        int a = 2;
    }

    for (int i = 0; table[i] < GROUP_MAX_GROUP; i += 2) {
        if (table[i] == group)
            return table[i + 1];
    }

    // missing entry!!!!
    return group;
}
int image_id_from_group(int group)
{
    switch (GAME_ENV)
    {
        case ENGINE_ENV_C3:
            return data.main.group_image_ids[group];
        case ENGINE_ENV_PHARAOH:
            group = image_groupid_translation(groupid_translation_table_ph, group);
            if (group < 67)
                return data.ph_terrain.group_image_ids[group];
            else if (group < 295)
                return data.main.group_image_ids[group - 66] + 2000;
            else if (group < 333)
                return data.ph_unloaded.group_image_ids[group - 294] + 5000;
            else
                return data.ph_fonts.group_image_ids[group - 332] + 6000;
    }
}
const image *image_get(int id)
{
    switch (GAME_ENV)
    {
        case ENGINE_ENV_C3:
            if (id >= data.main.entries_num && id < data.main.entries_num + MAX_MODDED_IMAGES)
                return mods_get_image(id);
            else if (id >= 0)
                return &data.main.images[id];
            else
                return NULL;
        case ENGINE_ENV_PHARAOH: // todo: mods
            if (id > 6000 && id - 6000 < data.ph_fonts.entries_num)
                return &data.ph_fonts.images[id - 6000];
            else if (id > 5000 && id - 5000 < data.ph_unloaded.entries_num)
                return &data.ph_unloaded.images[id - 5000];
            else if (id > 2000 && id - 2000 < data.main.entries_num)
                return &data.main.images[id - 2000];
            else if (id >= 0 && id < data.ph_terrain.entries_num)
                return &data.ph_terrain.images[id];
            else
                return NULL;
    }

}
const color_t *image_data(int id)
{
    image *img = image_get(id);
    if (img->draw.is_external)
        return load_external_data(img);
    else
        return img->draw.data; // todo: mods
}
const image *image_letter(int letter_id)
{
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT) {
        return &data.font.images[data.font_base_offset + letter_id];
    } else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return &data.font.images[data.font_base_offset + letter_id - IMAGE_FONT_MULTIBYTE_OFFSET];
    } else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        return image_get(image_id_from_group(GROUP_FONT) + letter_id);
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
    return image_letter(letter_id)->draw.data;
}
const color_t *image_data_enemy(int id)
{
    if (data.enemy.images[id].draw.offset > 0) {
        return &data.enemy.data[data.enemy.images[id].draw.offset];
    }
    return NULL;
}

int image_load_555(imagepak *pak, const char *filename_555, const char *filename_sgx)
{
    // prepare sgx data
    if (!io_read_file_into_buffer(filename_sgx, MAY_BE_LOCALIZED, data.tmp_data, SCRATCH_DATA_SIZE)) //int MAIN_INDEX_SIZE = 660680;
        return 0;
    int HEADER_SIZE = 0;
    if (file_has_extension(filename_sgx, "sg2"))
        HEADER_SIZE = 20680;
    else
        HEADER_SIZE = 40680;
    buffer buf;
    buffer_init(&buf, data.tmp_data, HEADER_SIZE);

    // read header
    buffer_read_raw(&buf, pak->header_data, sizeof(uint32_t) * 10);

    // allocate arrays
    int prev_pak_size = pak->entries_num;
    pak->entries_num = (int)pak->header_data[4] + 1;
    pak->name = filename_sgx;
    if (pak->initialized == 0) { // new pak! allocate memory!
        pak->initialized = 1;
        pak->images = (image *)malloc(sizeof(image) * pak->entries_num);
        pak->data = (color_t *)malloc(30000000);
        pak->group_image_ids = malloc(300 * sizeof(uint16_t)); // 300 entries is hardcoded? (total list is always 600 bytes)
    } else if (prev_pak_size != pak->entries_num) { // not new, but different! resize memory!
        realloc(pak->images, sizeof(image) * pak->entries_num);
        realloc(pak->data, 30000000);
    }
    buffer_skip(&buf, 40); // skip remaining 40 bytes

    // parse groups (always a fixed 300 pool)
    int groups_num = 0;
    for (int i = 0; i < 300; i++)
    {
        pak->group_image_ids[i] = buffer_read_u16(&buf);
        if (pak->group_image_ids[i] != 0) {
//            SDL_Log("%s group %i -> id %i", filename_sgx, i, pak->group_image_ids[i]);
            groups_num++;
        }
    }
    pak->groups_num = groups_num;

    // parse bitmap names
    int num_bmp_names = (int)pak->header_data[5];
    char bmp_names[num_bmp_names][200];
    buffer_read_raw(&buf, bmp_names, 200 * num_bmp_names); // every line is 200 chars - 97 entries in the original c3.sg2 header (100 for good measure) and 18 in Pharaoh_General.sg3

    // move on to the rest of the content
    buffer_init(&buf, &data.tmp_data[HEADER_SIZE], ENTRY_SIZE * pak->entries_num);

    // fill in image data
    int bmp_lastbmp = 0;
    int bmp_lastindex = 1;
    for (int i = 0; i < pak->entries_num; i++) {
        image img;
        img.draw.offset = buffer_read_i32(&buf);
        img.draw.data_length = buffer_read_i32(&buf);
        img.draw.uncompressed_length = buffer_read_i32(&buf);
        buffer_skip(&buf, 4);
        img.draw.offset_mirror = buffer_read_i32(&buf); // .sg3 only
        img.width = buffer_read_u16(&buf);
        img.height = buffer_read_u16(&buf);
        buffer_skip(&buf, 6);
        img.num_animation_sprites = buffer_read_u16(&buf);
        buffer_skip(&buf, 2);
        img.sprite_offset_x = buffer_read_i16(&buf);
        img.sprite_offset_y = buffer_read_i16(&buf);
        buffer_skip(&buf, 10);
        img.animation_can_reverse = buffer_read_i8(&buf);
        buffer_skip(&buf, 1);
        img.draw.type = buffer_read_u8(&buf);
        img.draw.is_fully_compressed = buffer_read_i8(&buf);
        img.draw.is_external = buffer_read_i8(&buf);
        img.draw.has_compressed_part = buffer_read_i8(&buf);
        buffer_skip(&buf, 2);
        int bitmap_id = buffer_read_u8(&buf);
        const char *bmn = bmp_names[bitmap_id];
        strncpy(img.draw.bitmap_name, bmn, 200);
        if (bitmap_id != bmp_lastbmp) {// new bitmap name, reset bitmap grouping index
            bmp_lastindex = 1;
            bmp_lastbmp = bitmap_id;
        }
        img.draw.bmp_index = bmp_lastindex;
        bmp_lastindex++;
        buffer_skip(&buf, 1);
        img.animation_speed_id = buffer_read_u8(&buf);
        if (pak->header_data[1] < 214)
            buffer_skip(&buf, 5);
        else
            buffer_skip(&buf, 5+8);
        pak->images[i] = img;
        int f = 1;
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

    // convert bitmap data for image pool
    color_t *dst = pak->data;
    color_t *start_dst = dst;
    dst++; // make sure img->offset > 0
    for (int i = 0; i < pak->entries_num; i++) {
        image *img = &pak->images[i];
        if (img->draw.is_external) {
            continue;
        }
        buffer_set(&buf, img->draw.offset);
        int img_offset = (int) (dst - start_dst);
        if (img->draw.is_fully_compressed) {
            dst += convert_compressed(&buf, img->draw.data_length, dst);
        } else if (img->draw.has_compressed_part) { // isometric tile
            dst += convert_uncompressed(&buf, img->draw.uncompressed_length, dst);
            dst += convert_compressed(&buf, img->draw.data_length - img->draw.uncompressed_length, dst);
        } else {
            dst += convert_uncompressed(&buf, img->draw.data_length, dst);
        }
        img->draw.offset = img_offset;
        img->draw.uncompressed_length /= 2;
        img->draw.data = &pak->data[img_offset];
    }

    return 1;
}
int image_pak_table_generate()
{
    // are you SURE you want to read through this mess?
    // I warn thee, you should stay away for your mental sanity's sake
    static imagepak c3_main;
    static imagepak ph_terr;
    static imagepak ph_main;
    static imagepak ph_unl;
    static imagepak ph_font;
    image_load_555(&c3_main, "DEV_TESTING/C3.555", "DEV_TESTING/C3.sg2");
    image_load_555(&ph_terr, gfc.PH_TERRAIN_555, gfc.PH_TERRAIN_SG3); // 1-2000
    image_load_555(&ph_main, gfc.PH_MAIN_555, gfc.PH_MAIN_SG3); // 2001-5000
    image_load_555(&ph_unl, gfc.PH_UNLOADED_555, gfc.PH_UNLOADED_SG3); // 5001-6000
    image_load_555(&ph_font, gfc.PH_FONTS_555, gfc.PH_FONTS_SG3); // 6001-8000

    FILE *fp = fopen("table_translation.txt", "w+"); // E:/Git/augustus/src/core/table_translation.h
    fprintf(fp, "#ifndef GRAPHICS_TABLE_TRANSLATION_H\n"
                "#define GRAPHICS_TABLE_TRANSLATION_H\n\n"
                "static int groupid_translation_table_ph[] = {\n");

    for (int group = 1; group <= 254; group++) {
        // get image index from c3
        int c3_id = c3_main.group_image_ids[group];

        // get bitmap name
        image c3_img = c3_main.images[c3_id];
        const char *bmp = c3_img.draw.bitmap_name;
        int bmp_index = c3_img.draw.bmp_index;

        // look up bitmap name in other files
        for (int i = 1; i < 7000; i++) {
            image img;
            imagepak *ph_pak;
            int id_offset;
            int group_offset;
            int ph_id;

            if (i > 6000) {
                ph_pak = &ph_font;
                id_offset = 5999;
                group_offset = 332;
            }
            else if (i > 5000) {
                ph_pak = &ph_unl;
                id_offset = 4999;
                group_offset = 294;
            }
            else if (i > 2000) {
                ph_pak = &ph_main;
                id_offset = 1999;
                group_offset = 66;
            }
            else if (i <= ph_terr.entries_num) {
                ph_pak = &ph_terr;
                id_offset = 0;
                group_offset = 0;
            }

            // convert global index into local pak index
            ph_id = i - id_offset;

            if (ph_id > ph_pak->entries_num)
                continue;
            img = ph_pak->images[ph_id];

            if (strcasecmp(bmp, img.draw.bitmap_name) == 0) { // yay, the image has the same bitmap name!

                int gfirst = 1;
                if (bmp_index == img.draw.bmp_index)
                    gfirst = 0;

                // look through the ph imagepak groups and see if one points to the same image
                for (int ph_group = 1; ph_group <= ph_pak->groups_num; ph_group++) {
                    int check_id = ph_pak->group_image_ids[ph_group];
                    if (check_id == ph_id) { // yay, there's a group that points to this image!
                        if (gfirst && ph_group != group)
                            goto nextindex;
//                        if (group != ph_group + group_offset)
                            fprintf(fp, "    %i, %i, // %s %s\n",group, ph_group + group_offset, ph_pak->name, bmp);
                        SDL_Log("[c3] group %i >> img %i (%s : %i) >> [ph] img %i (%i) >> group %i (%i)", group, c3_id-1, bmp, bmp_index, ph_id-1, ph_id-1 + id_offset, ph_group, ph_group + group_offset);
                        goto nextgroup;
                    }
                }
                if (gfirst)
                    goto nextindex;
                // no matching group found....
                SDL_Log("[c3] group %i >> img %i (%s : %i) >> [ph] img %i (%i) >> ????????????", group, c3_id-1, bmp, bmp_index, ph_id-1, ph_id-1 + id_offset);
                goto nextgroup;
            }
            nextindex:
            continue;
        }
        // no matching image found....
//        SDL_Log("[c3] group %i >> img %i (%s : %i) >> ????????????", group, c3_id-1, bmp, bmp_index);
        nextgroup:
        continue;
    }

    fprintf(fp, "};\n\n"
                "#endif // GRAPHICS_TABLE_TRANSLATION_H");
    fclose(fp);
}
int image_load_main(int climate_id, int is_editor, int force_reload)
{
//    image_pak_table_generate();

    if (climate_id == data.current_climate && is_editor == data.is_editor && !force_reload)
        return 1;

    const char *filename_555;
    const char *filename_sgx;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            filename_555 = is_editor ? gfc.C3_EDITOR_555[climate_id] : gfc.C3_MAIN_555[climate_id];
            filename_sgx = is_editor ? gfc.C3_EDITOR_SG2[climate_id] : gfc.C3_MAIN_SG2[climate_id];
            if (!image_load_555(&data.main, filename_555, filename_sgx))
                return 0;
            data.current_climate = climate_id;
            break;
        case ENGINE_ENV_PHARAOH:
            filename_555 = is_editor ? gfc.PH_EDITOR_GRAPHICS_555 : gfc.PH_MAIN_555;
            filename_sgx = is_editor ? gfc.PH_EDITOR_GRAPHICS_SG3 : gfc.PH_MAIN_SG3;
            if (!image_load_555(&data.main, filename_555, filename_sgx))
                return 0;
            if (!image_load_555(&data.ph_unloaded, gfc.PH_UNLOADED_555, gfc.PH_UNLOADED_SG3))
                return 0;
            if (!image_load_555(&data.ph_terrain, gfc.PH_TERRAIN_555, gfc.PH_TERRAIN_SG3))
                return 0;
            if (!image_load_555(&data.ph_fonts, gfc.PH_FONTS_555, gfc.PH_FONTS_SG3))
                return 0;
            break;
    }


    data.is_editor = is_editor;
    return 1;
}
int image_load_enemy(int enemy_id)
{
    const char *filename_555;
    const char *filename_sgx;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            filename_555 = gfc.C3_ENEMY_555[enemy_id];
            filename_sgx = gfc.C3_ENEMY_SG2[enemy_id];
            break;
        case ENGINE_ENV_PHARAOH:
            filename_555 = gfc.PH_ENEMY_555[enemy_id];
            filename_sgx = gfc.PH_ENEMY_SG2[enemy_id];
            break;
    }

    if (!image_load_555(&data.enemy, filename_555, filename_sgx))
        return 0;
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

int get_main_entries_num(void)
{
    return data.main.entries_num;
}