#include "text.h"

#include "core/string.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

#define ELLIPSIS_LENGTH 4
#define NUMBER_BUFFER_LENGTH 100

static uint8_t tmp_line[200];

struct input_cursor_t {
    int capture;
    int seen;
    int position;
    int cursor_position;
    int width;
    int visible;
    time_millis updated;
    int x_offset;
    int y_offset;
    int text_offset_start;
    int text_offset_end;
};

input_cursor_t input_cursor;

static struct {
    const uint8_t string[ELLIPSIS_LENGTH];
    int width[FONT_TYPES_MAX];
} ellipsis = {{'.', '.', '.', 0}};

static int get_ellipsis_width(e_font font) {
    if (!ellipsis.width[font])
        ellipsis.width[font] = text_get_width(ellipsis.string, font);

    return ellipsis.width[font];
}

void text_capture_cursor(int cursor_position, int offset_start, int offset_end) {
    input_cursor.capture = 1;
    input_cursor.seen = 0;
    input_cursor.position = 0;
    input_cursor.width = 0;
    input_cursor.cursor_position = cursor_position;
    input_cursor.text_offset_start = offset_start;
    input_cursor.text_offset_end = offset_end;
}
void text_draw_cursor(int x_offset, int y_offset, int is_insert) {
    if (!input_cursor.capture)
        return;
    input_cursor.capture = 0;
    time_millis curr = time_get_millis();
    time_millis diff = curr - input_cursor.updated;
    if (!input_cursor.visible && diff >= 200) {
        input_cursor.visible = 1;
        input_cursor.updated = curr;
    } else if (input_cursor.visible && diff >= 400) {
        input_cursor.visible = 0;
        input_cursor.updated = curr;
    }
    if (input_cursor.visible) {
        if (is_insert) {
            graphics_draw_horizontal_line(vec2i{x_offset + input_cursor.x_offset - 3, x_offset + input_cursor.x_offset + 1},
                                          y_offset + input_cursor.y_offset - 3,
                                          COLOR_WHITE);
            graphics_draw_vertical_line(vec2i{x_offset + input_cursor.x_offset - 1, y_offset + input_cursor.y_offset - 3},
                                        y_offset + input_cursor.y_offset + 13,
                                        COLOR_WHITE);
            graphics_draw_horizontal_line(vec2i{x_offset + input_cursor.x_offset - 3, x_offset + input_cursor.x_offset + 1},
                                          y_offset + input_cursor.y_offset + 14,
                                          COLOR_WHITE);
        } else {
            graphics_fill_rect(vec2i{x_offset + input_cursor.x_offset, y_offset + input_cursor.y_offset + 14},
                               vec2i{input_cursor.width, 2},
                               COLOR_WHITE);
        }
    }
}

int get_letter_height(const uint8_t* str, e_font font) {
    const font_definition* def = font_definition_for(font);
    int num_bytes = 1;

    int letter_id = font_letter_id(def, str, &num_bytes);
    return letter_id >= 0 ? image_letter(letter_id)->height : 0;
}

int text_get_width(const uint8_t* str, e_font font) {
    if (!str) {
        return 0;
    }

    const font_definition* def = font_definition_for(font);
    int maxlen = 10000;
    int width = 0;
    while (*str && maxlen > 0) {
        int num_bytes = 1;
        if (*str == ' ')
            width += def->space_width;
        else {
            int letter_id = font_letter_id(def, str, &num_bytes);
            if (letter_id >= 0) {
                const image_t* img = image_letter(letter_id);
                if (img != nullptr)
                    width += def->letter_spacing + img->width;
            }
        }
        str += num_bytes;
        maxlen -= num_bytes;
    }
    return width;
}

int get_letter_width(const uint8_t* str, const font_definition* def, int* num_bytes) {
    *num_bytes = 1;
    if (*str == ' ') {
        return def->space_width;
    }

    int letter_id = font_letter_id(def, str, num_bytes);
    if (letter_id >= 0) {
        return def->letter_spacing + image_letter(letter_id)->width;
    } else {
        return 0;
    }
}

