#include "renderer.h"
#include "core/hvector.h"
#include "core/main_thread.h"

#include "core/log.h"
#include "core/profiler.h"
#include "graphics/screen.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "platform/screen.h"
#include "platform/cursor.h"
#include "graphics/image_groups.h"
#include "graphics/render_stats.h"
#include "graphics/residency_atlas.h"
#include "graphics/texture_alpha.h"
#include "graphics/view/view.h"
#include "game/game.h"
#include "input/cursor.h"

#include <SDL.h>
#include <SDL_video.h>

#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
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

struct render_clip_t {
    bool enabled;
    SDL_Rect rect;
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
        atlas_data_t atlas;
        image_t img;
    } custom_textures[CUSTOM_IMAGE_MAX];

    struct {
        int width;
        int height;
    } max_texture_size;

    svector<buffer_texture, 8> texture_buffers;
    hvector<SDL_Vertex, 1024, false> run_vertices;
    hvector<int, 1536, false> run_indices;
    hvector<render_material_t, 64, false> materials;
    hvector<render_clip_t, 16, false> clips;
    render_clip_t clip = {};
    int texture_buffer_id = 0;
    struct {
        int id;
        time_millis last_used;
        SDL_Texture* texture;
    } unpacked_images[MAX_UNPACKED_IMAGES];

    struct {
        bool active = false;
        SDL_Texture *former_target = nullptr;
        SDL_Rect former_viewport = {};
        render_clip_t former_clip = {};
    } saved_texture_target;

    int supports_yuv_textures;
    bool is_opengl_context;

    float global_render_scale = 1.0f;
};

graphics_renderer_interface g_render;
renderer_data_t g_renderer_data;

static void flush_sprites();

bool graphics_renderer_interface::save_screen_buffer(painter &ctx, color* pixels, int x, int y, int width, int height, int row_width) {
    flush_sprites();
    SDL_Rect rect = {x, y, width, height};
    return SDL_RenderReadPixels(ctx.renderer, &rect, SDL_PIXELFORMAT_ARGB8888, pixels, row_width * sizeof(color)) == 0;
}

void graphics_renderer_interface::draw_line(vec2i start, vec2i end, color color) {
    flush_sprites();
    render_stats::note_primitive();
    main_thread::check("graphics_renderer_interface::draw_line");
    auto &data = g_renderer_data;
    render_stats::note_break();
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_RenderDrawLine(data.renderer, start.x, start.y, end.x, end.y);
}

void graphics_renderer_interface::draw_pixel(vec2i pixel, color color) {
    flush_sprites();
    render_stats::note_primitive();
    main_thread::check("graphics_renderer_interface::draw_pixel");
    auto &data = g_renderer_data;
    render_stats::note_break();
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_RenderDrawPoint(data.renderer, pixel.x, pixel.y);
}
void graphics_renderer_interface::draw_rect(vec2i start, vec2i size, color color) {
    flush_sprites();
    render_stats::note_primitive();
    main_thread::check("graphics_renderer_interface::draw_rect");
    auto &data = g_renderer_data;
    render_stats::note_break();
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_Rect rect = {start.x, start.y, size.x + 1, size.y + 1};
    SDL_RenderDrawRect(data.renderer, &rect);
}

