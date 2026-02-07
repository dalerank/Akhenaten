#include "imagepak.h"
#include "atlas_packer.h"
#include "core/buffer.h"
#include "core/string.h"
#include "core/vec2i.h"
#include "core/log.h"
#include "core/custom_span.hpp"
#include "core/profiler.h"
#include "graphics/font.h"
#include "io/io.h"
#include "platform/renderer.h"
#include "platform/platform.h"
#include "platform/arguments.h"
#include "graphics/text.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "content/zipreader.hpp"

#include "game/game.h"

#include "js/js_game.h"
#include "js/js.h"

#include <array>
#include <unordered_set>
#include <cinttypes>
#include <cstring>

SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src);
image_packer packer;

uint16_t imagepak::max_seen_imgid = 0;
uint16_t imagepak::max_seen_useridx = 0;

static int convert_uncompressed(buffer* buf, const image_t &img) {
    int pixels_count = 0;
    atlas_data_t *p_atlas = img.atlas.p_atlas;

    for (int y = 0; y < img.height; y++) {
        color* pixel = &p_atlas->temp.pixel_buffer[(img.atlas.offset.y + y) * p_atlas->width + img.atlas.offset.x];
        for (int x = 0; x < img.width; x++) {
            color color = image_to_32_bit(buf->read_u16());
            pixel[x] = color == COLOR_SG2_TRANSPARENT ? ALPHA_TRANSPARENT : color;
            pixels_count++;
        }
    }
    return pixels_count;
}

static int convert_compressed(buffer* buf, int data_length, const image_t &img) {
    // int pixels_count = 0;
    atlas_data_t *p_atlas = img.atlas.p_atlas;
    int atlas_dst = (img.atlas.offset.y * p_atlas->width) + img.atlas.offset.x;
    int y = 0;
    int x = 0;
    while (data_length > 0) {
        uint8_t control = buf->read_u8();
        if (control == 0xff) {
            // next byte = transparent pixels to skip
            x += buf->read_u8();
            while (x >= img.width) {
                y++;
                x -= img.width;
            }
            data_length -= 2;
        } else {
            // control = number of concrete pixels
            for (int i = 0; i < control; i++) {
                int dst = atlas_dst + y * p_atlas->width + x;
                p_atlas->temp.pixel_buffer[dst] = image_to_32_bit(buf->read_u16());
                x++;
                if (x >= img.width) {
                    y++;
                    x -= img.width;
                }
            }
            data_length -= control * 2 + 1;
        }
    }
    return 0; // pixels_count;
}

static const int FOOTPRINT_X_START_PER_HEIGHT[] = {
    28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28
};
#define FOOTPRINT_WIDTH 58
constexpr int FOOTPRINT_HEIGHT = 30;
#define FOOTPRINT_HALF_HEIGHT 15

static int convert_footprint_tile(buffer* buf, const image_t &img, int x_offset, int y_offset) {
    int pixels_count = 0;
    auto p_atlas = img.atlas.p_atlas;

    for (int y = 0; y < FOOTPRINT_HEIGHT; y++) {
        int x_start = FOOTPRINT_X_START_PER_HEIGHT[y];
        int x_max = FOOTPRINT_WIDTH - x_start;
        for (int x = x_start; x < x_max; x++) {
            int dst_index = (y + y_offset + img.atlas.offset.y) * p_atlas->width + img.atlas.offset.x + x + x_offset;
            if (dst_index >= p_atlas->bmp_size) {
                continue;
            }
            p_atlas->temp.pixel_buffer[dst_index] = image_to_32_bit(buf->read_u16());
        }
    }
    return pixels_count;
}

static int convert_isometric_footprint(buffer* buf, const image_t &img) {
    int pixels_count = 0;
    auto p_atlas = img.atlas.p_atlas;

    int num_tiles = img.isometric_size();
    int x_start = (num_tiles - 1) * FOOTPRINT_HEIGHT;
    int y_offset;

    y_offset = img.height - FOOTPRINT_HEIGHT * num_tiles;

    for (int i = 0; i < num_tiles; i++) {
        int x = -FOOTPRINT_HEIGHT * i + x_start;
        int y = FOOTPRINT_HALF_HEIGHT * i + y_offset;
        for (int j = 0; j <= i; j++) {
            convert_footprint_tile(buf, img, x, y);
            x += FOOTPRINT_WIDTH + 2;
        }
    }
    for (int i = num_tiles - 2; i >= 0; i--) {
        int x = -FOOTPRINT_HEIGHT * i + x_start;
        int y = FOOTPRINT_HALF_HEIGHT * (num_tiles * 2 - i - 2) + y_offset;
        for (int j = 0; j <= i; j++) {
            convert_footprint_tile(buf, img, x, y);
            x += FOOTPRINT_WIDTH + 2;
        }
    }
    return pixels_count;
}

static bool is_pixel_transparent(color pixel) {
    return (pixel & COLOR_CHANNEL_ALPHA) == ALPHA_TRANSPARENT;
}

