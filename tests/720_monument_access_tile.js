// building::access_tile() for every monument that does not use the plain road access: every part of a pyramid
// or mastaba family walks to main tile + (0, N) by size, Sphinx and Caesareum to their access_point(), the
// complex annexes keep their road_access. The *_CONE part types are never placed (cone_type is unused).
// Each monument is placed for real on a fresh map and every part of its chain is checked.

var T720_SHIFT = {}
T720_SHIFT[BUILDING_SMALL_MASTABA] = 10
T720_SHIFT[BUILDING_SMALL_MASTABA_ENTRANCE] = 10
T720_SHIFT[BUILDING_SMALL_MASTABA_WALL] = 10
T720_SHIFT[BUILDING_SMALL_MASTABA_SIDE] = 10
T720_SHIFT[BUILDING_SMALL_STEPPED_PYRAMID] = 10
T720_SHIFT[BUILDING_SMALL_STEPPED_PYRAMID_CORNER] = 10
T720_SHIFT[BUILDING_SMALL_STEPPED_PYRAMID_WALL] = 10
T720_SHIFT[BUILDING_SMALL_BENT_PYRAMID] = 10
T720_SHIFT[BUILDING_SMALL_BENT_PYRAMID_CORNER] = 10
T720_SHIFT[BUILDING_SMALL_BENT_PYRAMID_WALL] = 10
T720_SHIFT[BUILDING_SMALL_PYRAMID] = 10
T720_SHIFT[BUILDING_SMALL_PYRAMID_CORNER] = 10
T720_SHIFT[BUILDING_SMALL_PYRAMID_WALL] = 10
T720_SHIFT[BUILDING_SMALL_MUDBRICK_PYRAMID] = 10
T720_SHIFT[BUILDING_SMALL_MUDBRICK_PYRAMID_CORNER] = 10
T720_SHIFT[BUILDING_SMALL_MUDBRICK_PYRAMID_WALL] = 10
T720_SHIFT[BUILDING_MEDIUM_MASTABA] = 14
T720_SHIFT[BUILDING_MEDIUM_MASTABA_ENTRANCE] = 14
T720_SHIFT[BUILDING_MEDIUM_MASTABA_WALL] = 14
T720_SHIFT[BUILDING_MEDIUM_MASTABA_SIDE] = 14
T720_SHIFT[BUILDING_MEDIUM_STEPPED_PYRAMID] = 14
T720_SHIFT[BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER] = 14
T720_SHIFT[BUILDING_MEDIUM_STEPPED_PYRAMID_WALL] = 14
T720_SHIFT[BUILDING_MEDIUM_BENT_PYRAMID] = 14
T720_SHIFT[BUILDING_MEDIUM_BENT_PYRAMID_CORNER] = 14
T720_SHIFT[BUILDING_MEDIUM_BENT_PYRAMID_WALL] = 14
T720_SHIFT[BUILDING_MEDIUM_PYRAMID] = 14
T720_SHIFT[BUILDING_MEDIUM_PYRAMID_CORNER] = 14
T720_SHIFT[BUILDING_MEDIUM_PYRAMID_WALL] = 14
T720_SHIFT[BUILDING_MEDIUM_MUDBRICK_PYRAMID] = 14
T720_SHIFT[BUILDING_MEDIUM_MUDBRICK_PYRAMID_CORNER] = 14
T720_SHIFT[BUILDING_MEDIUM_MUDBRICK_PYRAMID_WALL] = 14
T720_SHIFT[BUILDING_LARGE_MASTABA] = 18
T720_SHIFT[BUILDING_LARGE_MASTABA_ENTRANCE] = 18
T720_SHIFT[BUILDING_LARGE_MASTABA_WALL] = 18
T720_SHIFT[BUILDING_LARGE_MASTABA_SIDE] = 18
T720_SHIFT[BUILDING_LARGE_MUDBRICK_PYRAMID] = 18
T720_SHIFT[BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER] = 18
T720_SHIFT[BUILDING_LARGE_MUDBRICK_PYRAMID_WALL] = 18
T720_SHIFT[BUILDING_MUDBRICK_PYRAMID_COMPLEX] = 22
T720_SHIFT[BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX] = 22
T720_SHIFT[BUILDING_LARGE_STEPPED_PYRAMID] = 22
T720_SHIFT[BUILDING_LARGE_STEPPED_PYRAMID_CORNER] = 22
T720_SHIFT[BUILDING_LARGE_STEPPED_PYRAMID_WALL] = 22
T720_SHIFT[BUILDING_STEPPED_PYRAMID_COMPLEX] = 22
T720_SHIFT[BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX] = 22
T720_SHIFT[BUILDING_LARGE_PYRAMID] = 22
T720_SHIFT[BUILDING_LARGE_PYRAMID_CORNER] = 22
T720_SHIFT[BUILDING_LARGE_PYRAMID_WALL] = 22
T720_SHIFT[BUILDING_PYRAMID_COMPLEX] = 22
T720_SHIFT[BUILDING_GRAND_PYRAMID_COMPLEX] = 22

