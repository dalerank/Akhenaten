
#include "core/app.h"
#include "core/encoding.h"
#include "core/game_environment.h"
#include "core/stacktrace.h"
#include "core/time.h"
#include "game/game.h"
#include "game/settings.h"
#include "game/system.h"
#include "graphics/screen.h"
#include "input/mouse.h"
#include "input/touch.h"
#include "io/file.h"
#include "io/gamefiles/lang.h"
#include "io/config/config.h"
#include "io/log.h"
#include "platform/arguments.h"
#include "platform/cursor.h"
#include "platform/file_manager.h"
#include "platform/keyboard_input.h"
#include "platform/platform.h"
#include "platform/prefs.h"
#include "platform/screen.h"
#include "platform/touch.h"
#include "platform/version.hpp"

#include "renderer.h"

#include <SDL.h>

#include <set>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "imguifiledialog.h"
#include "misc/cpp/imgui_stdlib.h"

#ifdef __SWITCH__
#include "platform/switch/switch.h"
#include "platform/switch/switch_input.h"
#endif

#ifdef __vita__
#include "platform/vita/vita.h"
#include "platform/vita/vita_input.h"
#endif

#if defined(_WIN32)

#include <string.h>

#if !defined(_MSC_VER)
#include <bits/exception_defines.h>
#endif

#endif

#include "graphics/boilerplate.h"
#include "graphics/text.h"
#include "graphics/window.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#define INTPTR(d) (*(int*)(d))

namespace {
void show_usage() {
    platform_screen_show_error_message_box("Command line interface", Arguments::usage());
}
} // namespace
void system_exit() {
    app_post_event(USER_EVENT_QUIT);
}

void system_center() {
    app_post_event(USER_EVENT_CENTER_WINDOW);
}

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
#if SDL_VERSION_ATLEAST(2, 0, 10)
    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
#elif SDL_VERSION_ATLEAST(2, 0, 4)
    SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
#endif
    logs::info("SDL initialized");
    return 1;
}
int pre_init_dir_attempt(std::string_view data_dir, const char* lmsg) {
    logs::info(lmsg, data_dir.data()); // TODO: get rid of data ???
    if (!platform_file_manager_set_base_path(data_dir))
        logs::info("%s: directory not found", data_dir);

    if (game_pre_init())
        return 1;

    return 0;
}

