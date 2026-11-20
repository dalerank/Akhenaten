// FIGURE_PHARAOH registered + walk anim (SprMain 28). Stub-only spawn.
// Markers:
//   [test-marker] pharaoh_spawn_ok
//   [test-marker] pharaoh_type_ok
//   [test-marker] pharaoh_anim_walk_ok
//   [test-marker] pharaoh_roam_action_ok
//   [test-marker] pharaoh_neighbor_ids_ok

var ACTION_PHARAOH_CREATED = 120
var ACTION_PHARAOH_ROAMING = 121

var __test538_spawn_ok = false
var __test538_type_ok = false
var __test538_anim_ok = false
var __test538_roam_ok = false
var __test538_neighbors_ok = false

function run_test() {
    __log_info_native('[test:538] pharaoh figure smoke (BF4)')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // Neighbor ids 108–110 must remain distinct registrations (BF4 acceptance).
    var artisan = test_figure_create(FIGURE_TOMB_ARTISAN, cx - 1, cy)
    var mummy = test_figure_create(FIGURE_MUMMY, cx + 1, cy)
    var fid = test_figure_create(FIGURE_PHARAOH, cx, cy)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:538] failed to create FIGURE_PHARAOH')
        __test_signal_ready()
        return
    }
    if (!artisan || __figure_get_type(artisan) != FIGURE_TOMB_ARTISAN
        || !mummy || __figure_get_type(mummy) != FIGURE_MUMMY
        || __figure_get_type(fid) != FIGURE_PHARAOH) {
        __log_info_native('[test:538] neighbor id regression 108/109/110')
        __test_signal_ready()
        return
    }
    __test_figure_kill(artisan)
    __test_figure_kill(mummy)
    __log_marker('pharaoh_neighbor_ids_ok')
    __test538_neighbors_ok = true

    __log_marker('pharaoh_spawn_ok')
    __test538_spawn_ok = true

    if (__figure_get_type(fid) != FIGURE_PHARAOH) {
        __log_info_native('[test:538] wrong type after create: ' + __figure_get_type(fid))
        __test_signal_ready()
        return
    }
    __log_marker('pharaoh_type_ok')
    __test538_type_ok = true

    __test_figure_set_action(fid, ACTION_PHARAOH_CREATED)
    __test_figure_action_perform(fid)
    var action = __figure_get_action_state(fid)
    if (action != ACTION_PHARAOH_ROAMING) {
        __log_info_native('[test:538] expected ROAMING 121 after CREATED, got ' + action)
        __test_signal_ready()
        return
    }
    __log_marker('pharaoh_roam_action_ok')
    __test538_roam_ok = true

    __test_figure_update_animation(fid)
    var key = __figure_get_anim_key(fid)
    if (key != 'walk') {
        __log_info_native('[test:538] anim key want "walk", got "' + key + '"')
        __test_signal_ready()
        return
    }
    __log_marker('pharaoh_anim_walk_ok')
    __test538_anim_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test538_spawn_ok || !__test538_type_ok || !__test538_roam_ok
        || !__test538_anim_ok || !__test538_neighbors_ok) {
        __log_info_native('[test:538] flag check failed')
        return false
    }

    var markers = [
        'pharaoh_neighbor_ids_ok',
        'pharaoh_spawn_ok',
        'pharaoh_type_ok',
        'pharaoh_roam_action_ok',
        'pharaoh_anim_walk_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:538] missing marker: ' + marker)
            return false
        }
    }
    return true
}
