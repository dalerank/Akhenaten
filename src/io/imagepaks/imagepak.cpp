#include <cstring>
#include <cinttypes>
#include "imagepak.h"
#include "core/stopwatch.h"
#include "core/buffer.h"
#include "core/string.h"
#include "io/io.h"
#include "atlas_packer.h"
#include "graphics/font.h"
#include "graphics/boilerplate.h"
#include "io/log.h"
#include "SDL_log.h"
#include "core/struct_types.h"
#include "platform/renderer.h"

///////// IMAGE DATA CONVERSION

static color_t to_32_bit(uint16_t c) {
    return ALPHA_OPAQUE |
           ((c & 0x7c00) << 9) | ((c & 0x7000) << 4) |
           ((c & 0x3e0) << 6) | ((c & 0x380) << 1) |
           ((c & 0x1f) << 3) | ((c & 0x1c) >> 2);
}

static int convert_uncompressed(buffer *buf, const image_t *img) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;

    for (int y = 0; y < img->height; y++) {
        color_t *pixel = &p_atlas->TEMP_PIXEL_BUFFER[(img->atlas.y_offset + y) * p_atlas->width + img->atlas.x_offset];
        for (int x = 0; x < img->width; x++) {
            color_t color = to_32_bit(buf->read_u16());
            pixel[x] = color == COLOR_SG2_TRANSPARENT ? ALPHA_TRANSPARENT : color;
            pixels_count++;
        }
    }
    return pixels_count;
}
static int convert_compressed(buffer *buf, int data_length, const image_t *img) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;
    int atlas_dst = (img->atlas.y_offset * p_atlas->width) + img->atlas.x_offset;
    int y = 0;
    int x = 0;
    while (data_length > 0) {
        int control = buf->read_u8();
        if (control == 255) {
            // next byte = transparent pixels to skip
            int skip = buf->read_u8();
            y += skip / img->width;
            x += skip % img->width;
            if (x >= img->width) {
                y++;
                x -= img->width;
            }
            data_length -= 2;
        } else {
            // control = number of concrete pixels
            for (int i = 0; i < control; i++) {
                int dst = atlas_dst + y * p_atlas->width + x;
                p_atlas->TEMP_PIXEL_BUFFER[dst] = to_32_bit(buf->read_u16());
                x++;
                if (x >= img->width) {
                    y++;
                    x -= img->width;
                }
            }
            data_length -= control * 2 + 1;
        }
    }
    return pixels_count;
}

static const int FOOTPRINT_X_START_PER_HEIGHT[] = {
        28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0,
        0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28
};

static int convert_footprint_tile(buffer *buf, const image_t *img, int x_offset, int y_offset) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;

    for (int y = 0; y < FOOTPRINT_HEIGHT; y++) {
        int x_start = FOOTPRINT_X_START_PER_HEIGHT[y];
        int x_max = FOOTPRINT_WIDTH - x_start;
        for (int x = x_start; x < x_max; x++) {
            int dst_index = (y + y_offset + img->atlas.y_offset) * p_atlas->width + img->atlas.x_offset + x + x_offset;
            if (dst_index >= p_atlas->bmp_size)
                continue;
            p_atlas->TEMP_PIXEL_BUFFER[dst_index] = to_32_bit(buf->read_u16());
        }
    }
    return pixels_count;
}
static int convert_isometric_footprint(buffer *buf, const image_t *img) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;

    int num_tiles = (img->width + 2) / (FOOTPRINT_WIDTH + 2);
    int x_start = (num_tiles - 1) * 30;
    int y_offset;

//    if (graphics_renderer()->isometric_images_are_joined()) {
    y_offset = img->height - 30 * num_tiles;
