#include "building_farm.h"

#include "building/building_granary.h"
#include "core/object_property.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "game/resource.h"
#include "game/game.h"
#include "game/game_events.h"
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
#include "figuretype/figure_worker.h"
#include "grid/tiles.h"
#include "figuretype/figure_cartpusher.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_farm)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_grain);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_grain);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_lettuce);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_lettuce);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_chickpeas);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_chickpeas);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_pomegranates);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_pomegranates);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_barley);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_barley);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_flax);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_flax);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_henna);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_henna);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_farm_figs);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_meadow_farm_figs);

using e_farm_worker_state_tokens_t = token_holder<e_farm_worker_state, e_farm_worker_tiling, e_farm_worker_count>;
const e_farm_worker_state_tokens_t ANK_CONFIG_ENUM(e_farm_worker_state_tokens);

void building_farm::map_building_tiles_add_farm(e_building_type type, int building_id, tile2i tile, int progress) {
    building *b = building_get(building_id);
    map_building_tiles_add(building_id, tile, b->size, get_farm_image(type, tile), TERRAIN_BUILDING);
}

bool building_farm::target_route_tile_blocked(int grid_offset) const {
    return false;
}

int building_farm::get_crops_image(e_building_type type, int growth) {
    const auto &params = building_static_params::get(type);
    return params.first_img(animkeys().crops) + growth;
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
    if (action < 0 || action >= e_farm_worker_count) {
        return;
    }

    pcstr anim_key = std::array{ "tiling", "seeding", "harvesting" } [action] ;

    auto &context = base.anims[0];
    context.setup(anim(anim_key));

    auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_sprite);
    command.image_id = context.start_frame() + direction + 8 * context.current_frame();
    command.pixel = coords + context.pos;
    command.mask = color_mask;
}

void building_farm::draw_crops(painter &ctx, e_building_type type, int progress, tile2i tile, vec2i point, color color_mask) {
    int image_crops = get_crops_image(type, 0);

    // Layout follows terrain (not building type). Offset tables SoT = JS tile_offsets on
    // canonical grain farms — cast to shared farm_params_t so ?: branches share one type.
    const farm_params_t &layout = map_terrain_is(tile, TERRAIN_FLOODPLAIN)
        ? static_cast<const farm_params_t &>(building_farm_grain::current_params())
        : static_cast<const farm_params_t &>(building_meadow_farm_grain::current_params());
    const auto &offsets = layout.tile_offsets;
    if (offsets.empty()) {
        return;
    }

    const int step = offsets.size() >= 9 ? 200 : 400;
    for (int i = 0; i < (int)offsets.size(); i++) {
        int growth_offset = fmin(5, fmax(0, (progress - i * step) / 100));

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_from_below);
        command.image_id = image_crops + growth_offset;
        command.pixel = point + offsets[i];
        command.mask = color_mask;
    }
}

bool building_farm::requested_workers() const {
    auto &d = runtime_data();
    return !d.worker_id && d.labor_days_left <= 47 && !num_workers();
}

void building_farm::draw_workers(painter &ctx, building *b, tile2i tile, vec2i pos) {
    if (b->num_workers == 0) {
        return;
    }

    auto &d = runtime_data();

    pos += {30, -15};
    int direction = map_random_get(b->tile.grid_offset()) % 8;
    const bool flood_imminent = b->is_floodplain_farm() && g_floods.state_is(FLOOD_STATE_IMMINENT);

    direction = (direction >= 0) ? direction : (game.simtime.absolute_tick() % 128 / 16);
    vec2i coords = farm_params().tile_coord(pos, d.worker_tile.x, d.worker_tile.y);
    draw_farm_worker(ctx, direction, d.worker_action, coords);
}

