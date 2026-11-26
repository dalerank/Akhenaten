#include "city_figures.h"
#include "figure/route.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"
#include "city/city_figures_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"
#include "grid/figure.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "figure/figure_names.h"
#include "core/custom_span.hpp"
#include "core/random.h"
#include "city/city_buildings.h"
#include "grid/grid.h"

struct figure_data_t {
    //int created_sequence;
    bool initialized;
    std::array<figure *, MAX_FIGURES> figures;

    void init() {
        if (initialized) {
            return;
        }

        for (int i = 0; i < MAX_FIGURES; i++) {
            figures[i] = new figure(i);

        }

        initialized = true;
    }
};

figure_data_t g_figure_data = { false };

city_figures_t& city_figures() {
    return xvalue<city_figures_t>::ref();
}

void city_figures_t::reset() {
    *this = {};
}

void city_figures_t::clear_tick_counters() {
    enemies = 0;
    rioters = 0;
    attacking_natives = 0;
    animals_number = 0;
    kingdome_soldiers = 0;
    soldiers = 0;
    if (security_breach_duration > 0) {
        security_breach_duration--;
    }
}

void city_figures_t::init_figures() {
    g_figure_data.init();
}

void city_figures_t::reload_objects() {
    for (auto &figure : map_figures()) {
        if (!figure || figure->type == FIGURE_NONE) {
            continue;
        }

        figure->dcast()->on_config_reload();
    }
}

void city_figures_t::add_enemy() {
    enemies++;
}

int city_figures_t::total_invading_enemies() const {
    return kingdome_soldiers + enemies;
}

void city_figures_t::on_post_load() {
    for (auto &figure: map_figures()) {
        if (figure->type == FIGURE_NONE) {
            continue;
        }

        figure->reset_flags();
        figure->dcast()->on_post_load();
    }
}

void city_figures_t::update() {
    OZZY_PROFILER_FUNCTION();
    clear_tick_counters();
    //g_city.entertainment.hippodrome_has_race = false;

    for (auto &figure: map_figures()) {
        // Stray tile from a bad save or a broken move: used to be dropped by the draw sort.
        if (figure->tile.x() >= GRID_LENGTH || figure->tile.y() >= GRID_LENGTH) {
            figure->tile = {-1, -1};
            map_figure_draw_state_reset(figure->id);
            figure->poof();
        }
        figure->action_perform();
    }
}

void city_figures_t::add_animal() {
    animals_number++;
}

void city_figures_t::add_attacking_native() {
    security_breach_duration = 10;
    attacking_natives++;
}

void city_figures_t::remove_figures(e_figure_type ftype) {
    for (auto& f: g_figure_data.figures) {
        if (f->is_valid() && f->type == ftype) {
            f->poof();
        }
    }
}

void city_figures_t::add_kingdome_soldier() {
    kingdome_soldiers++;
}

void city_figures_t::add_rioter(int is_attacking) {
    rioters++;
    if (is_attacking)
        security_breach_duration = 10;
}

void city_figures_t::add_soldier() {
    soldiers++;
}

bool city_figures_t::has_security_breach() const {
    return security_breach_duration > 0;
}

void city_figures_t::update_day() {
    figure_valid_do([](figure& f) { f.dcast()->update_day(); });
}

figure *figure_get(int id) {
    verify_no_crash(id >= 0 && id < MAX_FIGURES);
    if (id < 0 || id >= MAX_FIGURES) {
        return figure_get(0);
    }
    return g_figure_data.figures[id];
}

xspan<figure *> map_figures() {
    return make_span(g_figure_data.figures.data(), g_figure_data.figures.size());
}

figure *figure_take_from_pool() {
    auto it = std::find_if(g_figure_data.figures.begin() + 1, g_figure_data.figures.end(), [] (auto &f) { return f->available(); });
    return it != g_figure_data.figures.end() ? *it : nullptr;
}

figure *figure_create(e_figure_type type, tile2i tile, int dir) {
    figure *f = figure_take_from_pool();
    if (!f) {
        return figure_get(0);
    }

    const auto &params = figure_static_params::get(type);

    f->state = FIGURE_STATE_ALIVE;
    f->faction_id = 1;
    f->type = type;
    f->use_cross_country = false;
    f->terrain_usage = -1;

    f->reset_flags();

    f->direction = dir;
    f->roam_length = 0;
    f->source_tile = tile;
    f->destination_tile = tile;
    f->previous_tile = tile;
    f->tile = tile;
    f->destination_tile.set(0, 0);
    f->cc_coords.x = 15 * tile.x();
    f->cc_coords.y = 15 * tile.y();
    f->progress_on_tile = 8;
    f->progress_inside = 0;
    f->progress_inside_speed = 0;
    // OG figure_create draws one crt_rand for the phrase sequences; gods/floods share that stream.
    anti_scum_random_15bit();
    f->name = figure_name_get(type, f->id);
    f->map_figure_add();

    f->dcast()->on_create();

    return f;
}

void figure_clear_all() {
    stub_records_guard_reset();
    if (!g_figure_data.initialized) {
        return;
    }

    for (auto *f : g_figure_data.figures) {
        int figure_id = f->id;
        f->clear_impl();
        f->debug_lines_clear();
        memset(f, 0, sizeof(figure));
        f->state = FIGURE_STATE_NONE;
        f->id = figure_id;
    }
}

class figures_system : public sim_system {
public:
    const char* name() const override { return "figures"; }
    void on_reset() override {
        city_figures().reset();
        city_figures().init_figures();
        figure_clear_all();
        figure_route_clear_all();
        map_figure_draw_states_clear_all();
    }
    void push_save_sections(int file_version) override {
        g_chunk_io.push_chunk<city_figures_chunk>(city_figures_chunk::size, false);
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_figures, SIM_PHASE_TICK_END, [](int) { city_figures().update(); }});
        schedule.add({sim_step_figures_day, SIM_PHASE_DAY, [](int) { city_figures().update_day(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_figures_system) {
    static figures_system system;
    g_simulation.register_system(&system);
}
