var __test589_ok = false
var SAVE_DIR = 'Save/Apa'

function test589_fail(msg) {
    __log_info_native('[test:589] FAIL: ' + msg)
    __test_signal_ready()
}

function test589_place_school() {
    var bid = test_building_place(BUILDING_JUGGLER_SCHOOL, -1, -1)
    if (!bid) {
        return 0
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 5)
    var b = city.get_building(bid)
    b.has_road_access = true
    return bid
}

function test589_juggler_actions() {
    var actions = []
    for (var i = 1; i < 2000; i++) {
        var f = city.get_figure(i)
        if (f && f.valid && f.type == FIGURE_JUGGLER) {
            actions.push(f.action_state)
        }
    }
    return actions.join(',')
}

function run_test() {
    __log_info_native('[test:589] a save older than the minimum version is refused, the current layout round-trips')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    game.dynasty_name = 'Apa'

    var current_name = SAVE_DIR + '/layout_current.svx'
    var old_name = SAVE_DIR + '/layout_old.svx'

    var bid = test589_place_school()
    if (!bid) {
        test589_fail('juggler school place failed')
        return
    }

    var b = city.get_building(bid)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid })
    var expected = test589_juggler_actions()
    if (expected == '') {
        test589_fail('no juggler spawned')
        return
    }

    if (!game.write_savegame(current_name) || !game.load_savegame(current_name)) {
        test589_fail('current save/load failed')
        return
    }
    if (test589_juggler_actions() != expected) {
        test589_fail('current layout changed actions: ' + test589_juggler_actions() + ' != ' + expected)
        return
    }
    __log_marker('save_layout_current_ok')

    if (!game.write_savegame(old_name)) {
        test589_fail('write save failed')
        return
    }
    var patched = __test_legacyify_save(old_name)
    if (patched <= 0) {
        test589_fail('legacyify patched ' + patched + ' figures')
        return
    }
    if (game.load_savegame(old_name)) {
        test589_fail('a save older than the minimum version loaded')
        return
    }
    if (!__test_find_inlog('is older than 203')) {
        test589_fail('no refusal message for the old save')
        return
    }
    if (game.file_exists(SAVE_DIR + '/layout_old_v189.svx')) {
        test589_fail('loading an old save must not touch the player files')
        return
    }
    __log_marker('save_old_version_refused')

    game.delete_savegame(current_name)
    game.delete_savegame(old_name)

    __test589_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test589_ok
        && __test_find_inlog('[test-marker] save_layout_current_ok')
        && __test_find_inlog('[test-marker] save_old_version_refused')
}
