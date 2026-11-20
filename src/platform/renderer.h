#pragma once

#include "graphics/render_device.h"

#include "content/file_formats.h"
#include "content/vfs.h"
#include "core/string.h"
#include "core/vec2i.h"
#include "core/svector.h"
#include "graphics/image.h"

#include <string>
#include <vector>

int platform_renderer_init(SDL_Window* window, xstring renderer);
int platform_renderer_create_render_texture(int width, int height);
void platform_renderer_invalidate_all_textures();

int platform_renderer_lost_render_texture(void);
void platform_renderer_invalidate_target_textures(void);
void platform_renderer_generate_mouse_cursor_texture(int cursor_id, int size, const color* pixels, int hotspot_x, int hotspot_y);
void platform_renderer_render();
void platform_renderer_pause();
void platform_renderer_resume();
void platform_renderer_destroy();
void platform_render_setup_options(xstring driver);
void platform_render_init_filters();
void platform_render_shutdown_filters();
bool platform_render_support_filters();
bool platform_render_any_filter_active();
void platform_render_create_context();
void platform_render_proceed_filter(int w, int h, int format, const std::vector<uint8_t> &pixels, std::vector<uint8_t> &output_pixels);
void platform_render_init_filter_context();

struct video_mode : public vec2i {
    bstring64 str;
    inline video_mode() : vec2i(0, 0) {}
    inline video_mode(int _w, int _h) : vec2i(_w, _h) {
        str.printf("%u x %u", x, y);
    }
    inline bool operator<(const video_mode& o) const {
        return ((int64_t(x) << 32) + y) < ((int64_t(o.x) << 32) + o.y);
    }
};

std::vector<video_mode> get_video_modes();
svector<xstring, 8> get_video_drivers(bool log);
svector<xstring, 8> render_backend_order(const xstring& requested, const svector<xstring, 8>& available);
xstring platform_render_preferred_backend(const xstring& requested);
xstring get_video_driver();
