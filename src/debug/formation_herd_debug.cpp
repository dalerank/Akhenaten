#include "core/app.h"
#include "dev/debug.h"

#include "core/calc.h"
#include "figure/formation.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "grid/hyena_strength.h"

#include <vector>

static tile2i herd_spawn_point(const formation *m) {
    // herd_point is the mission-script herd id, not a slot in herd_points_predator — the
    // formation itself carries the tile the herd was created on.
    return m->home.valid() ? m->home : m->tile;
}

static void draw_animal_spawn_tile(vec2i pixel, tile2i point, painter &ctx) {
    int formation_id = 0;

    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m->in_use || !m->is_herd) {
            continue;
        }

        tile2i spawn_point = herd_spawn_point(m);
        if (!spawn_point.valid()) {
            continue;
        }

        if (calc_maximum_distance(point, spawn_point) <= m->reseach_radius) {
            formation_id = m->id;
            break;
        }
    }

    if (formation_id > 0) {
        ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, COLOR_MASK_GREEN_10);
        char str[32];
        snprintf(str, sizeof(str), "%d", formation_id);
        debug_text_a(ctx, str, pixel.x + 15, pixel.y + 15, 0, str, COLOR_BLACK, FONT_SMALL_PLAIN);
    }
}

struct spawn_area_data_t {
    tile2i spawn_point;
    int radius;
};

static void draw_animal_spawn_area(painter &ctx) {
    std::vector<spawn_area_data_t> areas;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m->in_use || !m->is_herd) {
            continue;
        }

        tile2i spawn_point = herd_spawn_point(m);
        if (!spawn_point.valid() || m->reseach_radius <= 0) {
            continue;
        }

        areas.push_back({spawn_point, m->reseach_radius});
    }

    g_camera.foreach_valid_map_tile(ctx, [&](vec2i pixel, tile2i tile, painter &tile_ctx) {
        for (const auto &area : areas) {
            if (calc_maximum_distance(tile, area.spawn_point) <= area.radius) {
                tile_ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, COLOR_MASK_BLUE);
                break;
            }
        }
    });
}

static void draw_hyena_strength_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_hyena_strength_get(point.grid_offset());
    if (!d)
        return;

    char str[64];
    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel, 0x80000000);
    snprintf(str, 30, "%d", d);
    text_draw(str, pixel.x + 15, pixel.y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);
}

void ANK_REGISTER_APPLICATION_MODULE(register_animal_spawn_debug) {
    g_debug.add_tile_render_handler("animal_spawn", draw_animal_spawn_tile);
    g_debug.add_tile_render_handler("hyena_strength", draw_hyena_strength_tile);
    g_debug.add_render_handler("animal_spawn_area", draw_animal_spawn_area);
}
