// Carpenter guild OG: progress>=400 (cap 400) + timber load dispatch, staffing 1-4,
// site-poof after work. Statue service stays behind gameplay feature flag.
// Markers:
//   [test-marker] carpenter_staffing_ok
//   [test-marker] carpenter_progress_gate_ok
//   [test-marker] carpenter_progress_cap_ok
//   [test-marker] carpenter_dispatch_ok
//   [test-marker] carpenter_statue_flag_off_ok

var __test258_ok = false

function test258_fail(msg) {
    __log_info_native('[test:258] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:258] carpenter OG')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(100000)

    if (!__scenario_building_allowed(BUILDING_CARPENTERS_GUILD)) {
        __scenario_building_allow(BUILDING_CARPENTERS_GUILD, true)
    }
    if (!__scenario_building_allowed(BUILDING_SMALL_OBELISK)) {
        __scenario_building_allow(BUILDING_SMALL_OBELISK, true)
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var gid = __test_building_create(BUILDING_CARPENTERS_GUILD, cx, cy)
    if (!gid) {
        return test258_fail('create guild failed')
    }
    __test_building_force_road_access(gid)
    __test_building_set_workers(gid, 8)

    var guild = city.get_building(gid)
    if (!guild) {
        return test258_fail('guild lookup failed')
    }

    // Full staff → max 4 concurrent carpenters.
    if (guild.num_workers < 8) {
        return test258_fail('expected full staff')
    }
    __log_marker('carpenter_staffing_ok')

    // Progress gate: no spawn below 400 even with timber + monument.
    guild.progress = 0
    guild.store_resource(RESOURCE_TIMBER, 200)

    var granite_need = 100
    var gy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, cx + 6, cy)
    if (!gy) {
        gy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, -1, -1)
    }
    var oid = __test_building_create(BUILDING_SMALL_OBELISK, cx + 10, cy)
    if (!oid) {
        return test258_fail('create obelisk failed')
    }
    __test_monument_set_phase(oid, 0)

    var before = __test_count_figures(FIGURE_CARPENTER)
    __test_building_spawn_figure(gid)
    if (__test_count_figures(FIGURE_CARPENTER) != before) {
        return test258_fail('must not spawn below progress 400')
    }
    __log_marker('carpenter_progress_gate_ok')

    // OG industry max for carpenter guild is 400 (2 * PROGRESS_DONE), not 800.
    guild.progress = 0
    for (var d = 0; d < 80; d++) {
        __test_building_update_day(gid)
    }
    if (guild.progress > 400) {
        return test258_fail('progress cap want <=400, got ' + guild.progress)
    }
    if (guild.progress != 400) {
        // 8 workers/day → hits 400 in 50 days; 80 days must sit at cap.
        return test258_fail('progress should sit at 400 after long staffed run, got ' + guild.progress)
    }
    __log_marker('carpenter_progress_cap_ok')

    guild.progress = 400
    var timber0 = guild.stored_resource(RESOURCE_TIMBER)
    before = __test_count_figures(FIGURE_CARPENTER)
    __test_building_spawn_figure(gid)
    var after = __test_count_figures(FIGURE_CARPENTER)
    if (after != before + 1) {
        return test258_fail('expected one carpenter after ready progress, before='
            + before + ' after=' + after)
    }
    var timber1 = guild.stored_resource(RESOURCE_TIMBER)
    if (timber1 != timber0 - 100) {
        return test258_fail('timber deduct want -100, before=' + timber0 + ' after=' + timber1)
    }
    if (guild.progress != 0) {
        return test258_fail('progress should reset on dispatch, got ' + guild.progress)
    }

    // Dispatched carpenter should already be heading to the monument (ACTION_1).
    var found_going = false
    for (var i = 1; i < 2000; i++) {
        var f = city.get_figure(i)
        if (!f || !f.valid || f.type != FIGURE_CARPENTER) {
            continue
        }
        if (f.action_state == ACTION_1_CARPENTER_GO_TO_SITE
            || f.action_state == ACTION_2_CARPENTER_WORK
            || f.action_state == ACTION_4_CARPENTER_CLIMB_RAMP) {
            found_going = true
            break
        }
    }
    if (!found_going) {
        return test258_fail('dispatched carpenter not going to site')
    }
    __log_marker('carpenter_dispatch_ok')

    // Statue service is Enhanced-only; with flag off and no monument need, no spawn.
    __test_monument_set_phase(oid, 5) // finished-ish: no carpenter need
    guild.progress = 400
    guild.store_resource(RESOURCE_TIMBER, 100)
    before = __test_count_figures(FIGURE_CARPENTER)
    // Poof existing carpenters so capacity is free.
    for (var j = 1; j < 2000; j++) {
        var fj = city.get_figure(j)
        if (fj && fj.valid && fj.type == FIGURE_CARPENTER) {
            __test_figure_kill(j)
        }
    }
    __test_pump_frames(2)
    before = __test_count_figures(FIGURE_CARPENTER)
    __test_building_spawn_figure(gid)
    if (__test_count_figures(FIGURE_CARPENTER) != before) {
        return test258_fail('statue service must stay off without feature flag')
    }
    __log_marker('carpenter_statue_flag_off_ok')

    __test258_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test258_ok
        && __test_find_inlog('[test-marker] carpenter_staffing_ok')
        && __test_find_inlog('[test-marker] carpenter_progress_gate_ok')
        && __test_find_inlog('[test-marker] carpenter_progress_cap_ok')
        && __test_find_inlog('[test-marker] carpenter_dispatch_ok')
        && __test_find_inlog('[test-marker] carpenter_statue_flag_off_ok')
}
