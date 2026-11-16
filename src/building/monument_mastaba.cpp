#include "monument_mastaba.h"

#include "building/monument_mastaba_engine.h"
#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "core/custom_span.hpp"
#include "graphics/image.h"
#include "widget/city/tile_draw.h"
#include "widget/city/flat_draw.h"
#include "window/building/common.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/undo.h"
#include "city/city_resource.h"
#include "grid/random.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "graphics/view/lookup.h"
#include "graphics/graphics.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_worker.h"
#include "grid/routing/routing_grids.h"
#include "widget/widget_city.h"
#include "js/js_game.h"

#include <numeric>
#include <string>
#include <random>

struct mastaba_complete_ev { building_id bid; };
ANK_REGISTER_STRUCT_WRITER(mastaba_complete_ev, bid)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mastaba);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mastaba_part_side);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mastaba_part_wall);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mastaba_part_entrance);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mastaba);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mastaba_part_side);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mastaba_part_wall);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mastaba_part_entrance);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mastaba);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mastaba_part_side);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mastaba_part_wall);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mastaba_part_entrance);

void building_mastaba::base_params::finalize_construction(e_building_type type) {
    construction.btype = type;
}

void building_small_mastaba::static_params::archive_load(archive /*arch*/) {
    finalize_construction(BUILDING_SMALL_MASTABA);
}

void building_medium_mastaba::static_params::archive_load(archive /*arch*/) {
    finalize_construction(BUILDING_MEDIUM_MASTABA);
}

void building_large_mastaba::static_params::archive_load(archive /*arch*/) {
    finalize_construction(BUILDING_LARGE_MASTABA);
}

const monument &building_mastaba::config() const {
    return get_params(type()).construction;
}

template<typename T>
const building_mastaba::base_params &mastaba_base_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_mastaba::base_params &)bparams;
}

static e_building_type mastaba_main_type(e_building_type type) {
    if (building_type_any_of(type, {BUILDING_SMALL_MASTABA, BUILDING_SMALL_MASTABA_SIDE,
                                    BUILDING_SMALL_MASTABA_WALL, BUILDING_SMALL_MASTABA_ENTRANCE})) {
        return BUILDING_SMALL_MASTABA;
    }
    if (building_type_any_of(type, {BUILDING_MEDIUM_MASTABA, BUILDING_MEDIUM_MASTABA_SIDE,
                                    BUILDING_MEDIUM_MASTABA_WALL, BUILDING_MEDIUM_MASTABA_ENTRANCE,
                                    BUILDING_MEDIUM_MASTABA_RESERVED})) {
        return BUILDING_MEDIUM_MASTABA;
    }
    if (building_type_any_of(type, {BUILDING_LARGE_MASTABA, BUILDING_LARGE_MASTABA_SIDE,
                                    BUILDING_LARGE_MASTABA_WALL, BUILDING_LARGE_MASTABA_ENTRANCE,
                                    BUILDING_LARGE_MASTABA_RESERVED})) {
        return BUILDING_LARGE_MASTABA;
    }
    return BUILDING_NONE;
}

const building_mastaba::base_params &building_mastaba::get_params(e_building_type type) {
    switch (mastaba_main_type(type)) {
    case BUILDING_SMALL_MASTABA: return mastaba_base_params<building_small_mastaba>(building_static_params::get(BUILDING_SMALL_MASTABA));
    case BUILDING_MEDIUM_MASTABA: return mastaba_base_params<building_medium_mastaba>(building_static_params::get(BUILDING_MEDIUM_MASTABA));
    case BUILDING_LARGE_MASTABA: return mastaba_base_params<building_large_mastaba>(building_static_params::get(BUILDING_LARGE_MASTABA));
    default: break;
    }

    static building_mastaba::base_params dummy;
    return dummy;
};

static e_building_type mastaba_side_type(e_building_type main_type) {
    switch (main_type) {
    case BUILDING_MEDIUM_MASTABA: return BUILDING_MEDIUM_MASTABA_SIDE;
    case BUILDING_LARGE_MASTABA: return BUILDING_LARGE_MASTABA_SIDE;
    default: return BUILDING_SMALL_MASTABA_SIDE;
    }
}

