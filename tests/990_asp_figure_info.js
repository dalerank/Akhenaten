// Debug test: load user's farm save, inspect asp figures and info window.
function run_test() {
    __log_info_native('[test:990] load farm save + asp inspect')
    var loaded = false
    var attempts = ['Save/Apa/farm.svx', 'Save/Apa/autosave_replay.svx']
    for (var a = 0; a < attempts.length && !loaded; a++) {
        loaded = game.load_savegame(attempts[a])
        __log_info_native('[test:990] load ' + attempts[a] + ' -> ' + loaded)
    }
    if (!loaded) {
        __log_info_native('[test:990] no save loaded')
        __test_signal_ready()
        return
    }
    __test_pump_frames(15)

    var asps = []
    for (var i = 1; i < 2000; i++) {
        if (!__figure_is_valid(i)) continue
        var t = __figure_get_type(i)
        if (t == FIGURE_ASP) {
            var tile = __figure_get_tile(i)
            asps.push({ id: i, x: tile.x, y: tile.y })
        }
    }
    __log_info_native('[test:990] asp count=' + asps.length)
    for (var k = 0; k < asps.length; k++) {
        var a = asps[k]
        __log_info_native('[test:990] asp id=' + a.id + ' at ' + a.x + ',' + a.y)
    }

    // For each asp: open info window via a work camp created right at its tile.
    for (var k = 0; k < asps.length; k++) {
        var a = asps[k]
        var bid = __test_building_create(BUILDING_WORK_CAMP, a.x, a.y)
        __log_info_native('[test:990] asp#' + k + ' id=' + a.id + ' at ' + a.x + ',' + a.y + ' bid=' + bid)
        if (bid) {
            __test_camera_center_building(bid)
            __test_pump_frames(6)
            __test_show_tile_info(bid)
            __test_pump_frames(10)
            var fc = __object_info_figure_count()
            var got = __test_info_ui_image('bigimage')
            var tn = __test_info_ui_text('typename')
            var nm = __test_info_ui_text('name')
            var off = city.object_info.offset
            __log_info_native('[test:990] asp#' + k + ' window offset=' + off.x + ',' + off.y)
            var f = city.get_figure(a.id)
            var img = get_image({ pack: PACK_UNLOADED, id: 25, offset: f.type })
            __log_info_native('[test:990] asp#' + k + ' window figcount=' + fc + ' typename="' + tn
                + '" name="' + nm + '" bigimage_tid=' + got
                + ' type=' + f.type + ' expected=' + (img ? img.tid : -1))
            if (k < asps.length - 1) {
                window_go_back()
                __test_pump_frames(2)
            }
        }
    }

    __test_signal_ready()
}

function check_valid() {
    return true
}
