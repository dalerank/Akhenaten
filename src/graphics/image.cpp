#include "image.h"
#include "font.h"
#include "image_groups.h"
#include "content/imagepak.h"
#include "graphics/image_desc.h"
#include "graphics/imagepak_holder.h"
#include "content/dir.h"
#include "core/svector.h"
#include "core/log.h"

#include <array>

// These functions are actually related to the imagepak class I/O, but it made slightly more
// sense to me to have here as "core" image struct/class & game graphics related functions.
bool set_pak_in_collection(int pak_id, imagepak** pak, std::vector<imagepak*>* collection) {
    if (pak_id >= collection->size()) {
        return false;
    }

    *pak = collection->at(pak_id);
    return true;
}

int image_copy_to_atlas(const image_t &img) {
    int pixels_count = 0;
    atlas_data_t *p_atlas = img.atlas.p_atlas;
    color *pixels = (color *)((SDL_Surface *)img.temp.surface)->pixels;

    for (int y = 0; y < img.height; y++) {
        color *pixel = &p_atlas->temp.pixel_buffer[(img.atlas.offset.y + y) * p_atlas->width + img.atlas.offset.x];
        for (int x = 0; x < img.width; x++) {
            color color = image_to_argb(pixels[y * img.width + x]);
            pixel[x] = color;
            pixels_count++;
        }
    }
    return pixels_count;
}

void image_data_touch(const imagepak_handle& h) {
    image_get(h.id, 0);
}

bool image_data_fonts_ready() {
    return g_image_data && g_image_data->fonts_loaded;
}

bool image_data_render_on_new_loadpacks() {
    return g_image_data && g_image_data->allow_updata_on_load;
}

bool image_load_paks() {
    auto& data = *g_image_data;
    data.fonts_loaded = false;
    data.allow_updata_on_load = true;
    data.font_base_offset = 0;

    auto &fontpack = data.pak_list[PACK_FONT];
    fontpack.handle = new imagepak(PACK_FONT, "Pharaoh_Fonts", 18765, false, true);
    fontpack.entries_num = fontpack.handle->get_entry_count();
    fontpack.index = fontpack.handle->global_image_index_offset;
    fontpack.id = PACK_FONT;
    data.fonts_loaded = true;

    for (uint8_t pakidx = 0; pakidx < g_image_data->pak_list.size(); ++pakidx) {
        auto &imgpak = g_image_data->pak_list[pakidx];
        if (imgpak.name.empty()) {
            continue;
        }

        const int pack_entries = imagepak::get_entries_num(imgpak.name);
        if (pack_entries > 0) {
            imgpak.entries_num = pack_entries;
        }
  
        if (imgpak.delayed) {
            continue;
        }

        imgpak.handle = new imagepak(pakidx, imgpak.name, imgpak.index, imgpak.system, false, imgpak.custom);
        if (imgpak.custom) {
            imgpak.entries_num = imgpak.handle->get_entry_count();
        }
        // Check if pack loaded successfully
        if (imgpak.handle && imgpak.handle->image_ids().size() == 0) {
            logs::error("image_load_paks: pack %d (%s) loaded but has 0 groups", pakidx, imgpak.name.c_str());
        }
    }

    data.allow_updata_on_load = false;

    return true;
}

static imagepak*pak_from_collection_name(const xstring &name) {
    auto &data = *g_image_data;
    const auto &pak_list = g_image_data->pak_list;

    for (const auto& pak: pak_list) {
        if (pak.name != name) {
            continue;
        }        

        if (!pak.handle) {
            image_data_touch(pak);
        }

        if (pak.handle) {
            return pak.handle;
        }
    }

    return nullptr;
}

static imagepak* pak_from_collection_id(int collection) {
    auto& data = *g_image_data;
    if (collection < 0 || collection >= data.pak_list.size()) {
        logs::error("pak_from_collection_id: invalid collection %d", collection);
        return nullptr;
    }
    
    const auto &imgpak = data.pak_list[collection];

    if (!imgpak.handle) {
        image_data_touch(data.pak_list[collection]);
    }
    
    if (imgpak.handle) {
        // Check if pack loaded successfully (has at least one group)
        if (imgpak.handle->image_ids().size() == 0) {
            logs::error("pak_from_collection_id: pack %d (%s) loaded but has 0 groups - pack file may be missing or corrupted", 
                        collection, imgpak.name.c_str());
            return nullptr;
        }
        return imgpak.handle;
    }

    return nullptr;
}

