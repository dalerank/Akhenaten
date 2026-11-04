// Military Academy OG: unique city building, labor-seeker only (no magistrate walker),
// full staffing required before recruits train there.
// Markers:
//   [test-marker] academy_unique_ok
//   [test-marker] academy_no_magistrate_ok
//   [test-marker] academy_full_staff_train_ok

var __test256_ok = false

function test256_fail(msg) {
    __log_info_native('[test:256] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:256] military academy OG')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(100000)

    if (!__scenario_building_allowed(BUILDING_MILITARY_ACADEMY)) {
        __scenario_building_allow(BUILDING_MILITARY_ACADEMY, true)
    }
    if (!__scenario_building_allowed(BUILDING_RECRUITER)) {
        __scenario_building_allow(BUILDING_RECRUITER, true)
    }
    if (!__scenario_building_allowed(BUILDING_FORT_ARCHERS)) {
        __scenario_building_allow(BUILDING_FORT_ARCHERS, true)
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var aid = __test_building_create(BUILDING_MILITARY_ACADEMY, cx, cy)
    if (!aid) {
        return test256_fail('create academy failed')
    }
    if (!building_is_unique_built(BUILDING_MILITARY_ACADEMY)) {
        return test256_fail('academy should be unique once placed')
    }
    __log_marker('academy_unique_ok')

    var before_mag = __test_count_figures(FIGURE_MAGISTRATE)
    var before_seek = __test_count_figures(FIGURE_LABOR_SEEKER)
    __test_building_set_workers(aid, 25)
    __test_building_spawn_figure(aid)
    if (__test_count_figures(FIGURE_MAGISTRATE) != before_mag) {
        return test256_fail('academy must not spawn magistrates')
    }
    if (__test_count_figures(FIGURE_LABOR_SEEKER) < before_seek) {
        return test256_fail('labor seeker count dropped unexpectedly')
    }
    __log_marker('academy_no_magistrate_ok')

    // Understaffed academy must not train recruits (experience stays no-academy path).
    __test_building_set_workers(aid, 10)
    var rid = __test_building_create(BUILDING_RECRUITER, cx + 8, cy)
    var fort = __test_building_create(BUILDING_FORT_ARCHERS, cx + 12, cy)
    if (!rid || !fort) {
        return test256_fail('create recruiter/fort failed')
    }
    __test_fort_update_recruit_status(fort)
    var fid = city.get_building(fort).formation_id
    __test_formation_set_experience(fid, 40)
    if (!__test_recruiter_create_soldier(rid)) {
        return test256_fail('create_soldier failed understaffed academy')
    }
    var form = city.get_formation(fid)
    if (!form || form.experience != 20) {
        return test256_fail('understaffed academy must not train, want exp 20 got '
            + (form ? form.experience : 'null'))
    }

    // Full staff: academy bonus averages into experience.
    __test_building_set_workers(aid, 25)
    __test_formation_set_experience(fid, 40)
    if (!__test_recruiter_create_soldier(rid)) {
        return test256_fail('create_soldier failed full academy')
    }
    form = city.get_formation(fid)
    // With academy training 25 and prior 40, OG average is not the no-academy 20.
    if (!form || form.experience == 20) {
        return test256_fail('full academy should change experience from no-academy 20, got '
            + (form ? form.experience : 'null'))
    }
    __log_marker('academy_full_staff_train_ok')

    __test256_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test256_ok
        && __test_find_inlog('[test-marker] academy_unique_ok')
        && __test_find_inlog('[test-marker] academy_no_magistrate_ok')
        && __test_find_inlog('[test-marker] academy_full_staff_train_ok')
}
