#include "image.h"

#include "SDL.h"

#include "core/buffer.h"
#include "core/file.h"
#include "core/io.h"
#include "core/log.h"
#include "core/mods.h"
#include "core/config.h"
#include "core/game_environment.h"

#include <stdlib.h>
#include <string.h>

#define ENTRY_SIZE 64
#define NAME_SIZE 32

#define SCRATCH_DATA_SIZE 20000000

enum {
    NO_EXTRA_FONT = 0,
    FULL_CHARSET_IN_FONT = 1,
    MULTIBYTE_IN_FONT = 2
};

static struct {
    int current_climate;
    bool is_editor;
    bool fonts_enabled;
    int font_base_offset;

    std::vector<imagepak**> pak_list;

    imagepak *main;
    imagepak *terrain;
    imagepak *unloaded;
    imagepak *sprmain;
    imagepak *sprambient;

    imagepak *expansion;
    imagepak *sprmain2;

    std::vector<imagepak*> temple_paks;
    std::vector<imagepak*> monument_paks;
    std::vector<imagepak*> enemy_paks;
//    std::vector<imagepak*> font_paks;

    imagepak *temple;
    imagepak *monument;
    imagepak *enemy;
    imagepak *empire;
    imagepak *font;

    color_t *tmp_image_data;
} data;

int terrain_ph_offset = 0;

static color_t to_32_bit(uint16_t c) {
    return ALPHA_OPAQUE |
           ((c & 0x7c00) << 9) | ((c & 0x7000) << 4) |
           ((c & 0x3e0) << 6) | ((c & 0x380) << 1) |
           ((c & 0x1f) << 3) | ((c & 0x1c) >> 2);
}

static int convert_uncompressed(buffer *buf, int amount, color_t *dst) {
    for (int i = 0; i < amount; i += 2) {
        color_t c = to_32_bit(buf->read_u16());
        *dst = c;
        dst++;
    }
    return amount / 2;
}
static int convert_compressed(buffer *buf, int amount, color_t *dst) {
    int dst_length = 0;
    while (amount > 0) {
        int control = buf->read_u8();
        if (control == 255) {
            // next byte = transparent pixels to skip
            *dst++ = 255;
            *dst++ = buf->read_u8();
            dst_length += 2;
            amount -= 2;
        } else {
            // control = number of concrete pixels
            *dst++ = control;
            for (int i = 0; i < control; i++) {
                *dst++ = to_32_bit(buf->read_u16());
            }
            dst_length += control + 1;
            amount -= control * 2 + 1;
        }
    }
    return dst_length;
}
static const color_t *load_external_data(const image *img) {
    char filename[FILE_NAME_MAX];
    int size = 0;
    buffer *buf = new buffer(img->draw.data_length);
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            strcpy(&filename[0], "555/");
            strcpy(&filename[4], img->draw.bitmap_name);
            file_change_extension(filename, "555");
            size = io_read_file_part_into_buffer(
                    &filename[4], MAY_BE_LOCALIZED, buf,
                    img->draw.data_length, img->draw.offset - 1
            );
            break;
        case ENGINE_ENV_PHARAOH:
            strcpy(&filename[0], "Data/");
            strcpy(&filename[5], img->draw.bitmap_name);
            file_change_extension(filename, "555");
            size = io_read_file_part_into_buffer(
                    &filename[5], MAY_BE_LOCALIZED, buf,
                    img->draw.data_length, img->draw.offset - 1
            );
            break;
    }
    if (!size) {
        // try in 555 dir
        size = io_read_file_part_into_buffer(
                filename, MAY_BE_LOCALIZED, buf,
                img->draw.data_length, img->draw.offset - 1
        );
        if (!size) {
            log_error("unable to load external image", img->draw.bitmap_name, 0);
            return NULL;
        }
    }
//    color_t *dst = (color_t *) &data.tmp_data[4000000];

    // NB: isometric images are never external
    if (img->draw.is_fully_compressed)
        convert_compressed(buf, img->draw.data_length, data.tmp_image_data);
    else {
        convert_uncompressed(buf, img->draw.data_length, data.tmp_image_data);
    }
    return data.tmp_image_data;
}

//////////////////////// IMAGEPAK

