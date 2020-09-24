#include "SDL.h"

#include "core/backtrace.h"
#include "core/encoding.h"
#include "core/file.h"
#include "core/lang.h"
#include "core/time.h"
#include "core/game_environment.h"
#include "game/game.h"
#include "game/system.h"
#include "input/mouse.h"
#include "input/touch.h"
#include "platform/arguments.h"
#include "platform/cursor.h"
#include "platform/file_manager.h"
#include "platform/keyboard_input.h"
#include "platform/platform.h"
#include "platform/prefs.h"
#include "platform/screen.h"
#include "platform/touch.h"

#include "tinyfiledialogs/tinyfiledialogs.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

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
#include <bits/exception_defines.h>

#endif

#ifdef DRAW_FPS
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#endif

#define INTPTR(d) (*(int*)(d))

enum {
    USER_EVENT_QUIT,
    USER_EVENT_RESIZE,
    USER_EVENT_FULLSCREEN,
    USER_EVENT_WINDOWED,
    USER_EVENT_CENTER_WINDOW,
};

static void handler(int sig)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Oops, crashed with signal %d :(", sig);
    backtrace_print();
    exit(1);
}

#if defined(_WIN32) || defined(__vita__) || defined(__SWITCH__)
/* Log to separate file on windows, since we don't have a console there */
static FILE *log_file = 0;

static void write_log(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    if (log_file) {
        if (priority == SDL_LOG_PRIORITY_ERROR)
            fwrite("ERROR: ", sizeof(char), 7, log_file);
 else {
            fwrite("INFO: ", sizeof(char), 6, log_file);
        }
        fwrite(message, sizeof(char), strlen(message), log_file);
        fwrite("\n", sizeof(char), 1, log_file);
        fflush(log_file);
    }
}
static void setup_logging(void)
{
    log_file = file_open("augustus-log.txt", "wt");
    SDL_LogSetOutputFunction(write_log, NULL);
}
static void teardown_logging(void)
{
    if (log_file)
        file_close(log_file);

}

#else
static void setup_logging(void) {}
static void teardown_logging(void) {}
#endif

static void post_event(int code)
{
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = code;
    SDL_PushEvent(&event);
}

