#include "building_farm.h"

#include "core/object_property.h"
#include "building/building_animation.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "core/calc.h"
#include "game/resource.h"
#include "game/game.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/floodplain.h"
#include "grid/building_tiles.h"
#include "grid/random.h"
#include "grid/figure.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "city/city_floods.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "widget/city/building_ghost.h"
#include "construction/build_planner.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "figure/figure.h"
#include "grid/tiles.h"
#include "dev/debug.h"
#include "figuretype/figure_cartpusher.h"
#include "js/js_game.h"

#include <iostream>

constexpr int CROPS_OFFSETS = 6;

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_grain);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_lettuce);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_chickpeas);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_pomegranates);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_barley);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_flax);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_henna);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_figs);

declare_console_command(addgrain, game_cheat_add_resource<RESOURCE_GRAIN>);
declare_console_command_p(farmgrow) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"100" : args.c_str());

    buildings_valid_farms_do([amount] (building &b) {
        building_farm *farm = b.dcast_farm();
        if (!farm) {
            return;
        }

        farm->runtime_data().progress += amount;
    });
};

void building_farm::map_building_tiles_add_farm(e_building_type type, int building_id, tile2i tile, int crop_image_offset, int progress) {
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    crop_image_offset += image_id_from_group(GROUP_BUILDING_FARMLAND);
    //    if (!map_grid_is_inside(x, y, 3))
    //        return;
    //    // farmhouse
    //    int x_leftmost, y_leftmost;
    //    switch (city_view_orientation()) {
    //    case DIR_0_TOP_RIGHT:
    //        x_leftmost = 0;
    //        y_leftmost = 1;
    //        break;
    //    case DIR_2_BOTTOM_RIGHT:
    //        x_leftmost = 0;
    //        y_leftmost = 0;
    //        break;
    //    case DIR_4_BOTTOM_LEFT:
    //        x_leftmost = 1;
    //        y_leftmost = 0;
    //        break;
    //    case DIR_6_TOP_LEFT:
    //        x_leftmost = 1;
    //        y_leftmost = 1;
    //        break;
    //    default:
    //        return;
    //    }
    //    for (int dy = 0; dy < 2; dy++) {
    //        for (int dx = 0; dx < 2; dx++) {
    //            int grid_offset = MAP_OFFSET(x + dx, y + dy);
    //            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
    //            map_terrain_add(grid_offset, TERRAIN_BUILDING);
    //            map_building_set(grid_offset, building_id);
    //            map_property_clear_constructing(grid_offset);
    //            map_property_set_multi_tile_size(grid_offset, 2);
    //            map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_FARM_HOUSE));
    //            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_leftmost && dy == y_leftmost);
    //        }
    //    }
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        //        int image_id = image_id_from_group(GROUP_BUILDING_FARM_HOUSE);
        //        if (map_terrain_is(map_grid_offset(x, y), TERRAIN_FLOODPLAIN))
        //            image_id = image_id_from_group(GROUP_BUILDING_FARMLAND);
    building *b = building_get(building_id);
    map_building_tiles_add(building_id, tile, b->size, get_farm_image(type, tile), TERRAIN_BUILDING);
}

int building_farm::preview::is_blocked(tile2i tile, int size, blocked_tile_vec &blocked_tiles) const {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    int num_tiles = (size * size);

    for (int i = 0; i < num_tiles; i++) {
        const int offset = build_planner::tile_grid_offset(orientation_index, i);
        tile2i check_tile = tile.shifted(offset);
        bool tile_blocked = !map_terrain_is(check_tile, TERRAIN_FLOODPLAIN)
            || (map_building_at(check_tile) != 0)
            || map_has_figure_at(check_tile);

        blocked_tiles.push_back({ check_tile, tile_blocked });
        blocked += (tile_blocked ? 1 : 0);
    }
    return blocked;
}

void building_farm::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    blocked_tile_vec blocked_tiles_farm;

    const bool blocked = is_blocked(end, params.building_size, blocked_tiles_farm);
    if (blocked) {
        planer.draw_partially_blocked(ctx, false, blocked_tiles_farm);
        return;
    }

    int image_id = get_farm_image(planer.build_type, end);
    planer.draw_building_ghost(ctx, image_id, pixel + vec2i{ -60, 30 });
    draw_crops(ctx, planer.build_type, 0, end, pixel + vec2i{ -60, 30 }, COLOR_MASK_GREEN);
}

