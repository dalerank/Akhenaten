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
#include "input/mouse.h"
#include "content/vfs.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "platform/arguments.h"
#include "platform/cursor.h"
#include "content/content.h"
#include "platform/keyboard_input.h"
#include "platform/platform.h"
#include "platform/prefs.h"
#include "platform/screen.h"
#include "platform/touch.h"
#include "platform/version.hpp"
#include "platform/options_window.h"
#include "widget/debug_console.h"
#include "window/autoconfig_window.h"
#include "graphics/imagepak_holder.h"
#include "renderer.h"

#include <SDL.h>

#include <set>
#include <platform/android/android.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "dev/imguifiledialog.h"
#include "misc/cpp/imgui_stdlib.h"

#ifdef __SWITCH__
#include "platform/switch/switch.h"
#include "platform/switch/switch_input.h"
#endif

#ifdef __vita__
#include "platform/vita/vita.h"
#include "platform/vita/vita_input.h"
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

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
#define URL_EDITOR "https://github.com/dalerank/akhenaten/wiki/Editor"

#define INTPTR(d) (*(int*)(d))

namespace {

void show_usage() {
    platform_screen_show_error_message_box("Command line interface", Arguments::usage());
}

} // namespace

static int init_sdl() {
    logs::info("Initializing SDL");
    Uint32 SDL_flags = SDL_INIT_AUDIO;

    // on Vita, need video init only to enable physical kbd/mouse and touch events
    SDL_flags |= SDL_INIT_VIDEO;

#if defined(__vita__) || defined(__SWITCH__)
    SDL_flags |= SDL_INIT_JOYSTICK;
#endif

    if (SDL_Init(SDL_flags) != 0) {
        logs::error("Could not initialize SDL: %s", SDL_GetError());
        return 0;
    }

    static_assert(SDL_VERSION_ATLEAST(2, 0, 10), "SDL version too old");
    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    //SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");

#if defined(GAME_PLATFORM_ANDROID)
    SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
#endif
    logs::info("SDL initialized");
    return 1;
}

bool pre_init_dir_attempt(pcstr data_dir, pcstr lmsg) {
    logs::info(lmsg, data_dir); // TODO: get rid of data ???
    const bool ok = vfs::platform_file_manager_set_base_path(data_dir);
    if (!ok) {
        logs::info("%s: directory not found", data_dir);
    }

    if (game.check_valid()) {
        return true;
    }

    return false;
}

static bool pre_init(pcstr custom_data_dir) {
    if (pre_init_dir_attempt(custom_data_dir, "Attempting to load game from %s")) {
        return true;
    }

    logs::info("Attempting to load game from working directory");
    if (game.check_valid()) {
        return true;
    }

#if !defined(GAME_PLATFORM_ANDROID)
    // ...then from the executable base path...
    static_assert(SDL_VERSION_ATLEAST(2, 0, 1), "SDL version too old");
#if defined(GAME_PLATFORM_MACOSX)
    char* tmp_path = SDL_GetPrefPath("", "Akhenaten");
#else
    char* tmp_path = SDL_GetBasePath();
#endif
    bstring512 base_path(tmp_path);
    SDL_free(tmp_path);
    if (pre_init_dir_attempt(base_path, "Attempting to load game from base path %s")) {
        return true;
    }
#else
    ; // android should has files in content directory
#endif //

    const char* user_dir = pref_get_gamepath();
    if (user_dir && pre_init_dir_attempt(user_dir, "Attempting to load game from user pref %s")) {
        return true;
    }

    logs::error("'*.eng' or '*_mm.eng' files not found or too large.");
    return false;
}