//    } else {
//        y_offset = img->top_height;
//    }

    for (int i = 0; i < num_tiles; i++) {
        int x = -30 * i + x_start;
        int y = FOOTPRINT_HALF_HEIGHT * i + y_offset;
        for (int j = 0; j <= i; j++) {
            convert_footprint_tile(buf, img, x, y);
            x += 60;
        }
    }
    for (int i = num_tiles - 2; i >= 0; i--) {
        int x = -30 * i + x_start;
        int y = FOOTPRINT_HALF_HEIGHT * (num_tiles * 2 - i - 2) + y_offset;
        for (int j = 0; j <= i; j++) {
            convert_footprint_tile(buf, img, x, y);
            x += 60;
        }
    }
    return pixels_count;
}

static void convert_to_plain_white(const image_t *img) {
    color_t *pixels = img->TEMP_PIXEL_DATA;
    int atlas_width = img->atlas.p_atlas->width;
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if ((pixels[x] & COLOR_CHANNEL_ALPHA) != ALPHA_TRANSPARENT)
                pixels[x] |= 0x00ffffff;
        }
        pixels += atlas_width;
    }
}
static void add_edge_to_letter(const image_t *img) {
    int atlas_width = img->atlas.p_atlas->width;
    int oldsize = img->width * img->height;
    color_t *TEMP_BUFFER = new color_t[oldsize];

    // copy original glyph to the buffer
    color_t *pixels_row = img->TEMP_PIXEL_DATA;
    auto p_buffer_row = TEMP_BUFFER;
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++)
            p_buffer_row[x] = pixels_row[x];
        pixels_row += atlas_width;
        p_buffer_row += img->width;
    }

    // paste back and create edges
    pixels_row = img->TEMP_PIXEL_DATA;
    p_buffer_row = TEMP_BUFFER;
    auto edge_color = COLOR_BLACK;
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if ((p_buffer_row[x] & COLOR_CHANNEL_ALPHA) != ALPHA_TRANSPARENT) {
//                pixels[atlas_width * 0 + x + 0] = COLOR_BLACK;
                pixels_row[atlas_width * 0 + x + 1] = edge_color;
                pixels_row[atlas_width * 0 + x + 2] = edge_color;
                pixels_row[atlas_width * 1 + x + 0] = edge_color;
                pixels_row[atlas_width * 1 + x + 1] = edge_color;
                pixels_row[atlas_width * 1 + x + 2] = edge_color;
                pixels_row[atlas_width * 2 + x + 0] = edge_color;
                pixels_row[atlas_width * 2 + x + 1] = edge_color;
                pixels_row[atlas_width * 2 + x + 2] = edge_color;
            }
        }
        pixels_row += atlas_width;
        p_buffer_row += img->width;
    }

    // paste white glyph in the center
    pixels_row = img->TEMP_PIXEL_DATA;
    p_buffer_row = TEMP_BUFFER;
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if ((p_buffer_row[x] & COLOR_CHANNEL_ALPHA) != ALPHA_TRANSPARENT)
                pixels_row[atlas_width * 1 + x + 1] = COLOR_WHITE;
        }
        pixels_row += atlas_width;
        p_buffer_row += img->width;
    }

    delete TEMP_BUFFER;
}
static int convert_font_glyph_to_bigger_space(buffer *buf, const image_t *img) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;

    for (int y = 0; y < img->height - 2; y++) {
        color_t *pixel = &p_atlas->TEMP_PIXEL_BUFFER[(img->atlas.y_offset + y) * p_atlas->width + img->atlas.x_offset];
        for (int x = 0; x < img->width - 2; x++) {
            color_t color = to_32_bit(buf->read_u16());
            pixel[x] = color == COLOR_SG2_TRANSPARENT ? ALPHA_TRANSPARENT : color;
            pixels_count++;
        }
    }
    return pixels_count;
}
static void create_special_fonts(std::vector<image_t> *images, int start_index) {
    for (int i = font_definition_for(FONT_SMALL_SHADED)->image_offset; i < images->size() - start_index; ++i) {
        const image_t *img = &images->at(i + start_index);
        image_packer_rect *rect = &packer.rects[i + start_index];
        rect->input.width = img->width + 2;
        rect->input.height = img->height + 2;
    }
}
static bool is_font_glyph_in_range(const image_t *img, font_t font_start, font_t font_end) {
    int i = img->sgx_index - 201;
    int starting_offset = font_definition_for(font_start)->image_offset;
    int ending_offset = font_definition_for(font_end)->image_offset;
    if (i >= starting_offset && i < ending_offset)
        return true;
    return false;
}