static tile2i mastaba_footprint_end(building *main) {
    const auto &bp = building_mastaba::get_params(main->type);
    return main->tile.shifted(bp.init_tiles.y - 1, bp.init_tiles.x - 1);
}

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
    int x_leftmost, y_leftmost;
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT: x_leftmost = 0; y_leftmost = 1; break;
    case DIR_2_BOTTOM_RIGHT: x_leftmost = y_leftmost = 0; break;
    case DIR_4_BOTTOM_LEFT: x_leftmost = 1; y_leftmost = 0; break;
    case DIR_6_TOP_LEFT: x_leftmost = y_leftmost = 1; break;
    default:
        return;
    }

    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    int x_proper = x_leftmost * (size - 1);
    int y_proper = y_leftmost * (size - 1);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, terrain);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_monuments_set_progress(tile2i(grid_offset), 0);
            if (image_id > 0) {
                map_image_set(grid_offset, image_id);
            }
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_proper && dy == y_proper);
        }
    }
}

tile2i building_small_mastaba_bricks_waiting_tile(building *b) {
    if (!b || !smart_cast<building_mastaba>(b)) {
        return tile2i{-1, -1};
    }

    grid_tiles tiles = map_grid_get_tiles(b, 0);
    tile2i tile = map_grid_area_first(tiles, [b] (tile2i tile) {
        int progress = map_monuments_get_progress(tile);
        tile2i offset = tile.dist2i(b->tile).mod(4, 4);
        return progress < 200
            && (offset.x() == 1 || offset.x() == 3) && (offset.y() == 1 || offset.y() == 3);
    });

    return tile;
}

void building_mastaba::update_images(building *b, int curr_phase, const vec2i size_b) {
    building *main = b->main();
    building *part = b;

    if (curr_phase < MASTABA_PHASE_BRICKS) {
        return;
    }

    // Layer index is 1-based in get_bricks_image; phase BRICKS (2) → layer 1.
    // COMPLETE/FINISHED share the last brick course (same as update_map_orientation).
    const int layer = (curr_phase >= MASTABA_PHASE_COMPLETE)
        ? (MASTABA_PHASE_COMPLETE - MASTABA_PHASE_BRICKS)
        : std::max(1, curr_phase - MASTABA_PHASE_BRICKS + 1);
    while (part) {
        int image_id = building_small_mastabe_get_bricks_image(b->orientation, part->type, part->tile, main->tile, main->tile.shifted(size_b.y - 1, size_b.x - 1), layer);
        map_building_tiles_add(part->id, part->tile, part->size, image_id, TERRAIN_BUILDING);
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_mastaba::sync_visuals() {
    if (!is_main() || is_finished()) {
        return;
    }
    const int ph = runtime_data().phase;
    if (ph < MASTABA_PHASE_BRICKS) {
        return;
    }

    const vec2i tiles_size = get_params(type()).init_tiles;
    update_images(&base, ph, tiles_size);

    // OG engine has no per-tile course progress — mark footprint complete so flat
    // "in progress" overlays do not fight height brick ornaments.
    building *part = &base;
    while (part) {
        grid_tiles tiles = map_grid_get_tiles(part, 0);
        map_grid_area_foreach(tiles, [](tile2i t) { map_monuments_set_progress(t, 200); });
        part = part->has_next() ? part->next() : nullptr;
    }
}

bool building_mastaba::need_workers() const {
    if (!is_main()) {
        return false;
    }

    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_mastaba::finalize(building *b, const vec2i size_b) {
    building *part = b;
    building *main = b->main();
    update_images(b, MASTABA_PHASE_COMPLETE, size_b);

    while (!!part) {
        auto monument = part->dcast_monument();
        monument->runtime_data().phase = MONUMENT_FINISHED;
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_mastaba::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }

    // south/west placement can retarget base.type to *_SIDE (no init_tiles on part params).
    update_construction_day(get_params(type()).init_tiles);
}

bool building_mastaba::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, get_params(type()).init_tiles);
}

void building_mastaba::remove_worker(figure_id fid) {
    auto &w = runtime_data().workers;
    auto it = std::find(w.begin(), w.end(), fid);
    if (it != w.end()) {
        *it = 0;
    }
}

void building_mastaba::add_workers(figure_id fid) {
    auto &w = runtime_data().workers;
    auto it = std::find(w.begin(), w.end(), 0);
    if (it != w.end()) {
        *it = fid;
    }
}

int building_mastaba::get_image(int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = model_building_medium_mastaba.static_params().base_img();
    int base_image_id = image_id - 7;
    bool insidex = (tile.x() > start.x() && tile.x() < end.x());
    bool insidey = (tile.y() > start.y() && tile.y() < end.y());
    int random = (image_id + 5 + (tile.x() + tile.y()) % 7);
    int result = random;
    if (tile == start) { // top corner
        result = image_id;
    } else if (tile == tile2i(start.x(), end.y())) {
        result = image_id - 2;
    } else if (tile == end) {
        result = image_id - 4;
    } else if (tile == tile2i(end.x(), start.y())) {
        result = image_id - 6;
    } else if (tile.x() == start.x()) {
        result = image_id - 1;
    } else if (tile.y() == end.y()) {
        result = image_id - 3;
    } else if (tile.y() == start.y()) {
        result = (insidex || insidey) ? image_id - 7 : random;
    } else if (tile.x() == end.x()) {
        result = image_id - 5;
    }

    if (result < random) {
        int offset = result - base_image_id;
        result = (base_image_id + (offset + (8 - g_camera.orientation)) % 8);
        return result;
    }

    return result;
}

int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer) {
    // Part types (wall/side/entrance) have no animations of their own â€” bricks live on the
    // main mastaba static params.
    const e_building_type bricks_type = mastaba_main_type(type);
    int image_base_bricks = building_static_params::get(bricks_type).first_img("base_bricks");

    int image_id = image_base_bricks + (layer - 1) * 8 + 4;
    int random = (image_base_bricks + 96 + (layer - 1) + (tile.x() + tile.y()) % 1 * 6);
    int result = random;
    if (building_type_any_of(type, { BUILDING_SMALL_MASTABA_ENTRANCE, BUILDING_MEDIUM_MASTABA_ENTRANCE, BUILDING_LARGE_MASTABA_ENTRANCE })) {
        int ids[4] = {image_base_bricks + 110, image_base_bricks + 104, image_base_bricks + 104, image_base_bricks + 109};
        int i = (orientation + (g_camera.orientation / 2)) % 4;
        return ids[i];
    } else if (building_type_any_of(type, { BUILDING_SMALL_MASTABA_WALL, BUILDING_MEDIUM_MASTABA_WALL, BUILDING_LARGE_MASTABA_WALL })) {
        return random;
    } else if (tile.y() == start.y()) { // top corner
        result = (image_id + 3);
    } else if (tile.y() == end.shifted(0, -1).y()) {
        result = (image_id + 1);
    } else {
        result = random;
    }

    if (result < random) {
        int offset = result - image_id;
        result = (image_id + (offset + (g_camera.orientation/2)) % 4);
        return result;
    }

    return result;
}

