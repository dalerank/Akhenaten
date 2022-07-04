#ifndef OZYMANDIAS_IMAGEPAK_H
#define OZYMANDIAS_IMAGEPAK_H

#include <vector>
#include "graphics/image.h"
#include "io/file.h"

#define PAK_HEADER_INFO_BYTES 80
#define PAK_BMP_NAME_SIZE 200
#define PAK_GROUPS_MAX 300
#define PAK_HEADER_SIZE_BASE PAK_HEADER_INFO_BYTES + (PAK_GROUPS_MAX * 2) // total = 680 bytes

#define PAK_IMAGE_ENTRY_SIZE 64
#define NAME_SIZE 32

class imagepak {
    int version;
    int entries_num;
    int groups_num;
    char *bmp_names;
    int num_bmp_names;
    uint16_t *group_image_ids;
    std::vector<image_t> images_array;

    bool SHOULD_LOAD_SYSTEM_SPRITES;
    bool SHOULD_CONVERT_FONTS;

    bool load_pak(const char *pak_name, int starting_index);
    void cleanup_and_destroy();
public:
    char name[MAX_FILE_NAME];
    std::vector<atlas_data_t> atlas_pages;

    int global_image_index_offset = 0;

    imagepak(const char *pak_name, int starting_index, bool SYSTEM_SPRITES = false, bool FONTS = false);
    ~imagepak();

    int get_entry_count();
    int get_global_image_index(int group);
    const image_t *get_image(int id, bool relative = false);
};

#endif //OZYMANDIAS_IMAGEPAK_H