#include <cassert>
#include <chrono>
#include <cinttypes>
#include "core/string.h"

using milli = std::chrono::milliseconds;

imagepak::imagepak(const char *filename_partial, int starting_index) {
    images = nullptr;
    image_data = nullptr;
    entries_num = 0;
    group_image_ids = new uint16_t[300];

    load_pak(filename_partial, starting_index);
}
imagepak::~imagepak() {
    delete images;
    delete image_data;
}

bool imagepak::load_pak(const char *filename_partial, int starting_index) {

    //////////////////////////////////////////////////////////////////
    auto TIME_START = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    // construct proper filepaths
    int str_index = 0;
    uint8_t filename_full[100];

    // add "data/" if loading paks in Pharaoh
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        string_copy(string_from_ascii("data/"), filename_full, 6);
        str_index += 5;
    }

    // copy file name over
    string_copy((const uint8_t*)filename_partial, &filename_full[str_index], string_length((const uint8_t*)filename_partial) + 1);
    str_index = string_length(filename_full);

    // split in .555 and .sg3 filename strings
    uint8_t filename_555[100];
    uint8_t filename_sgx[100];
    string_copy(filename_full, filename_555, str_index + 1);
    string_copy(filename_full, filename_sgx, str_index + 1);

    // add extension
    string_copy(string_from_ascii(".555"), &filename_555[str_index], 5);
    string_copy(string_from_ascii(".sg3"), &filename_sgx[str_index], 5);

    // prepare sgx data
    buffer *buf = new buffer(SCRATCH_DATA_SIZE);
    if (!io_read_file_into_buffer((const char*)filename_sgx, MAY_BE_LOCALIZED, buf, SCRATCH_DATA_SIZE)) //int MAIN_INDEX_SIZE = 660680;
        return false;
    int HEADER_SIZE = 0;
    if (file_has_extension((const char*)filename_sgx, "sg2"))
        HEADER_SIZE = 20680; // sg2 has 100 bitmap entries
    else
        HEADER_SIZE = 40680; //

    // read header
    buf->read_raw(header_data, sizeof(uint32_t) * 10);

    // allocate arrays
    entries_num = (size_t) header_data[4] + 1;
    name = (const char*)filename_sgx;
    images = new image[entries_num];
    image_data = new color_t[entries_num * 10000];

    buf->skip(40); // skip remaining 40 bytes

    // adjust global index (depends on the pak)
    id_shift_overall = starting_index;

    // parse groups (always a fixed 300 pool)
    groups_num = 0;
    for (int i = 0; i < 300; i++) {
        group_image_ids[i] = buf->read_u16();
        if (group_image_ids[i] != 0 || i == 0)
            groups_num++;
//        SDL_Log("%s group %i -> id %i", filename_sgx, i, group_image_ids[i]);
    }

    // parse bitmap names;
    // every line is 200 chars - 97 entries in the original c3.sg2
    // header (100 for good measure) and 18 in Pharaoh_General.sg3
    int num_bmp_names = (int)header_data[5];
    char bmp_names[num_bmp_names][200];
    buf->read_raw(bmp_names, 200 * num_bmp_names);

    // move on to the rest of the content
    buf->set_offset(HEADER_SIZE);

    //////////////////////////////////////////////////////////////////
    auto TIME_HEADER = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    // fill in image data
    int bmp_lastbmp = 0;
    int bmp_lastindex = 1;
    for (int i = 0; i < entries_num; i++) {
        image img;
        img.draw.offset = buf->read_i32();
        img.draw.data_length = buf->read_i32();
        img.draw.uncompressed_length = buf->read_i32();
        buf->skip(4);
        img.offset_mirror = buf->read_i32(); // .sg3 only
        img.width = buf->read_u16();
        img.height = buf->read_u16();
        buf->skip(6);
        img.num_animation_sprites = buf->read_u16();
        buf->skip(2);
        img.sprite_offset_x = buf->read_i16();
        img.sprite_offset_y = buf->read_i16();
        buf->skip(10);
        img.animation_can_reverse = buf->read_i8();
        buf->skip(1);
        img.draw.type = buf->read_u8();
        img.draw.is_fully_compressed = buf->read_i8();
        img.draw.is_external = buf->read_i8();
        img.draw.has_compressed_part = buf->read_i8();
        buf->skip(2);
        int bitmap_id = buf->read_u8();
        const char *bmn = bmp_names[bitmap_id];
        strncpy(img.draw.bitmap_name, bmn, 200);
        if (bitmap_id != bmp_lastbmp) {// new bitmap name, reset bitmap grouping index
            bmp_lastindex = 1;
            bmp_lastbmp = bitmap_id;
        }
        img.draw.bmp_index = bmp_lastindex;
        bmp_lastindex++;
        buf->skip(1);
        img.animation_speed_id = buf->read_u8();
        if (header_data[1] < 214)
            buf->skip(5);
        else
            buf->skip(5 + 8);
        images[i] = img;
        int f = 1;
    }

    //////////////////////////////////////////////////////////////////
    auto TIME_DATA = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    // fill in bmp offset data
    int offset = 4;
    for (int i = 1; i < entries_num; i++) {
        image *img = &images[i];
        if (img->draw.is_external) {
            if (!img->draw.offset)
                img->draw.offset = 1;
        } else {
            img->draw.offset = offset;
            offset += img->draw.data_length;
        }
    }

    // prepare bitmap data
    buf->clear();
    int data_size = io_read_file_into_buffer((const char*)filename_555, MAY_BE_LOCALIZED, buf, SCRATCH_DATA_SIZE);
    if (!data_size)
        return false;

    // convert bitmap data for image pool
    color_t *start_dst = image_data;
    color_t *dst = image_data;
    dst++; // make sure img->offset > 0
    for (int i = 0; i < entries_num; i++) {
        image *img = &images[i];
        if (img->draw.is_external)
            continue;
        buf->set_offset(img->draw.offset);
        int img_offset = (int) (dst - start_dst);

        if (img->draw.is_fully_compressed)
            dst += convert_compressed(buf, img->draw.data_length, dst);
        else if (img->draw.has_compressed_part) { // isometric tile
            dst += convert_uncompressed(buf, img->draw.uncompressed_length, dst);
            dst += convert_compressed(buf, img->draw.data_length - img->draw.uncompressed_length, dst);
        } else
            dst += convert_uncompressed(buf, img->draw.data_length, dst);

        img->draw.offset = img_offset;
        img->draw.uncompressed_length /= 2;
        img->draw.data = &image_data[img_offset];
//        SDL_Log("Loading... %s : %i", filename_555, i);
    }

    //////////////////////////////////////////////////////////////////
    auto TIME_FINISH = std::chrono::high_resolution_clock::now();
    //////////////////////////////////////////////////////////////////

    SDL_Log("Loading image collection from file '%s' ---- %i images, %i groups, %" PRIu64 " milliseconds.",
            filename_sgx,
            entries_num,
            groups_num,
            std::chrono::duration_cast<milli>(TIME_FINISH - TIME_START));

    return true;
}