static void setup() {
    platform.init_timers();

    logs::info("Akhenaten version %s", get_version().c_str());
    if (!init_sdl()) {
        logs::error("Exiting: SDL init failed");
        exit(-1);
    }

#ifdef PLATFORM_ENABLE_INIT_CALLBACK
    platform_init_callback();
#endif

#if defined(GAME_PLATFORM_ANDROID)
    g_args.set_data_directory(SDL_AndroidGetExternalStoragePath());
#endif

    // Show configuration window if --config flag is set or config file doesn't exist
    const bool support_window_options = !(platform.is_android() || platform.is_emscripten());
    if (g_args.should_show_config_window() || !g_args.config_file_exists()) {
        if (support_window_options) {
            show_options_window(g_args);
        }
    }

    // pre-init engine: assert game directory, pref files, etc.
    g_application.setup();
#if defined(GAME_PLATFORM_ANDROID)
    bool again = false;
#endif // GAME_PLATFORM_ANDROID
    while (!pre_init(g_args.get_data_directory())) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Warning",
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
            const SDL_MessageBoxButtonData buttons[] = {
                {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK"},
                {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel"}
            };
            const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_WARNING, NULL, "Wrong folder selected",
                "The selected folder is not a proper Pharaoh folder.\n\n"
                "Please select a path directly from either the internal storage "
                "or the SD card, otherwise the path may not be recognised.\n\n"
                "Press OK to select another folder or Cancel to exit.",
                SDL_arraysize(buttons), buttons, NULL
            };
            int result;
            SDL_ShowMessageBox(&messageboxdata, &result);
            if (!result) {
                exit(-2);
            }
        }
        again = true;
        pcstr user_dir = android_show_pharaoh_path_dialog(again);
        g_args.set_data_directory(user_dir);
 #endif
        if (support_window_options) {
            show_options_window(g_args);
        }
    }

    // set up game display
    if (!platform_screen_create("Akhenaten",
                                g_args.get_renderer(),
                                g_args.is_fullscreen(),
                                g_args.get_display_scale_percentage(),
                                g_args.get_window_size())) {
        logs::info("Exiting: SDL create window failed");
        exit(-2);
    }

    vfs::platform_file_manager_set_ext_path(g_args.get_extdata_directory());
    g_settings.set_cli_fullscreen(g_args.is_fullscreen());
    platform_init_cursors(g_args.get_cursor_scale_percentage()); // this has to come after platform_screen_create,
                                                               // otherwise it fails on Nintendo Switch
    image_data_init();                                         // image paks structures init
                                                               
    pcstr base_path = vfs::platform_file_manager_get_base_path();
    vfs::path scripts_base_path(base_path, vfs::SCRIPTS_FOLDER);
    js_vm_add_scripts_folder(scripts_base_path);    // setup script engine data scripts folder

    js_vm_add_scripts_folder(g_args.get_scripts_directory());    // setup script engine user folder
    js_vm_add_scripts_folder(vfs::SCRIPTS_FOLDER);      // setup script engine additional folder

    js_vm_setup();
    js_vm_sync();

    // init game!
    time_set_millis(SDL_GetTicks());
    game_opts opts = g_args.use_sound() ? game_opt_sound : game_opt_none;

    if (!game_init(opts)) {
        logs::info("Exiting: game init failed");
        exit(2);
    }

    config::refresh(g_config_arch);
}

static void teardown() {
    logs::info("Exiting game");
    game.exit();
    platform_screen_destroy();
    SDL_Quit();
}