void building_mastaba::on_create(int orientation) {
}

void building_mastaba::on_destroy() {
    mastaba_engine_clear_building(id());
    building_impl::on_destroy();
}

void building_mastaba::on_place(int orientation, int variant) {
    building_monument::on_place(orientation, variant);

    base.prev_part_building_id = 0;

    map_mastaba_tiles_add(id(), tile(), base.size, -1, TERRAIN_BUILDING);

    const e_building_type main_type = type();
    const auto &bparams = get_params(main_type);
    auto parts = bparams.config_north;
    switch (orientation) {
    case 0: parts = bparams.config_north; break;
    case 1: parts = bparams.config_east; break;
    case 2:
        parts = bparams.config_south;
        base.type = mastaba_side_type(main_type);
        break;

    case 3:
        parts = bparams.config_west;
        base.type = mastaba_side_type(main_type);
        break;
    }

    verify_no_crash(parts.size() > 0);
    for (auto &part : parts) {
        if (part.base) {
            part.b = &base;
            continue;
        }

        part.b = building_create(part.type, tile().shifted(part.offset), 0);
        // Part JS configs historically omitted building_size; force 2Ã—2 like the main piece.
        if (part.b->size <= 0) {
            part.b->size = base.size > 0 ? base.size : 2;
        }
        game_undo_add_building(part.b);
        tile2i btile_add = tile().shifted(part.offset);
        map_mastaba_tiles_add(part.b->id, btile_add, part.b->size, -1, TERRAIN_BUILDING);
    }

    building *prev_part = nullptr;
    for (auto &part : parts) {
        part.b->prev_part_building_id = prev_part ? prev_part->id : 0;
        if (prev_part) {
            prev_part->next_part_building_id = part.b->id;
        }
        prev_part = part.b;
    }

    mastaba_engine_init(&base);
}