static void convert_to_plain_white(image_t &img) {
    color* pixels = img.temp.pixel_data;
    int atlas_width = img.atlas.p_atlas->width;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (!is_pixel_transparent(pixels[x]))
                pixels[x] |= 0x00ffffff;
        }
        pixels += atlas_width;
    }
}

static void add_edge_to_letter(image_t &img) {
    int atlas_width = img.atlas.p_atlas->width;
    int oldsize = img.width * img.height;
    color* TEMP_BUFFER = new color[oldsize];

    // copy original glyph to the buffer
    color* pixels_row = img.temp.pixel_data;
    auto p_buffer_row = TEMP_BUFFER;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++)
            p_buffer_row[x] = pixels_row[x];
        pixels_row += atlas_width;
        p_buffer_row += img.width;
    }

    // paste back and create edges
    pixels_row = img.temp.pixel_data;
    p_buffer_row = TEMP_BUFFER;
    auto edge_color = COLOR_BLACK;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (!is_pixel_transparent(p_buffer_row[x])) {
                //            if ((p_buffer_row[x] & COLOR_CHANNEL_ALPHA) != ALPHA_TRANSPARENT) {
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
        p_buffer_row += img.width;
    }

    // paste white glyph in the center
    pixels_row = img.temp.pixel_data;
    p_buffer_row = TEMP_BUFFER;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (!is_pixel_transparent(p_buffer_row[x]))
                //            if ((p_buffer_row[x] & COLOR_CHANNEL_ALPHA) != ALPHA_TRANSPARENT)
                pixels_row[atlas_width * 1 + x + 1] = COLOR_WHITE;
        }
        pixels_row += atlas_width;
        p_buffer_row += img.width;
    }

    delete [] TEMP_BUFFER;
}

static int convert_font_glyph_to_bigger_space(buffer* buf, const image_t* img) {
    int pixels_count = 0;
    auto p_atlas = img->atlas.p_atlas;

    for (int y = 0; y < img->height - 2; y++) {
        color* pixel = &p_atlas->temp.pixel_buffer[(img->atlas.offset.y + y) * p_atlas->width + img->atlas.offset.x];
        for (int x = 0; x < img->width - 2; x++) {
            color color = image_to_32_bit(buf->read_u16());
            pixel[x] = color == COLOR_SG2_TRANSPARENT ? ALPHA_TRANSPARENT : color;
            pixels_count++;
        }
    }
    return pixels_count;
}

static void create_special_fonts(std::vector<image_t>* images, int start_index) {
    for (int i = font_definition_for(FONT_SMALL_OUTLINED)->image_offset; i < images->size() - start_index; ++i) {
        const image_t* img = &images->at(i + start_index);
        image_packer_rect* rect = &packer.rects[i + start_index];
        rect->input.width = img->width + 2;
        rect->input.height = img->height + 2;
    }
}
static bool is_font_glyph_in_range(const image_t &img, e_font font_start, e_font font_end) {
    int i = img.sgx_index - 201;
    int starting_offset = font_definition_for(font_start)->image_offset;
    int ending_offset = -1;
    if (font_end != FONT_TYPES_MAX)
        ending_offset = font_definition_for(font_end)->image_offset;
    if (i >= starting_offset && (i < ending_offset || font_end == FONT_TYPES_MAX))
        return true;
    return false;
}

static buffer* external_image_buf = nullptr;
static buffer* load_external_data(const image_t &img) {
    int size = 0;
    safe_realloc_for_size(&external_image_buf, img.data_length);

    // file path
    vfs::path filename("Data/", img.bmp.name.c_str());
    vfs::file_change_extension(filename, "555");

    // load external file
    size = io_read_file_part_into_buffer(filename, MAY_BE_LOCALIZED, external_image_buf, img.data_length, img.sgx_data_offset - 1);
    if (!size) {
        // try in 555 dir
        size = io_read_file_part_into_buffer(filename, MAY_BE_LOCALIZED, external_image_buf, img.data_length, img.sgx_data_offset - 1);
        if (!size) {
            logs::error("unable to load external image %s (tried: %s, offset=%d, length=%d)", 
                        img.bmp.name.c_str(), filename.c_str(), img.sgx_data_offset, img.data_length);
            return nullptr;
        }
    }
    return external_image_buf;
}

static int isometric_calculate_top_height(image_t &img) {
    int top_height = img.isometric_top_height();
    int tri_rows = img.height - top_height - HALF_TILE_HEIGHT_PIXELS * img.isometric_size() - 1;

    for (int d = 0; d < tri_rows; ++d) {  // diagonals
        for (int y = 0; y < d + 1; ++y) { // steps in the diagonal == y axis, too
            int x = 2 * (d - y);
            color* row = &img.temp.pixel_data[y * img.atlas.p_atlas->width];
            color* x_left = &row[x];
            color* x_right = &row[img.width - x - 2];
            if (!is_pixel_transparent(x_left[0]) || !is_pixel_transparent(x_left[1])
                || !is_pixel_transparent(x_right[0]) || !is_pixel_transparent(x_right[1])) {
                return top_height + tri_rows - d;
            }
        }
    }
    return top_height;
}