var T720_ACCESS_POINT = {}
T720_ACCESS_POINT[BUILDING_SPHINX] = true
T720_ACCESS_POINT[BUILDING_CAESAREUM] = true

var T720_PLACE = [
    { type: BUILDING_SMALL_MASTABA },
    { type: BUILDING_MEDIUM_MASTABA },
    { type: BUILDING_LARGE_MASTABA },
    { type: BUILDING_SMALL_STEPPED_PYRAMID },
    { type: BUILDING_MEDIUM_STEPPED_PYRAMID },
    { type: BUILDING_LARGE_STEPPED_PYRAMID },
    { type: BUILDING_STEPPED_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_SMALL_BENT_PYRAMID },
    { type: BUILDING_MEDIUM_BENT_PYRAMID },
    { type: BUILDING_SMALL_PYRAMID },
    { type: BUILDING_MEDIUM_PYRAMID },
    { type: BUILDING_LARGE_PYRAMID },
    { type: BUILDING_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_GRAND_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_SMALL_MUDBRICK_PYRAMID },
    { type: BUILDING_MEDIUM_MUDBRICK_PYRAMID },
    { type: BUILDING_LARGE_MUDBRICK_PYRAMID },
    { type: BUILDING_MUDBRICK_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, complex: true },
    { type: BUILDING_SPHINX },
    { type: BUILDING_CAESAREUM }
]

function t720_chain_head(bid) {
    var cur = city.get_building(bid)
    var guard = 0
    while (cur && cur.prev_part_building_id > 0 && guard < 512) {
        bid = cur.prev_part_building_id
        cur = city.get_building(bid)
        guard++
    }
    return bid
}

function t720_try_place(type, x, y) {
    if (!test_planner_enter_build_mode(type)) {
        return 0
    }
    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test_planner_exit_build_mode()
        return 0
    }
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    test_planner_exit_build_mode()
    return bid ? t720_chain_head(bid) : 0
}

function t720_place(entry) {
    test_reload_city_session('data/default.map')
    __camera_rotate_north()
    __test_set_treasury(5000000)
    if (!__scenario_building_allowed(entry.type)) {
        __scenario_building_allow(entry.type, true)
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var spots = [
        { x: cx - 10, y: cy - 10 }, { x: 70, y: 40 }, { x: cx, y: cy }, { x: 40, y: 40 },
        { x: 30, y: 30 }, { x: 20, y: 20 }, { x: cx - 9, y: cy - 3 }
    ]
    for (var i = 0; i < spots.length; i++) {
        if (entry.complex) {
            test_prepare_pyramid_complex_causeway(spots[i].x, spots[i].y, 20, 4, 3, 1)
        }
        var bid = t720_try_place(entry.type, spots[i].x, spots[i].y)
        if (bid) {
            return bid
        }
    }
    return 0
}

function t720_same(a, b) {
    return a && b && a.x == b.x && a.y == b.y
}

function t720_str(t) {
    return t ? (t.x + ',' + t.y) : 'null'
}

function run_test() {
    __log_info_native('[test:720] monument access_tile')
    var seen = {}
    var ok = true
    var checked = 0

    for (var pi = 0; pi < T720_PLACE.length; pi++) {
        var entry = T720_PLACE[pi]
        var head = t720_place(entry)
        if (!head) {
            __log_info_native('[test:720] FAIL: place type ' + entry.type)
            __log_marker('t720_place_fail:' + entry.type)
            ok = false
            continue
        }

        var bid = head
        var guard = 0
        while (bid > 0 && guard < 512) {
            var type = __building_type(bid)
            var got = __test_building_access_tile(bid)
            var want
            if (T720_SHIFT[type] !== undefined) {
                var m = __test_building_main_tile(bid)
                want = { x: m.x, y: m.y + T720_SHIFT[type] }
            } else if (T720_ACCESS_POINT[type]) {
                want = __test_monument_access_point(bid)
            } else {
                want = __test_building_road_access(bid)
            }
            if (!t720_same(got, want)) {
                __log_info_native('[test:720] FAIL: placed ' + entry.type + ' part ' + bid + ' type ' + type
                    + ' access ' + t720_str(got) + ' want ' + t720_str(want))
                ok = false
            }
            seen[type] = true
            checked++
            var cur = city.get_building(bid)
            bid = cur ? cur.next_part_building_id : 0
            guard++
        }
    }

    var keys = Object.keys(T720_SHIFT).concat(Object.keys(T720_ACCESS_POINT))
    for (var k = 0; k < keys.length; k++) {
        if (!seen[keys[k]]) {
            __log_info_native('[test:720] FAIL: no part of type ' + keys[k] + ' was placed')
            ok = false
        }
    }

    __log_info_native('[test:720] checked ' + checked + ' parts')
    if (ok) {
        __log_marker('t720_access_tile_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] t720_access_tile_ok')
}
