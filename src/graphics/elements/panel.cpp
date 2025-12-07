#include "panel.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "game/game.h"

void outer_panel_draw(vec2i pos, int width_blocks, int height_blocks) {
    int image_base = image_id_from_group(GROUP_DIALOG_BACKGROUND);
    int image_id;
    int image_y = 0;
    int y_add = 0;
    painter ctx = game.painter();
    for (int yy = 0; yy < height_blocks; yy++) {
        int image_x = 0;
        for (int xx = 0; xx < width_blocks; xx++) {
            if (yy == 0) {
                if (xx == 0)
                    image_id = 0;
                else if (xx < width_blocks - 1)
                    image_id = 1 + image_x++;
                else {
                    image_id = 11;
                }
                y_add = 0;
            } else if (yy < height_blocks - 1) {
                if (xx == 0)
                    image_id = 12 + image_y;
                else if (xx < width_blocks - 1)
                    image_id = 13 + image_y + image_x++;
                else {
                    image_id = 23 + image_y;
                }
                y_add = 12;
            } else {
                if (xx == 0)
                    image_id = 132;
                else if (xx < width_blocks - 1)
                    image_id = 133 + image_x++;
                else {
                    image_id = 143;
                }
                y_add = 0;
            }
            ctx.img_generic(image_base + image_id, pos + vec2i{16 * xx, 16 * yy});
            if (image_x >= 10) {
                image_x = 0;
            }
        }
        image_y += y_add;
        if (image_y >= 120)
            image_y = 0;
    }
}

/**
 * Draw outer panel with exact pixel size
 * Fills entire area with middle blocks, then overlays corners and edges with offset to match exact size
 */