static void isometric_clear_top_height(image_t &img) {
    for (int x = 0; x < img.width; ++x) {  // diagonals
        int start_y = 15 * (img.width / 58) + ((x < img.width / 2) ? (x / 2) : ((img.width - x) / 2)) + 2;
        for (int y = img.height - start_y; y >= 0; --y) { // steps in the diagonal == y axis, too
            int atlas_y = (y * img.atlas.p_atlas->width);
            color &c = img.temp.pixel_data[atlas_y + x];
            c = 0;
        }
    }
}

static void isometric_clear_foot_bottom(image_t &img) {
    for (int x = 0; x < img.width; ++x) {  // diagonals
        int start_y = 15 * (img.width / 58) + ((x < img.width / 2) ? (x / 4) : ((img.width - x) / 4));
        if (x < 4 || x > img.width - 4) {
            start_y += 4;
        }
        for (int y = img.height - start_y; y < img.height; ++y) { // steps in the diagonal == y axis, too
            int atlas_y = (y * img.atlas.p_atlas->width);
            color &c = img.temp.pixel_data[atlas_y + x];
            c = 0;
        }
    }

    int start_y = 15 * (img.width / 58);
    img.height = img.height - start_y;
}

static bool convert_image_data(buffer* buf, image_t &img, bool convert_fonts) {
    if (img.is_external)
        buf = load_external_data(img);

    if (buf == nullptr)
        return false;

    img.temp.pixel_data = &img.atlas.p_atlas->temp.pixel_buffer[(img.atlas.offset.y * img.atlas.p_atlas->width) + img.atlas.offset.x];

    if (img.type == IMAGE_TYPE_ISOMETRIC) {
        convert_isometric_footprint(buf, img);
        if (img.has_isometric_top) {
            convert_compressed(buf, img.data_length - img.uncompressed_length, img);
            img.isometric_box_height = isometric_calculate_top_height(img);
        }

        if (img.is_isometric_foot) {
            isometric_clear_top_height(img);
        }

        if (img.is_isometric_top) {
            isometric_clear_foot_bottom(img);
        }
    } else if (img.is_fully_compressed) {
        convert_compressed(buf, img.data_length, img);
    } else {
        convert_uncompressed(buf, img);
    }

    if (convert_fonts) { // special font conversions
        if (is_font_glyph_in_range(img, FONT_SMALL_PLAIN, FONT_NORMAL_BLACK_ON_LIGHT)
            || is_font_glyph_in_range(img, FONT_SMALL_SHADED, FONT_TYPES_MAX)) {
            convert_to_plain_white(img);
        
        } else if (is_font_glyph_in_range(img, FONT_SMALL_OUTLINED, FONT_NORMAL_BLACK_ON_DARK)) {
            add_edge_to_letter(img);
            img.width += 2;
            img.height += 2;
        }
    }

    img.uncompressed_length /= 2;
    return true;
}

///////// IMAGEPAK

#define MAX_FILE_SCRATCH_SIZE 20000000

imagepak::imagepak(uint8_t ipack, xstring pak_name, int starting_index, bool system_sprites, bool fonts, bool custom) {
    //    images = nullptr;
    //    image_data = nullptr;
    entries_num = 0;
    pack = ipack;
    std::memset(group_image_ids, 0, PAK_GROUPS_MAX * sizeof(uint16_t));
    should_load_system_sprites = system_sprites;
    should_convert_fonts = fonts;
    userpack = custom;

    if (g_args.is_log_resources()) {
        logs::info("VFS: Starting to load pack '%s' (id=%d, index=%d, custom=%d)", 
                   pak_name.c_str(), ipack, starting_index, custom ? 1 : 0);
    }

    if (custom) {
        if (!load_zip_pak(pak_name.c_str(), starting_index)) {
            if (g_args.is_log_resources()) {
                logs::warn("VFS: Failed to load zip pack '%s'", pak_name.c_str());
            }
            cleanup_and_destroy();
        }
        return;
    }

    useridx_update(ipack);

    if (!load_pak(pak_name.c_str(), starting_index)) {
        logs::warn("imagepak: failed to load pack '%s' (id=%d, index=%d) - file may be missing or corrupted", 
                    pak_name.c_str(), ipack, starting_index);
        if (g_args.is_log_resources()) {
            logs::warn("VFS: Failed to load pack '%s' (id=%d, index=%d)", pak_name.c_str(), ipack, starting_index);
        }
        cleanup_and_destroy();
    }
}

imagepak::~imagepak() {
    cleanup_and_destroy();
}

span_const<imagepak::bmp_name> imagepak::names() {
    return {bmp_names.data(), num_bmp_names};
}

span_const<uint16_t> imagepak::image_ids() {
    return {group_image_ids, groups_num};
}

void imagepak::cleanup_and_destroy() {
    for (int i = 0; i < atlas_pages.size(); ++i) {
        auto atlas_data = atlas_pages.at(i);
        if (atlas_data.temp.pixel_buffer != nullptr)
            delete atlas_data.temp.pixel_buffer;

        atlas_data.temp.pixel_buffer = nullptr;
        if (atlas_data.texture != nullptr) {
            SDL_DestroyTexture(atlas_data.texture);
        }
        atlas_data.texture = nullptr;
    }
    atlas_pages.clear();
}

