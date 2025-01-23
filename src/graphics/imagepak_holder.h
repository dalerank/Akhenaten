#pragma once 

#include <array>
#include <vector>
#include "content/imagepak.h"
#include "core/bstring.h"

struct imagepak_handle {
    bstring128 name;
    int id = -1;
    int index = -1;
    bool system = false;
    bool custom = false;
    imagepak *handle = nullptr;
};

struct imagepak_holder_t {
    bool fonts_enabled = false;
    bool fonts_loaded = false;
    bool common_inited = false;
    int font_base_offset;

    std::vector<imagepak **> pak_list;

    std::vector<imagepak *> temple_paks;
    std::vector<imagepak *> monument_paks;
    std::vector<imagepak *> enemy_paks;
    std::vector<imagepak *> font_paks;

    imagepak *monument = nullptr;
    imagepak *enemy = nullptr;
    imagepak *font = nullptr;

    color *tmp_image_data = nullptr;

    std::array<imagepak_handle, 16> common;
};

void image_data_init();

extern imagepak_holder_t *g_image_data;