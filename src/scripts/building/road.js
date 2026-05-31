log_info("akhenaten: building_road started")

function building_road_preview_image(tile) {
    var blocked = city.finance.is_out_of_money
    var image_id = 0

    if (terrain.is(tile, TERRAIN_CANAL)) {
        image_id = terrain.canal_image_begin()
        if (terrain.can_place_road_under_canal(tile)) {
            image_id += terrain.canal_with_road_image(tile)
        } else {
            blocked = true
        }

        return { blocked: blocked, image_id: image_id }
    }

    if (terrain.is(tile, TERRAIN_ROAD_BLOCKED)) {
        return { blocked: true, image_id: image_id }
    }

    image_id = terrain.dirt_road_image_base()
    if (!terrain.has_adjacent_y(tile, TERRAIN_ROAD) && terrain.has_adjacent_x(tile, TERRAIN_ROAD)) {
        image_id++
    }

    if (terrain.is(tile, TERRAIN_FLOODPLAIN)) {
        if (terrain.is(tile, TERRAIN_WATER)) {
            blocked = true
        }
        return { blocked: blocked, image_id: image_id }
    }

    if (!terrain.has_adjacent(tile, TERRAIN_FLOODPLAIN)) {
        return { blocked: blocked, image_id: image_id }
    }

    if (terrain.count_adjacent(tile, TERRAIN_FLOODPLAIN) != 1) {
        return { blocked: true, image_id: image_id }
    }

    if (terrain.has_adjacent_x(tile, TERRAIN_FLOODPLAIN)) {
        if (terrain.has_adjacent_y(tile, TERRAIN_ROAD)) {
            blocked = true
        } else {
            image_id++
        }
    }

    if (terrain.has_adjacent_y(tile, TERRAIN_FLOODPLAIN) && terrain.has_adjacent_x(tile, TERRAIN_ROAD)) {
        blocked = true
    }

    return { blocked: blocked, image_id: image_id }
}

function building_road_draw_preview_tile(tile) {
    var preview = building_road_preview_image(tile)
    var pixel = city.planner.tile_to_pixel(tile)
    if (preview.blocked) {
        city.planner.draw_blocked(pixel)
    } else {
        city.planner.draw_ghost(pixel, preview.image_id)
    }
}

[es=(building_road, ghost_preview)]
function building_road_ghost_preview(ev) {
    if (ev.in_progress) {
        if (!city.planner.preview_path) {
            return
        }
        for (var i = 0; i < city.planner.preview_path.length; i++) {
            var tile = city.planner.preview_path[i]
            building_road_draw_preview_tile(tile)
        }
    } else {
        building_road_draw_preview_tile(ev.end)
    }
}

[es=(building_road, construction_update)]
function building_road_construction_update(ev) {
    __game_undo_restore_map(0)
    city.planner.preview_path = null
    city.planner.construction_update_items = 0

    var start = { x: ev.start_x, y: ev.start_y }
    var end = { x: ev.end_x, y: ev.end_y }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start)) {
        return
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_ROAD, start, end)
    city.planner.preview_path = preview.tiles
    city.planner.construction_update_items = preview.items
}