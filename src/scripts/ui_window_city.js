log_info("akhenaten: ui_window_city started")

[es=event_save_city]
function window_city_on_save_city(ev) {
    if (!ui.window_is("window_city")) {
        return
    }
    window_file_dialog_save_show(FILE_TYPE_SAVED_GAME)
}
