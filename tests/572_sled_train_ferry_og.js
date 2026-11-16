// OG sled train at a ferry (laborer.c laborer_pulls_train / train_follow, boats.c follower_leader):
// the train keeps pulling while its laborer waits for or rides the ferry, hides while aboard,
// and is put on the landing with the laborer when the boat unloads.

var ACTION_17_LABORER_TO_PYRAMID = 17
var ACTION_4_FERRY_BOAT_WAITING_T572 = 4

var t572_ok = false

function t572_fail(msg) {
    __log_info_native('[test:572] FAIL: ' + msg)
    __test_signal_ready()
}

function t572_perform_train(lab) {
    var members = []
    for (var p = 1; p <= 6; p++) {
        var m = __pyramid_train_member(lab, p)
        if (m) {
            members.push(m)
        }
    }
    for (var i = 0; i < members.length; i++) {
        __test_figure_action_perform(members[i])
    }
    return members
}

function t572_all(members, pred) {
    for (var i = 0; i < members.length; i++) {
        if (!pred(members[i])) {
            return false
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:572] sled train ferry OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __scenario_building_allow(BUILDING_FERRY, true)
    __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)

    var landing = test_shoreline_building_place(BUILDING_FERRY, 2)
    if (!landing) {
        return t572_fail('place ferry')
    }
    __test_building_set_workers(landing, 8)
    var tile = __building_tile(landing)
    var boat = test_figure_create(FIGURE_FERRY_BOAT, tile.x, tile.y)
    test_figure_set_home(boat, landing)
    __test_building_set_figure_slot(landing, BUILDING_SLOT_BOAT, boat)
    __test_figure_set_action(boat, ACTION_4_FERRY_BOAT_WAITING_T572)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var pyramid = test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, 30, 30) || test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, 40, 40)
    if (!pyramid) {
        return t572_fail('place pyramid')
    }

    var lab = test_figure_create(FIGURE_LABORER, cx + 8, cy + 8)
    if (!lab) {
        return t572_fail('create laborer')
    }
    __test_figure_set_collecting_item(lab, RESOURCE_BRICKS)
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)
    __pyramid_spawn_sled_train(lab, pyramid)
    if (__pyramid_count_sled_train_followers(lab) != 6) {
        return t572_fail('train size ' + __pyramid_count_sled_train_followers(lab))
    }

    if (!__test_ferry_landing_enqueue(landing, lab)) {
        return t572_fail('enqueue laborer')
    }
    var members = t572_perform_train(lab)
    if (members.length != 6 || !t572_all(members, __test_figure_is_alive)) {
        return t572_fail('train must keep pulling while its laborer waits for the ferry')
    }
    __log_marker('t572_wait_keeps_train_ok')

    if (__test_ferry_boat_load(boat, landing) != 1) {
        return t572_fail('boat did not load the laborer')
    }
    if (__test_figure_get_action(lab) != __test_figure_ferry_action(lab, 1)) {
        return t572_fail('laborer not on ferry: ' + __test_figure_get_action(lab))
    }
    members = t572_perform_train(lab)
    if (members.length != 6 || !t572_all(members, __test_figure_is_alive)) {
        return t572_fail('train must ride the ferry with its laborer, members=' + members.length)
    }
    if (!t572_all(members, function (m) { return __test_figure_is_visible(m) == 0 })) {
        return t572_fail('train must hide while its laborer is aboard')
    }
    __log_marker('t572_ride_hidden_ok')

    __test_ferry_boat_unload(boat, landing)
    if (__test_figure_get_action(lab) != ACTION_17_LABORER_TO_PYRAMID) {
        return t572_fail('laborer did not resume after unload: ' + __test_figure_get_action(lab))
    }
    var ltile = __figure_get_tile(lab)
    members = t572_perform_train(lab)
    if (members.length != 6 || !t572_all(members, __test_figure_is_alive)) {
        return t572_fail('train lost at unload, members=' + members.length)
    }
    var placed = t572_all(members, function (m) {
        var mt = __figure_get_tile(m)
        return mt.x == ltile.x && mt.y == ltile.y
    })
    if (!placed) {
        return t572_fail('train not placed on the landing with its laborer')
    }
    __log_marker('t572_unload_with_laborer_ok')

    t572_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t572_ok
        && __test_find_inlog('[test-marker] t572_wait_keeps_train_ok')
        && __test_find_inlog('[test-marker] t572_ride_hidden_ok')
        && __test_find_inlog('[test-marker] t572_unload_with_laborer_ok')
}
