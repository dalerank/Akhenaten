log_info("akhenaten: ui editor started")

[es=event_load_scenario]
function editor_on_load_scenario(ev) {
    if (!ui.window_is("window_editor_map"))
        return
    window_show_by_id("file_dialog_load_scenario")
}

[es=event_save_scenario]
function editor_on_save_scenario(ev) {
    if (!ui.window_is("window_editor_map"))
        return
    window_show_by_id("file_dialog_save_scenario")
}
