#include "building/construction/build_planner.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"

#include <cmath>

namespace ghost_draw {

    void draw_building_ghost(painter& ctx, int image_id, vec2i pixel, color color_mask) {
        auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
        command.location = SOURCE_LOCATION;
    }

    void draw_ghost_overlay(painter& ctx, int image_id, vec2i pixel) {
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = COLOR_MASK_GREEN;
        command.scale = 1.f;
        command.location = SOURCE_LOCATION;
    }

    void draw_from_below(painter& ctx, int image_id, vec2i pixel, color color_mask) {
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_from_below);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
        command.scale = 1.f;
        command.location = SOURCE_LOCATION;
    }

    void draw_overlay_tile(painter& ctx, int image_id, vec2i pixel, color color_mask, float scale) {
        auto& command = ImageDraw::create_command(ctx, render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
        command.scale = scale;
        command.location = SOURCE_LOCATION;
    }

    void draw_ground_tile(painter& ctx, vec2i pixel, color color_mask) {
        auto& command = ImageDraw::create_command(ctx, render_command_t::ert_generic);
        command.layer = render_command_t::layer_ground;
        command.image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED);
        command.pixel = pixel;
        command.mask = color_mask;
        command.scale = 1.f;
        command.location = SOURCE_LOCATION;
    }

    void draw_ground_isometric(painter& ctx, int image_id, vec2i pixel, color color_mask) {
        const image_t* img = image_get(image_id);
        if (!img) {
            return;
        }
        const int ydiff = img->isometric_size() * HALF_TILE_HEIGHT_PIXELS;
        auto& base = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        base.layer = render_command_t::layer_ground;
        base.image_id = image_id;
        base.pixel = pixel + vec2i{0, ydiff};
        base.use_sort_pixel = true;
        base.sort_pixel = pixel;
        base.mask = color_mask;
        base.location = SOURCE_LOCATION;

        auto& top = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_top);
        top.layer = render_command_t::layer_ground;
        top.image_id = image_id;
        top.pixel = pixel;
        top.use_sort_pixel = true;
        top.sort_pixel = pixel;
        top.mask = color_mask;
        top.location = SOURCE_LOCATION;
    }

    void draw_partially_blocked(painter& ctx, int fully_blocked, const blocked_tile_vec& blocked_tiles) {
        for (auto& tile : blocked_tiles) {
            vec2i pixel = g_camera.lookup_tile_to_pixel(tile.tile);
            draw_ground_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
        }
    }
    void draw_partially_blocked(painter& ctx, int fully_blocked, const std::vector<blocked_tile>& blocked_tiles) {
        for (auto& tile : blocked_tiles) {
            vec2i pixel = g_camera.lookup_tile_to_pixel(tile.tile);
            draw_ground_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
        }
    }

    vec2i end_pixel(const build_planner& planner) {
        return g_camera.lookup_tile_to_pixel(planner.end);
    }

    vec2i pixel_coord_offset(const build_planner& planner, int row, int column) {
        vec2i view_tile = g_camera.lookup_tile_to_pixel(planner.end);
        if (view_tile.x == 0 && view_tile.y == 0) {
            view_tile = g_camera.selected_tile;
        }
        const int x_offset = column - planner.pivot.x;
        const int y_offset = row - planner.pivot.y;
        return {view_tile.x + x_offset * 30 - y_offset * 30, view_tile.y + x_offset * 15 + y_offset * 15};
    }

    void draw_tile_graphics_array(const build_planner& planner, painter& ctx) {
        // go through the tiles DIAGONALLY to render footprint and top correctly
        for (int dg_y = 0; dg_y < planner.size.y + planner.size.x - 1; dg_y++) {
            for (int dg_x = fmax(0, dg_y - planner.size.y + 1); dg_x < planner.size.x && dg_x < dg_y + 1; dg_x++) {
                // extract proper row and column index from the mess above
                int row = dg_y - dg_x;
                int column = dg_x;

                int image_id = planner.tile_graphics(row, column);
                if (image_id > 0) {
                    auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
                    command.image_id = image_id;
                    command.pixel = pixel_coord_offset(planner, row, column);
                    command.mask = COLOR_MASK_GREEN;
                    command.location = SOURCE_LOCATION;
                } else if (image_id < 0) {
                    auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                    command.image_id = image_id_from_group(GROUP_TERRAIN_BLACK);
                    command.pixel = pixel_coord_offset(planner, row, column);
                    command.mask = COLOR_MASK_GREEN;
                    command.location = SOURCE_LOCATION;
                }
            }
        }
    }

} // namespace ghost_draw
