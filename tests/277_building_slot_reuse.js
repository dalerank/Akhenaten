// A building created in a freed slot starts clean: nothing is inherited from the slot's previous
// building, whether that one vanished (destroy_by_poof) or was deleted (building_update_state).

var __t277_ok = false

function t277_fail(msg) {
    __log_info_native('[test:277] FAIL: ' + msg)
    __test_signal_ready()
}

// Leaves a dirty building in a slot, frees it, and returns the id of the next building created.
function t277_reuse(via_delete, x, y) {
    var old_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, x, y)
    if (!old_id) {
        return -1
    }
    var old = city.get_building(old_id)
    __test_building_force_road_access(old_id)
    old.num_workers = 7
    old.store_resource(RESOURCE_CLAY, 300)
    if (!__test_building_release_slot(old_id, via_delete)) {
        return -2
    }
    var new_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, x + 4, y)
    if (new_id != old_id) {
        __log_info_native('[test:277] slot not reused: old ' + old_id + ' new ' + new_id)
        return -3
    }
    return new_id
}

function t277_check_clean(bid, label) {
    var b = city.get_building(bid)
    var road = __test_building_road_access_tile(bid)
    if (road != -1 || b.num_workers != 0 || b.stored_resource(RESOURCE_CLAY) != 0) {
        t277_fail(label + ': road_access ' + road + ' num_workers ' + b.num_workers
            + ' clay ' + b.stored_resource(RESOURCE_CLAY))
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:277] building slot reuse')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var after_poof = t277_reuse(0, cx - 10, cy)
    if (after_poof < 0) {
        return t277_fail('poof setup ' + after_poof)
    }
    if (!t277_check_clean(after_poof, 'after poof')) {
        return
    }
    __log_marker('t277_poof_slot_clean')

    var after_delete = t277_reuse(1, cx - 10, cy + 6)
    if (after_delete < 0) {
        return t277_fail('delete setup ' + after_delete)
    }
    if (!t277_check_clean(after_delete, 'after delete')) {
        return
    }
    __log_marker('t277_delete_slot_clean')

    __t277_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t277_ok
        && __test_find_inlog('[test-marker] t277_poof_slot_clean')
        && __test_find_inlog('[test-marker] t277_delete_slot_clean')
}
