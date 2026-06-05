#include "core/app.h"

#include "core/encoding.h"
#include "core/stacktrace.h"
#include "core/log.h"
#include "figure/figure.h"
#include "js/js.h"
#include "js/js_game.h"
#include "core/profiler.h"
#include "game/game.h"
#include "game/system.h"
#include "graphics/screen.h"
#include "content/vfs.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "platform/arguments.h"
#include "platform/integral_tests.h"
#include "platform/cursor.h"
#include "content/content.h"
#include "platform/platform.h"
#include "platform/prefs.h"
#include "platform/screen.h"
#include "platform/version.hpp"
#include "platform/options_window.h"
#include "widget/debug_console.h"
#include "window/autoconfig_window.h"
#include "graphics/imagepak_holder.h"
#include "game/mission.h"
#include "sound/sound.h"
#include "scenario/scenario.h"
#include "core/cstring.h"
#include "renderer.h"

#include <SDL.h>

#include <filesystem>
#include <set>
#include <platform/android/android.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "dev/imguifiledialog.h"
#include "misc/cpp/imgui_stdlib.h"

#ifdef GAME_PLATFORM_BROWSER
#include <emscripten/emscripten.h>
#endif

#include "dev/perfmon.h"
#include "dev/perfmon_nanoprofiler.h"

#if defined(_WIN32)

#include <string.h>

#if !defined(GAME_PLATFORM_WIN)
#include <bits/exception_defines.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#endif

#include "graphics/graphics.h"
#include "graphics/text.h"
#include "graphics/window.h"

static_assert(SDL_VERSION_ATLEAST(2, 0, 17));
#define URL_PATCHES "https://github.com/dalerank/akhenaten/wiki/Patches"
#define URL_EDITOR  "https://github.com/dalerank/akhenaten/wiki/Editor"

namespace {

    void show_usage() {
        platform_screen_show_error_message_box("Command line interface", Arguments::usage());
    }

} // namespace

static int init_sdl() {
    logs::info("Initializing SDL");
    Uint32 SDL_flags = SDL_INIT_VIDEO;

    if (g_args.use_sound()) {
        SDL_flags |= SDL_INIT_AUDIO;
    }

    SDL_flags |= platform.sdl_init_flags();

    if (SDL_Init(SDL_flags) != 0) {
        logs::error("Could not initialize SDL: %s", SDL_GetError());
        return 0;
    }

    static_assert(SDL_VERSION_ATLEAST(2, 0, 10), "SDL version too old");
    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    // SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
    platform.post_hint_init();
    logs::info("SDL initialized");
    return 1;
}

bool pre_init_dir_attempt(const xstring& data_dir, pcstr lmsg) {
    logs::info(lmsg, data_dir.c_str()); // TODO: get rid of data ???
    const bool ok = vfs::platform_file_manager_set_base_path(data_dir.c_str());
    if (!ok) {
        logs::info("%s: directory not found", data_dir.c_str());
    }

    if (game.check_valid()) {
        return true;
    }

    return false;
}

static bool pre_init(const xstring& custom_data_dir) {
    if (pre_init_dir_attempt(custom_data_dir, "Attempting to load game from %s")) {
        return true;
    }

    logs::info("Attempting to load game from working directory");
    if (game.check_valid()) {
        return true;
    }

    if (!platform.is_android()) {
        pstr tmp_path = platform.is_macos() ? SDL_GetPrefPath("", "Akhenaten") : SDL_GetBasePath();
        xstring base_path(tmp_path);
        SDL_free(tmp_path);
        if (pre_init_dir_attempt(base_path, "Attempting to load game from base path %s")) {
            return true;
        }
    }

    const char* user_dir = pref_get_gamepath();
    if (user_dir && pre_init_dir_attempt(user_dir, "Attempting to load game from user pref %s")) {
        return true;
    }

    logs::error("'*.eng' or '*_mm.eng' files not found or too large.");
    return false;
}