static color mastaba_progress_alpha_mask(uint32_t progress, color color_mask) {
    return ((0xff * progress / 200) << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff);
}

static void mastaba_draw_stick_at(painter &ctx, tile2i tile, tile2i expected, int image_stick, color color_mask) {
    if (tile != expected || map_monuments_get_progress(tile) != 0) {
        return;
    }

    vec2i offset = g_camera.lookup_tile_to_pixel(tile);
    auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
    command.image_id = image_stick;
    command.pixel = offset;
    command.mask = color_mask;
    command.use_sort_pixel = true;
    command.sort_pixel = offset + vec2i(0, 1);
    command.location = SOURCE_LOCATION;
}

void building_mastaba::draw_flat_phase_site(painter &ctx, color color_mask, const vec2i tiles_size, int image_grounded, int image_stick) {
    building *main = base.main();

    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            uint32_t progress = map_monuments_get_progress(ntile);
            if (progress == 0 || progress > 200) {
                continue;
            }

            vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
            command.image_id = image_grounded + ((dy * 4 + dx) & 7);
            command.pixel = offset;
            command.mask = mastaba_progress_alpha_mask(progress, color_mask);
            command.flags = ImgFlag_Alpha;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
        }
    }

    mastaba_draw_stick_at(ctx, base.tile.shifted(0, 0), main->tile, image_stick, color_mask);
    mastaba_draw_stick_at(ctx, base.tile.shifted(1, 0), main->tile.shifted(tiles_size.y - 1, 0), image_stick, color_mask);
    mastaba_draw_stick_at(ctx, base.tile.shifted(0, 1), main->tile.shifted(0, tiles_size.x - 1), image_stick, color_mask);
    mastaba_draw_stick_at(ctx, base.tile.shifted(1, 1), main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), image_stick, color_mask);
}

void building_mastaba::draw_flat_phase_foundation(painter &ctx, color color_mask, const vec2i tiles_size, int image_grounded) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);

    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
            uint32_t progress = map_monuments_get_progress(ntile);

            if (progress < 200) {
                auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                command.pixel = offset;
                command.mask = color_mask;
            }

            if (progress > 0 && progress <= 200) {
                auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                command.image_id = get_image(base.orientation, ntile, main->tile, end);
                command.pixel = offset;
                command.mask = mastaba_progress_alpha_mask(progress, color_mask);
                command.flags = ImgFlag_Alpha;
            }
        }
    }
}

void building_mastaba::draw_flat_phase_bricks(painter &ctx, color color_mask, const vec2i tiles_size) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);

    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            uint32_t progress = map_monuments_get_progress(ntile);
            if (progress >= 200) {
                continue;
            }

            vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
            command.image_id = get_image(base.orientation, ntile, main->tile, end);
            command.pixel = offset;
            command.mask = color_mask;
        }
    }
}

bool building_mastaba::draw_ornaments_and_animations_flat_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    if (is_finished()) {
        return false;
    }

    // Wall/side/entrance parts have empty animations â€” art lives on the main mastaba type.
    const auto &mastaba_anims = building_static_params::get(mastaba_main_type(type()));
    const int image_grounded = mastaba_anims.first_img(animkeys().base_grounded);
    color_mask = (color_mask ? color_mask : 0xffffffff);

    switch (runtime_data().phase) {
    case MASTABA_PHASE_SITE:
        draw_flat_phase_site(ctx, color_mask, tiles_size, image_grounded, mastaba_anims.first_img(animkeys().image_stick));
        break;
    case MASTABA_PHASE_FOUNDATION:
        draw_flat_phase_foundation(ctx, color_mask, tiles_size, image_grounded);
        break;
    case MASTABA_PHASE_BRICKS:
        // OG block-engine drives courses via remaining_blocks; flat tile-progress
        // overlay fights height art when progress was never remake-worked.
        if (!mastaba_engine_block_phase_active(&base)) {
            draw_flat_phase_bricks(ctx, color_mask, tiles_size);
        }
        break;
    default:
        break;
    }

    return true;
}

