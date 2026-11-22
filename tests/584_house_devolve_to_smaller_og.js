// OG house_size.c devolve_to_smaller: a common manor (3x3) that decays becomes a fancy residence (2x2), a modest
// estate (4x4) a stately manor (3x3). The house keeps population/divisor + remainder of its people and of each good
// (divisor 6 for the manor, 8 for the estate); the freed strip of tiles becomes garden, no new houses appear.

var __test584_ok = false

function t584_fail(msg) {
    __log_info_native('[test:584] FAIL: ' + msg)
    __test_signal_ready()
}

function t584_case(name, type, x, y, old_size, pop, food, good, want_type, divisor) {
    var bid = __test_building_create(type, x, y)
    if (!bid) {
        return name + ': not created'
    }
    __test_house_set_population(bid, pop)
    __test_house_set_goods(bid, food, good)
    var got = __test_house_devolve(bid)
    var size = old_size - 1
    var share = function (v) { return ((v / divisor) | 0) + (v % divisor) }
    var want = x + ',' + y + ':' + want_type + ':' + size + ':' + share(pop) + ':' + share(food) + ':' + share(good) + ';'
    var area = __test_houses_in_area(x - 1, y - 1, x + old_size, y + old_size)
    if (got != want_type || area != want) {
        return name + ': devolve gave type ' + got + ', area ' + area + ', want ' + want
    }
    for (var i = 0; i <= size; i++) {
        if (!terrain.is({x: x + size, y: y + i}, TERRAIN_GARDEN) || !terrain.is({x: x + i, y: y + size}, TERRAIN_GARDEN)) {
            return name + ': freed strip is not garden at step ' + i
        }
    }
    return ''
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = ((__scenario_map.width / 2) | 0) - 8
    var cy = ((__scenario_map.height / 2) | 0) - 8

    var err = t584_case('manor', BUILDING_HOUSE_COMMON_MANOR, cx, cy, 3, 50, 13, 7, BUILDING_HOUSE_FANCY_RESIDENCE, 6)
    if (!err) {
        err = t584_case('estate', BUILDING_HOUSE_MODEST_ESTATE, cx + 8, cy, 4, 70, 17, 9, BUILDING_HOUSE_STATELY_MANOR, 8)
    }
    if (err) {
        return t584_fail(err)
    }

    __log_marker('house_devolve_to_smaller_ok')
    __test584_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test584_ok && __test_find_inlog('[test-marker] house_devolve_to_smaller_ok')
}
