#include "renderer.h"

#include "core/log.h"
#include "core/profiler.h"
#include "graphics/screen.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "platform/screen.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "game/game.h"
#include "input/cursor.h"

#include <SDL.h>
#include <SDL_video.h>

#include <string.h>
#include <algorithm>
#include <set>
#include <string>

#if SDL_VERSION_ATLEAST(2, 0, 1)
#define USE_YUV_TEXTURES
#define HAS_YUV_TEXTURES (platform_sdl_version_at_least(2, 0, 1))
#else
#define HAS_YUV_TEXTURES 0
#endif

#if SDL_VERSION_ATLEAST(2, 0, 10)
#define USE_RENDERCOPYF
#define HAS_RENDERCOPYF (platform_sdl_version_at_least(2, 0, 10))
#endif

#if SDL_VERSION_ATLEAST(2, 0, 12)
#define USE_TEXTURE_SCALE_MODE
#define HAS_TEXTURE_SCALE_MODE (platform_sdl_version_at_least(2, 0, 12))
#else
#define HAS_TEXTURE_SCALE_MODE 0
#endif

#define MAX_UNPACKED_IMAGES 10

#define MAX_PACKED_IMAGE_SIZE 64000

#if defined(GAME_PLATFORM_ANDROID) || defined(GAME_PLATFORM_WEB)
// On the arm versions of android, for some reason, atlas textures that are too large will make the renderer fetch
// some images from the atlas with an off-by-one pixel, making things look terrible. Defining a smaller atlas texture
// prevents the problem, at the cost of performance due to the extra texture context switching.
#define MAX_TEXTURE_SIZE 2048
#else
#undef min
#undef max
#endif

#if !(defined(GAME_PLATFORM_ANDROID) || defined(GAME_PLATFORM_WEB) || defined(GAME_PLATFORM_MACOSX))
#include <gpupixel.h>
#endif

#ifdef __vita__
// On Vita, due to the small amount of VRAM, having textures that are too large will cause the game to eventually crash
// when changing climates, due to lack of contiguous memory space. Creating smaller atlases mitigates the issue
#define MAX_TEXTURE_SIZE 2048
#endif

int IMG_InitPNG();
SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src);
int IMG_SavePNG(SDL_Surface *surface, const char *file);

struct buffer_texture {
    SDL_Texture* texture = nullptr;
    int id;
    int width;
    int height;
    int tex_width;
    int tex_height;
};

struct renderer_data_t {
    SDL_Window *window;
    SDL_Renderer* renderer;
    SDL_Texture* render_texture;
    SDL_Texture *filter_texture = nullptr;
    std::vector<uint8_t> filter_source_pixels;
    std::vector<uint8_t> filter_output_pixels;
    SDL_GLContext main_gl_context;
    int is_software_renderer;

    struct {
        SDL_Texture* texture;
        int size;
        struct {
            int x, y;
        } hotspot;
    } cursors[CURSOR_MAX];

    struct {
        SDL_Texture* texture;
        color* buffer;
        image_t img;
    } custom_textures[CUSTOM_IMAGE_MAX];

    struct {
        int width;
        int height;
    } max_texture_size;

    svector<buffer_texture, 8> texture_buffers;
    int texture_buffer_id = 0;
    struct {
        int id;
        time_millis last_used;
        SDL_Texture* texture;
    } unpacked_images[MAX_UNPACKED_IMAGES];

    int supports_yuv_textures;
    bool is_opengl_context;

    float global_render_scale = 1.0f;
};

graphics_renderer_interface g_render;
renderer_data_t g_renderer_data;

bool graphics_renderer_interface::save_screen_buffer(painter &ctx, color* pixels, int x, int y, int width, int height, int row_width) {
    SDL_Rect rect = {x, y, width, height};
    return SDL_RenderReadPixels(ctx.renderer, &rect, SDL_PIXELFORMAT_ARGB8888, pixels, row_width * sizeof(color)) == 0;
}

void graphics_renderer_interface::draw_line(vec2i start, vec2i end, color color) {
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_RenderDrawLine(data.renderer, start.x, start.y, end.x, end.y);
}

void graphics_renderer_interface::draw_pixel(vec2i pixel, color color) {
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_RenderDrawPoint(data.renderer, pixel.x, pixel.y);
}
void graphics_renderer_interface::draw_rect(vec2i start, vec2i size, color color) {
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_Rect rect = {start.x, start.y, size.x + 1, size.y + 1};
    SDL_RenderDrawRect(data.renderer, &rect);
}

void graphics_renderer_interface::fill_rect(vec2i start, vec2i size, color color) {
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_Rect rect = {start.x, start.y, size.x + 1, size.y + 1};
    SDL_RenderFillRect(data.renderer, &rect);
}

void graphics_renderer_interface::clear_screen(void) {
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(data.renderer);
}

void graphics_renderer_interface::set_viewport(int x, int y, int width, int height) {
    auto &data = g_renderer_data;
    SDL_Rect viewport = {x, y, width, height};
    SDL_RenderSetViewport(data.renderer, &viewport);
}

void graphics_renderer_interface::reset_viewport(void) {
    auto &data = g_renderer_data;
    SDL_RenderSetViewport(data.renderer, NULL);
    SDL_RenderSetClipRect(data.renderer, NULL);
}

void graphics_renderer_interface::set_clip_rectangle(vec2i pos, int width, int height) {
    auto &data = g_renderer_data;
    SDL_Rect clip = {pos.x, pos.y, width, height};
    SDL_RenderSetClipRect(data.renderer, &clip);
}

