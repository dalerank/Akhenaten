#include "game.h"

#include "building/construction/build_planner.h"
#include "building/building_barracks.h"
#include "building/building_granary.h"
#include "building/building_burning_ruin.h"
#include "core/random.h"
#include "core/profiler.h"
#include "core/log.h"
#include "grid/vegetation.h"
#include "grid/trees.h"
#include "grid/canals.h"
#include "grid/natives.h"
#include "editor/editor.h"
#include "game/file_editor.h"
#include "graphics/font.h"
#include "graphics/image.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/scroll.h"
#include "game/game_config.h"
#include "config/hotkeys.h"
#include "io/gamefiles/lang.h"
#include "content/content.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "mission.h"
#include "figure/formation.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "window/intro_video.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/autoconfig_window.h"
#include "input/hotkey.h"
#include "graphics/view/view.h"
#include "platform/renderer.h"
#include "io/movie_writer.h"
#include "graphics/screen.h"
#include "widget/widget_minimap.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_population.h"
#include "city/city_desirability.h"
#include "city/city_message.h"
#include "city/city_industry.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/distant_battle.h"
#include "scenario/empire.h"
#include "empire/empire.h"
#include "grid/ring.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "content/mods.h"
#include "undo.h"
#include "window/file_dialog_common.h"

#include "dev/debug.h"
#include <iostream>

game_t game;
events::typed_queue g_permanent_events;

declare_console_ref_int16(gameyear, game.simtime.year)
declare_console_ref_uint8(gamemonth, game.simtime.month)

declare_console_command_p(nextyear) {
    game.simtime.advance_year();
    game.advance_year();
}
const e_sound_type_tokens_t ANK_CONFIG_ENUM(e_sound_type_tokens);

namespace {
    static time_millis last_update;
}

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
    if (!animation || paused) {
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

    g_city.population.housing_type_counts_update();
    random_generate_next();
    game_undo_reduce_time_available();

    g_floods.tick_update(false);

    g_city.buildings.update_tick(game.paused);

    g_city.update_tick(simtick);

    if (simtime.advance_tick()) {
        advance_day();
    }

    g_city.figures.update();

    g_scenario.update();
}

void game_t::advance_year() {
    scenario_empire_process_expansion();
    game_undo_disable();
    simtime.advance_year();
    city_population_request_yearly_update();
    g_city.finance.advance_year();
    g_city.migration.advance_year();
    g_city.monuments.advance_year();
    // Update ratings before resetting trade amounts so we can use last year's export data
    g_city.ratings_update(/*yearly_update*/true);
    g_empire.reset_yearly_trade_amounts();
    g_city.kingdome.advance_year();
    g_city.buildings.update_year();
    //    city_gods_reset_yearly_blessings();
}

void game_t::advance_week() {
    g_city.update_week(simtime);

    events::emit(event_advance_week::from_simtime(simtime));
}

void game_t::advance_month() {
    g_city.update_month(simtime);
    g_distant_battle.update_month();

    random_generate_next();                  // TODO: find out the source / reason for this
    g_empire.update_month();
    g_scenario.events.process_random_events();
    g_scenario.events.process_events();

    formation_update_monthly_morale_at_rest();
    city_message_decrease_delays();

    map_tiles_update_all_roads();
    //    map_tiles_river_refresh_entire();
    map_routing_update_land_citizen();
    //    city_message_sort_and_compact();

    if (simtime.advance_month()) {
        advance_year();
    }

    if (game_features::gameopt_monthly_autosave.to_bool()) {
        bstring256 autosave_file("autosave_month.", saved_game_data_expanded.extension);
        GamestateIO::write_savegame(autosave_file);
    }

    events::emit(event_advance_month::from_simtime(game.simtime));
}