struct offset_ids {
    int start;
    int id;
};

bool imagepak::load_zip_pak(pcstr pak, int starting_index) {
    OZZY_PROFILER_FUNCTION();
    name = pak;

    if (g_args.is_log_resources()) {
        logs::info("VFS: Loading zip pack '%s' (starting_index=%d)", pak, starting_index);
    }

    entries_num = 0;
    groups_num = 0;
    int bmp_last_group_id = 0;
    int last_idx_in_bmp = 1;

    pcstr allow_dirs_to_find[] = { "Mods", "Data" };
    bool found = false;
    vfs::path datafile;

    for (const auto &dir : allow_dirs_to_find) {
        datafile.printf("%s/%s.sgx", dir, pak);

        if (vfs::file_exists(datafile)) {
            found = true;
            break;
        }
    }

    if (!found) {
        if (g_args.is_log_resources()) {
            logs::warn("VFS: Zip pack file not found: '%s'", pak);
        }
        return false;
    }

    if (g_args.is_log_resources()) {
        logs::info("VFS: Zip pack file found: '%s'", datafile.c_str());
    }

    if (!vfs::mount_pack(datafile)) {
        return false;
    }

    vfs::path configname(datafile, "/", pak, ".js");
    archive arch = config::load(configname);

    global_image_index_offset = starting_index;
    g_config_arch.r_array(pak, [&] (archive arch) {
        int start_index = arch.r_int("start_index");
        int finish_index = arch.r_int("finish_index");
        if (finish_index <= 0) {
            finish_index = start_index;
        }
        verify_no_crash(finish_index >= start_index);
        group_image_ids[groups_num] = entries_num;
        bmp_names[groups_num] = arch.r_string("name");
        entries_num += (finish_index - start_index) + 1;
        ++groups_num;
    });

    verify_no_crash(global_image_index_offset >= 25000);
    images_array.reserve(entries_num);

    svector<offset_ids, PAK_GROUPS_MAX> offset_ids_vec;
    for (int ii = 0; ii < groups_num; ++ii) {
        offset_ids_vec.push_back({ group_image_ids[ii], ii });
    }

    std::sort(offset_ids_vec.begin(), offset_ids_vec.end(), [] (auto &lhs, auto &rhs) { return lhs.start < rhs.start; });

    auto load_img = [&] (pcstr fn, int i, int group_id, int atlas_rect_id) {
        image_t img;
        img.pak_id = pack;
        img.pak_name = name;
        img.sgx_index = i;
        img.data_length = -1;
        img.uncompressed_length = -1;
        img.unk00 = -1;
        img.start_index = global_image_index_offset;
        img.offset_mirror = 0;

        vfs::reader file = vfs::file_open(fn);
        verify_no_crash(file && "file image should exist");

        SDL_Surface *surface = nullptr;
        if (file) {
            SDL_RWops *rw = SDL_RWFromConstMem((void *)file->data(), file->size());
            surface = IMG_LoadPNG_RW(rw);
        }

        img.width = surface ? surface->w : 0;
        img.height = surface ? surface->h : 0;
        img.temp.surface = (void*)surface;

        img.unk03 = -1;
        img.animation.num_sprites = -1;
        img.animation.unk04 = -1;
        img.animation.sprite_offset = {-1, -1};
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
        img.bmp.group_id = group_id;
        img.bmp.name = bmp_names[img.bmp.group_id];

        if (img.bmp.group_id != bmp_last_group_id) {
            last_idx_in_bmp = 1; // new bitmap name, reset bitmap grouping index
            bmp_last_group_id = img.bmp.group_id;
        }

        img.bmp.entry_index = last_idx_in_bmp;

        bstring64 img_bmp_short_name = bmp_names[img.bmp.group_id].data();
        img_bmp_short_name.replace(' ', '_');
        img_bmp_short_name.replace_str(".bmp", "");
        bstring256 img_bmp_tname;
        img_bmp_tname.printf("%s/%s_%05d", name.c_str(), img_bmp_short_name.c_str(), img.bmp.entry_index);
        img.bmp.tname = img_bmp_tname.tolower().c_str();

        if (offset_ids_vec.size() == 1) {
            img.group_id = 0;
            img.group_index = img.sgx_index - offset_ids_vec.front().start;
        } else {
            // Find the last group where start <= i
            auto group_it = std::upper_bound(offset_ids_vec.begin(), offset_ids_vec.end(), i, [] (int value, const auto &offsetid) { return value < offsetid.start; });
            if (group_it != offset_ids_vec.begin()) {
                --group_it;
                img.group_id = group_it->id;
                img.group_index = img.sgx_index - group_it->start;
            } else if (!offset_ids_vec.empty()) {
                img.group_id = offset_ids_vec.front().id;
                img.group_index = img.sgx_index - offset_ids_vec.front().start;
            }
        }

        last_idx_in_bmp++;

        img.unk13 = -1;
        img.animation.speed_id = 1;
        img.unk14 = -1;
        img.unk15 = -1;
        img.unk16 = -1;
        img.unk17 = -1;
        img.unk18 = -1;
        img.unk19 = -1;
        img.unk20 = -1;

        image_packer_rect* rect = &packer.rects[atlas_rect_id];
        rect->input.width = img.width;
        rect->input.height = img.height;

        images_array.push_back(img);
    };

    // prepare atlas packer & renderer
    vec2i max_texture_sizes = g_render.get_max_image_size();
    int init_result = packer.init(entries_num, max_texture_sizes);
    if (init_result != IMAGE_PACKER_OK) {
        return false;
    }

    int tmp_group_id = 0, atlas_rect_id = 0;
    g_config_arch.r_array(pak, [&] (archive arch) {
        bstring128 prefix = arch.r_string("prefix");
        int start_index = arch.r_int("start_index");
        int finish_index = arch.r_int("finish_index");
        if (finish_index <= 0) {
            finish_index = start_index;
        }
        verify_no_crash(finish_index >= start_index);

        for (int i = start_index; i <= finish_index; ++i) {
            bstring512 name;
            if (!prefix.ends_with("_")) {
                logs::warn("WARN! %s incorrect prefix format for %s, should ends with '_'", datafile.c_str(), name.c_str());
            }
            name.printf("%s%05u.png", prefix.c_str(), i);
            name = name.tolower();
            load_img(bstring256(datafile, "/", name), i - start_index, tmp_group_id, atlas_rect_id);
            ++atlas_rect_id;
        }
        ++tmp_group_id;
    });

    packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
    packer.options.reduce_image_size = 1;
    packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

    image_packer_pack(&packer);
    atlas_pages.reserve(packer.result.pages_needed);
    for (uint32_t i = 0; i < packer.result.pages_needed; ++i) {
        atlas_data_t atlas_data;
        atlas_data.width = i == packer.result.pages_needed - 1 ? packer.result.last_image_width : max_texture_sizes.x;
        atlas_data.height = i == packer.result.pages_needed - 1 ? packer.result.last_image_height : max_texture_sizes.y;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.temp.pixel_buffer = new color[atlas_data.bmp_size];
        memset(atlas_data.temp.pixel_buffer, 0, atlas_data.bmp_size * sizeof(uint32_t));
        atlas_data.texture = nullptr;
        atlas_pages.push_back(atlas_data);
    }

    // finish filling in image and atlas information
    for (int i = 0; i < entries_num; i++) {
        image_t& img = images_array.at(i);

        if (img.offset_mirror != 0) {
            img.mirrored_img = &images_array.at(i + img.offset_mirror);
        }

        image_packer_rect& rect = packer.rects[i];
        img.atlas.index = rect.output.image_index;
        atlas_data_t* p_data = &atlas_pages.at(img.atlas.index);
        img.atlas.p_atlas = p_data;
        img.atlas.offset = rect.output.pos;

        // load and convert image bitmap data
        image_copy_to_atlas(img);
    }

    // create textures from atlas data
    for (int i = 0; i < atlas_pages.size(); ++i) {
        atlas_data_t& atlas_data = atlas_pages.at(i);
        if (g_args.is_log_resources()) {
            logs::info("VFS: Creating atlas texture %d/%d for folder pak '%s' - size %dx%d", 
                       i + 1, atlas_pages.size(), name.c_str(), atlas_data.width, atlas_data.height);
        }
        atlas_data.texture = g_render.create_texture_from_buffer(atlas_data.temp.pixel_buffer, atlas_data.width, atlas_data.height);
        if (atlas_data.texture == nullptr) {
            if (g_args.is_log_resources()) {
                logs::error("VFS: Failed to create atlas texture %d/%d for folder pak '%s'", 
                           i + 1, atlas_pages.size(), name.c_str());
            }
            return false;
        }

        // delete temp data buffer in the atlas
        delete atlas_data.temp.pixel_buffer;
        atlas_data.temp.pixel_buffer = nullptr;
        if (g_args.is_log_resources()) {
            logs::info("VFS: Atlas texture %d/%d created successfully for folder pak '%s'", 
                       i + 1, atlas_pages.size(), name.c_str());
        }
    }

    // remove pointers to raw data buffer in the images
    for (int i = 0; i < images_array.size(); ++i) {
        image_t &img = images_array.at(i);
        SDL_FreeSurface((SDL_Surface *)img.temp.surface);
        img.temp.surface = nullptr;
    }

    image_packer_reset(packer);

    logs::info("Loaded folder pak from '%s' ---- %i images, %i groups, %ix%i atlas pages (%u)",
               name.c_str(), entries_num, groups_num, atlas_pages.at(atlas_pages.size() - 1).width, atlas_pages.at(atlas_pages.size() - 1).height, atlas_pages.size());
    if (g_args.is_log_resources()) {
        logs::info("VFS: Folder pak '%s' loaded successfully - %i images, %i groups, %u atlas pages (%ix%i)",
                   name.c_str(), entries_num, groups_num, atlas_pages.size(),
                   atlas_pages.at(atlas_pages.size() - 1).width, atlas_pages.at(atlas_pages.size() - 1).height);
    }

    int y_offset = screen_height() - 24;
    g_render.clear_screen();
    if (image_data_fonts_ready()) {
        text_draw(bstring512("loading folder pak (", pak, ")").c_str(), 5, y_offset, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_YELLOW);
    }

    platform_renderer_render();

    int max_imgid_this_pak = global_image_index_offset + entries_num;
    verify_no_crash(max_imgid_this_pak < 0xffff);
    update_max_imgid(max_imgid_this_pak);

    return true;
}

