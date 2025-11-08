#include "graphics/graphics.h"

#include "graphics/screen.h"
#include "platform/renderer.h"
#include "graphics/font.h"
#include "graphics/view/view.h"
#include "graphics/image_desc.h"
#include "core/profiler.h"
#include "game/game.h"

#ifdef __vita__
#include <vita2d.h>
#endif

#ifdef __vita__
extern vita2d_texture* tex_buffer_ui;
extern vita2d_texture* tex_buffer_city;
#endif

static void set_translation(int x, int y) {
    if (x != 0 || y != 0) {
        g_render.set_viewport(x, y, screen_width() - x, screen_height() - y);
    } else {
        g_render.reset_viewport();
    }
}

void graphics_set_to_dialog() {
    set_translation(screen_dialog_offset_x(), screen_dialog_offset_y());
}
void graphics_in_dialog_with_size(int width, int height) {
    set_translation((screen_width() - width) / 2, (screen_height() - height) / 2);
}
void graphics_reset_dialog() {
    set_translation(0, 0);
}

void graphics_set_clip_rectangle(vec2i pos, vec2i size) {
    g_render.set_clip_rectangle(pos, size.x, size.y);
}

bool graphics_inside_clip_rectangle(vec2i pos) {
    return g_render.inside_clip_rectangle(pos);
}

rect graphics_clip_rectangle() {
    return g_render.clip_rectangle();
}

void graphics_reset_clip_rectangle() {
    g_render.reset_clip_rectangle();
}

void graphics_draw_inset_rect(vec2i start, vec2i size) {
    vec2i end = start + size - vec2i{1, 1};
    g_render.draw_line(start, vec2i{end.x, start.y}, COLOR_INSET_DARK);
    g_render.draw_line(vec2i{end.x, start.y}, end, COLOR_INSET_LIGHT);
    g_render.draw_line(vec2i{start.x, end.y}, end, COLOR_INSET_LIGHT);
    g_render.draw_line(start, vec2i{start.x, end.y}, COLOR_INSET_DARK);
}

int graphics_save_to_texture(int image_id, vec2i pos, vec2i size) {
    return g_render.save_texture_from_screen(image_id, pos, size.x, size.y);
}

void graphics_delete_saved_texture(int image_id) {
    g_render.delete_saved_texture(image_id);
}

void graphics_clear_saved_texture(int image_id, color clr) {
    g_render.clear_saved_texture(image_id, clr);
}

void graphics_draw_from_texture(int image_id, vec2i pos, vec2i size) {
    g_render.draw_saved_texture_to_screen(image_id, pos.x, pos.y, size.x, size.y);
}

static int get_visible_footprint_pixels_per_row(int tiles, int width, int height, int row) {
    int base_height = tiles * TILE_HEIGHT_PIXELS;
    int footprint_row = row - (height - base_height);
    if (footprint_row < 0)
        return 0;
    else if (footprint_row < tiles * HALF_TILE_HEIGHT_PIXELS)
        return 2 + 4 * footprint_row;
    else
        return 2 + 4 * (base_height - 1 - footprint_row);
}

