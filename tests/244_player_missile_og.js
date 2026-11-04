// FIG_PLAYER_MISSILE / FIGURE_JAVELIN: OG figure_javelin_action.
// One file, several markers — cover is_attack_target hit/miss matrix and
// the ((20-def)*atk)/20 damage path (warship shooter → attack=6).
// Markers:
//   [test-marker] player_missile_hit_enemy_ok
//   [test-marker] player_missile_hit_predator_ok
//   [test-marker] player_missile_miss_citizen_ok
//   [test-marker] player_missile_miss_herd_ok
//   [test-marker] player_missile_kill_ok

var __test244_ok = false
var __test244_shooter = 0
var __test244_cx = 0
var __test244_cy = 0

function test244_fail(msg) {
    __log_info_native('[test:244] ' + msg)
    __test_signal_ready()
}

function test244_cleanup_targets() {
    city.figures.remove_figures(FIGURE_JAVELIN)
    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_SPEAR)
    city.figures.remove_figures(FIGURE_HYENA)
    city.figures.remove_figures(FIGURE_OSTRICH)
    city.figures.remove_figures(FIGURE_WATER_CARRIER)
}

// Fire a javelin onto the target's tile; return damage delta (or -1 on setup fail).
function test244_fire_at(target_fid) {
    var tt = __figure_get_tile(target_fid)
    var mid = __test_missile_create(__test244_shooter, FIGURE_JAVELIN, tt.x, tt.y)
    if (!mid) {
        return -1
    }
    var before = __test_figure_get_damage(target_fid)
    __test_figure_action_perform(mid)
    if (__test_figure_is_alive(mid) == 1) {
        // Miss path may leave the missile alive if move did not end — tick until gone
        // or treat as miss only when damage stayed put. Caller checks damage.
    }
    var after = __test_figure_get_damage(target_fid)
    return after - before
}

// Place each case on its own tile so leftover poofs cannot shadow the stack.
var __test244_slot = 1
function test244_next_tile() {
    var t = { x: __test244_cx + __test244_slot, y: __test244_cy }
    __test244_slot++
    return t
}

function test244_expect_hit(type, expect_dmg, label) {
    test244_cleanup_targets()
    var tile = test244_next_tile()
    var target = test_figure_create(type, tile.x, tile.y)
    if (!target) {
        return test244_fail(label + ': create failed type=' + type)
    }
    var got = test244_fire_at(target)
    if (got < 0) {
        return test244_fail(label + ': javelin create failed')
    }
    if (got != expect_dmg) {
        return test244_fail(label + ': expected dmg ' + expect_dmg + ', got ' + got)
    }
    return true
}

function test244_expect_miss(type, label) {
    test244_cleanup_targets()
    var tile = test244_next_tile()
    var target = test_figure_create(type, tile.x, tile.y)
    if (!target) {
        return test244_fail(label + ': create failed type=' + type)
    }
    var got = test244_fire_at(target)
    if (got < 0) {
        return test244_fail(label + ': javelin create failed')
    }
    if (got != 0) {
        return test244_fail(label + ': should miss, got dmg ' + got)
    }
    if (__test_figure_is_alive(target) != 1) {
        return test244_fail(label + ': non-target should stay alive')
    }
    return true
}

function run_test() {
    __log_info_native('[test:244] FIG_PLAYER_MISSILE / figure_javelin OG')

    test_ensure_city_session('data/default.map')

    __test244_cx = (__scenario_map.width / 2) | 0
    __test244_cy = (__scenario_map.height / 2) | 0

    __test244_shooter = test_figure_create(FIGURE_WARSHIP, __test244_cx, __test244_cy)
    if (!__test244_shooter) {
        return test244_fail('warship shooter create failed')
    }

    // Enemy: spearman missile_defense=1 → ((20-1)*6)/20 = 5
    if (!test244_expect_hit(FIGURE_ENEMY_EGYPTIAN_SPEAR, 5, 'enemy')) {
        return
    }
    __log_marker('player_missile_hit_enemy_ok')

    // Predator: hyena missile_defense=0 → ((20-0)*6)/20 = 6
    if (!test244_expect_hit(FIGURE_HYENA, 6, 'predator')) {
        return
    }
    __log_marker('player_missile_hit_predator_ok')

    // Citizen / walker: not in OG is_attack_target
    if (!test244_expect_miss(FIGURE_WATER_CARRIER, 'citizen')) {
        return
    }
    __log_marker('player_missile_miss_citizen_ok')

    // Herd prey: BIRDS..ANTELOPE — not an attack target for javelin
    if (!test244_expect_miss(FIGURE_OSTRICH, 'herd')) {
        return
    }
    __log_marker('player_missile_miss_herd_ok')

    // Kill: one hit of 5 on spearman (max_damage 50) from damage 46
    test244_cleanup_targets()
    var ktile = test244_next_tile()
    var prey = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, ktile.x, ktile.y)
    if (!prey) {
        return test244_fail('kill: create failed')
    }
    __test_figure_set_damage(prey, 46)
    var kdmg = test244_fire_at(prey)
    if (kdmg < 0) {
        return test244_fail('kill: javelin create failed')
    }
    if (__test_figure_is_alive(prey) == 1) {
        return test244_fail('kill: target should die (dmg delta=' + kdmg + ')')
    }
    __log_marker('player_missile_kill_ok')

    __test244_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test244_ok
        && __test_find_inlog('[test-marker] player_missile_hit_enemy_ok')
        && __test_find_inlog('[test-marker] player_missile_hit_predator_ok')
        && __test_find_inlog('[test-marker] player_missile_miss_citizen_ok')
        && __test_find_inlog('[test-marker] player_missile_miss_herd_ok')
        && __test_find_inlog('[test-marker] player_missile_kill_ok')
}