void game_t::advance_day() {
    OZZY_PROFILER_FUNCTION();
    //    map_advance_floodplain_growth();

    day_result dr = simtime.advance_day();
    if (dr.month_advanced) {
        advance_month();
    }

    if (dr.week_advanced) {
        advance_week();
    }

    g_distant_battle.update_day();

    g_city.update_day(simtime);
    g_city.victory.victory_check();
    g_city.avg_coverage.update();

    g_sound.music_update(false);
    widget_minimap_invalidate();

    events::emit(event_advance_day::from_simtime(game.simtime));
}

void game_t::shutdown() {
    free(frame_pixels);
}

void game_t::set_write_video(bool v) {
    if (!write_video && v) {
        assert(!mvwriter);
        mvwriter = new MovieWriter("test.webm", screen_width(), screen_height(), 4);
    } else if (write_video && !v) {
        assert(mvwriter);
        delete mvwriter;
        mvwriter = nullptr;
    }
    write_video = v;
}

void game_t::write_frame() {
    if (!write_video) {
        return;
    }

    if (!mvwriter) {
        return;
    }

    last_frame_tick++;
    if (last_frame_tick % 30 != 0) {
        return;
    }
    last_frame_tick = 0;
    
    ::painter ctx = this->painter();
    if (!frame_pixels) {
        frame_pixels = (color*)malloc(sizeof(color) * screen_width() * screen_height());
    }

    if (!g_render.save_screen_buffer(ctx, frame_pixels, 0, 0, screen_width(), screen_height(), screen_width())) {
        free(frame_pixels);
        return;
    }

    mvwriter->addFrame((const uint8_t*)frame_pixels);
}

void game_t::reload_objects() {
    g_city.reload_objects();

    events::emit(event_game_scripts_was_reloaded{});
}

::painter game_t::painter() {
    ::painter ctx;
    ctx.view = &g_camera;
    ctx.renderer = g_render.renderer();
    ctx.global_render_scale = g_render.scale();

    return ctx;
}

void game_t::reload_language() {
    locale_determine_language();
}

void game_t::add_frame_end_event(serial_event_t ev) {
    std::lock_guard<std::mutex> lock(frame_end_events_mutex);
    frame_end_events.push_back(std::move(ev));
}

