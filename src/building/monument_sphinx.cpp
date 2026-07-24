#include "monument_sphinx.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "construction/build_planner.h"
#include "core/profiler.h"
#include "game/game.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/property.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sphinx);

// TODO(orig-data): stub resource counts — replace from original .pak when known.
struct monument_sphinx_cfg : public monument {
    monument_sphinx_cfg() : monument{BUILDING_SPHINX} {
        // phase 0–1: timber scaffolding / architects
        phases.push_back({0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}});
        phases.push_back({1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}});
        // phase 2–5: carving (stonemasons + timber as needed)
        phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}});
        phases.push_back({3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 600}});
        phases.push_back({4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}});
        phases.push_back({5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 200}});
        // phase 6: finishing / painting (artisans — paint + clay)
        phases.push_back({6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_PAINT, 400}, {RESOURCE_CLAY, 400}});
        // phase 7: pre-finish
        phases.push_back({7, monument_phase_resource{RESOURCE_NONE, 0}});
    }
} g_monument_sphinx;

static const building_sphinx::base_params &sphinx_params() {
    return (const building_sphinx::base_params &)building_sphinx::current_params();
}

static vec2i part_offset(const svector<vec2i, 4> &offsets, int rotation, vec2i fallback) {
    if (offsets.size() >= 4) {
        return offsets[rotation % 4];
    }
    return fallback;
}

int building_sphinx::art_stage() const {
    const int p = runtime_data().phase; // int8_t: FINISHED == -1
    if (p == MONUMENT_FINISHED || p >= 6) {
        return 6;
    }
    if (p <= 1) {
        return 1;
    }
    return p;
}

xstring building_sphinx::anim_key_for(int stage, int part, int orient_idx) const {
    static const char part_letter[] = {'a', 'b', 'c'};
    if (part < 0 || part > 2) {
        part = 0;
    }
    if (orient_idx < 0 || orient_idx > 1) {
        orient_idx = 0;
    }
    if (stage < 1) {
        stage = 1;
    }
    if (stage > 6) {
        stage = 6;
    }
    bstring32 key;
    key.printf("s%d%c%d", stage, part_letter[part], orient_idx + 1);
    return xstring(key.c_str());
}

const monument &building_sphinx::config() const {
    return g_monument_sphinx;
}

bool building_sphinx::needs_resources() const {
    if (is_finished()) {
        return false;
    }
    auto &d = runtime_data();
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        if (needs_resource(r) <= 0) {
            continue;
        }
        if (d.resources_pct[r] < 100) {
            return true;
        }
    }
    return false;
}

bool building_sphinx::need_stonemason() {
    if (is_finished() || !is_main()) {
        return false;
    }
    const int p = runtime_data().phase;
    // Carving stages (art 2–5 / phase 2–5)
    return p >= 2 && p <= 5;
}

bool building_sphinx::need_workers() const {
    if (!is_main()) {
        return false;
    }
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

int building_sphinx::building_image_get() const {
    const int part = runtime_data().variant;
    const int stage = art_stage();
    const int orient_idx = (g_camera.orientation / 2) % 2;
    const xstring key = anim_key_for(stage, part, orient_idx);
    const int img = current_params().first_img(key);
    if (img > 0) {
        return img;
    }
    // Fallback to preview / first diag of stage1 part a
    return current_params().first_img("preview");
}

void building_sphinx::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &bp = sphinx_params();
    vec2i init_tiles = bp.init_tiles;
    if (init_tiles.x <= 0 || init_tiles.y <= 0) {
        init_tiles = vec2i{6, 18};
    }

    switch (g_camera.orientation / 2) {
    case 0:
        planer.init_tiles(init_tiles.y, init_tiles.x);
        break;
    case 1:
        planer.init_tiles(init_tiles.x, init_tiles.y);
        break;
    case 2:
        planer.init_tiles(init_tiles.y, init_tiles.x);
        break;
    case 3:
        planer.init_tiles(init_tiles.x, init_tiles.y);
        break;
    }
}