int imagepak::get_entry_count() {
    return entries_num;
}
int imagepak::get_id(int group) {
    if (group >= groups_num)
        return -1;
//        group = 0;
    int image_id = group_image_ids[group];
    return image_id + id_shift_overall;
}
const image *imagepak::get_image(int id, bool relative) {
    if (!relative)
        id -= id_shift_overall;
    if (id < 0 || id >= entries_num)
        return nullptr;
    return &images[id];
}

////////////////////////

#include "window/city.h"

static imagepak *pak_from_collection_id(int collection) {
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            return data.main; // only one for Caesar III
        case ENGINE_ENV_PHARAOH:
            switch (collection) {
                case IMAGE_COLLECTION_TERRAIN:
                    return data.terrain;
                case IMAGE_COLLECTION_GENERAL:
                    return data.main;
                case IMAGE_COLLECTION_UNLOADED:
                    return data.unloaded;
                case IMAGE_COLLECTION_EMPIRE:
                    return data.empire;
                case IMAGE_COLLECTION_SPR_MAIN:
                    return data.sprmain;
                case IMAGE_COLLECTION_SPR_AMBIENT:
                    return data.sprambient;
                    /////
                case IMAGE_COLLECTION_ENEMY:
                    return data.enemy;
                case IMAGE_COLLECTION_FONT:
                    return data.font;
                    /////
                case IMAGE_COLLECTION_EXPANSION:
                    return data.expansion;
                case IMAGE_COLLECTION_EXPANSION_SPR:
                    return data.sprmain2;
                    /////
                case IMAGE_COLLECTION_MONUMENT:
                    return data.monument;
            }
            break;
    }
    return nullptr;
}
int image_id_from_group(int collection, int group) {
    imagepak *pak = pak_from_collection_id(collection);
    if (pak == nullptr)
        return -1;
    return pak->get_id(group);
}
const image *image_get(int id, int mode) {
    const image *img;
    for (int i = 0; i < data.pak_list.size(); ++i) {
        imagepak *pak = *(data.pak_list.at(i));
        if (pak == nullptr)
            continue;
        img = (pak)->get_image(id);
        if (img != nullptr)
            return img;
    }
    // default (failure)
    return image_get(image_id_from_group(GROUP_TERRAIN_BLACK));
    return nullptr;
}
const image *image_letter(int letter_id) {
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT)
        return data.font->get_image(data.font_base_offset + letter_id);
    else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET)
        return data.font->get_image(data.font_base_offset + letter_id - IMAGE_FONT_MULTIBYTE_OFFSET);
    else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET)
        return image_get(image_id_from_group(GROUP_FONT) + letter_id);
    else {
        return nullptr;
    }
}
const image *image_get_enemy(int id) {
    return data.enemy->get_image(id);
}
const color_t *image_data(int id) {
    const image *lookup = image_get(id);
    const image *img = image_get(id + lookup->offset_mirror);
    if (img->draw.is_external)
        return load_external_data(img);
    else
        return img->draw.data; // todo: mods
}
const color_t *image_data_letter(int letter_id) {
    return image_letter(letter_id)->draw.data;
}
const color_t *image_data_enemy(int id) {
    const image *lookup = image_get(id);
    const image *img = image_get(id + lookup->offset_mirror);
    id += img->offset_mirror;
    if (img->draw.offset > 0)
        return img->draw.data;
    return NULL;
}

