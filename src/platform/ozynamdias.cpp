#include "core/encoding.h"
#include "core/game_environment.h"
#include "core/stacktrace.h"
#include "core/time.h"
#include "game/game.h"
#include "game/system.h"
#include "input/mouse.h"
#include "input/touch.h"
#include "io/file.h"
#include "io/gamefiles/lang.h"
#include "io/log.h"
#include "platform/arguments.h"
#include "platform/cursor.h"
#include "platform/file_manager.h"
#include "platform/keyboard_input.h"
#include "platform/platform.h"
#include "platform/prefs.h"
#include "platform/screen.h"
#include "platform/touch.h"

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

#ifdef DRAW_FPS
#include "graphics/boilerplate.h"
#include "graphics/text.h"
#include "graphics/window.h"
#endif

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#define INTPTR(d) (*(int*)(d))

enum E_USER_EVENT {
    USER_EVENT_QUIT,
    USER_EVENT_RESIZE,
    USER_EVENT_FULLSCREEN,
    USER_EVENT_WINDOWED,
    USER_EVENT_CENTER_WINDOW,
};

static void post_event(int code) {
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = code;
    SDL_PushEvent(&event);
}

void system_exit() {
    post_event(USER_EVENT_QUIT);
}
void system_resize(int width, int height) {
    static int s_width;
    static int s_height;

    s_width = width;
    s_height = height;
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = USER_EVENT_RESIZE;
    event.user.data1 = &s_width;
    event.user.data2 = &s_height;
    SDL_PushEvent(&event);
}
void system_center() {
    post_event(USER_EVENT_CENTER_WINDOW);
}
void system_set_fullscreen(int fullscreen) {
    post_event(fullscreen ? USER_EVENT_FULLSCREEN : USER_EVENT_WINDOWED);
    if (fullscreen == 0)
        system_resize(1200, 800);
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
int pre_init_dir_attempt(const char* data_dir, const char* lmsg) {
    logs::info(lmsg, data_dir);
    if (!platform_file_manager_set_base_path(data_dir))
        logs::info("%s: directory not found", data_dir);

    if (game_pre_init())
        return 1;

    return 0;
}

static int pre_init(const char* custom_data_dir) {
    // first attempt loading game from custom path passed as argument...
    if (custom_data_dir) {
        if (pre_init_dir_attempt(custom_data_dir, "Attempting to load game from %s")) {
            return 1;
        }

        logs::info("%s: directory not found", custom_data_dir);
        return 0;
    }

    // ...then from working directory...
    logs::info("Attempting to load game from working directory");
    if (game_pre_init()) {
        return 1;
    }

    // ...then from the executable base path...
    if (platform_sdl_version_at_least(2, 0, 1)) {
        char* base_path = SDL_GetBasePath();
        if (pre_init_dir_attempt(base_path, "Attempting to load game from base path %s")) {
            SDL_free(base_path);
            return 1;
        }
    }

    const char* user_dir = pref_get_gamepath();
    if (user_dir && pre_init_dir_attempt(user_dir, "Attempting to load game from user pref %s")) {
        return 1;
    }

    logs::error("'*.eng' or '*_mm.eng' files not found or too large.");
    return 0;
}

struct video_mode {
    int w, h;
    std::string str;
    video_mode(int _w, int _h)
      : w(_w),
        h(_h) {
        char buffer[64] = {0};
        snprintf(buffer, 64, "%u x %u", _w, _h);
        str = buffer;
    }
    bool operator<(const video_mode& o) const {
        return ((int64_t(w) << 32) + h) < ((int64_t(o.w) << 32) + o.h);
    }
};

static std::set<video_mode> get_video_modes() {
    /* Get available fullscreen/hardware modes */
    int num = SDL_GetNumDisplayModes(0);

    std::set<video_mode> uniqueModes;
    uniqueModes.insert({1920, 1080});
    uniqueModes.insert({1600, 900});
    uniqueModes.insert({1440, 800});
    uniqueModes.insert({1280, 1024});
    uniqueModes.insert({1280, 800});
    uniqueModes.insert({1024, 768});
    uniqueModes.insert({800, 600});

    int maxWidth = 0;
    for (int i = 0; i < num; ++i) {
        SDL_DisplayMode mode;
        if (SDL_GetDisplayMode(0, i, &mode) == 0 && mode.w > 640) {
            maxWidth = std::max(mode.w, maxWidth);
            if (uniqueModes.count({mode.w, mode.h}) == 0) {
                uniqueModes.insert(video_mode(mode.w, mode.h));
            }
        }
    }

    return uniqueModes;
}

/** Show configuration window to override parameters of the startup.
 */
static void show_options_window() {
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

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
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
            ImGui::InputText("default", ozymandias_core.data_directory, 64);
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
                    strcpy(ozymandias_core.data_directory, fileDialog.GetFilePathName().c_str());
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
                        ozymandias_core.window_width = it->w;
                        ozymandias_core.window_height = it->h;
                    }

                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            ImGui::Checkbox("Window mode", &ozymandias_core.window_mode);
            ImGui::InputInt("Skip Tutorial", &ozymandias_core.tutorial_skip);

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

static void setup(const ozymandias_args& args) {
    // init SDL and some other stuff
    crashhandler_install();
    logs::initialize();

    logs::info("Ozymandias version %s", system_version());
    if (!init_sdl()) {
        logs::error("Exiting: SDL init failed");
        exit(-1);
    }
#ifdef PLATFORM_ENABLE_INIT_CALLBACK
    platform_init_callback();
#endif

    // pre-init engine: assert game directory, pref files, etc.
    init_game_environment(args.game_engine_env, args.game_engine_debug_mode);
    while (!pre_init(args.data_directory)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Warning",
                                 "Ozymandias requires the original files from Pharaoh to run.\n"
                                 "Move the executable file to the directory containing an existing\n"
                                 "Pharaoh installation, or run: ozymandias path/to/directory",
                                 nullptr);
        show_options_window();
    }

    // set up game display
    char title[100] = {0};
    encoding_to_utf8(lang_get_string(9, 0), title, 100, 0);
    if (!platform_screen_create(title, args.display_scale_percentage)) {
        logs::info("Exiting: SDL create window failed");
        exit(-2);
    }
    platform_init_cursors(args.cursor_scale_percentage); // this has to come after platform_screen_create, otherwise it
                                                         // fails on Nintendo Switch

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

#ifdef DRAW_FPS
static struct {
    int frame_count;
    int last_fps;
    Uint32 last_update_time;
} fps = {0, 0, 0};

static void run_and_draw(void) {
    time_millis time_before_run = SDL_GetTicks();
    time_set_millis(time_before_run);

    game_run();
    Uint32 time_between_run_and_draw = SDL_GetTicks();
    game_draw();
    Uint32 time_after_draw = SDL_GetTicks();

    fps.frame_count++;
    if (time_after_draw - fps.last_update_time > 1000) {
        fps.last_fps = fps.frame_count;
        fps.last_update_time = time_after_draw;
        fps.frame_count = 0;
    }
    if (window_is(WINDOW_CITY) || window_is(WINDOW_CITY_MILITARY) || window_is(WINDOW_SLIDING_SIDEBAR)) {
        int y_offset = 24;
        int y_offset_text = y_offset + 5;
        graphics_fill_rect(0, y_offset, 100, 20, COLOR_WHITE);
        text_draw_number_colored(fps.last_fps, 'f', "", 5, y_offset_text, FONT_NORMAL_PLAIN, COLOR_FONT_RED);
        text_draw_number_colored(
          time_between_run_and_draw - time_before_run, 'g', "", 40, y_offset_text, FONT_NORMAL_PLAIN, COLOR_FONT_RED);
        text_draw_number_colored(
          time_after_draw - time_between_run_and_draw, 'd', "", 70, y_offset_text, FONT_NORMAL_PLAIN, COLOR_FONT_RED);
    }

    platform_screen_render();
}
#else
static void run_and_draw(void) {
    time_set_millis(SDL_GetTicks());

    game_run();
    game_draw();

    platform_renderer_render();
}
#endif

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
static void main_loop(void) {
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
    platform_parse_arguments(argc, argv, ozymandias_core);

    setup(ozymandias_core);

    main_loop();

    teardown();
    return 0;
}
