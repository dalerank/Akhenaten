// B14: ONLY_VIA leaf stays a template — second via re-fires (Iunet 1011 pottery/Hittite×48).
// Markers:
//   [test-marker] shared_leaf_kr_twice_ok
//   [test-marker] shared_leaf_iunet_1011_twice_ok
//   [test-marker] shared_leaf_burned_revive_ok

function test096_fail(msg) {
    __log_info_native('[test:096] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:096] B14 shared ONLY_VIA leaf re-fire')

    test_ensure_city_session('data/default.map')
    __test_kingdom_set_rating(50)

    city.create_chain_event({
        tag_id: 17701,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 5
    })
    __city_event_fire_chain(17701)
    __test_process_scenario_events()
    var kr1 = __test_kingdom_rating()
    if (kr1 !== 55) {
        test096_fail('first via want KR=55 got=' + kr1)
        return
    }

    __city_event_fire_chain(17701)
    __test_process_scenario_events()
    var kr2 = __test_kingdom_rating()
    if (kr2 !== 60) {
        test096_fail('second via want KR=60 got=' + kr2)
        return
    }
    __log_marker('shared_leaf_kr_twice_ok')

    // Mid-save path: burned facade + via must revive (prefer burned when no ONLY_VIA).
    city.create_chain_event({
        tag_id: 17702,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 3,
        trigger: EVENT_TRIGGER_ALREADY_FIRED
    })
    __test_kingdom_set_rating(40)
    __city_event_fire_chain(17702)
    __test_process_scenario_events()
    var kr_rev = __test_kingdom_rating()
    if (kr_rev !== 43) {
        test096_fail('burned revive want KR=43 got=' + kr_rev)
        return
    }
    __city_event_fire_chain(17702)
    __test_process_scenario_events()
    if (__test_kingdom_rating() !== 46) {
        test096_fail('burned revive second want KR=46 got=' + __test_kingdom_rating())
        return
    }
    __log_marker('shared_leaf_burned_revive_ok')

    __game_load_mission(16, 1)
    if (typeof mission16_ensure_pottery_leaves !== 'function') {
        test096_fail('mission16_ensure_pottery_leaves missing')
        return
    }
    mission16_ensure_pottery_leaves()
    __test_kingdom_set_rating(50)
    __city_event_fire_chain(1011)
    __test_process_scenario_events()
    if (__test_kingdom_rating() !== 60) {
        test096_fail('iunet 1011 first want KR=60 got=' + __test_kingdom_rating())
        return
    }
    __city_event_fire_chain(1011)
    __test_process_scenario_events()
    if (__test_kingdom_rating() !== 70) {
        test096_fail('iunet 1011 second want KR=70 got=' + __test_kingdom_rating())
        return
    }
    __log_marker('shared_leaf_iunet_1011_twice_ok')

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] shared_leaf_kr_twice_ok')
        && __test_find_inlog('[test-marker] shared_leaf_burned_revive_ok')
        && __test_find_inlog('[test-marker] shared_leaf_iunet_1011_twice_ok')
}
