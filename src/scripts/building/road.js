log_info("akhenaten: building_road started")

function building_road_path_has_adjacent_x(tile, pathTiles) {
    if (!pathTiles) {
        return false
    }
    for (var i = 0; i < pathTiles.length; i++) {
        var other = pathTiles[i]
        if (other.x == tile.x - 1 && other.y == tile.y) {
            return true
        }
        if (other.x == tile.x + 1 && other.y == tile.y) {
            return true
        }
    }
    return false
}

function building_road_path_has_adjacent_y(tile, pathTiles) {
    if (!pathTiles) {
        return false
    }
    for (var i = 0; i < pathTiles.length; i++) {
        var other = pathTiles[i]
        if (other.x == tile.x && other.y == tile.y - 1) {
            return true
        }
        if (other.x == tile.x && other.y == tile.y + 1) {
            return true
        }
    }
    return false
}

function building_road_preview_image(tile, pathTiles) {
    var blocked = city.finance.is_out_of_money
    var image_id = 0

    // construction_update places the path on the map (like the old C++ preview);
    // use the real tile sprite so junctions match neighbors.
    if (pathTiles && terrain.is(tile, TERRAIN_ROAD)) {
        return { blocked: blocked, image_id: __map_image_at(tile) }
    }

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
    var adj_x = terrain.has_adjacent_x(tile, TERRAIN_ROAD) || building_road_path_has_adjacent_x(tile, pathTiles)
    var adj_y = terrain.has_adjacent_y(tile, TERRAIN_ROAD) || building_road_path_has_adjacent_y(tile, pathTiles)
    if (!adj_y && adj_x) {
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

function building_road_draw_preview_tile(tile, pathTiles) {
    var preview = building_road_preview_image(tile, pathTiles)
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
        var tiles = city.planner.preview_path
        if (!tiles || tiles.length == 0) {
            building_road_draw_preview_tile(ev.end, null)
            return
        }
        for (var i = 0; i < tiles.length; i++) {
            building_road_draw_preview_tile(tiles[i], tiles)
        }
    } else {
        building_road_draw_preview_tile(ev.end, null)
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
    if (!preview.ok) {
        return
    }

    var items = __place_routed_building(start, end, ROUTED_BUILDING_ROAD)
    city.planner.preview_path = preview.tiles
    city.planner.construction_update_items = items
}