// static void draw_modded_footprint(int image_id, int x, int y, color color) {
//     const image *img = image_get(image_id);
//     const color *data = image_data(image_id);
//     if (!data)
//         return;
//     int tiles = (img->width + 2) / (FOOTPRINT_WIDTH + 2);
//     int y_top_offset = img->height - FOOTPRINT_HEIGHT * tiles;
//     y -= y_top_offset + FOOTPRINT_HALF_HEIGHT * tiles - FOOTPRINT_HALF_HEIGHT;
//     const clip_info *clip = graphics_get_clip_info(x, y + y_top_offset, img->width,
//                                                    img->height - y_top_offset);
//     if (!clip->is_visible)
//         return;
//     data += img->width * (clip->clipped_pixels_top + y_top_offset);
//     for (int _y = clip->clipped_pixels_top + y_top_offset; _y < img->height - clip->clipped_pixels_bottom; _y++) {
//         int visible_pixels_per_row = get_visible_footprint_pixels_per_row(tiles, img->width, img->height, _y);
//         int x_start = (img->width - visible_pixels_per_row) / 2;
//         int x_max = img->width - x_start;
//         if (x_start < clip->clipped_pixels_left)
//             x_start = clip->clipped_pixels_left;
//
//         if (x_max > img->width - clip->clipped_pixels_right)
//             x_max = img->width - clip->clipped_pixels_right;
//
//         if (x_start >= x_max) {
//             data += img->width;
//             continue;
//         }
//         color *dst = graphics_get_pixel(x + x_start, y + _y);
//         data += x_start;
//         if (color && color != COLOR_MASK_NONE) {
//             for (int _x = x_start; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data & color;
//
//                 data++;
//             }
//         } else {
//             for (int _x = x_start; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data;
//
//                 data++;
//             }
//         }
//         data += img->width - x_max;
//     }
// }
// static void draw_modded_top(int image_id, int x, int y, color color) {
//     const image *img = image_get(image_id);
//     const color *data = image_data(image_id);
//     if (!data)
//         return;
//     int tiles = (img->width + 2) / (FOOTPRINT_WIDTH + 2);
//     int y_top_offset = img->height - FOOTPRINT_HEIGHT * tiles;
//     y_top_offset += FOOTPRINT_HALF_HEIGHT * tiles - FOOTPRINT_HALF_HEIGHT;
//     y -= y_top_offset;
//     int height = img->height - FOOTPRINT_HALF_HEIGHT * tiles;
//     const clip_info *clip = graphics_get_clip_info(x, y, img->width, height);
//     if (!clip->is_visible)
//         return;
//     data += img->width * clip->clipped_pixels_top;
//     for (int _y = clip->clipped_pixels_top; _y < height - clip->clipped_pixels_bottom; _y++) {
//         int visible_pixels_per_row = get_visible_footprint_pixels_per_row(tiles, img->width, img->height, _y);
//         int half_width = img->width / 2;
//         int half_visible_pixels = visible_pixels_per_row / 2;
//         int x_start = clip->clipped_pixels_left;
//         if (x_start < half_width) {
//             color *dst = graphics_get_pixel(x + x_start, y + _y);
//             int x_max = half_width - half_visible_pixels;
//             if (x_start > x_max)
//                 x_start = x_max;
//
//             data += x_start;
//             int half_image_only = 0;
//             if (img->width - clip->clipped_pixels_right < x_max) {
//                 x_max = img->width - clip->clipped_pixels_right;
//                 half_image_only = 1;
//             }
//             if (color && color != COLOR_MASK_NONE) {
//                 for (int _x = x_start; _x < x_max; _x++, dst++) {
//                     color alpha = *data & COLOR_CHANNEL_ALPHA;
//                     if (alpha == ALPHA_OPAQUE)
//                         *dst = *data & color;
//                     else if (alpha != ALPHA_TRANSPARENT)
//                         *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA) & color;
//
//                     data++;
//                 }
//             } else {
//                 for (int _x = x_start; _x < x_max; _x++, dst++) {
//                     color alpha = *data & COLOR_CHANNEL_ALPHA;
//                     if (alpha == ALPHA_OPAQUE)
//                         *dst = *data;
//                     else if (alpha != ALPHA_TRANSPARENT)
//                         *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA);
//
//                     data++;
//                 }
//             }
//             if (half_image_only) {
//                 data += clip->clipped_pixels_right;
//                 continue;
//             }
//             data += half_width + half_visible_pixels - x_max;
//             x_start = half_width + half_visible_pixels;
//         } else {
//             x_start = half_width + half_visible_pixels;
//             if (x_start < clip->clipped_pixels_left)
//                 x_start = clip->clipped_pixels_left;
//
//             data += x_start;
//         }
//         int x_max = img->width - clip->clipped_pixels_right;
//         color *dst = graphics_get_pixel(x + x_start, y + _y);
//         if (color && color != COLOR_MASK_NONE) {
//             for (int _x = x_start; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data & color;
//                 else if (alpha != ALPHA_TRANSPARENT)
//                     *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA) & color;
//
//                 data++;
//             }
//         } else {
//             for (int _x = x_start; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data;
//                 else if (alpha != ALPHA_TRANSPARENT)
//                     *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA);
//
//                 data++;
//             }
//         }
//         if (x_start > x_max)
//             data -= x_start - x_max;
//
//         data += clip->clipped_pixels_right;
//     }
// }
// static void draw_modded_image(const image *img, const color *data, int x, int y, color color) {
//     const clip_info *clip = graphics_get_clip_info(x, y, img->width, img->height);
//     if (!clip->is_visible)
//         return;
//     data += img->width * clip->clipped_pixels_top;
//     for (int _y = clip->clipped_pixels_top; _y < img->height - clip->clipped_pixels_bottom; _y++) {
//         data += clip->clipped_pixels_left;
//         color *dst = graphics_get_pixel(x + clip->clipped_pixels_left, y + _y);
//         int x_max = img->width - clip->clipped_pixels_right;
//         if (color && color != COLOR_MASK_NONE) {
//             for (int _x = clip->clipped_pixels_left; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data & color;
//                 else if (alpha != ALPHA_TRANSPARENT)
//                     *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA) & color;
//                 data++;
//             }
//         } else {
//             for (int _x = clip->clipped_pixels_left; _x < x_max; _x++, dst++) {
//                 color alpha = *data & COLOR_CHANNEL_ALPHA;
//                 if (alpha == ALPHA_OPAQUE)
//                     *dst = *data;
//                 else if (alpha != ALPHA_TRANSPARENT)
//                     *dst = COLOR_BLEND_ALPHA_TO_OPAQUE(*data, *dst, alpha >> COLOR_BITSHIFT_ALPHA);
//                 data++;
//             }
//         }
//         data += clip->clipped_pixels_right;
//     }
// }
//
// static void draw_uncompressed(const image *img, const color *data, int x, int y, color color, draw_type type) {
////    if (image_is_external(image_id)) {
////        image_load_external_data(image_id);
////    } else if ((img->atlas.id >> IMAGE_ATLAS_BIT_OFFSET) == ATLAS_UNPACKED_EXTRA_ASSET) {
////        assets_load_unpacked_asset(image_id);
////    }
//    graphics_renderer()->draw_image(img, x, y, color, 1.0f);
//}
// static void draw_compressed(const image *img, const color *data, int x, int y, int height) {
////    bool mirr = (img->offset_mirror != 0);
////    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, img->width, height, mirr);
////    if (!clip->is_visible)
////        return;
////    int unclipped = clip->clip_x == CLIP_NONE;
////
////    for (int y = 0; y < height - clip->clipped_pixels_bottom; y++) {
////        int x = 0;
////        while (x < img->width) {
////            color b = *data;
////            data++;
////            if (b == 255) {
////                // transparent pixels to skip
////                x += *data;
////                data++;
////            } else if (y < clip->clipped_pixels_top) {
////                data += b;
////                x += b;
////            } else {
////                // number of concrete pixels
////                const color *pixels = data;
////                data += b;
////                color *dst;
////                if (mirr)
////                    dst = graphics_get_pixel(x_offset + img->width - x - b, y_offset + y);
////                else
////                    dst = graphics_get_pixel(x_offset + x, y_offset + y);
////                if (unclipped) {
////                    x += b;
////                    if (mirr)
////                        for (int px = 0; px < b; px++) {
////                            int pcorr = b - px - 1;
////                            memcpy(dst + px, pixels + pcorr, sizeof(color));
////                        }
////                    else
////                        memcpy(dst, pixels, b * sizeof(color));
////                } else {
////                    if (mirr)
////                        int a = 3565;
////
////                    while (b) {
////                        if (x >= clip->clipped_pixels_left && x < img->width - clip->clipped_pixels_right)
////                            *dst = *pixels;
////
////                        dst++;
////                        x++;
////                        pixels++;
////                        b--;
////                    }
////                }
////            }
////        }
////    }
////    graphics_renderer()->draw_isometric_top(img, x, y, color, 1.0f);
//}
// static void draw_compressed_set(const image *img, const color *data, int x_offset, int y_offset, int height,
// color color) {
////    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, img->width, height);
////    if (!clip->is_visible)
////        return;
////    int unclipped = clip->clip_x == CLIP_NONE;
////
////    for (int y = 0; y < height - clip->clipped_pixels_bottom; y++) {
////        int x = 0;
////        while (x < img->width) {
////            color b = *data;
////            data++;
////            if (b == 255) {
////                // transparent pixels to skip
////                x += *data;
////                data++;
////            } else if (y < clip->clipped_pixels_top) {
////                data += b;
////                x += b;
////            } else {
////                data += b;
////                color *dst = graphics_get_pixel(x_offset + x, y_offset + y);
////                if (unclipped) {
////                    x += b;
////                    while (b) {
////                        *dst = color;
////                        dst++;
////                        b--;
////                    }
////                } else {
////                    while (b) {
////                        if (x >= clip->clipped_pixels_left && x < img->width - clip->clipped_pixels_right)
////                            *dst = color;
////
////                        dst++;
////                        x++;
////                        b--;
////                    }
////                }
////            }
////        }
////    }
//}
// static void draw_compressed_and(const image *img, const color *data, int x_offset, int y_offset, int height,
// color color) {
//    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, img->width, height);
//    if (!clip->is_visible)
//        return;
//    int unclipped = clip->clip_x == CLIP_NONE;
//
//    for (int y = 0; y < height - clip->clipped_pixels_bottom; y++) {
//        int x = 0;
//        while (x < img->width) {
//            color b = *data;
//            data++;
//            if (b == 255) {
//                // transparent pixels to skip
//                x += *data;
//                data++;
//            } else if (y < clip->clipped_pixels_top) {
//                data += b;
//                x += b;
//            } else {
//                // number of concrete pixels
//                const color *pixels = data;
//                data += b;
//                color *dst = graphics_get_pixel(x_offset + x, y_offset + y);
//                if (unclipped) {
//                    x += b;
//                    while (b) {
//                        *dst = *pixels & color;
//                        dst++;
//                        pixels++;
//                        b--;
//                    }
//                } else {
//                    while (b) {
//                        if (x >= clip->clipped_pixels_left && x < img->width - clip->clipped_pixels_right)
//                            *dst = *pixels & color;
//
//                        dst++;
//                        x++;
//                        pixels++;
//                        b--;
//                    }
//                }
//            }
//        }
//    }
//}
// static void draw_compressed_blend(const image *img, const color *data, int x_offset, int y_offset, int height,
// color color) {
//    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, img->width, height);
//    if (!clip->is_visible)
//        return;
//    int unclipped = clip->clip_x == CLIP_NONE;
//
//    for (int y = 0; y < height - clip->clipped_pixels_bottom; y++) {
//        int x = 0;
//        while (x < img->width) {
//            color b = *data;
//            data++;
//            if (b == 255) {
//                // transparent pixels to skip
//                x += *data;
//                data++;
//            } else if (y < clip->clipped_pixels_top) {
//                data += b;
//                x += b;
//            } else {
//                data += b;
//                color *dst = graphics_get_pixel(x_offset + x, y_offset + y);
//                if (unclipped) {
//                    x += b;
//                    while (b) {
//                        *dst &= color;
//                        dst++;
//                        b--;
//                    }
//                } else {
//                    while (b) {
//                        if (x >= clip->clipped_pixels_left && x < img->width - clip->clipped_pixels_right)
//                            *dst &= color;
//
//                        dst++;
//                        x++;
//                        b--;
//                    }
//                }
//            }
//        }
//    }
//}
// static void draw_compressed_blend_alpha(const image *img, const color *data, int x_offset, int y_offset, int
// height, color color) {
//    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, img->width, height);
//    if (!clip->is_visible)
//        return;
//    color alpha = COLOR_COMPONENT(color, COLOR_BITSHIFT_ALPHA);
//    if (!alpha)
//        return;
//    if (alpha == 255) {
//        draw_compressed_set(img, data, x_offset, y_offset, height, color);
//        return;
//    }
//    color alpha_dst = 256 - alpha;
//    color src_rb = (color & 0xff00ff) * alpha;
//    color src_g = (color & 0x00ff00) * alpha;
//    int unclipped = clip->clip_x == CLIP_NONE;
//
//    for (int y = 0; y < height - clip->clipped_pixels_bottom; y++) {
//        int x = 0;
//        color *dst = graphics_get_pixel(x_offset, y_offset + y);
//        while (x < img->width) {
//            color b = *data;
//            data++;
//            if (b == 255) {
//                // transparent pixels to skip
//                x += *data;
//                dst += *data;
//                data++;
//            } else if (y < clip->clipped_pixels_top) {
//                data += b;
//                x += b;
//                dst += b;
//            } else {
//                data += b;
//                if (unclipped) {
//                    x += b;
//                    while (b) {
//                        color d = *dst;
//                        *dst = (((src_rb + (d & 0xff00ff) * alpha_dst) & 0xff00ff00) |
//                                ((src_g + (d & 0x00ff00) * alpha_dst) & 0x00ff0000)) >> 8;
//                        b--;
//                        dst++;
//                    }
//                } else {
//                    while (b) {
//                        if (x >= clip->clipped_pixels_left && x < img->width - clip->clipped_pixels_right) {
//                            color d = *dst;
//                            *dst = (((src_rb + (d & 0xff00ff) * alpha_dst) & 0xff00ff00) |
//                                    ((src_g + (d & 0x00ff00) * alpha_dst) & 0x00ff0000)) >> 8;
//                        }
//                        dst++;
//                        x++;
//                        b--;
//                    }
//                }
//            }
//        }
//    }
//}
// static void draw_footprint_simple(const color *src, int x, int y) {
//    memcpy(graphics_get_pixel(x + 28, y + 0), &src[0], 2 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 26, y + 1), &src[2], 6 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 24, y + 2), &src[8], 10 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 22, y + 3), &src[18], 14 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 20, y + 4), &src[32], 18 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 18, y + 5), &src[50], 22 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 16, y + 6), &src[72], 26 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 14, y + 7), &src[98], 30 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 12, y + 8), &src[128], 34 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 10, y + 9), &src[162], 38 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 8, y + 10), &src[200], 42 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 6, y + 11), &src[242], 46 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 4, y + 12), &src[288], 50 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 2, y + 13), &src[338], 54 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 0, y + 14), &src[392], 58 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 0, y + 15), &src[450], 58 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 2, y + 16), &src[508], 54 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 4, y + 17), &src[562], 50 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 6, y + 18), &src[612], 46 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 8, y + 19), &src[658], 42 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 10, y + 20), &src[700], 38 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 12, y + 21), &src[738], 34 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 14, y + 22), &src[772], 30 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 16, y + 23), &src[802], 26 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 18, y + 24), &src[828], 22 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 20, y + 25), &src[850], 18 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 22, y + 26), &src[868], 14 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 24, y + 27), &src[882], 10 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 26, y + 28), &src[892], 6 * sizeof(color));
//    memcpy(graphics_get_pixel(x + 28, y + 29), &src[898], 2 * sizeof(color));
//}
// static void draw_footprint_tile(const color *data, int x_offset, int y_offset, color color_mask) {
//    if (!color_mask)
//        color_mask = COLOR_MASK_NONE;
//
//    const clip_info *clip = graphics_get_clip_info(x_offset, y_offset, FOOTPRINT_WIDTH, FOOTPRINT_HEIGHT);
//    if (data == nullptr || !clip->is_visible)
//        return;
//    // If the current tile neither clipped nor color masked, just draw it normally
//    if (clip->clip_y == CLIP_NONE && clip->clip_x == CLIP_NONE && color_mask == COLOR_MASK_NONE) {
//        draw_footprint_simple(data, x_offset, y_offset);
//        return;
//    }
//    int clip_left = clip->clip_x == CLIP_LEFT || clip->clip_x == CLIP_BOTH;
//    int clip_right = clip->clip_x == CLIP_RIGHT || clip->clip_x == CLIP_BOTH;
//    const color *src = &data[FOOTPRINT_OFFSET_PER_HEIGHT[clip->clipped_pixels_top]];
//    for (int y = clip->clipped_pixels_top; y < clip->clipped_pixels_top + clip->visible_pixels_y; y++) {
//        int x_start = FOOTPRINT_X_START_PER_HEIGHT[y];
//        int x_max = 58 - x_start * 2;
//        int x_pixel_advance = 0;
//        if (clip_left) {
//            if (clip->clipped_pixels_left + clip->visible_pixels_x < x_start) {
//                src += x_max;
//                continue;
//            }
//            if (clip->clipped_pixels_left > x_start) {
//                int pixels_to_reduce = clip->clipped_pixels_left - x_start;
//                if (pixels_to_reduce >= x_max) {
//                    src += x_max;
//                    continue;
//                }
//                src += pixels_to_reduce;
//                x_max -= pixels_to_reduce;
//                x_start = clip->clipped_pixels_left;
//            }
//        }
//        if (clip_right) {
//            int clip_x = 58 - clip->clipped_pixels_right;
//            if (clip_x < x_start) {
//                src += x_max;
//                continue;
//            }
//            if (x_start + x_max > clip_x) {
//                int temp_x_max = clip_x - x_start;
//                x_pixel_advance = x_max - temp_x_max;
//                x_max = temp_x_max;
//            }
//        }
//        color *buffer = graphics_get_pixel(x_offset + x_start, y_offset + y);
//        if (color_mask == COLOR_MASK_NONE) {
//            memcpy(buffer, src, x_max * sizeof(color));
//            src += x_max + x_pixel_advance;
//        } else {
//            for (int x = 0; x < x_max; x++, buffer++, src++) {
//                *buffer = *src & color_mask;
//            }
//            src += x_pixel_advance;
//        }
//    }
//}

static const color* tile_data(const color* data, int index) {
    return &data[900 * index];
}

static void draw_footprint_size_any(int image_id, vec2i pos, int size, color color_mask, float scale) {
    //    const color *data = image_data(image_id);
    const image_t* img = image_get(image_id);

    // The offsets alternate very annoyingly.
    // The y offsets grow by 15 each "batch"
    // while for each "batch" there are multiple
    // x offsets, 60p apart from each other,
    // symmetric around the x axis.
    // What an absolute mess!
    int index = 0;
    painter ctx = game.painter();
    for (int k = 0; k < (size * 2) - 1; k++) {
        int k_limit = k;
        if (k >= size - 1)
            k_limit = 2 * size - 2 - k;

        for (int j = -30 * k_limit; j <= 30 * k_limit; j += 60) {
            int x_offset = j;
            int y_offset = k * 15;

            //            draw_footprint_tile(tile_data(data, index++), x + x_offset, y + y_offset, color_mask);
            ctx.draw_image(img, pos, color_mask, scale);
        }
    }
}