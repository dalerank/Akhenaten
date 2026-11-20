// Spawn FIGURE_SCORPION, set moving action, update_animation → walk (Expansion SprMain2 group 10).
// Markers:
//   [test-marker] scorpion_spawn_ok
//   [test-marker] scorpion_anim_walk_ok
//   [test-marker] scorpion_type_ok

// ACTION_10_SCORPION_MOVING — uses walk anim
var ACTION_SCORPION_MOVING = 10

var __test490_spawn_ok = false
var __test490_anim_ok = false
var __test490_type_ok = false

function run_test() {
    __log_info_native('[test:490] scorpion spawn + walk anim (CF3c)')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var land = { x: cx, y: cy }

    if (terrain.is(land, TERRAIN_WATER)) {
        __log_info_native('[test:490] map center is water; expected land')
        __test_signal_ready()
        return
    }

    var fid = test_figure_create(FIGURE_SCORPION, land.x, land.y)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:490] failed to create FIGURE_SCORPION')
        __test_signal_ready()
        return
    }
    __log_marker('scorpion_spawn_ok')
    __test490_spawn_ok = true

    if (__figure_get_type(fid) != FIGURE_SCORPION) {
        __log_info_native('[test:490] wrong type after create')
        __test_signal_ready()
        return
    }
    __log_marker('scorpion_type_ok')
    __test490_type_ok = true

    __test_figure_set_action(fid, ACTION_SCORPION_MOVING)
    __test_figure_update_animation(fid)

    var key = __figure_get_anim_key(fid)
    if (key != 'walk') {
        __log_info_native('[test:490] anim key want "walk", got "' + key + '"')
        __test_signal_ready()
        return
    }
    __log_marker('scorpion_anim_walk_ok')
    __test490_anim_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test490_spawn_ok) {
        __log_info_native('[test:490] spawn check failed')
        return false
    }
    if (!__test490_type_ok) {
        __log_info_native('[test:490] type check failed')
        return false
    }
    if (!__test490_anim_ok) {
        __log_info_native('[test:490] anim check failed')
        return false
    }

    var markers = ['scorpion_spawn_ok', 'scorpion_type_ok', 'scorpion_anim_walk_ok']
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:490] missing marker: ' + marker)
            return false
        }
    }
    return true
}
