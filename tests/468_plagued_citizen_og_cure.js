// Plagued citizen cure vs OG figure/military.c:350-367 figure_combat_attack_figure_at: a herbalist and a carrier on
// one tile end the carrier, whichever of them steps on the other's tile, also a carrier's corpse; a herbalist one
// tile away cures nothing. A priest of a Bast temple cures the same way, but only while the city's temple complex
// is Bast's and has its altar; a priest of another god never does.
// Markers:
//   [test-marker] plagued651_herbalist_ok
//   [test-marker] plagued651_herbalist_adjacent_ok
//   [test-marker] plagued651_herbalist_corpse_ok
//   [test-marker] plagued651_bast_needs_altar_ok
//   [test-marker] plagued651_bast_priest_ok
//   [test-marker] plagued651_other_priest_ok

function t468_fail(msg) {
    __log_info_native('[test:468] FAIL: ' + msg)
}

function t468_state(fid) {
    var f = city.get_figure(fid)
    return f ? f.state : FIGURE_STATE_NONE
}

function t468_alive(fid) {
    return __figure_is_valid(fid) && t468_state(fid) == FIGURE_STATE_ALIVE
}

function t468_gone(fid) {
    var s = t468_state(fid)
    return !__figure_is_valid(fid) || s == FIGURE_STATE_DEAD
}

function t468_road(x0, y, x1) {
    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return false
    }
    city_planner.update(x1, y)
    city_planner.construction_start(x0, y)
    city_planner.construction_update(x1, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    for (var x = x0; x <= x1; x++) {
        if (!terrain.is({ x: x, y: y }, TERRAIN_ROAD)) {
            return false
        }
    }
    return true
}

function t468_find_road_row() {
    var base = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!base) {
        return null
    }
    for (var tries = 0; tries < 6; tries++) {
        var ox = base.x - 3 + tries * 3
        var oy = base.y + tries * 3
        if (t468_road(ox, oy, ox + 8)) {
            return { x: ox, y: oy }
        }
    }
    return null
}

// The figure walking onto tile t meets everything already on it.
function t468_step_on(fid, t) {
    __test_figure_combat_attack_at(fid, t.x, t.y)
}

function t468_priest(temple, t) {
    var priest = test_figure_create(FIGURE_PRIEST, t.x, t.y)
    if (priest) {
        __test_figure_set_home(priest, temple)
    }
    return priest
}

function run_test() {
    __log_info_native('[test:468] OG plagued citizen cure')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    game.paused = true
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)

    var road = t468_find_road_row()
    if (!road) {
        t468_fail('road')
        __test_signal_ready()
        return
    }
    // One road tile per meeting: figures ended here stay on their tile until their next action.
    function at(i) {
        return { x: road.x + i, y: road.y }
    }

    var plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(0).x, at(0).y)
    var herbalist = test_figure_create(FIGURE_HERBALIST, at(0).x, at(0).y)
    t468_step_on(herbalist, at(0))
    if (!t468_gone(plagued) || !t468_alive(herbalist)) {
        t468_fail('herbalist steps on carrier: plagued=' + t468_state(plagued) + ' herbalist=' + t468_state(herbalist))
        __test_signal_ready()
        return
    }
    herbalist = test_figure_create(FIGURE_HERBALIST, at(1).x, at(1).y)
    plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(1).x, at(1).y)
    t468_step_on(plagued, at(1))
    if (!t468_gone(plagued) || !t468_alive(herbalist)) {
        t468_fail('carrier steps on herbalist: plagued=' + t468_state(plagued) + ' herbalist=' + t468_state(herbalist))
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_herbalist_ok')

    herbalist = test_figure_create(FIGURE_HERBALIST, at(2).x, at(2).y)
    plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(3).x, at(3).y)
    __test_figure_provide_service(herbalist)
    if (!t468_alive(plagued)) {
        t468_fail('herbalist cured a carrier on the next tile')
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_herbalist_adjacent_ok')

    __test_figure_kill(plagued)
    t468_step_on(herbalist, at(3))
    if (!t468_gone(plagued)) {
        t468_fail('herbalist left the carrier corpse, state=' + t468_state(plagued))
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_herbalist_corpse_ok')

    var bast = test_building_place(BUILDING_TEMPLE_BAST, -1, -1)
    var ra = test_building_place(BUILDING_TEMPLE_RA, -1, -1)
    if (!bast || !ra) {
        t468_fail('temples bast=' + bast + ' ra=' + ra)
        __test_signal_ready()
        return
    }
    plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(5).x, at(5).y)
    var priest = t468_priest(bast, at(5))
    t468_step_on(priest, at(5))
    if (!t468_alive(plagued)) {
        t468_fail('Bast priest cured without a complex')
        __test_signal_ready()
        return
    }
    var cid = test_building_place(BUILDING_TEMPLE_COMPLEX_BAST, -1, -1)
    var complex = city.get_temple_complex()
    if (!cid || !complex || complex.type != BUILDING_TEMPLE_COMPLEX_BAST) {
        t468_fail('bast complex place failed id=' + cid)
        __test_signal_ready()
        return
    }
    t468_step_on(priest, at(5))
    if (!t468_alive(plagued)) {
        t468_fail('Bast priest cured without the altar')
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_bast_needs_altar_ok')

    complex.temple_complex_upgrades = TEMPLE_COMPLEX_UPGRADE_ALTAR
    t468_step_on(priest, at(5))
    if (!t468_gone(plagued) || !t468_alive(priest)) {
        t468_fail('Bast priest steps on carrier: plagued=' + t468_state(plagued) + ' priest=' + t468_state(priest))
        __test_signal_ready()
        return
    }
    priest = t468_priest(bast, at(6))
    plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(6).x, at(6).y)
    t468_step_on(plagued, at(6))
    if (!t468_gone(plagued) || !t468_alive(priest)) {
        t468_fail('carrier steps on Bast priest: plagued=' + t468_state(plagued) + ' priest=' + t468_state(priest))
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_bast_priest_ok')

    var ra_priest = t468_priest(ra, at(7))
    plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, at(7).x, at(7).y)
    t468_step_on(ra_priest, at(7))
    t468_step_on(plagued, at(7))
    if (!t468_alive(plagued)) {
        t468_fail('Ra priest cured a carrier')
        __test_signal_ready()
        return
    }
    __log_marker('plagued651_other_priest_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['plagued651_herbalist_ok', 'plagued651_herbalist_adjacent_ok', 'plagued651_herbalist_corpse_ok',
        'plagued651_bast_needs_altar_ok', 'plagued651_bast_priest_ok', 'plagued651_other_priest_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:468] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)
}
