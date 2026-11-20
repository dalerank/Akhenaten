// BR2: Low Bridge menu — Perwadjyt locked until tutorial unlock; Bridges day-0 ON.
// Bridges.map needs Cleop Maps/; without it → hermetic Nekhen day-0 ON fallback.

function run_test() {
    __game_load_mission(2)
    if (__scenario_building_allowed(BUILDING_LOW_BRIDGE)) {
        __log_marker('bridge_menu_fail:perwadjyt_day0')
    } else {
        __log_marker('bridge_menu_ok:perwadjyt_day0')
    }
    // city.use_building emits an event; with 0 frames the handler never runs.
    // Call the menu ctrl directly (same as mission2 pottery step-2 unlock).
    building_menu_ctrl.use_building(BUILDING_LOW_BRIDGE, true)
    if (!__scenario_building_allowed(BUILDING_LOW_BRIDGE)) {
        __log_marker('bridge_menu_fail:perwadjyt_unlock')
    } else {
        __log_marker('bridge_menu_ok:perwadjyt_unlock')
    }

    if (__game_file_exists("Maps/Bridges.map") && __game_load_map("Bridges.map", 1)) {
        if (__scenario_building_allowed(BUILDING_LOW_BRIDGE)) {
            __log_marker('bridge_menu_ok:bridges_day0')
        } else {
            __log_marker('bridge_menu_fail:bridges_day0')
        }
    } else {
        __log_marker('bridge_menu_skipped:bridges_map')
        // Hermetic fallback: Nekhen (pak Bridge ON) has LOW_BRIDGE in buildings[].
        __game_load_mission(3)
        if (__scenario_building_allowed(BUILDING_LOW_BRIDGE)) {
            __log_marker('bridge_menu_ok:nekhen_day0')
        } else {
            __log_marker('bridge_menu_fail:nekhen_day0')
        }
    }

    // SB2: ship bridge must stay out of campaign unlock / menu.
    if (typeof BUILDING_UNUSED_SHIP_BRIDGE_83 !== 'undefined'
        && __scenario_building_allowed(BUILDING_UNUSED_SHIP_BRIDGE_83)) {
        __log_marker('bridge_menu_fail:ship_bridge_allowed')
    } else {
        __log_marker('bridge_menu_ok:ship_bridge_absent')
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('bridge_menu_fail:')) {
        return false
    }
    if (!__test_find_inlog('bridge_menu_ok:perwadjyt_day0')) {
        return false
    }
    if (!__test_find_inlog('bridge_menu_ok:perwadjyt_unlock')) {
        return false
    }
    if (!__test_find_inlog('bridge_menu_ok:ship_bridge_absent')) {
        return false
    }
    if (__test_find_inlog('bridge_menu_ok:bridges_day0')) {
        return true
    }
    return !!__test_find_inlog('bridge_menu_ok:nekhen_day0')
}
