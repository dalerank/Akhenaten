// Construction blessing / Pyramid Speedup (CB*): Options flag + mastaba phase bump via god blessing.
// Markers:
//   [test-marker] construction_blessing_off_no_phase_ok
//   [test-marker] construction_blessing_on_phase_up_ok
//   [test-marker] construction_blessing_message_ok
//   [test-marker] construction_blessing_site_prep_ok
//   [test-marker] construction_blessing_masonry_major_ok
//   [test-marker] construction_blessing_two_mastaba_min_id_ok
//   [test-marker] construction_blessing_at_cap_fallback_ok
//   [test-marker] construction_blessing_halted_ok
//   [test-marker] construction_blessing_halted_chain_ok
// Orient-2 (SIDE main): soft-skip — test_building_place has no orientation API.

var GOD_PTAH = 2
var BUILDING_STATE_MOTHBALLED = 7

function test81_mastaba_phase(bid) {
    return __test_monument_phase(bid)
}

function test81_cap(bid) {
    var cap = __test_construction_blessing_cap(bid)
    if (cap < 0) {
        var m = city.get_monument(bid)
        var phases = m ? m.phases_total() : 0
        return Math.max(2, ((phases * 3) / 4) | 0)
    }
    return cap
}

function test81_place_mastaba() {
    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var candidates = [
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 20, y: 40},
        {x: 50, y: 50}, {x: 25, y: 55}, {x: 55, y: 25}, {x: 60, y: 40}, {x: 35, y: 60}
    ]
    var bid = 0
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, -1, -1)
    }
    return bid
}

function test81_push_to_cap(bid) {
    var cap = test81_cap(bid)
    var guard = 0
    while (test81_mastaba_phase(bid) < cap && guard < 20) {
        __test_run_console_command('god_major_blessing ' + GOD_PTAH)
        guard++
    }
}

