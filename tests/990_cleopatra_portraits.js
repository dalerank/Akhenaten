// Regression: the Cleopatra special figures (types 102-109) must resolve their
// big-image portrait from the Expansion pack group 1 ("big people 2") rather
// than the numbered placeholder slots in the base pack group 25.
//
// Requires the original game data; when it is absent (CI with --no-resource)
// the test skips cleanly instead of failing.
function run_test() {
    __log_info_native('[test:990cleo] start')
    __test_pump_frames(10)

    // Force the delayed Expansion pack to resolve through the pak queue.
    var probe = get_image({ pack: PACK_EXPANSION, id: 1, offset: 0 })
    __test_pump_frames(30)
    probe = get_image({ pack: PACK_EXPANSION, id: 1, offset: 0 })
    if (!probe) {
        __log_info_native('[test:990cleo] no game data (Expansion pack unavailable) - skipped')
        __test_signal_ready()
        return
    }
    __log_info_native('[test:990cleo] expansion g1 probe=' + probe.tid + ' ' + probe.width + 'x' + probe.height)

    // Expansion group 1 offset per figure type (verified against the art).
    var EXPECTED = {
        102: 4, // FIGURE_ASP
        103: 5, // FIGURE_LION
        104: 2, // FIGURE_SCORPION
        105: 0, // FIGURE_ZOOKEEPER
        106: 6, // FIGURE_FROG
        107: 7, // FIGURE_LOCUST
        108: 3, // FIGURE_TOMB_ARTISAN
        109: 8  // FIGURE_MUMMY
    }
    var ok = true
    for (var type in EXPECTED) {
        var tid = FigureParams.for_type(parseInt(type)).first_img("big_image")
        var want = probe.tid + EXPECTED[type]
        var match = (tid == want)
        __log_info_native('[test:990cleo] type=' + type + ' offset=' + EXPECTED[type] + ' tid=' + tid
            + ' want=' + want + ' -> ' + (match ? 'OK' : 'MISMATCH'))
        if (!match) { ok = false }
    }
    __log_info_native('[test:990cleo] all_match=' + ok)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test:990cleo] all_match=true')
        || __test_find_inlog('[test:990cleo] no game data (Expansion pack unavailable) - skipped')
}