void system_exit(void)
{
    post_event(USER_EVENT_QUIT);
}
void system_resize(int width, int height)
{
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
void system_center(void)
{
    post_event(USER_EVENT_CENTER_WINDOW);
}
void system_set_fullscreen(int fullscreen)
{
    post_event(fullscreen ? USER_EVENT_FULLSCREEN : USER_EVENT_WINDOWED);
    if (fullscreen == 0)
        system_resize(1200,800);
}

#ifdef USE_TINYFILEDIALOGS
static const char *ask_for_data_dir(int again)
{
    const char *title = get_game_title();
    const char *form_1 = "Augustus requires the original files from %s to run.\n\nThe selected folder is not a proper %s folder.\n\nPress OK to select another folder or Cancel to exit.";
    const char *form_2 = "Please select your %s folder";

    // size of buffer is 200 initially - resized to (excess discarded) size of format + size of arg (game title) - 2 (%s) + 1 (null terminator)
    char *buf = (char*)malloc(200);
    if (again) {
        snprintf(buf, strlen(form_1) + 2 * strlen(title) - 3, form_1, title, title);
        if (!tinyfd_messageBox("Wrong folder selected", buf, "okcancel", "warning", 1)) // hitting cancel will return "0"
        {
            free(buf);
            return NULL;
        }
    }

    snprintf(buf, strlen(form_2) + strlen(title) - 1, form_2, title);

    const char *dir = tinyfd_selectFolderDialog(buf, NULL);
    free(buf);
    return dir;
}
#endif

static int init_sdl(void)
{
    SDL_Log("Initializing SDL");
    Uint32 SDL_flags = SDL_INIT_AUDIO;

    // on Vita, need video init only to enable physical kbd/mouse and touch events
    SDL_flags |= SDL_INIT_VIDEO;

#if defined(__vita__) || defined(__SWITCH__)
    SDL_flags |= SDL_INIT_JOYSTICK;
#endif

    if (SDL_Init(SDL_flags) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
        return 0;
    }
#if SDL_VERSION_ATLEAST(2, 0, 10)
    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
#elif SDL_VERSION_ATLEAST(2, 0, 4)
    SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
#endif
    SDL_Log("SDL initialized");
    return 1;
}
int pre_init_dir_attempt(const char *data_dir, const char *lmsg)
{
    SDL_Log(lmsg, data_dir);
    if (!platform_file_manager_set_base_path(data_dir))
        SDL_Log("%s: directory not found", data_dir);
    if (game_pre_init())
        return 1;
    return 0;
}
static int pre_init(const char *custom_data_dir)
{
    // first attempt loading game from custom path passed as argument...
    if (custom_data_dir) {
        if (pre_init_dir_attempt(custom_data_dir, "Attempting to load game from %s"))
            return 1;
        SDL_Log("%s: directory not found", custom_data_dir);
        return 0;
    }

    // ...then from working directory...
    SDL_Log("Attempting to load game from working directory");
    if (game_pre_init())
        return 1;


    // ...then from the executable base path...
    #if SDL_VERSION_ATLEAST(2, 0, 1)
        if (platform_sdl_version_at_least(2, 0, 1)) {
            char *base_path = SDL_GetBasePath();
            if (pre_init_dir_attempt(base_path, "Attempting to load game from base path %s")) {
                SDL_free(base_path);
                return 1;
            }
        }
    #endif

    // ...then finally from the user-defined path (saved in pref file)
    #ifdef USE_TINYFILEDIALOGS
        const char *user_dir = pref_get_gamepath();
        if (user_dir && pre_init_dir_attempt(user_dir, "Attempting to load game from user pref %s"))
            return 1;

        // if the saved path fails, ask the user for one
        user_dir = ask_for_data_dir(0);
        while (user_dir) {
            if (pre_init_dir_attempt(user_dir, "Attempting to load game from user-selected dir %s")) {
                pref_save_gamepath(user_dir); // save new accepted dir to pref
                return 1;
            }
            user_dir = ask_for_data_dir(1); // if not hitting "cancel" it will continue check the selected path (because the selection fills user_dir)
        }
    #else
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
            "Julius requires the original files from Caesar 3 to run.",
            "Move the Julius executable to the directory containing an existing "
            "Caesar 3 installation, or run:\njulius path-to-c3-directory",
            NULL);
    #endif

    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "'*.eng' or '*_mm.eng' files not found or too large.");
    return 0;
}
static void setup(const julius_args *args)
{
    // init SDL and some other stuff
    signal(SIGSEGV, handler);
    setup_logging();
    SDL_Log("Augustus version %s", system_version());
    if (!init_sdl()) {
        SDL_Log("Exiting: SDL init failed");
        exit(-1);
    }
    #ifdef PLATFORM_ENABLE_INIT_CALLBACK
        platform_init_callback();
    #endif

    // pre-init engine: assert game directory, pref files, etc.
    init_game_environment(args->game_engine_env);
    if (!pre_init(args->data_directory)) {
        SDL_Log("Exiting: game pre-init failed");
        exit(1);
    }

    #ifdef DEBUG
        goto skip;
    #endif
    // set up game display
    char title[100];
    encoding_to_utf8(lang_get_string(9, 0), title, 100, 0);
    if (!platform_screen_create(title, args->display_scale_percentage)) {
        SDL_Log("Exiting: SDL create window failed");
        exit(-2);
    }
    platform_init_cursors(args->cursor_scale_percentage); // this has to come after platform_screen_create, otherwise it fails on Nintendo Switch

    skip:
    // init game!
    time_set_millis(SDL_GetTicks());
    if (!game_init()) {
        SDL_Log("Exiting: game init failed");
        exit(2);
    }
}
static void teardown(void)
{
    SDL_Log("Exiting game");
    game_exit();
    platform_screen_destroy();
    SDL_Quit();
    teardown_logging();
}

#ifdef DRAW_FPS
static struct {
    int frame_count;
    int last_fps;
    Uint32 last_update_time;
} fps = {0, 0, 0};

static void run_and_draw(void)
{
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
        text_draw_number_colored(time_between_run_and_draw - time_before_run, 'g', "", 40, y_offset_text, FONT_NORMAL_PLAIN, COLOR_FONT_RED);
        text_draw_number_colored(time_after_draw - time_between_run_and_draw, 'd', "", 70, y_offset_text, FONT_NORMAL_PLAIN, COLOR_FONT_RED);
    }

    platform_screen_render();
}
#else
static void run_and_draw(void)
{
    time_set_millis(SDL_GetTicks());

    game_run();
    game_draw();

    platform_screen_render();
}
#endif

static void handle_mouse_button(SDL_MouseButtonEvent *event, int is_down)
{
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
static void handle_window_event(SDL_WindowEvent *event, int *window_active)
{
    switch (event->event) {
        case SDL_WINDOWEVENT_ENTER:
            mouse_set_inside_window(1);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            mouse_set_inside_window(0);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window resized to %d x %d", (int) event->data1, (int) event->data2);
            platform_screen_resize(event->data1, event->data2, 1);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("System resize to %d x %d", (int) event->data1, (int) event->data2);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window move to coordinates x: %d y: %d\n", (int) event->data1, (int) event->data2);
            platform_screen_move(event->data1, event->data2);
            break;

        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", (unsigned int) event->windowID);
            *window_active = 1;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", (unsigned int) event->windowID);
            *window_active = 0;
            break;
    }
}
#endif
static void handle_event(SDL_Event *event, int *active, int *quit)
{
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
static void main_loop(void)
{
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

int main(int argc, char **argv)
{
    julius_args args;
    platform_parse_arguments(argc, argv, &args);

    setup(&args);

    main_loop();

    teardown();
    return 0;
}
