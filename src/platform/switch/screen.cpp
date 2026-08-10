#include "platform/screen.h"

#include "SDL.h"

#include "core/calc.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/menu.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "input/mouse.h"
#include "config/config.h"

#include "switch.h"

platform_screen_t g_platform_screen;

namespace {
SDL_Window* as_sdl_window(void* window) {
    return static_cast<SDL_Window*>(window);
}
} // namespace

struct {
    SDL_Renderer* renderer;
    SDL_Texture* texture_ui;
    SDL_Texture* texture_city;
} SDL;

static struct {
    SDL_Rect offset;
    SDL_Rect renderer;
} city_texture_position;

static struct {
    int x;
    int y;
} window_pos;

int platform_screen_t::create(const xstring& title, const xstring& /*renderer*/, bool /*fullscreen*/,
  int /*display_scale_percentage*/, vec2i /*screen_size*/) {
    int width, height;
    int fullscreen = 1;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    if (fullscreen) {
        SDL_DisplayMode mode;
        SDL_GetDesktopDisplayMode(0, &mode);
        width = mode.w;
        height = mode.h;
    } else {
        setting_window(&width, &height);
    }

    destroy();

    logs::info("Creating screen %d x %d, fullscreen? %d\n", width, height, fullscreen);
    Uint32 flags = SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, flags);
    if (!window) {
        logs::error("Unable to create window: %s", SDL_GetError());
        return 0;
    }

    SDL.renderer = SDL_CreateRenderer(as_sdl_window(window), -1, SDL_RENDERER_PRESENTVSYNC);
    if (!SDL.renderer) {
        logs::info("Unable to create renderer, trying software renderer: %s", SDL_GetError());
        SDL.renderer = SDL_CreateRenderer(as_sdl_window(window), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);
        if (!SDL.renderer) {
            logs::error("Unable to create renderer: %s", SDL_GetError());
            return 0;
        }
    }

    SDL_SetRenderDrawColor(SDL.renderer, 0, 0, 0, 0xff);
    return resize(SWITCH_DISPLAY_WIDTH, SWITCH_DISPLAY_HEIGHT, 0) ? 1 : 0;
}

