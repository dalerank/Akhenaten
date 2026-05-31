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

function tile_shift(tile, direction) {
    return __map_tile_at_grid_offset(__map_grid_tiledir_offset(tile, direction))
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
        var current = end
        var guard = 0

        while (true) {
            guard++
            if (guard >= 400) {
                return { items: 0, tiles: [] }
            }

            var distance = __map_routing_distance(current)
            if (distance <= 0) {
                return { items: 0, tiles: [] }
            }
            tiles.push(current)
            items += routed_building_preview_item_count(current, mode)

            var direction = __calc_general_direction(current, start)
            if (direction == DIR_8_NONE) {
                return { items: items, tiles: tiles }
            }

            var routed = false
            var indices = ROUTED_DIRECTION_INDICES[direction]
            for (var i = 0; i < 4; i++) {
                var step = tile_shift(current, indices[i])
                var new_dist = __map_routing_distance(step)
                if (new_dist > 0 && new_dist < distance) {
                    current = step
                    routed = true
                    break
                }
            }

            if (!routed) {
                return { items: 0, tiles: [] }
            }
        }
    },
}