static vec2i mastaba_height_city_offset() {
    switch (g_camera.orientation / 2) {
    case 0: return vec2i(-30, +15);
    case 1: return vec2i(0, 0);
    case 2: return vec2i(-30, -15);
    case 3: return vec2i(-60, 0);
    default: return vec2i(0, 0);
    }
}

static void mastaba_fill_tiles_height(tile2i tile, int img) {
    const image_t *image = image_get(img);
    if (!image) {
        return;
    }
    int iso_size = image->isometric_size() - 1;
    grid_tiles tiles = map_grid_get_tiles(tile, tile.shifted(iso_size, iso_size));
    for (auto &t : tiles) {
        map_building_height_set(t.grid_offset(), image->isometric_top_height);
    }
}

static void mastaba_draw_height_brick(painter &ctx, tile2i tile, int img, vec2i city_offset, color color_mask) {
    vec2i offset = g_camera.lookup_tile_to_pixel(tile);
    auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
    command.image_id = img;
    command.pixel = offset + city_offset;
    command.mask = color_mask;
    mastaba_fill_tiles_height(tile, img);
}

void building_mastaba::draw_height_phase_bricks(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);

    for (auto &tile : tiles2draw) {
        if (map_monuments_get_progress(tile) < 200) {
            continue;
        }
        int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, end, 1);
        mastaba_draw_height_brick(ctx, tile, img, city_offset, color_mask);
    }
}

void building_mastaba::draw_height_phase_layers(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);
    const int phase = runtime_data().phase;

    for (auto &tile : tiles2draw) {
        uint32_t progress = map_monuments_get_progress(tile);
        int layer = (progress >= 200) ? (phase - MASTABA_PHASE_BRICKS + 1) : (phase - MASTABA_PHASE_BRICKS);
        int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, end, layer);
        mastaba_draw_height_brick(ctx, tile, img, city_offset, color_mask);
    }
}

void building_mastaba::draw_height_phase_complete(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);
    const int layer = MASTABA_PHASE_COMPLETE - MASTABA_PHASE_BRICKS;

    for (auto &tile : tiles2draw) {
        int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, end, layer);
        mastaba_draw_height_brick(ctx, tile, img, city_offset, color_mask);
    }
}

void building_mastaba::draw_height_side_figures(painter &ctx) {
    if (!building_type_any_of(base.type, {
            BUILDING_SMALL_MASTABA_SIDE, BUILDING_MEDIUM_MASTABA_SIDE, BUILDING_LARGE_MASTABA_SIDE})) {
        return;
    }

    building *main = base.main();
    grid_tiles tile2common = map_grid_get_tiles(main->tile, mastaba_footprint_end(main));
    for (auto &t : tile2common) {
        vec2i offset = g_camera.lookup_tile_to_pixel(t);
        g_screen_city.draw_figures(offset, t, ctx, /*force*/true);
    }
}

bool building_mastaba::draw_ornaments_and_animations_hight_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    color_mask = (color_mask ? color_mask : 0xffffffff);
    const vec2i city_offset = mastaba_height_city_offset();

    height_tiles tiles2draw;
    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            if (dx % 2 == 0 && dy % 2 == 0) {
                tiles2draw.push_back(base.tile.shifted(dx, dy));
            }
        }
    }

    std::sort(tiles2draw.begin(), tiles2draw.end(), [] (tile2i lhs, tile2i rhs) {
        return g_camera.lookup_tile_to_pixel(lhs).y < g_camera.lookup_tile_to_pixel(rhs).y;
    });

    const int phase = runtime_data().phase;
    if (is_finished() || phase == MASTABA_PHASE_COMPLETE) {
        draw_height_phase_complete(ctx, color_mask, tiles_size, city_offset, tiles2draw);
    } else if (phase == MASTABA_PHASE_BRICKS) {
        draw_height_phase_bricks(ctx, color_mask, tiles_size, city_offset, tiles2draw);
    } else if (phase > MASTABA_PHASE_BRICKS && phase < MASTABA_PHASE_COMPLETE) {
        draw_height_phase_layers(ctx, color_mask, tiles_size, city_offset, tiles2draw);
    }

    if (is_finished() || phase > MASTABA_PHASE_BRICKS) {
        draw_height_side_figures(ctx);
    }

    return true;
}