static buffer *external_image_buf = nullptr;
static buffer *load_external_data(const image_t *img) {
    char filename[MAX_FILE_NAME];
    int size = 0;
    safe_realloc_for_size(&external_image_buf, img->data_length);

    // file path
    strcpy(&filename[0], "Data/");
    strcpy(&filename[5], img->bmp.name);
    file_change_extension(filename, "555");

    // load external file
    size = io_read_file_part_into_buffer(
            &filename[5], MAY_BE_LOCALIZED, external_image_buf,
            img->data_length, img->sgx_data_offset - 1
    );
    if (!size) {
        // try in 555 dir
        size = io_read_file_part_into_buffer(
                filename, MAY_BE_LOCALIZED, external_image_buf,
                img->data_length, img->sgx_data_offset - 1
        );
        if (!size) {
            log_error("unable to load external image", img->bmp.name, 0);
            return nullptr;
        }
    }
    return external_image_buf;
}
static int convert_image_data(buffer *buf, image_t *img, bool convert_fonts) {
    if (img->is_external)
        buf = load_external_data(img);
    if (buf == nullptr)
        return 0;
    img->TEMP_PIXEL_DATA = &img->atlas.p_atlas->TEMP_PIXEL_BUFFER[(img->atlas.y_offset * img->atlas.p_atlas->width) + img->atlas.x_offset];
    if (img->is_fully_compressed) {
        convert_compressed(buf, img->data_length, img);
        if (convert_fonts) { // special font conversions
            if (is_font_glyph_in_range(img, FONT_SMALL_PLAIN, FONT_NORMAL_BLACK_ON_LIGHT))
                convert_to_plain_white(img);
            else if (is_font_glyph_in_range(img, FONT_SMALL_SHADED, FONT_NORMAL_BLACK_ON_DARK)) {
                add_edge_to_letter(img); // TODO: FIX (it crashes)
                img->width += 2;
                img->height += 2;
            }
        }
    } else if (img->top_height) { // isometric tile
        convert_isometric_footprint(buf, img);
        convert_compressed(buf, img->data_length - img->uncompressed_length, img);
    } else if (img->type == IMAGE_TYPE_ISOMETRIC)
        convert_isometric_footprint(buf, img);
    else
        convert_uncompressed(buf, img);

    img->uncompressed_length /= 2;
}

///////// IMAGEPAK

#define MAX_FILE_SCRATCH_SIZE 20000000

static stopwatch WATCH;

imagepak::imagepak(const char *pak_name, int starting_index, bool SYSTEM_SPRITES, bool FONTS) {
//    images = nullptr;
//    image_data = nullptr;
    entries_num = 0;
    group_image_ids = new uint16_t[300];
    SHOULD_LOAD_SYSTEM_SPRITES = SYSTEM_SPRITES;
    SHOULD_CONVERT_FONTS = FONTS;

    if (!load_pak(pak_name, starting_index))
        cleanup_and_destroy();
}
imagepak::~imagepak() {
    cleanup_and_destroy();
}
void imagepak::cleanup_and_destroy() {
    for (int i = 0; i < atlas_pages.size(); ++i) {
        auto atlas_data = atlas_pages.at(i);
        if (atlas_data.TEMP_PIXEL_BUFFER != nullptr)
            delete atlas_data.TEMP_PIXEL_BUFFER;
        atlas_data.TEMP_PIXEL_BUFFER = nullptr;
        if (atlas_data.texture != nullptr)
            SDL_DestroyTexture(atlas_data.texture);
        atlas_data.texture = nullptr;
    }
//    for (int i = 0; i < images_array.size(); ++i) {
//        auto img = images_array.at(i);
//        img.TEMP_PIXEL_DATA = nullptr;
//        img.atlas.p_atlas = nullptr;
//    }
}

