// FIG_ENEMY_MISSILE / FIGURE_SPEAR: OG figure_spear_action —
// missile_hit_target band (< native | transport..warship),
// attack from FIGURE_SPEAR props (ships: shooter type),
// ((damage_base-def)/max_defense)*attack, ship HP + dead-shooter abort.
// Markers:
//   [test-marker] enemy_missile_hit_infantry_ok
//   [test-marker] enemy_missile_miss_enemy_ok
//   [test-marker] enemy_missile_miss_predator_ok
//   [test-marker] enemy_missile_miss_citizen_ok
//   [test-marker] enemy_missile_kill_ok
//   [test-marker] enemy_missile_ship_hit_ok
//   [test-marker] enemy_missile_dead_shooter_ship_ok

var __test204_ok = false
var __test204_shooter = 0
var __test204_cx = 0
var __test204_cy = 0
var __test204_slot = 1

function test204_fail(msg) {
    __log_info_native('[test:204] ' + msg)
    __test_signal_ready()
}

function test204_cleanup() {
    city.figures.remove_figures(FIGURE_SPEAR)
    city.figures.remove_figures(FIGURE_INFANTRY)
    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_SPEAR)
    city.figures.remove_figures(FIGURE_HYENA)
    city.figures.remove_figures(FIGURE_WATER_CARRIER)
    city.figures.remove_figures(FIGURE_WARSHIP)
}

function test204_next_tile() {
    var t = { x: __test204_cx + __test204_slot, y: __test204_cy }
    __test204_slot++
    return t
}

function test204_fire_at(target_fid) {
    var tt = __figure_get_tile(target_fid)
    var mid = __test_missile_create(__test204_shooter, FIGURE_SPEAR, tt.x, tt.y)
    if (!mid) {
        return -1
    }
    var before = __test_figure_get_damage(target_fid)
    __test_figure_action_perform(mid)
    var after = __test_figure_get_damage(target_fid)
    return after - before
}

