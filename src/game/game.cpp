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
#include "game/settings.h"
#include "game/state.h"
#include "game/tutorial.h"
#include "graphics/font.h"
#include "graphics/image.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/scroll.h"
#include "game/game_config.h"
#include "config/hotkeys.h"
#include "io/gamefiles/lang.h"
#include "content/content.h"
#include "mission.h"
#include "figure/formation.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/logo_screen.h"
#include "window/main_menu.h"
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
#include "window/file_dialog.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "content/mods.h"
#include "undo.h"

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

uint16_t &game_speed() { return game.game_speed; }

namespace {
    static const time_millis MILLIS_PER_TICK_PER_SPEED[] = {0, 20, 35, 55, 80, 110, 160, 240, 350, 500, 700};
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
    OZZY_PROFILER_SECTION("Game/Update/Impl");
    if (editor_is_active()) {
        random_generate_next(); // update random to randomize native huts
        g_city.figures.update(); // just update the flag figures
        return;
    }

    random_generate_next();
    game_undo_reduce_time_available();

    g_tutorials_flags.update_starting_message();
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

    g_city.distant_battle.process();

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

    if (g_settings.monthly_autosave) {
        bstring256 autosave_file("autosave_month.", saved_game_data_expanded.extension);
        GamestateIO::write_savegame(autosave_file);
    }

    events::emit(event_advance_month::from_simtime(game.simtime));
}

void game_t::advance_day() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Advance Day");
    //    map_advance_floodplain_growth();

    day_result dr = simtime.advance_day();
    if (dr.month_advanced) {
        advance_month();
    }

    if (dr.week_advanced) {
        advance_week();
    }

    g_city.update_day(simtime);
    g_city.victory_check();

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
    ctx.view = &g_city_view;
    ctx.renderer = g_render.renderer();
    ctx.global_render_scale = g_render.scale();

    return ctx;
}

static void update_encoding() {
    int language = locale_determine_language();
}

static bool reload_language(int is_editor, int reload_images) {
    const xstring lang_dir = game_features::gameopt_language.to_string();
    //std::vector<lang_pack> lang_packs;
    //if (lang_dir.empty()) {
    //    lang_packs = get_def_lang_packs();
    //} else {
    //    lang_packs.emplace_back(lang_dir.c_str(), "loc", "Pharaoh_Text");
    //}

    //if (!lang_load(is_editor, lang_packs)) {
    //    if (is_editor)
    //        logs::error("'pharaoh_map.eng' or 'pharaoh_map_mm.eng' files not found or too large.");
    //    else
    //        logs::error("'pharaoh_text.eng' or 'pharaoh_mm.eng' files not found or too large.");
    //    return false;
    //}

    update_encoding();
    return true;
}

static int get_elapsed_ticks() {
    if (game.paused || !city_has_loaded) {
        return 0;
    }

    int game_speed_index = 0;
    int ticks_per_frame = 1;
    switch (window_get_id()) {
    default:
        return 0;

    case WINDOW_CITY:
    case WINDOW_CITY_MILITARY:
    case WINDOW_SLIDING_SIDEBAR:
    case WINDOW_OVERLAY_MENU:
    case WINDOW_BUILD_MENU:
        game_speed_index = (100 - game.game_speed) / 10;
        if (game_speed_index >= 10) {
            return 0;
        } else if (game_speed_index < 0) {
            ticks_per_frame = game.game_speed / 100;
            game_speed_index = 0;
        }
        break;

    case WINDOW_EDITOR_MAP:
        game_speed_index = 3; // 70%, nice speed for flag animations
        break;
    }

    if (g_city_planner.in_progress) {
        return 0;
    }

    if (scroll_in_progress() && !scroll_is_smooth()) {
        return 0;
    }

    time_millis now = time_get_millis();
    time_millis diff = now - last_update;
    if (diff < MILLIS_PER_TICK_PER_SPEED[game_speed_index] + 2) {
        return 0;
    }

    last_update = now;
    return ticks_per_frame;
}

