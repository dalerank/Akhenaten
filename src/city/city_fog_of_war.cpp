#include "city/city_fog_of_war.h"

#include "building/building.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_fog_of_war_chunks.h"
#include "core/app_module.h"
#include "core/log.h"
#include "core/profiler.h"
#include "core/xvalue.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/sim_schedule.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"
#include "scenario/scenario.h"

#include <algorithm>

city_fog_of_war_t& city_fog_of_war() {
    return xvalue<city_fog_of_war_t>::ref();
}

class fog_of_war_system : public sim_system {
public:
    const char* name() const override { return "fog_of_war"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_fog_of_war, SIM_PHASE_TICK_END, [](int tick) { city_fog_of_war().update(tick); }});
    }
    void on_reset() override { city_fog_of_war().reset(); }
    void on_reload_config() override { city_fog_of_war().reload_config(); }
    void push_save_sections() override { g_chunk_io.push_chunk<city_fog_of_war_chunk>(GRID_SIZE_TOTAL, false); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_fog_of_war_system) {
    static fog_of_war_system system;
    g_simulation.register_system(&system);
}

namespace {

    int8_t clamp_radius(int radius) {
        return (int8_t)std::clamp(radius, -1, 127);
    }

    bool tile_on_map(int x, int y) {
        return x >= 0 && y >= 0 && x < map_grid_width() && y < map_grid_height();
    }

} // namespace

void city_fog_of_war_t::reset() {
    reach.fill(reach_far);
    active = false;
    reload_config();
}

void city_fog_of_war_t::reload_config() {
    config = {};
    const bool ok = g_config_arch.r("city_fog_of_war", config);
    verify_no_crash_var(ok, "Variable not exist in config: %s", "city_fog_of_war");
    if (config.update_every_ticks <= 0 || 50 % config.update_every_ticks != 0) {
        logs::warn("[fog_of_war] update_every_ticks %d does not divide 50, using 5", config.update_every_ticks);
        config.update_every_ticks = 5;
    }

    radius_of_building.fill(no_radius);
    for (const auto& row : config.building_radius) {
        if (row.building > BUILDING_NONE && row.building < BUILDING_MAX) {
            radius_of_building[row.building] = clamp_radius(row.radius);
        }
    }

    radius_of_figure.fill(no_radius);
    for (const auto& row : config.figure_radius) {
        if (row.figure > FIGURE_NONE && row.figure < FIGURE_MAX) {
            radius_of_figure[row.figure] = clamp_radius(row.radius);
        }
    }

    radius_of_category.fill(-1);
    for (const auto& row : config.figure_radius_by_category) {
        if (row.category >= figure_category_inactive && row.category < figure_category_max) {
            radius_of_category[row.category] = clamp_radius(row.radius);
        }
    }
}

void city_fog_of_war_t::set_editor(bool editor) {
    in_editor = editor;
    if (editor) {
        active = false;
    }
}

bool city_fog_of_war_t::sync_active() {
    const bool was = active;
    active = !in_editor && !!game_features::gameplay_enhanced_fog_of_war && g_scenario.fog_of_war.enabled;
    return !was && active;
}

bool city_fog_of_war_t::any_explored() const {
    auto& grid = city_fog_of_war_chunk::grid;
    const int w = map_grid_width();
    const int h = map_grid_height();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (map_grid_get(grid, MAP_OFFSET(x, y))) {
                return true;
            }
        }
    }
    return false;
}

bool city_fog_of_war_t::is_explored(tile2i tile) const {
    if (!active) {
        return true;
    }
    const int offset = tile.grid_offset();
    if (!map_grid_is_valid_offset(offset)) {
        return false;
    }
    return map_grid_get(city_fog_of_war_chunk::grid, offset) != 0;
}

bool city_fog_of_war_t::is_visible(tile2i tile) const {
    if (!active) {
        return true;
    }
    const int offset = tile.grid_offset();
    if (!map_grid_is_valid_offset(offset)) {
        return false;
    }
    return reach[offset] >= 0;
}

e_fog_shade city_fog_of_war_t::shade(tile2i tile) const {
    if (!active) {
        return fog_visible;
    }
    const int offset = tile.grid_offset();
    if (!map_grid_is_valid_offset(offset)) {
        return fog_visible;
    }
    if (reach[offset] >= 0) {
        return fog_visible;
    }
    return map_grid_get(city_fog_of_war_chunk::grid, offset) ? fog_fogged : fog_unexplored;
}

int city_fog_of_war_t::edge(tile2i tile) const {
    if (!active) {
        return 0;
    }
    const int offset = tile.grid_offset();
    if (!map_grid_is_valid_offset(offset) || reach[offset] < 0) {
        return 0;
    }
    return std::max(0, config.soft_edge_tiles - reach[offset]);
}