void graphics_renderer_interface::fill_rect(vec2i start, vec2i size, color color) {
    flush_sprites();
    render_stats::note_primitive();
    main_thread::check("graphics_renderer_interface::fill_rect");
    auto &data = g_renderer_data;
    render_stats::note_break();
    SDL_SetRenderDrawColor(data.renderer,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_Rect rect = {start.x, start.y, size.x + 1, size.y + 1};
    SDL_RenderFillRect(data.renderer, &rect);
}

static void apply_texture_scale_mode(SDL_Texture* texture, bool linear) {
#ifdef USE_TEXTURE_SCALE_MODE
    if (HAS_TEXTURE_SCALE_MODE) {
        SDL_ScaleMode current_scale_mode;
        SDL_GetTextureScaleMode(texture, &current_scale_mode);
        const SDL_ScaleMode desired_scale_mode = linear ? SDL_ScaleModeLinear : SDL_ScaleModeNearest;
        if (current_scale_mode != desired_scale_mode) {
            SDL_SetTextureScaleMode(texture, desired_scale_mode);
        }
    }
#endif
}

static std::vector<sprite_draw_t> g_sprite_list;

static void copy_sprite(const sprite_draw_t& sprite) {
    auto& data = g_renderer_data;
    const render_material_t& m = data.materials[sprite.material];
    apply_texture_scale_mode(m.texture, m.linear);
    SDL_SetTextureColorMod(m.texture, sprite.r, sprite.g, sprite.b);
    SDL_SetTextureAlphaMod(m.texture, sprite.a);
    SDL_SetTextureBlendMode(m.texture, (SDL_BlendMode)m.blend);
    const SDL_Rect src{sprite.src_x, sprite.src_y, sprite.src_w, sprite.src_h};
    const SDL_FRect dst{sprite.dst_x, sprite.dst_y, sprite.dst_w, sprite.dst_h};
    SDL_RenderCopyExF(data.renderer, m.texture, &src, &dst, sprite.angle, nullptr,
      sprite.mirrored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

static void apply_clip(const render_clip_t& clip) {
    if (!g_renderer_data.renderer) {
        return;
    }
    SDL_RenderSetClipRect(g_renderer_data.renderer, clip.enabled ? &clip.rect : nullptr);
}

static bool same_clip(const render_clip_t& a, const render_clip_t& b) {
    return a.enabled == b.enabled && (!a.enabled || SDL_memcmp(&a.rect, &b.rect, sizeof(SDL_Rect)) == 0);
}

static uint16_t current_clip_id() {
    auto& data = g_renderer_data;
    auto& clips = data.clips;
    if (!clips.empty() && same_clip(clips.back(), data.clip)) {
        return (uint16_t)(clips.size() - 1);
    }
    clips.push_back(data.clip);
    return (uint16_t)(clips.size() - 1);
}

static bool same_run(const sprite_draw_t& a, const sprite_draw_t& b) {
    return a.material == b.material && a.clip == b.clip && b.angle == 0.0;
}

static void draw_sprite_run(const sprite_draw_t* first, size_t count) {
    const render_material_t& m = g_renderer_data.materials[first->material];
    SDL_Texture* texture = m.texture;
    int tex_w = 0;
    int tex_h = 0;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h) != 0 || tex_w <= 0 || tex_h <= 0) {
        for (size_t i = 0; i < count; ++i) {
            copy_sprite(first[i]);
        }
        return;
    }

    apply_texture_scale_mode(texture, m.linear);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(texture, 255);
    SDL_SetTextureBlendMode(texture, (SDL_BlendMode)m.blend);

    auto& vertices = g_renderer_data.run_vertices;
    auto& indices = g_renderer_data.run_indices;
    vertices.resize(count * 4);
    indices.resize(count * 6);
    const float inv_w = 1.0f / (float)tex_w;
    const float inv_h = 1.0f / (float)tex_h;
    for (size_t i = 0; i < count; ++i) {
        const sprite_draw_t& s = first[i];
        float u0 = (float)s.src_x * inv_w;
        float u1 = (float)(s.src_x + s.src_w) * inv_w;
        const float v0 = (float)s.src_y * inv_h;
        const float v1 = (float)(s.src_y + s.src_h) * inv_h;
        if (s.mirrored) {
            std::swap(u0, u1);
        }
        const float x0 = s.dst_x;
        const float y0 = s.dst_y;
        const float x1 = s.dst_x + s.dst_w;
        const float y1 = s.dst_y + s.dst_h;
        const SDL_Color c{s.r, s.g, s.b, s.a};
        SDL_Vertex* v = &vertices[i * 4];
        v[0] = {{x0, y0}, c, {u0, v0}};
        v[1] = {{x1, y0}, c, {u1, v0}};
        v[2] = {{x1, y1}, c, {u1, v1}};
        v[3] = {{x0, y1}, c, {u0, v1}};
        const int base = (int)(i * 4);
        int* idx = &indices[i * 6];
        idx[0] = base;
        idx[1] = base + 1;
        idx[2] = base + 2;
        idx[3] = base;
        idx[4] = base + 2;
        idx[5] = base + 3;
    }
    SDL_RenderGeometry(g_renderer_data.renderer, texture, vertices.data(), (int)vertices.size(),
      indices.data(), (int)indices.size());
}

static void flush_sprites() {
    auto& data = g_renderer_data;
    if (g_sprite_list.empty()) {
        apply_clip(data.clip);
        return;
    }
    render_stats::phase_scope phase(render_stats::phase_device);
    render_stats::note_flush();
    const size_t n = g_sprite_list.size();
    size_t i = 0;
    while (i < n) {
        const sprite_draw_t& first = g_sprite_list[i];
        if (i == 0 || first.clip != g_sprite_list[i - 1].clip) {
            apply_clip(data.clips[first.clip]);
        }
        size_t end = i + 1;
        if (!g_renderer_data.is_software_renderer && first.angle == 0.0) {
            while (end < n && same_run(first, g_sprite_list[end])) {
                ++end;
            }
        }
        if (end - i > 1) {
            draw_sprite_run(&g_sprite_list[i], end - i);
        } else {
            copy_sprite(first);
        }
        i = end;
    }
    g_sprite_list.clear();
    data.materials.clear();
    data.clips.clear();
    apply_clip(data.clip);
}

uint16_t graphics_renderer_interface::material(SDL_Texture* texture, int blend, bool linear) {
    auto& materials = g_renderer_data.materials;
    for (size_t i = materials.size(); i-- > 0;) {
        const render_material_t& m = materials[i];
        if (m.texture == texture && m.blend == blend && m.linear == linear) {
            return (uint16_t)i;
        }
    }
    materials.push_back({texture, blend, linear});
    return (uint16_t)(materials.size() - 1);
}

void graphics_renderer_interface::draw_sprite(const sprite_draw_t& sprite) {
    main_thread::check("graphics_renderer_interface::draw_sprite");
    g_sprite_list.push_back(sprite);
    g_sprite_list.back().clip = current_clip_id();
}

void graphics_renderer_interface::destroy_texture(SDL_Texture* texture) {
    flush_sprites();
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* graphics_renderer_interface::create_grayscale_texture(SDL_Texture* tx, vec2i offset, vec2i size) {
    flush_sprites();
    auto& data = g_renderer_data;
    uint32_t format;
    int w, h;

    /* Get information about texture we want to save */
    int st = SDL_QueryTexture(tx, &format, NULL, &w, &h);
    if (st != 0) {
        return nullptr;
    }

    if (SDL_BYTESPERPIXEL(format) != 4) {
        return nullptr;
    }

    SDL_Texture* ren_tex = SDL_CreateTexture(data.renderer, format, SDL_TEXTUREACCESS_TARGET, size.x, size.y);
    if (!ren_tex) {
        return nullptr;
    }

    struct RenTexDeleter {
        SDL_Texture* tx;
        ~RenTexDeleter() { SDL_DestroyTexture(tx); }
    } _renTexDeleter{ren_tex};

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we
     * can access
     */
    SDL_Texture* old_target = SDL_GetRenderTarget(data.renderer);
    st = SDL_SetRenderTarget(data.renderer, ren_tex);
    if (st != 0) {
        return nullptr;
    }

    // Declared after the deleter, so it runs first: the target is restored before ren_tex dies.
    struct RenTargetRestore {
        SDL_Renderer* renderer;
        SDL_Texture* target;
        ~RenTargetRestore() { SDL_SetRenderTarget(renderer, target); }
    } _renTargetRestore{data.renderer, old_target};

    SDL_SetRenderDrawColor(data.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(data.renderer);

    SDL_Rect srcrect{offset.x, offset.y, size.x, size.y};
    st = SDL_RenderCopy(data.renderer, tx, &srcrect, NULL);
    if (st != 0) {
        return nullptr;
    }

    /* Create buffer to hold texture data and load it */
    std::vector<uint32_t> pixels(size.x * size.y);
    st = SDL_RenderReadPixels(data.renderer, NULL, format, pixels.data(), size.x * SDL_BYTESPERPIXEL(format));

    const SDL_PixelFormat* pxformat = SDL_AllocFormat(format);
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            Uint32* pixel = pixels.data() + y * size.x + x;
            Uint8 r, g, b, a;
            SDL_GetRGBA(*pixel, pxformat, &r, &g, &b, &a);
            Uint8 gray = static_cast<Uint8>(0.3 * r + 0.59 * g + 0.11 * b);
            *pixel = SDL_MapRGBA(pxformat, gray, gray, gray, a);
        }
    }
    SDL_FreeFormat((SDL_PixelFormat*)pxformat);

    /* Copy pixel data over to surface */
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.data(), size.x, size.y, SDL_BITSPERPIXEL(format),
      size.x * SDL_BYTESPERPIXEL(format), format);
    if (!surface) {
        return nullptr;
    }

    SDL_Texture* gray_tx_ptr = SDL_CreateTextureFromSurface(data.renderer, surface);
    SDL_FreeSurface(surface);
    return gray_tx_ptr;
}

