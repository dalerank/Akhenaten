// OG building_state.c building_count_update: a building counts as active (god and education coverage, warnings)
// only while it works. Temples and scribal schools need workers; a shrine needs a road one or two tiles away
// on an axis (map_has_road_access_nearby); a working pavilion is also an active booth and bandstand.
// Akhenaten's count_active returned the total, so idle temples and roadless shrines still covered the city.

var __test635_ok = false

function test635_fail(msg) {
    __log_info_native('[test:635] FAIL: ' + msg)
    __test_signal_ready()
}

function test635_place(type) {
    var bid = test_building_place(type, -1, -1)
    if (!bid) {
        bid = __test_building_create(type, -1, -1)
    }
    return bid
}

function test635_active(type) {
    __test_city_buildings_update_counters()
    return city.count_active_buildings(type)
}

function test635_total(type) {
    __test_city_buildings_update_counters()
    return city.count_total_buildings(type)
}

function test635_check_temple() {
    var temple = test635_place(BUILDING_TEMPLE_OSIRIS)
    if (!temple) {
        test635_fail('temple placement failed')
        return false
    }
    __test_set_god_status(GOD_OSIRIS, 1)

    __test_building_set_workers(temple, 0)
    if (test635_total(BUILDING_TEMPLE_OSIRIS) != 1 || test635_active(BUILDING_TEMPLE_OSIRIS) != 0) {
        test635_fail('idle temple: total=' + test635_total(BUILDING_TEMPLE_OSIRIS)
            + ' active=' + test635_active(BUILDING_TEMPLE_OSIRIS) + ', want 1/0')
        return false
    }
    var idle_cov = __test_god_coverage_total(GOD_OSIRIS)
    if (idle_cov != 0) {
        test635_fail('idle temple must not cover Osiris, got ' + idle_cov)
        return false
    }

    __test_building_set_workers(temple, 8)
    var cov = __test_god_coverage_total(GOD_OSIRIS)
    if (test635_active(BUILDING_TEMPLE_OSIRIS) != 1 || cov != 750) {
        test635_fail('staffed temple: active=' + test635_active(BUILDING_TEMPLE_OSIRIS) + ' coverage=' + cov)
        return false
    }
    __log_marker('test635_temple_ok')
    return true
}

function test635_check_school() {
    var school = test635_place(BUILDING_SCRIBAL_SCHOOL)
    if (!school) {
        test635_fail('school placement failed')
        return false
    }
    __test_building_set_workers(school, 0)
    if (test635_active(BUILDING_SCRIBAL_SCHOOL) != 0) {
        test635_fail('idle school counted active')
        return false
    }
    __test_building_set_workers(school, 10)
    if (test635_active(BUILDING_SCRIBAL_SCHOOL) != 1) {
        test635_fail('staffed school not counted active')
        return false
    }
    __log_marker('test635_school_ok')
    return true
}

function test635_check_shrine() {
    var shrine = test635_place(BUILDING_SHRINE_RA)
    if (!shrine) {
        test635_fail('shrine placement failed')
        return false
    }
    var t = __building_tile(shrine)
    var nearby = [[0, -1], [1, 0], [0, 1], [-1, 0], [0, -2], [2, 0], [0, 2], [-2, 0], [1, 1], [3, 0]]
    for (var i = 0; i < nearby.length; i++) {
        terrain.remove({ x: t.x + nearby[i][0], y: t.y + nearby[i][1] }, TERRAIN_ROAD)
    }
    if (test635_total(BUILDING_SHRINE_RA) != 1 || test635_active(BUILDING_SHRINE_RA) != 0) {
        test635_fail('roadless shrine: total=' + test635_total(BUILDING_SHRINE_RA)
            + ' active=' + test635_active(BUILDING_SHRINE_RA) + ', want 1/0')
        return false
    }

    // road_access_distance 2: three tiles away is too far.
    terrain.add({ x: t.x + 3, y: t.y }, TERRAIN_ROAD)
    if (test635_active(BUILDING_SHRINE_RA) != 0) {
        test635_fail('a road three tiles away must not activate the shrine')
        return false
    }

    terrain.add({ x: t.x + 1, y: t.y + 1 }, TERRAIN_ROAD)
    if (test635_active(BUILDING_SHRINE_RA) != 0) {
        test635_fail('a diagonal road must not activate the shrine')
        return false
    }

    terrain.add({ x: t.x + 2, y: t.y }, TERRAIN_ROAD)
    if (test635_active(BUILDING_SHRINE_RA) != 1) {
        test635_fail('a road two tiles away on an axis must activate the shrine')
        return false
    }
    __log_marker('test635_shrine_ok')
    return true
}

function test635_check_pavilion() {
    var pavilion = test635_place(BUILDING_PAVILLION)
    if (!pavilion) {
        test635_fail('pavilion placement failed')
        return false
    }
    __test_building_set_workers(pavilion, 0)
    if (test635_active(BUILDING_BOOTH) + test635_active(BUILDING_BANDSTAND) + test635_active(BUILDING_PAVILLION) != 0) {
        test635_fail('idle pavilion counted active')
        return false
    }
    __test_building_set_workers(pavilion, 20)
    var booth = test635_active(BUILDING_BOOTH)
    var bandstand = test635_active(BUILDING_BANDSTAND)
    var own = test635_active(BUILDING_PAVILLION)
    if (booth != 1 || bandstand != 1 || own != 1 || test635_total(BUILDING_BOOTH) != 0) {
        test635_fail('staffed pavilion: booth=' + booth + ' bandstand=' + bandstand + ' pavilion=' + own
            + ' booth total=' + test635_total(BUILDING_BOOTH))
        return false
    }
    __log_marker('test635_pavilion_ok')
    return true
}

function run_test() {
    __log_info_native('[test:635] OG active building counts')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    if (!test635_check_temple() || !test635_check_school() || !test635_check_shrine() || !test635_check_pavilion()) {
        return
    }

    __test635_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test635_ok
        && __test_find_inlog('[test-marker] test635_temple_ok')
        && __test_find_inlog('[test-marker] test635_school_ok')
        && __test_find_inlog('[test-marker] test635_shrine_ok')
        && __test_find_inlog('[test-marker] test635_pavilion_ok')
}
