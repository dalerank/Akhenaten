#include "graphics.h"

#include "city/view/view.h"
#include "core/config.h"
#include "graphics/color.h"
#include "graphics/menu.h"
#include "graphics/screen.h"
#include "core/game_environment.h"
#include "graphics/renderer.h"

#include <stdlib.h>
#include <string.h>

#ifdef __vita__
#include <vita2d.h>
#endif

static struct {
    color_t *pixels;
    int width;
    int height;
} canvas[MAX_CANVAS];

static struct {
    int x_start;
    int x_end;
    int y_start;
    int y_end;
} clip_rectangle = {0, 800, 0, 600};

static struct {
    int x;
    int y;
} translation;

static clip_info clip;
static canvas_type active_canvas;

#ifdef __vita__
extern vita2d_texture *tex_buffer_ui;
extern vita2d_texture * tex_buffer_city;
#endif

void graphics_init_canvas(int width, int height) {
#ifdef __vita__
    canvas[CANVAS_UI].pixels = vita2d_texture_get_datap(tex_buffer_ui);
    if (config_get(CONFIG_UI_ZOOM))
        canvas[CANVAS_CITY].pixels = vita2d_texture_get_datap(tex_buffer_city);
 else {
        canvas[CANVAS_CITY].pixels = 0;
    }
#else
    free(canvas[CANVAS_UI].pixels);
    free(canvas[CANVAS_CITY].pixels);
    canvas[CANVAS_UI].pixels = (color_t *) malloc((size_t) width * height * sizeof(color_t));
    if (config_get(CONFIG_UI_ZOOM))
        canvas[CANVAS_CITY].pixels = (color_t *) malloc((size_t) width * height * 4 * sizeof(color_t));
    else {
        canvas[CANVAS_CITY].pixels = 0;
    }
#endif
    canvas[CANVAS_UI].width = width;
    canvas[CANVAS_UI].height = height;
    canvas[CANVAS_CITY].width = width * 2;
    canvas[CANVAS_CITY].height = height * 2;

    graphics_clear_screens();
    graphics_set_clip_rectangle(0, 0, width, height);
}
const void *graphics_canvas(canvas_type type) {
    if (!config_get(CONFIG_UI_ZOOM))
        return canvas[CANVAS_UI].pixels;

    return canvas[type].pixels;
}
void graphics_set_active_canvas(canvas_type type) {
    active_canvas = type;
    graphics_reset_clip_rectangle();
}
void graphics_set_custom_canvas(color_t *pixels, int width, int height) {
    canvas[CANVAS_CUSTOM].pixels = pixels;
    canvas[CANVAS_CUSTOM].width = width;
    canvas[CANVAS_CUSTOM].height = height;
    graphics_set_active_canvas(CANVAS_CUSTOM);
}
canvas_type graphics_get_canvas_type(void) {
    return active_canvas;
}

static void translate_clip(int dx, int dy) {
    clip_rectangle.x_start -= dx;
    clip_rectangle.x_end -= dx;
    clip_rectangle.y_start -= dy;
    clip_rectangle.y_end -= dy;
}
static void set_translation(int x, int y) {
    if (x != 0 || y != 0)
        graphics_renderer()->set_viewport(x, y, screen_width() - x, screen_height() - y);
    else
        graphics_renderer()->reset_viewport();
}

void graphics_in_dialog(void) {
    set_translation(screen_dialog_offset_x(), screen_dialog_offset_y());
}
void graphics_in_dialog_with_size(int width, int height)
{
    set_translation((screen_width() - width) / 2, (screen_height() - height) / 2);
}
void graphics_reset_dialog(void) {
    set_translation(0, 0);
}

void graphics_set_clip_rectangle(int x, int y, int width, int height) {
    graphics_renderer()->set_clip_rectangle(x, y, width, height);
}
void graphics_reset_clip_rectangle(void) {
    graphics_renderer()->reset_clip_rectangle();
}

static void set_clip_x(int x_offset, int width) {
    clip.clipped_pixels_left = 0;
    clip.clipped_pixels_right = 0;
    if (width <= 0
        || x_offset + width <= clip_rectangle.x_start
        || x_offset >= clip_rectangle.x_end) {
        clip.clip_x = CLIP_INVISIBLE;
        clip.visible_pixels_x = 0;
        return;
    }
    if (x_offset < clip_rectangle.x_start) {
        // clipped on the left
        clip.clipped_pixels_left = clip_rectangle.x_start - x_offset;
        if (x_offset + width <= clip_rectangle.x_end)
            clip.clip_x = CLIP_LEFT;
        else {
            clip.clip_x = CLIP_BOTH;
            clip.clipped_pixels_right = x_offset + width - clip_rectangle.x_end;
        }
    } else if (x_offset + width > clip_rectangle.x_end) {
        clip.clip_x = CLIP_RIGHT;
        clip.clipped_pixels_right = x_offset + width - clip_rectangle.x_end;
    } else {
        clip.clip_x = CLIP_NONE;
    }
    clip.visible_pixels_x = width - clip.clipped_pixels_left - clip.clipped_pixels_right;
}
static void set_clip_y(int y_offset, int height) {
    clip.clipped_pixels_top = 0;
    clip.clipped_pixels_bottom = 0;
    if (height <= 0
        || y_offset + height <= clip_rectangle.y_start
        || y_offset >= clip_rectangle.y_end) {
        clip.clip_y = CLIP_INVISIBLE;
    } else if (y_offset < clip_rectangle.y_start) {
        // clipped on the top
        clip.clipped_pixels_top = clip_rectangle.y_start - y_offset;
        if (y_offset + height <= clip_rectangle.y_end)
            clip.clip_y = CLIP_TOP;
        else {
            clip.clip_y = CLIP_BOTH;
            clip.clipped_pixels_bottom = y_offset + height - clip_rectangle.y_end;
        }
    } else if (y_offset + height > clip_rectangle.y_end) {
        clip.clip_y = CLIP_BOTTOM;
        clip.clipped_pixels_bottom = y_offset + height - clip_rectangle.y_end;
    } else {
        clip.clip_y = CLIP_NONE;
    }
    clip.visible_pixels_y = height - clip.clipped_pixels_top - clip.clipped_pixels_bottom;
}