static void setup() {
    platform.setup_begin();
    platform.init_timers();

    logs::info("Akhenaten version %s", get_version().c_str());
    if (!init_sdl()) {
        logs::error("Exiting: SDL init failed");
        exit(-1);
    }

    initialize_frame_string_allocator();

    platform.init_callback();

    if (platform.is_android()) {
        g_args.set_data_directory("");
    }

    // Show configuration window if --config flag is set or config file doesn't exist.
    // Skip in integral-tests mode: the dialog would block forever in a headless CI runner,
    // and SDL_CreateRenderer there fails because the dummy video driver doesn't support
    // SDL_RENDERER_ACCELERATED, which is what options_window.cpp requests.
    const bool support_window_options = !(platform.is_android() || platform.is_emscripten() || g_args.is_integral_tests());
    if (g_args.should_show_config_window() || !g_args.config_file_exists()) {
        if (support_window_options) {
            show_options_window(g_args);
        }
    }

    // pre-init engine: assert game directory, pref files, etc.
    g_app.setup();
    if (pcstr initial_user_dir = platform.request_initial_data_directory()) {
        g_args.set_data_directory(initial_user_dir);
    }
    bool again = platform.is_android();

    while (!pre_init(g_args.get_data_directory())) {
#if defined(GAME_PLATFORM_ANDROID)
            android_append_startup_log("Startup: folder validation failed");
#endif
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Warning",
              "Akhenaten requires the original files from Pharaoh to run.\n"
#if defined(GAME_PLATFORM_ANDROID)
              "Copy your entire Pharaoh folder to your Android device into folder"
              "/sdcard0/Android/data/com.github.dalerank.akhenaten/files",
#else
              "Move the executable file to the directory containing an existing\n"
              "Pharaoh installation, or run: akhenaten path/to/directory",
#endif
              nullptr);

#if defined(GAME_PLATFORM_ANDROID)
        if (again) {
            const SDL_MessageBoxButtonData buttons[] = {{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK"},
              {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel"}};
            const SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_WARNING, NULL, "Wrong folder selected",
              "The selected folder is not a proper Pharaoh folder.\n\n"
              "Please select a path directly from either the internal storage "
              "or the SD card, otherwise the path may not be recognised.\n\n"
              "Press OK to select another folder or Cancel to exit.",
              SDL_arraysize(buttons), buttons, NULL};
            int result;
            SDL_ShowMessageBox(&messageboxdata, &result);
            if (!result) {
                exit(-2);
            }
        }
        again = true;
        pcstr user_dir = android_show_pharaoh_path_dialog(again);
        if (!user_dir || !*user_dir) {
            android_append_startup_log("Startup: no folder selected after retry");
            exit(-2);
        }
        android_append_startup_log("Startup: retry folder selected");
        g_args.set_data_directory(user_dir);
#endif
        if (support_window_options) {
            show_options_window(g_args);
        }
    }

    // set up game display
    if (!platform_screen_create("Akhenaten", g_args.get_renderer(), g_args.is_fullscreen(),
          g_args.get_display_scale_percentage(), g_args.get_window_size())) {
        logs::info("Exiting: SDL create window failed");
        exit(-2);
    }

    game.set_cli_fullscreen(g_args.is_fullscreen());
    if (g_args.has_window_pos()) {
        const auto& pos = g_args.get_window_pos();
        platform_screen_move(pos.x, pos.y);
    }
    platform_init_cursors(g_args.get_cursor_scale_percentage()); // this has to come after platform_screen_create,
                                                                 // otherwise it fails on Nintendo Switch
    image_data_init();                                           // image paks structures init

    vfs::path scripts_base_path(vfs::SCRIPTS_FOLDER);
#if !defined(GAME_PLATFORM_ANDROID)
    pcstr base_path = vfs::platform_file_manager_get_base_path();
    scripts_base_path = vfs::path(base_path, "/", vfs::SCRIPTS_FOLDER);
#endif
    js_vm_add_scripts_folder(scripts_base_path); // setup script engine data scripts folder

    js_vm_add_scripts_folder(g_args.get_scripts_directory().c_str()); // setup script engine user folder
#if !defined(GAME_PLATFORM_ANDROID)
    js_vm_add_scripts_folder(vfs::SCRIPTS_FOLDER);                    // setup script engine additional folder
#endif

#if defined(GAME_PLATFORM_ANDROID)
    android_append_startup_log("Startup: js_vm_setup");
#endif
    js_vm_setup();
#if defined(GAME_PLATFORM_ANDROID)
    android_append_startup_log("Startup: js_vm_sync");
#endif
    js_vm_sync({});

    // init game!
    time_set_millis(SDL_GetTicks());
    game_opts opts = g_args.use_sound() ? game_opt_sound : game_opt_none;
#if defined(GAME_PLATFORM_ANDROID)
    android_append_startup_log("Startup: game_init");
#endif

    if (!game_init(opts)) {
#if defined(GAME_PLATFORM_ANDROID)
        android_append_startup_log("Startup: game_init failed");
#endif
        logs::info("Exiting: game init failed");
        exit(2);
    }

#if defined(GAME_PLATFORM_ANDROID)
    android_append_startup_log("Startup: config refresh");
#endif
    config::refresh(js_vm_state());

    if (platform.is_emscripten()) {
        game_features::gameopt_language = "en";
    } else if (!g_args.get_language().empty()) {
        logs::info("Language set from command line: %s", g_args.get_language().c_str());
        game_features::gameopt_language = g_args.get_language();
        game.reload_language();
    }
}

static void teardown() {
    logs::info("Exiting game");
    game.exit();
    js_vm_shutdown();
    platform_screen_destroy();
    SDL_Quit();
}

static void run_and_draw() {
    {
        NANO_PROFILE_SCOPE("_Frame");

        OZZY_PROFILER_BEGIN_FRAME();
        js_vm_frame_begin();
        reset_frame_string_allocator();

        time_millis time_before_run = SDL_GetTicks();
        time_set_millis(time_before_run);

        game_imgui_overlay_begin_frame();

        {
            NANO_PROFILE_SCOPE("_GameUpdate");
            game.update();
        }
        Uint32 time_between_run_and_draw = SDL_GetTicks();

        {
            NANO_PROFILE_SCOPE("_SoundUpdate");
            g_sound.begin_frame();
        }

        {
            NANO_PROFILE_SCOPE("_GameDraw");
            game.frame_begin();
            game.city_sounds_frame_begin();
            game.handle_input_frame();
        }
        Uint32 time_after_draw = SDL_GetTicks();

        game_perfmon_set_phase_ms((double)(time_between_run_and_draw - time_before_run),
          (double)(time_after_draw - time_between_run_and_draw));

        {
            NANO_PROFILE_SCOPE("_HUD");
            game.fps.frame_count++;
            if (time_after_draw - game.fps.last_update_time > 1000) {
                game.fps.last_fps = game.fps.frame_count;
                game.fps.last_update_time = time_after_draw;
                game.fps.frame_count = 0;
            }

            const bool main_windows
              = (g_window_manager.window_is("window_city") || g_window_manager.window_is("window_city_military")
                 || g_window_manager.window_is("window_city_warship") || g_window_manager.window_is("window_sliding_sidebar"));
            if (!!game_features::gameui_draw_fps && main_windows) {
                int y_offset = screen_height() - 24;
                int y_offset_text = y_offset + 5;

                text_draw_number_colored(game.fps.last_fps, 'f', "", 5, y_offset_text, FONT_NORMAL_WHITE_ON_DARK,
                  COLOR_FONT_RED);
                text_draw_number_colored(time_between_run_and_draw - time_before_run, 'g', "", 40, y_offset_text,
                  FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
                text_draw_number_colored(time_after_draw - time_between_run_and_draw, 'd', "", 70, y_offset_text,
                  FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
            }
        }

        {
            NANO_PROFILE_SCOPE("_DebugUI");
            game_debug_cli_draw();
            game_debug_properties_draw();
            game_debug_terrain_paint_draw();
            game_perfmon_draw();
        }

        {
            NANO_PROFILE_SCOPE("_ImGuiRender");
            game_imgui_overlay_draw();
        }

        {
            NANO_PROFILE_SCOPE("_Present");
            platform_renderer_render();
        }

        game.frame_end();
        game.write_frame();
    }

    game_perfmon_frame_mark_end();
    mission_id_t missionid(g_scenario.campaign_scenario_id);
    const bool need_reload = js_vm_sync(missionid.value());
    if (need_reload) {
        game.reload_objects();
    }

    if (game.system_language_changed || font_need_regeneration()) {
        game.system_language_changed = false;
        font_atlas_regenerate();
        autoconfig_window::refresh_all();
    }
}

static void handle_event(SDL_Event* event, bool& active, bool& quit) {
    switch (event->type) {
    case SDL_WINDOWEVENT:
        g_app.handle_window_event(&event->window);
        break;

    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_TEXTINPUT:
        g_app.handle_keyboard_event(event);
        break;

    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL:
        g_app.handle_mouse_event(event);
        break;

    case SDL_FINGERDOWN:
    case SDL_FINGERMOTION:
    case SDL_FINGERUP:
        g_app.handle_touch_event(event);
        break;

    case SDL_QUIT:
        quit = true;
        break;

    case SDL_USEREVENT:
        if (event->user.code == USER_EVENT_QUIT)
            quit = true;
        else
            g_app.handle_user_event(event);

        break;

    default:
        break;
    }
}

void application_t::pump_one_frame() {
    platform.per_frame_callback();
    /* Process event queue */

    CoreEvent event;
    while (platform.poll_event(reinterpret_cast<CoreEvent*>(&event))) {
        bool handled_imgui = game_imgui_overlay_handle_event(&event);
        if (!handled_imgui) {
            handle_event(&event, active, quit);
        }
    }

    if (quit) {
        return;
    }

    // Under --integraltests the test driver pumps frames manually and must
    // always advance the game loop. The dummy SDL video driver used in CI
    // fires spurious SDL_WINDOWEVENT_HIDDEN events that flip `active` to false;
    // skipping run_and_draw() there would stop processing simulated input (so
    // clicks never reach the UI) and SDL_WaitEvent() could block the run.
    if (active || g_args.is_integral_tests()) {
        run_and_draw();
    } else {
        SDL_WaitEvent(NULL);
    }
}

static int handle_unpack_scripts() {
    xstring scripts_path = vfs::platform_unpack_scripts();
    if (!scripts_path.empty()) {
        logs::info("Scripts unpacked successfully to: %s", scripts_path.c_str());
        return 0;
    } else {
        logs::error("Failed to unpack scripts");
        return 1;
    }
}

int main(int argc, char** argv) {
    g_args.parse(argc, argv);

    crashhandler_install();

    logs::initialize();

    g_app.register_modules();

    setup();

    if (g_args.should_unpack_scripts()) {
        return handle_unpack_scripts();
    }

    g_mouse.init();

    game_imgui_overlay_init();
    g_app.subscribe_events();
    platform.append_startup_log("Startup: language reload");

    lang_reload_localized_files();
    lang_reload_localized_tables();

    platform.append_startup_log("Startup: first frame");
    run_and_draw();
    platform.append_startup_log("Startup: first frame done");
    platform.hide_startup_log();

    if (g_args.is_integral_tests()) {
        int rc = run_integral_tests();
        game_imgui_overlay_destroy();
        teardown();
        return rc;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop([]() { g_app.pump_one_frame(); }, 0, 1);
#elif defined(GAME_PLATFORM_WIN)
    LONG CALLBACK debug_sehgilter(PEXCEPTION_POINTERS pExceptionPointers);
    __try {
        while (!g_app.quit) {
            g_app.pump_one_frame();
        }
    } __except (debug_sehgilter(GetExceptionInformation())) {
        return 0;
    }
#else
    while (!g_app.quit) {
        g_app.pump_one_frame();
    }
#endif


    game_imgui_overlay_destroy();

    teardown();

    return EXIT_SUCCESS;
}
