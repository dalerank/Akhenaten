// Chariots workshop (OG chariot maker): 4x4, military labor, timber is the only input.
// gameplay_chariots_workshop_needs_weapons adds weapons as a second input.
// Building JS wrappers can cache property values — re-fetch via city.get_building(bid).

var __test30_ok = false
var __test30_feat_prev = false

function test30_fail(msg) {
    __log_info_native('[test:30] FAIL: ' + msg)
    game_features.set('gameplay_chariots_workshop_needs_weapons', __test30_feat_prev)
    __test_signal_ready()
}

function test30_place() {
    var bid = test_building_place(BUILDING_CHARIOTS_WORKSHOP, -1, -1)
    if (!bid) {
        test30_fail('place failed')
    }
    return bid
}

function test30_animates(bid) {
    var b = city.get_building(bid)
    b.play_animation = true
    building_chariots_workshop_on_update_animation({ bid: bid })
    return city.get_building(bid).play_animation
}

function test30_empty(bid) {
    var b = city.get_building(bid)
    b.consume_resource(RESOURCE_TIMBER, b.stored_resource(RESOURCE_TIMBER))
    b.consume_resource(RESOURCE_WEAPONS, b.stored_resource(RESOURCE_WEAPONS))
}

function run_test() {
    __log_info_native('[test:30] chariots workshop OG rules')
    __test30_feat_prev = !!game_features.gameplay_chariots_workshop_needs_weapons
    game_features.set('gameplay_chariots_workshop_needs_weapons', false)
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test30_place()
    if (!bid) {
        return
    }
    var b = city.get_building(bid)
    if (b.size != 4) {
        return test30_fail('size=' + b.size + ' expected 4')
    }
    if (b.second_material != 'none') {
        return test30_fail('OG second input=' + b.second_material + ' expected none')
    }
    if (__building_static_labor_category(BUILDING_CHARIOTS_WORKSHOP) != LABOR_CATEGORY_MILITARY) {
        return test30_fail('labor category=' + __building_static_labor_category(BUILDING_CHARIOTS_WORKSHOP))
    }
    __log_marker('test30_og_footprint_and_inputs')

    var views_before = __test_sound_city_channel_views(SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP)
    var channel = __test_sound_city_mark_building(bid, 4)
    if (channel != SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP) {
        return test30_fail('sound channel=' + channel)
    }
    var views_marked = __test_sound_city_channel_views(SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP)
    if (views_marked != views_before + 4) {
        return test30_fail('city sound views ' + views_before + ' -> ' + views_marked)
    }
    __test_sound_city_decay_views()
    var views_decayed = __test_sound_city_channel_views(SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP)
    if (views_decayed != ((views_marked / 2) | 0)) {
        return test30_fail('city sound decay skipped the channel: ' + views_marked + ' -> ' + views_decayed)
    }
    __log_marker('test30_city_sound_channel')

    if (test30_animates(bid)) {
        return test30_fail('animates without timber')
    }
    city.get_building(bid).consume_resource(RESOURCE_TIMBER, -100)
    if (!test30_animates(bid)) {
        return test30_fail('stopped with timber only (OG needs no weapons)')
    }
    __log_marker('test30_og_timber_only_animates')

    test30_empty(bid)
    for (var i = 0; i < 8; i++) {
        b = city.get_building(bid)
        b.num_workers = b.max_workers
        b.play_animation = true
        __test_pump_frames(120)
        if (!city.get_building(bid).play_animation) {
            break
        }
    }
    if (city.get_building(bid).play_animation) {
        return test30_fail('day tick left play_animation=true without timber')
    }
    __log_marker('test30_day_tick_stops_without_materials')

    game_features.set('gameplay_chariots_workshop_needs_weapons', true)
    var bid2 = test30_place()
    if (!bid2) {
        return
    }
    if (city.get_building(bid2).second_material != 'weapons') {
        return test30_fail('feature on: second input=' + city.get_building(bid2).second_material)
    }
    test30_animates(bid)
    if (city.get_building(bid).second_material != 'weapons') {
        return test30_fail('feature on: existing workshop second input=' + city.get_building(bid).second_material)
    }
    city.get_building(bid2).consume_resource(RESOURCE_TIMBER, -100)
    if (test30_animates(bid2)) {
        return test30_fail('feature on: animates with timber but no weapons')
    }
    city.get_building(bid2).consume_resource(RESOURCE_WEAPONS, -100)
    if (!test30_animates(bid2)) {
        return test30_fail('feature on: stopped with timber+weapons')
    }
    __log_marker('test30_feature_needs_weapons')

    game_features.set('gameplay_chariots_workshop_needs_weapons', __test30_feat_prev)
    __test30_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test30_ok
        && __test_find_inlog('[test-marker] test30_og_footprint_and_inputs')
        && __test_find_inlog('[test-marker] test30_city_sound_channel')
        && __test_find_inlog('[test-marker] test30_og_timber_only_animates')
        && __test_find_inlog('[test-marker] test30_day_tick_stops_without_materials')
        && __test_find_inlog('[test-marker] test30_feature_needs_weapons')
}