const clip_info *graphics_get_clip_info(int x, int y, int width, int height, bool mirrored) {
    if (mirrored)
        set_clip_x(clip_rectangle.x_end - x - width, width);
    else
        set_clip_x(x, width);
    set_clip_y(y, height);
    if (clip.clip_x == CLIP_INVISIBLE || clip.clip_y == CLIP_INVISIBLE)
        clip.is_visible = 0;
    else {
        clip.is_visible = 1;
    }
    return &clip;
}

void graphics_save_to_buffer(int x, int y, int width, int height, color_t *buffer) {
    const clip_info *current_clip = graphics_get_clip_info(x, y, width, height);
    if (!current_clip->is_visible)
        return;
    int min_x = x + current_clip->clipped_pixels_left;
    int min_dy = current_clip->clipped_pixels_top;
    int max_dy = height - current_clip->clipped_pixels_bottom;
    for (int dy = min_dy; dy < max_dy; dy++) {
        memcpy(&buffer[dy * width], graphics_get_pixel(min_x, y + dy),
               sizeof(color_t) * current_clip->visible_pixels_x);
    }
}
void graphics_draw_from_buffer(int x, int y, int width, int height, const color_t *buffer) {
    const clip_info *current_clip = graphics_get_clip_info(x, y, width, height);
    if (!current_clip->is_visible)
        return;
    int min_x = x + current_clip->clipped_pixels_left;
    int min_dy = current_clip->clipped_pixels_top;
    int max_dy = height - current_clip->clipped_pixels_bottom;
    for (int dy = min_dy; dy < max_dy; dy++) {
        memcpy(graphics_get_pixel(min_x, y + dy), &buffer[dy * width],
               sizeof(color_t) * current_clip->visible_pixels_x);
    }
}

color_t *graphics_get_pixel(int x, int y) {
    if (active_canvas == CANVAS_UI)
        return &canvas[CANVAS_UI].pixels[(translation.y + y) * canvas[CANVAS_UI].width + translation.x + x];
    else {
        return &canvas[active_canvas].pixels[y * canvas[active_canvas].width + x];
    }
}

void graphics_clear_screen(canvas_type type) {
    graphics_renderer()->clear_screen();
}
void graphics_clear_city_viewport(void) {
    int x, y, width, height;
    city_view_get_unscaled_viewport(&x, &y, &width, &height);
    while (y < height) {
        auto b = graphics_get_pixel(0, y + TOP_MENU_HEIGHT);
        memset(b, 0, width * sizeof(color_t));
        y++;
    }
}
void graphics_clear_screens(void) {
    graphics_clear_screen(CANVAS_UI);
    if (config_get(CONFIG_UI_ZOOM))
        graphics_clear_screen(CANVAS_CITY);

}

void graphics_draw_line(int x_start, int x_end, int y_start, int y_end, color_t color)
{
    graphics_renderer()->draw_line(x_start, x_end, y_start, y_end, color);
}
void graphics_draw_vertical_line(int x, int y1, int y2, color_t color) {
    graphics_renderer()->draw_line(x, x, y1, y2, color);
}
void graphics_draw_horizontal_line(int x1, int x2, int y, color_t color) {
    graphics_renderer()->draw_line(x1, x2, y, y, color);
}
void graphics_draw_rect(int x, int y, int width, int height, color_t color) {
    graphics_renderer()->draw_rect(x, width, y, height, color);
}
void graphics_draw_inset_rect(int x, int y, int width, int height) {
    int x_end = x + width - 1;
    int y_end = y + height - 1;
    graphics_renderer()->draw_line(x, x_end, y, y, COLOR_INSET_DARK);
    graphics_renderer()->draw_line(x_end, x_end, y, y_end, COLOR_INSET_LIGHT);
    graphics_renderer()->draw_line(x, x_end, y_end, y_end, COLOR_INSET_LIGHT);
    graphics_renderer()->draw_line(x, x, y, y_end, COLOR_INSET_DARK);
}

void graphics_fill_rect(int x, int y, int width, int height, color_t color) {
    graphics_renderer()->fill_rect(x, width, y, height, color);
}
void graphics_shade_rect(int x, int y, int width, int height, int darkness) {
    color_t alpha = (0x11 * darkness) << COLOR_BITSHIFT_ALPHA;
    graphics_renderer()->fill_rect(x, width, y, height, alpha);
}

//////////////

int graphics_save_to_image(int image_id, int x, int y, int width, int height)
{
    return graphics_renderer()->save_image_from_screen(image_id, x, y, width, height);
}
void graphics_draw_from_image(int image_id, int x, int y)
{
    graphics_renderer()->draw_image_to_screen(image_id, x, y);
}