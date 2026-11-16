// Every building type must fit its save record: header + bind_dynamic get the first 186 bytes.
// Each type is placed through the planner, then the city is saved and loaded back; the record bind
// logs "[record-overflow]" for any type past the budget, which fails the test.
// A type that does not fit at the cursor is tried a few tiles further; past the right edge the cursor moves to the
// next row. It walks the middle half of the rows, where the play diamond is wide, and past the last of them starts
// again from the first. Tiles outside the area OG lets buildings use (3 tiles inside the map and the diamond) are
// skipped without spending a try. A type that finds no spot within
// T484_MAX_TRIES leaves the cursor where it was, so the next type does not start in a bad corner.
// Venues need a road junction, so booth, bandstand and pavilion get one first (same patterns as test 485).
// Marker: [test-marker] building_record_size_all_types_ok

var __t484_ok = false
var T484_STEP = 3
var T484_MAX_TRIES = 300

var T484_VENUES = [
    { type: BUILDING_BOOTH, roads: [[0, 1], [1, 1]], extra: [[1, 2], [2, 1]] },
    { type: BUILDING_BANDSTAND, roads: [[1, 0, 0], [1, 1, 1], [1, 0, 0]], extra: [] },
    { type: BUILDING_PAVILLION, roads: [[0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 0], [1, 1, 1, 1]], extra: [] }
]

function t484_try_place(x, y) {
    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        return 0
    }
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    // Drag-placed types (houses, walls, statues...) do not set the planner's last created building, and roads, ditches
    // or cleared land create none; they are still placed, so the cursor must move on (-1: placed, no record).
    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    if (!(bid > 0)) {
        bid = __building_at(x, y)
    }
    return bid > 0 ? bid : -1
}

function t484_step(cur, w, h) {
    cur.x += T484_STEP
    if (cur.x >= w) {
        cur.x = 0
        cur.y += T484_STEP
        if (cur.y >= ((h * 3) / 4) | 0) {
            cur.y = (h / 4) | 0
        }
    }
}

function t484_advance(cur, w, h) {
    var limit = ((w * h) / (T484_STEP * T484_STEP)) | 0
    do {
        t484_step(cur, w, h)
    } while (!__test_map_inside_building_area(cur.x, cur.y) && --limit > 0)
}

function t484_place_venue(v, x, y) {
    for (var dy = 0; dy < v.roads.length; dy++) {
        for (var dx = 0; dx < v.roads[dy].length; dx++) {
            if (v.roads[dy][dx]) {
                terrain.add({ x: x + dx, y: y + dy }, TERRAIN_ROAD)
            }
        }
    }
    for (var i = 0; i < v.extra.length; i++) {
        terrain.add({ x: x + v.extra[i][0], y: y + v.extra[i][1] }, TERRAIN_ROAD)
    }
    return test_building_place(v.type, x, y)
}

function run_test() {
    __log_info_native('[test:484] building record size, all types')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000000)
    __camera_rotate_north()

    var w = __scenario_map.width
    var h = __scenario_map.height
    var placed_types = {}
    var placed = 0

    var cx = (w / 2) | 0
    var cy = (h / 2) | 0
    for (var v = 0; v < T484_VENUES.length; v++) {
        if (t484_place_venue(T484_VENUES[v], cx - 30 + v * 10, cy - 20)) {
            placed_types[T484_VENUES[v].type] = true
            placed++
        }
    }

    var cur = { x: 0, y: (h / 4) | 0 }
    t484_advance(cur, w, h)
    var skipped = []
    for (var t = BUILDING_NONE + 1; t < BUILDING_MAX; t++) {
        if (placed_types[t] || !__building_static_config_name(t) || !test_planner_enter_build_mode(t)) {
            continue
        }

        var start = { x: cur.x, y: cur.y }
        var bid = t484_try_place(cur.x, cur.y)
        for (var i = 1; i < T484_MAX_TRIES && !bid; i++) {
            t484_advance(cur, w, h)
            bid = t484_try_place(cur.x, cur.y)
        }
        test_planner_exit_build_mode()

        if (bid) {
            placed++
            cur.x += __building_static_building_size(t) + 1
        } else {
            cur = start
            skipped.push(__building_static_config_name(t))
        }
    }
    __log_info_native('[test:484] placed ' + placed + ' types, not placeable here: ' + skipped.join(' '))

    __test_save_roundtrip('test_484_all_types.svx')

    if (!placed_types[BUILDING_BOOTH] || !placed_types[BUILDING_BANDSTAND] || !placed_types[BUILDING_PAVILLION]) {
        __log_info_native('[test:484] FAIL a venue could not be placed')
    } else if (placed < 80) {
        __log_info_native('[test:484] FAIL only ' + placed + ' building types were placed')
    } else if (__test_find_inlog('[record-overflow]')) {
        __log_info_native('[test:484] FAIL a building type overflows its record')
    } else {
        __log_marker('building_record_size_all_types_ok')
        __t484_ok = true
    }
    __test_signal_ready()
}

function check_valid() {
    return __t484_ok && __test_find_inlog('[test-marker] building_record_size_all_types_ok')
}