int building_farm::get_crops_image(e_building_type type, int growth) {
    int base = 0;
    base = image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH);
    switch (type) {
    case BUILDING_BARLEY_FARM: return base + 6 * 0 + growth;
    case BUILDING_FLAX_FARM: return base + 6 * 6 + growth;
    case BUILDING_GRAIN_FARM: return base + 6 * 2 + growth;
    case BUILDING_LETTUCE_FARM: return base + 6 * 3 + growth;
    case BUILDING_POMEGRANATES_FARM: return base + 6 * 4 + growth;
    case BUILDING_CHICKPEAS_FARM: return base + 6 * 5 + growth;
    case BUILDING_FIGS_FARM: return base + 6 * 1 + growth;

    default:
        assert(false);
    }

    return image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH) + (type - BUILDING_BARLEY_FARM) * 6; // temp
}

int building_farm::get_farm_image(e_building_type type, tile2i tile) {
    const auto &p = building_static_params::get(type);
    if (map_terrain_is(tile, TERRAIN_FLOODPLAIN)) {
        int base = p.first_img(animkeys().farmland);
        int fert_average = map_get_fertility_for_farm(tile);
        int fertility_index = std::clamp<int>(fert_average / 12, 0, 7);

        return base + fertility_index;
    }

    return p.first_img(animkeys().farm_house);
}

bool building_farm::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    return false;
}

void building_farm::draw_farm_worker(painter &ctx, int direction, int action, vec2i coords, color color_mask) {
    pcstr anim_key = std::array{"tiling", "seeding", "harvesting"}[action];
    const animation_t &action_anim = anim(anim_key);
    animation_context context;

    auto &d = runtime_data();
    context.setup(action_anim);
    context.frame = d.worker_frame;
    context.update(false);
    d.worker_frame = context.frame;

    auto& command = ImageDraw::create_subcommand(render_command_t::ert_sprite);
    command.image_id = context.start_frame() + direction + 8 * context.current_frame();
    command.pixel = coords + context.pos;
    command.mask = color_mask;
}

static const vec2i FARM_TILE_OFFSETS_FLOODPLAIN[9] = {{60, 0}, {90, 15}, {120, 30}, {30, 15}, {60, 30}, {90, 45}, {0, 30}, {30, 45}, {60, 60}};
static const vec2i FARM_TILE_OFFSETS_MEADOW[5] = {{0, 30}, {30, 45}, {60, 60}, {90, 45}, {120, 30}};

static vec2i farm_tile_coords(vec2i pos, int tile_x, int tile_y) {
    int tile_id = 3 * abs(tile_y) + abs(tile_x);
    return pos + FARM_TILE_OFFSETS_FLOODPLAIN[tile_id];
}

void building_farm::draw_crops(painter &ctx, e_building_type type, int progress, tile2i tile, vec2i point, color color_mask) {
    int image_crops = get_crops_image(type, 0);
    if (map_terrain_is(tile, TERRAIN_FLOODPLAIN)) { // on floodplains - all
        for (int i = 0; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 200) / 100));

            auto& command = ImageDraw::create_subcommand(render_command_t::ert_from_below);
            command.image_id = image_crops + growth_offset;
            command.pixel = { point.x + FARM_TILE_OFFSETS_FLOODPLAIN[i].x, point.y + FARM_TILE_OFFSETS_FLOODPLAIN[i].y };
            command.mask = color_mask;
        }
    } else { // on dry meadows
        for (int i = 0; i < 5; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 400) / 100));
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_from_below);
            command.image_id = image_crops + growth_offset;
            command.pixel = { point.x + FARM_TILE_OFFSETS_MEADOW[i].x, point.y + FARM_TILE_OFFSETS_MEADOW[i].y };
            command.mask = color_mask;
        }
    }
}

bvariant building_farm::get_property(const xstring &domain, const xstring &name) const {
    if (domain == tags().farm && name == tags().progress) {
        int pct_done = calc_percentage<int>(progress(), progress_max());
        return bvariant(pct_done);
    }

    return building_impl::get_property(domain, name);
}

