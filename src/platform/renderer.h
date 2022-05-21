#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

#include "graphics/color.h"

#include "SDL.h"
#include "core/file_formats.h"
#include "core/struct_types.h"
#include "core/image.h"

enum {
    CUSTOM_IMAGE_NONE = 0,
    CUSTOM_IMAGE_EXTERNAL = 1,
    CUSTOM_IMAGE_MINIMAP = 2,
    CUSTOM_IMAGE_VIDEO = 3,
    CUSTOM_IMAGE_EMPIRE_MAP = 4,
    CUSTOM_IMAGE_RED_FOOTPRINT = 5,
    CUSTOM_IMAGE_GREEN_FOOTPRINT = 6,
    CUSTOM_IMAGE_MAX = 7
};

enum {
    IMAGE_FILTER_NEAREST = 0,
    IMAGE_FILTER_LINEAR = 1
};

int platform_renderer_init(SDL_Window *window);
int platform_renderer_create_render_texture(int width, int height);
int platform_renderer_lost_render_texture(void);
void platform_renderer_invalidate_target_textures(void);
void platform_renderer_generate_mouse_cursor_texture(int cursor_id, int size, const color_t *pixels, int hotspot_x, int hotspot_y);
//void platform_renderer_clear(void);
void platform_renderer_render(void);
void platform_renderer_pause(void);
void platform_renderer_resume(void);
void platform_renderer_destroy(void);

//typedef struct image_t;

class graphics_renderer_interface {

public:
    void clear_screen();
    void set_viewport(int x, int y, int width, int height);
    void reset_viewport();
    void set_clip_rectangle(int x, int y, int width, int height);
    void reset_clip_rectangle();

    void draw_line(int x_start, int x_end, int y_start, int y_end, color_t color);
    void draw_rect(int x, int y, int width, int height, color_t color);
    void fill_rect(int x, int y, int width, int height, color_t color);

    void draw_image(const image_t *img, float x, float y, color_t color, float scale, bool mirrored);
//    void draw_isometric_top(const image_t *img, int x, int y, color_t color, float scale);

    void create_custom_texture(int type, int width, int height);
    int has_custom_texture(int type);
    color_t *get_custom_texture_buffer(int type, int *actual_texture_width);
    void release_custom_texture_buffer(int type);
    void update_custom_texture(int type);
    void update_custom_texture_yuv(int type, const uint8_t *y_data, int y_width, const uint8_t *cb_data, int cb_width, const uint8_t *cr_data, int cr_width);
    void draw_custom_texture(int type, int x, int y, float scale);
//    int supports_yuv_texture_format(void);

    int save_texture_from_screen(int image_id, int x, int y, int width, int height);
    void draw_saved_texture_to_screen(int image_id, int x, int y, int width, int height);
//    int save_screen_buffer(color_t *pixels, int x, int y, int width, int height, int row_width);

    pixel_coordinate get_max_image_size();

//    int prepare_image_atlas(atlas_data_t *atlas, image_packer *packer);
    SDL_Texture *create_texture_atlas(color_t *p_data, int width, int height);

//    void load_unpacked_image(const image *img, const color_t *pixels);
//    bool should_pack_image(int width, int height);
//    bool isometric_images_are_joined(void);

//    void (*update_scale_mode)(int city_scale);

    bool save_texture_to_file(const char *filename, SDL_Texture *tex, file_format_t file_format = FILE_FORMAT_BMP);
};


//extern graphics_renderer_interface *graphics_renderer;
graphics_renderer_interface *graphics_renderer(void);
//void graphics_renderer_set_interface(const graphics_renderer_interface *new_renderer);

void SET_RENDER_SCALE(float scale);

#endif // PLATFORM_RENDERER_H
