#include "ui.h"

#include "core/hvector.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "graphics/font.h"

namespace ui {

hvector<ui::cmd_t, 256> g_ui_commands;

void execute_ui_command(painter& ctx, const ui::cmd_t& cmd) {
    switch (cmd.type) {
    case cmd_t::image:
        ctx.img_generic(cmd.image_id, cmd.pos, cmd.mask, cmd.scale, cmd.img_flags);
        break;

    case cmd_t::fill_rect:
        ctx.fill_rect(cmd.pos, cmd.size, cmd.clr);
        break;

    case cmd_t::draw_rect:
        ctx.draw_rect(cmd.pos, cmd.size, cmd.clr);
        break;

    case cmd_t::h_line:
        graphics_draw_horizontal_line(cmd.pos, cmd.box_width, cmd.clr);
        break;

    case cmd_t::v_line:
        graphics_draw_vertical_line(cmd.pos, cmd.box_width, cmd.clr);
        break;

    case cmd_t::panel_outer:
        outer_panel_draw(cmd.pos, cmd.size.x, cmd.size.y);
        break;

    case cmd_t::panel_inner:
        inner_panel_draw(cmd.pos, cmd.size);
        break;

    case cmd_t::text:
        if (!!(cmd.flags & UiFlags_LabelMultiline)) {
            text_draw_multiline(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.font, 0);
        } else {
            lang_text_draw(cmd.str.c_str(), cmd.pos, cmd.font, cmd.box_width);
        }
        break;

    case cmd_t::text_centered:
        text_draw_centered(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.font, cmd.clr);
        break;

    case cmd_t::text_multiline:
        text_draw_multiline(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.font, cmd.clr);
        break;

    case cmd_t::lang_text_year:
        lang_text_draw_year(cmd.year, cmd.pos.x, cmd.pos.y, cmd.font);
        break;

    case cmd_t::text_colored:
        if (cmd.box_width > 0) {
            text_draw_centered(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.font, cmd.clr);
        } else if (text_cursor_capture_active()) {
            text_draw((const uint8_t*)cmd.str.c_str(), cmd.pos.x, cmd.pos.y + 3, cmd.font, cmd.clr);
        } else {
            lang_text_draw_colored(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.font, cmd.clr);
        }
        break;

    case cmd_t::text_rich: {
        rich_text_t rich_text;
        rich_text.set_fonts(cmd.font, FONT_NORMAL_YELLOW);
        const bool centered = !!(cmd.flags & UiFlags_AlignCentered);
        rich_text.draw(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.size.y, false, centered);
        break;
    }

    case cmd_t::clip_set:
        graphics_set_clip_rectangle(cmd.pos, cmd.size);
        break;

    case cmd_t::clip_reset:
        graphics_reset_clip_rectangle();
        break;

    case cmd_t::button_border:
        button_border_draw(cmd.pos, cmd.size, cmd.img_flags != 0);
        break;

    case cmd_t::small_panel:
        small_panel_draw_colored(cmd.pos, cmd.box_width, cmd.image_id, cmd.mask);
        break;

    case cmd_t::shade_rect:
        graphics_shade_rect(cmd.pos, cmd.size, cmd.image_id);
        break;

    case cmd_t::large_label: {
        large_label_draw(cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.image_id);
        const int letter_height = font_definition_for(cmd.font)->line_height;
        text_draw_centered((uint8_t*)cmd.str.c_str(), cmd.pos.x + 1, cmd.pos.y + (cmd.size.y - letter_height) / 2,
          cmd.size.x, cmd.font, 0);
        break;
    }

    case cmd_t::rich_draw:
        if (cmd.rt) {
            cmd.rt->draw(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.size.y, false);
            if (!(cmd.flags & UiFlags_NoScroll)) {
                cmd.rt->draw_scrollbar(vec2i{-16, 0});
            }
        }
        break;

    case cmd_t::cursor_capture:
        text_capture_cursor(cmd.pos.x, cmd.pos.y, cmd.box_width);
        break;

    case cmd_t::cursor_consume:
        text_cursor_consume_capture();
        break;

    case cmd_t::cursor_insert: {
        const vec2i c = cmd.pos + vec2i{text_cursor_x_offset(), text_cursor_y_offset()};
        graphics_draw_horizontal_line(vec2i{c.x - 3, c.x + 1}, c.y - 3, COLOR_WHITE);
        graphics_draw_vertical_line(vec2i{c.x - 1, c.y - 3}, c.y + 13, COLOR_WHITE);
        graphics_draw_horizontal_line(vec2i{c.x - 3, c.x + 1}, c.y + 14, COLOR_WHITE);
        text_cursor_consume_capture();
        break;
    }
    case cmd_t::cursor_block: {
        const int w = cmd.box_width > 0 ? cmd.box_width : text_cursor_width();
        graphics_fill_rect(cmd.pos + vec2i{text_cursor_x_offset(), 14}, vec2i{w, 2}, COLOR_WHITE);
        text_cursor_consume_capture();
        break;
    }

    case cmd_t::saved_texture:
        graphics_draw_from_texture(cmd.image_id, cmd.pos, cmd.size);
        break;

    case cmd_t::texture_icon:
        if (cmd.sdl_texture) {
            painter tex_ctx = game.painter();
            tex_ctx.draw((SDL_Texture*)cmd.sdl_texture, cmd.pos, {0, 0}, cmd.size, cmd.mask, cmd.scale, cmd.scale, 0,
              (ImgFlags)cmd.img_flags);
        }
        break;

    default:
        break;
    }
}

void push_cmd(cmd_t&& cmd) {
    g_ui_commands.push_back(std::move(cmd));
}

void flush_commands() {
    painter ctx = game.painter();
    for (size_t i = 0; i < g_ui_commands.size(); ++i) {
        execute_ui_command(ctx, g_ui_commands[i]);
    }
    g_ui_commands.clear();
}

void reset_ui_command_queue() {
    g_ui_commands.clear();
}

} // namespace ui