static bool pre_init(std::string_view custom_data_dir) {
    if (pre_init_dir_attempt(custom_data_dir, "Attempting to load game from %s"))
        return true;

    logs::info("Attempting to load game from working directory");
    if (game_pre_init())
        return true;

    // ...then from the executable base path...
    if (platform_sdl_version_at_least(2, 0, 1)) {
        char* base_path = SDL_GetBasePath();
        if (pre_init_dir_attempt(base_path, "Attempting to load game from base path %s")) {
            SDL_free(base_path);
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

/** Show configuration window to override parameters of the startup.
 */
static void show_options_window(Arguments& args) {
    auto const window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    SDL_Window* platform_window = SDL_CreateWindow(
      "Ozymandias: configuration", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    SDL_Renderer* renderer
      = SDL_CreateRenderer(platform_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        logs::info("Error creating SDL_Renderer!");
        exit(-1);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(platform_window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    auto video_modes = get_video_modes();
    ImGuiFileDialog fileDialog;
    bool store_configuration = false;

    for (bool done = false; !done;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                exit(1);
            }
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
                && event.window.windowID == SDL_GetWindowID(platform_window)) {
                exit(1);
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            auto data_directory = args.get_data_directory();
            ImVec2 window_size(1280 * 0.75, 720 * 0.75);
            int platform_window_w, platform_window_h;
            SDL_GetWindowSize(platform_window, &platform_window_w, &platform_window_h);

            ImVec2 window_pos{(platform_window_w - window_size.x) / 2, (platform_window_h - window_size.y) / 2};
            ImGui::SetNextWindowPos(window_pos);
            ImGui::SetNextWindowSize(window_size);

            ImGui::Begin("Configuration",
                         nullptr,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
                           | ImGuiWindowFlags_NoBringToFrontOnFocus);
            ImGui::Text("Folder with original game data:");
            ImGui::InputText("default", &data_directory);
            ImGui::SameLine();
            if (ImGui::Button("...")) {
                fileDialog.OpenDialog("Choose Folder", "", nullptr, ".", 1, nullptr, ImGuiFileDialogFlags_Modal);
            }

            ImVec2 filedialog_size(1280 * 0.5, 720 * 0.5);
            ImVec2 filedialog_pos{(platform_window_w - filedialog_size.x) / 2,
                                  (platform_window_h - filedialog_size.y) / 2};
            if (fileDialog.Display("Choose Folder",
                                   ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize,
                                   filedialog_size,
                                   filedialog_size,
                                   filedialog_pos)) {
                ImGui::SetWindowFocus();
                if (fileDialog.IsOk()) {
                    args.set_data_directory(fileDialog.GetFilePathName());
                }
                fileDialog.Close();
            }

            ImGui::Text("Resolution:");
            static int item_current_idx = 0;
            if (ImGui::BeginListBox("##resolution")) {
                int index = 0;
                for (auto it = video_modes.begin(); it != video_modes.end(); ++it, ++index) {
                    const bool is_selected = (item_current_idx == index);
                    if (ImGui::Selectable(it->str.c_str(), is_selected)) {
                        item_current_idx = index;
                        args.set_window_size({it->w, it->h});
                    }

                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            bool is_window_mode = args.is_window_mode();
            if (ImGui::Checkbox("Window mode", &is_window_mode)) {
                args.set_window_mode(is_window_mode);
            }

            ImGui::Checkbox("Store configuration (to skip this dialog for the next time)", &store_configuration);

            ImVec2 left_bottom_corner{5, window_size.y - 30};
            ImGui::SetCursorPos(left_bottom_corner);
            if (ImGui::Button("RUN GAME")) {
                done = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Quit")) {
                exit(EXIT_SUCCESS);
            }
            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
            // ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (store_configuration)
            arguments::store(args);

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer,
                               (Uint8)(clear_color.x * 255),
                               (Uint8)(clear_color.y * 255),
                               (Uint8)(clear_color.z * 255),
                               (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(platform_window);
}

static void setup(Arguments& args) {
    crashhandler_install();

    logs::info("Ozymandias version %s", get_version().c_str());
    if (!init_sdl()) {
        logs::error("Exiting: SDL init failed");
        exit(-1);
    }
#ifdef PLATFORM_ENABLE_INIT_CALLBACK
    platform_init_callback();
#endif

    // pre-init engine: assert game directory, pref files, etc.
    init_game_environment(ENGINE_ENV_PHARAOH);
    while (!pre_init(args.get_data_directory())) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Warning",
                                 "Ozymandias requires the original files from Pharaoh to run.\n"
                                 "Move the executable file to the directory containing an existing\n"
                                 "Pharaoh installation, or run: ozymandias path/to/directory",
                                 nullptr);
        show_options_window(args);
    }

    // set up game display
    char title[100] = {0};
    encoding_to_utf8(lang_get_string(9, 0), title, 100, 0);
    if (!platform_screen_create(title,
                                args.get_renderer(),
                                args.is_fullscreen(),
                                args.get_display_scale_percentage(),
                                args.get_window_size())) {
        logs::info("Exiting: SDL create window failed");
        exit(-2);
    }
    platform_init_cursors(args.get_cursor_scale_percentage()); // this has to come after platform_screen_create,
                                                               // otherwise it fails on Nintendo Switch

    // init game!
    time_set_millis(SDL_GetTicks());
    if (!game_init()) {
        logs::info("Exiting: game init failed");
        exit(2);
    }
}
static void teardown(void) {
    logs::info("Exiting game");
    game_exit();
    platform_screen_destroy();
    SDL_Quit();
}

struct fps_data_t {
    int frame_count;
    int last_fps;
    Uint32 last_update_time;
};

fps_data_t g_fps = {0, 0, 0};

static void run_and_draw(void) {
    time_millis time_before_run = SDL_GetTicks();
    time_set_millis(time_before_run);

    game_run();
    Uint32 time_between_run_and_draw = SDL_GetTicks();
    game_draw();
    Uint32 time_after_draw = SDL_GetTicks();

    g_fps.frame_count++;
    if (time_after_draw - g_fps.last_update_time > 1000) {
        g_fps.last_fps = g_fps.frame_count;
        g_fps.last_update_time = time_after_draw;
        g_fps.frame_count = 0;
    }

    if (config_get(CONFIG_UI_DRAW_FPS) && (window_is(WINDOW_CITY) || window_is(WINDOW_CITY_MILITARY) || window_is(WINDOW_SLIDING_SIDEBAR))) {
        int y_offset = screen_height() - 24;
        int y_offset_text = y_offset + 5;
 
        text_draw_number_colored(g_fps.last_fps, 
                                    'f', "", 5, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
        text_draw_number_colored(time_between_run_and_draw - time_before_run, 
                                    'g', "", 40, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
        text_draw_number_colored(time_after_draw - time_between_run_and_draw,
                                    'd', "", 70, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
    }

    platform_renderer_render();
}

static void handle_mouse_button(SDL_MouseButtonEvent* event, int is_down) {
    if (!SDL_GetRelativeMouseMode())
        mouse_set_position(event->x, event->y);

    if (event->button == SDL_BUTTON_LEFT)
        mouse_set_left_down(is_down);
    else if (event->button == SDL_BUTTON_MIDDLE)
        mouse_set_middle_down(is_down);
    else if (event->button == SDL_BUTTON_RIGHT)
        mouse_set_right_down(is_down);
}
#ifndef __SWITCH__
static void handle_window_event(SDL_WindowEvent* event, int* window_active) {
    switch (event->event) {
    case SDL_WINDOWEVENT_ENTER:
        mouse_set_inside_window(1);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouse_set_inside_window(0);
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
        *window_active = 1;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        logs::info("Window %d hidden", (unsigned int)event->windowID);
        *window_active = 0;
        break;
    }
}
#endif
static void handle_event(SDL_Event* event, int* active, int* quit) {
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
        if (event->motion.which != SDL_TOUCH_MOUSEID && !SDL_GetRelativeMouseMode())
            mouse_set_position(event->motion.x, event->motion.y);

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
        if (event->wheel.which != SDL_TOUCH_MOUSEID)
            mouse_set_scroll(event->wheel.y > 0 ? SCROLL_UP : event->wheel.y < 0 ? SCROLL_DOWN : SCROLL_NONE);

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
        *quit = 1;
        break;

    case SDL_USEREVENT:
        if (event->user.code == USER_EVENT_QUIT)
            *quit = 1;
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
    mouse_set_inside_window(1);

    run_and_draw();
    int active = 1;
    int quit = 0;
    while (!quit) {
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
            handle_event(&event, &active, &quit);
        }
        if (!quit) {
            if (active)
                run_and_draw();
            else {
                SDL_WaitEvent(NULL);
            }
        }
    }
}

int main(int argc, char** argv) {
    logs::initialize();

    Arguments arguments(argc, argv);
    setup(arguments);
    main_loop();
    teardown();

    return EXIT_SUCCESS;
}