buffer *pak_buf = new buffer(MAX_FILE_SCRATCH_SIZE);
bool imagepak::load_pak(const char *pak_name, int starting_index) {

    WATCH.START();

    // construct proper filepaths
    int str_index = 0;
    uint8_t filename_full[MAX_FILE_NAME];

    // add "data/" if loading paks in Pharaoh
    string_copy(string_from_ascii("data/"), filename_full, 6);
    str_index += 5;

    // copy file name over
    strncpy_safe((char *)name, pak_name, MAX_FILE_NAME);
    string_copy((const uint8_t*)pak_name, &filename_full[str_index], string_length((const uint8_t*)pak_name) + 1);
    str_index = string_length(filename_full);

    // split in .555 and .sg3 filename strings
    uint8_t filename_555[MAX_FILE_NAME];
    uint8_t filename_sgx[MAX_FILE_NAME];
    string_copy(filename_full, filename_555, str_index + 1);
    string_copy(filename_full, filename_sgx, str_index + 1);

    // add extension
    string_copy(string_from_ascii(".555"), &filename_555[str_index], 5);
    string_copy(string_from_ascii(".sg3"), &filename_sgx[str_index], 5);

    // *********** PAK_FILE.SGX ************

    // read sgx data into buffer
    safe_realloc_for_size(&pak_buf, MAX_FILE_SCRATCH_SIZE);
    if (!io_read_file_into_buffer((const char*)filename_sgx, MAY_BE_LOCALIZED, pak_buf, MAX_FILE_SCRATCH_SIZE))
        return false;

    // sgx files are always:
    // - 695080
    // - 887080

    // top header data
    int unk00 = pak_buf->read_u32(); // ???
    version = pak_buf->read_u32();
    int unk02 = pak_buf->read_u32();
    int unk03 = pak_buf->read_u32(); // max num of img entries (225 spaces at the end left unused?)
    entries_num = pak_buf->read_u32() + 1; // the first entry (id 0) in the pak is always empty, but necessary for the layout to get mapped properly
    num_bmp_names = pak_buf->read_u32();
    int unk06 = pak_buf->read_u32(); // bmp group names minus 1?
    int unk07 = pak_buf->read_u32(); // sum of unk08 and unk09
    int unk08 = pak_buf->read_u32(); // .555 file size (off by 4 sometimes)
    int unk09 = pak_buf->read_u32(); // size of something???
    // (the last 10 ints in the array are unknown/unused)
    int unk10 = pak_buf->read_u32();
    int unk11 = pak_buf->read_u32();
    int unk12 = pak_buf->read_u32();
    int unk13 = pak_buf->read_u32();
    int unk14 = pak_buf->read_u32();
    int unk15 = pak_buf->read_u32();
    int unk16 = pak_buf->read_u32();
    int unk17 = pak_buf->read_u32();
    int unk18 = pak_buf->read_u32();
    int unk19 = pak_buf->read_u32();

    // adjust global index (depends on the pak)
    global_image_index_offset = starting_index;

    // parse group ids
    groups_num = 0;
    for (int i = 0; i < PAK_GROUPS_MAX; i++) {
        group_image_ids[i] = pak_buf->read_u16();
        if (group_image_ids[i] != 0 || i == 0)
            groups_num++;
    }

    // determine if and when to load SYSTEM.BMP sprites
    bool has_system_bmp = false;
    if (groups_num > 0 && group_image_ids[0] == 0)
        has_system_bmp = true;

    // parse bitmap names
    bmp_names = (char*)malloc(sizeof(char) * (num_bmp_names * PAK_BMP_NAME_SIZE));
    pak_buf->read_raw(bmp_names, num_bmp_names * PAK_BMP_NAME_SIZE);

    // (move buffer to the rest of the data)
    if (file_has_extension((const char*)filename_sgx, "sg2"))
        pak_buf->set_offset(PAK_HEADER_SIZE_BASE + (100 * PAK_BMP_NAME_SIZE)); // sg2 = 20680 bytes
    else
        pak_buf->set_offset(PAK_HEADER_SIZE_BASE + (200 * PAK_BMP_NAME_SIZE)); // sg3 = 40680 bytes

    // prepare atlas packer & renderer
    pixel_coordinate max_texture_sizes = graphics_renderer()->get_max_image_size();
    if (image_packer_init(&packer, entries_num, max_texture_sizes.x, max_texture_sizes.y) != IMAGE_PACKER_OK)
        return false;
    packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
    packer.options.reduce_image_size = 1;
    packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

    // read img data and record atlas rect sizes
    int bmp_last_group_id = 0;
    int last_idx_in_bmp = 1;
    images_array.reserve(entries_num);
    for (int i = 0; i < entries_num; i++) {
        image_t img;
        img.pak_name = name;
        img.sgx_index = i;
        img.sgx_data_offset = pak_buf->read_i32();
        img.data_length = pak_buf->read_i32();
        img.uncompressed_length = pak_buf->read_i32();
        img.unk00 = pak_buf->read_i32();
        img.offset_mirror = pak_buf->read_i32(); // .sg3 only
        // clamp dimensions so that it's not below zero!
        img.width = pak_buf->read_i16(); img.width = img.width < 0 ? 0 : img.width;
        img.height = pak_buf->read_i16(); img.height = img.height < 0 ? 0 : img.height;
        img.unk01 = pak_buf->read_i16();
        img.unk02 = pak_buf->read_i16();
        img.unk03 = pak_buf->read_i16();
        img.animation.num_sprites = pak_buf->read_u16();
        img.animation.unk04 = pak_buf->read_i16();
        img.animation.sprite_x_offset = pak_buf->read_i16();
        img.animation.sprite_y_offset = pak_buf->read_i16();
        img.animation.unk05 = pak_buf->read_i16();
        img.animation.unk06 = pak_buf->read_i16();
        img.animation.unk07 = pak_buf->read_i16();
        img.animation.unk08 = pak_buf->read_i16();
        img.animation.unk09 = pak_buf->read_i16();
        img.animation.can_reverse = pak_buf->read_i8();
        img.animation.unk10 = pak_buf->read_i8();
        img.type = pak_buf->read_u8();
        img.is_fully_compressed = pak_buf->read_i8();
        img.is_external = pak_buf->read_i8();
        img.top_height = pak_buf->read_i8();
        img.unk11 = pak_buf->read_i8();
        img.unk12 = pak_buf->read_i8();
        img.bmp.group_id = pak_buf->read_u8();
        img.bmp.name = &bmp_names[img.bmp.group_id * PAK_BMP_NAME_SIZE];
        if (img.bmp.group_id != bmp_last_group_id) {
            last_idx_in_bmp = 1; // new bitmap name, reset bitmap grouping index
            bmp_last_group_id = img.bmp.group_id;
        }
        img.bmp.entry_index = last_idx_in_bmp;
        last_idx_in_bmp++;
        img.unk13 = pak_buf->read_i8();
        img.animation.speed_id = pak_buf->read_u8();
        img.unk14 = pak_buf->read_i8();
        img.unk15 = pak_buf->read_i8();
        img.unk16 = pak_buf->read_i8();
        img.unk17 = pak_buf->read_i8();
        img.unk18 = pak_buf->read_i8();
        if (version >= 214) {
            img.unk19 = pak_buf->read_i32();
            img.unk20 = pak_buf->read_i32();
        }

        if (has_system_bmp && !SHOULD_LOAD_SYSTEM_SPRITES && i < 201) {
            //continue;
        } else {
            // record atlas rect sizes in the packer
            image_packer_rect *rect = &packer.rects[i];
            rect->input.width = img.width;
            rect->input.height = img.height;
        }
        images_array.push_back(img);
    }

    // create special fonts
    if (SHOULD_CONVERT_FONTS) {
        create_special_fonts(&images_array, 1 + (200 * (!SHOULD_LOAD_SYSTEM_SPRITES)));
    }

    // repack and generate atlas pages
    image_packer_pack(&packer);
    atlas_pages.reserve(packer.result.pages_needed);
    for (int i = 0; i < packer.result.pages_needed; ++i) {
        atlas_data_t atlas_data;
        atlas_data.width = i == packer.result.pages_needed - 1 ? packer.result.last_image_width : max_texture_sizes.x;
        atlas_data.height = i == packer.result.pages_needed - 1 ? packer.result.last_image_height : max_texture_sizes.y;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.TEMP_PIXEL_BUFFER = new color_t[atlas_data.bmp_size];
        atlas_data.texture = nullptr;
        atlas_pages.push_back(atlas_data);
    }

    // *********** PAK_FILE.555 ************

    // read bitmap data into buffer
    safe_realloc_for_size(&pak_buf, MAX_FILE_SCRATCH_SIZE);
    if (!io_read_file_into_buffer((const char*)filename_555, MAY_BE_LOCALIZED, pak_buf, MAX_FILE_SCRATCH_SIZE))
        return false;

    // finish filling in image and atlas information
    for (int i = 0; i < entries_num; i++) {
        image_t *img = &images_array.at(i);
        if (has_system_bmp && !SHOULD_LOAD_SYSTEM_SPRITES && i < 201)
            continue;
        if (img->offset_mirror != 0)
            img->mirrored_img = &images_array.at(i + img->offset_mirror);
        image_packer_rect *rect = &packer.rects[i];
        img->atlas.index = rect->output.image_index;
        atlas_data_t *p_data = &atlas_pages.at(img->atlas.index);
        img->atlas.p_atlas = p_data;
        img->atlas.x_offset = rect->output.x;
        img->atlas.y_offset = rect->output.y;
//        p_data->images.push_back(img);

        // load and convert image bitmap data
        pak_buf->set_offset(img->sgx_data_offset);
        int r = convert_image_data(pak_buf, img, SHOULD_CONVERT_FONTS);
    }

    // create textures from atlas data
    for (int i = 0; i < atlas_pages.size(); ++i) {
        atlas_data_t *atlas_data = &atlas_pages.at(i);
        atlas_data->texture = graphics_renderer()->create_texture_from_buffer(atlas_data->TEMP_PIXEL_BUFFER,
                                                                              atlas_data->width, atlas_data->height);
        if (atlas_data->texture == nullptr)
            return false;

        // delete temp data buffer in the atlas
        delete atlas_data->TEMP_PIXEL_BUFFER;
        atlas_data->TEMP_PIXEL_BUFFER = nullptr;

        // ********* DEBUGGING **********
        if (false) {
            char *lfile = (char *) malloc(200);
            sprintf(lfile, "DEV_TESTING/tex/%s_%i.bmp", name, i); // TODO: make this a global function
            graphics_renderer()->save_texture_to_file(lfile, atlas_data->texture);
            free(lfile);
        }
        // ******************************
    }

    // remove pointers to raw data buffer in the images
    for (int i = 0; i < images_array.size(); ++i) {
        auto img = images_array.at(i);
        img.TEMP_PIXEL_DATA = nullptr;
    }

    image_packer_free(&packer);

    SDL_Log("Loaded imagepak from '%s' ---- %i images, %i groups, %ix%i atlas pages (%i), %" PRIu64 " milliseconds.",
            filename_sgx,
            entries_num,
            groups_num,
            atlas_pages.at(atlas_pages.size() - 1).width,
            atlas_pages.at(atlas_pages.size() - 1).height,
            atlas_pages.size(),
            WATCH.STOP());

    return true;
}

int imagepak::get_entry_count() {
    return entries_num;
}
int imagepak::get_global_image_index(int group) {
    if (group < 0 || group >= groups_num)
        return -1;
    int image_id = group_image_ids[group];
    return image_id + global_image_index_offset;
}
const image_t *imagepak::get_image(int id, bool relative) {
    if (!relative)
        id -= global_image_index_offset;
    if (id < 0 || id >= entries_num)
        return nullptr;
    return &images_array.at(id);
}

