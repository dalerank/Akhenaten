#pragma once 

#include "content/imagepak.h"
#include "core/xstring.h"
#include "core/archive.h"

struct imagepak_handle {
    xstring name;
    int16_t id = -1;
    int index = -1;
    uint32_t entries_num = 0;
    bool system = false;
    bool custom = false;
    bool delayed = true;
    imagepak *handle = nullptr;
};
ANK_CONFIG_STRUCT(imagepak_handle, name, id, index, entries_num, system, custom, delayed)

template<>
struct stable_array_max_elements<imagepak_handle> {
    enum { max_elements = 128 };
};

template<>
struct std::hash<imagepak_handle> {
    [[nodiscard]] size_t operator()(const imagepak_handle &h) const noexcept {
        return h.id;
    }
};

struct imagepak_holder_t {
    bool fonts_loaded = false;
    bool allow_updata_on_load = false;
    bool common_inited = false;
    int font_base_offset;

    color *tmp_image_data = nullptr;
    int last_active_index = -1;

    stable_array<imagepak_handle> pak_list;
    std::vector<const image_t *> image_cache;
};

void image_data_init();
void image_data_touch(const imagepak_handle& h);

extern imagepak_holder_t *g_image_data;