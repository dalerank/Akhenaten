#include "platform/screen.h"

#include "core/calc.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/menu.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "input/mouse.h"
#include "config/config.h"

#include "vita.h"
#include <vita2d.h>

// SDL_log
#include <SDL.h>

platform_screen_t g_platform_screen;

SDL_Window* as_sdl_window(void* window) {
    return static_cast<SDL_Window*>(window);
}

static SDL_Renderer* my_renderer;

SDL_Rect city_texture_position;

vita2d_texture* tex_buffer_ui = NULL;
vita2d_texture* tex_buffer_city = NULL;

static void create_textures(void) {
    logs::info("Creating empty textures");
    if (!tex_buffer_ui) {
        tex_buffer_ui = vita2d_create_empty_texture_format(VITA_DISPLAY_WIDTH,
                                                           VITA_DISPLAY_HEIGHT,
                                                           SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB);
    }
    if (config_get(CONFIG_UI_ZOOM) && !tex_buffer_city) {
        tex_buffer_city = vita2d_create_empty_texture_format(VITA_DISPLAY_WIDTH * 2,
                                                             VITA_DISPLAY_HEIGHT * 2,
                                                             SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB);
    }
    logs::info("Creating empty textures: done");
}

int platform_screen_t::create(const xstring& title, const xstring& /*renderer*/, bool /*fullscreen*/,
  int /*display_scale_percentage*/, vec2i /*screen_size*/) {
    if (!window) {
        window = SDL_CreateWindow(
          "Dummy window used only as event listener", 0, 0, VITA_DISPLAY_WIDTH, VITA_DISPLAY_HEIGHT, 0);
    }
    if (!my_renderer) {
        my_renderer = SDL_CreateRenderer(as_sdl_window(window), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
    logs::info("Creating empty texture");
    tex_buffer = vita2d_create_empty_texture_format(VITA_DISPLAY_WIDTH,
                                                    VITA_DISPLAY_HEIGHT,
                                                    SCE_GXM_TEXTURE_FORMAT_X8U8U8U8_1RGB);
    logs::info("Creating empty texture: done");
    (void)title;

    return resize(VITA_DISPLAY_WIDTH, VITA_DISPLAY_HEIGHT, 0) ? 1 : 0;
}

void platform_screen_t::destroy() {
    if (my_renderer) {
        SDL_DestroyRenderer(my_renderer);
        my_renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(as_sdl_window(window));
        window = nullptr;
    }
}

bool platform_screen_t::resize(int width, int height, int /*save*/) {
    g_screen.set_resolution(width, height);
    return true;
}

void platform_screen_t::move(int /*x*/, int /*y*/) {
}

void platform_screen_t::set_fullscreen() {
    logs::info("User to fullscreen");
    setting_set_display(1, VITA_DISPLAY_WIDTH, VITA_DISPLAY_HEIGHT);
}

void platform_screen_t::set_windowed() {
    int width, height;
    setting_window(&width, &height);
    logs::info("User to windowed");
    setting_set_display(0, width, height);
}

void platform_screen_t::set_window_size(int width, int height) {
    logs::info("User resize to");
    setting_set_display(0, width, height);
}

void platform_screen_t::center_window() {
}

void platform_screen_t::show_error_message_box(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, as_sdl_window(window));
}

void* platform_screen_t::surface_format() {
    SDL_Surface* scr_surface = SDL_GetWindowSurface(as_sdl_window(window));
    return scr_surface ? scr_surface->format : nullptr;
}

vec2i platform_screen_t::get_max_resolution() {
    return {VITA_DISPLAY_WIDTH, VITA_DISPLAY_HEIGHT};
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
    vita2d_start_drawing();
    vita2d_clear_screen();
    if (config_get(CONFIG_UI_ZOOM)) {
        city_view_get_scaled_viewport(&city_texture_position.x,
                                      &city_texture_position.y,
                                      &city_texture_position.w,
                                      &city_texture_position.h);
        float scale = city_view_get_scale() / 100.0f;
        scale = 1 / scale;
        vita2d_draw_texture_part_scale(tex_buffer_city,
                                       0,
                                       TOP_MENU_HEIGHT,
                                       city_texture_position.x,
                                       city_texture_position.y,
                                       city_texture_position.w,
                                       city_texture_position.h,
                                       scale,
                                       scale);
    }
    vita2d_draw_texture(tex_buffer_ui, 0, 0);

    const mouse* mouse = mouse_get();
    if (!mouse->is_touch) {
        vita2d_draw_texture(current_cursor->texture,
                            mouse->x - current_cursor->hotspot_x,
                            mouse->y - current_cursor->hotspot_y);
    }
    vita2d_end_drawing();
    vita2d_wait_rendering_done();
    vita2d_swap_buffers();
}

void platform_screen_t::warp_mouse(int* x, int* y) {
    *x = calc_bound(*x, 0, VITA_DISPLAY_WIDTH - 1);
    *y = calc_bound(*y, 0, VITA_DISPLAY_HEIGHT - 1);
    SDL_WarpMouseInWindow(as_sdl_window(window), *x, *y);
}

int system_is_fullscreen_only(void) {
    return 1;
}

void system_reload_textures(void) {
    create_textures();
    g_screen.set_resolution(VITA_DISPLAY_WIDTH, VITA_DISPLAY_HEIGHT);
}

int system_save_screen_buffer(void* pixels) {
    unsigned int* buffer = vita2d_get_current_fb();
    memcpy(pixels, buffer, sizeof(unsigned int) * VITA_DISPLAY_WIDTH * VITA_DISPLAY_HEIGHT);
    return 1;
}
