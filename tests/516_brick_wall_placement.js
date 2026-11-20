// Places a brick wall segment via build_planner (routed drag), checks TERRAIN_WALL + material.
// Also: clear+undo restores brick; mud↔brick overwrite is material no-op.
// Marker: [test-marker] test_brick_wall_placed:...

var __test516_result = null
var WALL_MATERIAL_NONE = 0
var WALL_MATERIAL_MUD = 1
var WALL_MATERIAL_BRICK = 2

function test516_find_wall_route(wall_type, end_dx, end_dy) {
    if (!test_planner_enter_build_mode(wall_type)) {
        return null
    }

    var w = __scenario_map.width
    var h = __scenario_map.height
    var cx = (w / 2) | 0
    var cy = (h / 2) | 0
    var best = null
    var best_dist_sq = 999999999

    for (var y = 1; y < h - 1; y++) {
        for (var x = 1; x < w - 1; x++) {
            var dx = x - cx
            var dy = y - cy
            var dist_sq = dx * dx + dy * dy
            if (best && dist_sq >= best_dist_sq) {
                continue
            }

            var end_x = x + end_dx
            var end_y = y + end_dy
            if (end_x < 0 || end_y < 0 || end_x >= w || end_y >= h) {
                continue
            }

            var start = { x: x, y: y }
            var end = { x: end_x, y: end_y }
            if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, start)) {
                continue
            }

            var preview = routed_building.preview_path(ROUTED_BUILDING_WALL, start, end)
            if (!preview.ok || preview.tiles.length < 2) {
                continue
            }

            best = {
                start_x: x,
                start_y: y,
                end_x: end_x,
                end_y: end_y,
                tiles: preview.tiles,
            }
            best_dist_sq = dist_sq
        }
    }

    test_planner_exit_build_mode()
    return best
}

function test516_wall_place(wall_type, start_x, start_y, end_x, end_y) {
    var start = { x: start_x, y: start_y }
    var end = { x: end_x, y: end_y }

    if (!test_planner_enter_build_mode(wall_type)) {
        return { ok: false, reason: 'build_mode', tiles: [] }
    }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, start)) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'routing', tiles: [] }
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_WALL, start, end)
    if (!preview.ok) {
        test_planner_exit_build_mode()
        return { ok: false, reason: preview.reason || 'preview', tiles: preview.tiles || [] }
    }

    city_planner.update(end_x, end_y)
    city_planner.construction_start(start_x, start_y)
    city_planner.construction_update(end_x, end_y)
    city_planner.construction_finalize()

    var items = city_planner.construction_update_items
    test_planner_exit_build_mode()
    return { ok: true, tiles: preview.tiles, items: items }
}

function test516_assert_material(tiles, material, building_type, tag) {
    for (var i = 0; i < tiles.length; i++) {
        var t = tiles[i]
        if (!terrain.is(t, TERRAIN_WALL)) {
            __log_info_native('[test:516] ' + tag + ': missing TERRAIN_WALL at ' + t.x + ',' + t.y)
            return false
        }
        var got = terrain.wall_material(t)
        if (got != material) {
            __log_info_native('[test:516] ' + tag + ': expected material ' + material
                + ' at ' + t.x + ',' + t.y + ' got ' + got)
            return false
        }
        if (terrain.wall_building_type(t) != building_type) {
            __log_info_native('[test:516] ' + tag + ': wall_building_type mismatch at ' + t.x + ',' + t.y)
            return false
        }
    }
    return true
}

function test516_clear_segment(tiles) {
    if (!tiles.length) {
        return { ok: false, reason: 'empty' }
    }
    var a = tiles[0]
    var b = tiles[tiles.length - 1]
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return { ok: false, reason: 'clear_mode' }
    }
    city_planner.update(a.x, a.y)
    city_planner.construction_start(a.x, a.y)
    city_planner.construction_update(b.x, b.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()

    for (var i = 0; i < tiles.length; i++) {
        if (terrain.is(tiles[i], TERRAIN_WALL)) {
            return { ok: false, reason: 'clear_left_wall' }
        }
    }
    return { ok: true }
}

function test516_clear_tile_and_undo(tile) {
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return { ok: false, reason: 'clear_mode' }
    }

    city_planner.update(tile.x, tile.y)
    city_planner.construction_start(tile.x, tile.y)
    city_planner.construction_update(tile.x, tile.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()

    if (terrain.is(tile, TERRAIN_WALL)) {
        return { ok: false, reason: 'clear_left_wall' }
    }
    if (terrain.wall_material(tile) != WALL_MATERIAL_NONE) {
        return { ok: false, reason: 'clear_left_material=' + terrain.wall_material(tile) }
    }
    if (!__ui_game_can_undo()) {
        return { ok: false, reason: 'no_undo_after_clear' }
    }

    __ui_game_undo_perform()

    if (!terrain.is(tile, TERRAIN_WALL)) {
        return { ok: false, reason: 'undo_missing_wall' }
    }
    if (terrain.wall_material(tile) != WALL_MATERIAL_BRICK) {
        return { ok: false, reason: 'undo_material=' + terrain.wall_material(tile) }
    }
    return { ok: true }
}

