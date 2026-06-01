log_info("akhenaten: routed_building.js started")

var DIR_8_NONE = 8

var ROUTED_DIRECTION_INDICES = [
    [0, 2, 6, 4],
    [0, 2, 6, 4],
    [2, 4, 0, 6],
    [2, 4, 0, 6],
    [4, 6, 2, 0],
    [4, 6, 2, 0],
    [6, 0, 4, 2],
    [6, 0, 4, 2],
]

function routed_building_tile_at_offset(grid_offset) {
    return __map_tile_at_grid_offset(grid_offset)
}

function routed_building_routing_distance(grid_offset) {
    return __map_routing_distance_at_grid_offset(grid_offset)
}

function routed_building_preview_item_count(tile, mode) {
    if (mode == ROUTED_BUILDING_ROAD) {
        return terrain.is(tile, TERRAIN_ROAD) ? 0 : 1
    }
    if (mode == ROUTED_BUILDING_WALL) {
        return terrain.is(tile, TERRAIN_WALL) ? 0 : 1
    }
    return 1
}

routed_building = {
    preview_path: function(mode, start, end) {
        var tiles = []
        var items = 0
        var grid_offset = __map_grid_offset(end)
        var guard = 0

        while (true) {
            guard++
            if (guard >= 400) {
                return { ok: false, items: 0, tiles: [], reason: "guard" }
            }

            var distance = routed_building_routing_distance(grid_offset)
            if (distance <= 0) {
                return { ok: false, items: 0, tiles: [], reason: "distance", step: guard, offset: grid_offset }
            }

            var tile = routed_building_tile_at_offset(grid_offset)
            tiles.push(tile)
            items += routed_building_preview_item_count(tile, mode)

            var direction = __calc_general_direction(tile, start)
            if (direction == DIR_8_NONE) {
                return { ok: true, items: items, tiles: tiles, reason: "ok" }
            }

            var routed = false
            var indices = ROUTED_DIRECTION_INDICES[direction]
            for (var i = 0; i < 4; i++) {
                var new_offset = grid_offset + __map_grid_direction_delta(indices[i])
                var new_dist = routed_building_routing_distance(new_offset)
                if (new_dist > 0 && new_dist < distance) {
                    grid_offset = new_offset
                    routed = true
                    break
                }
            }

            if (!routed) {
                return { ok: false, items: 0, tiles: [], reason: "no_next", step: guard, offset: grid_offset }
            }
        }
    },
}
