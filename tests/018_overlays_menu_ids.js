// Overlay smoke: overlay ids resolve, stock helpers, and Cleopatra Y/Z/H hotkey defaults.
// Markers:
//   [test-marker] overlays_menu_ids_ok
//   [test-marker] overlays_hotkeys_ok
//   [test-marker] overlays_stocks_ok
//   [test-marker] overlays_helpers_ok

function run_test() {
    __log_info_native('[test:018] overlays menu ids / stocks')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false

    var ids = [
        OVERLAY_GRAIN, OVERLAY_CHICKPEAS, OVERLAY_POMEGRANATES, OVERLAY_FIGS,
        OVERLAY_MEAT, OVERLAY_GAME, OVERLAY_POTTERY, OVERLAY_JEWELRY, OVERLAY_LINEN,
        OVERLAY_BREWERY, OVERLAY_DISEASE, OVERLAY_INFECTED_HOUSING, OVERLAY_MALARIA,
        OVERLAY_WATER_CROSSINGS, OVERLAY_EMPTY_HOUSING, OVERLAY_IRRIGATION,
        OVERLAY_FLOOD_BASIN, OVERLAY_CITY_DEFENSES, OVERLAY_HIDE_CLIFFS,
        OVERLAY_MALARIA_RISK, OVERLAY_PROBLEMS, OVERLAY_COUTHOUSE
    ]

    for (var i = 0; i < ids.length; i++) {
        if (ids[i] <= OVERLAY_NONE || ids[i] >= OVERLAY_SIZE) {
            __log_info_native('[test:018] invalid overlay id index=' + i + ' value=' + ids[i])
            __test_signal_ready()
            return
        }
        city.current_overlay = ids[i]
        var title = __city_get_overlay_title(ids[i])
        if (!title) {
            __log_info_native('[test:018] empty title for overlay ' + ids[i])
            __test_signal_ready()
            return
        }
    }
    city.current_overlay = OVERLAY_NONE
    __log_marker('overlays_menu_ids_ok')

    // Cleopatra hotkeys: Y / Z / H defaults (use_defaults=1 ignores user conf).
    // KEY_Y=25 KEY_Z=26 KEY_H=8 KEY_MOD_NONE=0 KEY_MOD_CTRL=2
    var malaria_hk = __hotkey_read_mapping(HOTKEY_SHOW_OVERLAY_MALARIA_RISK, 1)
    var disease_hk = __hotkey_read_mapping(HOTKEY_SHOW_OVERLAY_DISEASE, 1)
    var cliffs_hk = __hotkey_read_mapping(HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS, 1)
    var vacant_hk = __hotkey_read_mapping(HOTKEY_BUILD_VACANT_HOUSE, 1)
    var plaza_hk = __hotkey_read_mapping(HOTKEY_BUILD_PLAZA, 1)
    if (!malaria_hk || malaria_hk.key != 25 || malaria_hk.modifiers != 0
        || !disease_hk || disease_hk.key != 26 || disease_hk.modifiers != 0
        || !cliffs_hk || cliffs_hk.key != 8 || cliffs_hk.modifiers != 0
        || !vacant_hk || vacant_hk.key != 8 || vacant_hk.modifiers != 2
        || !plaza_hk || plaza_hk.key != 26 || plaza_hk.modifiers != 2) {
        __log_info_native('[test:018] OV5 hotkey defaults mismatch'
            + ' malaria=' + (malaria_hk ? malaria_hk.key + '/' + malaria_hk.modifiers : 'null')
            + ' disease=' + (disease_hk ? disease_hk.key + '/' + disease_hk.modifiers : 'null')
            + ' cliffs=' + (cliffs_hk ? cliffs_hk.key + '/' + cliffs_hk.modifiers : 'null')
            + ' vacant=' + (vacant_hk ? vacant_hk.key + '/' + vacant_hk.modifiers : 'null')
            + ' plaza=' + (plaza_hk ? plaza_hk.key + '/' + plaza_hk.modifiers : 'null'))
        __test_signal_ready()
        return
    }
    __log_marker('overlays_hotkeys_ok')

    var hid = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!hid) {
        hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!hid) {
        __log_info_native('[test:018] failed to place house')
        __test_signal_ready()
        return
    }
    __test_house_set_population(hid, 20)
    var house = city.get_house(hid)
    if (!house) {
        __log_info_native('[test:018] house wrapper missing')
        __test_signal_ready()
        return
    }

    // Helper thresholds: clamp / tooltip keys stay in sync with goods_stock.js.
    if (typeof goods_stock_clamp_column !== 'function'
        || typeof goods_stock_tooltip_key !== 'function'
        || typeof goods_stock_food_amount !== 'function') {
        __log_info_native('[test:018] goods_stock helpers missing')
        __test_signal_ready()
        return
    }
    if (goods_stock_clamp_column(0) !== 0
        || goods_stock_clamp_column(99) !== 9
        || goods_stock_clamp_column(100) !== 10
        || goods_stock_clamp_column(250) !== 10) {
        __log_info_native('[test:018] goods_stock_clamp_column mismatch')
        __test_signal_ready()
        return
    }
    if (goods_stock_tooltip_key('pottery', 0) !== '#pottery_stocks_none'
        || goods_stock_tooltip_key('pottery', 30) !== '#pottery_stocks_low'
        || goods_stock_tooltip_key('pottery', 70) !== '#pottery_stocks_medium'
        || goods_stock_tooltip_key('pottery', 71) !== '#pottery_stocks_high') {
        __log_info_native('[test:018] goods_stock_tooltip_key mismatch')
        __test_signal_ready()
        return
    }

    // Food lookup: resource absent from mission allowed_foods → 0.
    var grain_amt = goods_stock_food_amount(house, RESOURCE_GRAIN)
    if (grain_amt < 0) {
        __log_info_native('[test:018] food amount negative')
        __test_signal_ready()
        return
    }

    if (typeof malaria_is_active_case === 'function') {
        var b = city.get_building(hid)
        if (malaria_is_active_case(b)) {
            __log_info_native('[test:018] unexpected active malaria on fresh house')
            __test_signal_ready()
            return
        }
    }

    city.current_overlay = OVERLAY_BREWERY
    var beer = house.inv(3)
    city.current_overlay = OVERLAY_POTTERY
    var pottery = house.inv(0)
    city.current_overlay = OVERLAY_DISEASE
    city.current_overlay = OVERLAY_INFECTED_HOUSING
    city.current_overlay = OVERLAY_EMPTY_HOUSING
    city.current_overlay = OVERLAY_CITY_DEFENSES
    city.current_overlay = OVERLAY_NONE

    __log_info_native('[test:018] house stocks beer=' + beer + ' pottery=' + pottery + ' grain=' + grain_amt)
    __log_marker('overlays_stocks_ok')
    __log_marker('overlays_helpers_ok')
    __test_signal_ready()
}

function check_valid() {
    // Markers written by run_test; also assert flood-basin overlay id is in range.
    if (OVERLAY_FLOOD_BASIN <= OVERLAY_NONE || OVERLAY_FLOOD_BASIN >= OVERLAY_SIZE) {
        __log_info_native('[test:018] FAIL: OVERLAY_FLOOD_BASIN invalid')
        return false
    }
    return true
}
