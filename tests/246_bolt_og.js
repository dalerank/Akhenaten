// FIG_BOLT / figure_bolt: OG figure_bolt_action —
// map_figure_find_target (same as javelin), arrow damage formula
// ((damage_base-def)/max_defense)*attack, attack from FIGURE_BOLT props.
// Markers:
//   [test-marker] bolt_hit_enemy_ok
//   [test-marker] bolt_hit_predator_ok
//   [test-marker] bolt_miss_citizen_ok
//   [test-marker] bolt_kill_ok

var __test246_ok = false
var __test246_shooter = 0
var __test246_cx = 0
var __test246_cy = 0
var __test246_slot = 1

function test246_fail(msg) {
    __log_info_native('[test:246] ' + msg)
    __test_signal_ready()
}

function test246_cleanup() {
    city.figures.remove_figures(FIGURE_BOLT)
    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_SPEAR)
    city.figures.remove_figures(FIGURE_HYENA)
    city.figures.remove_figures(FIGURE_WATER_CARRIER)
}

function test246_next_tile() {
    var t = { x: __test246_cx + __test246_slot, y: __test246_cy }
    __test246_slot++
    return t
}

function test246_fire_at(target_fid) {
    var tt = __figure_get_tile(target_fid)
    var mid = __test_missile_create(__test246_shooter, FIGURE_BOLT, tt.x, tt.y)
    if (!mid) {
        return -1
    }
    var before = __test_figure_get_damage(target_fid)
    __test_figure_action_perform(mid)
    var after = __test_figure_get_damage(target_fid)
    return after - before
}

function run_test() {
    __log_info_native('[test:246] FIG_BOLT / figure_bolt OG')

    test_ensure_city_session('data/default.map')
    __test246_cx = (__scenario_map.width / 2) | 0
    __test246_cy = (__scenario_map.height / 2) | 0

    // Shooter type unused for bolt attack (props of FIGURE_BOLT); warship is fine.
    __test246_shooter = test_figure_create(FIGURE_WARSHIP, __test246_cx, __test246_cy)
    if (!__test246_shooter) {
        return test246_fail('shooter create failed')
    }

    // Enemy spearman def=1, bolt attack=100 → ((30-1)/20)*100 = 100 → kills (max 50)
    test246_cleanup()
    var et = test246_next_tile()
    var enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, et.x, et.y)
    if (!enemy) {
        return test246_fail('enemy create failed')
    }
    var edmg = test246_fire_at(enemy)
    if (edmg < 0) {
        return test246_fail('enemy: bolt create failed')
    }
    if (__test_figure_is_alive(enemy) == 1) {
        return test246_fail('enemy: should die from bolt (delta=' + edmg + ')')
    }
    __log_marker('bolt_hit_enemy_ok')

    // Hyena def=0, max=100 → damage ((30-0)/20)*100 = 100; total==max → survives
    test246_cleanup()
    var pt = test246_next_tile()
    var hyena = test_figure_create(FIGURE_HYENA, pt.x, pt.y)
    if (!hyena) {
        return test246_fail('predator create failed')
    }
    var hdmg = test246_fire_at(hyena)
    if (hdmg != 100) {
        return test246_fail('predator: expected dmg 100, got ' + hdmg)
    }
    if (__test_figure_is_alive(hyena) != 1) {
        return test246_fail('predator: should survive at exactly max_damage')
    }
    __log_marker('bolt_hit_predator_ok')

    // Citizen not in is_attack_target
    test246_cleanup()
    var ct = test246_next_tile()
    var citizen = test_figure_create(FIGURE_WATER_CARRIER, ct.x, ct.y)
    if (!citizen) {
        return test246_fail('citizen create failed')
    }
    var cdmg = test246_fire_at(citizen)
    if (cdmg != 0) {
        return test246_fail('citizen: should miss, got dmg ' + cdmg)
    }
    __log_marker('bolt_miss_citizen_ok')

    // Explicit kill marker (enemy path already kills)
    __log_marker('bolt_kill_ok')

    __test246_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test246_ok
        && __test_find_inlog('[test-marker] bolt_hit_enemy_ok')
        && __test_find_inlog('[test-marker] bolt_hit_predator_ok')
        && __test_find_inlog('[test-marker] bolt_miss_citizen_ok')
        && __test_find_inlog('[test-marker] bolt_kill_ok')
}

