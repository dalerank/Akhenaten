#include "platform/screen.h"

#include "core/calc.h"
#include "core/log.h"
#include "game/settings.h"
#include "game/system.h"
#include "graphics/graphics.h"
#include "graphics/elements/menu.h"
#include "graphics/image.h"
#include "graphics/screen.h"
#include "game/game_config.h"
#include "arguments.h"
#include "platform/android/android.h"
#include "platform/platform.h"
#include "platform/renderer.h"
#include "platform/switch/switch.h"
#include "platform/vita/vita.h"
#include "resource/icons.h"

#include "SDL.h"

#include <stdlib.h>

struct screen_t {
    SDL_Window* window;
    vec2i pos;
    int centered;
    struct {
        const int WIDTH;
        const int HEIGHT;
    } minimum = {640, 480};
    int scale_percentage = 100;
};

screen_t g_screen;

static int scale_logical_to_pixels(int logical_value) {
    return logical_value * g_screen.scale_percentage / 100;
}

static int scale_pixels_to_logical(int pixel_value) {
    return pixel_value * 100 / g_screen.scale_percentage;
}

static int get_max_scale_percentage(int pixel_width, int pixel_height) {
    int width_scale_pct = pixel_width * 100 / g_screen.minimum.WIDTH;
    int height_scale_pct = pixel_height * 100 / g_screen.minimum.HEIGHT;
    return SDL_min(width_scale_pct, height_scale_pct);
}

static void set_scale_percentage(int new_scale, int pixel_width, int pixel_height) {
#ifdef __vita__
    g_screen.scale_percentage = 100;
#else
    g_screen.scale_percentage = calc_bound(new_scale, 50, 500);
#endif

    if (!pixel_width || !pixel_height) {
        return;
    }

    int max_scale_pct = get_max_scale_percentage(pixel_width, pixel_height);
    if (max_scale_pct < g_screen.scale_percentage) {
        g_screen.scale_percentage = max_scale_pct;
        logs::info("Maximum scale of %i applied", g_screen.scale_percentage);
    }
    
    SDL_SetWindowMinimumSize(g_screen.window, scale_logical_to_pixels(g_screen.minimum.WIDTH), scale_logical_to_pixels(g_screen.minimum.HEIGHT));

    const char *scale_quality = "linear";
#if !defined(GAME_PLATFORM_ANDROID)
    // Scale using nearest neighbour when we scale a multiple of 100%: makes it look sharper.
    // But not on MacOS: users are used to the linear interpolation since that's what Apple also does.
    if (g_screen.scale_percentage % 100 == 0) {
        scale_quality = "nearest";
    }
#endif
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality);
}

#if defined(GAME_PLATFORM_ANDROID)
static void set_scale_for_screen(int pixel_width, int pixel_height) {
    set_scale_percentage(android_get_screen_density() * 100, pixel_width, pixel_height);
    //config_set(CONFIG_SCREEN_CURSOR_SCALE, scale_percentage);
    if (g_screen.window) {
        //system_init_cursors(scale_percentage);
    }
    logs::info("Auto-setting scale to %i", g_screen.scale_percentage);
}
#endif

int platform_screen_get_scale() {
    return g_screen.scale_percentage;
}

void* platform_screen_surfce_format() {
    SDL_Surface *scr_surface = SDL_GetWindowSurface( g_screen.window );
    return scr_surface->format;
}

#if !defined(GAME_PLATFORM_WIN) && !defined(GAME_PLATFORM_MACOSX)
static void set_window_icon() {
    // TODO platform_icon_get_pixels() not defined?
    // SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(platform_icon_get_pixels(), 16, 16, 32, 16 * 4,
    //     0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    // if (!surface) {
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create surface for icon. Reason: %s", SDL_GetError());
    // }
    // SDL_SetWindowIcon(SDL.window, surface);
    // SDL_FreeSurface(surface);
}
#endif

