#include "graphics/graphics.h"

#include "core/profiler.h"
#include "platform/renderer.h"
#include "graphics/screen.h"

#include "dev/debug.h"
#include <vector>
#include <deque>

std::vector<render_command_t> g_render_commands;
std::vector<render_command_t> g_render_subcommands;
std::vector<render_command_t> g_render_debug_commands;

void graphics_draw_line(vec2i start, vec2i end, color color) {
    g_render.draw_line(start, end, color);
}
void graphics_draw_vertical_line(vec2i start, int ny, color color) {
    g_render.draw_line(start, vec2i{start.x, start.y + ny}, color);
}
void graphics_draw_horizontal_line(vec2i start, int nx, color color) {
    g_render.draw_line(start, vec2i{start.x + nx, start.y}, color);
}
void graphics_draw_pixel(vec2i pixel, color color) {
    g_render.draw_pixel(pixel, color);
}
void graphics_draw_rect(vec2i start, vec2i size, color color) {
    g_render.draw_rect(start, size, color);
}

void graphics_shade_rect(vec2i start, vec2i size, int darkness) {
    color alpha = (darkness << COLOR_BITSHIFT_ALPHA);
    g_render.fill_rect(start, size, alpha);
}

void ImageDraw::img_background(painter& ctx, int image_id, float scale, vec2i offset) {
    const image_t* img = image_get(image_id);
    if (!img) {
        return;
    }

    if (scale == -1) {
        //        graphics_renderer()->draw_image(img, 0, 0, COLOR_MASK_NONE, scale, false); // todo?
    }
    else {
        ctx.draw_image(img, vec2i{ (screen_width() - img->width) / 2, (screen_height() - img->height) / 2 } + offset, COLOR_MASK_NONE, scale);
    }
}


void ImageDraw::execute_render_command(painter& ctx, const render_command_t& command) {
    const image_t *img = nullptr;
    switch (command.rtype) {
    case render_command_t::ert_drawtile: {
           img = ctx.isometric_from_drawtile(command.image_id, command.pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_drawtile_top: {
            img = ctx.isometric_from_drawtile_top(command.image_id, command.pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_drawtile_full: {
            img = ctx.isometric_from_drawtile(command.image_id, command.pixel, command.mask, command.flags);

            int offset_y = 15 * (img->width / 58);
            const vec2i pixel = command.pixel - vec2i{ 0, offset_y };
            ctx.isometric_from_drawtile_top(command.image_id, pixel, command.mask, command.flags);
        }
        break;

    case render_command_t::ert_generic: {
            img = ctx.img_generic(command.image_id, command.pixel, command.mask, command.scale, command.flags);
        }
        break;

    case render_command_t::ert_ornament: {
            img = ctx.img_ornament(command.image_id, command.base_id, command.pixel.x, command.pixel.y, command.mask, command.scale);
        }
        break;

    case render_command_t::ert_sprite: {
            img = ctx.img_sprite(command.image_id, command.pixel, command.mask, command.scale, command.flags);
        }
        break;

    case render_command_t::ert_from_below: {
            img = ctx.img_from_below(command.image_id, command.pixel.x, command.pixel.y, command.mask, command.scale);
        }
        break;

    case render_command_t::ert_draw_rect:
        ctx.draw_rect(command.pixel, command.size, COLOR_RED);
        break;
    }

    int sid = command.subcommand;
    while (sid != -1) {
        const render_command_t *subcommand = &g_render_subcommands[sid];
        execute_render_command(ctx, *subcommand);
        sid = subcommand->subcommand;
    }
}

render_command_t& ImageDraw::create_command(render_command_t::e_render_type rt) {
    auto &command = g_render_commands.emplace_back();
    command.id = g_render_commands.size() - 1;
    command.rtype = rt;
    command.use_sort_pixel = false;
    command.sort_pixel = {};
    command.subcommand = -1;
    return command;
}

render_command_t &ImageDraw::create_dcommand(render_command_t::e_render_type rt) {
    auto &command = g_render_debug_commands.emplace_back();
    command.id = g_render_commands.size() - 1;
    command.rtype = rt;
    command.use_sort_pixel = false;
    command.sort_pixel = {};
    command.subcommand = -1;
    return command;
}

render_command_t& ImageDraw::active_command() {
    return g_render_commands.back();
}

render_command_t& ImageDraw::create_subcommand(render_command_t::e_render_type rt) {
    OZZY_PROFILER_FUNCTION();
    if (g_render_commands.empty()) {
        return create_command(rt);
    }

    int last_idx = g_render_commands.size() - 1;
    int new_id = 0;
    
    // Add new subcommand to g_render_subcommands
    auto& subcommand = g_render_subcommands.emplace_back();
    int new_idx = g_render_subcommands.size() - 1;

    if (g_render_commands[last_idx].subcommand == -1) {
        // First subcommand - attach to main command
        g_render_commands[last_idx].subcommand = new_idx;
        subcommand.id = 0;
    } else {
        // Find last subcommand in chain
        render_command_t *current = g_render_commands[last_idx].last_subcommand();
        int current_idx = current - &g_render_subcommands[0];
        
        // Link to new subcommand
        g_render_subcommands[current_idx].subcommand = new_idx;
        subcommand.id = current->id + 1;
    }

    subcommand.rtype = rt;
    subcommand.use_sort_pixel = false;
    subcommand.sort_pixel = {};
    subcommand.subcommand = -1;
    return subcommand;
}

void ImageDraw::clear_render_commands() {
    OZZY_PROFILER_FUNCTION();
    g_render_commands.clear();
    g_render_subcommands.clear();
}

void ImageDraw::apply_render_commands(painter& ctx) {
    OZZY_PROFILER_FUNCTION();
    std::sort(g_render_commands.begin(), g_render_commands.end(),
        [] (const auto& lhs, const auto& rhs) {
            const vec2i lhs_sort = lhs.use_sort_pixel ? lhs.sort_pixel : lhs.pixel;
            const vec2i rhs_sort = rhs.use_sort_pixel ? rhs.sort_pixel : rhs.pixel;
            if (lhs_sort.y == rhs_sort.y) {
                return lhs_sort.x > rhs_sort.x;
            }

            return lhs_sort.y < rhs_sort.y;
        });

    for (const auto& command : g_render_commands) {
        execute_render_command(ctx, command);
    }

    clear_render_commands();
}

void ImageDraw::finalize_render(painter &ctx) {
    for (const auto &command : g_render_debug_commands) {
        execute_render_command(ctx, command);
    }

    g_render_debug_commands.clear();
}

render_command_t *render_command_t::last_subcommand() {
    if (this->subcommand == -1) {
        return nullptr;
    }
    
    // First subcommand is in g_render_subcommands
    render_command_t *cmd = &g_render_subcommands[this->subcommand];
    
    // Traverse the rest of the chain in g_render_subcommands
    while (cmd->subcommand != -1) {
        cmd = &g_render_subcommands[cmd->subcommand];
    }
    return cmd;
}
