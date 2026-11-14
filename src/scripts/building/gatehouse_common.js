log_info("akhenaten: building_gatehouse_common started")

var building_gatehouse_restricted_terrain = TERRAIN_NOT_CLEAR - TERRAIN_ROAD

function building_gatehouse_shift(tile, dx, dy) {
    return { x: tile.x + dx, y: tile.y + dy }
}

function building_gatehouse_tile_to_view(tile) {
    return { x: (tile.x - tile.y) * 30, y: (tile.x + tile.y) * 15 }
}

function building_gatehouse_tile_blocked(tile) {
    return __city_planner_is_blocked_for_building(tile, 1, building_gatehouse_restricted_terrain)
}

function building_gatehouse_make_candidate(tile, orientation) {
    var ok = !building_gatehouse_tile_blocked(tile)
    return {
        tile: tile,
        orientation: orientation,
        ok: ok,
        road: ok && terrain.is(tile, TERRAIN_ROAD)
    }
}

function building_gatehouse_pick_second_part(first, second) {
    if (first.road != second.road) {
        return first.road ? first : second
    }
    if (first.road && second.road) {
        return city_planner.road_orientation == 2 ? second : first
    }
    if (second.ok) {
        return second
    }
    if (first.ok) {
        return first
    }
    return { tile: { x: 0, y: 0 }, orientation: -1 }
}

function building_gatehouse_second_part_tile(end, city_orientation) {
    var first
    var second
    if (city_orientation == 0) {
        first = building_gatehouse_make_candidate(building_gatehouse_shift(end, 0, -1), 0)
        second = building_gatehouse_make_candidate(building_gatehouse_shift(end, 1, 0), 1)
    } else if (city_orientation == 1) {
        first = building_gatehouse_make_candidate(building_gatehouse_shift(end, 0, -1), 1)
        second = building_gatehouse_make_candidate(building_gatehouse_shift(end, 1, 0), 2)
    } else if (city_orientation == 2) {
        first = building_gatehouse_make_candidate(building_gatehouse_shift(end, 0, 1), 2)
        second = building_gatehouse_make_candidate(building_gatehouse_shift(end, 1, 0), 3)
    } else if (city_orientation == 3) {
        first = building_gatehouse_make_candidate(building_gatehouse_shift(end, 0, 1), 3)
        second = building_gatehouse_make_candidate(building_gatehouse_shift(end, -1, 0), 0)
    } else {
        return { tile: { x: 0, y: 0 }, orientation: -1 }
    }

    var picked = building_gatehouse_pick_second_part(first, second)
    return { tile: picked.tile, orientation: picked.orientation }
}

function building_gatehouse_footprint_origin(road_a, road_b) {
    var x0 = Math.min(road_a.x, road_b.x)
    var y0 = Math.min(road_a.y, road_b.y)
    var horizontal = road_a.y == road_b.y
    var candidates = horizontal
        ? [{ x: x0, y: y0 - 1 }, { x: x0, y: y0 }]
        : [{ x: x0 - 1, y: y0 }, { x: x0, y: y0 }]

    function score(origin) {
        var s = 0
        if (__map_orientation_for_gatehouse(origin) > 0) {
            s += 10
        }
        for (var dy = 0; dy < 2; dy++) {
            for (var dx = 0; dx < 2; dx++) {
                var t = { x: origin.x + dx, y: origin.y + dy }
                if ((t.x == road_a.x && t.y == road_a.y) || (t.x == road_b.x && t.y == road_b.y)) {
                    continue
                }
                if (terrain.is(t, TERRAIN_WALL) || terrain.is(t, TERRAIN_GATEHOUSE)) {
                    s += 2
                }
            }
        }
        return s
    }

    var best = -1
    var origin = candidates[1]
    for (var i = 0; i < candidates.length; i++) {
        var sc = score(candidates[i])
        if (sc > best) {
            best = sc
            origin = candidates[i]
        }
    }
    return origin
}

function building_gatehouse_side_tiles(end, back_tile) {
    var origin = building_gatehouse_footprint_origin(end, back_tile.tile)
    var sides = []
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 2; dx++) {
            var t = { x: origin.x + dx, y: origin.y + dy }
            if ((t.x == end.x && t.y == end.y) || (t.x == back_tile.tile.x && t.y == back_tile.tile.y)) {
                continue
            }
            sides.push(t)
        }
    }
    return sides
}

