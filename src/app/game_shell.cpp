#include "game/game.h"
#include "core/draw_phase.h"

#include "game/video_capture_module.h"
#include "building/construction/build_planner.h"
#include "core/random.h"
#include "core/profiler.h"
#include "core/log.h"
#include "editor/editor.h"
#include "game/file_editor.h"
#include "graphics/image.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/scroll.h"
#include "game/game_config.h"
#include "config/hotkeys.h"
#include "io/gamefiles/lang.h"
#include "content/vfs.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "game/mission.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "window/intro_video.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/autoconfig_window.h"
#include "input/hotkey.h"
#include "graphics/view/view.h"
#include "graphics/render_device.h"
#include "content/mods.h"

::painter game_t::painter() {
    ::painter ctx;
    ctx.view = &g_camera;
    ctx.renderer = g_render.renderer();
    ctx.global_render_scale = g_render.scale();

    return ctx;
}

static time_millis last_update;

static int get_elapsed_ticks() {
    if (game.paused || !city_has_loaded) {
        return 0;
    }

    int game_speed_index = 0;
    int ticks_per_frame = 1;
    if (g_simulation.time_runs || game.pause_allow) {
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

    if (g_scroll.in_progress() && !g_scroll.is_smooth()) {
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
    anti_scum_set_clock_reseed(!g_args.is_integral_tests());

    game_features::load(g_args.features_profile(), g_args.get_game_config_cli_overrides());

    const auto game_speed = (int)calc_bound(game_features::gameopt_game_speed.to_int(), 10, 1000);
    game_features::gameopt_game_speed.set(game_speed);
    game_hotkeys::load(); // hotkeys.conf
    g_scenario.init();
    random_init();

    paused = false;
    pause_allow = false;
    unsigned int n = g_args.get_thread_count();
    if (n == 0) {
        n = std::thread::hardware_concurrency();
    }
    mt.reset(n);
    mtrpc.reset(n);

    return true;
}

bool game_init(game_opts opts) {
    // In the data dir, where saves and maps are read from, not in the working directory.
    auto data_folder = [](pcstr folder) {
        pcstr base = vfs::platform_file_manager_get_base_path();
        return (base && *base) ? vfs::path(base, "/", folder) : vfs::path(folder);
    };
    vfs::create_folders(vfs::content_path(vfs::save_folder().c_str()));
    vfs::create_folders(data_folder(vfs::MAPS_FOLDER));

    if (!image_load_paks()) {
        logs::error("unable to load main graphics");
        return false;
    }

    if (!g_args.no_resource() && !game_load_campaign_file()) {
        logs::error("unable to load campaign data");
        return false;
    }

    mods_init({g_args.get_mods_directory().c_str(), g_args.is_integral_tests()});
    mods_load();
    mods_remount();

    if (!!(opts & game_opt_sound)) {
        g_sound.init();
    }

    game.init_state();

    if (g_args.is_editor()) {
        return game_init_editor();
    }

    if (g_args.no_logo()) {
        events::emit(event_show_main_menu{true});
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
    events::emit(event_show_main_menu{true});
}

void game_t::update() {
    OZZY_PROFILER_FUNCTION();
    animation_timers_update();

    int num_ticks = get_elapsed_ticks();
    for (int i = 0; i < num_ticks; i++) {
        update_tick(g_simulation.simtime.tick);
        // Above 100% speed one frame runs several ticks; handlers must see the tick that emitted the event.
        events::process();
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
    draw_phase::scope draw_scope;
    window_draw(false);
}

void game_t::city_sounds_frame_begin() {
    OZZY_PROFILER_FUNCTION();
    if (g_window_manager.current_window && g_window_manager.current_window->city_sounds) {
        sound_city_play();
    }
}

void game_t::handle_input_frame() {
    OZZY_PROFILER_FUNCTION();
    const mouse& m = mouse::get();
    const hotkeys* h = &g_hotkeys;

    g_window_manager.handle_input(&m, h);

    g_window_manager.update_input_after();
}

void game_t::exit() {
    events::emit(event_game_exit_requested{});
    events::process();
    video_shutdown();
    game_features::save();
    g_sound.shutdown();
}

void game_t::shutdown() {
    events::emit(event_video_capture_stop{});
    events::process();
}
