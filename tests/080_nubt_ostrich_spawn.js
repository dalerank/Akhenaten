// Regression #616/#621: Nubt mission0 herd_points_prey must place ostriches on load.
// Markers:
//   [test-marker] nubt_ostriches_ok

var __test080_ok = false

function test080_fail(msg) {
    __log_info_native('[test:080] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:080] Nubt ostrich spawn via herd_points_prey')
    __game_load_mission(0, 1)

    var ostriches = __test_count_figures(FIGURE_OSTRICH)
    if (ostriches < 1) {
        test080_fail('expected ostriches after mission0 load, got ' + ostriches)
        return
    }

    __log_marker('nubt_ostriches_ok')
    __test080_ok = true
    __log_info_native('[test:080] PASS ostriches=' + ostriches)
    __test_signal_ready()
}

function check_valid() {
    if (!__test080_ok) {
        return false
    }
    return true
}
