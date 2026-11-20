// FM1/FM2: Food Mill storage + variety (0..4).
// Markers:
//   [test-marker] food_mill_create_ok
//   [test-marker] food_mill_empty_variety_ok
//   [test-marker] food_mill_one_type_ok
//   [test-marker] food_mill_two_types_ok
//   [test-marker] food_mill_max_per_type_ok
//   [test-marker] food_mill_four_types_cap_ok

var __test069_ok = {
    create: false,
    empty: false,
    one: false,
    two: false,
    max_type: false,
    four: false
}

function run_test() {
    __log_info_native('[test:069] food mill storage + variety')
    test_ensure_city_session('data/default.map')

    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    game_features.set('gameplay_enhanced_food_mill', true)

    function finish() {
        game_features.set('gameplay_enhanced_food_mill', mill_prev)
        __test_signal_ready()
    }

    var bid = __test_building_create(BUILDING_FOOD_MILL, -1, -1)
    if (!bid) {
        __log_info_native('[test:069] create mill failed')
        finish()
        return
    }
    __log_marker('food_mill_create_ok')
    __test069_ok.create = true

    if (__test_food_mill_variety(bid) != 0) {
        __log_info_native('[test:069] empty variety want 0 got ' + __test_food_mill_variety(bid))
        finish()
        return
    }
    if (__test_food_mill_total_stored(bid) != 0) {
        __log_info_native('[test:069] empty total want 0 got ' + __test_food_mill_total_stored(bid))
        finish()
        return
    }
    var free0 = __test_food_mill_freespace(bid)
    if (free0 <= 0) {
        __log_info_native('[test:069] empty freespace want >0 got ' + free0)
        finish()
        return
    }
    __log_marker('food_mill_empty_variety_ok')
    __test069_ok.empty = true

    if (!__test_food_mill_add_resource(bid, RESOURCE_GRAIN, 100)) {
        __log_info_native('[test:069] add grain failed')
        finish()
        return
    }
    if (__test_food_mill_amount(bid, RESOURCE_GRAIN) != 100) {
        __log_info_native('[test:069] grain amount want 100 got '
            + __test_food_mill_amount(bid, RESOURCE_GRAIN))
        finish()
        return
    }
    if (__test_food_mill_variety(bid) != 1) {
        __log_info_native('[test:069] one type want 1 got ' + __test_food_mill_variety(bid))
        finish()
        return
    }
    __log_marker('food_mill_one_type_ok')
    __test069_ok.one = true

    if (!__test_food_mill_add_resource(bid, RESOURCE_FIGS, 100)) {
        __log_info_native('[test:069] add figs failed')
        finish()
        return
    }
    if (__test_food_mill_variety(bid) != 2) {
        __log_info_native('[test:069] two types want 2 got ' + __test_food_mill_variety(bid))
        finish()
        return
    }
    if (__test_food_mill_total_stored(bid) != 200) {
        __log_info_native('[test:069] total want 200 got ' + __test_food_mill_total_stored(bid))
        finish()
        return
    }
    __log_marker('food_mill_two_types_ok')
    __test069_ok.two = true

    // max_per_type default 800 — fill grain to cap, leftover rejected
    if (!__test_food_mill_add_resource(bid, RESOURCE_GRAIN, 700)) {
        __log_info_native('[test:069] top up grain to 800 failed')
        finish()
        return
    }
    if (__test_food_mill_amount(bid, RESOURCE_GRAIN) != 800) {
        __log_info_native('[test:069] grain cap want 800 got '
            + __test_food_mill_amount(bid, RESOURCE_GRAIN))
        finish()
        return
    }
    if (__test_food_mill_add_resource(bid, RESOURCE_GRAIN, 100)) {
        __log_info_native('[test:069] grain over max_per_type should fail')
        finish()
        return
    }
    __log_marker('food_mill_max_per_type_ok')
    __test069_ok.max_type = true

    if (!__test_food_mill_add_resource(bid, RESOURCE_MEAT, 50)) {
        __log_info_native('[test:069] add meat failed')
        finish()
        return
    }
    if (!__test_food_mill_add_resource(bid, RESOURCE_FISH, 50)) {
        __log_info_native('[test:069] add fish failed')
        finish()
        return
    }
    if (__test_food_mill_variety(bid) != 4) {
        __log_info_native('[test:069] four types want 4 got ' + __test_food_mill_variety(bid))
        finish()
        return
    }
    // fifth type should not raise variety above 4
    if (!__test_food_mill_add_resource(bid, RESOURCE_LETTUCE, 50)) {
        __log_info_native('[test:069] add lettuce failed')
        finish()
        return
    }
    if (__test_food_mill_variety(bid) != 4) {
        __log_info_native('[test:069] variety cap want 4 got ' + __test_food_mill_variety(bid))
        finish()
        return
    }
    __log_marker('food_mill_four_types_cap_ok')
    __test069_ok.four = true

    finish()
}

function check_valid() {
    return check_test()
}

function check_test() {
    if (!__test069_ok.create || !__test069_ok.empty || !__test069_ok.one
        || !__test069_ok.two || !__test069_ok.max_type || !__test069_ok.four) {
        __log_info_native('[test:069] one or more phases failed')
        return false
    }
    var markers = [
        'food_mill_create_ok',
        'food_mill_empty_variety_ok',
        'food_mill_one_type_ok',
        'food_mill_two_types_ok',
        'food_mill_max_per_type_ok',
        'food_mill_four_types_cap_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:069] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
