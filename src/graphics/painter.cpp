#include "graphics/painter.h"

#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "platform/renderer.h"

#include <string>
#include <unordered_map>

#include <SDL.h>

std::unordered_map<uint64_t, SDL_Texture *> grayscaled_txs;

void painter::draw(SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, color color, float scale_x, float scale_y,
                   double angle, ImgFlags flags, const bool force_linear) {
    if (!(flags & ImgFlag_Grayscale)) {
        draw_impl(texture, pos, offset, size, color, scale_x, scale_y, angle, flags, force_linear);
    } else {
        draw_grayscale(texture, pos, offset, size, scale_x, scale_y, angle, !!(flags & ImgFlag_Alpha), force_linear);
    }
}

void painter::draw_image_part(const image_t *img, int offset, vec2i pos, color color, float scale, ImgFlags flags) {
    if (img == nullptr) {
        return;
    }

    vec2i atlas_offset = img->atlas.offset;
    vec2i size = { img->width, (img->height - offset) / 2 + offset };
    draw(img->atlas.p_atlas->texture, pos, atlas_offset, size, color, scale, scale, 0, flags);
}

void painter::draw_image(const image_t *img, vec2i pos, color color, float scale, ImgFlags flags) {
    if (!img) {
        return;
    }

    if (!img->atlas.p_atlas) {
        return;
    }

    vec2i offset = img->atlas.offset;
    vec2i size = { img->width, img->height };
    if (offset.x >= 0 && offset.y >= 0) {
        draw(img->atlas.p_atlas->texture, pos, offset, size, color, scale, scale, 0, flags);
    }
}

void painter::draw_image_grayscale(const image_t *img, vec2i pos, float scale, ImgFlags flags) {
    if (!img) {
        return;
    }

    if (!img->atlas.p_atlas) {
        return;
    }

    vec2i offset = img->atlas.offset;
    vec2i size = { img->width, img->height };
    if (offset.x >= 0 && offset.y >= 0) {
        draw(img->atlas.p_atlas->texture, pos, offset, size, scale, scale, 0, flags);
    }
}

const image_t *painter::img_generic(int image_id, vec2i pos, color color_mask, float scale) {
    const image_t *img = image_get(image_id);
    draw_image(img, pos, color_mask, scale);
    return img;
}

const image_t *painter::img_generic(int pak, int image_id, vec2i p, color color_mask, float scale) {
    const image_t *img = image_get(pak, image_id);
    draw_image(img, p, color_mask, scale);
    return img;
}

const image_t *painter::img_generic(const image_desc &imgd, vec2i p, color color_mask, float scale) {
    const image_t *img = image_get(imgd);
    draw_image(img, p, color_mask, scale);
    return img;
}

const image_t *painter::img_generic(int image_id, vec2i p, color color_mask, float scale, ImgFlags flags) {
    const image_t *img = image_get(image_id);
    vec2i offset{ 0, 0 };
    if (!!(flags & ImgFlag_InternalOffset)) {
        offset = img->animation.sprite_offset;
    }

    draw_image(img, p - offset, color_mask, scale, flags);
    return img;
}

const image_t *painter::img_sprite(int image_id, vec2i p, color color_mask, float scale, ImgFlags flags) {
    const image_t *img = image_get(image_id);
    bool mirrored = (img->offset_mirror != 0);

    if (mirrored) {
        img = img->mirrored_img;
        p.x -= (img->width - img->animation.sprite_offset.x);
    } else {
        p.x -= img->animation.sprite_offset.x;
    }

    flags |= (mirrored ? ImgFlag_Mirrored : ImgFlag_None);

    p.y -= img->animation.sprite_offset.y;
    draw_image(img, p, color_mask, scale, flags);

    return img;
}

const image_t *painter::img_ornament(int image_id, int base_id, int x, int y, color color_mask, float scale) {
    const image_t *img = image_get(image_id);
    const image_t *base = image_get(base_id);
    int ydiff = HALF_TILE_HEIGHT_PIXELS * (base->isometric_size() + 1);
    x += base->animation.sprite_offset.x;
    y += base->animation.sprite_offset.y - base->height + ydiff;
    //    y += base->animation.sprite_y_offset - img->isometric_ydiff();
    draw_image(img, vec2i{ x, y }, color_mask, scale);
    return img;
}

const image_t *painter::img_from_below(int image_id, int x, int y, color color_mask, float scale) {
    const image_t *img = image_get(image_id);
    draw_image(img, vec2i{ x, y - img->height }, color_mask, scale);
    return img;
}