void building_mastaba::complete_construction(const vec2i tiles_size) {
    finalize(&base, tiles_size);
    if (!is_main()) {
        return;
    }

    // south/west heads can be *_SIDE â€” ES handlers live on the main size type.
    const auto &params = building_static_params::get(mastaba_main_type(type()));
    js_event(mastaba_complete_ev{ id() }, params.name, "complete_construction");
}

bool building_mastaba::clay_delivery_enabled() {
    return game_features::gameplay_change_mastaba_clay_delivery.to_bool();
}

bool building_mastaba::clay_stock_ready() const {
    if (!clay_delivery_enabled()) {
        return true;
    }
    const int need = needs_resource(RESOURCE_CLAY);
    if (need <= 0) {
        return true;
    }
    return resource_pct(RESOURCE_CLAY) >= 100;
}

int building_mastaba::clay_to_haul(int loads_under_way, int load) const {
    if (!clay_delivery_enabled() || !is_main() || is_finished()) {
        return 0;
    }
    const int need = needs_resource(RESOURCE_CLAY);
    const int on_site = need * resource_pct(RESOURCE_CLAY) / 100;
    return std::max(0, need - on_site - loads_under_way * load);
}

int building_mastaba::needs_resource(e_resource resource) const {
    return needs_resource(resource, runtime_data().phase);
}

int building_mastaba::needs_resource(e_resource resource, int phase) const {
    if (resource == RESOURCE_CLAY && !clay_delivery_enabled()) {
        return 0;
    }
    return building_monument::needs_resource(resource, phase);
}

int building_mastaba::try_assign_bricklayer(figure_id fid) {
    return mastaba_engine_try_assign_bricklayer(&base, fid);
}

void building_mastaba::place_bricklayer_block(figure_id fid) {
    mastaba_engine_place_block(id(), fid);
}

bool building_mastaba::need_bricklayers() {
    if (!is_main() || is_finished()) {
        return false;
    }
    auto &d = runtime_data();
    if (d.phase < MASTABA_PHASE_BRICKS) {
        return false;
    }
    if (!clay_stock_ready()) {
        return false;
    }
    auto *ms = pyramid_main_state_get(id());
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return false;
    }
    if (!has_free_worker_slot()) {
        return false;
    }
    int works = 0;
    for (auto &wid : d.workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        works += (f && f->type == FIGURE_BRICKLAYER) ? 1 : 0;
    }
    return works < needs_bricklayers(d.phase);
}

int building_mastaba::needs_bricklayers(int ph_id) const {
    const int want = phase_worker_count(ph_id, FIGURE_BRICKLAYER);
    if (want > 0) {
        return want;
    }
    return has_free_worker_slot() ? 1 : 0;
}

