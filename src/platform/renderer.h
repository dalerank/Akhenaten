#pragma once

#include "graphics/color.h"

#include "content/file_formats.h"
#include "content/vfs.h"
#include "core/string.h"
#include "core/vec2i.h"
#include "graphics/image.h"

#include <string>
#include <vector>

enum e_custome_image_type {
    CUSTOM_IMAGE_NONE = 0,
    CUSTOM_IMAGE_EXTERNAL = 1,
    CUSTOM_IMAGE_MINIMAP = 2,
    CUSTOM_IMAGE_VIDEO = 3,
    CUSTOM_IMAGE_EMPIRE_MAP = 4,
    CUSTOM_IMAGE_RED_FOOTPRINT = 5,
    CUSTOM_IMAGE_GREEN_FOOTPRINT = 6,
    CUSTOM_IMAGE_MAX = 7
};

enum { IMAGE_FILTER_NEAREST = 0, IMAGE_FILTER_LINEAR = 1 };

int platform_renderer_init(SDL_Window* window, std::string renderer);
int platform_renderer_create_render_texture(int width, int height);
int platform_renderer_lost_render_texture(void);
void platform_renderer_invalidate_target_textures(void);
void platform_renderer_generate_mouse_cursor_texture(int cursor_id, int size, const color* pixels, int hotspot_x, int hotspot_y);
void platform_renderer_clear();
void platform_renderer_render();
void platform_renderer_pause();
void platform_renderer_resume();
void platform_renderer_destroy();

struct video_mode {
    int w, h;
    bstring64 str;
    inline video_mode()
      : w(0),
        h(0) {
    }
    inline video_mode(int _w, int _h)
      : w(_w),
        h(_h) {
        char buffer[64] = {0};
        snprintf(buffer, 64, "%u x %u", _w, _h);
        str = buffer;
    }
    inline bool operator<(const video_mode& o) const {
        return ((int64_t(w) << 32) + h) < ((int64_t(o.w) << 32) + o.h);
    }
};

class graphics_renderer_interface {
public:
    void clear_screen();
    void set_viewport(int x, int y, int width, int height);
    void reset_viewport();
    void set_clip_rectangle(int x, int y, int width, int height);
    void reset_clip_rectangle();

    void draw_line(int x_start, int x_end, int y_start, int y_end, color color);
    void draw_rect(int x, int y, int width, int height, color color);
    void fill_rect(int x, int y, int width, int height, color color);

    void draw_image(const image_t* img, float x, float y, color color, float scale, bool mirrored);
    int save_screen_buffer(color *pixels, int x, int y, int width, int height, int row_width);

    void create_custom_texture(int type, int width, int height);
    int has_custom_texture(int type);
    color* get_custom_texture_buffer(int type, int* actual_texture_width);
    void release_custom_texture_buffer(int type);
    void update_custom_texture(int type);
    void update_custom_texture_yuv(int type, const uint8_t* y_data, int y_width, const uint8_t* cb_data, int cb_width, const uint8_t* cr_data, int cr_width);
    void draw_custom_texture(int type, int x, int y, float scale);

    int save_texture_from_screen(int image_id, int x, int y, int width, int height);
    void draw_saved_texture_to_screen(int image_id, int x, int y, int width, int height);

    vec2i get_max_image_size();

    SDL_Texture* create_texture_from_buffer(color* p_data, int width, int height);

    bool save_texture_to_file(const char* filename, SDL_Texture* tex, e_file_format file_format = FILE_FORMAT_BMP);
};

graphics_renderer_interface* graphics_renderer();

void set_render_scale(float scale);
std::vector<video_mode> get_video_modes();
std::vector<std::string> get_video_drivers(bool log);
