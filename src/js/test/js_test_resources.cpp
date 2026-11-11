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

#include <cstdio>
#include <filesystem>
#include <string>

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
