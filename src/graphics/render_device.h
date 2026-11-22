#pragma once

#include "content/file_formats.h"
#include "core/string.h"
#include "core/vec2i.h"
#include "graphics/color.h"

#include <cstdint>

struct painter;
struct image_t;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;

enum e_custome_image_type {
    CUSTOM_IMAGE_NONE = 0,
    CUSTOM_IMAGE_EXTERNAL = 1,
    CUSTOM_IMAGE_MINIMAP = 2,
    CUSTOM_IMAGE_VIDEO = 3,
    CUSTOM_IMAGE_EMPIRE_MAP = 4,
    CUSTOM_IMAGE_RED_FOOTPRINT = 5,
    CUSTOM_IMAGE_GREEN_FOOTPRINT = 6,
    CUSTOM_IMAGE_CLOUDS = 7,
    CUSTOM_IMAGE_MAX = 8
};

struct render_material_t {
    SDL_Texture* texture;
    int blend;
    bool linear;
};

struct sprite_draw_t {
    uint16_t material;
    int src_x, src_y, src_w, src_h;
    float dst_x, dst_y, dst_w, dst_h;
    uint8_t r, g, b, a;
    double angle;
    bool mirrored;
    uint16_t clip = 0;
};

struct graphics_renderer_interface {
    void clear_screen();
    void set_clip_rectangle(vec2i pos, int width, int height);
    bool inside_clip_rectangle(vec2i pos);
    rect clip_rectangle();
    void reset_clip_rectangle();
    void apply_filter();

    void draw_line(vec2i start, vec2i end, color color);
    void draw_pixel(vec2i pixel, color color);
    void draw_rect(vec2i start, vec2i size, color color);
    void fill_rect(vec2i start, vec2i size, color color);
    uint16_t material(SDL_Texture* texture, int blend, bool linear);
    void draw_sprite(const sprite_draw_t& sprite);

    bool save_screen_buffer(painter& ctx, color* pixels, int x, int y, int width, int height, int row_width);

    void create_custom_texture(int type, int width, int height);
    int has_custom_texture(int type);
    color* get_custom_texture_buffer(int type, int* actual_texture_width);
    void release_custom_texture_buffer(int type);
    void update_custom_texture(int type);
    SDL_Texture* get_custom_texture(int type);
    void update_custom_texture_from(int type, const color* buffer, int x_offset, int y_offset, int width, int height);
    void update_custom_texture_yuv(int type, const uint8_t* y_data, int y_width, const uint8_t* cb_data, int cb_width,
      const uint8_t* cr_data, int cr_width);
    void draw_texture_advanced(const image_t* img, float x, float y, color color, float scale_x, float scale_y,
      double angle, int disable_coord_scaling);
    void draw_custom_texture(int type, int x, int y, float scale);

    int save_texture_from_screen(int image_id, vec2i pos, int width, int height);
    int ensure_saved_texture(int image_id, int width, int height);
    bool begin_saved_texture_target(int image_id);
    void end_saved_texture_target();
    void delete_saved_texture(int image_id);
    void draw_saved_texture_to_screen(int image_id, int x, int y, int width, int height);
    void clear_saved_texture(int image_id, color clr);
    void set_texture_scale_mode(SDL_Texture* texture, float scale_factor, bool force_linear);
    unsigned int premult_alpha();

    vec2i get_max_image_size();

    SDL_Texture* create_texture_from_buffer(color* p_data, int width, int height);
    void destroy_texture(SDL_Texture* texture);
    SDL_Texture* create_grayscale_texture(SDL_Texture* tx, vec2i offset, vec2i size);
    SDL_Texture* create_texture_from_png_buffer(void* p_data, int size, vec2i& txsize);

    bool has_texture_scale_mode();

    bool save_texture_to_file(pcstr filename, SDL_Texture* tex, e_file_format file_format = FILE_FORMAT_BMP);
    float scale();

    /**
     * Returns whether the window must always be fullscreen
     * @return true when only fullscreen can be used, false otherwise
     */
    bool is_fullscreen_only();

    SDL_Renderer* renderer();
    SDL_Window* window();
};

extern graphics_renderer_interface g_render;

void set_render_scale(painter& ctx, float scale);
