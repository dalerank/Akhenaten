// Gardens follow OG placement (building_construction_place_garden); tile art comes from config variants.
// Markers:
//   [test-marker] garden_og_floodplain_adjacent_ok
//   [test-marker] garden_og_herd_point_rejects_area_ok
//   [test-marker] garden_og_images_ok

var __test227_result = null

function test227_fail(reason) {
    __test227_result = { ok: false, reason: reason }
    __log_info_native('[test:227] fail: ' + reason)
    __test_signal_ready()
}

function test227_clear_area(x0, y0, x1, y1) {
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            var tile = { x: x, y: y }
            terrain.remove(tile, TERRAIN_WATER | TERRAIN_CANAL | TERRAIN_ROAD | TERRAIN_ROCK | TERRAIN_TREE
                | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_FLOODPLAIN | TERRAIN_RUBBLE | TERRAIN_GARDEN
                | TERRAIN_MEADOW | TERRAIN_MARSHLAND | TERRAIN_DUNE | TERRAIN_ORE)
            __map_image_set(tile, 0)
        }
    }
}

function test227_drag_garden(x0, y0, x1, y1) {
    if (!test_planner_enter_build_mode(BUILDING_GARDENS)) {
        return false
    }
    city_planner.update(x1, y1)
    city_planner.construction_start(x0, y0)
    city_planner.construction_update(x1, y1)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    return true
}

function test227_count_gardens(x0, y0, x1, y1) {
    var n = 0
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            if (terrain.is({ x: x, y: y }, TERRAIN_GARDEN)) {
                n++
            }
        }
    }
    return n
}

function run_test() {
    __log_info_native('[test:227] gardens OG placement and images')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_clear_scenario_herd_points()
    __test_clear_scenario_prey_points()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test227_clear_area(cx - 8, cy - 8, cx + 8, cy + 8)

    // 1. A tile right next to the floodplain takes a garden; the floodplain tile itself does not.
    var flood = { x: cx - 6, y: cy - 6 }
    var beside = { x: cx - 5, y: cy - 6 }
    terrain.add(flood, TERRAIN_FLOODPLAIN)
    if (!test227_drag_garden(flood.x, flood.y, beside.x, beside.y)) {
        test227_fail('build_mode')
        return
    }
    if (terrain.is(flood, TERRAIN_GARDEN)) {
        test227_fail('garden_on_floodplain')
        return
    }
    if (!terrain.is(beside, TERRAIN_GARDEN)) {
        test227_fail('garden_not_placed_beside_floodplain')
        return
    }
    __log_marker('garden_og_floodplain_adjacent_ok')

    // 2. A herd point anywhere in the dragged area cancels the whole drag.
    var hx0 = cx - 6, hy0 = cy - 3, hx1 = cx - 2, hy1 = cy - 2
    __test_set_scenario_prey_point(0, hx1, hy1)
    test227_drag_garden(hx0, hy0, hx1, hy1)
    __test_clear_scenario_prey_points()
    var herd_gardens = test227_count_gardens(hx0, hy0, hx1, hy1)
    if (herd_gardens != 0) {
        test227_fail('herd_point_area_placed_' + herd_gardens)
        return
    }
    __log_marker('garden_og_herd_point_rejects_area_ok')

    // 3. Art comes from the config variants: a lone tile from variants1 (offsets 0..3), a 3x3 block from variants3 (+7).
    // Without Pharaoh data (CI) the garden pack is not loaded: ids are unresolved (<= 0), so only placement is checked.
    var base = __building_static_base_img(BUILDING_GARDENS)
    var has_art = base > 0
    var lone = { x: cx + 1, y: cy + 1 }
    test227_drag_garden(lone.x, lone.y, lone.x, lone.y)
    var lone_img = __map_image_at(lone)
    if (has_art && (lone_img < base || lone_img > base + 3)) {
        test227_fail('lone_img_offset_' + (lone_img - base))
        return
    }

    var bx = cx + 4, by = cy + 4
    test227_drag_garden(bx, by, bx + 2, by + 2)
    if (test227_count_gardens(bx, by, bx + 2, by + 2) != 9) {
        test227_fail('block_not_placed')
        return
    }
    if (!has_art) {
        __log_marker('garden_og_images_skipped_no_data')
        __test227_result = { ok: true }
        __test_signal_ready()
        return
    }
    var found_big = false
    for (var y = by; y <= by + 2; y++) {
        for (var x = bx; x <= bx + 2; x++) {
            if (__map_image_at({ x: x, y: y }) == base + 7) {
                found_big = true
            }
        }
    }
    if (!found_big) {
        test227_fail('block_missing_3x3_img')
        return
    }
    __log_marker('garden_og_images_ok')

    __test227_result = { ok: true }
    __test_signal_ready()
}

function check_valid() {
    if (!__test227_result || !__test227_result.ok) {
        __log_info_native('[test:227] fail: ' + ((__test227_result && __test227_result.reason) || 'no_result'))
        return false
    }
    return __test_find_inlog('[test-marker] garden_og_floodplain_adjacent_ok')
        && __test_find_inlog('[test-marker] garden_og_herd_point_rejects_area_ok')
        && (__test_find_inlog('[test-marker] garden_og_images_ok')
            || __test_find_inlog('[test-marker] garden_og_images_skipped_no_data'))
}
