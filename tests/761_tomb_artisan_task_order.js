// OG find_tomb_artisan_task (construction_worker.c:955): the artisans guild takes the first royal tomb
// part in building id order whose stage wants an artisan, whatever the tomb's size. A medium tomb
// placed before a small one gets the artisan; the small tomb's chamber waits.
// Markers: t761_tombs_ok t761_stage2_ok t761_id_order_ok

function t761_fail(msg) {
    __log_info_native('[test:761] ' + msg)
    __log_marker('t761_fail')
    __test_signal_ready()
}

function t761_place_tomb(type, spots) {
    if (!__scenario_building_allowed(type)) {
        __scenario_building_allow(type, true)
    }
    for (var i = 0; i < spots.length; i++) {
        __test_royal_tomb_paint_site(type, spots[i].x, spots[i].y)
        var bid = test_building_place(type, spots[i].x, spots[i].y)
        if (bid) {
            return bid
        }
    }
    return 0
}

function t761_cut_first_chamber(bid) {
    __test_royal_tomb_set_lamp_stock(bid, 5000)
    var mason = __test_royal_tomb_attach_worker(bid, FIGURE_STONEMASON)
    if (!mason || __test_royal_tomb_part_worker(bid, 0) != mason) {
        return false
    }
    return __test_royal_tomb_work(mason, 5000) > 0 && __test_royal_tomb_part_stage(bid, 0) == 2
}

function run_test() {
    __log_info_native('[test:761] tomb artisan task order')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)

    var medium = t761_place_tomb(BUILDING_MEDIUM_ROYAL_TOMB, [{ x: 40, y: 40 }, { x: 30, y: 30 }, { x: 50, y: 30 }])
    var small = t761_place_tomb(BUILDING_SMALL_ROYAL_TOMB, [{ x: 40, y: 80 }, { x: 80, y: 40 }, { x: 80, y: 80 }, { x: 30, y: 90 }])
    if (!medium || !small || medium >= small) {
        return t761_fail('tombs medium=' + medium + ' small=' + small)
    }
    __log_marker('t761_tombs_ok')

    if (!t761_cut_first_chamber(medium) || !t761_cut_first_chamber(small)) {
        return t761_fail('first chambers not at stage 2: medium=' + __test_royal_tomb_part_stage(medium, 0)
            + ' small=' + __test_royal_tomb_part_stage(small, 0))
    }
    __log_marker('t761_stage2_ok')

    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }
    var guild = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    if (!guild) {
        return t761_fail('guild place failed')
    }
    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    var g = city.get_building(guild)
    g.num_workers = g.max_workers
    g.consume_resource(RESOURCE_CLAY, g.stored_resource(RESOURCE_CLAY) - 100)
    g.consume_resource(RESOURCE_PAINT, g.stored_resource(RESOURCE_PAINT))
    __test_building_spawn_figure(guild)
    var f = city.get_building(guild).get_figure(BUILDING_SLOT_SERVICE)
    var fid = (f && f.valid && f.type == FIGURE_TOMB_ARTISAN) ? f.id : 0
    var at_medium = __test_royal_tomb_part_worker(medium, 0)
    var at_small = __test_royal_tomb_part_worker(small, 0)
    if (!fid || at_medium != fid || at_small != 0) {
        return t761_fail('artisan ' + fid + ' went to medium=' + at_medium + ' small=' + at_small)
    }
    __log_marker('t761_id_order_ok')
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('[test-marker] t761_fail')) {
        return false
    }
    var required = ['t761_tombs_ok', 't761_stage2_ok', 't761_id_order_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:761] missing marker ' + required[i])
            return false
        }
    }
    return true
}