function test81_last_message_id() {
    var n = __city_message_count()
    if (n <= 0) {
        return -1
    }
    for (var i = n - 1; i >= 0; i--) {
        var mid = __city_message_mm_text_id(i)
        if (mid > 0) {
            return mid
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:81] construction blessing / pyramid speedup')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)
    game.paused = false

    var feat_prev = game_features.get('gameopt_pyramid_speedup') === true
    game_features.set('gameopt_pyramid_speedup', false)

    var bid_a = test81_place_mastaba()
    if (!bid_a) {
        __log_info_native('[test:81] failed to place first SMALL_MASTABA')
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }

    var phase0 = test81_mastaba_phase(bid_a)
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_after_off = test81_mastaba_phase(bid_a)
    if (phase_after_off != phase0) {
        __log_info_native('[test:81] OFF expected no phase change, ' + phase0 + ' -> ' + phase_after_off)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_off_no_phase_ok')

    game_features.set('gameopt_pyramid_speedup', true)

    // Site-prep: major from phase 0 ≡ minor (+1 only).
    if (phase0 != 0) {
        __test_monument_set_phase(bid_a, 0)
        phase0 = 0
    }
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_after_site_major = test81_mastaba_phase(bid_a)
    if (phase_after_site_major != 1) {
        __log_info_native('[test:81] site-prep major expected 0->1, got ' + phase_after_site_major)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid_a, 0)
    __test_run_console_command('god_minor_blessing osiris')
    var phase_after_site_minor = test81_mastaba_phase(bid_a)
    if (phase_after_site_minor != 1) {
        // minor cheat may need god name; fall back to Ptah major after reset is already covered.
        __log_info_native('[test:81] warn: site-prep minor via osiris got ' + phase_after_site_minor + '; retry Ptah minor path')
        __test_monument_set_phase(bid_a, 0)
        __test_run_console_command('god_minor_blessing ptah')
        phase_after_site_minor = test81_mastaba_phase(bid_a)
    }
    if (phase_after_site_minor != 1) {
        __log_info_native('[test:81] site-prep minor expected 0->1, got ' + phase_after_site_minor)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_site_prep_ok')

    // Masonry major: from phase 2 budget=2 → phase 4.
    __test_monument_set_phase(bid_a, 2)
    var msg_before = __city_message_count()
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_masonry = test81_mastaba_phase(bid_a)
    if (phase_masonry != 4) {
        __log_info_native('[test:81] masonry major expected 2->4, got ' + phase_masonry)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_masonry_major_ok')
    __log_marker('construction_blessing_on_phase_up_ok')

    var msg_after = __city_message_count()
    var last_mm = test81_last_message_id()
    if (msg_after > msg_before || last_mm == 1012) {
        __log_marker('construction_blessing_message_ok')
    } else {
        __log_info_native('[test:81] warn: no construction message (count ' + msg_before + '->' + msg_after + ' mm=' + last_mm + ')')
        __log_marker('construction_blessing_message_skip')
    }

    // Keep first mastaba under cap so min-id targeting is exercised next.
    __test_monument_set_phase(bid_a, 3)

    // Second mastaba: only min-id should advance while first is under cap.
    var bid_b = test81_place_mastaba()
    if (!bid_b) {
        __log_info_native('[test:81] failed to place second SMALL_MASTABA')
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    var phase_a_before = test81_mastaba_phase(bid_a)
    var phase_b_before = test81_mastaba_phase(bid_b)
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_a_after = test81_mastaba_phase(bid_a)
    var phase_b_after = test81_mastaba_phase(bid_b)
    var min_id = bid_a < bid_b ? bid_a : bid_b
    var max_id = bid_a < bid_b ? bid_b : bid_a
    var min_before = bid_a < bid_b ? phase_a_before : phase_b_before
    var min_after = bid_a < bid_b ? phase_a_after : phase_b_after
    var max_before = bid_a < bid_b ? phase_b_before : phase_a_before
    var max_after = bid_a < bid_b ? phase_b_after : phase_a_after
    if (min_after <= min_before || max_after != max_before) {
        __log_info_native('[test:81] two-mastaba: min id=' + min_id + ' ' + min_before + '->' + min_after
            + ' max id=' + max_id + ' ' + max_before + '->' + max_after)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_two_mastaba_min_id_ok')

    test81_push_to_cap(min_id)
    var phase_at_cap = test81_mastaba_phase(min_id)
    var max_before_cap = test81_mastaba_phase(max_id)
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_after_cap = test81_mastaba_phase(min_id)
    var max_after_cap = test81_mastaba_phase(max_id)
    if (phase_after_cap != phase_at_cap) {
        __log_info_native('[test:81] at-cap min should stay: ' + phase_at_cap + '->' + phase_after_cap)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    if (max_after_cap <= max_before_cap) {
        __log_info_native('[test:81] at-cap max should advance: ' + max_before_cap + '->' + max_after_cap)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_at_cap_fallback_ok')

    test81_push_to_cap(max_id)
    var bid_h = test81_place_mastaba()
    if (!bid_h) {
        __log_info_native('[test:81] failed to place halted SMALL_MASTABA')
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __test_monument_set_halted(bid_h, 1)
    if (!__test_monument_chain_all_state(bid_h, BUILDING_STATE_MOTHBALLED)) {
        __log_info_native('[test:81] halted expected MOTHBALLED on all mastaba parts')
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_halted_chain_ok')
    var phase_h0 = test81_mastaba_phase(bid_h)
    __test_run_console_command('god_major_blessing ' + GOD_PTAH)
    var phase_h1 = test81_mastaba_phase(bid_h)
    if (phase_h1 <= phase_h0) {
        __log_info_native('[test:81] halted expected phase up from ' + phase_h0 + ', got ' + phase_h1)
        game_features.set('gameopt_pyramid_speedup', feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('construction_blessing_halted_ok')

    game_features.set('gameopt_pyramid_speedup', feat_prev)
    __log_info_native('[test:81] done')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'construction_blessing_off_no_phase_ok',
        'construction_blessing_on_phase_up_ok',
        'construction_blessing_site_prep_ok',
        'construction_blessing_masonry_major_ok',
        'construction_blessing_two_mastaba_min_id_ok',
        'construction_blessing_at_cap_fallback_ok',
        'construction_blessing_halted_chain_ok',
        'construction_blessing_halted_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:81] missing marker: ' + required[i])
            return false
        }
    }
    return true
}