void graphics_renderer_interface::clear_screen(void) {
    flush_sprites();
    main_thread::check("graphics_renderer_interface::clear_screen");
    auto &data = g_renderer_data;
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(data.renderer);
}

void graphics_renderer_interface::set_clip_rectangle(vec2i pos, int width, int height) {
    main_thread::check("graphics_renderer_interface::set_clip_rectangle");
    auto &data = g_renderer_data;
    render_stats::note_break();
    if (width >= 0 && height >= 0) {
        data.clip = {true, {pos.x, pos.y, width, height}};
    } else {
        data.clip = {};
    }
}

bool graphics_renderer_interface::inside_clip_rectangle(vec2i pos) {
    const SDL_Rect& clip = g_renderer_data.clip.rect;
    if (clip.w <= 0 || clip.h <= 0) {
        return true;
    }

    return (pos.x > clip.x && pos.y > clip.y && pos.x < (clip.x + clip.w) && pos.y < (clip.y + clip.h));
}

rect graphics_renderer_interface::clip_rectangle() {
    const SDL_Rect& clip = g_renderer_data.clip.rect;
    return { {clip.x, clip.y}, {clip.x + clip.w, clip.y + clip.h} };
}

void graphics_renderer_interface::reset_clip_rectangle(void) {
    main_thread::check("graphics_renderer_interface::reset_clip_rectangle");
    auto &data = g_renderer_data;
    render_stats::note_break();
    data.clip = {};
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
    flush_sprites();
    apply_texture_scale_mode(texture, force_linear || scale_factor < 1.0f);
}