buffer* pak_buf = new buffer(MAX_FILE_SCRATCH_SIZE);
bool imagepak::load_pak(pcstr pak_name, int starting_index) {
    OZZY_PROFILER_FUNCTION();

    if (g_args.is_log_resources()) {
        logs::info("VFS: Loading pak '%s' (starting_index=%d)", pak_name, starting_index);
    }

    // construct proper filepaths
    name = pak_name;
    vfs::path filename_full("Data/", pak_name);

    // split in .555 and .sg3 filename strings
    vfs::path filename_555(filename_full, ".555");
    vfs::path filename_sgx(filename_full, ".sg3");

    if (g_args.is_log_resources()) {
        logs::info("VFS: Looking for pak files: '%s' and '%s'", filename_555.c_str(), filename_sgx.c_str());
    }

    // *********** PAK_FILE.SGX ************

    // read sgx data into buffer
    safe_realloc_for_size(&pak_buf, MAX_FILE_SCRATCH_SIZE);
    if (!io_read_file_into_buffer((pcstr)filename_sgx, MAY_BE_LOCALIZED, pak_buf, MAX_FILE_SCRATCH_SIZE)) {
        if (g_args.is_log_resources()) {
            logs::warn("VFS: Failed to read pak file '%s'", filename_sgx.c_str());
        }
        return false;
    }

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
    if (groups_num > 0 && group_image_ids[0] == 0) {
        has_system_bmp = true;
    }

    svector<offset_ids, PAK_GROUPS_MAX> offset_ids_vec;
    for (int ii = 0; ii < groups_num; ++ii) {
        offset_ids_vec.push_back({ group_image_ids[ii], ii });
    }

    std::sort(offset_ids_vec.begin(), offset_ids_vec.end(), [] (auto &lhs, auto &rhs) { return lhs.start < rhs.start; });

    // parse bitmap names
    using bmp_name_data = std::array<char, bmp_name::capacity>;
    std::vector<bmp_name_data> names(num_bmp_names);
    pak_buf->read_raw(names.data(), num_bmp_names * bmp_name::capacity);
    for (int i = 0; i < num_bmp_names; ++i) {
        bmp_names[i] = names[i].data();
        //logs::info("%s, %u", bmp_names[i].c_str(), i);
    }

    // (move buffer to the rest of the data)
    verify_no_crash(vfs::file_has_extension((const char *)filename_sgx, "sg3"));
    pak_buf->set_offset(PAK_HEADER_SIZE_BASE + (200 * bmp_name::capacity)); // sg3 = 40680 bytes

    // prepare atlas packer & renderer
    vec2i max_texture_sizes = g_render.get_max_image_size();
    int result = packer.init(entries_num * 2, max_texture_sizes);
    if (result != IMAGE_PACKER_OK) {
        return false;
    }

    packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
    packer.options.reduce_image_size = 1;
    packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

    // read img data and record atlas rect sizes
    constexpr uint32_t system_img_size = 200;
    int bmp_last_group_id = 0;
    int last_idx_in_bmp = 1;
    images_array.reserve(entries_num * 2);
    for (int i = 0; i < entries_num; i++) {
        image_t &img = images_array.emplace_back();
        img.pak_id = pack;
        img.is_isometric_foot = true;
        img.is_isometric_top = false;
        img.pak_name = name;
        img.sgx_index = i;
        img.rect_index = i;
        img.sgx_data_offset = pak_buf->read_i32();
        img.data_length = pak_buf->read_i32();
        img.uncompressed_length = pak_buf->read_i32();
        img.unk00 = pak_buf->read_i32();
        img.start_index = starting_index;
        img.offset_mirror = pak_buf->read_i32(); // .sg3 only
        // clamp dimensions so that it's not below zero!
        img.width = pak_buf->read_i16();
        img.width = std::max<int>(0, img.width);
        img.height = pak_buf->read_i16();
        img.height = std::max<int>(0, img.height);
        img.group_id = pak_buf->read_u16();
        img.group_index = pak_buf->read_u16();
        img.unk03 = pak_buf->read_i16();
        img.animation.num_sprites = pak_buf->read_u16();
        img.animation.unk04 = pak_buf->read_i16();
        img.animation.sprite_offset.x = pak_buf->read_i16();
        img.animation.sprite_offset.y = pak_buf->read_i16();
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
        img.has_isometric_top = pak_buf->read_i8();
        img.unk11 = pak_buf->read_i8();
        img.unk12 = pak_buf->read_i8();
        img.bmp.group_id = pak_buf->read_u8();
        img.bmp.name = bmp_names[img.bmp.group_id];

        if (img.bmp.group_id != bmp_last_group_id) {
            last_idx_in_bmp = 1; // new bitmap name, reset bitmap grouping index
            bmp_last_group_id = img.bmp.group_id;
        }

        if (img.bmp.group_id == 0) {
            // Find the last group where start <= last_idx_in_bmp
            auto group_it = std::upper_bound(offset_ids_vec.begin(), offset_ids_vec.end(), last_idx_in_bmp, [] (int value, const auto &offsetid) { return value < offsetid.start; });
            if (group_it != offset_ids_vec.begin()) {
                --group_it;
                img.bmp.group_id = group_it->id;
                img.bmp.name.printf("group_%d", img.bmp.group_id);
            } else if (!offset_ids_vec.empty()) {
                img.bmp.group_id = offset_ids_vec.front().id;
                img.bmp.name.printf("group_%d", img.bmp.group_id);
            }
        } else {
            // Find the last group where start <= i
            auto group_it = std::upper_bound(offset_ids_vec.begin(), offset_ids_vec.end(), i, [] (int value, const auto &offsetid) { return value < offsetid.start; });
            if (group_it != offset_ids_vec.begin()) {
                --group_it;
                img.group_id = group_it->id;
                img.group_index = img.sgx_index - group_it->start;
            } else if (!offset_ids_vec.empty()) {
                img.group_id = offset_ids_vec.front().id;
                img.group_index = img.sgx_index - offset_ids_vec.front().start;
            }
        }

        img.bmp.entry_index = last_idx_in_bmp;
        bstring64 img_bmp_short_name = bmp_names[img.bmp.group_id].data();
        img_bmp_short_name = img_bmp_short_name.tolower();
        img_bmp_short_name.replace(' ', '_');
        img_bmp_short_name.replace_str(".bmp", "");
        bstring256 img_bmp_tname;
        img_bmp_tname.printf("%s/%s_%05d", name.c_str(), img_bmp_short_name.c_str(), img.bmp.entry_index);
        img.bmp.tname = img_bmp_tname.tolower().c_str();

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

        if (has_system_bmp && !should_load_system_sprites && i < (system_img_size+1)) {
            // continue;
        } else {
            // record atlas rect sizes in the packer
            image_packer_rect& rect = packer.rects[i];
            rect.input.width = img.width;
            rect.input.height = img.height;
        }
        img.debug.max_frame = 0xff;
    }

    for (int i = 0, rect_i = entries_num; i < entries_num; ++i) {
        image_t &img = images_array[i];
        if (img.type != IMAGE_TYPE_ISOMETRIC) {
            continue;
        }
        image_t isometric_img = images_array[i];
        image_packer_rect& rect = packer.rects[rect_i];
        rect.input.width = img.width;
        rect.input.height = img.height;
        isometric_img.is_isometric_foot = false;
        isometric_img.is_isometric_top = true;
        isometric_img.isometric_base = &img;
        isometric_img.rect_index = rect_i;
        images_array.push_back(isometric_img);
        img.isometric_top = &images_array.back();
        ++rect_i;
    }

    // create special fonts
    if (should_convert_fonts) {
        create_special_fonts(&images_array, 1 + (200 * (!should_load_system_sprites)));
    }

    // repack and generate atlas pages
    image_packer_pack(&packer);
    atlas_pages.reserve(packer.result.pages_needed);
    for (uint32_t i = 0; i < packer.result.pages_needed; ++i) {
        atlas_data_t atlas_data;
        atlas_data.width = i == packer.result.pages_needed - 1 ? packer.result.last_image_width : max_texture_sizes.x;
        atlas_data.height = i == packer.result.pages_needed - 1 ? packer.result.last_image_height : max_texture_sizes.y;
        atlas_data.bmp_size = atlas_data.width * atlas_data.height;
        atlas_data.temp.pixel_buffer = new color[atlas_data.bmp_size];
        memset(atlas_data.temp.pixel_buffer, 0, atlas_data.bmp_size * sizeof(uint32_t));
        atlas_data.texture = nullptr;
        atlas_pages.push_back(atlas_data);
    }

    // *********** PAK_FILE.555 ************

    // read bitmap data into buffer
    safe_realloc_for_size(&pak_buf, MAX_FILE_SCRATCH_SIZE);
    if (!io_read_file_into_buffer((const char *)filename_555, MAY_BE_LOCALIZED, pak_buf, MAX_FILE_SCRATCH_SIZE)) {
        return false;
    }

    // finish filling in image and atlas information
    for (auto &img: images_array) {
        if (has_system_bmp && !should_load_system_sprites && img.sgx_index < 201) {
            continue;
        }

        if (img.offset_mirror != 0) {
            img.mirrored_img = &images_array.at(img.sgx_index + img.offset_mirror);
        }

        image_packer_rect& rect = packer.rects[img.rect_index];
        img.atlas.index = rect.output.image_index;
        atlas_data_t* p_data = &atlas_pages.at(img.atlas.index);
        img.atlas.p_atlas = p_data;
        img.atlas.offset = rect.output.pos;

        // load and convert image bitmap data
        pak_buf->set_offset(img.sgx_data_offset);
        if (!convert_image_data(pak_buf, img, should_convert_fonts)) {
            if (img.is_external) {
                logs::error("imagepak: failed to convert external image %s (group=%d, sgx_index=%d, rect_index=%d) - external file may be missing", 
                            img.bmp.name.c_str(), img.group_id, img.sgx_index, img.rect_index);
            } else {
                logs::error("imagepak: failed to convert image %s (group=%d, sgx_index=%d, rect_index=%d)", 
                            img.bmp.name.c_str(), img.group_id, img.sgx_index, img.rect_index);
            }
        }
    }

    // create textures from atlas data
    for (int i = 0; i < atlas_pages.size(); ++i) {
        atlas_data_t& atlas_data = atlas_pages.at(i);
        if (g_args.is_log_resources()) {
            logs::info("VFS: Creating atlas texture %d/%d for pak '%s' - size %dx%d", 
                       i + 1, atlas_pages.size(), pak_name, atlas_data.width, atlas_data.height);
        }
        atlas_data.texture = g_render.create_texture_from_buffer(atlas_data.temp.pixel_buffer, atlas_data.width, atlas_data.height);
        if (atlas_data.texture == nullptr) {
            if (g_args.is_log_resources()) {
                logs::error("VFS: Failed to create atlas texture %d/%d for pak '%s'", i + 1, atlas_pages.size(), pak_name);
            }
            return false;
        }

        // delete temp data buffer in the atlas
        delete atlas_data.temp.pixel_buffer;
        atlas_data.temp.pixel_buffer = nullptr;

        if (g_args.is_log_resources()) {
            logs::info("VFS: Atlas texture %d/%d created successfully for pak '%s'", 
                       i + 1, atlas_pages.size(), pak_name);
        }

        // ********* DEBUGGING **********
#if defined(GAME_PLATFORM_WIN)
        if (game.save_debug_texture) {
            vfs::path fs_fpath;
            fs_fpath.printf("DEV_TESTING/tex/%s_%i.bmp", name.c_str(), i);
            g_render.save_texture_to_file(fs_fpath.c_str(), atlas_data.texture);
        }
#endif
        // ******************************
    }

    // remove pointers to raw data buffer in the images
    for (int i = 0; i < images_array.size(); ++i) {
        auto img = images_array.at(i);
        img.temp.pixel_data = nullptr;
    }

    image_packer_reset(packer);

    if (g_args.is_log_resources()) {
        logs::info("Loaded imagepak from '%s' ---- %i images, %i groups, %ix%i atlas pages (%u)",
                    filename_sgx.c_str(), entries_num, groups_num, atlas_pages.at(atlas_pages.size() - 1).width, 
                    atlas_pages.at(atlas_pages.size() - 1).height, atlas_pages.size());
    }

    int y_offset = screen_height() - 24;

    g_render.clear_screen();
    if (image_data_fonts_ready() && image_data_render_on_new_loadpacks()) {
        bstring512 loadpack_text("loading pak (", pak_name, ")");
        text_draw(loadpack_text.c_str(), 5, y_offset, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_YELLOW);
    }
    platform_renderer_render();

    int max_imgid_this_pak = global_image_index_offset + entries_num;
    verify_no_crash(max_imgid_this_pak < 0xffff);
    update_max_imgid(max_imgid_this_pak);

    return true;
}