const image_t *painter::img_letter(const image_t *img, e_font font, int letter_id, int x, int y, color color_mask, float scale) {
    if (!color_mask) {
        color_mask = base_color_for_font(font);
    }

    if (font == FONT_SMALL_SHADED) {
        draw_image(img, vec2i{ x + 1, y + 1 }, COLOR_BLACK, scale);
    }

    draw_image(img, vec2i{ x, y }, color_mask, scale);
    return img;
}

const image_t *painter::img_generic(const image_t *img, vec2i p, color color_mask, float scale, ImgFlags flags) {
    vec2i offset{ 0, 0 };
    if (!!(flags & ImgFlag_InternalOffset)) {
        offset = img->animation.sprite_offset;
    }

    draw_image(img, p - offset, color_mask, scale, flags);
    return img;
}

const image_t* painter::img_isometric(int image_id, vec2i pixel, color color_mask, float scale) {
    return img_generic(image_id, pixel, color_mask, scale);
}

const image_t *painter::isometric_from_drawtile(int image_id, vec2i pos, color color_mask, ImgFlags flags) {
    const image_t *img = image_get(image_id);
    if (!img) {
        return nullptr;
    }
    //    if ((img->atlas.id >> IMAGE_ATLAS_BIT_OFFSET) == ATLAS_UNPACKED_EXTRA_ASSET) {
    //        assets_load_unpacked_asset(image_id);
    //    }
    pos.y += HALF_TILE_HEIGHT_PIXELS * (img->isometric_size() + 1) - img->height;

    draw_image(img, pos, color_mask, 1.f, flags);
    return img;
}

const image_t *painter::isometric_from_drawtile_top(int image_id, vec2i pos, color color_mask, ImgFlags flags) {
    const image_t *img = image_get(image_id);
    if (!img) {
        return nullptr;
    }
    const image_t *img_top = img->isometric_top;
    if (!img_top) {
        return nullptr;
    }
    pos.y += HALF_TILE_HEIGHT_PIXELS * (img_top->isometric_size() + 1) - img_top->height;

    draw_image(img_top, pos, color_mask, 1.f, flags);
    return img_top;
}

const image_t *painter::img_isometric(int image_id, vec2i p, color color_mask, float scale, ImgFlags flags) {
    isometric_from_drawtile(image_id, p, color_mask, flags);
    return isometric_from_drawtile_top(image_id, p, color_mask, flags);
}