unsigned int graphics_renderer_interface::premult_alpha() {
    return ::premult_alpha;
}

void graphics_renderer_interface::create_custom_texture(int type, int width, int height) {
    flush_sprites();
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
    data.custom_textures[type].atlas.texture = data.custom_textures[type].texture;
    data.custom_textures[type].atlas.width = width;
    data.custom_textures[type].atlas.height = height;
    data.custom_textures[type].img.width = width;
    data.custom_textures[type].img.height = height;
    data.custom_textures[type].img.atlas.offset = {0, 0};
    data.custom_textures[type].img.atlas.p_atlas = &data.custom_textures[type].atlas;
    //    data.custom_textures[type].img.atlas.id = (ATLAS_CUSTOM << IMAGE_ATLAS_BIT_OFFSET) | type;
    SDL_SetTextureBlendMode(data.custom_textures[type].texture, SDL_BLENDMODE_BLEND);
}
color* graphics_renderer_interface::get_custom_texture_buffer(int type, int* actual_texture_width) {
    flush_sprites();
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
    flush_sprites();
    auto &data = g_renderer_data;
#ifndef __vita__
    free(data.custom_textures[type].buffer);
    data.custom_textures[type].buffer = nullptr;
#endif
}

void graphics_renderer_interface::update_custom_texture(int type) {
    flush_sprites();
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
    flush_sprites();
    auto &data = g_renderer_data;
    return data.custom_textures[type].texture;
}

void graphics_renderer_interface::update_custom_texture_from(int type, const color *buffer,
    int x_offset, int y_offset, int width, int height)
{
    flush_sprites();
    auto &data = g_renderer_data;
    if (!data.custom_textures[type].texture) {
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
    flush_sprites();
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
    flush_sprites();
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

    // GLES keeps the screen clip across SetRenderTarget; a sidebar clip
    // (e.g. minimap) lies outside the small save texture and blanks the copy.
    // Prefer ensure_saved_texture + begin/end_saved_texture_target to draw into
    // the cache directly — FBO→texture copies are unreliable on Android GLES.
    SDL_Rect former_viewport;
    SDL_Rect former_clip;
    SDL_RenderGetViewport(data.renderer, &former_viewport);
    SDL_bool had_clip = SDL_RenderIsClipEnabled(data.renderer);
    if (had_clip) {
        SDL_RenderGetClipRect(data.renderer, &former_clip);
    }
    SDL_Rect src_rect = {pos.x + former_viewport.x, pos.y + former_viewport.y, width, height};
    SDL_Rect dst_rect = {0, 0, width, height};
    SDL_BlendMode former_blend = SDL_BLENDMODE_BLEND;
    SDL_GetTextureBlendMode(former_target, &former_blend);
    SDL_SetTextureBlendMode(former_target, SDL_BLENDMODE_NONE);
    SDL_RenderSetClipRect(data.renderer, nullptr);
    SDL_SetRenderTarget(data.renderer, texture_info.texture);
    SDL_RenderSetViewport(data.renderer, &dst_rect);
    SDL_RenderCopy(data.renderer, former_target, &src_rect, &dst_rect);
    SDL_SetRenderTarget(data.renderer, former_target);
    SDL_SetTextureBlendMode(former_target, former_blend);
    SDL_RenderSetViewport(data.renderer, &former_viewport);
    SDL_RenderSetClipRect(data.renderer, had_clip ? &former_clip : nullptr);

    return texture_info.id;
}

int graphics_renderer_interface::ensure_saved_texture(int texture_id, int width, int height) {
    flush_sprites();
    assert(width > 0 && height > 0);

    auto &data = g_renderer_data;
    buffer_texture texture_info;
    buffer_texture *exist_texture_info = get_saved_texture_info(texture_id);
    if (exist_texture_info) {
        int w, h;
        uint32_t format;
        SDL_QueryTexture(exist_texture_info->texture, &format, nullptr, &w, &h);
        if (w == width && h == height) {
            return exist_texture_info->id;
        }
        delete_saved_texture(exist_texture_info->id);
    }

    texture_info.texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture_info.texture) {
        return 0;
    }

    texture_info.id = ++data.texture_buffer_id;
    texture_info.width = width;
    texture_info.height = height;
    data.texture_buffers.push_back(texture_info);

#ifdef USE_TEXTURE_SCALE_MODE
    if (HAS_TEXTURE_SCALE_MODE) {
        SDL_SetTextureScaleMode(texture_info.texture, SDL_ScaleModeNearest);
    }
#endif
    SDL_SetTextureBlendMode(texture_info.texture, SDL_BLENDMODE_BLEND);
    return texture_info.id;
}

