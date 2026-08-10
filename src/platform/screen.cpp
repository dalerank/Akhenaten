#include "platform/screen.h"

#include "core/calc.h"
#include "core/log.h"
#include "game/game.h"
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

platform_screen_t g_platform_screen;

namespace {
SDL_Window* as_sdl_window(void* window) {
    return static_cast<SDL_Window*>(window);
}
} // namespace

static int get_max_scale_percentage(int pixel_width, int pixel_height) {
    int width_scale_pct = pixel_width * 100 / g_platform_screen.minimum.x;
    int height_scale_pct = pixel_height * 100 / g_platform_screen.minimum.y;
    return SDL_min(width_scale_pct, height_scale_pct);
}

void platform_screen_t::set_scale_percentage(int new_scale, int pixel_width, int pixel_height) {
#ifdef __vita__
    scale_percentage = 100;
#else
    scale_percentage = calc_bound(new_scale, 50, 500);
#endif

    if (!pixel_width || !pixel_height) {
        return;
    }

    int max_scale_pct = get_max_scale_percentage(pixel_width, pixel_height);
    if (max_scale_pct < scale_percentage) {
        scale_percentage = max_scale_pct;
        logs::info("Maximum scale of %i applied", scale_percentage);
    }

    SDL_SetWindowMinimumSize(as_sdl_window(window), scale_logical_to_pixels(minimum.x),
      scale_logical_to_pixels(minimum.y));

    const char* scale_quality = "linear";
#if !defined(GAME_PLATFORM_ANDROID)
    // Scale using nearest neighbour when we scale a multiple of 100%: makes it look sharper.
    // But not on MacOS: users are used to the linear interpolation since that's what Apple also does.
    if (scale_percentage % 100 == 0) {
        scale_quality = "nearest";
    }
#endif
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality);
}