bool building_farm::time_to_deliver(bool floodplains, int resource_id) {
    if (floodplains) {
        float current_cycle = g_floods.current_cycle();
        float start_cycle = g_floods.start_cycle();
        float harvest_cycle = start_cycle - 28.0f;
        return g_floods.state_is(FLOOD_STATE_IMMINENT) && (current_cycle >= harvest_cycle);
    } else {
        const auto &months = farm_params().month_harvest;
        const bool is_correct_month = std::count(months.begin(), months.end(), game.simtime.month) > 0;
        // OG: day == 0 only. Remake retry window (day < 2) behind the feature flag.
        const int day_limit = game_features::gameplay_change_farm_meadow_harvest_retry.to_bool() ? 2 : 1;
        return is_correct_month && game.simtime.day < day_limit;
    }
}

void building_farm::on_create(int orientation) {
    auto &d = runtime_data();
    base.progress_max = 2000;
    d.is_floodplain = base.is_floodplain_farm();
}

void building_farm::on_post_load() {
    building_impl::on_post_load();
    runtime_data().is_floodplain = base.is_floodplain_farm();
    restore_tiles_if_emerged();
}

void building_farm::on_place_update_tiles(int orientation, int variant) {
    map_building_tiles_add_farm(type(), id(), tile(), 0);
}

bool building_farm::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i t, color mask) {
    if (is_currently_flooded()) {
        return true;
    }
    draw_crops(ctx, type(), base.progress, tile(), point, mask);
    draw_workers(ctx, &base, t, point);

    return true;
}

void building_farm::draw_normal_anim(painter &ctx, vec2i pixel, tile2i tile, color mask) {
    if (!base.anim.valid()) {
        return;
    }

    if (!base.play_animation) {
        return;
    }

    vec2i pos = pixel + base.anim.pos;
    ctx.img_sprite(base.anim.start_frame() + base.anim.current_frame(), pos, mask);
}

void building_farm::update_count() const {
    building_impl::update_count();

    static std::pair<e_building_type, e_resource> farms[] = {
        {BUILDING_GRAIN_FARM, RESOURCE_GRAIN},
        {BUILDING_GRAIN_MEADOW_FARM, RESOURCE_GRAIN},
        {BUILDING_BARLEY_FARM, RESOURCE_BARLEY},
        {BUILDING_BARLEY_MEADOW_FARM, RESOURCE_BARLEY},
        {BUILDING_FLAX_FARM, RESOURCE_FLAX},
        {BUILDING_FLAX_MEADOW_FARM, RESOURCE_FLAX},
        {BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE},
        {BUILDING_LETTUCE_MEADOW_FARM, RESOURCE_LETTUCE},
        {BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES},
        {BUILDING_POMEGRANATES_MEADOW_FARM, RESOURCE_POMEGRANATES},
        {BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS},
        {BUILDING_CHICKPEAS_MEADOW_FARM, RESOURCE_CHICKPEAS},
        {BUILDING_FIGS_FARM, RESOURCE_FIGS},
        {BUILDING_FIGS_MEADOW_FARM, RESOURCE_FIGS},
        {BUILDING_HENNA_FARM, RESOURCE_HENNA},
        {BUILDING_HENNA_MEADOW_FARM, RESOURCE_HENNA}
    };
    auto it = std::find_if(std::begin(farms), std::end(farms), [btype = type()](auto &t) { return t.first == btype; });
    g_city.buildings.increase_industry_count(it->second, num_workers() > 0);
}

void building_farm::update_month() {
    building_impl::update_month();

    figure_id fid = runtime_data().worker_id;
    auto worker = figure_get(fid)->dcast_worker();
    if (!worker || !worker->is_destination(&base)) {
        runtime_data().worker_id = 0;
    }
}

void building_farm::spawn_figure() {
    bool is_floodplain = base.is_floodplain_farm();
    if (!is_floodplain && has_road_access()) { // only for meadow farms
        common_spawn_labor_seeker(current_params().min_houses_coverage);
        if (time_to_deliver(false, base.output.resource)) { // UGH!!
            spawn_figure_harvests();
        }
    } else if (is_floodplain) {
        if (time_to_deliver(true)) {
            spawn_figure_harvests();
        }
    }
}

void building_farm::update_graphic() {
    building_impl::update_graphic();
}