void outer_panel_draw_exact(vec2i pos, vec2i size) {
    int image_base = image_id_from_group(GROUP_DIALOG_BACKGROUND);
    painter ctx = game.painter();

    // Calculate whole blocks and remainders
    int width_whole_blocks = size.x / 16;
    int height_whole_blocks = size.y / 16;
    int width_remainder = size.x % 16;
    int height_remainder = size.y % 16;

    // Ensure at least one block if size is very small
    if (width_whole_blocks == 0 && width_remainder > 0) {
        width_whole_blocks = 1;
        width_remainder = 0;
    }
    if (height_whole_blocks == 0 && height_remainder > 0) {
        height_whole_blocks = 1;
        height_remainder = 0;
    }

    // Fill entire area with middle blocks (where they fit completely)
    int image_y = 0;
    for (int yy = 0; yy < height_whole_blocks; yy++) {
        int image_x = 0;
        for (int xx = 0; xx < width_whole_blocks; xx++) {
            // Use middle block pattern (13 + image_y + image_x)
            int image_id = 13 + image_y + image_x++;
            ctx.img_generic(image_base + image_id, pos + vec2i{ 16 * xx, 16 * yy });
            if (image_x >= 10) {
                image_x = 0;
            }
        }
        image_y += 12;
        if (image_y >= 120) {
            image_y = 0;
        }
    }

    // Now overlay correct edge and corner blocks with offset to match exact size
    // Overlay top edge
    if (width_whole_blocks > 0) {
        int image_x = 0;
        for (int xx = 0; xx < width_whole_blocks; xx++) {
            int image_id;
            if (xx == 0) {
                image_id = 0; // Top left corner
            } else if (xx < width_whole_blocks - 1) {
                image_id = 1 + image_x++; // Top edge middle
                if (image_x >= 10)
                    image_x = 0;
            } else {
                if (width_remainder == 0) {
                    image_id = 11; // Top right corner
                } else {
                    image_id = 1 + image_x; // Top edge middle (will be clipped)
                }
            }

            if (width_remainder > 0 && xx == width_whole_blocks - 1) {
                // Last block on right - clip it
                int clip_x = pos.x + width_whole_blocks * 16 - width_remainder;
                ctx.img_generic(image_base + image_id, pos + vec2i{ 16 * xx, 0 });
            } else {
                ctx.img_generic(image_base + image_id, pos + vec2i{ 16 * xx, 0 });
            }
        }
    }

    // Overlay left edge
    if (height_whole_blocks > 0) {
        int current_image_y = 0;
        for (int yy = 1; yy < height_whole_blocks; yy++) {
            int image_id = 12 + current_image_y; // Left edge middle
            ctx.img_generic(image_base + image_id, pos + vec2i{ 0, 16 * yy });
            current_image_y += 12;
            if (current_image_y >= 120)
                current_image_y = 0;
        }
    }

    // Overlay bottom edge - start from bottom edge of window, draw blocks with offset
    if (height_whole_blocks > 0 && width_whole_blocks > 0) {
        int bottom_edge_y = pos.y + size.y; // Bottom edge of window
        int block_start_y = bottom_edge_y - 16; // Start drawing block one block size up

        int image_x = 0;
        for (int xx = 0; xx < width_whole_blocks; xx++) {
            int image_id;
            if (xx == 0) {
                image_id = 132; // Bottom left corner
            } else if (xx < width_whole_blocks - 1) {
                image_id = 133 + image_x++; // Bottom edge middle
                if (image_x >= 10)
                    image_x = 0;
            } else {
                if (width_remainder == 0) {
                    image_id = 143; // Bottom right corner
                } else {
                    image_id = 133 + image_x; // Bottom edge middle
                }
            }

            if (height_remainder > 0) {
                // Clip the block to match exact window height
                int clip_y = bottom_edge_y - height_remainder;
                int clip_height = height_remainder;
                ctx.img_generic(image_base + image_id, vec2i{ pos.x + 16 * xx, block_start_y });
            } else {
                // No remainder, draw normally
                ctx.img_generic(image_base + image_id, vec2i{ pos.x + 16 * xx, block_start_y });
            }
        }
    }

    // Overlay bottom-left corner
    if (height_whole_blocks > 0 && width_whole_blocks > 0) {
        int yy = height_whole_blocks - 1;
        if (height_remainder == 0) {
            int image_id = 132; // Bottom left corner
            ctx.img_generic(image_base + image_id, pos + vec2i{ 0, 16 * yy });
        }
    }

    // Overlay bottom-right corner - start from bottom-right corner of window
    if (width_whole_blocks > 0 && height_whole_blocks > 0) {
        int right_edge_x = pos.x + size.x; // Right edge of window
        int bottom_edge_y = pos.y + size.y; // Bottom edge of window
        int block_start_x = right_edge_x - 16; // Start one block size to the left
        int block_start_y = bottom_edge_y - 16; // Start one block size up

        if (width_remainder > 0 && height_remainder > 0) {
            // Clip the corner block to match exact window size
            int clip_x = right_edge_x - width_remainder;
            int clip_y = bottom_edge_y - height_remainder;
            ctx.img_generic(image_base + 143, vec2i{ block_start_x, block_start_y }); // Bottom right corner
        } else {
            // No remainders, draw bottom-right corner normally
            ctx.img_generic(image_base + 143, vec2i{ block_start_x, block_start_y });
        }
    }

    // Overlay right edge - draw after everything else, start from right edge of window
    if (width_whole_blocks > 0 && height_whole_blocks > 0) {
        int right_edge_x = pos.x + size.x; // Right edge of window
        int block_start_x = right_edge_x - 16; // Start drawing block one block size to the left
        
        int current_image_y = 0;
        for (int yy = 0; yy < height_whole_blocks; yy++) {
            int image_id;
            if (yy == 0) {
                image_id = 11; // Top right corner
            } else if (yy < height_whole_blocks - 1) {
                image_id = 23 + current_image_y; // Right edge middle
                current_image_y += 12;
                if (current_image_y >= 120)
                    current_image_y = 0;
            } else {
                if (height_remainder == 0) {
                    image_id = 143; // Bottom right corner
                } else {
                    image_id = 23 + current_image_y; // Right edge middle
                }
            }

            if (width_remainder > 0) {
                // Clip the block to match exact window width
                int clip_x = right_edge_x - width_remainder;
                int clip_width = width_remainder;
                ctx.img_generic(image_base + image_id, vec2i{ block_start_x, pos.y + 16 * yy });
            } else {
                // No remainder, draw normally
                ctx.img_generic(image_base + image_id, vec2i{ block_start_x, pos.y + 16 * yy });
            }
        }
    }
}