int image_id_from_group(int collection, int group) {
    imagepak* pak = pak_from_collection_id(collection);
    if (pak == nullptr) {
        return -1;
    }

    int result = pak->get_global_image_index(group);
    if (result < 0) {
        logs::error("image_id_from_group: group %d not found in pack %d (pack has %d groups)", 
                    group, collection, pak->image_ids().size());
    }
    return result;
}

image_desc image_desc_from_name(const xstring &name) {
    bstring128 tname = name.c_str();

    svector<bstring128, 4> parts;
    string_to_array_t(parts, tname, '/');
    if (parts.size() > 1) {
        imagepak *pak = pak_from_collection_name(parts[0].c_str());
        if (pak) {
            return pak->get_image_desc(name);
        }
    }

    return image_desc{};
}

const image_t *image_get(image_desc desc) {
    int id = image_id_from_group(desc.pack, desc.id) + desc.offset;
    return image_get(id);
}

const image_t *image_next_close_get(image_desc desc, bool &last, int &last_index) {
    last = false;
    imagepak *pak = pak_from_collection_id(desc.pack);
    if (pak == nullptr) {
        return nullptr;
    }

    auto ids = pak->image_ids();
    svector<uint16_t, imagepak::PAK_GROUPS_MAX> sorted_ids;
    std::copy(ids.begin(), ids.end(), std::back_inserter(sorted_ids));
    const int start = ids[desc.id];

    std::sort(sorted_ids.begin(), sorted_ids.end());
    auto it = std::lower_bound(sorted_ids.begin(), sorted_ids.end(), start);
    if (it == sorted_ids.end()) {
        return nullptr;
    }

    if (*it == sorted_ids.back()) {
        last = true;
        last_index = pak->get_entry_count();
        return nullptr;
    }

    const int end = *(it + 1);

    return pak->get_image(end, true);
}

const image_t *image_get(int pak, int id, int offset) {
    auto& data = *g_image_data;
    if (pak >= data.pak_list.size()) {
        return nullptr;
    }

    auto &pakref = data.pak_list[pak];
    if (pakref.handle == nullptr) {
        pakref.handle = new imagepak(pak, pakref.name, pakref.index, pakref.system, false, pakref.custom);
        if (pakref.custom) {
            pakref.entries_num = pakref.handle->get_entry_count();
        }
    }

    if (pakref.handle != nullptr) {
        int img_id = pakref.handle->get_global_image_index(id) + offset;
        return pakref.handle->get_image(img_id, true);
    }

    return nullptr;
}

const image_t* image_get(int id) {
    if (id < 0) {
        return nullptr;
    }

    auto& data = *g_image_data;
    if (data.image_cache[id]) {
        return data.image_cache[id];
    }

    const image_t* img = nullptr;
    for (uint8_t pakidx = 1; pakidx < data.pak_list.size(); ++pakidx) {
        auto &pak = data.pak_list[pakidx];
        if (pak.index < 0) {
            break;
        }

        const bool is_pak_id = (id >= pak.index && id < pak.index + pak.entries_num);
        if (!is_pak_id) {
            continue;
        }

        if (pak.handle == nullptr) {
            pak.handle = new imagepak(pakidx, pak.name, pak.index, pak.system, false, pak.custom);
        }

        img = pak.handle->get_image(id);
        if (img != nullptr) {
            data.image_cache[id] = img;
            return img;
        }
    }

    // default (failure)
    data.image_cache[id] = data.pak_list[PACK_GENERAL].handle->get_image(98);
    return nullptr;
}

const image_t* image_letter(int letter_id) {
    auto& data = *g_image_data;
    auto fontpak = data.pak_list[PACK_FONT].handle;
    if (letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return image_get(letter_id);
    } else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        const int image_id = image_id_from_group(PACK_FONT, 1) + letter_id;
        return image_get(image_id);
    } else {
        return nullptr;
    }
}

const image_t* image_get_enemy(int type, int id) {
    auto& data = *g_image_data;
    return data.pak_list[type].handle->get_image(id);
}

const int image_t::isometric_size() const {
    return (width + 2) / TILE_WIDTH_PIXELS;
}
const int image_t::isometric_top_height() const {
    if (has_isometric_top)
        return height - (isometric_size() * TILE_HEIGHT_PIXELS);
    return 0;
}
const int image_t::isometric_3d_height() const {
    if (has_isometric_top)
        return isometric_box_height;
    return 0;
}

int terrain_ph_offset;