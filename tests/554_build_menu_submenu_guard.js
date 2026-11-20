// Build-menu submenu groups (BUILDING_MENU_*) must never arm the build planner,
// and an empty submenu must not be offered as a menu entry.
// Regression: in a city whose scenario lists the Farms menu group as allowed
// but none of the farm crops, selecting "Farms" armed the planner with
// BUILDING_MENU_FARMS; the next map click hit
// `verify_no_crash(params.building_size > 0)` and left the UI stuck
// ("No building model registered for type 2").

function run_test() {
    test_reload_city_session('data/default.map')
    __test_process_events()

    // Reproduce the scenario state of a map that lists menu-group ids in its
    // allowed buildings: the FARMS menu group allowed, but no farm crops, and
    // exactly one real food building (WORK_CAMP) available.
    for (var i = 0; i < BUILDING_MAX; i++) {
        __scenario_building_allow(i, false)
    }
    __scenario_building_allow(BUILDING_MENU_FARMS, true)
    __scenario_building_allow(BUILDING_WORK_CAMP, true)
    building_menu_ctrl.update('stage_normal')

    // The empty Farms submenu must not be reported as a menu entry.
    __log_marker('menu_submenu_guard:count_items_farms=' + building_menu_ctrl.count_items(BUILDING_MENU_FARMS))
    var first_index = building_menu_ctrl.next_index(BUILDING_MENU_FOOD, -1)
    var first_type = building_menu_ctrl.item_type(BUILDING_MENU_FOOD, first_index)
    __log_marker('menu_submenu_guard:next_index_food=' + first_index)
    __log_marker('menu_submenu_guard:next_index_type=' + first_type)

    // Clicking the submenu entry switches the menu but leaves the planner unarmed.
    build_menu_widget.set_submenu(BUILDING_MENU_FOOD)
    build_menu_widget.button_menu_item(0)
    __test_process_events()
    __log_marker('menu_submenu_guard:selected_submenu=' + build_menu_widget.selected_submenu)
    __log_marker('menu_submenu_guard:planner_after_submenu_click=' + city_planner.build_type)

    // A direct event for a menu group must also be a no-op.
    emit event_city_building_mode{ value: BUILDING_MENU_FARMS }
    __test_process_events()
    __log_marker('menu_submenu_guard:planner_after_direct_event=' + city_planner.build_type)

    // Real buildings still arm and place.
    var bid = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    __log_marker('menu_submenu_guard:work_camp_placed=' + (bid ? 1 : 0))

    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('menu_submenu_guard:planner_after_submenu_click=0')
        && __test_find_inlog('menu_submenu_guard:planner_after_direct_event=0')
        && __test_find_inlog('menu_submenu_guard:work_camp_placed=1')
        && __test_find_inlog('menu_submenu_guard:count_items_farms=0')
        && __test_find_inlog('menu_submenu_guard:next_index_type=' + BUILDING_WORK_CAMP)) {
        return true
    }
    __log_info_native('[test:menu_submenu_guard] guard conditions not met')
    return false
}