int city_fog_of_war_t::building_vision(const building& b) const {
    const int8_t by_type = radius_of_building[b.type];
    if (by_type != no_radius) {
        return by_type;
    }
    for (const auto& row : config.building_radius_by_size) {
        if (row.size == b.size) {
            return row.radius;
        }
    }
    return config.default_building_radius;
}

int city_fog_of_war_t::figure_vision(const figure& f) const {
    if (f.type <= FIGURE_NONE || f.type >= FIGURE_MAX) {
        return -1;
    }
    const int8_t by_type = radius_of_figure[f.type];
    if (by_type != no_radius) {
        return by_type;
    }
    const e_figure_category category = f.category();
    if (category < figure_category_inactive || category >= figure_category_max) {
        return -1;
    }
    return radius_of_category[category];
}

bool city_fog_of_war_t::figure_seen(const figure& f) const {
    if (!active) {
        return true;
    }
    if (figure_vision(f) >= 0) {
        return true;
    }
    return is_visible(f.tile);
}

void city_fog_of_war_t::reveal_area(tile2i center, int radius) {
    if (!center.valid() || radius < 0) {
        return;
    }
    auto& grid = city_fog_of_war_chunk::grid;
    for (int y = center.y() - radius; y <= center.y() + radius; ++y) {
        for (int x = center.x() - radius; x <= center.x() + radius; ++x) {
            if (tile_on_map(x, y)) {
                map_grid_set(grid, MAP_OFFSET(x, y), 1);
            }
        }
    }
}

void city_fog_of_war_t::reveal_rect(tile2i from, tile2i to) {
    auto& grid = city_fog_of_war_chunk::grid;
    for (int y = std::min(from.y(), to.y()); y <= std::max(from.y(), to.y()); ++y) {
        for (int x = std::min(from.x(), to.x()); x <= std::max(from.x(), to.x()); ++x) {
            if (tile_on_map(x, y)) {
                map_grid_set(grid, MAP_OFFSET(x, y), 1);
            }
        }
    }
}

void city_fog_of_war_t::initial_reveal() {
    const auto& mission = g_scenario.fog_of_war;
    const int radius = mission.initial_reveal_radius > 0 ? mission.initial_reveal_radius : config.initial_reveal_radius;
    reveal_area(g_scenario.entry_point, radius);
    reveal_area(g_scenario.river_entry_point, radius);
    for (const auto& area : mission.reveal) {
        if (area.radius > 0) {
            reveal_area(area.tile, area.radius);
        } else if (area.from.valid() && area.to.valid()) {
            reveal_rect(area.from, area.to);
        }
    }
    recompute(true);
}

void city_fog_of_war_t::recompute(bool explore) {
    OZZY_PROFILER_FUNCTION();
    if (!active) {
        return;
    }

    reach.fill(reach_far);
    auto seed = [this](int x, int y, int radius) {
        if (radius < 0 || !tile_on_map(x, y)) {
            return;
        }
        int8_t& v = reach[MAP_OFFSET(x, y)];
        v = std::max<int8_t>(v, (int8_t)radius);
    };

    buildings_valid_do([&](building& b) {
        const int radius = building_vision(b);
        if (radius < 0) {
            return;
        }
        const int size = std::max<int>(1, b.size);
        for (int dy = 0; dy < size; ++dy) {
            for (int dx = 0; dx < size; ++dx) {
                seed(b.tile.x() + dx, b.tile.y() + dy, radius);
            }
        }
    });

    for (figure* f : map_figures()) {
        if (!f || !f->is_alive()) {
            continue;
        }
        seed(f->tile.x(), f->tile.y(), figure_vision(*f));
    }

    map_grid_king_reach(make_span(reach.data(), reach.size()));

    if (!explore) {
        return;
    }

    auto& grid = city_fog_of_war_chunk::grid;
    bool changed = false;
    const int w = map_grid_width();
    const int h = map_grid_height();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const int offset = MAP_OFFSET(x, y);
            if (reach[offset] >= 0 && !map_grid_get(grid, offset)) {
                map_grid_set(grid, offset, 1);
                changed = true;
            }
        }
    }
    if (changed) {
        events::emit(event_fog_explored{});
    }
}

void city_fog_of_war_t::on_post_load() {
    sync_active();
    if (!active) {
        return;
    }
    if (!any_explored()) {
        initial_reveal();
        return;
    }
    recompute(false);
}

void city_fog_of_war_t::update(int tick) {
    const bool turned_on = sync_active();
    if (!active) {
        return;
    }
    if (turned_on && !any_explored()) {
        initial_reveal();
        return;
    }
    if (turned_on || tick % config.update_every_ticks == 0) {
        recompute(true);
    }
}
