// Writing a save must not change live state: empire trader amounts used to be scaled
// by 0.01 and back by 100 in place (150 -> 100), and figure draw_mode was reset to 0.

var __test298_ok = false

function test298_fail(reason) {
    __log_marker('save_no_mutate_fail:' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:298] save does not mutate state')
    test_ensure_city_session('data/default.map')

    var handle = __test_empire_trader_create_with(RESOURCE_POTTERY, 150, 250)
    if (handle < 0) {
        return test298_fail('trader_create')
    }

    var fid = __test_figure_create(FIGURE_LABORER, -1, -1)
    if (!fid) {
        __test_empire_trader_release(handle)
        return test298_fail('figure_create')
    }
    __test_figure_set_draw_mode(fid, e_figure_draw_routing)

    var save_name = 'test_298_save_no_mutate.svx'
    for (var i = 0; i < 2; i++) {
        if (!__game_write_savegame(save_name)) {
            __test_empire_trader_release(handle)
            return test298_fail('write_' + i)
        }
        var bought = __test_empire_trader_bought_at(handle, RESOURCE_POTTERY)
        var sold = __test_empire_trader_sold_at(handle, RESOURCE_POTTERY)
        var draw_mode = __test_figure_draw_mode(fid)
        __log_info_native('[test:298] after save ' + i + ': bought=' + bought + ' sold=' + sold + ' draw_mode=' + draw_mode)
        if (bought != 150 || sold != 250) {
            __game_delete_savegame(save_name)
            __test_empire_trader_release(handle)
            return test298_fail('trader_changed_' + i)
        }
        if (draw_mode != e_figure_draw_routing) {
            __game_delete_savegame(save_name)
            __test_empire_trader_release(handle)
            return test298_fail('draw_mode_changed_' + i)
        }
    }
    __game_delete_savegame(save_name)
    __test_empire_trader_release(handle)

    __log_marker('save_no_mutate_ok')
    __test298_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test298_ok && __test_find_inlog('[test-marker] save_no_mutate_ok')
}
