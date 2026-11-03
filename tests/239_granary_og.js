// OG granary: dual cart, Get@100%, per-food Empty, 4-type cap, empty haul 400, fancy update.
// Markers:
//   [test-marker] granary_og_emptying_ok
//   [test-marker] granary_og_empty_haul_400_ok
//   [test-marker] granary_og_getting_staff_gate_ok
//   [test-marker] granary_og_second_cart_ok
//   [test-marker] granary_og_allow_food_types_ok
//   [test-marker] granary_og_fancy_update_ok

var GRANARY_TASK_NONE = 0
var GRANARY_TASK_GETTING = 1
var GRANARY_TASK_EMPTYING = 2
var GRANARY_TASK_GETTING_MOAR = 3

var __test239 = {
    emptying: false,
    haul: false,
    staff_gate: false,
    second_cart: false,
    food_types: false,
    fancy: false
}

function grant_granary_road(bid) {
    var b = city.get_building(bid)
    var t = __building_tile(bid)
    var dx
    for (dx = -1; dx <= b.size; dx++) {
        terrain.add({ x: t.x + dx, y: t.y - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    b.has_road_access = true
    return __test_tile_road_network(__test_grid_offset_xy(t.x, t.y - 1))
}

function run_test() {
    __log_info_native('[test:239] granary OG behavior')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var g1 = __test_building_create(BUILDING_GRANARY, cx - 8, cy - 8)
    var g2 = __test_building_create(BUILDING_GRANARY, cx + 4, cy - 8)
    var g3 = __test_building_create(BUILDING_GRANARY, cx - 8, cy + 8)
    if (!g1 || !g2 || !g3 || g1 == g2) {
        __log_info_native('[test:239] create failed')
        __test_signal_ready()
        return
    }

    grant_granary_road(g1)
    grant_granary_road(g2)
    grant_granary_road(g3)
    var t1 = __building_tile(g1)
    var t2 = __building_tile(g2)
    var x
    for (x = Math.min(t1.x, t2.x) - 1; x <= Math.max(t1.x + 3, t2.x + 3); x++) {
        terrain.add({ x: x, y: t1.y - 1 }, TERRAIN_ROAD)
        terrain.add({ x: x, y: t2.y - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    var road_net = __test_tile_road_network(__test_grid_offset_xy(t1.x, t1.y - 1))
    city.get_building(g1).road_network_id = road_net
    city.get_building(g2).road_network_id = road_net
    city.get_building(g1).has_road_access = true
    city.get_building(g2).has_road_access = true
    city.get_building(g3).has_road_access = true
    city.get_building(g1).distance_from_entry = 1
    city.get_building(g2).distance_from_entry = 2

    __test_building_set_workers(g1, 20)
    __test_building_set_workers(g2, 20)
    __test_building_set_workers(g3, 20)

    // 1/3/5: per-food Empty + haul 400 at spawn
    if (!__test_granary_set_resource(g1, RESOURCE_GRAIN, 800)) {
        __log_info_native('[test:239] stock g1 failed')
        __test_signal_ready()
        return
    }
    if (!__test_granary_set_emptying(g1, RESOURCE_GRAIN)) {
        __log_info_native('[test:239] set emptying failed')
        __test_signal_ready()
        return
    }
    var task = __test_granary_worker_task(g1)
    var tres = __test_granary_worker_task_resource(g1)
    if (task != GRANARY_TASK_EMPTYING || tres != RESOURCE_GRAIN) {
        __log_info_native('[test:239] emptying task failed task=' + task + ' res=' + tres)
        __test_signal_ready()
        return
    }
    __log_marker('granary_og_emptying_ok')
    __test239.emptying = true

    __test_granary_spawn_figure(g1)
    var fid0 = __test_building_figure_id(g1, 0)
    var haul = __test_figure_carrying_amount(fid0)
    var haul_res = __test_figure_resource(fid0)
    if (fid0 <= 0 || haul != 400 || haul_res != RESOURCE_GRAIN) {
        __log_info_native('[test:239] empty haul failed fid=' + fid0 + ' haul=' + haul + ' res=' + haul_res)
        __test_signal_ready()
        return
    }
    __log_marker('granary_og_empty_haul_400_ok')
    __test239.haul = true

    // 2: Get staffing gate — 50% workers must not GET
    __test_granary_set_resource(g1, RESOURCE_MEAT, 800)
    if (!__test_granary_set_getting(g2, RESOURCE_MEAT)) {
        __log_info_native('[test:239] set getting failed')
        __test_signal_ready()
        return
    }
    __test_building_set_workers(g2, 10)
    __test_granary_find_getting_source(g2)
    var get_task = __test_granary_worker_task(g2)
    if (get_task != GRANARY_TASK_NONE) {
        __log_info_native('[test:239] understaffed get not blocked task=' + get_task)
        __test_signal_ready()
        return
    }
    __log_marker('granary_og_getting_staff_gate_ok')
    __test239.staff_gate = true

    // 1: full staff + large lack → GETTING_MOAR + second cart
    __test_building_set_workers(g2, 20)
    __test_granary_set_resource(g2, RESOURCE_MEAT, 0)
    __test_granary_find_getting_source(g2)
    get_task = __test_granary_worker_task(g2)
    if (get_task != GRANARY_TASK_GETTING_MOAR && get_task != GRANARY_TASK_GETTING) {
        __log_info_native('[test:239] full-staff get missing task=' + get_task)
        __test_signal_ready()
        return
    }
    __test_granary_spawn_figure(g2)
    __test_granary_spawn_figure(g2)
    var c0 = __test_building_figure_id(g2, 0)
    var c1 = __test_building_figure_id(g2, 1)
    if (c0 <= 0) {
        __log_info_native('[test:239] first get cart missing')
        __test_signal_ready()
        return
    }
    if (get_task == GRANARY_TASK_GETTING_MOAR && c1 <= 0) {
        __log_info_native('[test:239] second cart missing under MOAR')
        __test_signal_ready()
        return
    }
    __log_marker('granary_og_second_cart_ok')
    __test239.second_cart = true

    // 4: allow_food_types — 4 present → 5th refused
    __test_granary_set_resource(g3, RESOURCE_GRAIN, 100)
    __test_granary_set_resource(g3, RESOURCE_MEAT, 100)
    __test_granary_set_resource(g3, RESOURCE_LETTUCE, 100)
    __test_granary_set_resource(g3, RESOURCE_FIGS, 100)
    if (__test_granary_add_resource_noforce(g3, RESOURCE_FISH, 100)) {
        __log_info_native('[test:239] 5th food type accepted (should refuse)')
        __test_signal_ready()
        return
    }
    __log_marker('granary_og_allow_food_types_ok')
    __test239.food_types = true

    // 8: fancy graphic update path
    __test_granary_update_graphic(g3)
    __log_marker('granary_og_fancy_update_ok')
    __test239.fancy = true

    __test_signal_ready()
}

function check_valid() {
    return __test239.emptying
        && __test239.haul
        && __test239.staff_gate
        && __test239.second_cart
        && __test239.food_types
        && __test239.fancy
        && __test_find_inlog('[test-marker] granary_og_emptying_ok')
        && __test_find_inlog('[test-marker] granary_og_empty_haul_400_ok')
        && __test_find_inlog('[test-marker] granary_og_getting_staff_gate_ok')
        && __test_find_inlog('[test-marker] granary_og_second_cart_ok')
        && __test_find_inlog('[test-marker] granary_og_allow_food_types_ok')
        && __test_find_inlog('[test-marker] granary_og_fancy_update_ok')
}
