// Formation layout spots come from formation_layouts in figures.js: 16 layouts in order, 16 spots each,
// OG herd spots 11 (0,3) and 15 (-3,2), chariot double-line spots twice the infantry gaps.

function t476_check() {
    var rows = formation_layouts
    if (!rows || rows.length != 16) {
        return '16 layouts expected, got ' + (rows ? rows.length : 'none')
    }
    for (var i = 0; i < rows.length; i++) {
        if (rows[i].layout != i || !rows[i].hint || !rows[i].spots || rows[i].spots.length != 16) {
            return 'layout row ' + i + ' says layout ' + rows[i].layout
        }
    }
    var herd = rows[FORMATION_HERD].spots
    if (herd[11][0] != 0 || herd[11][1] != 3 || herd[15][0] != -3 || herd[15][1] != 2) {
        return 'herd spots 11/15: ' + herd[11] + ' / ' + herd[15]
    }
    var dl1 = rows[FORMATION_DOUBLE_LINE_1]
    if (!dl1.chariot_spots || dl1.chariot_spots.length != 16 || dl1.chariot_spots[2][0] != 2 * dl1.spots[2][0]) {
        return 'chariot double line 1 spots'
    }
    var packed = __test_formation_layout_position(FORMATION_HERD, 15)
    var px = packed >> 16
    var py = (packed << 16) >> 16
    if (px != -3 || py != 2) {
        return 'formation_layout_position(herd, 15) = ' + px + ',' + py
    }
    return ''
}

function run_test() {
    __log_info_native('[test:476] formation layouts config')
    var err = t476_check()
    if (err) {
        __log_info_native('[test:476] FAIL: ' + err)
    } else {
        __log_marker('t476_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] t476_ok')
}
