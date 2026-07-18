// Spawn FIGURE_HIPPO on land and water, run update_animation, assert walk vs swim.
// Markers:
//   [test-marker] hippo_land_anim_walk_ok
//   [test-marker] hippo_water_anim_swim_ok

// ACTION_10_HIPPO_GOING — moving state uses walk on land / swim on water.
var ACTION_HIPPO_GOING = 10

var __test40_land_ok = false
var __test40_water_ok = false

function test40_check_anim(fid, expected_key, tag) {
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[' + tag + '] figure missing')
        return false
    }
    if (__figure_get_type(fid) != FIGURE_HIPPO) {
        __log_info_native('[' + tag + '] wrong type')
        return false
    }

    __test_figure_set_action(fid, ACTION_HIPPO_GOING)
    __test_figure_update_animation(fid)

    var key = __figure_get_anim_key(fid)
    if (key != expected_key) {
        __log_info_native('[' + tag + '] anim key want "' + expected_key + '", got "' + key + '"')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:40] hippo land/water animation')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var land = { x: cx, y: cy }

    if (terrain.is(land, TERRAIN_WATER)) {
        __log_info_native('[test:40] map center is water; expected land')
        __test_signal_ready()
        return
    }

    var fid_land = test_figure_create(FIGURE_HIPPO, land.x, land.y)
    if (!test40_check_anim(fid_land, 'walk', 'test:40 land')) {
        __test_signal_ready()
        return
    }
    __log_marker('hippo_land_anim_walk_ok')
    __test40_land_ok = true
    city.figures.remove_figures(FIGURE_HIPPO)

    // Paint open water and spawn hippo on it.
    terrain.add(land, TERRAIN_WATER)
    if (!terrain.is(land, TERRAIN_WATER)) {
        __log_info_native('[test:40] failed to paint TERRAIN_WATER')
        __test_signal_ready()
        return
    }

    var fid_water = test_figure_create(FIGURE_HIPPO, land.x, land.y)
    if (!test40_check_anim(fid_water, 'swim', 'test:40 water')) {
        __test_signal_ready()
        return
    }
    __log_marker('hippo_water_anim_swim_ok')
    __test40_water_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test40_land_ok) {
        __log_info_native('[test:40] land anim check failed')
        return false
    }
    if (!__test40_water_ok) {
        __log_info_native('[test:40] water anim check failed')
        return false
    }

    var markers = ['hippo_land_anim_walk_ok', 'hippo_water_anim_swim_ok']
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:40] missing marker: ' + marker)
            return false
        }
    }
    return true
}