bool graphics_renderer_interface::inside_clip_rectangle(vec2i pos) {
    auto &data = g_renderer_data;
    SDL_Rect clip;
    SDL_RenderGetClipRect(data.renderer, &clip);

    if (clip.w <= 0 || clip.h <= 0) {
        return true;
    }

    return (pos.x > clip.x && pos.y > clip.y && pos.x < (clip.x + clip.w) && pos.y < (clip.y + clip.h));
}

rect graphics_renderer_interface::clip_rectangle() {
    auto &data = g_renderer_data;
    SDL_Rect clip;
    SDL_RenderGetClipRect(data.renderer, &clip);

    return { {clip.x, clip.y}, {clip.x + clip.w, clip.y + clip.h} };
}

void graphics_renderer_interface::reset_clip_rectangle(void) {
    auto &data = g_renderer_data;
    SDL_RenderSetClipRect(data.renderer, NULL);
}

vec2i graphics_renderer_interface::get_max_image_size() {
    auto &data = g_renderer_data;
    return {data.max_texture_size.width, data.max_texture_size.height};
}

std::vector<video_mode> get_video_modes() {
    /* Get available fullscreen/hardware modes */
    int num = SDL_GetNumDisplayModes(0);

    std::set<video_mode> uniqueModes;
    uniqueModes.insert({1920, 1080});
    uniqueModes.insert({1600, 900});
    uniqueModes.insert({1440, 800});
    uniqueModes.insert({1280, 1024});
    uniqueModes.insert({1280, 800});
    uniqueModes.insert({1024, 768});
    uniqueModes.insert({800, 600});

    int maxWidth = 0;
    for (int i = 0; i < num; ++i) {
        SDL_DisplayMode mode;
        if (SDL_GetDisplayMode(0, i, &mode) == 0 && mode.w > 640) {
            maxWidth = std::max(mode.w, maxWidth);
            if (uniqueModes.count({mode.w, mode.h}) == 0) {
                uniqueModes.insert(video_mode(mode.w, mode.h));
            }
        }
    }

    std::vector<video_mode> modes;
    modes.resize(uniqueModes.size());
    std::copy(uniqueModes.begin(), uniqueModes.end(), modes.begin());
    std::sort(modes.begin(), modes.end());

    return modes;
}

static const SDL_BlendMode premult_alpha = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE,
                                                                      SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                                                                      SDL_BLENDOPERATION_ADD,
                                                                      SDL_BLENDFACTOR_ONE,
                                                                      SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                                                                      SDL_BLENDOPERATION_ADD);

void set_render_scale(painter &ctx, float scale) {
    ctx.global_render_scale = scale;
}

void graphics_renderer_interface::set_texture_scale_mode(SDL_Texture* texture, float scale_factor, bool force_linear) {
#ifdef USE_TEXTURE_SCALE_MODE
    if (HAS_TEXTURE_SCALE_MODE) {
        SDL_ScaleMode current_scale_mode;
        SDL_GetTextureScaleMode(texture, &current_scale_mode);
        SDL_ScaleMode desired_scale_mode = (force_linear || scale_factor < 1.0f ? SDL_ScaleModeLinear : SDL_ScaleModeNearest);
        //        SDL_ScaleMode desired_scale_mode = (scale_factor < 1.0f ? SDL_ScaleModeBest : SDL_ScaleModeNearest);
        if (current_scale_mode != desired_scale_mode) {
            SDL_SetTextureScaleMode(texture, desired_scale_mode);
        }
    }
#endif
}

unsigned int graphics_renderer_interface::premult_alpha() {
    return ::premult_alpha;
}

void graphics_renderer_interface::create_custom_texture(int type, int width, int height) {
    auto &data = g_renderer_data;
    if (data.custom_textures[type].texture) {
        SDL_DestroyTexture(data.custom_textures[type].texture);
        data.custom_textures[type].texture = 0;
    }
    memset(&data.custom_textures[type].img, 0, sizeof(data.custom_textures[type].img));
#ifndef __vita__
    if (data.custom_textures[type].buffer) {
        free(data.custom_textures[type].buffer);
        data.custom_textures[type].buffer = 0;
    }
#endif

    data.custom_textures[type].texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    data.custom_textures[type].img.width = width;
    data.custom_textures[type].img.height = height;
    //    data.custom_textures[type].img.atlas.id = (ATLAS_CUSTOM << IMAGE_ATLAS_BIT_OFFSET) | type;
    SDL_SetTextureBlendMode(data.custom_textures[type].texture, SDL_BLENDMODE_BLEND);
}
color* graphics_renderer_interface::get_custom_texture_buffer(int type, int* actual_texture_width) {
    auto &data = g_renderer_data;
    if (!data.custom_textures[type].texture) {
        return 0;
    }

#ifdef __vita__
    int pitch;
    SDL_LockTexture(data.custom_textures[type].texture, NULL, (void**)&data.custom_textures[type].buffer, &pitch);
    if (actual_texture_width) {
        *actual_texture_width = pitch / sizeof(color);
    }
    SDL_UnlockTexture(data.custom_textures[type].texture);
#else
    free(data.custom_textures[type].buffer);
    int width, height;
    Uint32 format;
    SDL_QueryTexture(data.custom_textures[type].texture, &format, NULL, &width, &height);
    if (format == SDL_PIXELFORMAT_YV12) {
        logs::error("Cannot get buffer to YUV texture");
        return 0;
    }
    data.custom_textures[type].buffer = (color*)malloc((size_t)width * height * sizeof(color));
    if (actual_texture_width) {
        *actual_texture_width = width;
    }
#endif
    return data.custom_textures[type].buffer;
}