static int create_textures(int width, int height) {
    if (SDL.texture_ui) {
        SDL_DestroyTexture(SDL.texture_ui);
        SDL.texture_ui = 0;
    }
    if (SDL.texture_city) {
        SDL_DestroyTexture(SDL.texture_city);
        SDL.texture_city = 0;
    }

    SDL.texture_ui
      = SDL_CreateTexture(SDL.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    int city_texture_error;

    if (config_get(CONFIG_UI_ZOOM)) {
        SDL.texture_city = SDL_CreateTexture(
          SDL.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width * 2, height * 2);
        city_texture_position.renderer.x = 0;
        city_texture_position.renderer.y = TOP_MENU_HEIGHT;
        city_texture_position.renderer.h = height * 2 - TOP_MENU_HEIGHT;
        SDL_SetTextureBlendMode(SDL.texture_ui, SDL_BLENDMODE_BLEND);
        city_texture_error = SDL.texture_city == 0;
    } else {
        city_texture_error = 0;
        SDL_SetTextureBlendMode(SDL.texture_ui, SDL_BLENDMODE_NONE);
    }

    if (SDL.texture_ui && !city_texture_error) {
        logs::info("Textures created (%d x %d)", width, height);
        return 1;
    } else {
        logs::error("Unable to create textures: %s", SDL_GetError());
        return 0;
    }
}

void platform_screen_t::destroy() {
    if (SDL.texture_ui) {
        SDL_DestroyTexture(SDL.texture_ui);
        SDL.texture_ui = 0;
    }
    if (SDL.texture_city) {
        SDL_DestroyTexture(SDL.texture_city);
        SDL.texture_city = 0;
    }
    if (SDL.renderer) {
        SDL_DestroyRenderer(SDL.renderer);
        SDL.renderer = 0;
    }
    if (window) {
        SDL_DestroyWindow(as_sdl_window(window));
        window = nullptr;
    }
}

bool platform_screen_t::resize(int width, int height, int /*save*/) {
    setting_set_display(setting_fullscreen(), width, height);
    if (create_textures(width, height)) {
        g_screen.set_resolution(width, height);
        return true;
    }
    return false;
}

void platform_screen_t::move(int /*x*/, int /*y*/) {
}

void platform_screen_t::set_fullscreen() {
    SDL_GetWindowPosition(as_sdl_window(window), &window_pos.x, &window_pos.y);
    int orig_w, orig_h;
    SDL_GetWindowSize(as_sdl_window(window), &orig_w, &orig_h);
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(as_sdl_window(window)), &mode);
    logs::info("User to fullscreen %d x %d\n", mode.w, mode.h);
    if (0 != SDL_SetWindowFullscreen(as_sdl_window(window), SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        logs::info("Unable to enter fullscreen: %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowDisplayMode(as_sdl_window(window), &mode);
    setting_set_display(1, mode.w, mode.h);
}

void platform_screen_t::set_windowed() {
    int width, height;
    setting_window(&width, &height);
    logs::info("User to windowed %d x %d\n", width, height);
    SDL_SetWindowFullscreen(as_sdl_window(window), 0);
    SDL_SetWindowSize(as_sdl_window(window), width, height);
    SDL_SetWindowPosition(as_sdl_window(window), window_pos.x, window_pos.y);
    setting_set_display(0, width, height);
}

void platform_screen_t::set_window_size(int width, int height) {
    if (setting_fullscreen()) {
        SDL_SetWindowFullscreen(as_sdl_window(window), 0);
    }
    SDL_SetWindowSize(as_sdl_window(window), width, height);
    SDL_SetWindowPosition(as_sdl_window(window), window_pos.x, window_pos.y);
    logs::info("User resize to %d x %d\n", width, height);
    setting_set_display(0, width, height);
}

void platform_screen_t::center_window() {
    SDL_SetWindowPosition(as_sdl_window(window), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void platform_screen_t::show_error_message_box(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, as_sdl_window(window));
}

void* platform_screen_t::surface_format() {
    SDL_Surface* scr_surface = SDL_GetWindowSurface(as_sdl_window(window));
    return scr_surface ? scr_surface->format : nullptr;
}

vec2i platform_screen_t::get_max_resolution() {
    return {SWITCH_DISPLAY_WIDTH, SWITCH_DISPLAY_HEIGHT};
}

void platform_screen_t::recreate_texture() {
}

void platform_screen_t::set_scale_percentage(int /*new_scale*/, int /*pixel_width*/, int /*pixel_height*/) {
    scale_percentage = 100;
}

int platform_screen_t::scale_display(int /*display_scale_percentage*/) {
    return scale_percentage;
}

void platform_screen_render(void) {
    if (config_get(CONFIG_UI_ZOOM)) {
        SDL_RenderClear(SDL.renderer);
        city_view_get_unscaled_viewport(&city_texture_position.offset.x,
                                        &city_texture_position.offset.y,
                                        &city_texture_position.renderer.w,
                                        &city_texture_position.offset.h);
        city_view_get_scaled_viewport(&city_texture_position.offset.x,
                                      &city_texture_position.offset.y,
                                      &city_texture_position.offset.w,
                                      &city_texture_position.offset.h);
        city_texture_position.renderer.w = city_texture_position.renderer.w * 2 + 1;
        SDL_UpdateTexture(SDL.texture_city,
                          &city_texture_position.offset,
                          graphics_canvas(CANVAS_CITY),
                          screen_width() * 4 * 2);
        SDL_RenderCopy(SDL.renderer, SDL.texture_city, &city_texture_position.offset, &city_texture_position.renderer);
    }
    SDL_UpdateTexture(SDL.texture_ui, NULL, graphics_canvas(CANVAS_UI), screen_width() * 4);
    SDL_RenderCopy(SDL.renderer, SDL.texture_ui, NULL, NULL);

    const mouse* mouse = mouse_get();
    if (!mouse->is_touch) {
        SDL_Rect dst;
        dst.x = ((mouse->x - current_cursor->hotspot_x) * SWITCH_PIXEL_WIDTH) / SWITCH_DISPLAY_WIDTH;
        dst.y = ((mouse->y - current_cursor->hotspot_y) * SWITCH_PIXEL_HEIGHT) / SWITCH_DISPLAY_HEIGHT;
        dst.w = (32 * SWITCH_PIXEL_WIDTH) / SWITCH_DISPLAY_WIDTH;
        dst.h = (32 * SWITCH_PIXEL_HEIGHT) / SWITCH_DISPLAY_HEIGHT;
        SDL_RenderCopy(SDL.renderer, current_cursor->texture, NULL, &dst);
    }

    SDL_RenderPresent(SDL.renderer);
}

void platform_screen_t::warp_mouse(int* x, int* y) {
    *x = calc_bound(*x, 0, SWITCH_DISPLAY_WIDTH - 1);
    *y = calc_bound(*y, 0, SWITCH_DISPLAY_HEIGHT - 1);
    SDL_WarpMouseInWindow(as_sdl_window(window), *x, *y);
}

int system_is_fullscreen_only(void) {
    return 1;
}

void system_reload_textures(void) {
    int width = screen_width();
    int height = screen_height();
    create_textures(width, height);
    g_screen.set_resolution(width, height);
}

int system_save_screen_buffer(void* pixels) {
    return SDL_RenderReadPixels(SDL.renderer, NULL, SDL_PIXELFORMAT_ARGB8888, pixels, screen_width() * sizeof(color))
           == 0;
}
