// Regression: JS must be able to WRITE building.play_animation through the generic
// property binding (empty `{ }` descriptor). The write has to reach the real C++
// base.play_animation field, not a throwaway own-property on the JS wrapper -- verify
// by reading back through a FRESH city.get_building() handle.
//
// This guards the brewery animation bug: the es(update_animation) handler sets
// b.play_animation = false when out of resources; if the setter is missing, the
// animation keeps playing regardless of barley/water.

var __test25_ok = false

function run_test() {
    __log_info_native('[test:25] checking play_animation write-through path')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_BREWERY_WORKSHOP, -1, -1)

    city.get_building(bid).play_animation = true
    var after_true = city.get_building(bid).play_animation
    city.get_building(bid).play_animation = false
    var after_false = city.get_building(bid).play_animation

    __log_info_native('[test:25] after_true=' + after_true + ' after_false=' + after_false)
    if (after_true === true && after_false === false) {
        __log_marker('test25_play_animation_write_ok')
        __test25_ok = true
    } else {
        __log_info_native('[test:25] play_animation write-through FAILED')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test25_ok && __test_find_inlog('[test-marker] test25_play_animation_write_ok')
}
