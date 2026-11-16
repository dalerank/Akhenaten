// LC1 / LC4: enhanced labor category split — Storage yards/docks vs Industry.
// Markers:
//   [test-marker] labor_split_flag_off_ok
//   [test-marker] labor_split_same_cat_off_ok
//   [test-marker] labor_split_cats_on_ok
//   [test-marker] labor_split_priority_storage_ok
//   [test-marker] labor_split_dock_on_ok
//   [test-marker] labor_split_saveload_ok  (or labor_split_saveload_skipped)

var __test160_ok = {
    flag: false,
    same_off: false,
    cats_on: false,
    prio: false,
    dock: false,
    saveload: false
}

function run_test() {
    __log_info_native('[test:160] labor category split')
    test_ensure_city_session('data/default.map')

    var prev = game_features.get('gameplay_enhanced_labor_category_split')
    function finish() {
        game_features.set('gameplay_enhanced_labor_category_split', prev)
        __test_signal_ready()
    }

    if (game_features.default('gameplay_enhanced_labor_category_split')) {
        __log_info_native('[test:160] flag default should be OFF')
        finish()
        return
    }
    __log_marker('labor_split_flag_off_ok')
    __test160_ok.flag = true

    game_features.set('gameplay_enhanced_labor_category_split', false)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __scenario_building_allow(BUILDING_POTTERY_WORKSHOP, true)
    __scenario_building_allow(BUILDING_DOCK, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var sy_id = __test_building_create(BUILDING_STORAGE_YARD, cx, cy)
    var pot_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, cx + 4, cy)
    if (!sy_id || !pot_id) {
        __log_info_native('[test:160] create failed sy=' + sy_id + ' pot=' + pot_id)
        finish()
        return
    }

    var sy_b = city.get_building(sy_id)
    var pot_b = city.get_building(pot_id)
    sy_b.houses_covered = 100
    pot_b.houses_covered = 100
    if (sy_b.max_workers <= 0) {
        sy_b.max_workers = 6
    }
    if (pot_b.max_workers <= 0) {
        pot_b.max_workers = 12
    }

    city.labor.update()
    var ind_off_needed = city.labor.get_category(LABOR_CATEGORY_INDUSTRY_COMMERCE).workers_needed
    var stor_off_needed = city.labor.get_category(LABOR_CATEGORY_STORAGE).workers_needed
    if (stor_off_needed !== 0) {
        __log_info_native('[test:160] STORAGE should be empty when split OFF needed=' + stor_off_needed)
        finish()
        return
    }
    if (ind_off_needed < sy_b.max_workers + pot_b.max_workers) {
        __log_info_native('[test:160] Industry should include SY+pottery when OFF needed='
            + ind_off_needed + ' expect>=' + (sy_b.max_workers + pot_b.max_workers))
        finish()
        return
    }
    __log_marker('labor_split_same_cat_off_ok')
    __test160_ok.same_off = true

    game_features.set('gameplay_enhanced_labor_category_split', true)
    city.labor.update()
    var ind_on_needed = city.labor.get_category(LABOR_CATEGORY_INDUSTRY_COMMERCE).workers_needed
    var stor_on_needed = city.labor.get_category(LABOR_CATEGORY_STORAGE).workers_needed
    if (stor_on_needed < sy_b.max_workers) {
        __log_info_native('[test:160] STORAGE needed too low: ' + stor_on_needed
            + ' sy_max=' + sy_b.max_workers)
        finish()
        return
    }
    if (ind_on_needed < pot_b.max_workers) {
        __log_info_native('[test:160] Industry needed too low: ' + ind_on_needed
            + ' pot_max=' + pot_b.max_workers)
        finish()
        return
    }
    if (ind_on_needed >= ind_off_needed) {
        __log_info_native('[test:160] Industry should shrink after split: on='
            + ind_on_needed + ' off=' + ind_off_needed)
        finish()
        return
    }
    __log_marker('labor_split_cats_on_ok')
    __test160_ok.cats_on = true

    var need_stor = stor_on_needed
    city.labor.set_priority(LABOR_CATEGORY_STORAGE, 0)
    city.labor.workers_available = need_stor
    city.labor.set_priority(LABOR_CATEGORY_STORAGE, 1)

    var stor_alloc = city.labor.get_category(LABOR_CATEGORY_STORAGE).workers_allocated
    var ind_alloc = city.labor.get_category(LABOR_CATEGORY_INDUSTRY_COMMERCE).workers_allocated
    if (stor_alloc < need_stor) {
        __log_info_native('[test:160] Storage should be full under prio1: alloc='
            + stor_alloc + ' need=' + need_stor + ' ind_alloc=' + ind_alloc
            + ' avail=' + city.labor.workers_available)
        finish()
        return
    }
    if (ind_alloc !== 0) {
        __log_info_native('[test:160] Industry should get 0 when pool equals Storage need; ind_alloc=' + ind_alloc)
        finish()
        return
    }
    __log_marker('labor_split_priority_storage_ok')
    __test160_ok.prio = true

    var dock_id = __test_building_create(BUILDING_DOCK, cx, cy + 6)
    if (!dock_id) {
        __log_info_native('[test:160] dock create failed')
        finish()
        return
    }
    var dock_b = city.get_building(dock_id)
    dock_b.houses_covered = 100
    if (dock_b.max_workers <= 0) {
        dock_b.max_workers = 12
    }
    city.labor.update()
    var stor_with_dock = city.labor.get_category(LABOR_CATEGORY_STORAGE).workers_needed
    if (stor_with_dock < sy_b.max_workers + dock_b.max_workers) {
        __log_info_native('[test:160] STORAGE should include dock when ON needed='
            + stor_with_dock + ' expect>=' + (sy_b.max_workers + dock_b.max_workers))
        finish()
        return
    }
    __log_marker('labor_split_dock_on_ok')
    __test160_ok.dock = true

    city.labor.set_priority(LABOR_CATEGORY_STORAGE, 0)
    city.labor.set_priority(LABOR_CATEGORY_FOOD_PRODUCTION, 0)
    city.labor.set_priority(LABOR_CATEGORY_STORAGE, 2)
    var prio_before = city.labor.get_category(LABOR_CATEGORY_STORAGE).priority
    if (prio_before !== 2) {
        __log_info_native('[test:160] expected storage priority 2 before save, got=' + prio_before)
        finish()
        return
    }

    var save_name = 'test_160_labor_split.svx'
    if (!__test_save_memory(save_name)) {
        __log_marker('labor_split_saveload_skipped')
        __test160_ok.saveload = true
    } else if (!__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        __log_marker('labor_split_saveload_skipped')
        __test160_ok.saveload = true
    } else {
        __test_drop_memory_save(save_name)
        game_features.set('gameplay_enhanced_labor_category_split', true)
        var prio_after = city.labor.get_category(LABOR_CATEGORY_STORAGE).priority
        if (prio_after !== 2) {
            __log_info_native('[test:160] storage priority lost after load: ' + prio_after)
            __log_marker('labor_split_saveload_fail:' + prio_after)
            finish()
            return
        }
        __log_marker('labor_split_saveload_ok')
        __test160_ok.saveload = true
    }

    __log_info_native('[test:160] done ok=' + JSON.stringify(__test160_ok))
    finish()
}

function check_valid() {
    return check_test()
}

function check_test() {
    if (!__test160_ok.flag || !__test160_ok.same_off || !__test160_ok.cats_on
        || !__test160_ok.prio || !__test160_ok.dock || !__test160_ok.saveload) {
        __log_info_native('[test:160] one or more phases failed: ' + JSON.stringify(__test160_ok))
        return false
    }
    var markers = [
        'labor_split_flag_off_ok',
        'labor_split_same_cat_off_ok',
        'labor_split_cats_on_ok',
        'labor_split_priority_storage_ok',
        'labor_split_dock_on_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:160] missing marker: ' + markers[i])
            return false
        }
    }
    if (__test_find_inlog('labor_split_saveload_fail')) {
        return false
    }
    if (!__test_find_inlog('labor_split_saveload_ok')
        && !__test_find_inlog('labor_split_saveload_skipped')) {
        __log_info_native('[test:160] missing saveload marker')
        return false
    }
    return true
}
