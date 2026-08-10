#include "bridge_grid.h"

#include "core/svector.h"
#include "core/vec2i.h"
#include "core/xstring.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "grid/grid.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"
#include "scenario/map.h"

#include <unordered_map>

const e_bridge_part_tokens_t ANK_CONFIG_ENUM(e_bridge_part_tokens);

grid_xx g_bridge_part_grid(FS_UINT16);
grid_xx g_bridge_part_grid_backup(FS_UINT16);
grid_xx g_bridge_type_grid(FS_UINT16);
grid_xx g_bridge_type_grid_backup(FS_UINT16);

struct bridge_part_draw_t {
    int part = 0;
    int img = 0;
    vec2i pos;
};

struct bridge_style_t {
    uint16_t index = 0;
    xstring type;
    image_desc desc;
    svector<bridge_part_draw_t, 16> parts;
};

static svector<bridge_style_t, 16> g_bridge_styles;
static std::unordered_map<xstring, uint16_t> g_bridge_style_by_type;

// Julius/C3 defaults if a style has no parts[] entry for this frame.
static bool bridge_part_draw_fallback(int part, int &img_offset, vec2i &pos) {
    switch ((e_bridge_part)part) {
    case BRIDGE_PART_RAMP_DIR_0: img_offset = 5; pos = {0, -20}; return true;
    case BRIDGE_PART_RAMP_DIR_2: img_offset = 0; pos = {-1, -8}; return true;
    case BRIDGE_PART_RAMP_DIR_4: img_offset = 3; pos = {0, -8}; return true;
    case BRIDGE_PART_RAMP_DIR_6: img_offset = 2; pos = {7, -20}; return true;
    case BRIDGE_PART_MID_NE_SW: img_offset = 4; pos = {0, -21}; return true;
    case BRIDGE_PART_MID_NW_SE: img_offset = 1; pos = {5, -21}; return true;
    case BRIDGE_PART_NONE:
    case BRIDGE_PART_MAX:
    default:
        return false;
    }
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_bridge_styles) {
    g_bridge_styles.clear();
    g_bridge_style_by_type.clear();
    g_config_arch.r_array("bridge_styles", [] (archive arch) {
        bridge_style_t style;
        style.index = (uint16_t)arch.r_int("index");
        style.type = arch.r_string("type");

        if (!arch.r_desc_impl(style.desc) || !style.desc.valid()) {
            style.desc.pack = (int16_t)arch.r_int("pack");
            style.desc.id = (int16_t)arch.r_int("id");
            style.desc.offset = (int16_t)arch.r_int("offset");
        }
        if (!style.desc.valid()) {
            return;
        }

        arch.r_array("parts", [&] (archive part_arch) {
            bridge_part_draw_t part;
            part.part = part_arch.r_int("part");
            part.img = part_arch.r_int("img");
            part.pos = part_arch.r_vec2i("pos");
            if (part.part > 0) {
                style.parts.push_back(part);
            }
        });

        g_bridge_styles.push_back(style);
        if (!style.type.empty()) {
            g_bridge_style_by_type[style.type] = style.index;
        }
    });
}

uint16_t bridge_style_index(pcstr type) {
    if (!type || !*type) {
        return 0;
    }
    auto it = g_bridge_style_by_type.find(type);
    if (it != g_bridge_style_by_type.end()) {
        return it->second;
    }
    return 0;
}

int bridge_style_image_base(uint16_t type) {
    for (auto &style : g_bridge_styles) {
        if (style.index == type && style.desc.valid()) {
            return style.desc.tid();
        }
    }
    return image_id_from_group(GROUP_BUILDING_BRIDGE);
}

bool bridge_style_part_draw(uint16_t type, int part, int &img_offset, vec2i &pos) {
    for (const auto &style : g_bridge_styles) {
        if (style.index != type) {
            continue;
        }
        for (const auto &p : style.parts) {
            if (p.part == part) {
                img_offset = p.img;
                pos = p.pos;
                return true;
            }
        }
        break;
    }
    return bridge_part_draw_fallback(part, img_offset, pos);
}

int map_bridge_part_at(int grid_offset) {
    return map_grid_get(g_bridge_part_grid, grid_offset);
}

void map_bridge_part_set(int grid_offset, int value) {
    map_grid_set(g_bridge_part_grid, grid_offset, value);
}

uint16_t map_bridge_type_at(int grid_offset) {
    return (uint16_t)map_grid_get(g_bridge_type_grid, grid_offset);
}

void map_bridge_type_set(int grid_offset, uint16_t value) {
    map_grid_set(g_bridge_type_grid, grid_offset, value);
}

void map_bridge_tile_clear(int grid_offset) {
    map_grid_set(g_bridge_part_grid, grid_offset, 0);
    map_grid_set(g_bridge_type_grid, grid_offset, 0);
}

void map_bridge_grids_clear() {
    map_grid_clear(g_bridge_part_grid);
    map_grid_clear(g_bridge_type_grid);
}

void map_bridge_grids_backup() {
    map_grid_copy(g_bridge_part_grid, g_bridge_part_grid_backup);
    map_grid_copy(g_bridge_type_grid, g_bridge_type_grid_backup);
}

void map_bridge_grids_restore() {
    map_grid_copy(g_bridge_part_grid_backup, g_bridge_part_grid);
    map_grid_copy(g_bridge_type_grid_backup, g_bridge_type_grid);
}

void map_bridge_migrate_from_sprite() {
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
                continue;
            }
            if (map_bridge_part_at(grid_offset) != 0) {
                continue;
            }
            const int sprite = map_sprite_animation_at(grid_offset);
            if (sprite >= 1 && sprite <= 15) {
                map_bridge_part_set(grid_offset, sprite);
                map_bridge_type_set(grid_offset, 0);
            }
        }
    }
}

// Both bridge grids default to empty: saves older than v171 keep bridges in the
// sprite grid, and map_bridge_migrate_from_sprite() rebuilds them during post_load.
io_buffer *iob_bridge_part_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_bridge_part_grid);
}, [] (size_t version) {
    map_grid_clear(g_bridge_part_grid);
});

io_buffer *iob_bridge_type_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_bridge_type_grid);
}, [] (size_t version) {
    map_grid_clear(g_bridge_type_grid);
});