bool graphics_renderer_interface::begin_saved_texture_target(int texture_id) {
    flush_sprites();
    auto &data = g_renderer_data;
    render_stats::note_break();
    if (data.saved_texture_target.active) {
        return false;
    }

    buffer_texture *texture_info = get_saved_texture_info(texture_id);
    if (!texture_info || !texture_info->texture) {
        return false;
    }

    data.saved_texture_target.former_target = SDL_GetRenderTarget(data.renderer);
    SDL_RenderGetViewport(data.renderer, &data.saved_texture_target.former_viewport);
    data.saved_texture_target.former_clip = data.clip;

    SDL_Rect viewport = {0, 0, texture_info->width, texture_info->height};
    data.clip = {};
    apply_clip(data.clip);
    if (SDL_SetRenderTarget(data.renderer, texture_info->texture) != 0) {
        data.clip = data.saved_texture_target.former_clip;
        apply_clip(data.clip);
        return false;
    }
    SDL_RenderSetViewport(data.renderer, &viewport);
    data.saved_texture_target.active = true;
    return true;
}

void graphics_renderer_interface::end_saved_texture_target() {
    flush_sprites();
    auto &data = g_renderer_data;
    render_stats::note_break();
    if (!data.saved_texture_target.active) {
        return;
    }

    SDL_SetRenderTarget(data.renderer, data.saved_texture_target.former_target);
    SDL_RenderSetViewport(data.renderer, &data.saved_texture_target.former_viewport);
    data.clip = data.saved_texture_target.former_clip;
    apply_clip(data.clip);
    data.saved_texture_target = {};
}

void graphics_renderer_interface::delete_saved_texture(int image_id) {
    flush_sprites();
    auto &data = g_renderer_data;

    auto it = std::find_if(data.texture_buffers.begin(), data.texture_buffers.end(), [image_id] (auto &i) { return i.id == image_id; });
    if (it == data.texture_buffers.end()) {
        return;
    }

    SDL_DestroyTexture(it->texture);
    data.texture_buffers.erase(it);
}

void graphics_renderer_interface::draw_saved_texture_to_screen(int texture_id, int x, int y, int width, int height) {
    flush_sprites();
    auto &data = g_renderer_data;
    render_stats::note_break();
    buffer_texture* texture_info = get_saved_texture_info(texture_id);
    if (!texture_info) {
        return;
    }
    SDL_Rect src_coords = {0, 0, texture_info->width, texture_info->height};
    SDL_Rect dst_coords = {x, y, width, height};
    SDL_RenderCopy(data.renderer, texture_info->texture, &src_coords, &dst_coords);
}

