#include "rich_text.h"

#include "core/calc.h"
#include "core/string.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "game/game.h"

int rich_text_t::init(pcstr text, vec2i ptext, int width_blocks, int height_blocks, bool adjust_width_on_no_scroll) {
    x_text = ptext.x;
    y_text = ptext.y;
    if (!num_lines) {
        clear_links();

        text_height_blocks = height_blocks;
        text_height_lines = height_blocks - 1;
        text_width_blocks = width_blocks;

        num_lines = draw(text, vec2i(x_text + 8, y_text + 6), 16 * text_width_blocks - 16, text_height_lines, /*meaure_only*/true);
        dscrollbar.pos.x = x_text + 16 * text_width_blocks - 1;
        dscrollbar.pos.y = y_text;
        dscrollbar.height = 16 * text_height_blocks;
        dscrollbar.init(dscrollbar.scroll_position, num_lines - text_height_lines);
        if (num_lines <= text_height_lines && adjust_width_on_no_scroll) {
            text_width_blocks += 2;
        }
    }

    dscrollbar.onscroll([this] {
        clear_links();
    });

    return text_width_blocks;
}

void rich_text_t::set_fonts(e_font normal_font, e_font link_font) {
    normal_font_def = font_definition_for(normal_font);
    link_font_def = font_definition_for(link_font);
}

void rich_text_t::reset(int scroll_position) {
    scrollbar_reset(&dscrollbar, scroll_position);
    num_lines = 0;
    clear_links();
}

void rich_text_t::clear_links(void) {
    links.clear();
}

int rich_text_t::get_clicked_link(const mouse* m) {
    if (m->left.went_up) {
        for (int i = 0; i < links.size(); i++) {
            if (m->x >= links[i].x_min && m->x <= links[i].x_max && m->y >= links[i].y_min && m->y <= links[i].y_max) {
                return links[i].message_id;
            }
        }
    }
    return -1;
}

void rich_text_t::add_link(int message_id, int x_start, int x_end, int y) {
    if (!links.full()) {
        links.push_back({});
        auto &link = links.back();
        link.message_id = message_id;
        link.x_min = x_start - 2;
        link.x_max = x_end + 2;
        link.y_min = y - 1;
        link.y_max = y + 13;
    }
}

int rich_text_t::get_lexem_width(pcstr str, int in_link) {
    if (!str) {
        return 0;
    }

    int width = 0;
    int guard = 0;
    int word_char_seen = 0;
    int num_bytes = 1;
    while (*str && ++guard < 2000) {
        if (*str == ' ') {
            if (word_char_seen) {
                break;
            }

            width += 4;
        } else if (*str > ' ') {
            // normal char
            const auto glyph = font_letter_id(normal_font_def, (const uint8_t*)str, &num_bytes);
            if (glyph.imagid >= 0) {
                width += normal_font_def->letter_spacing + image_letter(glyph.imagid)->width;
            }
        }
        str++;
    }

    return width;
}

int rich_text_t::get_word_width(pcstr str, int in_link, int* num_chars) {
    if (!str) {
        return 0;
    }

    int width = 0;
    int guard = 0;
    int word_char_seen = 0;
    int start_link = 0;
    *num_chars = 0;
    while (*str && ++guard < 2000) {
        if (*str == '@') {
            str++;
            if (!word_char_seen) {
                if (*str == 'P' || *str == 'L') {
                    *num_chars += 2;
                    width = 0;
                    break;
                } else if (*str == 'G') {
                    // skip graphic
                    *num_chars += 2;
                    while (*str >= '0' && *str <= '9') {
                        str++;
                        (*num_chars)++;
                    }
                    width = 0;
                    break;
                } else {
                    (*num_chars)++;
                    while (*str >= '0' && *str <= '9') {
                        str++;
                        (*num_chars)++;
                    }
                    in_link = 1;
                    start_link = 1;
                }
            }
        }
        int num_bytes = 1;
        if (*str == ' ') {
            if (word_char_seen)
                break;

            width += 4;
        } else if (*str > ' ') {
            // normal char
            const auto glyph = font_letter_id(normal_font_def, (const uint8_t*)str, &num_bytes);
            if (glyph.imagid >= 0) {
                width += 1 + image_letter(glyph.imagid)->width;
            }

            word_char_seen = 1;
            if (num_bytes > 1) {
                if (start_link) {
                    // add space before links in multibyte charsets
                    width += 4;
                    start_link = 0;
                }
                if (!in_link) {
                    *num_chars += num_bytes;
                    break;
                }
            }
        }
        str += num_bytes;
        *num_chars += num_bytes;
    }
    return width;
}

