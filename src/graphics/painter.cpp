#include "graphics/painter.h"

#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "platform/renderer.h"

#include <string>

#include <SDL.h>

void painter::draw(SDL_Texture *texture, float x, float y, vec2i offset, vec2i size, color color, float scale, bool mirrored, bool alpha) {
    if (texture == nullptr) {
        return;
    }

    if (!color) {
        color = COLOR_MASK_NONE;
    }

    float overall_scale_factor = scale * this->global_render_scale;
    bool DOWNSCALED_CITY = false;
    if (this->global_render_scale < 1.0f) {
        DOWNSCALED_CITY = true;
    }

    graphics_renderer()->set_texture_scale_mode(texture, overall_scale_factor);

#ifdef USE_RENDER_GEOMETRY
    // if (HAS_RENDER_GEOMETRY) {
    //     SDL_Rect src_coords = { x_offset, y_offset, img->width, height };
    //     SDL_FRect dst_coords = { x / scale, y / scale, img->width / scale, height / scale };
    //     if (img->type == IMAGE_TYPE_ISOMETRIC) {
    //         draw_isometric_footprint_raw(img, texture, &src_coords, &dst_coords, color, scale);
    //     } else {
    //         draw_texture_raw(img, texture, &src_coords, &dst_coords, color, scale);
    //     }
    //     return;
    // }
#endif

    SDL_SetTextureColorMod(texture,
                           (color & COLOR_CHANNEL_RED) >> COLOR_BITSHIFT_RED,
                           (color & COLOR_CHANNEL_GREEN) >> COLOR_BITSHIFT_GREEN,
                           (color & COLOR_CHANNEL_BLUE) >> COLOR_BITSHIFT_BLUE);
    SDL_SetTextureAlphaMod(texture, (color & COLOR_CHANNEL_ALPHA) >> COLOR_BITSHIFT_ALPHA);
    SDL_SetTextureBlendMode(texture, alpha ? SDL_BLENDMODE_BLEND : (SDL_BlendMode)graphics_renderer()->premult_alpha());

    // uncomment here if you want save something from atlases
    int k = 0;
    if (k == 1) {
        char filename[32] = {0};
        static int index = 0;
        sprintf(filename, "%u_img.bmp", index);
        graphics_renderer()->save_texture_to_file(filename, texture);
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
        screen_coords = {static_cast<float>(x * this->global_render_scale - 0.25),
                         static_cast<float>(y * this->global_render_scale - 0.25),
                         static_cast<float>(size.x * overall_scale_factor + 0.5),
                         static_cast<float>(size.y * overall_scale_factor + 0.5)};
    } else {
        screen_coords = {x * this->global_render_scale,
                         y * this->global_render_scale,
                         size.x * overall_scale_factor,
                         size.y * overall_scale_factor};
    }

    if (mirrored) {
        SDL_RenderCopyExF(this->renderer, texture, &texture_coords, &screen_coords, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyExF(this->renderer, texture, &texture_coords, &screen_coords, 0, nullptr, SDL_FLIP_NONE);
    }

    // #ifdef USE_RENDERCOPYF
    //     if (HAS_RENDERCOPYF) {
    //         SDL_FRect dst_coords = { x / scale, y / scale, img->width / scale, height / scale };
    //         SDL_Point center = {0, 0};
    //         SDL_RenderCopyF(data.renderer, texture, &src_coords, &dst_coords);
    //         return;
    //     }
    // #endif
    //
    //     SDL_Rect dst_coords = { (int) round(x / scale), (int) round(y / scale),
    //         (int) round(img->width / scale), (int) round(height / scale) };
    //     SDL_RenderCopy(data.renderer, texture, &src_coords, &dst_coords);
}

void painter::draw(const sprite &spr, vec2i pos, color color_mask, float scale, bool mirrored, bool alpha) {
    if (spr.img == nullptr) {
        return;
    }

    vec2i offset = spr.img->atlas.offset;
    vec2i size = spr.img->size();
    draw(spr.img->atlas.p_atlas->texture, pos.x, pos.y, offset, size, color_mask, scale, mirrored, alpha);
}

sprite_resource_icon::sprite_resource_icon(e_resource res) {
    int image_id = image_id_resource_icon(res);
    img = image_get(image_id);
}
