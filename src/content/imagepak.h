#pragma once

#include "graphics/image.h"
#include "content/vfs.h"
#include "core/xstring.h"
#include "core/bstring.h"
#include "core/custom_span.hpp"

#include <vector>

#define PAK_HEADER_INFO_BYTES 80
#define PAK_HEADER_SIZE_BASE PAK_HEADER_INFO_BYTES + (PAK_GROUPS_MAX * 2) // total = 680 bytes

#define PAK_IMAGE_ENTRY_SIZE 64


class imagepak {
public:
    using bmp_name = bstring<200>;
    enum {
        PAK_GROUPS_MAX = 300,
    };

private:
    int entries_num;
    bool userpack;
    int useridx;
    int version;
    size_t groups_num;
    std::array<bmp_name, PAK_GROUPS_MAX> bmp_names;
    uint16_t num_bmp_names;
    uint16_t group_image_ids[PAK_GROUPS_MAX];
    std::vector<image_t> images_array;

    bool should_load_system_sprites;
    bool should_convert_fonts;

    bool load_pak(pcstr pak_name, int starting_index);
    bool load_zip_pak(pcstr folder, int starting_index);
    void cleanup_and_destroy();

public:
    xstring name;
    std::vector<atlas_data_t> atlas_pages;

    int global_image_index_offset = 0;

    imagepak(xstring pak_name, int starting_index, bool system_sprites = false, bool fonts = false, bool custom = false);
    ~imagepak();

    span_const<bmp_name> names();
    span_const<uint16_t> image_ids();

    const image_t *front() const { return &images_array.front(); }
    const image_t *back() const { return &images_array.back(); }

    inline int get_entry_count() const { return entries_num; }
    int get_global_image_index(int group);
    inline int get_user_idx() const { return useridx; }
    const image_t* get_image(int id, bool relative = false);
    bool loaded_system_sprites() const { return should_load_system_sprites; }

    static int get_entries_num(xstring pak_name);
};