void* platform_screen_t::surface_format() {
    SDL_Surface* scr_surface = SDL_GetWindowSurface(as_sdl_window(window));
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

int platform_screen_t::create(const xstring& title, const xstring& renderer, bool fullscreen,
  int display_scale_percentage, vec2i screen_size) {
#if defined(GAME_PLATFORM_ANDROID)
    // scale.screen_density = android_get_screen_density();
#endif

    set_scale_percentage(display_scale_percentage, 0, 0);

    vec2i wsize;
    if (!fullscreen && g_render.is_fullscreen_only()) {
        fullscreen = true;
    }

    // For emscripten, always use windowed mode and get size from canvas
    if (platform.is_emscripten()) {
        fullscreen = false;
        // Use a reasonable default size - actual size will be obtained after window creation
        wsize = {1920, 1080};
    } else if (fullscreen) {
        SDL_DisplayMode mode;
        SDL_GetDesktopDisplayMode(0, &mode);
        wsize = {mode.w, mode.h};
    } else {
        wsize = game_features::gameopt_display_size.to_vec2i();
        wsize.x = std::max<int>(wsize.x, screen_size.x);
        wsize.y = std::max<int>(wsize.y, screen_size.y);

        wsize.x = scale_logical_to_pixels(wsize.x);
        wsize.y = scale_logical_to_pixels(wsize.y);
    }

    destroy();

#if defined(GAME_PLATFORM_ANDROID)
    // Fix for wrong colors on some android devices
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
#endif

    logs::info("Creating screen %d x %d, %s, driver: %s", wsize.x, wsize.y, fullscreen ? "fullscreen" : "windowed",
      SDL_GetCurrentVideoDriver());
    Uint32 flags = SDL_WINDOW_RESIZABLE;

#if SDL_VERSION_ATLEAST(2, 0, 1)
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif

    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    platform_render_setup_options(renderer);
    if (!renderer.empty() && renderer == "opengl") {
        flags |= SDL_WINDOW_OPENGL;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wsize.x, wsize.y, flags);

    if (!window) {
        logs::error("Unable to create window: %s", SDL_GetError());
        return 0;
    }

#if !defined(_WIN32) && !defined(__APPLE__)
    // Windows and mac don't need setting a window icon. In fact the icon gets blurry if we do
    set_window_icon();
#endif

    // For emscripten and fullscreen-only platforms, always get the actual window size
    // as the canvas size may differ from the requested size
    if (g_render.is_fullscreen_only() || platform.is_emscripten()) {
        SDL_GetWindowSize(as_sdl_window(window), &wsize.x, &wsize.y);
    }

    if (!platform_renderer_init(as_sdl_window(window), renderer)) {
        return 0;
    }

    vec2i tmp_size;
    SDL_SetWindowIcon(as_sdl_window(window), load_icon_surface(":akhenaten_72.png", tmp_size));

#if !defined(__APPLE__)
    if (fullscreen && SDL_GetNumVideoDisplays() > 1) {
        SDL_SetWindowGrab(as_sdl_window(window), SDL_TRUE);
    }
#endif // !__APPLE__
    set_scale_percentage(display_scale_percentage, wsize.x, wsize.y);
    return resize(wsize.x, wsize.y, 1);
}

void platform_screen_t::destroy() {
    platform_renderer_destroy();
    if (window) {
        SDL_DestroyWindow(as_sdl_window(window));
        window = nullptr;
    }
}

bool platform_screen_t::resize(int pixel_width, int pixel_height, int save) {
#if defined(GAME_PLATFORM_ANDROID)
    set_scale_percentage(android_get_screen_density() * 100, pixel_width, pixel_height);
    logs::info("Auto-setting scale to %i", scale_percentage);
#endif

    int logical_width = scale_pixels_to_logical(pixel_width);
    int logical_height = scale_pixels_to_logical(pixel_height);

    if (save) {
        game_features::gameopt_display_size.set({logical_width, logical_height});
    }

    if (platform_renderer_create_render_texture(logical_width, logical_height)) {
        g_screen.set_resolution(logical_width, logical_height);
        return true;
    }

    return false;
}

int platform_screen_t::scale_display(int display_scale_percentage) {
    int width, height;
    SDL_GetWindowSize(as_sdl_window(window), &width, &height);
    set_scale_percentage(display_scale_percentage, width, height);
    resize(width, height, 1);
    return scale_percentage;
}

void platform_screen_t::move(int x, int y) {
    if (!game.is_fullscreen()) {
        pos.x = x;
        pos.y = y;
        centered = 0;
        SDL_SetWindowPosition(as_sdl_window(window), x, y);
    }
}

void platform_screen_t::set_fullscreen() {
    SDL_GetWindowPosition(as_sdl_window(window), &pos.x, &pos.y);
    int display = SDL_GetWindowDisplayIndex(as_sdl_window(window));
    SDL_DisplayMode mode;

    if (platform.is_emscripten()) {
        // For emscripten, get the actual window size after setting fullscreen
        // as SDL_GetDesktopDisplayMode may return incorrect values
        if (0 != SDL_SetWindowFullscreen(as_sdl_window(window), SDL_WINDOW_FULLSCREEN_DESKTOP)) {
            logs::info("Unable to enter fullscreen: %s", SDL_GetError());
            return;
        }
        SDL_GetWindowSize(as_sdl_window(window), &mode.w, &mode.h);
        logs::info("User to fullscreen %d x %d on display %d", mode.w, mode.h, display);
    } else {
        SDL_GetDesktopDisplayMode(display, &mode);
        logs::info("User to fullscreen %d x %d on display %d", mode.w, mode.h, display);
        if (0 != SDL_SetWindowFullscreen(as_sdl_window(window), SDL_WINDOW_FULLSCREEN_DESKTOP)) {
            logs::info("Unable to enter fullscreen: %s", SDL_GetError());
            return;
        }
        SDL_SetWindowDisplayMode(as_sdl_window(window), &mode);
    }

    if (!platform.is_macos()) {
        if (SDL_GetNumVideoDisplays() > 1) {
            SDL_SetWindowGrab(as_sdl_window(window), SDL_TRUE);
        }
    }

    game.set_fullscreen(true);
    game_features::gameopt_display_size.set({mode.w, mode.h});
}

void platform_screen_t::set_windowed() {
    if (g_render.is_fullscreen_only()) {
        return;
    }
    auto wsize = game_features::gameopt_display_size.to_vec2i();
    int pixel_width = scale_logical_to_pixels(wsize.x);
    int pixel_height = scale_logical_to_pixels(wsize.y);
    int display = SDL_GetWindowDisplayIndex(as_sdl_window(window));
    logs::info("User to windowed %d x %d on display %d", pixel_width, pixel_height, display);
    SDL_SetWindowFullscreen(as_sdl_window(window), 0);
    SDL_SetWindowSize(as_sdl_window(window), pixel_width, pixel_height);
    if (centered) {
        center_window();
    }
    if (SDL_GetWindowGrab(as_sdl_window(window)) == SDL_TRUE) {
        SDL_SetWindowGrab(as_sdl_window(window), SDL_FALSE);
    }
    game.set_fullscreen(false);
    game_features::gameopt_display_size.set({pixel_width, pixel_height});
}

void platform_screen_t::set_window_size(int logical_width, int logical_height) {
    if (g_render.is_fullscreen_only()) {
        return;
    }
    int pixel_width = scale_logical_to_pixels(logical_width);
    int pixel_height = scale_logical_to_pixels(logical_height);
    int display = SDL_GetWindowDisplayIndex(as_sdl_window(window));
    if (game.is_fullscreen()) {
        SDL_SetWindowFullscreen(as_sdl_window(window), 0);
    } else {
        SDL_GetWindowPosition(as_sdl_window(window), &pos.x, &pos.y);
    }
    if (SDL_GetWindowFlags(as_sdl_window(window)) & SDL_WINDOW_MAXIMIZED) {
        SDL_RestoreWindow(as_sdl_window(window));
    }
    SDL_SetWindowSize(as_sdl_window(window), pixel_width, pixel_height);
    if (centered) {
        center_window();
    }
    logs::info("User resize to %d x %d on display %d", pixel_width, pixel_height, display);
    if (SDL_GetWindowGrab(as_sdl_window(window)) == SDL_TRUE) {
        SDL_SetWindowGrab(as_sdl_window(window), SDL_FALSE);
    }
    game.set_fullscreen(false);
    game_features::gameopt_display_size.set({pixel_width, pixel_height});
}

void platform_screen_t::center_window() {
    int display = SDL_GetWindowDisplayIndex(as_sdl_window(window));
    SDL_SetWindowPosition(as_sdl_window(window), SDL_WINDOWPOS_CENTERED_DISPLAY(display),
      SDL_WINDOWPOS_CENTERED_DISPLAY(display));
    centered = 1;
}

void platform_screen_t::recreate_texture() {
#if defined(GAME_PLATFORM_WIN)
    // On Windows, if ctrl + alt + del is pressed during fullscreen, the rendering context may be lost for a few frames
    // after restoring the window, preventing the texture from being recreated. This forces an attempt to recreate the
    // texture every frame to bypass that issue.
    if (game.is_fullscreen() && platform_renderer_lost_render_texture()) {
        SDL_DisplayMode mode;
        SDL_GetWindowDisplayMode(as_sdl_window(window), &mode);
        g_screen.set_resolution(scale_pixels_to_logical(mode.w), scale_pixels_to_logical(mode.h));
        platform_renderer_create_render_texture(screen_width(), screen_height());
    }
#endif
}

void platform_screen_t::show_error_message_box(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, as_sdl_window(window));
}

void platform_screen_t::warp_mouse(int* x, int* y) {
    *x = calc_bound(*x, 0, screen_width() - 1);
    *y = calc_bound(*y, 0, screen_height() - 1);
    SDL_WarpMouseInWindow(as_sdl_window(window), scale_logical_to_pixels(*x), scale_logical_to_pixels(*y));
}

vec2i platform_screen_t::get_max_resolution() {
    SDL_DisplayMode mode;
    int index = SDL_GetWindowDisplayIndex(as_sdl_window(window));
    SDL_GetCurrentDisplayMode(index, &mode);
    return {scale_pixels_to_logical(mode.w), scale_pixels_to_logical(mode.h)};
}

