#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "core/xstring.h"
#include "core/vec2i.h"
#include "core/svector.h"
#include "graphics/elements/scrollbar.h"

struct mouse;
struct painter;

struct rich_text_link_t {
    int message_id;
    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

struct rich_text_t {
    int x_text;
    int y_text;
    int text_width_blocks;
    int text_height_blocks;
    int text_height_lines;
    int num_lines;
    int max_scroll_position;

    struct margin_t {
        int16_t left = 0;
        int16_t top = 0;
        int16_t right = 0;
        int16_t bottom = 0;
    } margin;

    const font_definition *normal_font_def;
    const font_definition *link_font_def;

    scrollbar_t dscrollbar = { {0, 0}, 0, nullptr };

    svector<rich_text_link_t, 50> links;

    /**
     * Initializes the rich text
     * @param text Text to show
     * @param x_text X offset for the text
     * @param y_text Y offset for the text
     * @param width_blocks Width of the text in blocks of 16px
     * @param height_blocks Height of the text in blocks of 16px
     * @param adjust_width_on_no_scroll Whether to expand the text area into the scrollbar area
     * @return Width of the text in blocks
     */
    int init(pcstr text, vec2i ptext, int width_blocks, int height_blocks, bool adjust_width_on_no_scroll);

    inline int init(xstring text, vec2i ptext, int width_blocks, int height_blocks, bool adjust_width_on_no_scroll) {
        return init(text.c_str(), ptext, width_blocks, height_blocks, adjust_width_on_no_scroll);
    }

    /**
     * Sets fonts to use
     * @param normal_font Normal text
     * @param link_font Link text
     */
    void set_fonts(e_font normal_font, e_font link_font);

    void set_margin(margin_t m) { margin = m; }

    void reset(int scroll_position);
    void clear_links(void);

    /**
     * Get the clicked link, if any
     * @param m Mouse state
     * @return ID of the link (>= 0), or -1 if no link was clicked
     */
    int get_clicked_link(const mouse *m);


    /**
     * Draws rich text
     * @param text Text to draw
     * @param x_offset X offset
     * @param y_offset Y offset
     * @param box_width Width of the box in pixels
     * @param height_lines Number of available lines
     * @param measure_only True to only measure text, not draw it
     * @return Total number of lines required for the text
     */
    int draw(pcstr text, vec2i offset, int box_width, int height_lines, bool measure_only, bool centered = false);

    inline int draw(xstring text, vec2i offset, int box_width, int height_lines, bool measure_only, bool centered = false) {
        return draw(text.c_str(), offset, box_width, height_lines, measure_only, centered);
    }

    /**
     * Draws rich text with specified color
     * @param text Text to draw
     * @param x_offset X offset
     * @param y_offset Y offset
     * @param box_width Width of the box in pixels
     * @param height_lines Number of available lines
     * @param color Color to draw with
     * @return Total number of lines required for the text
     */
    int draw_colored(pcstr text, vec2i offset, int box_width, int height_lines, color color);

    inline int draw_colored(xstring text, vec2i offset, int box_width, int height_lines, color color) {
        return draw_colored(text.c_str(), offset, box_width, height_lines, color);
    }


    void draw_scrollbar(vec2i pos);
    int handle_mouse(const mouse *m, vec2i pos);

    int scroll_position();
    scrollbar_t *scrollbar();

    void add_link(int message_id, int x_start, int x_end, int y);
    int get_lexem_width(pcstr str, int in_link);
    int get_word_width(pcstr str, int in_link, int *num_chars);
    void draw_line(painter &ctx, pcstr str, int x, int y, color clr, bool measure_only);
    int draw_impl(pcstr text, vec2i offset, int box_width, int height_lines, color color, bool measure_only, bool centered);
};
