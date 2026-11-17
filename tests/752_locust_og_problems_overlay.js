// Problems overlay vs OG widget/city_overlay_show.c problems_show_figure: the frog, mummy and locust plague figures
// are drawn on the problems overlay; an ordinary walker is not.
// Markers:
//   [test-marker] locust_og_problems_overlay_ok

function test752_fail(msg) {
    __log_info_native('[test:752] FAIL: ' + msg)
}

function test752_run() {
    test_reload_city_session('data/default.map')
    var types = [FIGURE_LOCUST, FIGURE_FROG, FIGURE_MUMMY]
    for (var i = 0; i < types.length; i++) {
        var fid = test_figure_create(types[i], -1, -1)
        if (!fid) {
            test752_fail('create type ' + types[i])
            return
        }
        if (__test_overlay_show_figure(OVERLAY_PROBLEMS, fid) != 1) {
            test752_fail('type ' + types[i] + ' not shown on the problems overlay')
            return
        }
    }
    var other = test_figure_create(FIGURE_FIREMAN, -1, -1)
    if (!other || __test_overlay_show_figure(OVERLAY_PROBLEMS, other) != 0) {
        test752_fail('fireman shown on the problems overlay')
        return
    }
    __log_marker('locust_og_problems_overlay_ok')
}

function run_test() {
    __log_info_native('[test:752] OG problems overlay plague figures')
    try {
        test752_run()
    } catch (e) {
        test752_fail('exception: ' + e)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] locust_og_problems_overlay_ok')
}

function done() {
    city.figures.remove_figures(FIGURE_LOCUST)
    city.figures.remove_figures(FIGURE_FROG)
    city.figures.remove_figures(FIGURE_MUMMY)
    city.figures.remove_figures(FIGURE_FIREMAN)
}
