#include "js/test/js_test_common.h"

#include "content/content.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "graphics/image.h"
#include "graphics/imagepak_holder.h"
#include "grid/gardens.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "platform/arguments.h"
#include "platform/platform.h"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <string>
#include <thread>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

static pcstr __test_data_dir() {
    return vfs::platform_file_manager_get_base_path();
}
ANK_FUNCTION(__test_data_dir);

static bool __test_data_dir_from_cli() {
    return g_args.is("data_directory_cli", false);
}
ANK_FUNCTION(__test_data_dir_from_cli);

static int __test_paks_loaded() {
    return image_paks_loaded_count();
}
ANK_FUNCTION(__test_paks_loaded);

static bool __test_pak_loaded(pcstr name) {
    return image_pak_is_loaded(xstring(name));
}
ANK_FUNCTION_1(__test_pak_loaded);

// Hash of what the simulation reads from a tile: terrain, property bits and whether an image is assigned.
// The image id itself is art and differs with and without data.
static int __test_map_sim_state_hash(int x0, int y0, int x1, int y1) {
    uint32_t h = 2166136261u;
    auto mix = [&h](uint32_t v) {
        for (int i = 0; i < 4; ++i) {
            h = (h ^ ((v >> (i * 8)) & 0xFF)) * 16777619u;
        }
    };
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            const tile2i tile(x, y);
            if (!map_grid_is_inside(tile, 1)) {
                continue;
            }
            mix((uint32_t)map_terrain_get(tile));
            mix((uint32_t)map_property_get(tile));
            mix(map_image_at(tile) != 0 ? 1u : 0u);
        }
    }
    return (int)(h & 0x7FFFFFFF);
}
ANK_FUNCTION_4(__test_map_sim_state_hash);

static void __test_tiles_update_all_rocks() {
    map_tiles_update_all_rocks();
}
ANK_FUNCTION(__test_tiles_update_all_rocks);

static void __test_tiles_update_all_dunes() {
    map_tiles_update_all_dunes();
}
ANK_FUNCTION(__test_tiles_update_all_dunes);

static void __test_gardens_update_all() {
    map_tiles_gardens_update_all();
}
ANK_FUNCTION(__test_gardens_update_all);

static int test_pak_id(pcstr name) {
    const xstring key = xstring(name).tolower();
    for (size_t i = 0; i < g_image_data->pak_list.size(); ++i) {
        if (g_image_data->pak_list[i].name == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

static bool __test_image_exists(int id) {
    return image_get(id) != nullptr;
}
ANK_FUNCTION_1(__test_image_exists);

static bool __test_image_cached(int id) {
    return id >= 0 && static_cast<size_t>(id) < g_image_data->image_cache.size()
           && g_image_data->image_cache[id] != nullptr;
}
ANK_FUNCTION_1(__test_image_cached);

static int __test_pak_first_image(pcstr name) {
    const int pak_id = test_pak_id(name);
    return pak_id < 0 ? -1 : g_image_data->pak_list[pak_id].index;
}
ANK_FUNCTION_1(__test_pak_first_image);

static void __test_image_unload_pak(pcstr name) {
    image_unload_pak(test_pak_id(name));
}
ANK_FUNCTION_1(__test_image_unload_pak);

static int __test_image_id_from_group(int pack, int group, int offset) {
    return image_id_from_group(pack, group, offset);
}
ANK_FUNCTION_3(__test_image_id_from_group);

// Loads a pack the way a render worker would: must only queue the request, never load off the main thread.
static bool __test_pak_ensure_from_worker(pcstr name) {
    const int pak_id = test_pak_id(name);
    if (pak_id < 0) {
        return false;
    }
    image_unload_pak(pak_id);
    bool worker_result = true;
    std::thread worker([&] { worker_result = image_ensure_pak_loaded(pak_id); });
    worker.join();

    const auto& pak = g_image_data->pak_list[pak_id];
    bool queued = false;
    {
        std::scoped_lock lock(g_image_data->worker_requests_mutex);
        const auto& requests = g_image_data->worker_requests;
        queued = std::find(requests.begin(), requests.end(), pak_id) != requests.end();
    }
    return !worker_result && pak.handle == nullptr && pak.load_status == IMAGEPAK_LOAD_IDLE && queued;
}
ANK_FUNCTION_1(__test_pak_ensure_from_worker);

// An independent view of a UTF-8 path: on Windows through the wide API, so a narrow call that went
// through the ANSI code page (instead of UTF-8) shows up as a missing file.
static std::filesystem::path test_native_path(pcstr utf8) {
#if defined(_WIN32)
    const int n = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
    std::wstring wide(n > 0 ? n - 1 : 0, L' ');
    if (n > 1) {
        MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide.data(), n);
    }
    return std::filesystem::path(wide);
#else
    return std::filesystem::path(utf8);
#endif
}

// Cyrillic "test" / "file.txt" in UTF-8.
static bool __test_vfs_utf8_roundtrip() {
    const vfs::path dir(platform.user_directory(), "/utf8_probe_\xD1\x82\xD0\xB5\xD1\x81\xD1\x82");
    const vfs::path file(dir, "/\xD1\x84\xD0\xB0\xD0\xB9\xD0\xBB.txt");
    std::error_code ec;
    std::filesystem::create_directories(test_native_path(dir.c_str()), ec);

    FILE* f = vfs::file_open_os(file, "wb");
    if (!f) {
        return false;
    }
    std::fputs("ok", f);
    std::fclose(f);

    const bool native_exists = std::filesystem::exists(test_native_path(file.c_str()), ec);
    const bool vfs_exists = vfs::file_exists(file);
    std::filesystem::remove_all(test_native_path(dir.c_str()), ec);
    return native_exists && vfs_exists;
}
ANK_FUNCTION(__test_vfs_utf8_roundtrip);

// A file on disk as "Data/SprMain.SG3" must be found when the game asks for "data/sprmain.sg3".
static bool __test_vfs_case_probe() {
    namespace fs = std::filesystem;
    std::error_code ec;
    const xstring saved_base = vfs::platform_file_manager_get_base_path();
    const vfs::path root(platform.user_directory(), "/case_probe");
    fs::remove_all(root.c_str(), ec);
    fs::create_directories(fs::path(root.c_str()) / "Data" / "Sub", ec);
    {
        FILE* f = std::fopen((fs::path(root.c_str()) / "Data" / "Sub" / "SprMain.SG3").string().c_str(), "wb");
        if (f) {
            std::fclose(f);
        }
    }

    vfs::platform_file_manager_set_base_path(root.c_str());
    const vfs::path found = vfs::content_path("data/sub/sprmain.sg3");
    const vfs::path missing = vfs::content_path("data/sub/nothing.sg3");
    const bool ok = fs::exists(found.c_str(), ec) && !fs::exists(missing.c_str(), ec);

    vfs::platform_file_manager_set_base_path(saved_base.c_str());
    vfs::content_cache_paths();
    fs::remove_all(root.c_str(), ec);
    return ok;
}
ANK_FUNCTION(__test_vfs_case_probe);

static int __test_vfs_path_len(int n) {
    const std::string s(n, 'a');
    const vfs::path p(s.c_str());
    return (int)p.len();
}
ANK_FUNCTION_1(__test_vfs_path_len);
