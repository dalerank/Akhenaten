log_info("akhenaten: ui_window_city started")

window_city {
    ui {
        background : dummy({size:[0, 0]})
    }
}

[es=event_save_city]
function window_city_on_save_city(ev) {
    if (!ui.window_is("window_city")) {
        return
    }
    window_file_dialog_save_show(FILE_TYPE_SAVED_GAME)
}

[es=event_set_bookmark]
function window_city_on_set_bookmark(ev) {
    city.bookmarks.set(ev.value, __camera.view_center)
}

[es=event_goto_bookmark]
function window_city_on_goto_bookmark(ev) {
    var tile = city.bookmarks.get(ev.value)
    if (tile && tile.x >= 0 && tile.y >= 0) {
        __camera_go_to_bookmark_tile(tile)
    }
}
