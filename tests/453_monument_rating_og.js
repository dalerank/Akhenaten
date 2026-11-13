// OG monument rating (city/monument_rating.c): trunc(6.32 * sqrt(points) + 0.5), one less while a monument is
// unfinished, with OG monument_defs weights and a burial goods share (32 loads of a material or 16 of goods per
// point). Checks the curve against original goals: small obelisk 6, small mastaba 9, three small mastabas plus
// On's burial goods 18, Meidum small stepped + complex 39. Only the monuments that took a scenario slot count
// (OG monument_register): a carried-over or extra monument adds nothing and, unfinished, costs no point.
// Markers:
//   [test-marker] monument_og_curve_ok
//   [test-marker] monument_og_weights_ok
//   [test-marker] monument_og_slots_ok

function run_test() {
    __log_info_native('[test:453] OG monument rating curve')
    test_ensure_city_session('data/default.map')

    // [points, unfinished, rating]
    var curve = [
        [0, false, 0],
        [1, false, 6],
        [2, false, 9],
        [2, true, 8],
        [3, false, 11],
        [4, false, 13],
        [8, false, 18],
        [39, false, 39],
        [250, false, 100],
        [0, true, 0],
    ]
    for (var i = 0; i < curve.length; i++) {
        var got = monument_rating_from_points(curve[i][0], curve[i][1])
        if (got !== curve[i][2]) {
            __log_info_native('[test:453] points=' + curve[i][0] + ' unfinished=' + curve[i][1]
                + ' want ' + curve[i][2] + ' got ' + got)
            __test_signal_ready()
            return
        }
    }
    __log_marker('monument_og_curve_ok')

    var w = MONUMENT_WEIGHTS
    var on_burial = ((8 / 16) | 0) * 3 + ((32 / 32) | 0) * 2
    var checks = [
        [w[BUILDING_SMALL_OBELISK], 6],
        [w[BUILDING_SMALL_MASTABA], 9],
        [3 * w[BUILDING_SMALL_MASTABA] + on_burial, 18],
        [w[BUILDING_SMALL_STEPPED_PYRAMID] + w[BUILDING_STEPPED_PYRAMID_COMPLEX], 39],
        [w[BUILDING_SUN_TEMPLE], 13],
        [w[BUILDING_SMALL_ROYAL_TOMB], 13],
        [w[BUILDING_MEDIUM_ROYAL_TOMB], 22],
    ]
    for (var c = 0; c < checks.length; c++) {
        var r = monument_rating_from_points(checks[c][0], false)
        if (r !== checks[c][1]) {
            __log_info_native('[test:453] weights case ' + c + ' points=' + checks[c][0] + ' want ' + checks[c][1] + ' got ' + r)
            __test_signal_ready()
            return
        }
    }
    __log_marker('monument_og_weights_ok')

    var slots0 = [__scenario_monuments.first, __scenario_monuments.second, __scenario_monuments.third]
    function finish() {
        __scenario_monuments.first = slots0[0]
        __scenario_monuments.second = slots0[1]
        __scenario_monuments.third = slots0[2]
        __test_signal_ready()
    }
    test_monument_slots([BUILDING_SMALL_OBELISK])
    var carried = __test_building_create(BUILDING_SMALL_OBELISK, 20, 20)
    var built = __test_building_create(BUILDING_SMALL_OBELISK, 40, 40)
    var extra = __test_building_create(BUILDING_SUN_TEMPLE, 60, 60)
    if (!carried || !built || !extra || carried >= built) {
        __log_info_native('[test:453] monuments create failed ' + carried + '/' + built + '/' + extra)
        finish()
        return
    }
    __test_monument_set_preexisting(carried, 1)
    __test_monument_set_phase(carried, 1)
    __test_monument_set_phase(built, -1)
    __test_monument_set_phase(extra, 1)
    var rating = city_monument_rating()
    var slot_bid = city_monument_slot_buildings()[0]
    if (rating !== 6 || slot_bid !== built) {
        __log_info_native('[test:453] slots want rating 6 from ' + built + ' got ' + rating + ' from ' + slot_bid)
        finish()
        return
    }
    __log_marker('monument_og_slots_ok')
    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] monument_og_curve_ok')
        && __test_find_inlog('[test-marker] monument_og_weights_ok')
        && __test_find_inlog('[test-marker] monument_og_slots_ok')
}