int platform_screen_create(const xstring& title, const xstring& renderer, bool fullscreen, int display_scale_percentage, vec2i screen_size) {
#if defined(GAME_PLATFORM_ANDROID)
    //scale.screen_density = android_get_screen_density();
#endif

    set_scale_percentage(display_scale_percentage, 0, 0);

    vec2i wsize;
    if (!fullscreen && system_is_fullscreen_only()) {
        fullscreen = true;
    }

    if (fullscreen) {
        SDL_DisplayMode mode;
        SDL_GetDesktopDisplayMode(0, &mode);
        wsize = {mode.w, mode.h};
    } else {
        wsize = g_settings.display_size;
        wsize.x = std::max<int>(wsize.x, screen_size.x);
        wsize.y = std::max<int>(wsize.y, screen_size.y);

        wsize.x = scale_logical_to_pixels(wsize.x);
        wsize.y = scale_logical_to_pixels(wsize.y);
    }

    platform_screen_destroy();

#if defined(GAME_PLATFORM_ANDROID)
    // Fix for wrong colors on some android devices
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
#endif

    logs::info("Creating screen %d x %d, %s, driver: %s", wsize.x, wsize.y, fullscreen ? "fullscreen" : "windowed", SDL_GetCurrentVideoDriver());
    Uint32 flags = SDL_WINDOW_RESIZABLE;

#if SDL_VERSION_ATLEAST(2, 0, 1)
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif

    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    platform_render_setup_options(renderer);
    g_screen.window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wsize.x, wsize.y, flags);

    if (!g_screen.window) {
        logs::error("Unable to create window: %s", SDL_GetError());
        return 0;
    }

#if !defined(_WIN32) && !defined(__APPLE__)
    // Windows and mac don't need setting a window icon. In fact the icon gets blurry if we do
    set_window_icon();
#endif

    if (system_is_fullscreen_only()) {
        SDL_GetWindowSize(g_screen.window, &wsize.x, &wsize.y);
    }

    if (!platform_renderer_init(g_screen.window, renderer)) {
        return 0;
    }

    vec2i tmp_size;
    SDL_SetWindowIcon(g_screen.window, load_icon_surface(":akhenaten_72.png", tmp_size));

#if !defined(__APPLE__)
    if (fullscreen && SDL_GetNumVideoDisplays() > 1) {
        SDL_SetWindowGrab(g_screen.window, SDL_TRUE);
    }
#endif // !__APPLE__
    set_scale_percentage(display_scale_percentage, wsize.x, wsize.y);
    int error = platform_screen_resize(wsize.x, wsize.y, 1);

    return error;
}

void platform_screen_destroy(void) {
    platform_renderer_destroy();
    if (g_screen.window) {
        SDL_DestroyWindow(g_screen.window);
        g_screen.window = 0;
    }
}

bool platform_screen_resize(int pixel_width, int pixel_height, int save) {
#ifdef __ANDROID__
    set_scale_for_screen(pixel_width, pixel_height);
#endif

    int logical_width = scale_pixels_to_logical(pixel_width);
    int logical_height = scale_pixels_to_logical(pixel_height);

    if (save) {
        g_settings.display_size = {logical_width, logical_height};
    }

    if (platform_renderer_create_render_texture(logical_width, logical_height)) {
        screen_set_resolution(logical_width, logical_height);
        return true;
    } 

    return false;
}

int system_scale_display(int display_scale_percentage) {
    int width, height;
    SDL_GetWindowSize(g_screen.window, &width, &height);
    set_scale_percentage(display_scale_percentage, width, height);
    platform_screen_resize(width, height, 1);
    return g_screen.scale_percentage;
}

int system_get_max_display_scale(void) {
    int width, height;
    SDL_GetWindowSize(g_screen.window, &width, &height);
    return get_max_scale_percentage(width, height);
}

void platform_screen_move(int x, int y) {
    if (!g_settings.is_fullscreen()) {
        g_screen.pos.x = x;
        g_screen.pos.y = y;
        g_screen.centered = 0;
        SDL_SetWindowPosition(g_screen.window, x, y);
    }
}

