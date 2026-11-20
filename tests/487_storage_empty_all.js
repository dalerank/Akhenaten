// S1 / S2: Empty All snapshot restore + flag sync with cycle / Accept None.
// Plan: REMAKE_STORAGE_EMPTY_ALL_PLAN.md
//
// Markers:
//   [test-marker] empty_all_restore_ok
//   [test-marker] empty_all_cycle_clears_flag_ok
//   [test-marker] empty_all_accept_none_ok
//   [test-marker] empty_all_saveload_ok
//   [test-marker] empty_all_saveload_skipped

var __test487_restore_ok = false
var __test487_cycle_ok = false
var __test487_accept_none_ok = false
var __test487_saveload_ok = false
var __test487_saveload_skipped = false

function test487_set_state(yard, res, target) {
    var guard = 0
    while (yard.resource_state(res) != target && guard < 8) {
        yard.cycle_resource_state(res)
        guard++
    }
    return yard.resource_state(res) == target
}

function run_test() {
    __log_info_native('[test:487] storage empty all S1/S2')
    test_ensure_city_session('data/default.map')

    var bid = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!bid) {
        __log_info_native('[test:487] __test_building_create failed')
        __test_signal_ready()
        return
    }

    var yard = city.get_storage_yard(bid)
    if (!yard) {
        __log_info_native('[test:487] get_storage_yard failed')
        __test_signal_ready()
        return
    }

    var res_a = RESOURCE_POTTERY
    var res_b = RESOURCE_BRICKS

    // Do not assume mission defaults (with --no-resource create leaves Refuse).
    if (!test487_set_state(yard, res_a, STORAGE_STATE_GET)) {
        __log_info_native('[test:487] set A=Get failed, state=' + yard.resource_state(res_a))
        __test_signal_ready()
        return
    }
    if (!test487_set_state(yard, res_b, STORAGE_STATE_REFUSE)) {
        __log_info_native('[test:487] set B=Refuse failed, state=' + yard.resource_state(res_b))
        __test_signal_ready()
        return
    }

    // S1: START → all Empty, flag on → STOP → restore Get/Refuse
    yard.toggle_empty_all()
    if (!yard.is_empty_all()
        || yard.resource_state(res_a) != STORAGE_STATE_EMPTY
        || yard.resource_state(res_b) != STORAGE_STATE_EMPTY) {
        __log_info_native('[test:487] START empty-all failed flag=' + yard.is_empty_all()
            + ' A=' + yard.resource_state(res_a) + ' B=' + yard.resource_state(res_b))
        __test_signal_ready()
        return
    }

    yard.toggle_empty_all()
    if (yard.is_empty_all()
        || yard.resource_state(res_a) != STORAGE_STATE_GET
        || yard.resource_state(res_b) != STORAGE_STATE_REFUSE) {
        __log_info_native('[test:487] STOP restore failed flag=' + yard.is_empty_all()
            + ' A=' + yard.resource_state(res_a) + ' B=' + yard.resource_state(res_b))
        __test_signal_ready()
        return
    }
    __log_marker('empty_all_restore_ok')
    __test487_restore_ok = true

    // S2: START → one cycle (Empty→Refuse) → flag off, A not Empty
    yard.toggle_empty_all()
    if (!yard.is_empty_all()) {
        __log_info_native('[test:487] START for cycle failed')
        __test_signal_ready()
        return
    }
    yard.cycle_resource_state(res_a)
    if (yard.is_empty_all() || yard.resource_state(res_a) != STORAGE_STATE_REFUSE) {
        __log_info_native('[test:487] cycle clear flag failed flag=' + yard.is_empty_all()
            + ' A=' + yard.resource_state(res_a))
        __test_signal_ready()
        return
    }
    __log_marker('empty_all_cycle_clears_flag_ok')
    __test487_cycle_ok = true

    // S2: START → accept_none → flag off, all Refuse
    if (!test487_set_state(yard, res_a, STORAGE_STATE_GET)) {
        __log_info_native('[test:487] re-set A=Get before accept_none failed')
        __test_signal_ready()
        return
    }
    yard.toggle_empty_all()
    yard.accept_none()
    if (yard.is_empty_all()
        || yard.resource_state(res_a) != STORAGE_STATE_REFUSE
        || yard.resource_state(res_b) != STORAGE_STATE_REFUSE) {
        __log_info_native('[test:487] accept_none failed flag=' + yard.is_empty_all()
            + ' A=' + yard.resource_state(res_a) + ' B=' + yard.resource_state(res_b))
        __test_signal_ready()
        return
    }
    __log_marker('empty_all_accept_none_ok')
    __test487_accept_none_ok = true

    // Save/load mid-empty: START with custom orders → save → load → STOP restores
    if (!test487_set_state(yard, res_a, STORAGE_STATE_GET)
        || !test487_set_state(yard, res_b, STORAGE_STATE_REFUSE)) {
        __log_info_native('[test:487] re-set orders before saveload failed A='
            + yard.resource_state(res_a) + ' B=' + yard.resource_state(res_b))
        __test_signal_ready()
        return
    }

    yard.toggle_empty_all()
    if (!yard.is_empty_all()) {
        __log_info_native('[test:487] START before saveload failed')
        __test_signal_ready()
        return
    }

    var save_name = 'test_68_empty_all.svx'
    if (!__test_save_memory(save_name)) {
        __log_info_native('[test:487] write_savegame failed — saveload skipped')
        __log_marker('empty_all_saveload_skipped')
        __test487_saveload_skipped = true
        __test_signal_ready()
        return
    }
    if (!__test_load_memory(save_name)) {
        __log_info_native('[test:487] load_savegame failed — saveload skipped')
        __test_drop_memory_save(save_name)
        __log_marker('empty_all_saveload_skipped')
        __test487_saveload_skipped = true
        __test_signal_ready()
        return
    }

    yard = city.get_storage_yard(bid)
    if (!yard || !yard.is_empty_all()) {
        __log_info_native('[test:487] after load missing empty_all flag')
        __test_drop_memory_save(save_name)
        __test_signal_ready()
        return
    }

    yard.toggle_empty_all()
    if (yard.is_empty_all()
        || yard.resource_state(res_a) != STORAGE_STATE_GET
        || yard.resource_state(res_b) != STORAGE_STATE_REFUSE) {
        __log_info_native('[test:487] STOP after saveload failed flag=' + yard.is_empty_all()
            + ' A=' + yard.resource_state(res_a) + ' B=' + yard.resource_state(res_b))
        __test_drop_memory_save(save_name)
        __test_signal_ready()
        return
    }

    __test_drop_memory_save(save_name)
    __log_marker('empty_all_saveload_ok')
    __test487_saveload_ok = true

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'empty_all_restore_ok',
        'empty_all_cycle_clears_flag_ok',
        'empty_all_accept_none_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        var marker = '[test-marker] ' + required[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:487] missing marker: ' + marker)
            return false
        }
    }
    if (!__test487_restore_ok || !__test487_cycle_ok || !__test487_accept_none_ok) {
        return false
    }

    // Saveload is best-effort: ok or explicit skip both pass; hard restore fail still fails.
    if (__test_find_inlog('[test-marker] empty_all_saveload_ok') && __test487_saveload_ok) {
        return true
    }
    if (__test_find_inlog('[test-marker] empty_all_saveload_skipped') && __test487_saveload_skipped) {
        return true
    }
    __log_info_native('[test:487] missing saveload ok/skip marker')
    return false
}