bool game_t::check_valid() {
    vfs::content_cache_paths();

    logs::switch_output(vfs::platform_file_manager_get_base_path());
    update_encoding();
    g_settings.load(); // c3.inf
    game_features::load();   // akhenaten.conf
    game_hotkeys::load();    // hotkeys.conf
    g_scenario.init();
    random_init();

    paused = false;
    mt.reset(4);
    mtrpc.reset(4);

    return true;
}

bool game_init(game_opts opts) {
    if (!image_load_paks()) {
        logs::error("unable to load main graphics");
        return false;
    }

    if (!game_load_campaign_file()) {
        logs::error("unable to load campaign data");
        return false;
    }

    mods_init();
    mods_load();
    mods_remount();

    if (!!(opts & game_opt_sound)) {
        g_sound.init();
    }

    game_state_init();
    window_logo_show(MESSAGE_NONE);

    return true;
}

bool game_init_editor() {
    if (!reload_language(1, 0)) {
        return false;
    }

    game_file_editor_clear_data();
    game_file_editor_create_scenario(2);

    if (city_view_is_sidebar_collapsed()) {
        city_view_toggle_sidebar();
    }

    editor_set_active(1);
    window_editor_map_show();
    return true;
}

void game_exit_editor() {
    if (!reload_language(0, 0)) {
        return;
    }

    editor_set_active(0);
    main_menu_screen::show(/*restart_music*/true);
}

int game_reload_language() {
    return reload_language(0, 1);
}

void game_t::update() {
    OZZY_PROFILER_SECTION("Game/Update");
    animation_timers_update();

    int num_ticks = get_elapsed_ticks();
    for (int i = 0; i < num_ticks; i++) {
        update_tick(simtime.tick);
    }

    if (window_is(WINDOW_CITY)) {
        anti_scum_random_15bit();
    }

    events::process();
}

void game_t::frame_begin() {
    OZZY_PROFILER_SECTION("Render/Frame");
    frame++;
    window_draw(false);
}

void game_t::frame_end() {
    animation = true;
}

void game_t::time_init(int year) {
    simtime.init(year);
}

void game_t::sound_frame_begin() {
    OZZY_PROFILER_SECTION("Sound/Frame");
    sound_city_play();
}

void game_t::increase_game_speed() {
    if (game_speed >= 100) {
        if (game_speed < 1000)
            game_speed += 100;
    } else {
        game_speed = calc_bound(game_speed + 10, 10, 100);
    }
}

void game_t::decrease_game_speed() {
    if (game_speed > 100) {
        game_speed -= 100;
    } else {
        game_speed = calc_bound(game_speed - 10, 10, 100);
    }
}

void game_t::before_start_simulation() {
    events::emit(event_advance_day::from_simtime(game.simtime));

    events::subscribe([this] (event_toggle_pause) {
        paused = !paused;
    });

    events::subscribe([this] (event_change_gamespeed ev) {
        if (ev.value == HOTKEY_INCREASE_GAME_SPEED) {
            increase_game_speed();
        } else {
            decrease_game_speed();
        }
    });

    events::subscribe([] (event_save_city ev) {
        window_file_dialog_save_show(FILE_TYPE_SAVED_GAME);
    });

    events::subscribe([] (event_load_city ev) {
        window_file_dialog_load_show(FILE_TYPE_SAVED_GAME);
    });
}

void game_t::handle_input_frame() {
    OZZY_PROFILER_SECTION("Input/Frame/Current");
    const mouse& m = mouse::get();
    const hotkeys *h = hotkey_state();

    g_window_manager.handle_input(&m ,h);
    g_window_manager.handle_tooltip(&m);

    g_window_manager.update_input_after();
}

void game_t::exit() {
    video_shutdown();
    g_settings.save();
    game_features::save();
    g_sound.shutdown();
}
