// Places a strong wall (BUILDING_WALL / id 169) via build_planner, checks TERRAIN_WALL +
// WALL_MATERIAL_STRONG. Also: clear+undo restores strong; mud/brick overwrite is material no-op.
// Marker: [test-marker] test_strong_wall_placed:...

var __test78_result = null
var WALL_MATERIAL_NONE = 0
var WALL_MATERIAL_MUD = 1
var WALL_MATERIAL_BRICK = 2
var WALL_MATERIAL_STRONG = 3

function test78_find_wall_route(wall_type, end_dx, end_dy) {
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

function test78_wall_place(wall_type, start_x, start_y, end_x, end_y) {
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

function test78_assert_material(tiles, material, building_type, tag) {
    for (var i = 0; i < tiles.length; i++) {
        var t = tiles[i]
        if (!terrain.is(t, TERRAIN_WALL)) {
            __log_info_native('[test:78] ' + tag + ': missing TERRAIN_WALL at ' + t.x + ',' + t.y)
            return false
        }
        var got = terrain.wall_material(t)
        if (got != material) {
            __log_info_native('[test:78] ' + tag + ': expected material ' + material
                + ' at ' + t.x + ',' + t.y + ' got ' + got)
            return false
        }
        if (terrain.wall_building_type(t) != building_type) {
            __log_info_native('[test:78] ' + tag + ': wall_building_type mismatch at ' + t.x + ',' + t.y
                + ' expected ' + building_type + ' got ' + terrain.wall_building_type(t))
            return false
        }
    }
    return true
}

function test78_clear_segment(tiles) {
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

function test78_clear_tile_and_undo(tile) {
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
    if (terrain.wall_material(tile) != WALL_MATERIAL_STRONG) {
        return { ok: false, reason: 'undo_material=' + terrain.wall_material(tile) }
    }
    return { ok: true }
}

function test78_place_on_tile(wall_type, tile) {
    return test78_wall_place(wall_type, tile.x, tile.y, tile.x, tile.y)
}

function run_test() {
    __log_info_native('[test:78] placing strong wall segment via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    if (BUILDING_WALL != 169) {
        __test78_result = { ok: false, reason: 'BUILDING_WALL id expected 169 got ' + BUILDING_WALL, tiles: [] }
        __test_signal_ready()
        return
    }

    var route = test78_find_wall_route(BUILDING_WALL, 0, 5)
    if (!route) {
        __test78_result = { ok: false, reason: 'no_route', tiles: [] }
        __log_info_native('[test:78] test78_find_wall_route failed')
        __test_signal_ready()
        return
    }

    __log_info_native('[test:78] strong-over-mud overwrite no-op')
    var mud = test78_wall_place(BUILDING_MUD_WALL, route.start_x, route.start_y, route.end_x, route.end_y)
    if (!mud.ok) {
        __test78_result = { ok: false, reason: 'mud_seed:' + (mud.reason || 'unknown'), tiles: [] }
        __test_signal_ready()
        return
    }
    if (!test78_assert_material(mud.tiles, WALL_MATERIAL_MUD, BUILDING_MUD_WALL, 'mud_seed')) {
        __test78_result = { ok: false, reason: 'mud_seed_material', tiles: mud.tiles }
        __test_signal_ready()
        return
    }
    var strong_over_mud = test78_place_on_tile(BUILDING_WALL, mud.tiles[0])
    if (!strong_over_mud.ok) {
        __test78_result = { ok: false, reason: 'strong_over_mud:' + (strong_over_mud.reason || 'unknown'), tiles: mud.tiles }
        __test_signal_ready()
        return
    }
    if (!test78_assert_material(mud.tiles, WALL_MATERIAL_MUD, BUILDING_MUD_WALL, 'strong_over_mud')) {
        __test78_result = { ok: false, reason: 'strong_converted_mud', tiles: mud.tiles }
        __test_signal_ready()
        return
    }

    var cleared_mud = test78_clear_segment(mud.tiles)
    if (!cleared_mud.ok) {
        __test78_result = { ok: false, reason: 'clear_mud:' + cleared_mud.reason, tiles: mud.tiles }
        __test_signal_ready()
        return
    }

    var placed = test78_wall_place(BUILDING_WALL, route.start_x, route.start_y, route.end_x, route.end_y)
    if (!placed.ok) {
        __test78_result = placed
        __log_info_native('[test:78] test78_wall_place failed: ' + (placed.reason || 'unknown'))
        __test_signal_ready()
        return
    }

    __log_marker('test_strong_wall_placed:' + route.start_x + ',' + route.start_y + '-'
        + route.end_x + ',' + route.end_y + ':tiles=' + placed.tiles.length)

    var clear_tile = placed.tiles[0]
    __log_info_native('[test:78] clear+undo strong wall tile ' + clear_tile.x + ',' + clear_tile.y)
    var cleared = test78_clear_tile_and_undo(clear_tile)
    if (!cleared.ok) {
        __test78_result = { ok: false, reason: cleared.reason, tiles: placed.tiles }
        __log_info_native('[test:78] clear+undo failed: ' + cleared.reason)
        __test_signal_ready()
        return
    }

    __log_info_native('[test:78] mud-over-strong overwrite no-op')
    var mud_over_strong = test78_place_on_tile(BUILDING_MUD_WALL, placed.tiles[0])
    if (!mud_over_strong.ok) {
        __test78_result = { ok: false, reason: 'mud_over_strong:' + (mud_over_strong.reason || 'unknown'), tiles: placed.tiles }
        __test_signal_ready()
        return
    }
    if (!test78_assert_material(placed.tiles, WALL_MATERIAL_STRONG, BUILDING_WALL, 'mud_over_strong')) {
        __test78_result = { ok: false, reason: 'mud_converted_strong', tiles: placed.tiles }
        __test_signal_ready()
        return
    }

    __log_info_native('[test:78] brick-over-strong overwrite no-op')
    var brick_over_strong = test78_place_on_tile(BUILDING_BRICK_WALL, placed.tiles[0])
    if (!brick_over_strong.ok) {
        __test78_result = { ok: false, reason: 'brick_over_strong:' + (brick_over_strong.reason || 'unknown'), tiles: placed.tiles }
        __test_signal_ready()
        return
    }
    if (!test78_assert_material(placed.tiles, WALL_MATERIAL_STRONG, BUILDING_WALL, 'brick_over_strong')) {
        __test78_result = { ok: false, reason: 'brick_converted_strong', tiles: placed.tiles }
        __test_signal_ready()
        return
    }

    __test78_result = {
        ok: true,
        tiles: placed.tiles,
        clear_undo: true,
        overwrite_noop: true,
    }
    __test_signal_ready()
}

function check_valid() {
    if (!__test78_result || !__test78_result.ok) {
        __log_info_native('[test:78] run_test did not place strong wall'
            + (__test78_result && __test78_result.reason ? (': ' + __test78_result.reason) : ''))
        return false
    }

    if (!test78_assert_material(__test78_result.tiles, WALL_MATERIAL_STRONG, BUILDING_WALL, 'final')) {
        return false
    }

    __log_info_native('[test:78] strong wall ok tiles=' + __test78_result.tiles.length
        + ' clear_undo=' + (__test78_result.clear_undo ? 1 : 0)
        + ' overwrite_noop=' + (__test78_result.overwrite_noop ? 1 : 0))
    return true
}