void image_data_init() {
    data.current_climate = -1;
    data.is_editor = false;
    data.fonts_enabled = false;
    data.font_base_offset = 0;

    data.tmp_image_data = new color_t[SCRATCH_DATA_SIZE - 4000000];

    // add paks to parsing list cache
    data.pak_list.push_back(&data.sprmain);
    data.pak_list.push_back(&data.unloaded);
    data.pak_list.push_back(&data.main);
    data.pak_list.push_back(&data.terrain);
    data.pak_list.push_back(&data.temple);
    data.pak_list.push_back(&data.sprambient);
    data.pak_list.push_back(&data.font);
    data.pak_list.push_back(&data.empire);
    data.pak_list.push_back(&data.sprmain2);
    data.pak_list.push_back(&data.expansion);
    data.pak_list.push_back(&data.monument);
}

const char* enemy_file_names_c3[20] = {
        "goths",
        "Etruscan",
        "Etruscan",
        "carthage",
        "Greek",
        "Greek",
        "egyptians",
        "Persians",
        "Phoenician",
        "celts",
        "celts",
        "celts",
        "Gaul",
        "Gaul",
        "goths",
        "goths",
        "goths",
        "Phoenician",
        "North African",
        "Phoenician"
};
const char* enemy_file_names_ph[20] = {
        "Assyrian",
        "Egyptian",
        "Canaanite",
        "Enemy_1",
        "Hittite",
        "Hyksos",
        "Kushite",
        "Libian",
        "Mitani",
        "Nubian",
        "Persian",
        "Phoenician",
        "Roman",
        "SeaPeople",
        "",
        "",
        "",
        "",
        "",
        ""
};