void graphics_renderer_interface::clear_saved_texture(int texture_id, color clr) {
    flush_sprites();
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
    SDL_Rect former_clip;
    SDL_RenderGetViewport(data.renderer, &former_viewport);
    SDL_bool had_clip = SDL_RenderIsClipEnabled(data.renderer);
    if (had_clip) {
        SDL_RenderGetClipRect(data.renderer, &former_clip);
    }
    SDL_Rect dst_rect = {0, 0, texture_info->width, texture_info->height};
    SDL_RenderSetClipRect(data.renderer, nullptr);
    SDL_SetRenderTarget(data.renderer, texture_info->texture);
    SDL_RenderSetViewport(data.renderer, &dst_rect);
    SDL_SetRenderDrawColor(data.renderer,
                           (clr & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (clr & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (clr & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE,
                           (clr & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_RenderClear(data.renderer);

    SDL_SetRenderTarget(data.renderer, former_target);
    SDL_RenderSetViewport(data.renderer, &former_viewport);
    SDL_RenderSetClipRect(data.renderer, had_clip ? &former_clip : nullptr);
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
    data.custom_textures[type].atlas.texture = data.custom_textures[type].texture;
    data.custom_textures[type].atlas.width = 58;
    data.custom_textures[type].atlas.height = 30;
    memset(&data.custom_textures[type].img, 0, sizeof(data.custom_textures[type].img));
    data.custom_textures[type].img.type = IMAGE_TYPE_ISOMETRIC;
    data.custom_textures[type].img.width = 58;
    data.custom_textures[type].img.height = 30;
    data.custom_textures[type].img.atlas.offset = {0, 0};
    data.custom_textures[type].img.atlas.p_atlas = &data.custom_textures[type].atlas;
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
    flush_sprites();
    main_thread::check("graphics_renderer_interface::draw_texture_advanced");
    auto &data = g_renderer_data;
    render_stats::note_break();
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
    flush_sprites();
    main_thread::check("graphics_renderer_interface::draw_custom_texture");
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
    flush_sprites();
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
    flush_sprites();
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

    res_atlas::register_source(texture);

    return texture;
}

bool graphics_renderer_interface::has_texture_scale_mode() {
    return HAS_TEXTURE_SCALE_MODE;
}

SDL_Texture* graphics_renderer_interface::create_texture_from_png_buffer(void *buffer, int size, vec2i &txsize) {
    flush_sprites();
    auto &data = g_renderer_data;
    SDL_RWops *rw = SDL_RWFromMem(buffer, size);
    if (!rw) {
        return nullptr;
    }
    SDL_Surface* loadedSurface= IMG_LoadPNG_RW(rw);
    SDL_RWclose(rw);

    if (loadedSurface == nullptr) {
        return nullptr;
    }

    if(loadedSurface != NULL) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(data.renderer, loadedSurface);
        txsize.x = loadedSurface->w;
        txsize.y = loadedSurface->h;
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        texture_alpha::mark_straight(texture);
        SDL_FreeSurface( loadedSurface );
        return texture;
    }

    return nullptr;
}

bool graphics_renderer_interface::is_fullscreen_only() {
#if defined(GAME_PLATFORM_ANDROID) || defined(GAME_PLATFORM_IOS) || defined(__SWITCH__) || defined(__vita__)
    return true;
#else
    return false;
#endif
}


float graphics_renderer_interface::scale() {
    return g_renderer_data.global_render_scale;
}

SDL_Renderer *graphics_renderer_interface::renderer() {
    flush_sprites();
    return g_renderer_data.renderer;
}

SDL_Window *graphics_renderer_interface::window() {
    return g_renderer_data.window;
}

bool graphics_renderer_interface::save_texture_to_file(pcstr filename, SDL_Texture* tex, e_file_format file_format) {
    flush_sprites();
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

    if (data.is_opengl_context && data.main_gl_context) {
        SDL_GL_MakeCurrent(data.window, data.main_gl_context);
    }
}

void platform_render_create_context() {
    auto &data = g_renderer_data;

    if (data.is_opengl_context) {
        data.main_gl_context = SDL_GL_CreateContext(data.window);
        if (!data.main_gl_context) {
            logs::warn("Failed to create OpenGL context: %s", SDL_GetError());
            return;
        }
        if (SDL_GL_MakeCurrent(data.window, data.main_gl_context) != 0) {
            logs::warn("Failed to activate OpenGL context: %s", SDL_GetError());
        }
    }
}

enum e_render_backend {
    RENDER_BACKEND_SDL_DEFAULT,
    RENDER_BACKEND_DIRECT3D11,
    RENDER_BACKEND_OPENGL,
    RENDER_BACKEND_DIRECT3D,
    RENDER_BACKEND_SOFTWARE,
};

enum e_render_backend_limits {
    RENDER_BACKEND_MIN_TEXTURE_SIZE = 2048,
    RENDER_BACKEND_PROBE_TARGET_SIZE = 64,
};

static pcstr render_backend_name(e_render_backend backend) {
    switch (backend) {
    case RENDER_BACKEND_DIRECT3D11:
        return "direct3d11";
    case RENDER_BACKEND_OPENGL:
        return "opengl";
    case RENDER_BACKEND_DIRECT3D:
        return "direct3d";
    case RENDER_BACKEND_SOFTWARE:
        return "software";
    case RENDER_BACKEND_SDL_DEFAULT:
        break;
    }
    return "";
}

// Tried in order after the user's choice. On Windows opengl comes first because shader effects start there;
// direct3d11 keeps its speed when sprites switch textures (atlas off), where opengl slows down; SDL's own pick
// there is direct3d (D3D9). Elsewhere SDL's pick is kept.
static const e_render_backend k_render_backend_chain[] = {
#if defined(GAME_PLATFORM_WIN)
  RENDER_BACKEND_OPENGL,
  RENDER_BACKEND_DIRECT3D11,
  RENDER_BACKEND_DIRECT3D,
#else
  RENDER_BACKEND_SDL_DEFAULT,
#endif
  RENDER_BACKEND_SOFTWARE,
};

svector<xstring, 8> render_backend_order(const xstring& requested, const svector<xstring, 8>& available) {
    svector<xstring, 8> order;
    auto add = [&](const xstring& name) {
        const bool listed = name.empty() || std::find(available.begin(), available.end(), name) != available.end();
        if (listed && std::find(order.begin(), order.end(), name) == order.end()) {
            order.push_back(name);
        }
    };

    if (!requested.empty()) {
        add(requested);
    }
    for (const e_render_backend backend : k_render_backend_chain) {
        add(render_backend_name(backend));
    }
    return order;
}

xstring platform_render_preferred_backend(const xstring& requested) {
    const auto order = render_backend_order(requested, get_video_drivers(false));
    return order.empty() ? xstring() : order.front();
}

static bool renderer_usable(SDL_Renderer* renderer, bstring256& problem) {
    SDL_RendererInfo info;
    if (SDL_GetRendererInfo(renderer, &info) != 0) {
        problem = SDL_GetError();
        return false;
    }
    if (!(info.flags & SDL_RENDERER_TARGETTEXTURE)) {
        problem = "no render target support";
        return false;
    }
    const bool limited = info.max_texture_width > 0 && info.max_texture_height > 0;
    if (limited
        && (info.max_texture_width < RENDER_BACKEND_MIN_TEXTURE_SIZE
            || info.max_texture_height < RENDER_BACKEND_MIN_TEXTURE_SIZE)) {
        problem.printf("max texture size %dx%d", info.max_texture_width, info.max_texture_height);
        return false;
    }

    SDL_Texture* probe = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
      RENDER_BACKEND_PROBE_TARGET_SIZE, RENDER_BACKEND_PROBE_TARGET_SIZE);
    const bool ok = probe && SDL_SetRenderTarget(renderer, probe) == 0;
    if (!ok) {
        problem.printf("render target: %s", SDL_GetError());
    }
    SDL_SetRenderTarget(renderer, nullptr);
    if (probe) {
        SDL_DestroyTexture(probe);
    }
    return ok;
}

static SDL_Renderer* create_renderer(SDL_Window* window, const xstring& requested, const svector<xstring, 8>& drivers) {
    bstring512 failed;
    if (!requested.empty() && std::find(drivers.begin(), drivers.end(), requested) == drivers.end()) {
        logs::warn("Renderer %s failed: not available in this build", requested.c_str());
        failed = requested.c_str();
    }

    // SDL drops command batching for a renderer picked by index, so every copy would flush on its own (about twice
    // the frame time on a full city). Native GPU work (filters) calls SDL_RenderFlush first.
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

    for (const xstring& name : render_backend_order(requested, drivers)) {
        const auto it = std::find(drivers.begin(), drivers.end(), name);
        const int index = it != drivers.end() ? (int)std::distance(drivers.begin(), it) : -1;
        const bool software = (name == render_backend_name(RENDER_BACKEND_SOFTWARE));
        const pcstr label = name.empty() ? "(SDL default)" : name.c_str();

        platform_render_setup_options(name);
        const Uint32 vsync = g_args.is_integral_tests() ? 0 : SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer* renderer
          = SDL_CreateRenderer(window, index, vsync | (software ? SDL_RENDERER_SOFTWARE : SDL_RENDERER_ACCELERATED));
        bstring256 problem;
        if (!renderer) {
            problem = SDL_GetError();
        } else if (!renderer_usable(renderer, problem)) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        if (!renderer) {
            logs::warn("Renderer %s failed: %s", label, problem.c_str());
            if (!failed.empty()) {
                failed.append(", ");
            }
            failed.append(label);
            continue;
        }

        SDL_RendererInfo info;
        SDL_GetRendererInfo(renderer, &info);
        if (!failed.empty()) {
            logs::info("Renderer: %s (fallback after %s failed)", info.name, failed.c_str());
        } else {
            logs::info("Renderer: %s (%s)", info.name, requested.empty() ? "default" : "user choice");
        }
        return renderer;
    }
    return nullptr;
}

int platform_renderer_init(SDL_Window* window, xstring renderer) {
    auto &data = g_renderer_data;

    auto drivers = get_video_drivers(true);
    data.window = window;

    data.renderer = create_renderer(window, renderer, drivers);
    if (!data.renderer) {
        logs::error("Unable to create renderer: %s", SDL_GetError());
        return 0;
    }

    platform_render_save_options();

    SDL_RendererInfo info;
    SDL_GetRendererInfo(data.renderer, &info);

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
    flush_sprites();
    auto &data = g_renderer_data;
    destroy_render_texture();

    res_atlas::invalidate();

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
        if (g_platform_screen.get_scale() % 100 == 0) {
            scale_quality = "nearest";
        }
#endif
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality);
#ifdef USE_TEXTURE_SCALE_MODE
    }
#endif

    SDL_SetRenderTarget(data.renderer, NULL);
    SDL_RenderSetLogicalSize(data.renderer, width, height);

    data.render_texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height);

    if (data.render_texture) {
        logs::info("Render texture created (%d x %d)", width, height);
        SDL_SetRenderTarget(data.renderer, data.render_texture);
        data.clip = {};
        SDL_SetRenderDrawBlendMode(data.renderer, SDL_BLENDMODE_BLEND);

#ifdef USE_TEXTURE_SCALE_MODE
        if (HAS_TEXTURE_SCALE_MODE) {
            SDL_ScaleMode scale_quality = SDL_ScaleModeLinear;
#ifndef __APPLE__
            if (g_platform_screen.get_scale() % 100 == 0) {
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

void platform_renderer_invalidate_all_textures() {
    flush_sprites();
    auto &data = g_renderer_data;

    // Destroy texture buffers (TARGET textures)
    for (auto &tb : data.texture_buffers) {
        if (tb.texture) {
            SDL_DestroyTexture(tb.texture);
        }
    }
    data.texture_buffers.clear();

    // Destroy custom textures (e.g. blend textures which are TARGET)
    for (int i = 0; i < CUSTOM_IMAGE_MAX; i++) {
        if (data.custom_textures[i].texture) {
            SDL_DestroyTexture(data.custom_textures[i].texture);
            data.custom_textures[i].texture = nullptr;
        }
    }

    // Destroy unpacked images (STATIC textures, might be invalid)
    for (int i = 0; i < MAX_UNPACKED_IMAGES; i++) {
        if (data.unpacked_images[i].texture) {
            SDL_DestroyTexture(data.unpacked_images[i].texture);
            data.unpacked_images[i].texture = nullptr;
        }
    }

    // Recreate the main render texture
    platform_renderer_create_render_texture(screen_width(), screen_height());

    // Invalidate residency atlas so it repacks onto a fresh GPU texture
    res_atlas::invalidate();

    // Recreate imagepak static textures from buffers
    image_recreate_all_textures();
}


void platform_renderer_invalidate_target_textures() {
    flush_sprites();
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
        cursor_shape current = xvalue<platform_cursor_t>::ref().current();
        int size
          = calc_adjust_with_percentage(data.cursors[current].size, calc_percentage(100, g_platform_screen.get_scale()));
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
    flush_sprites();
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
        if (data.main_gl_context) {
            SDL_GL_MakeCurrent(data.window, data.main_gl_context);
        }
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
    flush_sprites();
    OZZY_PROFILER_FUNCTION();
    auto &data = g_renderer_data;

    g_render.apply_filter();

    SDL_SetRenderTarget(data.renderer, NULL);
    // Clear letterbox/pillarbox regions left by SDL_RenderSetLogicalSize (otherwise a 1px
    // strip can show as uninitialized garbage, especially at the bottom edge).
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(data.renderer);

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
    data.clip = {};
}

void platform_renderer_generate_mouse_cursor_texture(int cursor_id, int size, const color* pixels, int hotspot_x, int hotspot_y) {
    flush_sprites();
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
    flush_sprites();
    auto &data = g_renderer_data;
    SDL_SetRenderTarget(data.renderer, NULL);
}

void platform_renderer_resume() {
    auto &data = g_renderer_data;
    platform_renderer_create_render_texture(screen_width(), screen_height());
    SDL_SetRenderTarget(data.renderer, data.render_texture);
    data.clip = {};
}

void platform_renderer_destroy(void) {
    flush_sprites();
    auto &data = g_renderer_data;
    destroy_render_texture();
    platform_render_shutdown_filters();
    if (data.renderer) {
        SDL_DestroyRenderer(data.renderer);
        data.renderer = 0;
    }
}

void platform_render_setup_options(xstring driver) {
    if (driver != "opengl") {
        return;
    }

    // GPUPixel filter shaders use GLSL 1.x (varying, gl_FragColor, texture2D).
    // OpenGL 3.3 core profile rejects those constructs; compatibility keeps them valid.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
}