void painter::draw_impl(SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, color color, float scale_x,
                        float scale_y, double angle, ImgFlags flags, const bool force_linear) {
    if (texture == nullptr) {
        return;
    }

    if (!color) {
        color = COLOR_MASK_NONE;
    }

    const float x_scale_factor = scale_x * global_render_scale;
    const float y_scale_factor = scale_y * global_render_scale;
    const float overall_scale_factor = scale_x == scale_y ? x_scale_factor : this->global_render_scale;
    bool DOWNSCALED_CITY = false;
    if (this->global_render_scale < 1.0f) {
        DOWNSCALED_CITY = true;
    }

    g_render.set_texture_scale_mode(texture, overall_scale_factor, force_linear);

    SDL_SetTextureColorMod(texture,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE);
    SDL_SetTextureAlphaMod(texture, (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);

    const bool alpha = !!(flags & ImgFlag_Alpha);
    SDL_SetTextureBlendMode(texture, alpha ? SDL_BLENDMODE_BLEND : (SDL_BlendMode)g_render.premult_alpha());

    // uncomment here if you want save something from atlases
    int k = 0;
    if (k == 1) {
        char filename[32] = {0};
        static int index = 0;
        sprintf(filename, "%u_img.bmp", index);
        g_render.save_texture_to_file(filename, texture);
    }

    float texture_coord_correction = 0;
    SDL_Rect texture_coords = {static_cast<int>(offset.x + texture_coord_correction),
                               static_cast<int>(offset.y + texture_coord_correction),
                               static_cast<int>(size.x - texture_coord_correction),
                               static_cast<int>(size.y - texture_coord_correction)};

    SDL_FRect screen_coords;
    if (DOWNSCALED_CITY) {
        // hack to prevent ugly dark borders around sprites -- yes, there's DEFINITELY a better way to do this,
        // but I can't be arsed to find it. I tried, I gave up.
        screen_coords = {static_cast<float>(pos.x * this->global_render_scale - 0.25),
                         static_cast<float>(pos.y * this->global_render_scale - 0.25),
                         static_cast<float>(size.x * x_scale_factor + 0.5),
                         static_cast<float>(size.y * y_scale_factor + 0.5)};
    } else {
        screen_coords = {pos.x * this->global_render_scale,
                         pos.y * this->global_render_scale,
                         size.x * x_scale_factor,
                         size.y * y_scale_factor};
    }

    if (!!(flags & ImgFlag_Mirrored)) {
        SDL_RenderCopyExF(this->renderer, texture, &texture_coords, &screen_coords, angle, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyExF(this->renderer, texture, &texture_coords, &screen_coords, angle, nullptr, SDL_FLIP_NONE);
    }
}

SDL_Texture* painter::convertToGrayscale(SDL_Texture *tx, vec2i offset, vec2i size) {
    if (!tx) {
        return nullptr;
    }

    uint64_t hash = ((uint64_t)tx & 0xffffffff) | ((uint64_t)offset.x << 32) | ((uint64_t)offset.y << 48);

    auto it = grayscaled_txs.find(hash);
    if (it != grayscaled_txs.end()) {
        return it->second;
    }

    auto gray_tx = grayscaled_txs.insert({ hash , nullptr });

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

    SDL_Texture* ren_tex = SDL_CreateTexture(this->renderer, format, SDL_TEXTUREACCESS_TARGET, size.x, size.y);
    if (!ren_tex) {
        return nullptr;
    }

    struct RenTexDeleter {
        SDL_Texture *tx;
        ~RenTexDeleter() { SDL_DestroyTexture(tx); }
    } _renTexDeleter{ ren_tex };

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we
     * can access
     */
    SDL_Texture *old_target = SDL_GetRenderTarget(this->renderer);
    st = SDL_SetRenderTarget(this->renderer, ren_tex);
    if (st != 0) {
        return nullptr;
    }

    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(this->renderer);

    SDL_Rect srcrect{ offset.x, offset.y, size.x, size.y };
    st = SDL_RenderCopy(this->renderer, tx, &srcrect, NULL);
    if (st != 0) {
        return nullptr;
    }

    /* Create buffer to hold texture data and load it */
    std::vector<uint32_t> pixels(size.x * size.y);
    st = SDL_RenderReadPixels(this->renderer, NULL, format, pixels.data(), size.x * SDL_BYTESPERPIXEL(format));

    const SDL_PixelFormat *pxformat = SDL_AllocFormat(format);
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            Uint32 *pixel = pixels.data() + y * size.x + x;
            Uint8 r, g, b, a;
            SDL_GetRGBA(*pixel, pxformat, &r, &g, &b, &a);
            Uint8 gray = static_cast<Uint8>(0.3 * r + 0.59 * g + 0.11 * b);
            *pixel = SDL_MapRGBA(pxformat, gray, gray, gray, a);
        }
    }

    /* Copy pixel data over to surface */
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.data(), size.x, size.y, SDL_BITSPERPIXEL(format),
                                                              size.x * SDL_BYTESPERPIXEL(format), format);
    if (!surface) {
        return nullptr;
    }

    SDL_Texture *gray_tx_ptr = SDL_CreateTextureFromSurface(this->renderer, surface);

    gray_tx.first->second = gray_tx_ptr;
    SDL_FreeSurface(surface);

    SDL_SetRenderTarget(this->renderer, old_target);

    return gray_tx_ptr;
}

auto painter::draw_grayscale(SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, float scale_x, float scale_y,
                             double angle, ImgFlags flags, bool force_linear) -> void {
    if (texture == nullptr) {
        return;
    }

    SDL_Texture *grtx = convertToGrayscale(texture, offset, size);
    if (!grtx) { 
        return;
    }

    draw_impl(grtx, pos, vec2i{ 0, 0 }, size, COLOR_WHITE, scale_x, scale_y, angle, flags, force_linear);
}

void painter::draw(const sprite &spr, vec2i pos, color color_mask, float scale_x, float scale_y, double angle, ImgFlags flags, const bool force_linear) {
    if (spr.img == nullptr) {
        return;
    }

    vec2i offset = spr.img->atlas.offset;
    vec2i size = spr.img->size();
    draw(spr.img->atlas.p_atlas->texture, pos, offset, size, color_mask, scale_x, scale_y, angle, flags, force_linear);
}

sprite_resource_icon::sprite_resource_icon(e_resource res) {
    int image_id = image_id_resource_icon(res);
    img = image_get(image_id);
}