function run_test() {
    __log_info_native('[test:204] FIG_ENEMY_MISSILE / figure_spear OG')

    test_ensure_city_session('data/default.map')
    __test204_cx = (__scenario_map.width / 2) | 0
    __test204_cy = (__scenario_map.height / 2) | 0

    // Shooter type unused for non-ship hits (attack from FIGURE_SPEAR=20).
    __test204_shooter = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, __test204_cx, __test204_cy)
    if (!__test204_shooter) {
        return test204_fail('shooter create failed')
    }

    // Infantry def=0, spear attack=20 → ((30-0)/20)*20 = 20 (int div)
    test204_cleanup()
    var it = test204_next_tile()
    var infantry = test_figure_create(FIGURE_INFANTRY, it.x, it.y)
    if (!infantry) {
        return test204_fail('infantry create failed')
    }
    __test_figure_set_faction(infantry, 1)
    var idmg = test204_fire_at(infantry)
    if (idmg != 20) {
        return test204_fail('infantry: expected dmg 20, got ' + idmg)
    }
    __log_marker('enemy_missile_hit_infantry_ok')

    // Enemy types sit in native..transport gap — missile_hit_target skips them
    test204_cleanup()
    var et = test204_next_tile()
    var enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, et.x, et.y)
    if (!enemy) {
        return test204_fail('enemy create failed')
    }
    var edmg = test204_fire_at(enemy)
    if (edmg != 0) {
        return test204_fail('enemy: should miss, got dmg ' + edmg)
    }
    __log_marker('enemy_missile_miss_enemy_ok')

    // Hyena (83) > WARSHIP (78) — outside hit band
    test204_cleanup()
    var pt = test204_next_tile()
    var hyena = test_figure_create(FIGURE_HYENA, pt.x, pt.y)
    if (!hyena) {
        return test204_fail('predator create failed')
    }
    var hdmg = test204_fire_at(hyena)
    if (hdmg != 0) {
        return test204_fail('predator: should miss, got dmg ' + hdmg)
    }
    __log_marker('enemy_missile_miss_predator_ok')

    // Water carrier (87) > WARSHIP — miss
    test204_cleanup()
    var ct = test204_next_tile()
    var citizen = test_figure_create(FIGURE_WATER_CARRIER, ct.x, ct.y)
    if (!citizen) {
        return test204_fail('citizen create failed')
    }
    var cdmg = test204_fire_at(citizen)
    if (cdmg != 0) {
        return test204_fail('citizen: should miss, got dmg ' + cdmg)
    }
    __log_marker('enemy_missile_miss_citizen_ok')

    // Kill: infantry max 150, one hit of 20 from damage 131 → total 151 > 150
    test204_cleanup()
    var kt = test204_next_tile()
    var prey = test_figure_create(FIGURE_INFANTRY, kt.x, kt.y)
    if (!prey) {
        return test204_fail('kill: create failed')
    }
    __test_figure_set_faction(prey, 1)
    __test_figure_set_damage(prey, 131)
    var kdmg = test204_fire_at(prey)
    if (kdmg < 0) {
        return test204_fail('kill: spear create failed')
    }
    if (__test_figure_is_alive(prey) == 1) {
        return test204_fail('kill: target should die (delta=' + kdmg + ')')
    }
    __log_marker('enemy_missile_kill_ok')

    // Ship: attack from shooter (archer=6) → ((30-0)/20)*6 = 6
    test204_cleanup()
    __test204_shooter = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, __test204_cx, __test204_cy)
    if (!__test204_shooter) {
        return test204_fail('ship shooter create failed')
    }
    var st = test204_next_tile()
    var ship = test_figure_create(FIGURE_WARSHIP, st.x, st.y)
    if (!ship) {
        return test204_fail('warship create failed')
    }
    __test_figure_set_faction(ship, 1)
    var sdmg = test204_fire_at(ship)
    if (sdmg != 6) {
        return test204_fail('ship: expected dmg 6, got ' + sdmg)
    }
    if (__test_figure_is_alive(ship) != 1) {
        return test204_fail('ship: should survive one hit')
    }
    __log_marker('enemy_missile_ship_hit_ok')

    // Dead shooter vs ship: spear poofs, no damage
    test204_cleanup()
    __test204_shooter = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, __test204_cx, __test204_cy)
    if (!__test204_shooter) {
        return test204_fail('dead-shooter setup failed')
    }
    var dst = test204_next_tile()
    var dship = test_figure_create(FIGURE_WARSHIP, dst.x, dst.y)
    if (!dship) {
        return test204_fail('dead-shooter warship create failed')
    }
    __test_figure_set_faction(dship, 1)
    var before = __test_figure_get_damage(dship)
    var mid = __test_missile_create(__test204_shooter, FIGURE_SPEAR, dst.x, dst.y)
    if (!mid) {
        return test204_fail('dead-shooter spear create failed')
    }
    __test_figure_kill(__test204_shooter)
    __test_figure_action_perform(mid)
    var after = __test_figure_get_damage(dship)
    if (after != before) {
        return test204_fail('dead shooter: ship should take no damage')
    }
    if (__test_figure_is_alive(mid) == 1) {
        return test204_fail('dead shooter: spear should poof')
    }
    __log_marker('enemy_missile_dead_shooter_ship_ok')

    __test204_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test204_ok
        && __test_find_inlog('[test-marker] enemy_missile_hit_infantry_ok')
        && __test_find_inlog('[test-marker] enemy_missile_miss_enemy_ok')
        && __test_find_inlog('[test-marker] enemy_missile_miss_predator_ok')
        && __test_find_inlog('[test-marker] enemy_missile_miss_citizen_ok')
        && __test_find_inlog('[test-marker] enemy_missile_kill_ok')
        && __test_find_inlog('[test-marker] enemy_missile_ship_hit_ok')
        && __test_find_inlog('[test-marker] enemy_missile_dead_shooter_ship_ok')
}
