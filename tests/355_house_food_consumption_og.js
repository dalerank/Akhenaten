// OG city/resources.c city_resource_consume_food: once a month a house eats 25% of its people (20% with a Bast
// complex or an Osiris complex with its altar), split over the food kinds its level needs, taken from the first
// city foods it has in stock; a kind with less than the share is emptied and still counts as eaten.
// The remake model (house.js, twice a month) runs only with gameplay_change_food_consumption_remake.
//   [test-marker] house_food_consumption_og_ok

var __test355_ok = false
var __test355_feat_prev = false

function test355_fail(msg) {
    __log_info_native('[test:355] FAIL: ' + msg)
}

function test355_house(x, y, type, pop, food0, food1) {
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, x, y)
    if (!bid || !__test_house_change_to(bid, type)) {
        return null
    }
    __test_house_set_population(bid, pop)
    var house = city.get_house(bid)
    house.set_food(0, food0)
    house.set_food(1, food1)
    house.set_food(2, 0)
    house.set_food(3, 0)
    return house
}

function test355_foods(house, want0, want1, what) {
    var got0 = house.get_food(0)
    var got1 = house.get_food(1)
    if (got0 != want0 || got1 != want1) {
        test355_fail(what + ': foods=[' + got0 + ', ' + got1 + '] want [' + want0 + ', ' + want1 + ']')
        return false
    }
    return true
}

function test355_check(cx, cy) {
    __test_set_allowed_food(0, RESOURCE_GRAIN)
    __test_set_allowed_food(1, RESOURCE_FIGS)
    __test_set_allowed_food(2, RESOURCE_NONE)
    __test_set_allowed_food(3, RESOURCE_NONE)

    game_features.gameplay_change_food_consumption_remake = false
    var pct = __test_city_food_consumption_percentage()
    if (pct != 25) {
        test355_fail('food consumption percentage=' + pct + ' want 25')
        return false
    }

    var one_kind = test355_house(cx, cy - 14, BUILDING_HOUSE_COMMON_SHANTY, 40, 100, 100)
    var two_kinds = test355_house(cx + 3, cy - 14, BUILDING_HOUSE_SPACIOUS_RESIDENCE, 40, 100, 3)
    var first_empty = test355_house(cx + 6, cy - 14, BUILDING_HOUSE_COMMON_SHANTY, 40, 0, 100)
    if (!one_kind || !two_kinds || !first_empty) {
        test355_fail('house create/change failed')
        return false
    }

    __test_city_consume_food_weekly()
    if (!test355_foods(one_kind, 100, 100, 'weekly with the flag off')) {
        return false
    }

    __test_city_consume_food_monthly()
    if (!test355_foods(one_kind, 90, 100, 'one kind, 40 people')
        || !test355_foods(two_kinds, 95, 0, 'two kinds, 40 people')
        || !test355_foods(first_empty, 0, 90, 'first kind out of stock')) {
        return false
    }
    if (two_kinds.num_foods != 2 || one_kind.num_foods != 1) {
        test355_fail('num_foods one_kind=' + one_kind.num_foods + ' two_kinds=' + two_kinds.num_foods)
        return false
    }

    game_features.gameplay_change_food_consumption_remake = true
    __test_city_consume_food_monthly()
    if (!test355_foods(one_kind, 90, 100, 'monthly with the flag on')) {
        return false
    }
    __test_city_consume_food_weekly()
    if (one_kind.get_food(0) >= 90) {
        test355_fail('remake weekly consumption did not eat, food0=' + one_kind.get_food(0))
        return false
    }
    return true
}

function run_test() {
    __test355_ok = false
    __test355_feat_prev = !!game_features.gameplay_change_food_consumption_remake
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test355_check(cx, cy)) {
            __test355_ok = true
            __log_info_native('[test-marker] house_food_consumption_og_ok')
        }
    } else {
        test355_fail('session reload failed')
    }
    game_features.gameplay_change_food_consumption_remake = __test355_feat_prev
    __test_signal_ready()
}

function check_valid() {
    return __test355_ok && __test_find_inlog('[test-marker] house_food_consumption_og_ok')
}
