#include "image.h"
#include "font.h"
#include "image_groups.h"
#include "content/imagepak.h"
#include "graphics/image_desc.h"
#include "graphics/imagepak_holder.h"
#include "content/dir.h"
#include "core/svector.h"

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

bool image_set_font_pak(encoding_type encoding) {
    auto& data = *g_image_data;
    // TODO?
    if (encoding == ENCODING_CYRILLIC) {
        return false;
    } else if (encoding == ENCODING_TRADITIONAL_CHINESE) {
        return false;
    } else if (encoding == ENCODING_SIMPLIFIED_CHINESE) {
        return false;
    } else if (encoding == ENCODING_KOREAN) {
        return false;
    } else {
        //        free(data.font);
        //        free(data.font_data);
        //        data.font = 0;
        //        data.font_data = 0;
        data.fonts_enabled = NO_EXTRA_FONT;
        return true;
    }
}

bool image_data_fonts_ready() {
    return g_image_data && g_image_data->fonts_loaded;
}

//bool image_set_enemy_pak(int enemy_id) {
//    auto& data = *g_image_data;
//    return set_pak_in_collection(enemy_id, &data.enemy, &data.enemy_paks);
//}
//bool image_set_temple_complex_pak(int temple_id) {
//    auto& data = *g_image_data;
//    return set_pak_in_collection(temple_id, &data.temple, &data.temple_paks);
//}
//bool image_set_monument_pak(int monument_id) {
//    auto& data = *g_image_data;
//    return set_pak_in_collection(monument_id, &data.monument, &data.monument_paks);
//}

bool image_load_paks() {
    auto& data = *g_image_data;
    data.fonts_enabled = false;
    data.fonts_loaded = false;
    data.font_base_offset = 0;

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
    data.font = new imagepak("Pharaoh_Fonts", 18765, false, true); // 18765 --> 20305
    data.pak_list.push_back(&data.font);
    data.fonts_loaded = true;

    for (auto &imgpak : g_image_data->common) {
        if (imgpak.name.empty()) {
            continue;
        }

        imgpak.entries_num = imagepak::get_entries_num(imgpak.name);
        if (imgpak.delayed) {
            continue;
        }

        auto *newpak = new imagepak(imgpak.name, imgpak.index, imgpak.system, false, imgpak.custom);
        data.common[imgpak.id].handle = newpak;
        data.pak_list.push_back(&data.common[imgpak.id].handle);
    }

    auto folders = vfs::dir_find_all_subdirectories("Data/", true);
    for (const auto &f : folders) {
        auto *newpak = new imagepak(f.c_str(), 0, false, false, /*custom*/true);
        if (!newpak->get_entry_count()) {
            delete newpak;
            continue;
        }
        int useridx = newpak->get_user_idx();
        data.common[useridx].handle = newpak;
        data.common[useridx].id = useridx;
        data.common[useridx].index = newpak->get_global_image_index(0);
        data.common[useridx].custom = true;
        data.pak_list.push_back(&data.common[useridx].handle);
    }

    return true;
}

static imagepak* pak_from_collection_id(int collection, int pak_cache_idx) {
    auto& data = *g_image_data;
    if (collection == PACK_FONT) {
        return data.font;
    }

    auto handle = g_image_data->common[collection].handle;
    if (handle) {
        return handle;
    }

    return nullptr;
}

int image_group(image_desc desc) {
    return image_id_from_group(desc.pack, desc.id) + desc.offset;
}

int image_id_from_group(int collection, int group, int pak_cache_idx) {
    imagepak* pak = pak_from_collection_id(collection, pak_cache_idx);
    if (pak == nullptr) {
        return -1;
    }
    return pak->get_global_image_index(group);
}

const image_t *image_get(image_desc desc) {
    int id = image_id_from_group(desc.pack, desc.id) + desc.offset;
    return image_get(id);
}

const image_t *image_next_close_get(image_desc desc, bool &last, int &last_index) {
    last = false;
    imagepak *pak = pak_from_collection_id(desc.pack, -1);
    if (pak == nullptr) {
        return nullptr;
    }

    auto ids = pak->image_ids();
    svector<uint16_t, PAK_GROUPS_MAX> sorted_ids;
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

const image_t *image_get(int pak, int id) {
    auto& data = *g_image_data;
    if (pak >= data.common.size()) {
        return nullptr;
    }
    const image_t* img = nullptr;
    auto pakptr = data.common[pak].handle;
    if (pakptr != nullptr) {
        return pakptr->get_image(id);
    }

    return nullptr;
}

const image_t* image_get(int id) {
    auto& data = *g_image_data;
    const image_t* img;
    for (auto &pak: data.pak_list) {
        if (*pak == nullptr) {
            continue;
        }

        img = (*pak)->get_image(id);
        if (img != nullptr) {
            return img;
        }
    }
    // default (failure)
    return nullptr;
}

const image_t* image_letter(int letter_id) {
    auto& data = *g_image_data;
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT) {
        return data.font->get_image(data.font_base_offset + letter_id);
    } else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return data.font->get_image(data.font_base_offset + letter_id - IMAGE_FONT_MULTIBYTE_OFFSET);
    } else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        return image_get(image_id_from_group(GROUP_FONT) + letter_id);
    } else {
        return nullptr;
    }
}

const image_t* image_get_enemy(int type, int id) {
    auto& data = *g_image_data;
    return data.common[type].handle->get_image(id);
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