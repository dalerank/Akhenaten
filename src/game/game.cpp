#include "game.h"

#include "building/construction/build_planner.h"
#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "building/building_burning_ruin.h"
#include "core/random.h"
#include "core/profiler.h"
#include "core/log.h"
#include "dev/debug.h"
#include "editor/editor.h"
#include "platform/arguments.h"
#include "game/sim_schedule.h"
#include "city/building_index.h"
#include "city/city_buildings.h"
#include "grid/vegetation.h"
#include "grid/trees.h"
#include "grid/canals.h"
#include "grid/natives.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "mission.h"
#include "figure/formation.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/scenario_invasion.h"
#include "graphics/view/view.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_population.h"
#include "city/city_desirability.h"
#include "city/city_message.h"
#include "city/city_industry.h"
#include "figuretype/figure_locust.h"
#include "scenario/distant_battle.h"
#include "scenario/empire.h"
#include "empire/empire.h"
#include "grid/ring.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "undo.h"


game_t game;
events::typed_queue g_permanent_events;

declare_console_ref_int16(gameyear, g_simulation.simtime.year);
declare_console_ref_uint8(gamemonth, g_simulation.simtime.month);

declare_console_command_p(nextyear) {
    g_simulation.simtime.advance_year();
    game.advance_year();
}
const e_sound_type_tokens_t ANK_CONFIG_ENUM(e_sound_type_tokens);

void game_t::animation_timers_init() {
    for (auto &timer: animation_timers) {
        timer.last_update = 0;
        timer.should_update = false;
    }
}

void game_t::animation_timers_update() {
    time_millis now_millis = time_get_millis();
    for (auto &timer : animation_timers) {
        timer.should_update = false;
    }

    unsigned int delay_millis = 0;
    for (auto &timer: animation_timers) {
        if (now_millis - timer.last_update >= delay_millis) {
            timer.should_update = true;
            timer.last_update = now_millis;
        }
        delay_millis += 20;
    }
}

bool game_t::animation_should_advance(uint32_t speed) {
    if (!animation || paused || redraw_read_only) {
        return false;
    }

    if (speed >= MAX_ANIM_TIMERS) {
        return false;
    }

    return animation_timers[speed].should_update;
}

void game_t::update_tick(int simtick) {
    OZZY_PROFILER_FUNCTION();
    if (editor_is_active()) {
        random_generate_next(); // update random to randomize native huts
        g_city.figures.update(); // just update the flag figures
        return;
    }

    static const bool guard_stub_records = g_args.is_integral_tests();
    if (guard_stub_records) {
        stub_records_guard_check("between ticks");
    }

    sim_schedule_run(SIM_PHASE_TICK_BEGIN, g_city);
    g_city.update_tick(simtick);

    if (g_simulation.simtime.advance_tick()) {
        advance_day();
    }

    sim_schedule_run(SIM_PHASE_TICK_END, g_city);

    if (guard_stub_records) {
        stub_records_guard_check("during tick");
        g_building_index.verify("during tick");
    }
}

void game_t::advance_year() {
    sim_schedule_run(SIM_PHASE_YEAR, g_city);
}

void game_t::advance_week() {
    sim_schedule_run(SIM_PHASE_WEEK, g_city);
}

void game_t::advance_month() {
    sim_schedule_run(SIM_PHASE_MONTH_CITY, g_city);
    sim_schedule_run(SIM_PHASE_MONTH, g_city);

    // OG advance_month: the yearly update recomputes the ratings, so December does not also run the monthly one.
    if (g_simulation.simtime.advance_month()) {
        advance_year();
    } else {
        g_city.ratings_update(/*yearly_update*/false);
    }

    sim_schedule_run(SIM_PHASE_MONTH_END, g_city);
}

void game_t::advance_day() {
    OZZY_PROFILER_FUNCTION();
    //    map_advance_floodplain_growth();

    day_result dr = g_simulation.simtime.advance_day();
    if (dr.month_advanced) {
        advance_month();
    }

    if (dr.week_advanced) {
        advance_week();
    }

    sim_schedule_run(SIM_PHASE_DAY, g_city);
}

