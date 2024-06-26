#pragma once

#include "graphics/image.h"
#include "content/vfs.h"
#include "core/bstring.h"

#include <vector>

#define PAK_HEADER_INFO_BYTES 80
#define PAK_GROUPS_MAX 300
#define PAK_HEADER_SIZE_BASE PAK_HEADER_INFO_BYTES + (PAK_GROUPS_MAX * 2) // total = 680 bytes

#define PAK_IMAGE_ENTRY_SIZE 64

using bmp_name = bstring<200>;

class imagepak {
    bool userpack;
    int useridx;
    int version;
    int entries_num;
    int groups_num;
    bmp_name bmp_names[PAK_GROUPS_MAX];
    int num_bmp_names;
    uint16_t group_image_ids[PAK_GROUPS_MAX];
    std::vector<image_t> images_array;

    bool should_load_system_sprites;
    bool should_convert_fonts;

    bool load_pak(pcstr pak_name, int starting_index);
    bool load_folder_pak(pcstr folder);
    void cleanup_and_destroy();

public:
    bstring512 name;
    std::vector<atlas_data_t> atlas_pages;

    int global_image_index_offset = 0;

    imagepak(pcstr pak_name, int starting_index, bool system_sprites = false, bool fonts = false, bool custom = false);
    ~imagepak();

    int get_entry_count();
    int get_global_image_index(int group);
    inline int get_user_idx() const { return useridx; }
    const image_t* get_image(int id, bool relative = false);
};