void graphics_renderer_interface::release_custom_texture_buffer(int type) {
    auto &data = g_renderer_data;
#ifndef __vita__
    free(data.custom_textures[type].buffer);
    data.custom_textures[type].buffer = nullptr;
#endif
}

void graphics_renderer_interface::update_custom_texture(int type) {
    auto &data = g_renderer_data;
#ifndef __vita__
    if (!data.custom_textures[type].texture || !data.custom_textures[type].buffer) {
        return;
    }
    int width, height;
    SDL_QueryTexture(data.custom_textures[type].texture, NULL, NULL, &width, &height);
    SDL_UpdateTexture(data.custom_textures[type].texture, NULL, data.custom_textures[type].buffer, sizeof(color) * width);
#endif
}

SDL_Texture* graphics_renderer_interface::get_custom_texture(int type) {
    auto &data = g_renderer_data;
    return data.custom_textures[type].texture;
}

void graphics_renderer_interface::update_custom_texture_from(int type, const color *buffer,
    int x_offset, int y_offset, int width, int height)
{
    auto &data = g_renderer_data;
    if (game.paused || !data.custom_textures[type].texture) {
        return;
    }
    int texture_width, texture_height;
    SDL_QueryTexture(data.custom_textures[type].texture, nullptr, nullptr, &texture_width, &texture_height);
    if (x_offset + width > texture_width || y_offset + height > texture_height) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Partial texture copy goes out of bounds");
        return;
    }
#ifdef __vita__
    int pitch;
    SDL_LockTexture(data.custom_textures[type].texture, NULL, (void **) &data.custom_textures[type].buffer, &pitch);
    texture_width = pitch / sizeof(color_t);
    color_t *offset = &data.custom_textures[type].buffer[y_offset * texture_width + x_offset];
    for (int y = 0; y < height; y++) {
        memcpy(&offset[y * texture_width], &buffer[y * width], width * sizeof(color_t));
    }
    SDL_UnlockTexture(data.custom_textures[type].texture);
#else
    SDL_Rect rect = { x_offset, y_offset, width, height };
    SDL_UpdateTexture(data.custom_textures[type].texture, &rect, buffer, sizeof(color) * width);
#endif
}

void graphics_renderer_interface::update_custom_texture_yuv(int type, const uint8_t* y_data, int y_width, const uint8_t* cb_data, int cb_width, const uint8_t* cr_data, int cr_width) {
    auto &data = g_renderer_data;
#ifdef USE_YUV_TEXTURES
    if (!data.supports_yuv_textures || !data.custom_textures[type].texture) {
        return;
    }
    int width, height;
    Uint32 format;
    SDL_QueryTexture(data.custom_textures[type].texture, &format, NULL, &width, &height);
    if (format != SDL_PIXELFORMAT_YV12) {
        logs::error("Texture is not YUV format");
        return;
    }
    SDL_UpdateYUVTexture(
      data.custom_textures[type].texture, NULL, y_data, y_width, cb_data, cb_width, cr_data, cr_width);
#endif
}
static buffer_texture* get_saved_texture_info(int texture_id) {
    auto &data = g_renderer_data;
    if (!texture_id || data.texture_buffers.empty()) {
        return nullptr;
    }

    auto it = std::find_if(data.texture_buffers.begin(), data.texture_buffers.end(), [texture_id] (auto &i) { return i.id == texture_id; });
    
    return (it != data.texture_buffers.end() ? it : nullptr);
}

int graphics_renderer_interface::save_texture_from_screen(int texture_id, vec2i pos, int width, int height) {
    assert(width > 0 && height > 0);

    auto &data = g_renderer_data;
    SDL_Texture* former_target = SDL_GetRenderTarget(data.renderer);
    if (!former_target) {
        return 0;
    }

    buffer_texture texture_info;
    buffer_texture *exist_texture_info = get_saved_texture_info(texture_id);
    if (exist_texture_info) {
        int w, h;
        uint32_t format;
        SDL_QueryTexture(exist_texture_info->texture, &format, nullptr, &w, &h);
        if (w == width && h == height) {
            texture_info = *exist_texture_info;
        }
    } 

    if (!texture_info.texture) {
        texture_info.texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height);

        texture_info.id = ++data.texture_buffer_id;
        texture_info.width = width;
        texture_info.height = height;

        data.texture_buffers.push_back(texture_info);
    }

    if (!texture_info.texture) {
        return 0;
    }

#ifdef USE_TEXTURE_SCALE_MODE
    if (HAS_TEXTURE_SCALE_MODE) {
        SDL_SetTextureScaleMode(texture_info.texture, SDL_ScaleModeNearest);
    }
#endif // USE_TEXTURE_SCALE_MODE

    SDL_Rect former_viewport;
    SDL_RenderGetViewport(data.renderer, &former_viewport);
    SDL_Rect src_rect = {pos.x + former_viewport.x, pos.y + former_viewport.y, width, height};
    SDL_Rect dst_rect = {0, 0, width, height};
    SDL_SetRenderTarget(data.renderer, texture_info.texture);
    SDL_RenderCopy(data.renderer, former_target, &src_rect, &dst_rect);
    SDL_SetRenderTarget(data.renderer, former_target);
    SDL_RenderSetViewport(data.renderer, &former_viewport);

    return texture_info.id;
}

void graphics_renderer_interface::delete_saved_texture(int image_id) {
    auto &data = g_renderer_data;

    auto it = std::find_if(data.texture_buffers.begin(), data.texture_buffers.end(), [image_id] (auto &i) { return i.id == image_id; });
    if (it == data.texture_buffers.end()) {
        return;
    }

    SDL_DestroyTexture(it->texture);
    data.texture_buffers.erase(it);
}

