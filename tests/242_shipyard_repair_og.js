// OG shipwright repair: queued warship is healed with timber (1 wood / day,
// heal by worker progress). Markers:
//   [test-marker] shipyard_repair_queued
//   [test-marker] shipyard_repair_healed

var __test242_ok = false

function test242_fail(msg) {
    __log_info_native('[test:242] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:242] shipyard OG repair')

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)

    var bid = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!bid) {
        return test242_fail('shipwright place failed')
    }

    __test_building_set_workers(bid, 20)
    var yard = city.get_building(bid)
    yard.store_resource(RESOURCE_TIMBER, 100)

    var dock = yard.water_access_tile(0)
    if (!dock || dock.x < 0) {
        dock = yard.tile
    }

    var fid = test_figure_create(FIGURE_WARSHIP, dock.x, dock.y)
    if (!fid) {
        return test242_fail('warship create failed')
    }

    __test_figure_set_damage(fid, 40)
    if (__test_shipyard_queue_ship(bid, fid) != 1) {
        return test242_fail('queue_ship failed')
    }
    __log_marker('shipyard_repair_queued')

    __test_building_update_day(bid)
    if (__test_shipyard_is_reparing(bid) != 1) {
        return test242_fail('expected reparing after idle update_day')
    }
    if (__test_shipyard_repair_fid(bid) != fid) {
        return test242_fail('repair_fid mismatch')
    }

    var wood0 = yard.stored_resource(RESOURCE_TIMBER)
    var dmg0 = __test_figure_get_damage(fid)
    __test_building_update_day(bid)
    var wood1 = yard.stored_resource(RESOURCE_TIMBER)
    var dmg1 = __test_figure_get_damage(fid)

    if (wood1 != wood0 - 1) {
        return test242_fail('expected 1 timber consumed, wood0=' + wood0 + ' wood1=' + wood1)
    }
    if (dmg1 >= dmg0) {
        return test242_fail('expected damage to drop, dmg0=' + dmg0 + ' dmg1=' + dmg1)
    }
    __log_marker('shipyard_repair_healed')

    __test242_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test242_ok
        && __test_find_inlog('[test-marker] shipyard_repair_queued')
        && __test_find_inlog('[test-marker] shipyard_repair_healed')
}