static int get_word_width(const uint8_t* str, e_font font, int* out_num_chars) {
    const font_definition* def = font_definition_for(font);
    int width = 0;
    int guard = 0;
    int word_char_seen = 0;
    int num_chars = 0;
    while (*str && ++guard < 200) {
        int num_bytes = 1;
        if (*str == ' ' || *str == '\n') {
            if (word_char_seen)
                break;

            width += def->space_width;
        } else if (*str == '$') {
            if (word_char_seen)
                break;

        } else if (*str > ' ') {
            // normal char
            int letter_id = font_letter_id(def, str, &num_bytes);
            if (letter_id >= 0)
                width += image_letter(letter_id)->width + def->letter_spacing;

            word_char_seen = 1;
            if (num_bytes > 1) {
                num_chars += num_bytes;
                break;
            }
        }
        str += num_bytes;
        num_chars += num_bytes;
    }
    *out_num_chars = num_chars;
    return width;
}
uint32_t text_get_max_length_for_width(const uint8_t* str, int length, e_font font, unsigned int requested_width, int invert) {
    const font_definition* def = font_definition_for(font);
    if (!length)
        length = string_length(str);

    if (invert) {
        unsigned int maxlen = length;
        unsigned int width = 0;
        const uint8_t* s = str;
        while (maxlen) {
            int num_bytes;
            width += get_letter_width(s, def, &num_bytes);
            s += num_bytes;
            maxlen -= num_bytes;
        }

        maxlen = length;
        while (maxlen && width > requested_width) {
            int num_bytes;
            width -= get_letter_width(str, def, &num_bytes);
            str += num_bytes;
            maxlen -= num_bytes;
        }
        return maxlen;
    } else {
        unsigned int maxlen = length;
        unsigned int width = 0;
        while (maxlen) {
            int num_bytes;
            width += get_letter_width(str, def, &num_bytes);
            if (width > requested_width)
                break;

            str += num_bytes;
            maxlen -= num_bytes;
        }
        return length - maxlen;
    }
}

void text_ellipsize(uint8_t* str, e_font font, int requested_width) {
    uint8_t* orig_str = str;
    const font_definition* def = font_definition_for(font);
    int ellipsis_width = get_ellipsis_width(font);
    int maxlen = 10000;
    int width = 0;
    int length_with_ellipsis = 0;
    while (*str && maxlen > 0) {
        int num_bytes = 1;
        if (*str == ' ')
            width += def->space_width;
        else {
            int letter_id = font_letter_id(def, str, &num_bytes);
            if (letter_id >= 0)
                width += def->letter_spacing + image_letter(letter_id)->width;
        }
        if (ellipsis_width + width <= requested_width)
            length_with_ellipsis += num_bytes;

        if (width > requested_width)
            break;

        str += num_bytes;
        maxlen -= num_bytes;
    }

    if (10000 - maxlen < string_length(orig_str)) {
        string_copy(ellipsis.string, orig_str + length_with_ellipsis, ELLIPSIS_LENGTH);
    }
}

int text_draw(const uint8_t *str, int x, int y, e_font font, color color) {
    painter ctx = game.painter();
    return text_draw(ctx, str, x, y, font, color);
}

int text_draw(painter &ctx, const uint8_t* str, int x, int y, e_font font, color color, float scale) {
    y = y - 3;


    const font_definition* def = font_definition_for(font);
    if (!def) {
        return 0;
    }

    int length = string_length(str);
    if (!length) {
        return 0;
    }

    if (input_cursor.capture) {
        str += input_cursor.text_offset_start;
        length = input_cursor.text_offset_end - input_cursor.text_offset_start;
    }

    int current_x = x;
    while (length > 0) {
        int num_bytes = 1;

        if (*str >= ' ') {
            int letter_id = font_letter_id(def, str, &num_bytes);
            int width = 0;

            if (letter_id < 0) {
                letter_id = font_letter_id(def, (uint8_t*)"?", &num_bytes);
            }

            if (*str == ' ' || *str == '_') {
                width = (def->space_width * scale);
            } else {
                const image_t* img = image_letter(letter_id);
                if (img != nullptr) {
                    int height = def->image_y_offset(*str, img->height, def->line_height);
                    ImageDraw::img_letter(ctx, font, letter_id, current_x, y - height, color, scale);
                    width = (def->letter_spacing + img->width) * scale;
                }
            }

            if (input_cursor.capture && input_cursor.position == input_cursor.cursor_position) {
                if (!input_cursor.seen) {
                    input_cursor.width = width;
                    input_cursor.x_offset = current_x - x;
                    input_cursor.seen = 1;
                }
            }
            current_x += width;
        }

        str += num_bytes;
        length -= num_bytes;
        input_cursor.position += num_bytes;
    }

    if (input_cursor.capture && !input_cursor.seen) {
        input_cursor.width = 4;
        input_cursor.x_offset = current_x - x;
        input_cursor.seen = 1;
    }

    current_x += def->space_width;
    return current_x - x;
}
void text_draw_centered(const uint8_t* str, int x, int y, int box_width, e_font font, color color) {
    int offset = (box_width - (int)text_get_width(str, font)) / 2;
    if (offset < 0) {
        offset = 0;
    }

    text_draw(str, offset + x, y, font, color);
}
int text_draw_left(uint8_t* str, int x, int y, e_font font, color color) {
    return text_draw(str, x - (int)text_get_width(str, font), y, font, color);
}