void graphics_renderer_interface::draw_saved_texture_to_screen(int texture_id, int x, int y, int width, int height) {
    auto &data = g_renderer_data;
    buffer_texture* texture_info = get_saved_texture_info(texture_id);
    if (!texture_info) {
        return;
    }
    SDL_Rect src_coords = {0, 0, texture_info->width, texture_info->height};
    SDL_Rect dst_coords = {x, y, width, height};
    SDL_RenderCopy(data.renderer, texture_info->texture, &src_coords, &dst_coords);
}

void graphics_renderer_interface::clear_saved_texture(int texture_id, color clr) {
    auto &data = g_renderer_data;
    SDL_Texture *former_target = SDL_GetRenderTarget(data.renderer);
    if (!former_target) {
        return;
    }

    buffer_texture *texture_info = get_saved_texture_info(texture_id);
    if (!texture_info) {
        return;
    }

    SDL_Rect former_viewport;
    SDL_RenderGetViewport(data.renderer, &former_viewport);
    SDL_Rect dst_rect = { 0, 0, texture_info->width, texture_info->height };
    SDL_SetRenderTarget(data.renderer, texture_info->texture);
    SDL_SetRenderDrawColor(data.renderer,
                            (clr & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA,
                            (clr & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                            (clr & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                            (clr & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE);

    SDL_SetRenderTarget(data.renderer, former_target);
    SDL_RenderSetViewport(data.renderer, &former_viewport);
}

static void create_blend_texture(int type) {
    auto &data = g_renderer_data;
    SDL_Texture* texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 58, 30);
    if (!texture) {
        return;
    }
    const image_t* img = image_get(image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT));
    //    SDL_Texture *flat_tile = get_texture(img->atlas.bitflags);
    SDL_Texture* flat_tile = img->atlas.p_atlas->texture;
    SDL_Texture* former_target = SDL_GetRenderTarget(data.renderer);
    SDL_Rect former_viewport;
    SDL_Rect former_clip;
    SDL_RenderGetViewport(data.renderer, &former_viewport);
    SDL_RenderGetClipRect(data.renderer, &former_clip);

    SDL_SetRenderTarget(data.renderer, texture);
    SDL_Rect rect = {0, 0, 58, 30};
    SDL_RenderSetClipRect(data.renderer, &rect);
    SDL_RenderSetViewport(data.renderer, &rect);
    SDL_SetRenderDrawColor(data.renderer, 0xff, 0xff, 0xff, 0xff);
    color color = type == CUSTOM_IMAGE_RED_FOOTPRINT ? COLOR_MASK_RED : COLOR_MASK_GREEN;
    SDL_RenderClear(data.renderer);
    SDL_SetTextureBlendMode(flat_tile, SDL_BLENDMODE_BLEND);

    SDL_SetTextureColorMod(flat_tile,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE);
    SDL_SetTextureAlphaMod(flat_tile, 0xff);
    SDL_Rect src_coords = {img->atlas.offset.x, img->atlas.offset.y, img->width, img->height};
    SDL_RenderCopy(data.renderer, flat_tile, &src_coords, 0);

    SDL_SetRenderTarget(data.renderer, former_target);
    SDL_RenderSetViewport(data.renderer, &former_viewport);
    SDL_RenderSetClipRect(data.renderer, &former_clip);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);

    data.custom_textures[type].texture = texture;
    memset(&data.custom_textures[type].img, 0, sizeof(data.custom_textures[type].img));
    data.custom_textures[type].img.type = IMAGE_TYPE_ISOMETRIC;
    data.custom_textures[type].img.width = 58;
    data.custom_textures[type].img.height = 30;
    //    data.custom_textures[type].img.atlas.bitflags = (ATLAS_CUSTOM << IMAGE_ATLAS_BIT_OFFSET) | type;
}

static void set_texture_color_and_scale_mode(SDL_Texture *texture, color color, float scale) {
    if (!color) {
        color = COLOR_MASK_NONE;
    }

    SDL_SetTextureColorMod(texture,
        (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
        (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
        (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE);
    SDL_SetTextureAlphaMod(texture, (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);

#ifdef USE_TEXTURE_SCALE_MODE
    if (!HAS_TEXTURE_SCALE_MODE) {
        return;
    }
    SDL_ScaleMode current_scale_mode;
    SDL_GetTextureScaleMode(texture, &current_scale_mode);

    SDL_ScaleMode city_scale_mode = SDL_ScaleModeNearest;
    SDL_ScaleMode texture_scale_mode = scale != 1.0f ? SDL_ScaleModeLinear : SDL_ScaleModeNearest;
    //SDL_ScaleMode desired_scale_mode = data.city_scale == scale ? city_scale_mode : texture_scale_mode;
    //if (data.disable_linear_filter) {
    //    desired_scale_mode = SDL_ScaleModeNearest;
    //}
    //if (current_scale_mode != desired_scale_mode) {
        SDL_SetTextureScaleMode(texture, texture_scale_mode);
    //}
#endif
}

void graphics_renderer_interface::draw_texture_advanced(const image_t *img, float x, float y, color color, float scale_x, float scale_y, double angle, int disable_coord_scaling) {
    auto &data = g_renderer_data;
    if (!img->atlas.p_atlas) {
        return;
    }

    SDL_Texture *texture = img->atlas.p_atlas->texture;
    if (!texture) {
        return;
    }

    float scale = scale_x == scale_y ? scale_x : 0.0f;

    set_texture_color_and_scale_mode(texture, color, scale);

    x += img->animation.sprite_offset.x;
    y += img->animation.sprite_offset.y;

    int src_correction = 0; // scale == data.city_scale && data.should_correct_texture_offset ? 1 : 0;

    SDL_Rect src_coords = { img->atlas.offset.x + src_correction, img->atlas.offset.y + src_correction, img->width - src_correction, img->height - src_correction };

    // When zooming out, instead of drawing the grid image, we reduce the isometric textures' size,
    // which ends up simulating a grid without any performance penalty
    int grid_correction =  /*(img->is_isometric && config_get(CONFIG_UI_SHOW_GRID) && data.city_scale > 2.0f) ? 2 : */ -src_correction;

    float coord_scale_x = disable_coord_scaling ? 1.0f : scale_x;
    float coord_scale_y = disable_coord_scaling ? 1.0f : scale_y;

#ifdef USE_RENDERCOPYF
    if (HAS_RENDERCOPYF) {
        SDL_FRect dst_coords = {
            (x + grid_correction) / coord_scale_x,
            (y + grid_correction) / coord_scale_y,
            (img->width - grid_correction) / scale_x,
            (img->height - grid_correction) / scale_y
        };
        SDL_RenderCopyExF(data.renderer, texture, &src_coords, &dst_coords, angle, NULL, SDL_FLIP_NONE);
        return;
    }
#endif

    SDL_Rect dst_coords = {
        (int) round((x + grid_correction) / coord_scale_x),
        (int) round((y + grid_correction) / coord_scale_y),
        (int) round((img->width - grid_correction) / scale_x),
        (int) round((img->height - grid_correction) / scale_y)
    };
    SDL_RenderCopyEx(data.renderer, texture, &src_coords, &dst_coords, angle, NULL, SDL_FLIP_NONE);
}

static void draw_texture(const image_t *img, int x, int y, color color, float scale) {
    g_render.draw_texture_advanced(img, (float) x, (float) y, color, scale, scale, 0.0, 0);
}

void graphics_renderer_interface::draw_custom_texture(int type, int x, int y, float scale) {
    auto &data = g_renderer_data;
    if (type == CUSTOM_IMAGE_RED_FOOTPRINT || type == CUSTOM_IMAGE_GREEN_FOOTPRINT) {
        if (!data.custom_textures[type].texture) {
            create_blend_texture(type);
        }
    }
    //data.disable_linear_filter = disable_filtering;
    draw_texture(&data.custom_textures[type].img, x, y, 0, scale);
    //data.disable_linear_filter = 0;
}

int graphics_renderer_interface::has_custom_texture(int type) {
    auto &data = g_renderer_data;
    return data.custom_textures[type].texture != 0;
}

void load_unpacked_image(const image_t* img, const color* pixels) {
    auto &data = g_renderer_data;
    //    int unpacked_image_id = img->atlas.bitflags & IMAGE_ATLAS_BIT_MASK;
    int unpacked_image_id = 0;
    int first_empty = -1;
    int oldest_texture_index = 0;
    for (int i = 0; i < MAX_UNPACKED_IMAGES; i++) {
        if (data.unpacked_images[i].id == unpacked_image_id && data.unpacked_images[i].texture) {
            return;
        }
        if (first_empty == -1 && !data.unpacked_images[i].texture) {
            first_empty = i;
            break;
        }
        if (data.unpacked_images[oldest_texture_index].last_used < data.unpacked_images[i].last_used) {
            oldest_texture_index = i;
        }
    }
    int index = first_empty != -1 ? first_empty : oldest_texture_index;

    if (g_args.is_log_resources()) {
        logs::info("VFS: Loading unpacked image - size %dx%d", img->width, img->height);
    }
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)pixels, img->width, img->height, 32, img->width * sizeof(color),
                                                    COLOR_CHANNEL_RED,
                                                    COLOR_CHANNEL_GREEN,
                                                    COLOR_CHANNEL_BLUE,
                                                    COLOR_CHANNEL_ALPHA);
    if (!surface) {
        logs::error("Unable to create surface for texture. Reason: %s", SDL_GetError());
        return;
    }
    data.unpacked_images[index].last_used = time_get_millis();
    data.unpacked_images[index].id = unpacked_image_id;

    if (data.unpacked_images[index].texture) {
        SDL_DestroyTexture(data.unpacked_images[index].texture);
        data.unpacked_images[index].texture = 0;
    }
    data.unpacked_images[index].texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    while (!data.unpacked_images[index].texture) {
        int oldest_texture_index = -1;
        for (int i = 0; i < MAX_UNPACKED_IMAGES; i++) {
            if (data.unpacked_images[i].texture
                && (oldest_texture_index == -1
                    || data.unpacked_images[oldest_texture_index].last_used < data.unpacked_images[i].last_used)) {
                oldest_texture_index = i;
            }
        }
        if (oldest_texture_index == -1) {
            logs::error("Unable to create surface for texture - %s", SDL_GetError());
            SDL_FreeSurface(surface);
            return;
        }
        SDL_DestroyTexture(data.unpacked_images[oldest_texture_index].texture);
        data.unpacked_images[oldest_texture_index].texture = 0;
        data.unpacked_images[index].texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    }
    if (g_args.is_log_resources()) {
        logs::info("VFS: Unpacked image texture created successfully - %dx%d", img->width, img->height);
    }
    SDL_SetTextureBlendMode(data.unpacked_images[index].texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surface);
}

SDL_Texture* graphics_renderer_interface::create_texture_from_buffer(color* p_data, int width, int height) {
    auto &data = g_renderer_data;
    if (p_data == nullptr)
        return nullptr;
#ifdef __VITA__
    for (int i = 0; i < num_images; i++) {
        SDL_UnlockTexture(list[i]);
    }
#else
    // create RGB surface, and texture atlas from that surface
    // SDL_Log("Creating atlas texture with size %dx%d", width, height);
    if (g_args.is_log_resources()) {
        logs::info("VFS: Creating texture from buffer - size %dx%d", width, height);
    }
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)p_data, width, height, 32, width * sizeof(color), COLOR_CHANNEL_RED, COLOR_CHANNEL_GREEN, COLOR_CHANNEL_BLUE, COLOR_CHANNEL_ALPHA);
    if (!surface) {
        logs::error("Unable to create surface for texture. Reason: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    if (!texture) {
        logs::error("Unable to create texture. Reason: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return nullptr;
    }
    if (g_args.is_log_resources()) {
        logs::info("VFS: Texture created successfully - %dx%d", width, height);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surface);
#endif

    return texture;
}

bool graphics_renderer_interface::has_texture_scale_mode() {
    return HAS_TEXTURE_SCALE_MODE;
}

SDL_Texture* graphics_renderer_interface::create_texture_from_png_buffer(void *buffer, int size, vec2i &txsize) {
    auto &data = g_renderer_data;
    SDL_RWops *rw = SDL_RWFromMem(buffer, size);
    SDL_Surface* loadedSurface= IMG_LoadPNG_RW(rw);

    if (loadedSurface == nullptr) {
        return nullptr;
    }

    if(loadedSurface != NULL) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(data.renderer, loadedSurface);
        txsize.x = loadedSurface->w;
        txsize.y = loadedSurface->h;
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface( loadedSurface );
        return texture;
    }

    return nullptr;
}

bool graphics_renderer_interface::is_fullscreen_only() {
#if defined(GAME_PLATFORM_ANDROID) || defined(__SWITCH__) || defined(__vita__)
    return true;
#else
    return false;
#endif
}


float graphics_renderer_interface::scale() {
    return g_renderer_data.global_render_scale;
}

SDL_Renderer *graphics_renderer_interface::renderer() {
    return g_renderer_data.renderer;
}

SDL_Window *graphics_renderer_interface::window() {
    return g_renderer_data.window;
}

bool graphics_renderer_interface::save_texture_to_file(pcstr filename, SDL_Texture* tex, e_file_format file_format) {
    auto &data = g_renderer_data;
    SDL_Texture* ren_tex;
    SDL_Surface* surf;
    int st;
    int w;
    int h;
    uint32_t format;
    void* pixels;

    pixels = NULL;
    surf = NULL;
    ren_tex = NULL;

    /* Get information about texture we want to save */
    st = SDL_QueryTexture(tex, &format, NULL, &w, &h);
    if (st != 0) {
        logs::info("Failed querying texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    ren_tex = SDL_CreateTexture(data.renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!ren_tex) {
        logs::info("Failed creating render texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we
     * can access
     */
    st = SDL_SetRenderTarget(data.renderer, ren_tex);
    if (st != 0) {
        logs::info("Failed setting render target: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_SetRenderDrawColor(data.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(data.renderer);

    st = SDL_RenderCopy(data.renderer, tex, NULL, NULL);
    if (st != 0) {
        logs::info("Failed copying texture data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        logs::info("Failed allocating memory");
        goto cleanup;
    }

    st = SDL_RenderReadPixels(data.renderer, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
    if (st != 0) {
        logs::info("Failed reading pixel data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        logs::info("Failed creating new surface: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Save result to an image */
    switch (file_format) {
    case FILE_FORMAT_BMP:
        st = SDL_SaveBMP(surf, filename);
        break;

    case FILE_FORMAT_PNG:
        st = IMG_SavePNG(surf, filename);
        break;

    default:
        st = -1;
        break;
    }
    if (st != 0) {
        logs::info("Failed saving image: %s\n", SDL_GetError());
        goto cleanup; // technically redundant
    } else
        logs::info("Saved texture to %s\n", filename);

cleanup:
    SDL_FreeSurface(surf);
    free(pixels);
    SDL_DestroyTexture(ren_tex);
    if (st == -1)
        return false;
    else
        return true;
}

svector<xstring, 8> get_video_drivers(bool log) {
    SDL_RendererInfo info;
    svector<xstring, 8> drivers;
    for (int k = 0; k < SDL_GetNumRenderDrivers(); k++) {
        SDL_GetRenderDriverInfo(k, &info);
        if (log) {
            logs::info("SDLGraficEngine: available render %s", info.name);
        }
        drivers.push_back(info.name);
    }

    return drivers;
}

xstring get_video_driver() {
    auto &data = g_renderer_data;

    SDL_RendererInfo info;
    SDL_GetRendererInfo(data.renderer, &info);

    return info.name;
}

void platform_render_save_options() {
    auto &data = g_renderer_data;

    xstring driver = get_video_driver();
    data.is_opengl_context = (driver == "opengl");
}

void platform_render_make_current_context() {
    auto &data = g_renderer_data;

    if (data.is_opengl_context) {
        SDL_GL_MakeCurrent(data.window, data.main_gl_context);
    }
}

void platform_render_create_context() {
    auto &data = g_renderer_data;

    if (data.is_opengl_context) {
        data.main_gl_context = SDL_GL_CreateContext(data.window);
        SDL_GL_MakeCurrent(data.window, data.main_gl_context);
    }
}

int platform_renderer_init(SDL_Window* window, xstring renderer) {
    auto &data = g_renderer_data;

    auto drivers = get_video_drivers(true);
    data.window = window;

    auto driver_it = std::find(drivers.begin(), drivers.end(), renderer);
    int driver_index = driver_it != drivers.end() ? std::distance(drivers.begin(), driver_it) : -1;

    logs::info("Creating renderer");
    data.renderer = SDL_CreateRenderer(window, driver_index, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!data.renderer) {
        logs::info("Unable to create renderer, trying software renderer: %s", SDL_GetError());
        data.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (!data.renderer) {
            logs::error("Unable to create renderer: %s", SDL_GetError());
            return 0;
        }
    }

    platform_render_save_options();

    SDL_RendererInfo info;
    SDL_GetRendererInfo(data.renderer, &info);
    logs::info("Loaded renderer: %s", info.name);

    platform_render_create_context();

#ifdef USE_YUV_TEXTURES
    if (!data.supports_yuv_textures && HAS_YUV_TEXTURES) {
        for (unsigned int i = 0; i < info.num_texture_formats; i++) {
            if (info.texture_formats[i] == SDL_PIXELFORMAT_YV12) {
                data.supports_yuv_textures = 1;
                break;
            }
        }
    }
#endif

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    data.is_software_renderer = info.flags & SDL_RENDERER_SOFTWARE;
    if (data.is_software_renderer) {
        data.max_texture_size.width = 4096;
        data.max_texture_size.height = 4096;
    } else {
        data.max_texture_size.width = info.max_texture_width;
        data.max_texture_size.height = info.max_texture_height;
    }

#if defined(MAX_TEXTURE_SIZE)
    if (data.max_texture_size.width > MAX_TEXTURE_SIZE) {
        data.max_texture_size.width = MAX_TEXTURE_SIZE;
    }
    if (data.max_texture_size.height > MAX_TEXTURE_SIZE) {
        data.max_texture_size.height = MAX_TEXTURE_SIZE;
    }
#endif // MAX_TEXTURE_SIZE

    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0xff);
    IMG_InitPNG();

    platform_render_make_current_context();
    platform_render_init_filters();

    return 1;
}

static void destroy_render_texture(void) {
    auto &data = g_renderer_data;
    if (data.render_texture) {
        SDL_DestroyTexture(data.render_texture);
        data.render_texture = 0;
    }
}

int platform_renderer_create_render_texture(int width, int height) {
    auto &data = g_renderer_data;
    destroy_render_texture();

    if (data.filter_texture) {
        SDL_DestroyTexture(data.filter_texture);
        data.filter_texture = nullptr;
    }

#ifdef USE_TEXTURE_SCALE_MODE
    if (!HAS_TEXTURE_SCALE_MODE) {
#endif
        const char* scale_quality = "linear";
#ifndef __APPLE__
        // Scale using nearest neighbour when we scale a multiple of 100%: makes it look sharper.
        // But not on MacOS: users are used to the linear interpolation since that's what Apple also does.
        if (platform_screen_get_scale() % 100 == 0) {
            scale_quality = "nearest";
        }
#endif
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality);
#ifdef USE_TEXTURE_SCALE_MODE
    }
#endif

    SDL_SetRenderTarget(data.renderer, NULL);
    
    // Check if texture is larger than window to prevent automatic window resizing
    // SDL_RenderSetLogicalSize can automatically resize window if logical size > window size
    // So we only set logical size if texture fits within window or if in fullscreen/maximized mode
    int window_w = 0, window_h = 0;
    bool should_set_logical_size = true;
    if (data.window) {
        Uint32 flags = SDL_GetWindowFlags(data.window);
        bool is_fullscreen = (flags & SDL_WINDOW_FULLSCREEN) || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP);
        bool is_maximized = (flags & SDL_WINDOW_MAXIMIZED) != 0;
        
        if (!is_fullscreen && !is_maximized) {
            SDL_GetWindowSize(data.window, &window_w, &window_h);
            
            // If texture is larger than window, don't set logical size to prevent window resize
            // The texture will still be created, but logical size won't be set
            if (window_w > 0 && window_h > 0 && (width > window_w || height > window_h)) {
                should_set_logical_size = false;
            }
        }
    }
    
    // Only set logical size if it won't cause window resize
    // If texture is larger than window, don't set logical size to prevent automatic window resize
    if (should_set_logical_size) {
        SDL_RenderSetLogicalSize(data.renderer, width, height);
    }
    // Otherwise, leave logical size unchanged to avoid affecting window size

    data.render_texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height);

    if (data.render_texture) {
        logs::info("Render texture created (%d x %d)", width, height);
        SDL_SetRenderTarget(data.renderer, data.render_texture);
        SDL_SetRenderDrawBlendMode(data.renderer, SDL_BLENDMODE_BLEND);

#ifdef USE_TEXTURE_SCALE_MODE
        if (HAS_TEXTURE_SCALE_MODE) {
            SDL_ScaleMode scale_quality = SDL_ScaleModeLinear;
#ifndef __APPLE__
            if (platform_screen_get_scale() % 100 == 0) {
                scale_quality = SDL_ScaleModeNearest;
            }
#endif
            SDL_SetTextureScaleMode(data.render_texture, scale_quality);
        } else {
#endif
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
#ifdef USE_TEXTURE_SCALE_MODE
        }
#endif

        return 1;
    } else {
        logs::error("Unable to create render texture: %s", SDL_GetError());
        return 0;
    }
}

int platform_renderer_lost_render_texture() {
    auto &data = g_renderer_data;
    return !data.render_texture && data.renderer;
}

void platform_renderer_invalidate_target_textures() {
    auto &data = g_renderer_data;
    if (data.custom_textures[CUSTOM_IMAGE_RED_FOOTPRINT].texture) {
        SDL_DestroyTexture(data.custom_textures[CUSTOM_IMAGE_RED_FOOTPRINT].texture);
        data.custom_textures[CUSTOM_IMAGE_RED_FOOTPRINT].texture = 0;
        create_blend_texture(CUSTOM_IMAGE_RED_FOOTPRINT);
    }
    if (data.custom_textures[CUSTOM_IMAGE_GREEN_FOOTPRINT].texture) {
        SDL_DestroyTexture(data.custom_textures[CUSTOM_IMAGE_GREEN_FOOTPRINT].texture);
        data.custom_textures[CUSTOM_IMAGE_GREEN_FOOTPRINT].texture = 0;
        create_blend_texture(CUSTOM_IMAGE_GREEN_FOOTPRINT);
    }
}

#ifdef PLATFORM_USE_SOFTWARE_CURSOR
static void draw_software_mouse_cursor(void) {
    const mouse* mouse = mouse_get();
    if (!mouse->is_touch) {
        cursor_shape current = platform_cursor_get_current_shape();
        int size
          = calc_adjust_with_percentage(data.cursors[current].size, calc_percentage(100, platform_screen_get_scale()));
        SDL_Rect dst;
        dst.x = mouse->x - data.cursors[current].hotspot.x;
        dst.y = mouse->y - data.cursors[current].hotspot.y;
        dst.w = size;
        dst.h = size;
        SDL_RenderCopy(data.renderer, data.cursors[current].texture, NULL, &dst);
    }
}
#endif

void graphics_renderer_interface::apply_filter() {
    auto &data = g_renderer_data;

    if (!platform_render_support_filters()) {
        return;
    }

    if (!platform_render_any_filter_active()) {
        return;
    }

    OZZY_PROFILER_FUNCTION();
    float texw, texh;
    int pitch, w, h;
    uint32_t format;
    int render_texture_id;

    SDL_QueryTexture(data.render_texture, &format, NULL, &w, &h);
    if (!data.filter_texture) {
        data.filter_source_pixels.resize(w * h * SDL_BYTESPERPIXEL(format));
        data.filter_output_pixels.resize(w * h * SDL_BYTESPERPIXEL(format));

        data.filter_texture = SDL_CreateTexture(data.renderer, format, SDL_TEXTUREACCESS_STREAMING, w, h);
    }

    SDL_RenderFlush(data.renderer);
    int error = -1;
    {
        OZZY_PROFILER_SECTION(_, "Game/Run/Renderer/Render/Filter/ReadPixels");
        error = SDL_RenderReadPixels(data.renderer, NULL, format, data.filter_source_pixels.data(), w * SDL_BYTESPERPIXEL(format));
        
        SDL_RenderFlush(data.renderer);
        //error = 0;
    }

    if (!error) {
        SDL_GL_MakeCurrent(data.window, data.main_gl_context);
        platform_render_proceed_filter(w, h, format, data.filter_source_pixels, data.filter_output_pixels);

        // Copy filtered pixels back to filter_texture if it exists
        if (data.filter_texture && !data.filter_output_pixels.empty()) {
            void *dst_pixels = nullptr;
            int dst_pitch;
            if (SDL_LockTexture(data.filter_texture, nullptr, &dst_pixels, &dst_pitch) == 0) {
                int src_pitch = w * SDL_BYTESPERPIXEL(format);
                uint32_t expected_size = w * h * SDL_BYTESPERPIXEL(format);
                
                assert(dst_pitch == src_pitch);
                memcpy(dst_pixels, data.filter_output_pixels.data(), expected_size);
                SDL_UnlockTexture(data.filter_texture);
            }
        }
    }
}

void platform_renderer_render() {
    OZZY_PROFILER_FUNCTION();
    auto &data = g_renderer_data;

    g_render.apply_filter();

    SDL_SetRenderTarget(data.renderer, NULL);

    if (platform_render_any_filter_active()) {
        SDL_RenderCopy(data.renderer, data.filter_texture, NULL, NULL);
    } else {
        SDL_RenderCopy(data.renderer, data.render_texture, NULL, NULL);
    }

#ifdef PLATFORM_USE_SOFTWARE_CURSOR
        draw_software_mouse_cursor();
#endif

    SDL_RenderPresent(data.renderer);
    SDL_SetRenderTarget(data.renderer, data.render_texture);
}

void platform_renderer_generate_mouse_cursor_texture(int cursor_id, int size, const color* pixels, int hotspot_x, int hotspot_y) {
    auto &data = g_renderer_data;
    if (data.cursors[cursor_id].texture) {
        SDL_DestroyTexture(data.cursors[cursor_id].texture);
        SDL_memset(&data.cursors[cursor_id], 0, sizeof(data.cursors[cursor_id]));
    }
    data.cursors[cursor_id].texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, size, size);
    if (!data.cursors[cursor_id].texture) {
        return;
    }
    SDL_UpdateTexture(data.cursors[cursor_id].texture, NULL, pixels, size * sizeof(color));
    data.cursors[cursor_id].hotspot.x = hotspot_x;
    data.cursors[cursor_id].hotspot.y = hotspot_y;
    data.cursors[cursor_id].size = size;
    SDL_SetTextureBlendMode(data.cursors[cursor_id].texture, SDL_BLENDMODE_BLEND);
}

void platform_renderer_pause() {
    auto &data = g_renderer_data;
    SDL_SetRenderTarget(data.renderer, NULL);
}

void platform_renderer_resume() {
    auto &data = g_renderer_data;
    platform_renderer_create_render_texture(screen_width(), screen_height());
    SDL_SetRenderTarget(data.renderer, data.render_texture);
}

void platform_renderer_destroy(void) {
    auto &data = g_renderer_data;
    destroy_render_texture();
    if (data.renderer) {
        SDL_DestroyRenderer(data.renderer);
        data.renderer = 0;
    }
}

void platform_render_setup_options(xstring driver) {
    auto &data = g_renderer_data;
    if (data.is_opengl_context) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    }
}