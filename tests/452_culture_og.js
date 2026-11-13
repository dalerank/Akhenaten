// OG culture rating (city/ratings.c, city_data.c culture_records): the lowest of 11 coverage records
// (jugglers, musicians, dancers, senet, zoo, religion, school, library, dentist, physician, mortuary),
// and the advisor explanation is that record's index.
// Markers:
//   [test-marker] culture_og_full_ok
//   [test-marker] culture_og_lowest_ok

var CULTURE_FIELDS = ['booth', 'bandstand', 'pavilion', 'senet_house', 'zoo', 'school', 'library', 'religion',
    'dentist', 'physician', 'mortuary']

function culture_with(overrides) {
    for (var i = 0; i < CULTURE_FIELDS.length; i++) {
        var f = CULTURE_FIELDS[i]
        __test_coverage_set(f, (f in overrides) ? overrides[f] : 100)
    }
    __test_city_update_culture()
    return { rating: city.rating.culture | 0, explanation: city.rating.culture_explanation | 0 }
}

function run_test() {
    __log_info_native('[test:452] OG culture rating')
    test_ensure_city_session('data/default.map')

    var full = culture_with({})
    if (full.rating !== 100) {
        __log_info_native('[test:452] full coverage want 100 got ' + full.rating)
        __test_signal_ready()
        return
    }
    __log_marker('culture_og_full_ok')

    // [overrides, rating, explanation index]
    var cases = [
        [{ booth: 0 }, 5, 0],
        [{ religion: 30 }, 25, 5],
        [{ school: 50, library: 10 }, 60, 6],
        [{ dentist: 85 }, 65, 8],
        [{ dentist: 90 }, 100, 0],
        [{ mortuary: 99 }, 100, 0],
        [{ mortuary: 79 }, 85, 10],
        [{ zoo: 0, senet_house: 0 }, 50, 3],
    ]
    for (var c = 0; c < cases.length; c++) {
        var got = culture_with(cases[c][0])
        if (got.rating !== cases[c][1] || got.explanation !== cases[c][2]) {
            __log_info_native('[test:452] case ' + c + ' want ' + cases[c][1] + '/' + cases[c][2]
                + ' got ' + got.rating + '/' + got.explanation)
            __test_signal_ready()
            return
        }
    }
    __log_marker('culture_og_lowest_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] culture_og_full_ok')
        && __test_find_inlog('[test-marker] culture_og_lowest_ok')
}