static int number_to_string(uint8_t* str, int value, char prefix, const char* postfix) {
    int offset = 0;
    if (prefix)
        str[offset++] = prefix;

    offset += string_from_int(&str[offset], value, 0);
    while (*postfix) {
        str[offset++] = *postfix;
        postfix++;
    }
    str[offset] = 0;
    return offset;
}

int text_draw_number(int value, char prefix, const char* postfix, int x_offset, int y_offset, e_font font) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, prefix, postfix);
    return text_draw(str, x_offset, y_offset, font, 0);
}
int text_draw_number_colored(int value, char prefix, const char* postfix, int x_offset, int y_offset, e_font font, color color) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, prefix, postfix);
    return text_draw(str, x_offset, y_offset, font, color);
}
void text_draw_number_centered(int value, int x_offset, int y_offset, int box_width, e_font font) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, '@', " ");
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}
void text_draw_number_centered_prefix(int value, char prefix, int x_offset, int y_offset, int box_width, e_font font) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, prefix, " ");
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}
void text_draw_number_centered_colored(int value, int x_offset, int y_offset, int box_width, e_font font, color color) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, '@', " ");
    text_draw_centered(str, x_offset, y_offset, box_width, font, color);
}

int text_draw_money(int value, int x_offset, int y_offset, e_font font) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    int money_len = number_to_string(str, value, '@', " ");
    const uint8_t* postfix = lang_get_string(6, 0);
    if (postfix)
        string_copy(postfix, str + money_len, NUMBER_BUFFER_LENGTH - money_len - 1);

    return text_draw(str, x_offset, y_offset, font, 0);
}

int text_draw_percentage(int value, int x_offset, int y_offset, e_font font) {
    uint8_t str[NUMBER_BUFFER_LENGTH];
    number_to_string(str, value, '@', "%");
    return text_draw(str, x_offset, y_offset, font, 0);
}

int text_draw_label_and_number(const char* label, int value, const char* postfix, int x_offset, int y_offset, e_font font, color color) {
    uint8_t str[2 * NUMBER_BUFFER_LENGTH];
    uint8_t* pos = label ? string_copy((const uint8_t*)label, str, NUMBER_BUFFER_LENGTH) : str;
    number_to_string(pos, value, '@', postfix);
    return text_draw(str, x_offset, y_offset, font, color);
}
void text_draw_label_and_number_centered(const char* label, int value, const char* postfix, int x_offset, int y_offset, int box_width, e_font font, color color) {
    uint8_t str[2 * NUMBER_BUFFER_LENGTH];
    uint8_t* pos = label ? string_copy((const uint8_t*)label, str, NUMBER_BUFFER_LENGTH) : str;
    number_to_string(pos, value, '@', postfix);
    text_draw_centered(str, x_offset, y_offset, box_width, font, color);
}

int text_draw_multiline(const uint8_t* str, int x_offset, int y_offset, int box_width, e_font font, uint32_t color) {
    int line_height = font_definition_for(font)->line_height;
    if (line_height < 11)
        line_height = 11;

    int has_more_characters = 1;
    int guard = 0;
    int y = y_offset;
    while (has_more_characters) {
        if (++guard >= 100)
            break;

        // clear line
        for (int i = 0; i < 200; i++) {
            tmp_line[i] = 0;
        }
        int current_width = 0;
        int line_index = 0;
        while (has_more_characters && current_width < box_width) {
            int word_num_chars;
            int word_width = get_word_width(str, font, &word_num_chars);
            current_width += word_width;
            if (current_width >= box_width) {
                if (current_width == 0)
                    has_more_characters = 0;

            } else {
                for (int i = 0; i < word_num_chars; i++) {
                    if (line_index == 0 && *str <= ' ')
                        str++; // skip whitespace at start of line
                    else {
                        tmp_line[line_index++] = *str++;
                    }
                }
                if (!*str)
                    has_more_characters = 0;
                else if (*str == '\n') {
                    str++;
                    break;
                }
            }
        }
        text_draw(tmp_line, x_offset, y, font, color);
        y += line_height + 5;
    }
    return y - y_offset;
}
int text_measure_multiline(const uint8_t* str, int box_width, e_font font) {
    int has_more_characters = 1;
    int guard = 0;
    int num_lines = 0;
    while (has_more_characters) {
        if (++guard >= 100)
            break;

        int current_width = 0;
        while (has_more_characters && current_width < box_width) {
            int word_num_chars;
            int word_width = get_word_width(str, font, &word_num_chars);
            current_width += word_width;
            if (current_width >= box_width) {
                if (current_width == 0)
                    has_more_characters = 0;

            } else {
                str += word_num_chars;
                if (!*str)
                    has_more_characters = 0;
                else if (*str == '\n') {
                    str++;
                    break;
                }
            }
        }
        num_lines += 1;
    }
    return num_lines;
}
