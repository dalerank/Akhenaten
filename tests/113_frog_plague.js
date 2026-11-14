// FIGURE_FROG register + anims; Ptah curse / EVENT / console command start the OG frog countdown (amount * 816);
// house infest + lockout; infested days survive a save round trip. Frog spawning and walking: test 551.
// Markers:
//   [test-marker] frog_registered_ok
//   [test-marker] frog_anim_walk_ok
//   [test-marker] frog_anim_idle_ok
//   [test-marker] frog_ptah_countdown_ok
//   [test-marker] frog_event_countdown_ok
//   [test-marker] frog_happiness_ok
//   [test-marker] frog_cheat_ok
//   [test-marker] frog_house_infest_ok
//   [test-marker] frog_saveload_ok

var GOD_PTAH = 2
var ACTION_FROG_CREATED = 120
var ACTION_FROG_GOING_TO_HOUSE = 121

function test113_fail(msg) {
    __log_info_native('[test:113] FAIL: ' + msg)
    __test_signal_ready()
}

function test113_house(pop) {
    var hid = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!hid) {
        hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!hid || __test_house_set_population(hid, pop) < 1) {
        return 0
    }
    return hid
}

// Ptah major is ~50% industry vs frogs — retry until the countdown starts.
function test113_try_ptah_frogs(max_tries) {
    for (var i = 0; i < max_tries; i++) {
        __test_run_console_command('god_major_curse ' + GOD_PTAH)
        if (__test_plagues_frogs_countdown() == 6 * 816) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:113] frog plague start')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)

    var probe = test_figure_create(FIGURE_FROG, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_FROG) {
        return test113_fail('FIGURE_FROG not registered')
    }
    __log_marker('frog_registered_ok')

    __test_figure_set_action(probe, ACTION_FROG_GOING_TO_HOUSE)
    __test_figure_update_animation(probe)
    var key = __figure_get_anim_key(probe)
    if (key != 'walk') {
        return test113_fail('anim key want "walk", got "' + key + '"')
    }
    __log_marker('frog_anim_walk_ok')

    __test_figure_set_action(probe, ACTION_FROG_CREATED)
    __test_figure_update_animation(probe)
    key = __figure_get_anim_key(probe)
    if (key != 'idle') {
        return test113_fail('anim key want "idle", got "' + key + '"')
    }
    __log_marker('frog_anim_idle_ok')
    city.figures.remove_figures(FIGURE_FROG)

    if (!test113_try_ptah_frogs(40)) {
        return test113_fail('Ptah curse: countdown=' + __test_plagues_frogs_countdown() + ' (want ' + 6 * 816 + ')')
    }
    __log_marker('frog_ptah_countdown_ok')

    var hid = test113_house(20)
    if (!hid) {
        return test113_fail('failed to create populated house for happiness')
    }
    __test_house_set_happiness(hid, 50)
    city.create_chain_event({ tag_id: 11301, type: EVENT_TYPE_FROGS, amount: 3, trigger: EVENT_TRIGGER_ONCE }).execute()
    if (__test_plagues_frogs_countdown() != 3 * 816) {
        return test113_fail('EVENT_TYPE_FROGS amount=3: countdown=' + __test_plagues_frogs_countdown())
    }
    __log_marker('frog_event_countdown_ok')

    var happiness = __test_house_happiness(hid)
    if (happiness != 35) {
        return test113_fail('happiness want 35, got ' + happiness)
    }
    __log_marker('frog_happiness_ok')

    __test_run_console_command('frog_plague')
    if (__test_plagues_frogs_countdown() != 6 * 816) {
        return test113_fail('frog_plague: countdown=' + __test_plagues_frogs_countdown())
    }
    __log_marker('frog_cheat_ok')

    var hid2 = test113_house(8)
    if (!hid2 || !__test_frog_infest_house(hid2)) {
        return test113_fail('infest_house failed')
    }
    var h2 = city.get_house(hid2)
    if (h2.frog_infest_days < 1 || h2.population != 0 || h2.population_room != 0 || h2.is_vacant_lot) {
        return test113_fail('infest: days=' + h2.frog_infest_days + ' pop=' + h2.population
            + ' room=' + h2.population_room + ' vacant=' + h2.is_vacant_lot)
    }
    __test_house_add_population(hid2, 3)
    if (city.get_house(hid2).population != 0) {
        return test113_fail('add_population must not refill an infested house')
    }
    __log_marker('frog_house_infest_ok')

    var days_before = city.get_house(hid2).frog_infest_days
    var save_name = 'test_113_frog.svx'
    if (!__game_write_savegame(save_name) || !__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        return test113_fail('save/load failed')
    }
    __game_delete_savegame(save_name)
    var h_sl = city.get_house(hid2)
    if (!h_sl || h_sl.frog_infest_days != days_before) {
        return test113_fail('after load frog_infest_days want ' + days_before + ', got ' + (h_sl ? h_sl.frog_infest_days : 'no-house'))
    }
    __log_marker('frog_saveload_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['frog_registered_ok', 'frog_anim_walk_ok', 'frog_anim_idle_ok', 'frog_ptah_countdown_ok',
        'frog_event_countdown_ok', 'frog_happiness_ok', 'frog_cheat_ok', 'frog_house_infest_ok', 'frog_saveload_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:113] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FROG)
}
