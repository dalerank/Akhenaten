#include "graphics/graphics.h"
#include "graphics/painter.h"

#include "core/profiler.h"
#include "platform/renderer.h"
#include "graphics/screen.h"
#include "game/game.h"

#include "dev/debug.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <queue>

ImageDraw::render_command_vec g_render_commands;
ImageDraw::render_command_vec g_render_draw_temp_commands;
ImageDraw::render_command_vec g_render_subcommands;
ImageDraw::render_command_vec g_render_debug_commands;

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

render_command_t& ImageDraw::create_command(painter& ctx, render_command_t::e_render_type rt) {
    render_command_vec* dst = ctx.command_buffer ? ctx.command_buffer : &g_render_commands;
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

render_command_t& ImageDraw::active_command(painter& ctx) {
    if (ctx.command_buffer && !ctx.command_buffer->empty())
        return ctx.command_buffer->back();

    return g_render_commands.back();
}

render_command_t& ImageDraw::create_subcommand(painter& ctx, render_command_t::e_render_type rt) {
    OZZY_PROFILER_FUNCTION();
    render_command_vec* cmds = ctx.command_buffer ? ctx.command_buffer : &g_render_commands;
    render_command_vec* subcmds = ctx.subcommand_buffer ? ctx.subcommand_buffer : &g_render_subcommands;

    if (cmds->empty()) {
        return create_command(ctx, rt);
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
        auto sort_less = [](const render_command_t& lhs, const render_command_t& rhs) {
            const vec2i lhs_sort = lhs.use_sort_pixel ? lhs.sort_pixel : lhs.pixel;
            const vec2i rhs_sort = rhs.use_sort_pixel ? rhs.sort_pixel : rhs.pixel;
            if (lhs_sort.y == rhs_sort.y) {
                return lhs_sort.x > rhs_sort.x;
            }
            return lhs_sort.y < rhs_sort.y;
        };

        auto& vec = g_render_commands;
        const size_t n = vec.size();
        const size_t num_threads = static_cast<size_t>(game.mt.get_thread_count());

        if (n < 256 || num_threads < 2) {
            std::sort(vec.begin(), vec.end(), sort_less);
        } else {
            auto futures = game.mt.submit_blocks(size_t(0), n, [&vec, sort_less](size_t start, size_t end) {
                OZZY_PROFILER_SECTION(_, "parallel_sort");
                std::sort(vec.begin() + start, vec.begin() + end, sort_less);
            });
            futures.wait();

            const size_t num_blocks = std::min(n, num_threads);
            const size_t block_size = n / num_blocks;
            const size_t remainder = n % num_blocks;
            auto boundary = [&](size_t b) {
                return b * block_size + (b < remainder ? b : remainder);
            };

            g_render_draw_temp_commands.clear();
            g_render_draw_temp_commands.reserve(n);
            using It = render_command_vec::iterator;
            hvector<std::pair<It, It>, 64> segments;
            for (size_t b = 0; b < num_blocks; ++b) {
                size_t s = boundary(b), e = boundary(b + 1);
                if (s < e) {
                    segments.push_back({ vec.begin() + s, vec.begin() + e });
                }
            }
            auto heap_comp = [&sort_less, &segments](size_t i, size_t j) {
                return sort_less(*segments[j].first, *segments[i].first);
            };
            std::priority_queue<size_t, hvector<size_t, 256>, decltype(heap_comp)> pq(heap_comp);
            for (size_t i = 0; i < segments.size(); ++i) {
                pq.push(i);
            }
            while (!pq.empty()) {
                const size_t i = pq.top();
                pq.pop();
                // Copy a run from this segment while it stays ≤ other segments' heads (bulk copy + fewer heap ops)
                It cur = segments[i].first;
                It run_end = cur;
                const It seg_end = segments[i].second;
                for (;;) {
                    ++run_end;
                    if (run_end == seg_end)
                        break;
                    if (!pq.empty() && sort_less(*segments[pq.top()].first, *run_end))
                        break;
                }
                g_render_draw_temp_commands.insert(g_render_draw_temp_commands.end(), cur, run_end);
                segments[i].first = run_end;
                if (run_end != seg_end)
                    pq.push(i);
            }
            vec = std::move(g_render_draw_temp_commands);
        }
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