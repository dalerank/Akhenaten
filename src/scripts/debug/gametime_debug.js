log_info("akhenaten: gametime_debug")

[es=event_draw_debug_properties]
function gametime_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Game Time")) {
        return
    }

    imgui.begin_table("Game Time", 2, imgui.table_flags_debug_props())
    imgui.property_input("day:", __game_simtime, "day")
    imgui.property_input("month:", __game_simtime, "month")
    imgui.property_input("year:", __game_simtime, "year")
    imgui.property_input("abs. tick:", __game_simtime_absolute_tick(true))
    imgui.property_input("year tick:", __game_simtime_absolute_tick(false))
    imgui.property_input("abs. day:", __game_simtime_absolute_day(true))
    imgui.property_input("year day:", __game_simtime_absolute_day(false))
    imgui.end_table()
    imgui.tree_pop()
}