void building_farm::on_undo() {
    map_building_tiles_add_farm(type(), id(), tile(), 0);
}

void building_farm::on_tick(bool refresh) {
    building_impl::on_tick(refresh);

    auto &d = runtime_data();
    d.is_floodplain = base.is_floodplain_farm();
    d.flood_imminent = (d.is_floodplain && g_floods.state_is(FLOOD_STATE_IMMINENT));
    restore_tiles_if_emerged();
}

void building_farm::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(22);
    iob->bind____skip(48);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT16, &base.progress_max);
    iob->bind____skip(1); // was produce_multiplier (removed; keep save layout)
    iob->bind(BIND_SIGNATURE_UINT16, &d.work_camp_id);
    iob->bind(BIND_SIGNATURE_UINT16, &d.worker_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.labor_state);
    iob->bind(BIND_SIGNATURE_UINT8, &d.labor_days_left);
    iob->bind(BIND_SIGNATURE_UINT16, &base.progress);
    iob->bind____skip(1);
}

void building_farm::start_production() {
    base.progress = 0;
    update_tiles_image();
}

void building_farm::add_tiles() {
    map_building_tiles_add_farm(type(), id(), tile(), 0);
}

int building_farm::expected_produce() {
    auto &d = runtime_data();

    int progress = d.ready_production > 0
        ? d.ready_production
        : base.progress;

    if (!game_features::gameplay_fix_farm_produce_quantity) {
        progress = (progress / 20) * 20;
    }
    // In OG Pharaoh, the progress value gets counted as if it was rounded
    // down to the lowest 20 points. No idea why! But here's as an option.

    // OG farm_harvest_loads: floodplain harvest doubles while the city Osiris flag is set.
    float modifier = 1.f;
    if (base.is_floodplain_farm() && g_city.religion.osiris_double_farm_yield_days > 0) {
        modifier = 2.f;
    }

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
        if (base.has_road_access && base.progress > 0) {
            if (!!game_features::gameplay_change_farm_harvest_fertility) {
                const int farm_fertility = map_get_fertility_for_farm(tile());
                d.ready_production = base.progress * farm_fertility / 100;
            } else {
                d.ready_production = 0;
            }
            // OG: any floodplain harvest under the blessing marks the flag used; clear after the wave.
            if (g_city.religion.osiris_double_farm_yield_days > 0) {
                g_city.religion.osiris_double_farm_yield_used = true;
            }
            const int primary = this->expected_produce();
            produced_resources(base.output.resource, primary);
            figure *f = create_cartpusher(base.output.resource, primary, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
            deplete_soil();
            f->sender_building_id = id();

            // OG building_figure.c: grain harvest also sends a fixed 100-load straw cart (not progress-based).
            if (base.output.resource_second != RESOURCE_NONE
                && !g_city.resource.is_mothballed(base.output.resource_second)) {
                const int secondary = 100;
                produced_resources(base.output.resource_second, secondary);
                figure *f2 = create_cartpusher(base.output.resource_second, secondary,
                    (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER_2);
                f2->sender_building_id = id();
            }

            base.progress = 0;
            d.ready_production = 0;
            d.worker_id = 0;
            d.work_camp_id = 0;
            d.labor_state = LABOR_STATE_NONE;
            d.labor_days_left = 0;
            base.num_workers = 0;
        }
    } else { // meadow farms
        if (base.has_road_access) {
            if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
                return;
            }

            const int primary = expected_produce();
            produced_resources(base.output.resource, primary);
            create_cartpusher(base.output.resource, primary, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);

            if (base.output.resource_second != RESOURCE_NONE
                && !g_city.resource.is_mothballed(base.output.resource_second)) {
                const int secondary = 100;
                produced_resources(base.output.resource_second, secondary);
                figure *f2 = create_cartpusher(base.output.resource_second, secondary,
                    (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER_2);
                f2->sender_building_id = id();
            }
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

bool building_farm::is_currently_flooded() const {
    if (!base.is_floodplain_farm()) {
        return false;
    }

    for (int _y = tile().y(); _y < tile().y() + size(); _y++) {
        for (int _x = tile().x(); _x < tile().x() + size(); _x++) {
            const int offset = MAP_OFFSET(_x, _y);
            // Nile tiles in a 3x3 edge farm stay WATER year-round — only floodplain water is inundation.
            if (map_terrain_is(offset, TERRAIN_FLOODPLAIN) && map_terrain_is(offset, TERRAIN_WATER)) {
                return true;
            }
        }
    }

    return false;
}

bool building_farm::allow_demolish() const {
    return !is_currently_flooded();
}

xstring building_farm::demolish_blocked_message() const {
    return is_currently_flooded() ? xstring("#cannot_demolish_flooded_farm") : xstring{};
}

void building_farm::restore_tiles_if_emerged() {
    if (!base.is_floodplain_farm() || !base.is_valid()) {
        return;
    }
    if (is_currently_flooded()) {
        return;
    }
    if (map_terrain_is(tile(), TERRAIN_BUILDING)) {
        return;
    }
    add_tiles();
}

void building_farm::update_tiles_image() {
    if (!is_currently_flooded()) {
        map_building_tiles_add_farm(type(), id(), tile(), base.progress);
    }
}

void building_farm::deplete_soil() {
    // DIFFERENT from original Pharaoh... and a bit easier to do?
    if (!!game_features::gameplay_change_soil_depletion) {
        int malus = (float)base.progress / (float)current_params().progress_max * (float)-100;
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    } else {
        // OG farm_reduce_fertility_of: an irrigated farm loses 50%, a dry one 80%, never below 1.
        const int keep = map_is_irrigated_for_farm(tile()) ? 50 : 20;
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                const int fert = map_get_fertility(MAP_OFFSET(_x, _y), FERT_WITH_MALUS);
                int new_fert = std::max(1, fert * keep / 100);
                int malus = new_fert - map_get_fertility(MAP_OFFSET(_x, _y), FERT_NO_MALUS);
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    }
    update_tiles_image();
}

int building_farm::food_warning() {
    // OG map/farm.c building_farm_food_warning — once near flood start.
    enum {
        PRODUCE_FACTOR = 8,
        MIN_PRODUCE = 800,
        GRANARY_GAP = 50,
        GRANARIES_GAP = 3200,
    };

    int produced = 0;
    buildings_valid_do([&](building &b) {
        if (!b.is_floodplain_farm()) {
            return;
        }
        // Industrial crops are not food for this warning.
        switch (b.type) {
        case BUILDING_BARLEY_FARM:
        case BUILDING_FLAX_FARM:
        case BUILDING_HENNA_FARM:
            return;
        default:
            break;
        }

        const int fert = map_get_fertility_for_farm(b.tile);
        const int laborers = building_static_params::get(b.type).laborers;
        // OG: fertility * 0.16 * (1/99) * laborers * 10
        const int expected = std::max(1, (int)((double)fert * 0.16 * (1.0 / 99.0) * laborers * 10.0));
        const int progress_max = b.progress_max > 0 ? b.progress_max : 2000;
        const int growth_pct = calc_percentage<int>(b.progress, progress_max);
        int amount = (expected + growth_pct) * PRODUCE_FACTOR;
        if (amount < MIN_PRODUCE) {
            amount = MIN_PRODUCE;
        }
        if (g_city.religion.osiris_double_farm_yield_days > 0) {
            amount += amount;
        }
        produced += amount;
    });

    int free_space = 0;
    buildings_valid_do([&](building &b) {
        if (b.type != BUILDING_GRANARY && b.type != BUILDING_GRANARY_UP) {
            return;
        }
        auto *g = b.dcast_granary();
        if (g) {
            free_space += g->freespace();
        }
    });

    const int gap = produced - free_space;
    if (gap > GRANARIES_GAP) {
        events::emit(event_city_warning{ "#build_granaries" });
        return 2;
    }
    if (gap > GRANARY_GAP) {
        events::emit(event_city_warning{ "#build_granary" });
        return 1;
    }
    return 0;
}