void unbordered_panel_draw(int x, int y, int width_blocks, int height_blocks) {
    int image_base = image_id_from_group(GROUP_DIALOG_BACKGROUND);
    int image_y = 0;
    painter ctx = game.painter();
    for (int yy = 0; yy < height_blocks; yy++) {
        int image_x = 0;
        for (int xx = 0; xx < width_blocks; xx++) {
            int image_id = 13 + image_y + image_x++;
            ctx.img_generic(image_base + image_id, vec2i{x + 16 * xx, y + 16 * yy});
            if (image_x >= 10)
                image_x = 0;
        }
        image_y += 12;
        if (image_y >= 120)
            image_y = 0;
    }
}
void inner_panel_draw(vec2i pos, vec2i size) {
    int image_base = image_id_from_group(GROUP_SUNKEN_TEXTBOX_BACKGROUND);
    int image_y = 0;
    int y_add = 0;
    painter ctx = game.painter();
    for (int yy = 0; yy < size.y; yy++) {
        int image_x = 0;
        for (int xx = 0; xx < size.x; xx++) {
            int image_id;
            if (yy == 0) {
                if (xx == 0)
                    image_id = 0;
                else if (xx < size.x - 1)
                    image_id = 1 + image_x++;
                else {
                    image_id = 6;
                }
                y_add = 0;
            } else if (yy < size.y - 1) {
                if (xx == 0)
                    image_id = 7 + image_y;
                else if (xx < size.x - 1)
                    image_id = 8 + image_y + image_x++;
                else {
                    image_id = 13 + image_y;
                }
                y_add = 7;
            } else {
                if (xx == 0)
                    image_id = 42;
                else if (xx < size.x - 1)
                    image_id = 43 + image_x++;
                else {
                    image_id = 48;
                }
                y_add = 0;
            }
            ctx.img_generic(image_base + image_id, pos + vec2i{16 * xx, 16 * yy});
            if (image_x >= 5)
                image_x = 0;
        }
        image_y += y_add;
        if (image_y >= 35)
            image_y = 0;
    }
}

void small_panel_draw(vec2i pos, int width_blocks, int type) {
    int image_base = image_id_from_group(GROUP_PANEL_BUTTON);
    painter ctx = game.painter();
    for (int i = 0; i < width_blocks; i++) {
        int image_id;
        if (i == 0) { image_id = 3 * type + 40; }
        else if (i < width_blocks - 1) { image_id = 3 * type + 41; }
        else { image_id = 3 * type + 42; }
        ctx.img_generic(image_base + image_id, vec2i{pos.x + 16 * i, pos.y});
    }
}

void small_panel_draw_colored(vec2i pos, int width_blocks, int type, uint32_t mask) {
    painter ctx = game.painter();
    int image_base = image_id_from_group(GROUP_PANEL_BUTTON);
    for (int i = 0; i < width_blocks; i++) {
        int image_id;
        if (i == 0) { image_id = 3 * type + 40; }
        else if (i < width_blocks - 1) { image_id = 3 * type + 41; }
        else { image_id = 3 * type + 42; }
        ctx.img_generic(image_base + image_id, vec2i{pos.x + 16 * i, pos.y}, mask);
    }
}

void large_label_draw(int x, int y, int width_blocks, int type) {
    painter ctx = game.painter();
    int image_base = image_id_from_group(GROUP_PANEL_BUTTON);
    for (int i = 0; i < width_blocks; i++) {
        int image_id;
        if (i == 0)
            image_id = 3 * type;
        else if (i < width_blocks - 1)
            image_id = 3 * type + 1;
        else
            image_id = 3 * type + 2;
        ctx.img_generic(image_base + image_id, vec2i{x + 16 * i, y});
    }
}
