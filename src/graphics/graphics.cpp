#include "graphics/graphics.h"

#include "core/profiler.h"
#include "platform/renderer.h"
#include "graphics/screen.h"

#include "dev/debug.h"
#include <vector>

std::vector<render_command_t> g_render_commands;

void graphics_clear_screen() {
    OZZY_PROFILER_SECTION("Render/Frame/Clear Screen");
    graphics_renderer()->clear_screen();
}

namespace ImageDraw
{
    const image_t* isometric_from_drawtile(painter& ctx, int image_id, vec2i pos, color color_mask, ImgFlags flags = 0)
    {
        const image_t* img = image_get(image_id);
        if (!img) {
            return nullptr;
        }
        //    if ((img->atlas.id >> IMAGE_ATLAS_BIT_OFFSET) == ATLAS_UNPACKED_EXTRA_ASSET) {
        //        assets_load_unpacked_asset(image_id);
        //    }
        pos.y += HALF_TILE_HEIGHT_PIXELS * (img->isometric_size() + 1) - img->height;

        g_render.draw_image(ctx, img, pos, color_mask, 1.f, flags);
        return img;
    }

    const image_t* isometric_from_drawtile_top(painter& ctx, int image_id, vec2i pos, color color_mask, ImgFlags flags = 0)
    {
        const image_t* img = image_get(image_id);
        if (!img) {
            return nullptr;
        }
        const image_t* img_top = img->isometric_top;
        if (!img_top) {
            return nullptr;
        }
        pos.y += HALF_TILE_HEIGHT_PIXELS * (img_top->isometric_size() + 1) - img_top->height;

        g_render.draw_image(ctx, img_top, pos, color_mask, 1.f, flags);
        return img_top;
    }

    const image_t* img_sprite(painter& ctx, int image_id, vec2i p, color color_mask, float scale, ImgFlags flags)
    {
        const image_t* img = image_get(image_id);
        bool mirrored = (img->offset_mirror != 0);

        if (mirrored) {
            img = img->mirrored_img;
            p.x -= (img->width - img->animation.sprite_offset.x);
        }
        else {
            p.x -= img->animation.sprite_offset.x;
        }

        flags |= (mirrored ? ImgFlag_Mirrored : ImgFlag_None);

        p.y -= img->animation.sprite_offset.y;
        graphics_renderer()->draw_image(ctx, img, p, color_mask, scale, flags);

        return img;
    }

    const image_t* img_generic(painter& ctx, int image_id, int x, int y, color color_mask, float scale)
    {
        const image_t* img = image_get(image_id);
        graphics_renderer()->draw_image(ctx, img, vec2i{ x, y }, color_mask, scale);
        return img;
    }

    const image_t* img_generic(painter& ctx, int pak, int image_id, vec2i p, color color_mask, float scale)
    {
        const image_t* img = image_get(pak, image_id);
        graphics_renderer()->draw_image(ctx, img, p, color_mask, scale);
        return img;
    }

    const image_t* img_generic(painter& ctx, const image_desc& imgd, vec2i p, color color_mask, float scale)
    {
        const image_t* img = image_get(imgd);
        graphics_renderer()->draw_image(ctx, img, p, color_mask, scale);
        return img;
    }

    const image_t* img_generic(painter& ctx, int image_id, vec2i p, color color_mask, float scale, ImgFlags flags)
    {
        const image_t* img = image_get(image_id);
        vec2i offset{ 0, 0 };
        if (!!(flags & ImgFlag_InternalOffset)) {
            offset = img->animation.sprite_offset;
        }

        graphics_renderer()->draw_image(ctx, img, p - offset, color_mask, scale, flags);
        return img;
    }

    const image_t* img_generic(painter& ctx, const image_t* img, vec2i p, color color_mask, float scale, ImgFlags flags)
    {
        vec2i offset{ 0, 0 };
        if (!!(flags & ImgFlag_InternalOffset)) {
            offset = img->animation.sprite_offset;
        }

        graphics_renderer()->draw_image(ctx, img, p - offset, color_mask, scale, flags);
        return img;
    }
}

void graphics_draw_line(vec2i start, vec2i end, color color) {
    graphics_renderer()->draw_line(start, end, color);
}
void graphics_draw_vertical_line(vec2i start, int ny, color color) {
    graphics_renderer()->draw_line(start, vec2i{start.x, start.y + ny}, color);
}
void graphics_draw_horizontal_line(vec2i start, int nx, color color) {
    graphics_renderer()->draw_line(start, vec2i{start.x + nx, start.y}, color);
}
void graphics_draw_pixel(vec2i pixel, color color) {
    graphics_renderer()->draw_pixel(pixel, color);
}
void graphics_draw_rect(vec2i start, vec2i size, color color) {
    graphics_renderer()->draw_rect(start, size, color);
}

