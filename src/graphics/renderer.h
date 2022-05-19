#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <core/image_packer.h>
#include "core/image.h"

//enum {
//    ATLAS_FIRST = 0,
//    ATLAS_MAIN = 0,
//    ATLAS_ENEMY = 1,
//    ATLAS_FONT = 2,
//    ATLAS_EXTRA_ASSET = 3,
//    ATLAS_UNPACKED_EXTRA_ASSET = 4,
//    ATLAS_CUSTOM = 5,
//    ATLAS_EXTERNAL = 6,
//    ATLAS_MAX = 7
//};

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

//typedef struct {
//    int type;
//    int num_images;
//    color_t **buffers;
//    SDL_Texture **textures;
//    int *image_widths;
//    int *image_heights;
//} image_atlas_data;

void SET_RENDER_SCALE(float scale);

typedef struct {
    void (*clear_screen)(void);

    void (*set_viewport)(int x, int y, int width, int height);
    void (*reset_viewport)(void);

    void (*set_clip_rectangle)(int x, int y, int width, int height);
    void (*reset_clip_rectangle)(void);

    void (*draw_line)(int x_start, int x_end, int y_start, int y_end, color_t color);
    void (*draw_rect)(int x, int y, int width, int height, color_t color);
    void (*fill_rect)(int x, int y, int width, int height, color_t color);

    void (*draw_image)(const image *img, float x, float y, color_t color, float scale, bool mirrored);
//    void (*draw_isometric_top)(const image *img, int x, int y, color_t color, float scale);

    void (*create_custom_image)(int type, int width, int height);
    int (*has_custom_image)(int type);
    color_t *(*get_custom_image_buffer)(int type, int *actual_texture_width);
    void (*release_custom_image_buffer)(int type);
    void (*update_custom_image)(int type);
    void (*update_custom_image_yuv)(int type, const uint8_t *y_data, int y_width,
        const uint8_t *cb_data, int cb_width, const uint8_t *cr_data, int cr_width);
    void (*draw_custom_image)(int type, int x, int y, float scale);
    int (*supports_yuv_image_format)(void);

    int (*save_image_from_screen)(int image_id, int x, int y, int width, int height);
    void (*draw_image_to_screen)(int image_id, int x, int y, int width, int height);
    int (*save_screen_buffer)(color_t *pixels, int x, int y, int width, int height, int row_width);

    void (*get_max_image_size)(int *width, int *height);

//    const image_atlas_data *(*prepare_image_atlas)(int type, int num_images, int last_width, int last_height);
    int (*prepare_image_atlas)(imagepak *pak, image_packer *packer);
//    int (*create_image_atlas)(const image_atlas_data *data);
    bool (*create_image_atlas)(imagepak *pak, image_packer *packer);
//    int (*has_image_atlas)(int type);
    void (*free_image_atlas)(imagepak *pak);

    void (*load_unpacked_image)(const image *img, const color_t *pixels);

    int (*should_pack_image)(int width, int height);

    int (*isometric_images_are_joined)(void);

//    void (*update_scale_mode)(int city_scale);
} graphics_renderer_interface;

const graphics_renderer_interface *graphics_renderer(void);

void graphics_renderer_set_interface(const graphics_renderer_interface *new_renderer);

#endif // GRAPHICS_RENDERER_H