void rich_text_t::draw_line(painter &ctx, pcstr str, int x, int y, color clr, bool measure_only) {
    int start_link = 0;
    int num_link_chars = 0;
    color saved_color = clr;
    bool long_colored_string = false;
    const font_definition* def = normal_font_def;

    while (*str) {
        if (*str == '@') {
            if (*(str + 1) == 'Y') {
                str += 2;
                long_colored_string = true;
                def = font_definition_for(FONT_NORMAL_YELLOW);
            } else if (*(str + 1) == 'I') {
                str += 2; // skip @I
                int small_image_id = atoi(str);
                while (*str >= '0' && *str <= '9') {
                    str++;
                }

                const image_t* letter = image_letter('@');
                x -= letter->width;
                const image_t *img = ImageDraw::img_generic(ctx, small_image_id, x, y);
                x += img->width;
                continue;
            } else {
                int message_id = atoi(++str);
                while (*str >= '0' && *str <= '9') {
                    str++;
                }
                int width = get_word_width(str, 1, &num_link_chars);
                add_link(message_id, x, x + width, y);
                start_link = 1;
            }
        }

        if (*str == '&' && long_colored_string) {
            long_colored_string = false;
            clr = saved_color;
            def = normal_font_def;
            str++;
        }

        if (*str >= ' ') {
           
            if (num_link_chars > 0) {
                def = link_font_def;
            }

            int num_bytes = 1;
            const auto glyph = font_letter_id(def, (const uint8_t*)str, &num_bytes);
            if (glyph.imagid < 0) {
                x += def->space_width;
            } else {
                if (num_bytes > 1 && start_link) {
                    // add space before links in multibyte charsets
                    x += def->space_width;
                    start_link = 0;
                }

                const image_t* img = image_letter(glyph.imagid);
                if (!measure_only) {
                    int height = def->image_y_offset((const uint8_t *)str, img->height, def->line_height);
                    ImageDraw::img_letter(ctx, img, def->font, glyph.imagid, x, y - height, clr);
                }
                x += img->width + def->letter_spacing;
            }

            if (num_link_chars > 0) {
                num_link_chars -= num_bytes;
            }

            str += num_bytes;
        } else {
            str++;
        }
    }
}