void building_farm::draw_workers(painter &ctx, building* b, tile2i tile, vec2i pos) {
    if (b->num_workers == 0) {
        return;
    }

    pos += {30, -15};
    int random_seed = 1234.567f * (1 + game.simtime.day) * map_random_get(b->tile.grid_offset());
    int d = random_seed % 8;
    if (building_is_floodplain_farm(*b)) {
        auto farm = b->dcast_farm();
        const short progress = farm->progress();
        if (g_floods.state_is(FLOOD_STATE_IMMINENT)) {
            //int random_x = random_seed % 3;
            //int random_y = int(1234.567f * random_seed) % 3;
            //auto coords = farm_tile_coords(x, y, random_x, random_y);
            //draw_ph_worker(d, 2, animation_offset, coords);
        } else {
            if (progress < 400)
                draw_farm_worker(ctx, game.simtime.absolute_tick() % 128 / 16, 1, farm_tile_coords(pos, 1, 1));
            else if (progress < 500)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 1, 0));
            else if (progress < 600)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 0));
            else if (progress < 700)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 0, 1));
            else if (progress < 800)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 1, 1));
            else if (progress < 900)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 1));
            else if (progress < 1000)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 0, 2));
            else if (progress < 1100)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 1, 2));
            else if (progress < 1200)
                draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 2));
            else if (progress < 1300)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 1, 0));
            else if (progress < 1400)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 2, 0));
            else if (progress < 1500)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 0, 1));
            else if (progress < 1600)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 1, 1));
            else if (progress < 1700)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 2, 1));
            else if (progress < 1800)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 0, 2));
            else if (progress < 1900)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 1, 2));
            else if (progress < 2000)
                draw_farm_worker(ctx, d, 2, farm_tile_coords(pos, 2, 2));
        }
    } else {
        auto farm = b->dcast_farm();
        const short progress = farm->progress();
        if (progress < 100)
            draw_farm_worker(ctx, game.simtime.absolute_tick() % 128 / 16, 1, farm_tile_coords(pos, 1, 1));
        else if (progress < 400)
            draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 0, 2));
        else if (progress < 800)
            draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 1, 2));
        else if (progress < 1200)
            draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 2));
        else if (progress < 1600)
            draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 1));
        else if (progress < 2000)
            draw_farm_worker(ctx, d, 0, farm_tile_coords(pos, 2, 0));
    }
}

static bool farm_harvesting_month_for_produce(int resource_id, int month) {
    switch (resource_id) {
        // annual meadow farms
    case RESOURCE_CHICKPEAS:
    case RESOURCE_LETTUCE:
        return (month == MONTH_APRIL);

    case RESOURCE_FIGS:
        return (month == MONTH_SEPTEMPTER);

    case RESOURCE_FLAX:
        return (month == MONTH_DECEMBER);

    // biannual meadow farms
    case RESOURCE_GRAIN:
        return (month == MONTH_JANUARY || month == MONTH_MAY);

    case RESOURCE_BARLEY:
        return (month == MONTH_FEBRUARY || month == MONTH_AUGUST);

    case RESOURCE_POMEGRANATES:
        return (month == MONTH_JUNE || month == MONTH_NOVEMBER);
    }
    return false;
}

bool building_farm_time_to_deliver(bool floodplains, int resource_id) {
    if (floodplains) {
        float current_cycle = g_floods.current_cycle();
        float start_cycle = g_floods.start_cycle();
        float harvest_cycle = start_cycle - 28.0f;
        return g_floods.state_is(FLOOD_STATE_IMMINENT) && (current_cycle >= harvest_cycle);
    } else {
        const bool result = game.simtime.day < 2 && farm_harvesting_month_for_produce(resource_id, game.simtime.month);
        return result;
    }
}

void building_farm::on_create(int orientation) {
    runtime_data().progress_max = 2000;
}

