#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "core/xstring.h"
#include "core/vec2i.h"

struct mouse;
struct scrollbar_t;

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
int rich_text_init(const uint8_t* text, vec2i ptext, int width_blocks, int height_blocks, bool adjust_width_on_no_scroll);
inline int rich_text_init(xstring text, vec2i ptext, int width_blocks, int height_blocks, bool adjust_width_on_no_scroll) {
    return rich_text_init((const uint8_t *)text.c_str(), ptext, width_blocks, height_blocks, adjust_width_on_no_scroll);
}

/**
 * Sets fonts to use
 * @param normal_font Normal text
 * @param link_font Link text
 */
void rich_text_set_fonts(e_font normal_font, e_font link_font);
void rich_text_reset(int scroll_position);
void rich_text_clear_links(void);

/**
 * Get the clicked link, if any
 * @param m Mouse state
 * @return ID of the link (>= 0), or -1 if no link was clicked
 */
int rich_text_get_clicked_link(const mouse* m);

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
int rich_text_draw(const uint8_t* text, vec2i offset, int box_width, int height_lines, bool measure_only, bool centered = false);
inline int rich_text_draw(xstring text, vec2i offset, int box_width, int height_lines, bool measure_only, bool centered = false) {
    return rich_text_draw((const uint8_t *)text.c_str(), offset, box_width, height_lines, measure_only, centered);
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
int rich_text_draw_colored(const uint8_t* text, vec2i offset, int box_width, int height_lines, color color);
inline int rich_text_draw_colored(xstring text, vec2i offset, int box_width, int height_lines, color color) {
    return rich_text_draw_colored((const uint8_t *)text.c_str(), offset, box_width, height_lines, color);
}
void rich_text_draw_scrollbar(vec2i pos);

int rich_text_handle_mouse(const mouse* m, vec2i pos);
int rich_text_scroll_position();
scrollbar_t *rich_text_scrollbar();
