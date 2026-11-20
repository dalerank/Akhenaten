// LW1 / LW2 / LW4: enhanced walker spawn + move boost.
// Markers:
//   [test-marker] walker_spawn_boost_table_ok
//   [test-marker] walker_move_speed_ok
//   [test-marker] walker_cart_wait_ok
//   [test-marker] walker_flags_default_off_ok

function run_test() {
    __log_info_native('[test:079] lazy walkers spawn/move boost')
    test_ensure_city_session('data/default.map')

    var prev_spawn = game_features.get('gameplay_enhanced_walker_spawn_boost')
    var prev_move = game_features.get('gameplay_enhanced_walker_move_boost')
    function finish() {
        game_features.set('gameplay_enhanced_walker_spawn_boost', prev_spawn)
        game_features.set('gameplay_enhanced_walker_move_boost', prev_move)
        __test_signal_ready()
    }

    if (game_features.default('gameplay_enhanced_walker_spawn_boost')
        || game_features.default('gameplay_enhanced_walker_move_boost')) {
        __log_info_native('[test:079] flags default should be OFF')
        finish()
        return
    }
    __log_marker('walker_flags_default_off_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = __test_building_create(BUILDING_FIREHOUSE, cx, cy)
    if (!bid) {
        __log_info_native('[test:079] firehouse create failed')
        finish()
        return
    }
    var b = city.get_building(bid)
    if (b.max_workers <= 0) {
        b.max_workers = 6
    }
    var maxw = b.max_workers

    function expect_timer(workers, off_want, on_want, label) {
        __test_building_set_workers(bid, workers)
        game_features.set('gameplay_enhanced_walker_spawn_boost', false)
        var off = __test_building_figure_spawn_timer(bid)
        game_features.set('gameplay_enhanced_walker_spawn_boost', true)
        var on = __test_building_figure_spawn_timer(bid)
        if (off !== off_want || on !== on_want) {
            __log_info_native('[test:079] spawn table ' + label
                + ' workers=' + workers + ' off=' + off + ' want ' + off_want
                + ' on=' + on + ' want ' + on_want)
            return false
        }
        return true
    }

    // Explicit headcount so pct lands in the intended band (maxw=6 → 5=83%, 3=50%, 2=33%).
    var w75 = Math.ceil(maxw * 0.75)
    var w50 = Math.ceil(maxw * 0.50)
    var w25 = Math.ceil(maxw * 0.25)
    if (w75 < maxw && ((w75 * 100 / maxw) | 0) < 75) {
        w75 = w75 + 1
    }
    if (!expect_timer(maxw, 0, 0, '100pct')
        || !expect_timer(w75, 1, 0, '75pct')
        || !expect_timer(w50, 3, 1, '50pct')
        || !expect_timer(w25, 7, 3, '25pct')
        || !expect_timer(1, 15, 7, '1pct')
        || !expect_timer(0, -1, -1, '0pct')) {
        finish()
        return
    }
    game_features.set('gameplay_enhanced_walker_spawn_boost', false)
    __log_marker('walker_spawn_boost_table_ok')

    var citizen_fid = test_figure_create(FIGURE_LABOR_SEEKER, cx + 2, cy)
    var animal_fid = test_figure_create(FIGURE_HYENA, cx + 3, cy)
    if (!citizen_fid || !animal_fid) {
        __log_info_native('[test:079] figure create failed citizen=' + citizen_fid + ' hyena=' + animal_fid)
        finish()
        return
    }

    game_features.set('gameplay_enhanced_walker_move_boost', false)
    var citizen_off = __test_figure_apply_params_speed(citizen_fid)
    var animal_off = __test_figure_apply_params_speed(animal_fid)

    game_features.set('gameplay_enhanced_walker_move_boost', true)
    var citizen_on = __test_figure_apply_params_speed(citizen_fid)
    var animal_on = __test_figure_apply_params_speed(animal_fid)

    if (citizen_off < 1 || citizen_on !== citizen_off + 1) {
        __log_info_native('[test:079] citizen speed off=' + citizen_off + ' on=' + citizen_on + ' want on=off+1')
        finish()
        return
    }
    if (animal_on !== animal_off) {
        __log_info_native('[test:079] hyena speed changed off=' + animal_off + ' on=' + animal_on)
        finish()
        return
    }
    __log_marker('walker_move_speed_ok')

    game_features.set('gameplay_enhanced_walker_move_boost', false)
    var th_off = __test_cartpusher_destination_wait_threshold()
    var wait_off = __test_building_create_cartpusher_wait_ticks(bid)
    var slot_fig = b.get_figure(BUILDING_SLOT_CARTPUSHER)
    if (slot_fig && slot_fig.id) {
        __test_figure_kill(slot_fig.id)
    }
    game_features.set('gameplay_enhanced_walker_move_boost', true)
    var th_on = __test_cartpusher_destination_wait_threshold()
    var wait_on = __test_building_create_cartpusher_wait_ticks(bid)

    if (th_off !== 30 || th_on !== 10) {
        __log_info_native('[test:079] cart threshold off=' + th_off + ' on=' + th_on)
        finish()
        return
    }
    if (wait_off !== 30 || wait_on !== 10) {
        __log_info_native('[test:079] cart create wait off=' + wait_off + ' on=' + wait_on)
        finish()
        return
    }
    __log_marker('walker_cart_wait_ok')

    finish()
}

function check_valid() {
    var markers = [
        'walker_flags_default_off_ok',
        'walker_spawn_boost_table_ok',
        'walker_move_speed_ok',
        'walker_cart_wait_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:079] missing marker: ' + marker)
            return false
        }
    }
    return true
}