image_desc imagepak::get_image_desc(const xstring &name) const {
    const xstring name_lower = name.tolower();
    
    for (const auto& img : images_array) {
        verify_no_crash(!img.bmp.tname.empty() && "Texture name shouldn't be empty");
        if (img.bmp.tname.empty()) {
            continue;
        }

        if (img.bmp.tname == name_lower) {
            image_desc desc;
            desc.pack = static_cast<int16_t>(get_pack());
            desc.id = static_cast<int16_t>(img.group_id);
            desc.offset = static_cast<int16_t>(img.group_index);
            desc.path = img.bmp.tname;
            return desc;
        }
    }
    
    return image_desc{};
}

int imagepak::get_global_image_index(int group) {
    if (group < 0 || group >= groups_num) {
        return -1;
    }

    int image_id = group_image_ids[group];
    return image_id + global_image_index_offset;
}

const image_t* imagepak::get_image(int id, bool relative) {
    if (!relative) {
        id -= global_image_index_offset;
    }

    if (id < 0 || id >= entries_num) {
        return nullptr;
    }

    return &images_array[id];
}

void imagepak::useridx_update(uint16_t index) {
    max_seen_useridx = std::max(max_seen_useridx, index);
}

void imagepak::update_max_imgid(uint16_t imgid) {
    max_seen_imgid = std::max(max_seen_imgid, imgid);
}

int imagepak::get_entries_num(xstring pak_name) {
    vfs::path filename_sgx(pak_name.c_str());
    if (!vfs::file_has_extension(filename_sgx, "sgx")) {
        filename_sgx.append(".sgx");
        filename_sgx = filename_sgx.resolve();
    }
    
    if (!filename_sgx.empty() && vfs::file_exists(filename_sgx.c_str())) {
        return io_read_sgx_entries_num(filename_sgx);
    }

    vfs::path filename_full("Data/", pak_name.c_str());
    vfs::path filename_sg3(filename_full, ".sg3");
    return io_read_sg3_entries_num(filename_sg3);
}