void building_farm::on_place_update_tiles(int orientation, int variant) {
    switch (type()) {
    case BUILDING_BARLEY_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), 0, 0);
        break;

    case BUILDING_FLAX_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS, 0);
        break;

    case BUILDING_GRAIN_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 2, 0);
        break;

    case BUILDING_LETTUCE_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 3, 0);
        break;

    case BUILDING_POMEGRANATES_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 4, 0);
        break;

    case BUILDING_CHICKPEAS_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 5, 0);
        break;

    case BUILDING_FIGS_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 6, 0);
        break;

    case BUILDING_HENNA_FARM:
        map_building_tiles_add_farm(type(), id(), tile(), CROPS_OFFSETS * 7, 0);
        break;

    default:
        assert(false);
    }
}

bool building_farm::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i t, color mask) {
    if (map_terrain_is(t.grid_offset(), TERRAIN_BUILDING)) {
        draw_crops(ctx, type(), progress(), tile(), point, mask);
        draw_workers(ctx, &base, t, point);
    }

    return true;
}

void building_farm::draw_normal_anim(painter &ctx, vec2i pixel, tile2i tile, color mask) {
    if (!base.anim.valid()) {
        return;
    }

    if (!can_play_animation()) {
        return;
    }

    vec2i pos = pixel + base.anim.pos;
    ctx.img_sprite(base.anim.start_frame() + base.anim.current_frame(), pos, mask);
}

e_sound_channel_city building_farm::sound_channel() const {
    switch (type()) {
    case BUILDING_CHICKPEAS_FARM:
    case BUILDING_BARLEY_FARM:
    case BUILDING_FLAX_FARM:
    case BUILDING_GRAIN_FARM:
    case BUILDING_FIGS_FARM:
        return SOUND_CHANNEL_CITY_CHICKFARM;

    default:
        assert(false);
    }
    return SOUND_CHANNEL_CITY_CHICKFARM;
}

void building_farm::update_count() const {
    building_impl::update_count();

    static std::pair<e_building_type, e_resource> farms[] = {
        {BUILDING_GRAIN_FARM, RESOURCE_GRAIN},
        {BUILDING_BARLEY_FARM, RESOURCE_BARLEY},
        {BUILDING_FLAX_FARM, RESOURCE_FLAX},
        {BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE},
        {BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES},
        {BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS},
        {BUILDING_FIGS_FARM, RESOURCE_FIGS},
        {BUILDING_HENNA_FARM, RESOURCE_HENNA}
    };
    auto it = std::find_if(std::begin(farms), std::end(farms), [btype = type()](auto &t) { return t.first == btype; });
    g_city.buildings.increase_industry_count(it->second, num_workers() > 0);
}

void building_farm::spawn_figure() {
    bool is_floodplain = building_is_floodplain_farm(base);
    if (!is_floodplain && has_road_access()) { // only for meadow farms
        common_spawn_labor_seeker(current_params().min_houses_coverage);
        if (building_farm_time_to_deliver(false, base.output.resource)) { // UGH!!
            spawn_figure_harvests();
        }
    } else if (is_floodplain) {
        if (building_farm_time_to_deliver(true)) {
            spawn_figure_harvests();
        }
    }
}

void building_farm::update_graphic() {
    building_impl::update_graphic();
}

void building_farm::on_undo() {
    int img_id = anim(animkeys().farmland).first_img();
    map_building_tiles_add_farm(type(), id(), tile(), img_id, 0);
}

void building_farm::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(22);
    iob->bind____skip(48);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT16, &d.progress_max);
    iob->bind(BIND_SIGNATURE_UINT8, &d.produce_multiplier);
    iob->bind(BIND_SIGNATURE_UINT16, &d.work_camp_id);
    iob->bind(BIND_SIGNATURE_UINT16, &d.worker_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.labor_state);
    iob->bind(BIND_SIGNATURE_UINT8, &d.labor_days_left);
    iob->bind(BIND_SIGNATURE_UINT16, &d.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &d.worker_frame);
}

void building_farm::start_production() {
    auto &d = runtime_data();
    d.progress = 0;
    update_tiles_image();
}

void building_farm::add_tiles() {
    map_building_tiles_add_farm(type(), id(), tile(), 0, 0);
}

