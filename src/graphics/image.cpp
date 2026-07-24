#include "image.h"
#include "font.h"
#include "image_groups.h"
#include "content/imagepak.h"
#include "graphics/image_desc.h"
#include "graphics/imagepak_holder.h"
#include "content/dir.h"
#include "core/svector.h"
#include "core/log.h"
#include "core/profiler.h"
#include "platform/arguments.h"

#include <SDL.h>

#include <algorithm>
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
    image_ensure_pak_loaded(h.id);
}

bool image_data_fonts_ready() {
    return g_image_data && g_image_data->fonts_loaded;
}

bool image_data_render_on_new_loadpacks() {
    return g_image_data && g_image_data->allow_updata_on_load;
}

static void image_dequeue_pak(int pak_id) {
    if (!g_image_data) {
        return;
    }

    auto &queue = g_image_data->load_queue;
    const auto it = std::find(queue.begin(), queue.end(), pak_id);
    if (it == queue.end()) {
        return;
    }

    queue.erase(it);
    if (g_args.is_log_resources()) {
        logs::info("VFS: pak-queue: dequeue on sync id=%d queue_size=%zu", pak_id, queue.size());
    }
}

static int image_find_pak_id_by_name(const xstring &name) {
    if (!g_image_data || name.empty()) {
        return -1;
    }

    xstring key = xstring(name).tolower();

    for (size_t i = 0; i < g_image_data->pak_list.size(); ++i) {
        const auto &pak = g_image_data->pak_list[i];
        if (pak.name.empty()) {
            continue;
        }
        if (pak.name == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

static bool image_pak_load_succeeded(const imagepak *pak) {
    if (!pak) {
        return false;
    }
    if (g_args.no_resource()) {
        return true;
    }
    return !pak->atlas_pages.empty();
}

bool image_pak_is_loaded(int pak_id) {
    if (!g_image_data || pak_id < 0 || pak_id >= static_cast<int>(g_image_data->pak_list.size())) {
        return false;
    }
    const auto &pak = g_image_data->pak_list[pak_id];
    return pak.handle != nullptr && pak.load_status == IMAGEPAK_LOAD_LOADED;
}

bool image_pak_is_loaded(const xstring &name) {
    return image_pak_is_loaded(image_find_pak_id_by_name(name));
}

bool image_ensure_pak_loaded(int pak_id) {
    OZZY_PROFILER_FUNCTION();

    if (!g_image_data || pak_id < 0 || pak_id >= static_cast<int>(g_image_data->pak_list.size())) {
        return false;
    }

    auto &pak = g_image_data->pak_list[pak_id];
    if (pak.name.empty() && pak.handle == nullptr) {
        return false;
    }

    if (pak.load_status == IMAGEPAK_LOAD_LOADED && pak.handle != nullptr) {
        return true;
    }

    if (pak.load_status == IMAGEPAK_LOAD_LOADING) {
        return false;
    }

    if (pak.handle != nullptr && pak.load_status != IMAGEPAK_LOAD_FAILED) {
        if (pak.entries_num == 0) {
            pak.entries_num = pak.handle->get_entry_count();
        }
        pak.load_status = IMAGEPAK_LOAD_LOADED;
        image_dequeue_pak(pak_id);
        return true;
    }

    const bool was_queued = pak.load_status == IMAGEPAK_LOAD_QUEUED;
    if (was_queued) {
        image_dequeue_pak(pak_id);
        logs::info("VFS: pak-queue: sync load id=%d name=%s", pak_id, pak.name.c_str());
    }

    pak.load_status = IMAGEPAK_LOAD_LOADING;
    const Uint32 t0 = SDL_GetTicks();

    delete pak.handle;
    pak.handle = new imagepak(static_cast<uint8_t>(pak_id), pak.name, pak.index, pak.system, false, pak.custom);

    if (!image_pak_load_succeeded(pak.handle)) {
        logs::warn("VFS: pak-queue: fail id=%d name=%s", pak_id, pak.name.c_str());
        delete pak.handle;
        pak.handle = nullptr;
        pak.load_status = IMAGEPAK_LOAD_FAILED;
        return false;
    }

    pak.entries_num = pak.handle->get_entry_count();
    pak.load_status = IMAGEPAK_LOAD_LOADED;

    const Uint32 elapsed = SDL_GetTicks() - t0;
    logs::info("VFS: pak-queue: done id=%d name=%s entries=%u pages=%zu ms=%u",
               pak_id, pak.name.c_str(), pak.entries_num, pak.handle->atlas_pages.size(), elapsed);
    return true;
}

bool image_request_pak(int pak_id) {
    if (!g_image_data || pak_id < 0 || pak_id >= static_cast<int>(g_image_data->pak_list.size())) {
        return false;
    }

    auto &pak = g_image_data->pak_list[pak_id];
    if (pak.name.empty()) {
        return false;
    }

    if (pak.load_status == IMAGEPAK_LOAD_LOADED && pak.handle != nullptr) {
        if (g_args.is_log_resources()) {
            logs::info("VFS: pak-queue: already loaded id=%d name=%s", pak_id, pak.name.c_str());
        }
        return true;
    }

    if (pak.load_status == IMAGEPAK_LOAD_QUEUED || pak.load_status == IMAGEPAK_LOAD_LOADING) {
        if (g_args.is_log_resources()) {
            logs::info("VFS: pak-queue: already queued id=%d name=%s status=%d",
                       pak_id, pak.name.c_str(), static_cast<int>(pak.load_status));
        }
        return true;
    }

    pak.load_status = IMAGEPAK_LOAD_QUEUED;
    g_image_data->load_queue.push_back(pak_id);
    logs::info("VFS: pak-queue: enqueued id=%d name=%s queue_size=%zu",
               pak_id, pak.name.c_str(), g_image_data->load_queue.size());
    return true;
}

bool image_request_pak(const xstring &name) {
    const int pak_id = image_find_pak_id_by_name(name);
    if (pak_id < 0) {
        logs::warn("VFS: pak-queue: request unknown name=%s", name.c_str());
        return false;
    }
    return image_request_pak(pak_id);
}

void image_paks_pump() {
    if (!g_image_data || !g_image_data->common_inited) {
        return;
    }

    auto &queue = g_image_data->load_queue;
    if (queue.empty()) {
        return;
    }

    const int pak_id = queue.front();
    queue.erase(queue.begin());

    if (pak_id < 0 || pak_id >= static_cast<int>(g_image_data->pak_list.size())) {
        return;
    }

    auto &pak = g_image_data->pak_list[pak_id];
    if (pak.load_status == IMAGEPAK_LOAD_LOADED && pak.handle != nullptr) {
        return;
    }
    if (pak.load_status == IMAGEPAK_LOAD_LOADING) {
        return;
    }

    // Already removed from queue; avoid "sync load" log inside ensure.
    pak.load_status = IMAGEPAK_LOAD_IDLE;
    logs::info("VFS: pak-queue: pump start id=%d name=%s", pak_id, pak.name.c_str());
    image_ensure_pak_loaded(pak_id);
}

bool image_load_paks() {
    auto& data = *g_image_data;
    data.fonts_loaded = false;
    data.allow_updata_on_load = true;
    data.font_base_offset = 0;
    data.load_queue.clear();

    auto &fontpack = data.pak_list[PACK_FONT];
    if (!fontpack.handle) {
        fontpack.handle = new imagepak(PACK_FONT, "Pharaoh_Fonts", 18765, false, true);
        fontpack.entries_num = fontpack.handle->get_entry_count();
        fontpack.index = fontpack.handle->global_image_index_offset;
        fontpack.id = PACK_FONT;
        if (image_pak_load_succeeded(fontpack.handle)) {
            fontpack.load_status = IMAGEPAK_LOAD_LOADED;
        } else {
            delete fontpack.handle;
            fontpack.handle = nullptr;
            fontpack.load_status = IMAGEPAK_LOAD_FAILED;
        }
    } else {
        fontpack.load_status = IMAGEPAK_LOAD_LOADED;
    }
    data.fonts_loaded = fontpack.load_status == IMAGEPAK_LOAD_LOADED;

    for (uint8_t pakidx = 0; pakidx < g_image_data->pak_list.size(); ++pakidx) {
        auto &imgpak = g_image_data->pak_list[pakidx];
        if (imgpak.name.empty()) {
            continue;
        }

        imagepak::useridx_update(pakidx);

        const int pack_entries = imagepak::get_entries_num(imgpak.name, imgpak.system);
        if (pack_entries > 0) {
            imgpak.entries_num = pack_entries;
            imagepak::update_max_imgid(imgpak.index + imgpak.entries_num);
        }

        if (imgpak.delayed) {
            continue;
        }

        // Already loaded early (sync ensure before image_load_paks) — do not reload.
        if (imgpak.handle && imgpak.load_status == IMAGEPAK_LOAD_LOADED) {
            if (g_args.is_log_resources()) {
                logs::info("VFS: Pack %d (%s) already loaded - %d groups, %d entries",
                           pakidx, imgpak.name.c_str(), imgpak.handle->image_ids().size(), imgpak.entries_num);
            }
            continue;
        }

        delete imgpak.handle;
        imgpak.handle = new imagepak(pakidx, imgpak.name, imgpak.index, imgpak.system, false, imgpak.custom);
        if (image_pak_load_succeeded(imgpak.handle)) {
            imgpak.entries_num = imgpak.handle->get_entry_count();
            imgpak.load_status = IMAGEPAK_LOAD_LOADED;
        } else {
            delete imgpak.handle;
            imgpak.handle = nullptr;
            imgpak.load_status = IMAGEPAK_LOAD_FAILED;
        }

        if (g_args.is_log_resources()) {
            if (imgpak.handle) {
                logs::info("VFS: Pack %d (%s) loaded - %d groups, %d entries",
                           pakidx, imgpak.name.c_str(), imgpak.handle->image_ids().size(), imgpak.entries_num);
            } else {
                logs::warn("VFS: Pack %d (%s) failed to load", pakidx, imgpak.name.c_str());
            }
        }

        if (imgpak.handle && imgpak.handle->image_ids().size() == 0) {
            logs::warn("image_load_paks: pack %d (%s) loaded but has 0 groups", pakidx, imgpak.name.c_str());
        }
    }

    data.allow_updata_on_load = false;

    if (!data.fonts_loaded) {
        font_enable_sg3_fallback();
    }

    return true;
}

static imagepak* pak_from_collection_name(const xstring &name) {
    const int pak_id = image_find_pak_id_by_name(name);
    if (pak_id < 0) {
        return nullptr;
    }

    if (!image_ensure_pak_loaded(pak_id)) {
        return nullptr;
    }

    return g_image_data->pak_list[pak_id].handle;
}

static imagepak* pak_from_collection_id(int collection) {
    auto& data = *g_image_data;
    if (collection < 0 || collection >= static_cast<int>(data.pak_list.size())) {
        logs::error("pak_from_collection_id: invalid collection %d", collection);
        return nullptr;
    }

    if (!image_ensure_pak_loaded(collection)) {
        return nullptr;
    }

    const auto &imgpak = data.pak_list[collection];
    if (g_args.no_resource()) {
        return imgpak.handle;
    }

    if (imgpak.handle->image_ids().size() == 0) {
        logs::error("pak_from_collection_id: pack %d (%s) loaded but has 0 groups - pack file may be missing or corrupted",
                    collection, imgpak.name.c_str());
        return nullptr;
    }
    return imgpak.handle;
}

int image_id_from_group(int collection, int group) {
    imagepak* pak = pak_from_collection_id(collection);
    if (pak == nullptr) {
        return -1;
    }

    if (g_args.no_resource()) {
        return 0;
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
    if (pak < 0 || pak >= static_cast<int>(data.pak_list.size())) {
        return nullptr;
    }

    if (!image_ensure_pak_loaded(pak)) {
        return nullptr;
    }

    auto &pakref = data.pak_list[pak];
    int img_id = pakref.handle->get_global_image_index(id) + offset;
    return pakref.handle->get_image(img_id, true);
}

const image_t* image_get(int id) {
    OZZY_PROFILER_FUNCTION();

    if (id < 0) {
        return nullptr;
    }

    auto& data = *g_image_data;
    if (static_cast<size_t>(id) >= data.image_cache.size()) {
        return nullptr;
    }

    if (data.image_cache[id]) {
        return data.image_cache[id];
    }

    const image_t* img = nullptr;
    for (uint8_t pakidx = 1; pakidx < data.pak_list.size(); ++pakidx) {
        auto &pak = data.pak_list[pakidx];
        if (pak.index < 0) {
            continue;
        }

        const bool is_pak_id = (id >= pak.index && id < pak.index + static_cast<int>(pak.entries_num));
        if (!is_pak_id) {
            continue;
        }

        if (!image_ensure_pak_loaded(pakidx)) {
            continue;
        }

        img = pak.handle->get_image(id);
        if (img != nullptr) {
            data.image_cache[id] = img;
            return img;
        }
    }

    // default (failure)
    if (data.pak_list[PACK_GENERAL].handle) {
        data.image_cache[id] = data.pak_list[PACK_GENERAL].handle->get_image(98);
    }
    return nullptr;
}

const image_t* image_letter(int letter_id) {
    auto& data = *g_image_data;
    auto fontpak = data.pak_list[PACK_FONT].handle;
    if (letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET) {
        return image_get(letter_id);
    }

    if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET) {
        const int image_id = image_id_from_group(PACK_FONT, 1) + letter_id;
        return image_get(image_id);
    }

    return nullptr;
}

const image_t* image_get_enemy(int type, int id) {
    auto& data = *g_image_data;
    return data.pak_list[type].handle->get_image(id);
}

int image_t::isometric_size() const {
    return (width + 2) / TILE_WIDTH_PIXELS;
}

int image_t::calc_isometric_top_height() const {
    if (has_isometric_top)
        return height - (isometric_size() * TILE_HEIGHT_PIXELS);

    return 0;
}

int image_t::isometric_3d_height() const {
    if (has_isometric_top)
        return isometric_box_height;
    return 0;
}