bool image_load_main_paks(int climate_id, int is_editor, int force_reload) {
    if (climate_id == data.current_climate && is_editor == data.is_editor && !force_reload)
        return true;

    const char *filename_555;
    const char *filename_sgx;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
//            filename_555 = is_editor ? gfc.C3_EDITOR_555[climate_id] : gfc.C3_MAIN_555[climate_id];
//            filename_sgx = is_editor ? gfc.C3_EDITOR_SG2[climate_id] : gfc.C3_MAIN_SG2[climate_id];
//            if (!data.main->load_555(filename_555, filename_sgx))
//                return 0;
//            data.current_climate = climate_id;
            break;
        case ENGINE_ENV_PHARAOH:

            // Pharaoh loads every image into a global listed cache; however, some
            // display systems use discordant indexes; The sprites cached in the
            // save files, for examples, appear to start at 700 while the terrain
            // system displays them starting at the immediate index after the first
            // pak has ended (683).
            // Moreover, the monuments, temple complexes, and enemies all make use
            // of a single shared index, which is swapped in "real time" for the
            // correct pak in use by the mission, or even depending on buildings
            // present on the map, like the Temple Complexes.
            // What an absolute mess!

            data.unloaded = new imagepak("Pharaoh_Unloaded", 0);    // 0     --> 682
            data.sprmain = new imagepak("SprMain", 700);                              // 700   --> 11007
            // <--- original enemy pak in here                                                               // 11008 --> 11866
            data.main = new imagepak("Pharaoh_General", 11906 - 200);                 // 11906 --> 11866
            data.terrain = new imagepak("Pharaoh_Terrain", 14452 -200);               // 14252 --> 15767 (+64)
            // <--- original temple complex pak here
            data.sprambient = new imagepak("SprAmbient", 15831);                      // 15831 --> 18765
            data.font = new imagepak("Pharaoh_Fonts", 18765);                         // 18765 --> 20305
            data.empire = new imagepak("Empire", 20305);                              // 20305 --> 20506 (+177)
            data.sprmain2 = new imagepak("SprMain2", 20683);                          // 20683 --> 23035
            data.expansion = new imagepak("Expansion", 23035);                        // 23035 --> 23935 (-200)
            // <--- original pyramid pak in here                                                             // 23735 --> 24163

            // the 5 Temple Complex paks.
            data.temple_paks.push_back(new imagepak("Temple_nile", 15591));
            data.temple_paks.push_back(new imagepak("Temple_ra", 15591));
            data.temple_paks.push_back(new imagepak("Temple_ptah", 15591));
            data.temple_paks.push_back(new imagepak("Temple_seth", 15591));
            data.temple_paks.push_back(new imagepak("Temple_bast", 15591));

            // the various Monument paks.
            data.monument_paks.push_back(new imagepak("Mastaba", 23735));
            data.monument_paks.push_back(new imagepak("Pyramid", 23735));
            data.monument_paks.push_back(new imagepak("bent_pyramid", 23735));

            // the various Enemy paks.
            for (int i = 0; i < 20; ++i) {
                if (enemy_file_names_ph[i] != "")
                    data.enemy_paks.push_back(new imagepak(enemy_file_names_ph[i], 11026));
            }

            // (set the first in the bunch as active initially, just for defaults)
            data.temple = data.temple_paks.at(0);
            data.monument = data.monument_paks.at(0);
            data.enemy = data.enemy_paks.at(0);
            break;
    }

    data.is_editor = is_editor;
    return true;
}

bool image_set_enemy_pak(int enemy_id) {
    data.enemy = data.enemy_paks.at(enemy_id);
//    switch (GAME_ENV) {
//        case ENGINE_ENV_C3:
////            if (!data.enemy->load_pak(enemy_file_names_c3[enemy_id], 0))
////                return false;
//            break;
//        case ENGINE_ENV_PHARAOH:
//            data.enemy = new imagepak(enemy_file_names_ph[enemy_id], 11026);
//            break;
//    }
    return true;
}
bool image_set_font_pak(encoding_type encoding) {
    // TODO?
    if (encoding == ENCODING_CYRILLIC)
        return false;
    else if (encoding == ENCODING_TRADITIONAL_CHINESE)
        return false;
    else if (encoding == ENCODING_SIMPLIFIED_CHINESE)
        return false;
    else if (encoding == ENCODING_KOREAN)
        return false;
    else {
//        free(data.font);
//        free(data.font_data);
//        data.font = 0;
//        data.font_data = 0;
        data.fonts_enabled = NO_EXTRA_FONT;
        return true;
    }
}