int building_farm::expected_produce() {
    auto &d = runtime_data();

    int progress = d.ready_production > 0
        ? d.ready_production
        : d.progress;

    if (!game_features::gameplay_fix_farm_produce_quantity) {
        progress = (progress / 20) * 20;
    }
    // In OG Pharaoh, the progress value gets counted as if it was rounded
    // down to the lowest 20 points. No idea why! But here's as an option.

    float modifier = 1.f;
    const bool osiris_blessing = (g_city.religion.osiris_double_farm_yield_days > 0);
    if (building_is_floodplain_farm(base)) {
        if (osiris_blessing) {
            modifier = 2.f;
        } else {
            modifier = (1.f + d.produce_multiplier / 100.f);
        }
    } else {
        modifier = (1.f + d.produce_multiplier / 100.f);
    }
    d.produce_multiplier = 0.f;

    return int((progress / 2.5f) * modifier);
}


void building_farm::spawn_figure_harvests() {
    if (is_floodplain_farm()) { // floodplain farms
                                // In OG Pharaoh, farms can NOT send out a cartpusher if the cartpusher
                                // from the previous harvest is still alive. The farm will get "stuck"
                                // and remain in active production till flooded, though the farm worker
                                // still displays with the harvesting animation.
        if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
            return;
        }

        auto &d = runtime_data();
        if (base.has_road_access && d.progress > 0) {
            int farm_fertility = map_get_fertility_for_farm(tile());

            d.ready_production = d.progress * farm_fertility / 100;
            {
                const int expected_produce = this->expected_produce();
                events::emit(event_produced_resources{ base.output.resource, expected_produce });
                figure *f = create_cartpusher(base.output.resource, expected_produce);
                building_farm *farm = dcast_farm();
                farm->deplete_soil();

                f->sender_building_id = id();

                d.progress = 0;
                d.ready_production = 0;
                d.worker_id = 0;
                d.work_camp_id = 0;
                d.labor_state = LABOR_STATE_NONE;
                d.labor_days_left = 0;
                base.num_workers = 0;
            }

            if (base.output.resource_second != RESOURCE_NONE) {
                const int rate = std::max<int>(1, base.output_resource_second_rate);
                const int expected_produce = this->expected_produce();
                const int second_produce_expected = expected_produce / rate;
                events::emit(event_produced_resources{ base.output.resource_second, second_produce_expected });
                figure *f = create_cartpusher(base.output.resource_second, second_produce_expected, FIGURE_ACTION_20_INITIAL, BUILDING_SLOT_CARTPUSHER_2);
                f->sender_building_id = id();
            }
        }
    } else { // meadow farms
        if (base.has_road_access) {
            if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
                return;
            }

            const int amount = expected_produce();
            events::emit(event_produced_resources{ base.output.resource, amount });
            create_cartpusher(base.output.resource, amount);
            start_production();
        }
    }
}

void building_farm::add_workers(figure_id fid) {
    runtime_data().worker_id = fid;
}

void building_farm::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    if (d.worker_id == fid) {
        d.worker_id = 0;
    }
}

void building_farm::update_tiles_image() {
    bool is_flooded = false;
    if (building_is_floodplain_farm(base)) {
        for (int _y = tile().y(); _y < tile().y() + size(); _y++) {
            for (int _x = tile().x(); _x < tile().x() + size(); _x++) {
                if (map_terrain_is(MAP_OFFSET(_x, _y), TERRAIN_WATER))
                    is_flooded = true;
            }
        }
    }

    if (!is_flooded) {
        int img_id = anim(animkeys().farmland).first_img();
        map_building_tiles_add_farm(type(), id(), tile(), img_id + 5 * (base.output.resource - 1), progress());
    }
}

void building_farm::deplete_soil() {
    // DIFFERENT from original Pharaoh... and a bit easier to do?
    if (!!game_features::gameplay_change_soil_depletion) {
        int malus = (float)progress() / (float)MAX_PROGRESS_FARM_PH * (float)-100;
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    } else {
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                int new_fert = map_get_fertility(MAP_OFFSET(_x, _y), FERT_WITH_MALUS) * 0.2f;
                int malus = new_fert - map_get_fertility(MAP_OFFSET(_x, _y), FERT_NO_MALUS);
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    }
    update_tiles_image();
}