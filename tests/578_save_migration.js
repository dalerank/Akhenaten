// Loading an older-format .svx silently converts it: the loaded file is renamed
// to "<name>_v<old_version>.svx", the already-converted city state is written to
// the canonical "<name>.svx", and the player is only informed afterwards (no
// choice is offered). A current-format save must load without any conversion.
// Markers:
//   [test-marker] save_migration_clean_load_no_migrate
//   [test-marker] save_migration_ok
//   [test-marker] save_migration_figure_ok

var __test578_ok = false
var SAVE_DIR = 'Save/Apa'

function test578_fail(msg) {
    __log_info_native('[test:578] FAIL: ' + msg)
    __test_signal_ready()
}

function test578_place_school() {
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

function test578_juggler_action_states() {
    var actions = []
    for (var i = 1; i < 2000; i++) {
        var f = city.get_figure(i)
        if (f && f.valid && f.type == FIGURE_JUGGLER) {
            actions.push(f.action_state)
        }
    }
    return actions
}

function run_test() {
    __log_info_native('[test:578] old-format save silent migration')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    game.dynasty_name = 'Apa'

    var clean_name = SAVE_DIR + '/clean.svx'
    var save_name = SAVE_DIR + '/migtest.svx'
    var backup_name = SAVE_DIR + '/migtest_v189.svx'

    var bid = test578_place_school()
    if (!bid) {
        test578_fail('juggler school place failed')
        return
    }

    var before = __test_count_figures(FIGURE_JUGGLER)
    var b = city.get_building(bid)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid })
    if (__test_count_figures(FIGURE_JUGGLER) <= before) {
        test578_fail('no juggler spawned')
        return
    }

    // Negative check: a current-format save must load without any migration.
    if (!game.write_savegame(clean_name) || !game.load_savegame(clean_name)) {
        test578_fail('clean save/load failed')
        return
    }
    if (__test_find_inlog('[test-marker] save_migrated:')) {
        test578_fail('current-format save must not migrate')
        return
    }
    if (__test_count_figures(FIGURE_JUGGLER) == 0) {
        test578_fail('juggler lost across clean save/load')
        return
    }
    __log_marker('save_migration_clean_load_no_migrate')

    // Write the save that will be downgraded to an older format.
    if (!game.write_savegame(save_name)) {
        test578_fail('write save failed')
        return
    }
    var patched = __test_legacyify_save(save_name)
    if (patched <= 0) {
        test578_fail('legacyify patched ' + patched + ' figures')
        return
    }

    if (!game.load_savegame(save_name)) {
        test578_fail('legacy load failed')
        return
    }

    if (!game.file_exists(save_name)) {
        test578_fail('canonical converted save missing')
        return
    }
    if (!game.file_exists(backup_name)) {
        test578_fail('backup of the original missing')
        return
    }
    if (!__test_find_inlog('[test-marker] save_migrated:' + save_name
        + ':to=' + save_name + ':backup=' + backup_name)) {
        test578_fail('migration marker missing')
        return
    }
    __log_marker('save_migration_ok')

    // Jugglers must be alive on valid (linear 0..7) action states after the load.
    var actions = test578_juggler_action_states()
    if (actions.length == 0) {
        test578_fail('no juggler found after migration load')
        return
    }
    for (var i = 0; i < actions.length; i++) {
        if (actions[i] < 0 || actions[i] > 7) {
            test578_fail('juggler action state ' + actions[i] + ' not remapped')
            return
        }
    }
    __log_marker('save_migration_figure_ok')

    game.delete_savegame(clean_name)
    game.delete_savegame(save_name)
    game.delete_savegame(backup_name)

    __test578_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test578_ok
        && __test_find_inlog('[test-marker] save_migration_clean_load_no_migrate')
        && __test_find_inlog('[test-marker] save_migration_ok')
        && __test_find_inlog('[test-marker] save_migration_figure_ok')
}