function test516_place_on_tile(wall_type, tile) {
    // Same-tile place: routed path is one tile (existing wall). Used for overwrite checks —
    // L-drag cannot route *through* walls (only CITIZEN_4_CLEAR_TERRAIN).
    return test516_wall_place(wall_type, tile.x, tile.y, tile.x, tile.y)
}

function run_test() {
    __log_info_native('[test:516] placing brick wall segment via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var route = test516_find_wall_route(BUILDING_BRICK_WALL, 0, 5)
    if (!route) {
        __test516_result = { ok: false, reason: 'no_route', tiles: [] }
        __log_info_native('[test:516] test516_find_wall_route failed')
        __test_signal_ready()
        return
    }

    // Brick over mud must not convert material.
    __log_info_native('[test:516] brick-over-mud overwrite no-op')
    var mud = test516_wall_place(BUILDING_MUD_WALL, route.start_x, route.start_y, route.end_x, route.end_y)
    if (!mud.ok) {
        __test516_result = { ok: false, reason: 'mud_seed:' + (mud.reason || 'unknown'), tiles: [] }
        __test_signal_ready()
        return
    }
    if (!test516_assert_material(mud.tiles, WALL_MATERIAL_MUD, BUILDING_MUD_WALL, 'mud_seed')) {
        __test516_result = { ok: false, reason: 'mud_seed_material', tiles: mud.tiles }
        __test_signal_ready()
        return
    }
    var brick_over_mud = test516_place_on_tile(BUILDING_BRICK_WALL, mud.tiles[0])
    if (!brick_over_mud.ok) {
        __test516_result = { ok: false, reason: 'brick_over_mud:' + (brick_over_mud.reason || 'unknown'), tiles: mud.tiles }
        __test_signal_ready()
        return
    }
    if (!test516_assert_material(mud.tiles, WALL_MATERIAL_MUD, BUILDING_MUD_WALL, 'brick_over_mud')) {
        __test516_result = { ok: false, reason: 'brick_converted_mud', tiles: mud.tiles }
        __test_signal_ready()
        return
    }

    var cleared_mud = test516_clear_segment(mud.tiles)
    if (!cleared_mud.ok) {
        __test516_result = { ok: false, reason: 'clear_mud:' + cleared_mud.reason, tiles: mud.tiles }
        __test_signal_ready()
        return
    }

    var placed = test516_wall_place(BUILDING_BRICK_WALL, route.start_x, route.start_y, route.end_x, route.end_y)
    if (!placed.ok) {
        __test516_result = placed
        __log_info_native('[test:516] test516_wall_place failed: ' + (placed.reason || 'unknown'))
        __test_signal_ready()
        return
    }

    __log_marker('test_brick_wall_placed:' + route.start_x + ',' + route.start_y + '-'
        + route.end_x + ',' + route.end_y + ':tiles=' + placed.tiles.length)

    var clear_tile = placed.tiles[0]
    __log_info_native('[test:516] clear+undo brick wall tile ' + clear_tile.x + ',' + clear_tile.y)
    var cleared = test516_clear_tile_and_undo(clear_tile)
    if (!cleared.ok) {
        __test516_result = { ok: false, reason: cleared.reason, tiles: placed.tiles }
        __log_info_native('[test:516] clear+undo failed: ' + cleared.reason)
        __test_signal_ready()
        return
    }

    // Mud over brick must not convert material.
    __log_info_native('[test:516] mud-over-brick overwrite no-op')
    var mud_over_brick = test516_place_on_tile(BUILDING_MUD_WALL, placed.tiles[0])
    if (!mud_over_brick.ok) {
        __test516_result = { ok: false, reason: 'mud_over_brick:' + (mud_over_brick.reason || 'unknown'), tiles: placed.tiles }
        __test_signal_ready()
        return
    }
    if (!test516_assert_material(placed.tiles, WALL_MATERIAL_BRICK, BUILDING_BRICK_WALL, 'mud_over_brick')) {
        __test516_result = { ok: false, reason: 'mud_converted_brick', tiles: placed.tiles }
        __test_signal_ready()
        return
    }

    __test516_result = {
        ok: true,
        tiles: placed.tiles,
        clear_undo: true,
        overwrite_noop: true,
    }
    __test_signal_ready()
}

function check_valid() {
    if (!__test516_result || !__test516_result.ok) {
        __log_info_native('[test:516] run_test did not place brick wall'
            + (__test516_result && __test516_result.reason ? (': ' + __test516_result.reason) : ''))
        return false
    }

    if (!test516_assert_material(__test516_result.tiles, WALL_MATERIAL_BRICK, BUILDING_BRICK_WALL, 'final')) {
        return false
    }

    __log_info_native('[test:516] brick wall ok tiles=' + __test516_result.tiles.length
        + ' clear_undo=' + (__test516_result.clear_undo ? 1 : 0)
        + ' overwrite_noop=' + (__test516_result.overwrite_noop ? 1 : 0))
    return true
}