function building_gatehouse_placement_check(ev) {
    var fully_blocked = !!city.finance.is_out_of_money
    var blocked = fully_blocked
    var end = ev.end
    var city_orientation = Math.floor(__camera.orientation / 2)
    var back_tile = building_gatehouse_second_part_tile(end, city_orientation)
    var blocked_tiles_main = []
    var blocked_tiles_second = []
    var side_tiles = []

    if (back_tile.orientation >= 0) {
        var main_blocked = building_gatehouse_tile_blocked(end)
        var second_blocked = building_gatehouse_tile_blocked(back_tile.tile)
        blocked_tiles_main.push({ tile: end, blocked: main_blocked })
        blocked_tiles_second.push({ tile: back_tile.tile, blocked: second_blocked })
        blocked = blocked || main_blocked || second_blocked
        side_tiles = building_gatehouse_side_tiles(end, back_tile)
    } else {
        blocked = true
        blocked_tiles_main.push({ tile: end, blocked: true })
        blocked_tiles_main.push({ tile: building_gatehouse_shift(end, 0, -1), blocked: true })
    }

    return {
        blocked: blocked,
        fully_blocked: fully_blocked,
        city_orientation: city_orientation,
        back_tile: back_tile,
        blocked_tiles_main: blocked_tiles_main,
        blocked_tiles_second: blocked_tiles_second,
        side_tiles: side_tiles
    }
}

function building_gatehouse_draw_partially_blocked(tiles, fully_blocked) {
    for (var i = 0; i < tiles.length; i++) {
        var entry = tiles[i]
        var pixel = city_planner.tile_to_pixel(entry.tile)
        var color = (fully_blocked || entry.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30
        city_planner.draw_flat_tile(pixel, color)
    }
}

function building_gatehouse_draw_blocked(check) {
    building_gatehouse_draw_partially_blocked(check.blocked_tiles_main, check.fully_blocked)
    building_gatehouse_draw_partially_blocked(check.blocked_tiles_second, check.fully_blocked)
}

function building_gatehouse_ghost_blocked(ev) {
    building_gatehouse_draw_blocked(building_gatehouse_placement_check(ev))
}

function building_gatehouse_ghost_preview(ev) {
    var check = building_gatehouse_placement_check(ev)
    if (check.blocked) {
        building_gatehouse_draw_blocked(check)
        return
    }

    var params = city.get_building_params_by_type(city_planner.build_type)
    var cfg = get_building_config_by_id(city_planner.build_type)
    var ghost = cfg.ghost
    var back_tile = check.back_tile
    var final_rot = (check.city_orientation + back_tile.orientation) % 8
    var main_off = ghost.main_view_offset[final_rot] || [0, 0]
    var part_off = ghost.part_view_offset[final_rot] || [0, 0]
    var pixel = ev.pixel
    var main_pixel = { x: pixel.x + main_off[0], y: pixel.y + main_off[1] }
    var ground_pixel = { x: pixel.x + part_off[0], y: pixel.y + part_off[1] }

    var cover_key = (back_tile.orientation == 0 || back_tile.orientation == 2) ? "base_cover_n" : "base_cover_w"
    if (back_tile.orientation == 0 || back_tile.orientation == 2) {
        city_planner.draw_ghost(ground_pixel, params.first_img("base_second_n"))
        city_planner.draw_ghost(main_pixel, params.first_img("base_n"))
    } else {
        city_planner.draw_ghost(main_pixel, params.first_img("base_second_w"))
        city_planner.draw_ghost(ground_pixel, params.first_img("base_w"))
    }

    var cover_id = params.first_img(cover_key)
    var end_view = building_gatehouse_tile_to_view(ev.end)
    for (var i = 0; i < check.side_tiles.length; i++) {
        var side = check.side_tiles[i]
        var side_view = building_gatehouse_tile_to_view(side)
        var side_pixel = {
            x: pixel.x + (side_view.x - end_view.x),
            y: pixel.y + (side_view.y - end_view.y)
        }
        city_planner.draw_ghost(side_pixel, cover_id)
    }
}
