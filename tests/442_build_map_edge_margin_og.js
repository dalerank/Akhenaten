// Issue #637: OG map_building_tiles_shrub_fits keeps every footprint tile 3 tiles inside the
// playable diamond (and the map rectangle). Probe the north tip of the diamond on data/default.map
// with a 1x1 small statue and a 2x2 work camp: the OG-edge site must place, one tile further out must not.

var __test442_ok = false

function test442_og_buildable(x, y, w, h) {
    var margin = 3
    if (x < margin || y < margin || x >= w - margin || y >= h - margin) {
        return false
    }
    var grid = 228
    var x_min = ((grid - w) / 2) | 0
    var y_min = ((grid - h) / 2) | 0
    var x_max = x_min - 1 + w
    var y_max = y_min - 1 + h
    var x_center = ((x_max + x_min) / 2) | 0
    var y_center = ((y_max + y_min) / 2) | 0
    var ax = x + x_min
    var ay = y + y_min
    if (ax <= x_center) {
        if (ay <= y_center) {
            return ax + ay - margin >= x_min + y_center
        }
        return ax - ay - margin >= x_center - y_max
    }
    if (ay <= y_center) {
        return ax - ay + margin <= x_max - y_center
    }
    return ax + ay + margin <= x_max + 1 + y_center
}

function test442_footprint_og(x, y, size, w, h) {
    for (var dy = 0; dy < size; dy++) {
        for (var dx = 0; dx < size; dx++) {
            if (!test442_og_buildable(x + dx, y + dy, w, h)) {
                return false
            }
        }
    }
    return true
}

function test442_can_place(type, x, y) {
    if (!test_planner_enter_build_mode(type)) {
        return false
    }
    city_planner.update(x, y)
    var ok = city_planner.can_be_placed() == CAN_PLACE
    test_planner_exit_build_mode()
    return ok
}

function test442_fail(msg) {
    __log_info_native('[test:442] FAIL: ' + msg)
    __test_signal_ready()
}

function test442_check_site(type, size, x, y, w, h) {
    if (!test442_footprint_og(x, y, size, w, h)) {
        test442_fail('site ' + x + ',' + y + ' size ' + size + ' is not at the OG edge')
        return false
    }
    var outward = [[0, -1], [-1, 0], [1, 0]]
    for (var i = 0; i < outward.length; i++) {
        var ox = x + outward[i][0]
        var oy = y + outward[i][1]
        if (test442_footprint_og(ox, oy, size, w, h)) {
            continue
        }
        if (test442_can_place(type, ox, oy)) {
            test442_fail('size ' + size + ' placeable outside the OG edge at ' + ox + ',' + oy)
            return false
        }
    }
    var bid = test_building_place(type, x, y)
    if (!bid) {
        test442_fail('size ' + size + ' not placeable at the OG edge ' + x + ',' + y)
        return false
    }
    __log_marker('test442_edge_ok:' + size + ':' + x + ',' + y)
    return true
}

function run_test() {
    __log_info_native('[test:442] build map edge margin')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var w = __scenario_map.width
    var h = __scenario_map.height
    if (__building_static_building_size(BUILDING_SMALL_STATUE) != 1 || __building_static_building_size(BUILDING_WORK_CAMP) != 2) {
        test442_fail('unexpected footprint sizes')
        return
    }

    var tip_y = -1
    var tip_x = -1
    for (var y = 0; y < h && tip_y < 0; y++) {
        for (var x = 0; x < w; x++) {
            if (test442_footprint_og(x, y, 2, w, h)) {
                tip_x = x
                tip_y = y
                break
            }
        }
    }
    if (tip_y < 0) {
        test442_fail('no OG buildable 2x2 site on ' + w + 'x' + h)
        return
    }

    for (var cy = 0; cy <= tip_y + 4; cy++) {
        for (var cx = tip_x - 6; cx <= tip_x + 7; cx++) {
            var t = { x: cx, y: cy }
            __map_terrain_remove(t, TERRAIN_ALL)
        }
    }

    if (!test442_check_site(BUILDING_WORK_CAMP, 2, tip_x, tip_y, w, h)) {
        return
    }

    var statue_x = tip_x + 4
    var statue_y = -1
    for (var sy = 0; sy < h; sy++) {
        if (test442_og_buildable(statue_x, sy, w, h)) {
            statue_y = sy
            break
        }
    }
    if (statue_y < 0 || statue_y > tip_y + 4) {
        test442_fail('no OG buildable 1x1 site near the tip')
        return
    }
    if (!test442_check_site(BUILDING_SMALL_STATUE, 1, statue_x, statue_y, w, h)) {
        return
    }

    __test442_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test442_ok && __test_find_inlog('[test-marker] test442_edge_ok:2:') && __test_find_inlog('[test-marker] test442_edge_ok:1:')
}
