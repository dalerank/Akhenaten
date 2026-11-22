// House expansion and the 2x2 split, as the original does them (house_evolve.c evolve_expand, house_size.c expand_to
// and split_into_huts): a house that expands takes the houses in the new area with their people and goods and moves
// to the area; a 2x2 residence that decays splits into four spacious apartments, the main one keeping the remainder.
// The houses then live the same days whether or not the game was saved and loaded in between.

var __test583_ok = false

function t583_fail(msg) {
    __log_info_native('[test:583] FAIL: ' + msg)
    __test_signal_ready()
}

function t583_house(type, x, y, pop, food, good) {
    var bid = __test_building_create(type, x, y)
    if (bid) {
        __test_house_set_population(bid, pop)
        __test_house_set_goods(bid, food, good)
    }
    return bid
}

function t583_expand_case(name, main_type, x, y, size, around, expect_type) {
    var main = t583_house(main_type, x, y, 30, 10, 5)
    if (!main) {
        return name + ': main not created'
    }
    var pop = 30
    var food = 10
    var good = 5
    for (var i = 0; i < around.length; i++) {
        if (!t583_house(BUILDING_HOUSE_SPACIOUS_APARTMENT, x + around[i][0], y + around[i][1], 7, 3, 1)) {
            return name + ': neighbour ' + i + ' not created'
        }
        pop += 7
        food += 3
        good += 1
    }
    var got = __test_house_expand(main)
    var area = __test_houses_in_area(x - 1, y - 1, x + size, y + size)
    var want = x + ',' + y + ':' + expect_type + ':' + size + ':' + pop + ':' + food + ':' + good + ';'
    if (got != expect_type || area != want) {
        return name + ': expand gave type ' + got + ', area ' + area + ', want ' + want
    }
    return ''
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = ((__scenario_map.width / 2) | 0) - 12
    var cy = ((__scenario_map.height / 2) | 0) - 12

    var err = t583_expand_case('2x2', BUILDING_HOUSE_SPACIOUS_APARTMENT, cx, cy, 2,
        [[1, 0], [0, 1], [1, 1]], BUILDING_HOUSE_COMMON_RESIDENCE)
    if (!err) {
        err = t583_expand_case('3x3', BUILDING_HOUSE_FANCY_RESIDENCE, cx + 8, cy, 3,
            [[2, 0], [2, 1], [0, 2], [1, 2], [2, 2]], BUILDING_HOUSE_COMMON_MANOR)
    }
    if (!err) {
        err = t583_expand_case('4x4', BUILDING_HOUSE_STATELY_MANOR, cx + 16, cy, 4,
            [[3, 0], [3, 1], [3, 2], [0, 3], [1, 3], [2, 3], [3, 3]], BUILDING_HOUSE_MODEST_ESTATE)
    }
    if (err) {
        return t583_fail(err)
    }

    var sx = cx
    var sy = cy + 8
    var residence = t583_house(BUILDING_HOUSE_COMMON_RESIDENCE, sx, sy, 43, 9, 6)
    if (!residence) {
        return t583_fail('residence not created')
    }
    var split_type = __test_house_devolve(residence)
    var split_area = __test_houses_in_area(sx - 1, sy - 1, sx + 2, sy + 2)
    var t = BUILDING_HOUSE_SPACIOUS_APARTMENT
    var split_want = sx + ',' + sy + ':' + t + ':1:13:3:3;' + (sx + 1) + ',' + sy + ':' + t + ':1:10:2:1;'
        + sx + ',' + (sy + 1) + ':' + t + ':1:10:2:1;' + (sx + 1) + ',' + (sy + 1) + ':' + t + ':1:10:2:1;'
    if (split_type != t || split_area != split_want) {
        return t583_fail('2x2 split gave type ' + split_type + ', area ' + split_area + ', want ' + split_want)
    }

    var whole = [cx - 2, cy - 2, cx + 22, cy + 12]
    var before = __test_houses_in_area(whole[0], whole[1], whole[2], whole[3])
    __test_save_memory('t583')
    for (var d = 1; d <= 3; d++) {
        __test_city_house_process_evolve_on_day(d)
    }
    var lived = __test_houses_in_area(whole[0], whole[1], whole[2], whole[3])
    __test_load_memory('t583')
    var loaded = __test_houses_in_area(whole[0], whole[1], whole[2], whole[3])
    if (loaded != before) {
        return t583_fail('houses differ after load: ' + before + ' -> ' + loaded)
    }
    for (var d2 = 1; d2 <= 3; d2++) {
        __test_city_house_process_evolve_on_day(d2)
    }
    var relived = __test_houses_in_area(whole[0], whole[1], whole[2], whole[3])
    if (relived != lived) {
        return t583_fail('days after a load differ: ' + lived + ' vs ' + relived)
    }

    __log_info_native('[test:583] after 3 days: ' + lived)
    __log_marker('house_expand_split_ok')
    __test583_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test583_ok && __test_find_inlog('[test-marker] house_expand_split_ok')
}
