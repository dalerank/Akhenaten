// Scribal School OG spawn_stock_walker: days between teachers from {5,10,25,50,100} by worker %,
// papyrus (walker_cost by difficulty) paid only when the teacher leaves; no papyrus => no teacher,
// while the day counter keeps running.

var __test221_ok = false

function test221_fail(msg) {
    __log_info_native('[test:221] FAIL: ' + msg)
    __test_signal_ready()
}

function test221_spawn(bid) {
    building_scribal_school_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_TEACHER)
}

function run_test() {
    __log_info_native('[test:221] scribal school OG teacher spawn')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test_building_place(BUILDING_SCRIBAL_SCHOOL, -1, -1)
    if (!bid) {
        test221_fail('place failed')
        return
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 10)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    city.figures.remove_figures(FIGURE_TEACHER)

    var cost = dcy_get(building_scribal_school.walker_cost)
    if (cost <= 0) {
        test221_fail('walker_cost not configured')
        return
    }

    for (var i = 0; i < 10; i++) {
        if (test221_spawn(bid) > 0) {
            test221_fail('teacher spawned without papyrus at day ' + i)
            return
        }
    }
    b = city.get_building(bid)
    if (b.figure_spawn_delay != 10) {
        test221_fail('day counter must keep running without stock, got ' + b.figure_spawn_delay)
        return
    }
    __log_marker('test221_no_papyrus_no_teacher')

    b.consume_resource(RESOURCE_PAPYRUS, -(cost * 2))
    if (test221_spawn(bid) < 1) {
        test221_fail('expected teacher once papyrus stocked, cost=' + cost)
        return
    }
    b = city.get_building(bid)
    if (b.stored_resource(RESOURCE_PAPYRUS) != cost) {
        test221_fail('papyrus after spawn expected ' + cost + ' got ' + b.stored_resource(RESOURCE_PAPYRUS))
        return
    }
    if (b.figure_spawn_delay != 0) {
        test221_fail('day counter must reset after spawn, got ' + b.figure_spawn_delay)
        return
    }
    __log_marker('test221_paid_on_spawn:' + cost)

    // 100% workers: OG delay 5 => 6th day spawns. Fresh school: a poofed teacher keeps its slot until cleanup.
    var bid2 = test_building_place(BUILDING_SCRIBAL_SCHOOL, -1, -1)
    if (!bid2) {
        test221_fail('second place failed')
        return
    }
    var zt2 = __building_tile(bid2)
    for (var dx2 = 0; dx2 < 3; dx2++) {
        terrain.add({ x: zt2.x + dx2, y: zt2.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_workers(bid2, 10)
    var b2 = city.get_building(bid2)
    b2.has_road_access = true
    b2.figure_spawn_delay = 0
    b2.consume_resource(RESOURCE_PAPYRUS, -cost)

    var teachers = __test_count_figures(FIGURE_TEACHER)
    for (var d = 1; d <= 5; d++) {
        if (test221_spawn(bid2) > teachers) {
            test221_fail('teacher spawned too early at day ' + d)
            return
        }
    }
    if (test221_spawn(bid2) <= teachers) {
        test221_fail('teacher expected on day 6 at 100% workers')
        return
    }
    __log_marker('test221_delay_100pct')

    __test221_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test221_ok
        && __test_find_inlog('[test-marker] test221_no_papyrus_no_teacher')
        && __test_find_inlog('[test-marker] test221_paid_on_spawn:')
        && __test_find_inlog('[test-marker] test221_delay_100pct')
}