void building_mastaba::update_construction_day(const vec2i tiles_size) {
    auto &monumentd = runtime_data();
    if (monumentd.phase >= MASTABA_PHASE_COMPLETE) {
        complete_construction(tiles_size);
        return;
    }

    if (!is_main()) {
        return;
    }

    if (monumentd.phase >= MASTABA_PHASE_BRICKS) {
        auto *ms = pyramid_main_state_get(id());
        if (!ms) {
            mastaba_engine_init(&base);
            ms = pyramid_main_state_get(id());
        }
        if (ms && !ms->block_phase_active && monumentd.phase == MASTABA_PHASE_BRICKS) {
            mastaba_engine_start_block_phase(&base);
        }
        if (mastaba_engine_blocks_finished(&base)) {
            building_impl *part = this;
            while (part) {
                if (auto *m = part->dcast_monument()) {
                    m->set_phase(MASTABA_PHASE_COMPLETE);
                }
                part = part->has_next() ? part->next() : nullptr;
            }
        }
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{ -1, -1 });
    building_impl *part = this;

    if (all_tiles_finished) {
        int curr_phase = monumentd.phase;
        if (curr_phase + 1 < MASTABA_PHASE_COMPLETE) {
            map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        }
        update_images(&base, curr_phase, tiles_size);
        while (part) {
            verify_no_crash(part->dcast_monument());
            part->dcast_monument()->set_phase(curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
        if (monumentd.phase >= MASTABA_PHASE_BRICKS) {
            mastaba_engine_start_block_phase(&base);
        }
    }
}

void building_mastaba::update_count() const {
    if (!is_main()) {
        return;
    }

    building_monument::update_count();
}

void building_mastaba::update_month() {
    if (!is_main()) {
        return;
    }

    auto &monumentd = runtime_data();
    for (uint16_t &w_id : monumentd.workers) {
        figure* f = figure_get(w_id);
        if (!f || !f->is_alive() || f->destination() != &base) {
            w_id = 0;
        }
    }
}

void building_mastaba::update_map_orientation(int map_orientation) {
    if (is_finished()) {
        building *main = base.main();
        tile2i end = mastaba_footprint_end(main);
        int image_id = building_small_mastabe_get_bricks_image(base.orientation, type(), tile(), main->tile, end, 6);
        map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
    }
}

bool building_mastaba::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    if (is_finished()) {
        return false;
    }

    auto &monumentd = runtime_data();
    return (monumentd.phase < MASTABA_PHASE_BRICKS);
}

void building_mastaba::bind_dynamic(io_buffer *iob, size_t version) {
    if (version >= 196) {
        bind_block_engine_state(iob, 0);
        return;
    }

    auto &monumentd = runtime_data();

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.burial_stock[i]);
    }
    iob->bind____skip(2); // was skip(38); 36 = burial_stock
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.funeral_done); // was skip(1) statue_offset
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.preexisting);  // was skip(1) temple_complex_attachments
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }

    auto &main = monumentd.og_main;
    iob->bind_u8((uint8_t &)main.style);
    iob->bind_u8(main.size_variant);
    iob->bind_u16(main.remaining_blocks);
    iob->bind_u8(main.block_phase_active);
    iob->bind_u8(main.force_show_ramps);

    auto &part = monumentd.og_part;
    iob->bind_u8(part.size_variant);
    iob->bind_u8(part.stage);
    iob->bind_u8(part.blocks);
    iob->bind_u8(part.layer);
    iob->bind_u8(part.target_layers);
    iob->bind_u8(part.subtype);
    iob->bind_u16(part.worker_figure_id);
    iob->bind_u8(part.ramp1_height);
    iob->bind_u8(part.ramp2_height);
    iob->bind_u32(part.ramp_image_id);
    iob->bind_i16(part.ramp_image_x1);
    iob->bind_i16(part.ramp_image_y1);
    iob->bind_i16(part.ramp_image_x2);
    iob->bind_i16(part.ramp_image_y2);
}

bool building_mastaba::get_route_citizen_land_type(int grid_offset, int &land_result) const {
    {
        if (is_finished()) {
            land_result = CITIZEN_N1_BLOCKED;
            return true;
        } else if (phase() > MASTABA_PHASE_BRICKS) {
            building *maint_b = base.main();
            tile2i maint = maint_b->tile;
            tile2i end = mastaba_footprint_end(maint_b);
            tile2i tile(grid_offset);
            land_result = (tile.x() == maint.x() || tile.y() == maint.y() || tile.x() == end.x()) ? CITIZEN_N1_BLOCKED : CITIZEN_2_PASSABLE_TERRAIN;
            return true;
        }
    }
    land_result = CITIZEN_2_PASSABLE_TERRAIN;
    return true;
}

bool building_mastaba::target_route_tile_blocked(int grid_offset) const {
    return is_finished();
}

int building_mastaba::building_image_get() const {
    // Wall/side/entrance static params have no animations â€” art lives on the main type.
    const int base = building_static_params::get(mastaba_main_type(type())).base_img();
    switch (runtime_data().phase) {
    case MASTABA_PHASE_FOUNDATION:
        return base;
    default:
        return base + 1;
    }
}

grid_area building_mastaba::get_area() const {
    building *m = base.main();
    return { m->tile, mastaba_footprint_end(m) };
}

bool building_mastaba::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (city_flat_should_flatten_building(base)) {
        return false;
    }

    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, get_params(type()).init_tiles);
    }

    if (runtime_data().phase < MASTABA_PHASE_BRICKS) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, get_params(type()).init_tiles);
}

tile2i building_mastaba::center_point() const {
    grid_area area = get_area();
    return area.tmin().add(area.tmax()).div(2);
}

tile2i building_mastaba::access_point() const {
    // init_tiles is [height, width]; workers approach along the long axis from the NW origin.
    return base.main()->tile.shifted(0, get_params(type()).init_tiles.x);
}