void ImageDraw::fill_rect(vec2i start, vec2i size, color color) {
    graphics_renderer()->fill_rect(start, size, color);
}

void graphics_shade_rect(vec2i start, vec2i size, int darkness) {
    color alpha = (darkness << COLOR_BITSHIFT_ALPHA);
    graphics_renderer()->fill_rect(start, size, alpha);
}

const image_t* ImageDraw::img_isometric(painter& ctx, int image_id, vec2i p, color color_mask, float scale, ImgFlags flags) {
    isometric_from_drawtile(ctx, image_id, p, color_mask, flags);
    const image_t* img = isometric_from_drawtile_top(ctx, image_id, p, color_mask, flags);
    return img;
}

void ImageDraw::img_background(painter& ctx, int image_id, float scale, vec2i offset)
{
    const image_t* img = image_get(image_id);
    if (scale == -1) {
        //        graphics_renderer()->draw_image(img, 0, 0, COLOR_MASK_NONE, scale, false); // todo?
    }
    else {
        g_render.draw_image(ctx, img, vec2i{ (screen_width() - img->width) / 2, (screen_height() - img->height) / 2 } + offset, COLOR_MASK_NONE, scale);
    }
}

void ImageDraw::isometric(painter& ctx, int image_id, vec2i pixel, color color_mask, float scale)
{
    ImageDraw::img_generic(ctx, image_id, pixel, color_mask, scale);
}

void ImageDraw::execute_render_command(painter& ctx, const render_command_t& command) {
    switch (command.rtype) {
    case render_command_t::ert_drawtile: {
            ImageDraw::isometric_from_drawtile(ctx, command.image_id, command.pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_drawtile_top: {
            ImageDraw::isometric_from_drawtile_top(ctx, command.image_id, command.pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_drawtile_full: {
            ImageDraw::isometric_from_drawtile(ctx, command.image_id, command.pixel, command.mask, command.flags);
            ImageDraw::isometric_from_drawtile_top(ctx, command.image_id, command.pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_generic: {
            ImageDraw::img_generic(ctx, command.image_id, command.pixel, command.mask, command.scale, command.flags);
        }
        break;

    case render_command_t::ert_ornament: {
            ImageDraw::img_ornament(ctx, command.image_id, command.base_id, command.pixel.x, command.pixel.y, command.mask, command.scale);
        }
        break;

    case render_command_t::ert_sprite: {
            ImageDraw::img_sprite(ctx, command.image_id, command.pixel, command.mask, command.scale, command.flags);
        }
        break;

    case render_command_t::ert_from_below: {
            ImageDraw::img_from_below(ctx, command.image_id, command.pixel.x, command.pixel.y, command.mask, command.scale);
        }
        break;
    }

    for (const auto& subcommand : command.commands) {
        execute_render_command(ctx, subcommand);
    }
}

render_command_t& ImageDraw::create_command(render_command_t::e_render_type rt) {
    auto &command = g_render_commands.emplace_back();
    command.id = g_render_commands.size() - 1;
    command.rtype = rt;
    return command;
}

render_command_t& ImageDraw::active_command() {
    return g_render_commands.back();
}

render_command_t& ImageDraw::create_subcommand(render_command_t::e_render_type rt) {
    if (g_render_commands.empty()) {
        return create_command(rt);
    }
    auto& commands = g_render_commands.back().commands;
    auto& subcommand = commands.emplace_back();
    subcommand.id = commands.size() - 1;
    subcommand.rtype = rt;
    return subcommand;
}

void ImageDraw::clear_render_commands() {
    g_render_commands.clear();
}

void ImageDraw::apply_render_commands(painter& ctx) {
    std::sort(g_render_commands.begin(), g_render_commands.end(),
        [] (const auto& lhs, const auto& rhs) {
            if (lhs.pixel.y == rhs.pixel.y) {
                return lhs.pixel.x > rhs.pixel.x;
            }

            return lhs.pixel.y < rhs.pixel.y;
        });

    for (const auto& command : g_render_commands) {
        execute_render_command(ctx, command);
    }

    clear_render_commands();
}