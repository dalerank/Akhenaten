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

function building_gatehouse_placement_check(ev) {
    var fully_blocked = !!city.finance.is_out_of_money
    var blocked = fully_blocked
    var end = ev.end
    var city_orientation = Math.floor(__camera.orientation / 2)
    var back_tile = building_gatehouse_second_part_tile(end, city_orientation)
    var blocked_tiles_main = []
    var blocked_tiles_second = []

    if (back_tile.orientation >= 0) {
        var main_blocked = building_gatehouse_tile_blocked(end)
        var second_blocked = building_gatehouse_tile_blocked(back_tile.tile)
        blocked_tiles_main.push({ tile: end, blocked: main_blocked })
        blocked_tiles_second.push({ tile: back_tile.tile, blocked: second_blocked })
        blocked = blocked || main_blocked || second_blocked
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
        blocked_tiles_second: blocked_tiles_second
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

    if (back_tile.orientation == 0 || back_tile.orientation == 2) {
        city_planner.draw_ghost(ground_pixel, params.first_img("base_second_n"))
        city_planner.draw_ghost(main_pixel, params.first_img("base_n"))
    } else {
        city_planner.draw_ghost(main_pixel, params.first_img("base_second_w"))
        city_planner.draw_ghost(ground_pixel, params.first_img("base_w"))
    }
}

function building_gatehouse_on_place_checks(ev, size) {
    var main_id = __building_main_id(ev.bid)
    var b = city.get_building(main_id)
    if (!b) {
        return
    }
    var check_size = size || b.params.building_size
    var near_walls = !__map_terrain_is_adjacent_to_wall(b.tile, check_size)
    city.warnings.show_if_not(near_walls, "#warning_shipwright_needed")
}
