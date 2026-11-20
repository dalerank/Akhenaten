// OG follow_on_ground (laborer.c): a train member sets its bridge target height only when it steps onto a
// new tile (MOVEMENT_BRIDGE_CLIMB_TICKS, then the counter runs down), not every tick like a walker of the
// generic figure loop. The leader is driven by hand across a low bridge; only the train members act.

var ACTION_17_LABORER_TO_PYRAMID = 17
var DIR_4_BOTTOM_LEFT = 4
var BRIDGE_CLIMB_TICKS = 18
var STEPS_PER_TILE = 15
var TILE_CHANGE_STEP = 8

var t428_ok = false

function t428_fail(msg) {
    __log_info_native('[test:428] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:428] sled train bridge height')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_LOW_BRIDGE, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var start = test_prepare_bridge_channel(cx, cy, 3, 4)
    if (!__map_bridge_calculate_valid(start, false) || __map_bridge_add(start, false) < 2) {
        return t428_fail('bridge not placed')
    }
    var bridge_tiles = 0
    for (var by = cy - 1; by <= cy + 4; by++) {
        if (__map_is_bridge({x: cx, y: by})) {
            bridge_tiles++
        }
    }
    if (bridge_tiles < 2) {
        return t428_fail('bridge does not run along y, tiles=' + bridge_tiles)
    }

    var x = cx
    var y = cy - 3
    var lab = __test_figure_create(FIGURE_LABORER, x, y)
    __test_figure_set_collecting_item(lab, RESOURCE_STONE)
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)
    __test_figure_set_direction(lab, DIR_4_BOTTOM_LEFT)
    if (__pyramid_spawn_sled_train(lab, 1) != 6) {
        return t428_fail('train not spawned')
    }
    var puller = __pyramid_train_member(lab, 1)
    var members = []
    for (var m = 1; m <= 6; m++) {
        members.push(__pyramid_train_member(lab, m))
    }

    var bridge_steps = 0
    var countdown_ok = 0
    var prev_tile = ''
    var prev_ticks = -1
    for (var s = 1; s < STEPS_PER_TILE * 9; s++) {
        var p = s % STEPS_PER_TILE
        if (p == TILE_CHANGE_STEP) {
            y++
            __test_figure_set_tile_raw(lab, x, y)
        }
        __test_figure_set_progress_on_tile(lab, p)
        for (var j = 0; j < members.length; j++) {
            __test_figure_action_perform(members[j])
        }
        if (!__test_figure_is_alive(puller)) {
            return t428_fail('puller died at step ' + s)
        }
        var px = __test_figure_tile_x(puller)
        var py = __test_figure_tile_y(puller)
        var tile_key = px + ',' + py
        var ticks = __test_figure_height_adjusted_ticks(puller)
        if (__map_is_bridge({x: px, y: py})) {
            if (tile_key != prev_tile) {
                var want = __test_map_bridge_height(px, py)
                if (ticks != BRIDGE_CLIMB_TICKS - 1 || __test_figure_target_height(puller) != want) {
                    return t428_fail('entering bridge tile ' + tile_key + ': ticks=' + ticks + ' target='
                        + __test_figure_target_height(puller) + ' want ' + want)
                }
                bridge_steps++
            } else if (prev_ticks > 0) {
                if (ticks != prev_ticks - 1) {
                    return t428_fail('bridge climb counter must run down on ' + tile_key + ': ' + prev_ticks + ' -> ' + ticks)
                }
                countdown_ok++
            }
        }
        prev_tile = tile_key
        prev_ticks = ticks
    }
    for (var w = 0; w < 60; w++) {
        for (var k = 0; k < members.length; k++) {
            __test_figure_action_perform(members[k])
        }
    }
    if (bridge_steps < 2 || countdown_ok < 10) {
        return t428_fail('puller crossed too few bridge tiles: entered=' + bridge_steps + ' countdown=' + countdown_ok)
    }
    if (__test_figure_current_height(puller) != 0) {
        return t428_fail('puller must be back on the ground after the bridge, height=' + __test_figure_current_height(puller))
    }
    __log_marker('t428_bridge_height_ok:' + bridge_steps + ':' + countdown_ok)

    t428_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t428_ok && __test_find_inlog('[test-marker] t428_bridge_height_ok')
}
