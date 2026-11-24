#include "widget/city/placement_preview.h"
#include "city/city_finance.h"

#include "building/building_bridge.h"
#include "building/construction/build_planner.h"
#include "city/city.h"
#include "core/profiler.h"
#include "game/game_config.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "grid/bridge.h"
#include "grid/orientation.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"

namespace {

    void draw_bridge(tile2i tile, vec2i pixel, int type, painter& ctx) {
        const bool is_ship = (type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        int length, direction;
        int end_grid_offset = map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction, is_ship);

        int dir = direction - map_view_orientation();
        if (dir < 0)
            dir += 8;

        const int min_length = bridge_span_min_length(is_ship);
        const int max_length = bridge_span_max_length(is_ship);

        bool blocked = false;
        if (length < min_length || length > max_length)
            blocked = true;
        else if (!end_grid_offset)
            blocked = true;

        if (city_finance().is_out_of_money())
            blocked = true;

        int x_delta, y_delta;
        switch (dir) {
        case DIR_0_TOP_RIGHT:
            x_delta = 29;
            y_delta = -15;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x_delta = 29;
            y_delta = 15;
            break;
        case DIR_4_BOTTOM_LEFT:
            x_delta = -29;
            y_delta = 15;
            break;
        case DIR_6_TOP_LEFT:
            x_delta = -29;
            y_delta = -15;
            break;
        default:
            return;
        }
        if (blocked) {
            ghost_draw::draw_ground_tile(ctx, pixel, length > 0 ? COLOR_MASK_GREEN : COLOR_MASK_RED);
            if (length > 1)
                ghost_draw::draw_ground_tile(ctx, pixel + vec2i(x_delta * (length - 1), y_delta * (length - 1)),
                  COLOR_MASK_RED);

        } else {
            if (dir == DIR_0_TOP_RIGHT || dir == DIR_6_TOP_LEFT) {
                for (int i = length - 1; i >= 0; i--) {
                    int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                    city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id,
                      COLOR_MASK_GREEN);
                }
            } else {
                for (int i = 0; i < length; i++) {
                    int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                    city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id,
                      COLOR_MASK_GREEN);
                }
            }
        }
    }

    void draw_road_access_marker(build_planner& planner, painter& ctx) {
        if (!game_features::gameui_show_building_road_access.to_bool()) {
            return;
        }
        if (!building_type_ghost_road_access(planner.build_type)) {
            return;
        }

        const auto& params = building_static_params::get(planner.build_type);
        const int bsize = params.building_size > 0 ? params.building_size : planner.size.x;
        const bool assume = building_type_ghost_assume_occupied(planner.build_type);
        building_road_ports ports = building_road_ports_preview(planner.end, planner.build_type, bsize,
          planner.absolute_orientation, planner.building_variant, assume);
        if (!ports.valid) {
            return;
        }

        // Dim when the access tile has no route to kingdom entry (last-tick distances).
        const color mask = map_routing_distance(ports.tile) > 0 ? COLOR_MASK_AMBER : COLOR_MASK_AMBER_40;
        vec2i access_pixel = g_camera.lookup_tile_to_pixel(ports.tile);
        ghost_draw::draw_building_ghost(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, access_pixel,
          mask);
    }

    void draw_preview(build_planner& planner, painter& ctx) {
        if (planner.needBridge()) {
            draw_bridge(planner.end, ghost_draw::pixel_coord_offset(planner, 0, 0), planner.build_type, ctx);
            return;
        }

        if (planner.size.x < 1 || planner.size.y < 1) {
            return;
        }

        const vec2i pixel = ghost_draw::pixel_coord_offset(planner, 0, 0);
        const auto& painter_of_type = ghost_painter_of(planner.build_type);
        if (planner.can_be_placed() == CAN_NOT_PLACE) {
            painter_of_type.ghost_blocked(planner, ctx, planner.start, planner.end, pixel, true);
        } else if (planner.blocked_tiles_count() > 0) {
            painter_of_type.ghost_blocked(planner, ctx, planner.start, planner.end, pixel, false);
            draw_road_access_marker(planner, ctx);
        } else if (!planner.draw_as_constructing) {
            painter_of_type.ghost_preview(planner, ctx, planner.start, planner.end, pixel);
            draw_road_access_marker(planner, ctx);
        }
    }

} // namespace

void placement_preview::draw(painter& ctx) {
    OZZY_PROFILER_FUNCTION();
    build_planner& planner = g_city_planner;
    struct restore_draw_ctx {
        painter*& slot;
        painter* previous;
        ~restore_draw_ctx() { slot = previous; }
    } restore{planner.draw_ctx, planner.draw_ctx};
    planner.draw_ctx = &ctx;
    draw_preview(planner, ctx);
}