void platform_screen_set_fullscreen(void) {
    SDL_GetWindowPosition(g_screen.window, &g_screen.pos.x, &g_screen.pos.y);
    int display = SDL_GetWindowDisplayIndex(g_screen.window);
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(display, &mode);
    logs::info("User to fullscreen %d x %d on display %d", mode.w, mode.h, display);
    if (0 != SDL_SetWindowFullscreen(g_screen.window, SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        logs::info("Unable to enter fullscreen: %s", SDL_GetError());
        return;
    }
    SDL_SetWindowDisplayMode(g_screen.window, &mode);

#if !defined(__APPLE__)
    if (SDL_GetNumVideoDisplays() > 1) {
        SDL_SetWindowGrab(g_screen.window, SDL_TRUE);
    }
#endif
    g_settings.set_fullscreen(1);
    g_settings.display_size = {mode.w, mode.h};
}

void platform_screen_set_windowed() {
    if (system_is_fullscreen_only()) {
        return;
    }
    auto wsize = g_settings.display_size;
    int pixel_width = scale_logical_to_pixels(wsize.x);
    int pixel_height = scale_logical_to_pixels(wsize.y);
    int display = SDL_GetWindowDisplayIndex(g_screen.window);
    logs::info("User to windowed %d x %d on display %d", pixel_width, pixel_height, display);
    SDL_SetWindowFullscreen(g_screen.window, 0);
    SDL_SetWindowSize(g_screen.window, pixel_width, pixel_height);
    if (g_screen.centered) {
        platform_screen_center_window();
    }
    if (SDL_GetWindowGrab(g_screen.window) == SDL_TRUE) {
        SDL_SetWindowGrab(g_screen.window, SDL_FALSE);
    }
    g_settings.set_fullscreen(false);
    g_settings.display_size = {pixel_width, pixel_height};
}

void platform_screen_set_window_size(int logical_width, int logical_height) {
    if (system_is_fullscreen_only()) {
        return;
    }
    int pixel_width = scale_logical_to_pixels(logical_width);
    int pixel_height = scale_logical_to_pixels(logical_height);
    int display = SDL_GetWindowDisplayIndex(g_screen.window);
    if (g_settings.is_fullscreen()) {
        SDL_SetWindowFullscreen(g_screen.window, 0);
    } else {
        SDL_GetWindowPosition(g_screen.window, &g_screen.pos.x, &g_screen.pos.y);
    }
    if (SDL_GetWindowFlags(g_screen.window) & SDL_WINDOW_MAXIMIZED) {
        SDL_RestoreWindow(g_screen.window);
    }
    SDL_SetWindowSize(g_screen.window, pixel_width, pixel_height);
    if (g_screen.centered) {
        platform_screen_center_window();
    }
    logs::info("User resize to %d x %d on display %d", pixel_width, pixel_height, display);
    if (SDL_GetWindowGrab(g_screen.window) == SDL_TRUE) {
        SDL_SetWindowGrab(g_screen.window, SDL_FALSE);
    }
    g_settings.set_fullscreen(0);
    g_settings.display_size = {pixel_width, pixel_height};
}

void platform_screen_center_window() {
    int display = SDL_GetWindowDisplayIndex(g_screen.window);
    SDL_SetWindowPosition(g_screen.window, SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display));
    g_screen.centered = 1;
}

#ifdef _WIN32
void platform_screen_recreate_texture() {
    // On Windows, if ctrl + alt + del is pressed during fullscreen, the rendering context may be lost for a few frames
    // after restoring the window, preventing the texture from being recreated. This forces an attempt to recreate the
    // texture every frame to bypass that issue.
    if (g_settings.is_fullscreen() && platform_renderer_lost_render_texture()) {
        SDL_DisplayMode mode;
        SDL_GetWindowDisplayMode(g_screen.window, &mode);
        screen_set_resolution(scale_pixels_to_logical(mode.w), scale_pixels_to_logical(mode.h));
        platform_renderer_create_render_texture(screen_width(), screen_height());
    }
}
#endif

void platform_screen_show_error_message_box(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, g_screen.window);
}

void system_set_mouse_position(int* x, int* y) {
    *x = calc_bound(*x, 0, screen_width() - 1);
    *y = calc_bound(*y, 0, screen_height() - 1);
    SDL_WarpMouseInWindow(g_screen.window, scale_logical_to_pixels(*x), scale_logical_to_pixels(*y));
}

int system_is_fullscreen_only(void) {
#if defined(GAME_PLATFORM_ANDROID) || defined(__SWITCH__) || defined(__vita__)
    return 1;
#else
    return 0;
#endif
}

void system_get_max_resolution(int* width, int* height) {
    SDL_DisplayMode mode;
    int index = SDL_GetWindowDisplayIndex(g_screen.window);
    SDL_GetCurrentDisplayMode(index, &mode);
    *width = scale_pixels_to_logical(mode.w);
    *height = scale_pixels_to_logical(mode.h);
}

// void platform_screen_render(void) {
//     if (config_get(CONFIG_UI_ZOOM)) {
//         SDL_RenderClear(SDL.renderer);
//         city_view_get_scaled_viewport(&city_texture_position.offset.x, &city_texture_position.offset.y,
//                                         &city_texture_position.renderer.w, &city_texture_position.offset.h);
//         city_view_get_scaled_viewport(&city_texture_position.offset.x, &city_texture_position.offset.y,
//                                       &city_texture_position.offset.w, &city_texture_position.offset.h);
//         SDL_UpdateTexture(SDL.texture_city, &city_texture_position.offset, graphics_canvas(CANVAS_CITY),
//                           screen_width() * 4 * 2);
//         SDL_RenderCopy(SDL.renderer, SDL.texture_city, &city_texture_position.offset,
//         &city_texture_position.renderer);
//     }
//     SDL_UpdateTexture(SDL.texture_ui, NULL, graphics_canvas(CANVAS_UI), screen_width() * 4);
//     SDL_RenderCopy(SDL.renderer, SDL.texture_ui, NULL, NULL);
//     SDL_RenderPresent(SDL.renderer);
// }