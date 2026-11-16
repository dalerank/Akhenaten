// FIGURE_LOCUST register + cloud anim + post_load; Osiris curse / EVENT / pak chain / console command
// start the OG countdown (-1: waits for the flood) without spawning locusts. OG behaviour itself: test 550.
// Markers:
//   [test-marker] locust_registered_ok
//   [test-marker] locust_anim_walk_ok
//   [test-marker] locust_post_load_ok
//   [test-marker] locust_osiris_countdown_ok
//   [test-marker] locust_event_countdown_ok
//   [test-marker] locust_cheat_ok
//   [test-marker] locust_pak_chain_ok

var GOD_OSIRIS = 0
var ACTION_LOCUST_GOING_TO_FIELD = 121

function test94_fail(msg) {
    __log_info_native('[test:94] FAIL: ' + msg)
    __test_signal_ready()
}

function test94_count_locusts() {
    return __test_count_figures(FIGURE_LOCUST)
}

// Osiris major is ~50% flood vs locusts — retry until the countdown starts.
function test94_try_locust_curse(max_tries) {
    for (var i = 0; i < max_tries; i++) {
        __test_plagues_set_locusts_countdown(0)
        __test_run_console_command('god_major_curse ' + GOD_OSIRIS)
        if (__test_plagues_locusts_countdown() == -1) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:94] locust plague start')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)

    var probe = test_figure_create(FIGURE_LOCUST, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_LOCUST) {
        return test94_fail('FIGURE_LOCUST not registered')
    }
    __log_marker('locust_registered_ok')

    __test_figure_set_action(probe, ACTION_LOCUST_GOING_TO_FIELD)
    __test_figure_update_animation(probe)
    var key = __figure_get_anim_key(probe)
    var variant = __test_locust_cloud_variant(probe)
    if (key != 'walk' || variant < 0 || variant > 4 || __test_figure_current_height(probe) <= 0) {
        return test94_fail('anim key=' + key + ' variant=' + variant + ' height=' + __test_figure_current_height(probe))
    }
    __log_marker('locust_anim_walk_ok')

    if (!__test_locust_post_load(probe)) {
        return test94_fail('on_post_load restore failed')
    }
    __log_marker('locust_post_load_ok')
    city.figures.remove_figures(FIGURE_LOCUST)

    if (!test94_try_locust_curse(40) || test94_count_locusts() != 0) {
        return test94_fail('Osiris curse: countdown=' + __test_plagues_locusts_countdown() + ' locusts=' + test94_count_locusts())
    }
    __log_marker('locust_osiris_countdown_ok')

    __test_plagues_set_locusts_countdown(0)
    city.create_chain_event({ tag_id: 9401, type: EVENT_TYPE_LOCUSTS, amount: 3, trigger: EVENT_TRIGGER_ONCE }).execute()
    if (__test_plagues_locusts_countdown() != -1 || test94_count_locusts() != 0) {
        return test94_fail('EVENT_TYPE_LOCUSTS: countdown=' + __test_plagues_locusts_countdown() + ' locusts=' + test94_count_locusts())
    }
    __log_marker('locust_event_countdown_ok')

    __test_plagues_set_locusts_countdown(0)
    __test_run_console_command('locust_start_plague')
    if (__test_plagues_locusts_countdown() != -1) {
        return test94_fail('console command: countdown=' + __test_plagues_locusts_countdown())
    }
    __log_marker('locust_cheat_ok')

    // Pak-style ONLY_VIA_EVENT chain (mission leaf type 24).
    __test_plagues_set_locusts_countdown(0)
    city.create_chain_event({ tag_id: 9420, type: EVENT_TYPE_LOCUSTS, amount: 2 })
    __city_event_fire_chain(9420)
    __test_process_scenario_events()
    if (__test_plagues_locusts_countdown() != -1) {
        return test94_fail('pak chain: countdown=' + __test_plagues_locusts_countdown())
    }
    __log_marker('locust_pak_chain_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['locust_registered_ok', 'locust_anim_walk_ok', 'locust_post_load_ok', 'locust_osiris_countdown_ok',
        'locust_event_countdown_ok', 'locust_cheat_ok', 'locust_pak_chain_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:94] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_LOCUST)
}