int rich_text_t::draw_impl(pcstr text, vec2i offset, int box_width, int height_lines, color color, bool measure_only, bool centered) {
    int image_height_lines = 0;
    int image_id = 0;
    int lines_before_image = 0;
    int paragraph = 0;
    int has_more_characters = 1;
    int y = offset.y;
    int guard = 0;
    int line = 0;
    int num_lines = 0;
    painter ctx = game.painter();
    struct line_image {
        int pos;
        int img;
    };
    bstring256 tmp_line;
    while (has_more_characters || image_height_lines) {
        if (++guard >= 1000) {
            break;
        }

        tmp_line.clear();

        int current_width, x_line_offset;
        current_width = x_line_offset = paragraph ? 50 : 0;
        paragraph = 0;
        while ((has_more_characters || image_height_lines) && current_width < box_width) {
            if (image_height_lines) {
                image_height_lines--;
                break;
            }
            int word_num_chars;
            int last_word_width = get_word_width(text, 0, &word_num_chars);
            current_width += last_word_width;
            if (current_width >= box_width) {
                if (current_width == 0)
                    has_more_characters = 0;

            } else {
                for (int i = 0; i < word_num_chars; i++) {
                    char c = *text++;
                    if (c == '@') {
                        if (*text == 'P') {
                            paragraph = 1;
                            text++;
                            current_width = box_width;
                            break;
                        } else if (*text == 'L') {
                            text++;
                            current_width = box_width;
                            break;
                        } else if (*text == 'I') {
                            int small_image_id = atoi(text + 1);
                            int id_word_width = get_lexem_width(text - 2, 0);

                            const image_t *img = image_get(small_image_id);
                            const int img_width = img->width;

                            current_width -= id_word_width;
                            current_width -= img_width;

                            tmp_line.append('@');
                            while (c >= '0' && c <= '9') {
                                tmp_line.append(c);
                                c = *text++;
                            }
                            break;
                        } else if (*text == 'G') {
                            if (!tmp_line.empty()) {
                                num_lines++;
                            }

                            text++; // skip 'G'
                            current_width = box_width;
                            image_id = atoi(text);
                            c = *text++;
                            while (c >= '0' && c <= '9') {
                                c = *text++;
                            }
                            image_id += image_id_from_group(GROUP_MESSAGE_IMAGES) - 1;
                            image_height_lines = image_get(image_id)->height / 16 + 2;
                            if (line > 0) {
                                lines_before_image = 1;
                            }

                            break;
                        }
                    }

                    if (!tmp_line.empty() || c != ' ') { // no space at start of line, should we need this trim?
                        tmp_line.append(c);
                    }
                }
                if (!text || !*text) {
                    has_more_characters = 0;
                }
            }
        }

        int outside_viewport = 0;
        if (!measure_only) {
            if (line < dscrollbar.scroll_position || line >= dscrollbar.scroll_position + height_lines)
                outside_viewport = 1;
        }

        if (!outside_viewport) {
            int centering_offset = 0;
            if (centered) {
                centering_offset = (box_width - current_width) / 2;
            }
            draw_line(ctx, tmp_line, x_line_offset + offset.x + centering_offset, y, color, measure_only);
        }

        if (!measure_only) {
            if (image_id) {
                if (lines_before_image)
                    lines_before_image--;
                else {
                    const image_t* img = image_get(image_id);
                    image_height_lines = img->height / 16 + 2;
                    int image_offset_x = offset.x + (box_width - img->width) / 2 - 4;
                    if (line < height_lines + dscrollbar.scroll_position) {
                        if (line >= dscrollbar.scroll_position)
                            ImageDraw::img_generic(ctx, image_id, image_offset_x, y + 8);
                        else {
                            ImageDraw::img_generic(ctx, image_id, image_offset_x, y + 8 - 16 * (dscrollbar.scroll_position - line));
                        }
                    }
                    image_id = 0;
                }
            }
        }
        line++;
        num_lines++;
        if (!outside_viewport) {
            y += 16;
        }
    }
    return num_lines;
}

int rich_text_t::draw(pcstr text, vec2i offset, int box_width, int height_lines, bool measure_only, bool centered) {
    return draw_impl(text, offset, box_width, height_lines, 0, measure_only, centered);
}

int rich_text_t::draw_colored(pcstr text, vec2i offset, int box_width, int height_lines, color color) {
    return draw_impl(text, offset, box_width, height_lines, color, 0, false);
}

void rich_text_t::draw_scrollbar(vec2i pos) {
    if (dscrollbar.max_scroll_position > 0 || dscrollbar.always_visible) {
        inner_panel_draw(dscrollbar.pos + pos + vec2i{ 3, 16 }, vec2i{ 2, (dscrollbar.height - 2) / 16 });
    }
    scrollbar_draw(pos, &dscrollbar);
}

int rich_text_t::handle_mouse(const mouse* m, vec2i pos) {
    return scrollbar_handle_mouse(pos, &dscrollbar, m);
}

int rich_text_t::scroll_position() {
    return dscrollbar.scroll_position;
}

scrollbar_t *rich_text_t::scrollbar() {
    return &dscrollbar;
}