static void run_and_draw() {
    OZZY_PROFILER_FRAME(x);
    time_millis time_before_run = SDL_GetTicks();
    time_set_millis(time_before_run);

    game_imgui_overlay_begin_frame();

    game.update();
    Uint32 time_between_run_and_draw = SDL_GetTicks();

    game.frame_begin();
    game.sound_frame_begin();

    game.handle_input_frame();
    Uint32 time_after_draw = SDL_GetTicks();

    game.fps.frame_count++;
    if (time_after_draw - game.fps.last_update_time > 1000) {
        game.fps.last_fps = game.fps.frame_count;
        game.fps.last_update_time = time_after_draw;
        game.fps.frame_count = 0;
    }

    if (!!game_features::gameui_draw_fps && (window_is(WINDOW_CITY) || window_is(WINDOW_CITY_MILITARY) || window_is(WINDOW_SLIDING_SIDEBAR))) {
        int y_offset = screen_height() - 24;
        int y_offset_text = y_offset + 5;
 
        text_draw_number_colored(game.fps.last_fps, 'f', "", 5, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
        text_draw_number_colored(time_between_run_and_draw - time_before_run, 'g', "", 40, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
        text_draw_number_colored(time_after_draw - time_between_run_and_draw, 'd', "", 70, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
    }

    game_debug_cli_draw();
    game_debug_properties_draw();

    game_imgui_overlay_draw();
    platform_renderer_render();

    game.frame_end();
    game.write_frame();

    const bool need_reload = js_vm_sync();
    if (need_reload) {
        game.reload_objects();
    }

    if (game.system_language_changed || font_need_regeneration()) {
        game.system_language_changed = false;
        font_atlas_regenerate();
        autoconfig_window::refresh_all();
    }
}

static void handle_mouse_button(SDL_MouseButtonEvent* event, int is_down) {
    auto &m = mouse::ref();
    if (!SDL_GetRelativeMouseMode()) {
        m.set_position({ event->x, event->y });
    }

    if (event->button == SDL_BUTTON_LEFT) {
        m.set_left_down(is_down);
    } else if (event->button == SDL_BUTTON_MIDDLE) {
        m.set_middle_down(is_down);
    } else if (event->button == SDL_BUTTON_RIGHT) {
        m.set_right_down(is_down);
    }
}

#ifndef __SWITCH__
static void handle_window_event(SDL_WindowEvent* event, bool &window_active) {
    switch (event->event) {
    case SDL_WINDOWEVENT_ENTER:
        g_mouse.set_inside_window(1);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        g_mouse.set_inside_window(0);
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        logs::info("Window resized to %d x %d", (int)event->data1, (int)event->data2);
        platform_screen_resize(event->data1, event->data2, 1);
        break;
    case SDL_WINDOWEVENT_RESIZED:
        logs::info("System resize to %d x %d", (int)event->data1, (int)event->data2);
        break;
    case SDL_WINDOWEVENT_MOVED:
        logs::info("Window move to coordinates x: %d y: %d\n", (int)event->data1, (int)event->data2);
        platform_screen_move(event->data1, event->data2);
        break;

    case SDL_WINDOWEVENT_SHOWN:
        logs::info("Window %d shown", (unsigned int)event->windowID);
        window_active = true;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        logs::info("Window %d hidden", (unsigned int)event->windowID);
        window_active = false;
        break;
    }
}
#endif
static void handle_event(SDL_Event* event, bool &active, bool &quit) {
    switch (event->type) {
#ifndef __SWITCH__
    case SDL_WINDOWEVENT:
        handle_window_event(&event->window, active);
        break;
#endif
    case SDL_KEYDOWN:
        platform_handle_key_down(&event->key);
        break;
    case SDL_KEYUP:
        platform_handle_key_up(&event->key);
        break;
    case SDL_TEXTINPUT:
        platform_handle_text(&event->text);
        break;
    case SDL_MOUSEMOTION: 
        if (event->motion.which != SDL_TOUCH_MOUSEID && !SDL_GetRelativeMouseMode()) {
            mouse::ref().set_position({ event->motion.x, event->motion.y });
        }

        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.which != SDL_TOUCH_MOUSEID)
            handle_mouse_button(&event->button, 1);

        break;
    case SDL_MOUSEBUTTONUP:
        if (event->button.which != SDL_TOUCH_MOUSEID)
            handle_mouse_button(&event->button, 0);

        break;
    case SDL_MOUSEWHEEL:
        if (event->wheel.which != SDL_TOUCH_MOUSEID) {
            mouse::ref().set_scroll(event->wheel.y > 0 ? SCROLL_UP : event->wheel.y < 0 ? SCROLL_DOWN : SCROLL_NONE);
        }

        break;

    case SDL_FINGERDOWN:
        platform_touch_start(&event->tfinger);
        break;
    case SDL_FINGERMOTION:
        platform_touch_move(&event->tfinger);
        break;
    case SDL_FINGERUP:
        platform_touch_end(&event->tfinger);
        break;

    case SDL_QUIT:
        quit = true;
        break;

    case SDL_USEREVENT:
        if (event->user.code == USER_EVENT_QUIT)
            quit = true;
        else if (event->user.code == USER_EVENT_RESIZE)
            platform_screen_set_window_size(INTPTR(event->user.data1), INTPTR(event->user.data2));
        else if (event->user.code == USER_EVENT_FULLSCREEN)
            platform_screen_set_fullscreen();
        else if (event->user.code == USER_EVENT_WINDOWED)
            platform_screen_set_windowed();
        else if (event->user.code == USER_EVENT_CENTER_WINDOW)
            platform_screen_center_window();

        break;

    default:
        break;
    }
}

static void main_loop() {
    SDL_Event event;
#ifdef PLATFORM_ENABLE_PER_FRAME_CALLBACK
    platform_per_frame_callback();
#endif
    /* Process event queue */
#ifdef __vita__
    while (vita_poll_event(&event)) {
#elif defined(__SWITCH__)
    while (switch_poll_event(&event)) {
#else
    while (SDL_PollEvent(&event)) {
#endif
        bool handled_imgui = game_imgui_overlay_handle_event(&event);
        if (!handled_imgui) {
            handle_event(&event, g_application.active, g_application.quit);
        }
    }

    if (g_application.quit) {
        return;
    }

    if (g_application.active) {
        run_and_draw();
    } else {
        SDL_WaitEvent(NULL);
    }
}

int main(int argc, char** argv) {
    g_args.parse(argc, argv);

    crashhandler_install();

    logs::initialize();

    setup();
    g_mouse.init();
    
    game_imgui_overlay_init();
    g_application.subscribe_events();
    lang_reload_localized_files();
    lang_reload_localized_tables();

    run_and_draw();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#elif defined(GAME_PLATFORM_WIN)
    LONG CALLBACK debug_sehgilter(PEXCEPTION_POINTERS pExceptionPointers);
    __try {
        while (!g_application.quit) {
            main_loop();
        }
    } __except (debug_sehgilter(GetExceptionInformation())) {
        return 0;
    }
#else
    while (!g_application.quit) {
        main_loop();
    }
#endif
    

    game_imgui_overlay_destroy();

    teardown();

    return EXIT_SUCCESS;
}
