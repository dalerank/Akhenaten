#pragma once 

#include <array>
#include <vector>
#include "content/imagepak.h"
#include "core/bstring.h"

struct imagepak_handle {
    bstring128 name;
    int id = -1;
    int index = -1;
    uint32_t entries_num = 0;
    bool system = false;
    bool custom = false;
    bool delayed = true;
    imagepak *handle = nullptr;
};

struct imagepak_holder_t {
    bool fonts_loaded = false;
    bool allow_updata_on_load = false;
    bool common_inited = false;
    int font_base_offset;

    color *tmp_image_data = nullptr;
    int last_active_index = -1;

    std::array<imagepak_handle, 128> pak_list;
    std::vector<const image_t *> image_cache;
};

void image_data_init();
void image_data_touch(const imagepak_handle& h);

extern imagepak_holder_t *g_image_data;