void game_t::execute_frame_end_events() {
    std::lock_guard<std::mutex> lock(frame_end_events_mutex);
    for (auto &ev : frame_end_events) {
        ev();
    }
    frame_end_events.clear();
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

static int get_elapsed_ticks() {
    if (game.paused || !city_has_loaded) {
        return 0;
    }

    int game_speed_index = 0;
    int ticks_per_frame = 1;
    pcstr meaning_windows[] = {
        "window_city",
        "window_city_military",
        "window_city_warship",
        "window_sliding_sidebar",
        "overlay_menu_widget",
        "build_menu_widget",
        "window_editor_map"
    };
    auto it = std::find_if(std::begin(meaning_windows), std::end(meaning_windows), [] (pcstr id) {
        return window_get_id() == id;
    });
    const bool empire_map_runs_sim = game_features::gameplay_change_empire_map_runs_simulation.to_bool()
        && window_get_id() == "window_empire";
    if (it != std::end(meaning_windows) || empire_map_runs_sim) {
        game_speed_index = (100 - game_features::gameopt_game_speed.to_int()) / 10;
        if (game_speed_index >= 10) {
            return 0;
        } else if (game_speed_index < 0) {
            ticks_per_frame = game_features::gameopt_game_speed.to_int() / 100;
            game_speed_index = 0;
        }
    } else {
        return 0;
    }

    if (g_city_planner.in_progress && game_features::gameplay_pause_sim_while_building.to_bool()) {
        return 0;
    }

    if (scroll_in_progress() && !scroll_is_smooth()) {
        return 0;
    }

    time_millis now = time_get_millis();
    time_millis diff = now - last_update;
    if (diff < game.tick_timer_ms) {
        return 0;
    }

    last_update = now;
    return ticks_per_frame;
}

bool game_t::check_valid() {
    vfs::content_cache_paths();

    vfs::path log_directory = vfs::platform_file_manager_get_base_path();
    if (g_args.is_integral_tests()) {
        log_directory = platform.user_directory();
    }
    logs::switch_output(log_directory.c_str());
    locale_determine_language();

    game_features::load();   // akhenaten.conf
    game_features::apply_cli_overrides(make_span(g_args.get_game_config_cli_overrides()));

    const auto game_speed = (int)calc_bound(game_features::gameopt_game_speed.to_int(), 10, 1000);
    game_features::gameopt_game_speed.set( game_speed );
    game_hotkeys::load();    // hotkeys.conf
    g_scenario.init();
    random_init();

    paused = false;
    unsigned int n = g_args.get_thread_count();
    if (n == 0) {
        n = std::thread::hardware_concurrency();
    }
    mt.reset(n);
    mtrpc.reset(n);

    return true;
}

bool game_init(game_opts opts) {
    if (!image_load_paks()) {
        logs::error("unable to load main graphics");
        return false;
    }

    if (!g_args.no_resource() && !game_load_campaign_file()) {
        logs::error("unable to load campaign data");
        return false;
    }

    mods_init();
    mods_load();
    mods_remount();

    if (!!(opts & game_opt_sound)) {
        g_sound.init();
    }

    game.init_state();

    if (g_args.no_logo()) {
        events::emit(event_show_main_menu{ true });
    } else {
        game.logo_show_patch_message = 0;
        if (!!game_features::gameui_show_intro_video && !g_args.no_intro()) {
            window_intro_video_show();
        } else {
            g_sound.play_intro();
            autoconfig_window::show("window_logo");
        }
    }

    return true;
}

bool game_init_editor() {
    locale_determine_language();

    game_file_editor_clear_data();
    game_file_editor_create_scenario(2);

    if (g_camera.sidebar_collapsed) {
        g_camera.toggle_sidebar();
    }

    editor_set_active(1);
    window_editor_map_show();
    return true;
}

void game_exit_editor() {
    locale_determine_language();

    editor_set_active(0);
    events::emit(event_show_main_menu{ true });
}

void game_t::update() {
    OZZY_PROFILER_FUNCTION();
    animation_timers_update();

    int num_ticks = get_elapsed_ticks();
    for (int i = 0; i < num_ticks; i++) {
        update_tick(simtime.tick);
    }

    if (g_window_manager.window_is("window_city")) {
        anti_scum_random_15bit();
    }

    events::emit(event_update_game_tick_timer{});
    events::process();
}

void game_t::frame_begin() {
    OZZY_PROFILER_FUNCTION();
    frame++;
    g_camera.frame_begin();
    window_draw(false);
}

void game_t::frame_end() {
    animation = true;

    execute_frame_end_events();
}

void game_t::time_init(int year) {
    simtime.init(year);
}

void game_t::init_state() {
    g_city.victory.reset();
    g_city.migration.reset();
    map_ring_init();

    g_camera.reset_orientation();
    //    city_view_go_to_screen_tile_corner(screen_tile(76, 152), true);

    random_generate_pool();
}

void game_t::city_sounds_frame_begin() {
    OZZY_PROFILER_FUNCTION();
    if (g_window_manager.window_is("window_city") || g_window_manager.window_is("window_city_military") || g_window_manager.window_is("window_city_warship") || g_window_manager.window_is("window_sliding_sidebar")) {
        sound_city_play();
    }
}

void game_t::before_start_simulation() {
    events::emit(event_advance_day::from_simtime(game.simtime));
}

void game_t::handle_input_frame() {
    OZZY_PROFILER_FUNCTION();
    const mouse& m = mouse::get();
    const hotkeys *h = hotkey_state();

    g_window_manager.handle_input(&m ,h);

    g_window_manager.update_input_after();
}

void game_t::exit() {
    video_shutdown();
    game_features::save();
    g_sound.shutdown();
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