void building_sphinx::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &bp = sphinx_params();
    const int rotation = building_rotation_global_rotation() % 4;
    const int size = params.building_size > 0 ? params.building_size : 6;

    const vec2i off_b = part_offset(bp.part_b_offset, rotation, vec2i{0, 6});
    const vec2i off_c = part_offset(bp.part_c_offset, rotation, vec2i{0, 12});

    tile2i tile_b = end.shifted(off_b);
    tile2i tile_c = end.shifted(off_c);

    blocked_tile_vec blocked_a, blocked_b, blocked_c;
    bool blocked = false;
    blocked |= !!planer.is_blocked_for_building(end, size, blocked_a);
    blocked |= !!planer.is_blocked_for_building(tile_b, size, blocked_b);
    blocked |= !!planer.is_blocked_for_building(tile_c, size, blocked_c);

    const int img_a = params.first_img("s1a1");
    const int img_b = params.first_img("s1b1");
    const int img_c = params.first_img("s1c1");
    const int preview = params.first_img("preview");

    if (blocked) {
        planer.draw_partially_blocked(ctx, false, blocked_a);
        planer.draw_partially_blocked(ctx, false, blocked_b);
        planer.draw_partially_blocked(ctx, false, blocked_c);
        return;
    }

    planer.draw_building_ghost(ctx, img_a > 0 ? img_a : preview, pixel);
    planer.draw_building_ghost(ctx, img_b > 0 ? img_b : preview, g_camera.lookup_tile_to_pixel(tile_b));
    planer.draw_building_ghost(ctx, img_c > 0 ? img_c : preview, g_camera.lookup_tile_to_pixel(tile_c));
}

void building_sphinx::on_place_update_tiles(int orientation, int variant) {
    // TODO(sphinx-rock): no placement restriction in C6
    base.prev_part_building_id = 0;
    runtime_data().variant = 0;
    base.orientation = orientation;

    const int size = base.size > 0 ? base.size : 6;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);

    const auto &bp = sphinx_params();
    const int rotation = building_rotation_global_rotation() % 4;
    const vec2i off_b = part_offset(bp.part_b_offset, rotation, vec2i{0, 6});
    const vec2i off_c = part_offset(bp.part_c_offset, rotation, vec2i{0, 12});

    building *part_b = building_create(BUILDING_SPHINX, tile().shifted(off_b), 0);
    building *part_c = building_create(BUILDING_SPHINX, tile().shifted(off_c), 0);
    game_undo_add_building(part_b);
    game_undo_add_building(part_c);

    auto *sb = part_b->dcast_sphinx();
    auto *sc = part_c->dcast_sphinx();
    if (sb) {
        sb->runtime_data().variant = 1;
        sb->runtime_data().phase = runtime_data().phase;
    }
    if (sc) {
        sc->runtime_data().variant = 2;
        sc->runtime_data().phase = runtime_data().phase;
    }

    map_building_tiles_add(part_b->id, part_b->tile, size,
        sb ? sb->building_image_get() : 0, TERRAIN_BUILDING);
    map_building_tiles_add(part_c->id, part_c->tile, size,
        sc ? sc->building_image_get() : 0, TERRAIN_BUILDING);

    part_b->prev_part_building_id = id();
    base.next_part_building_id = part_b->id;
    part_b->next_part_building_id = part_c->id;
    part_c->prev_part_building_id = part_b->id;
    part_c->next_part_building_id = 0;
}

void building_sphinx::on_destroy() {
    building_monument_remove_all_deliveries(id());
    // Cascade delete of linked parts is handled by clear.cpp via prev/next.
}

void building_sphinx::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    progress();
}

void building_sphinx::update_map_orientation(int /*map_orientation*/) {
    const int size = base.size > 0 ? base.size : 6;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);
}

bool building_sphinx::draw_ornaments_and_animations_height(painter &, vec2i, tile2i, color) {
    // Main sprite lives in tiles; refreshed via update_map_orientation (Q10).
    return false;
}

grid_area building_sphinx::get_area() const {
    building *m = base.main();
    tile2i start = m->tile;
    tile2i end = start.shifted(m->size - 1, m->size - 1);
    for (building *p = m; p; p = p->has_next() ? p->next() : nullptr) {
        tile2i pmin = p->tile;
        tile2i pmax = p->tile.shifted(p->size - 1, p->size - 1);
        if (pmin.x() < start.x()) {
            start = tile2i(pmin.x(), start.y());
        }
        if (pmin.y() < start.y()) {
            start = tile2i(start.x(), pmin.y());
        }
        if (pmax.x() > end.x()) {
            end = tile2i(pmax.x(), end.y());
        }
        if (pmax.y() > end.y()) {
            end = tile2i(end.x(), pmax.y());
        }
    }
    return {start, end};
}

tile2i building_sphinx::center_point() const {
    grid_area area = get_area();
    return area.tmin().add(area.tmax()).div(2);
}

tile2i building_sphinx::access_point() const {
    return main()->tile().shifted(0, 6);
}

void building_sphinx::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }
}