void game_t::reload_objects() {
    g_city.reload_objects();

    events::emit(event_game_scripts_was_reloaded{});
}

void game_t::reload_language() {
    locale_determine_language();
}

void game_t::add_frame_end_event(serial_event_t ev) {
    std::lock_guard<std::mutex> lock(frame_end_events_mutex);
    frame_end_events.push_back(std::move(ev));
}

void game_t::execute_frame_end_events() {
    // A callback may queue the next frame. This mutex is not recursive, and clearing
    // after the loop would drop that event.
    hvector<serial_event_t, 16> batch;
    {
        std::lock_guard<std::mutex> lock(frame_end_events_mutex);
        for (auto &ev : frame_end_events) {
            batch.push_back(std::move(ev));
        }
        frame_end_events.clear();
    }
    for (auto &ev : batch) {
        ev();
    }
}

void game_t::add_frame_pre_present_handler(serial_event_t handler) {
    std::lock_guard<std::mutex> lock(frame_pre_present_handlers_mutex);
    frame_pre_present_handlers.push_back(std::move(handler));
}

void game_t::frame_pre_present() {
    std::lock_guard<std::mutex> lock(frame_pre_present_handlers_mutex);
    for (auto &handler : frame_pre_present_handlers) {
        handler();
    }
}

void game_t::add_frame_serial_part_handler(serial_event_t handler) {
    std::lock_guard<std::mutex> lock(frame_serial_part_handlers_mutex);
    frame_serial_part_handlers.push_back(std::move(handler));
}

void game_t::frame_serial_part() {
    std::lock_guard<std::mutex> lock(frame_serial_part_handlers_mutex);
    for (auto& handler : frame_serial_part_handlers) {
        handler();
    }
}

void game_t::add_frame_phase_ms_handler(frame_phase_ms_handler_t handler) {
    std::lock_guard<std::mutex> lock(frame_phase_ms_handlers_mutex);
    frame_phase_ms_handlers.push_back(std::move(handler));
}

void game_t::frame_phase_ms(double game_update_ms, double draw_ms) {
    std::lock_guard<std::mutex> lock(frame_phase_ms_handlers_mutex);
    for (auto &handler : frame_phase_ms_handlers) {
        handler(game_update_ms, draw_ms);
    }
}

void game_t::add_debug_ui_draw_handler(serial_event_t handler) {
    std::lock_guard<std::mutex> lock(debug_ui_draw_handlers_mutex);
    debug_ui_draw_handlers.push_back(std::move(handler));
}

void game_t::debug_ui_draw() {
    std::lock_guard<std::mutex> lock(debug_ui_draw_handlers_mutex);
    for (auto &handler : debug_ui_draw_handlers) {
        handler();
    }
}

void game_t::frame_end() {
    animation = true;

    execute_frame_end_events();
}

void game_t::init_state() {
    g_city.victory.reset();
    g_city.migration.reset();
    map_ring_init();

    g_camera.reset_orientation();
    //    city_view_go_to_screen_tile_corner(screen_tile(76, 152), true);

    random_generate_pool();
}

void game_t::before_start_simulation() {
    events::emit(event_advance_day::from_simtime(g_simulation.simtime));
}

bool game_t::is_fullscreen(bool check_cli) const {
    return game_features::gameopt_fullscreen.to_bool() && (check_cli ? cli_fullscreen : true);
}

void game_t::set_fullscreen(bool v) {
    game_features::gameopt_fullscreen.set(v);
}

uint8_t game_difficulty() {
    return game.difficulty.get();
}

void game_t::difficulty_t::set(e_difficulty v) {
    game_features::gameopt_difficulty.set( std::clamp<e_difficulty>(v, DIFFICULTY_VERY_EASY, DIFFICULTY_VERY_HARD) );
}

e_difficulty game_t::difficulty_t::get() const {
    return (e_difficulty)game_features::gameopt_difficulty.to_int();
}
