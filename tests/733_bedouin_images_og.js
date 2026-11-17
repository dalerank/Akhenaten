// FIGURE_BEDOUIN images and movement vs OG figure/enemy.c enemy_foot_action(ENEMY_FOOT_BEDOUIN):
// walk / attack / corpse come from IMAGE_GROUP_FIGURE_BEDOUIN 590, _ATTACK 592, _DEATH 591 (SprAmbient 13, 15,
// 14), speed 8 walks 1, 1, 2 ticks per tick (movement.c figure_movement_move_ticks), and a Bedouin whose
// formation is a herd dies (enemy.c:548).
// Markers:
//   [test-marker] bedouin_image_groups_ok
//   [test-marker] bedouin_images_per_action_ok
//   [test-marker] bedouin_move_cycle_ok
//   [test-marker] bedouin_herd_formation_dies_ok

var T733_ACTION_CORPSE = 149
var T733_ACTION_MARCHING = 153
var T733_ACTION_ATTACK = 154

function test733_fail(msg) {
    __log_info_native('[test:733] FAIL: ' + msg)
}

function test733_groups() {
    var a = figure_bedouin.animations
    var groups = [[a.walk, 13], [a.death, 14], [a.attack, 15]]
    for (var i = 0; i < groups.length; i++) {
        if (groups[i][0].pack != PACK_SPR_AMBIENT || groups[i][0].id != groups[i][1]) {
            test733_fail('animation ' + i + ' is pack ' + groups[i][0].pack + ' id ' + groups[i][0].id
                + ', want SprAmbient ' + groups[i][1])
            return
        }
    }
    __log_marker('bedouin_image_groups_ok')
}

function test733_images(fid) {
    var cases = [[T733_ACTION_MARCHING, 'walk'], [T733_ACTION_ATTACK, 'attack'], [T733_ACTION_CORPSE, 'death']]
    for (var i = 0; i < cases.length; i++) {
        __test_figure_set_action(fid, cases[i][0])
        __test_figure_update_animation(fid)
        var key = __test_figure_anim_key(fid)
        if (key != cases[i][1]) {
            test733_fail('action ' + cases[i][0] + ' anim ' + key + ' want ' + cases[i][1])
            return
        }
    }
    __log_marker('bedouin_images_per_action_ok')
}

function test733_move_cycle(fid) {
    var got = []
    for (var i = 0; i < 6; i++) {
        got.push(__test_bedouin_walk_ticks(fid))
    }
    if (got.join(',') != '1,1,2,1,1,2') {
        test733_fail('move cycle ' + got.join(',') + ' want 1,1,2,1,1,2')
        return
    }
    __log_marker('bedouin_move_cycle_ok')
}

function test733_herd() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    __test_invasion_points_clear()
    __test_invasion_land_point_set(0, 0, (__scenario_map.height / 2) | 0)
    city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_13_BEDOUIN,
        size: 4,
        invasion_id: 1,
        tilex: 0,
        tiley: (__scenario_map.height / 2) | 0,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
    var fid = __test_first_figure_of_type(FIGURE_BEDOUIN)
    var formation = fid ? __test_figure_get_formation_id(fid) : 0
    if (!fid || !formation) {
        test733_fail('herd: no bedouin army, fid=' + fid + ' formation=' + formation)
        return
    }
    __test_figure_action_perform(fid)
    if (__test_figure_is_alive(fid) != 1) {
        test733_fail('herd: bedouin of an enemy formation died')
        return
    }
    __test_formation_set_herd(formation, 1)
    __test_figure_action_perform(fid)
    if (__test_figure_is_alive(fid) != 0) {
        test733_fail('herd: bedouin of a herd formation still alive')
        return
    }
    __log_marker('bedouin_herd_formation_dies_ok')
}

function run_test() {
    __log_info_native('[test:733] OG Bedouin images')
    test733_groups()

    test_reload_city_session('data/default.map')
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var fid = test_figure_create(FIGURE_BEDOUIN, cx, cy)
    if (!fid) {
        test733_fail('no bedouin created')
    } else {
        test733_move_cycle(fid)
        test733_images(fid)
    }

    test733_herd()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'bedouin_image_groups_ok',
        'bedouin_images_per_action_ok',
        'bedouin_move_cycle_ok',
        'bedouin_herd_formation_dies_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:733] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
