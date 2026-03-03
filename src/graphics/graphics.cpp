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

namespace {
thread_local ImageDraw::render_command_vec* tls_render_commands = nullptr;
thread_local ImageDraw::render_command_vec* tls_render_subcommands = nullptr;
}

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
    OZZY_PROFILER_FUNCTION();

    if (command.location != nullptr) {
        OZZY_PROFILER_TAG("location", command.location);
    }

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

    int sid = command.start_subcommand;
    if (sid != -1) {
        for (sid = command.start_subcommand; sid <= command.finish_subcommand; ++sid) {
            const render_command_t *subcommand = &g_render_subcommands[sid];
            execute_render_command(ctx, *subcommand);
        }
    }
}

void ImageDraw::set_thread_command_buffers(render_command_vec* commands, render_command_vec* subcommands) {
    tls_render_commands = commands;
    tls_render_subcommands = subcommands;
}

void ImageDraw::clear_thread_command_buffers() {
    tls_render_commands = nullptr;
    tls_render_subcommands = nullptr;
}

void ImageDraw::merge_block_commands_into_global(const render_command_block& block_commands, const render_command_block & block_subcommands) {
    for (size_t b = 0; b < block_commands.size(); b++) {
        const auto& subcmds = block_subcommands[b];
        const size_t sub_offset = g_render_subcommands.size();
        g_render_subcommands.insert(g_render_subcommands.end(), subcmds.begin(), subcmds.end());

        for (const auto& cmd : block_commands[b]) {
            render_command_t c = cmd;
            if (c.start_subcommand >= 0) {
                c.start_subcommand += static_cast<int>(sub_offset);
                c.finish_subcommand += static_cast<int>(sub_offset);
            }
            c.id = static_cast<uint32_t>(g_render_commands.size());
            g_render_commands.push_back(c);
        }
    }
}

render_command_t& ImageDraw::create_command(render_command_t::e_render_type rt) {
    std::vector<render_command_t>* dst = tls_render_commands ? tls_render_commands : &g_render_commands;
    auto& command = dst->emplace_back();
    command.id = static_cast<uint32_t>(dst->size() - 1);
    command.rtype = rt;
    command.use_sort_pixel = false;
    command.sort_pixel = {};
    command.start_subcommand = -1;
    command.finish_subcommand = -1;
    return command;
}

render_command_t &ImageDraw::create_dcommand(render_command_t::e_render_type rt) {
    auto &command = g_render_debug_commands.emplace_back();
    command.id = g_render_commands.size() - 1;
    command.rtype = rt;
    command.use_sort_pixel = false;
    command.sort_pixel = {};
    command.start_subcommand = -1;
    command.finish_subcommand = -1;
    return command;
}

render_command_t& ImageDraw::active_command() {
    if (tls_render_commands && !tls_render_commands->empty())
        return tls_render_commands->back();
    return g_render_commands.back();
}

render_command_t& ImageDraw::create_subcommand(render_command_t::e_render_type rt) {
    OZZY_PROFILER_FUNCTION();
    std::vector<render_command_t>* cmds = tls_render_commands ? tls_render_commands : &g_render_commands;
    std::vector<render_command_t>* subcmds = tls_render_subcommands ? tls_render_subcommands : &g_render_subcommands;

    if (cmds->empty()) {
        return create_command(rt);
    }

    int last_idx = static_cast<int>(cmds->size()) - 1;
    auto& subcommand = subcmds->emplace_back();
    int new_idx = static_cast<int>(subcmds->size()) - 1;

    if ((*cmds)[last_idx].start_subcommand == -1) {
        (*cmds)[last_idx].start_subcommand = new_idx;
        (*cmds)[last_idx].finish_subcommand = new_idx;
        subcommand.id = 0;
    } else {
        int current_idx = (*cmds)[last_idx].finish_subcommand;
        (*cmds)[last_idx].finish_subcommand = new_idx;
        subcommand.id = (*subcmds)[current_idx].id + 1;
    }

    subcommand.rtype = rt;
    subcommand.use_sort_pixel = false;
    subcommand.sort_pixel = {};
    subcommand.start_subcommand = -1;
    subcommand.finish_subcommand = -1;
    return subcommand;
}

void ImageDraw::clear_render_commands() {
    OZZY_PROFILER_FUNCTION();
    g_render_commands.clear();
    g_render_subcommands.clear();
}

void ImageDraw::apply_render_commands(painter& ctx, std::string_view p) {
    OZZY_PROFILER_SECTION(_, p);
    {
        OZZY_PROFILER_SECTION(_, "sort");
        std::sort(g_render_commands.begin(), g_render_commands.end(),
            [] (const auto &lhs, const auto &rhs) {
            const vec2i lhs_sort = lhs.use_sort_pixel ? lhs.sort_pixel : lhs.pixel;
            const vec2i rhs_sort = rhs.use_sort_pixel ? rhs.sort_pixel : rhs.pixel;
            if (lhs_sort.y == rhs_sort.y) {
                return lhs_sort.x > rhs_sort.x;
            }

            return lhs_sort.y < rhs_sort.y;
        });
    }

    {
        OZZY_PROFILER_SECTION(_, "draw");
        for (const auto &command : g_render_commands) {
            execute_render_command(ctx, command);
        }
    }

    clear_render_commands();
}

void ImageDraw::finalize_render(painter &ctx) {
    for (const auto &command : g_render_debug_commands) {
        execute_render_command(ctx, command);
    }

    g_render_debug_commands.clear();
}