log_info("akhenaten: ui_window_city started")

[es=event_show_advisor]
function top_menu_widget_open_submenu(ev) {
    log_info("akhenaten: ui_window_city: event_show_advisor: " + ev.advisor)
	if (!ui.window_is(WINDOW_CITY))
        return

    ui.show_advisor(ev.advisor);
}