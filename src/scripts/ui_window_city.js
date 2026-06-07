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

function window_city_copy_build_type_from_tile(tile) {
    if (tile.x < 0 || tile.y < 0) {
        return BUILDING_NONE
    }

    var bid = __building_at(tile.x, tile.y)
    if (bid) {
        var b = city.get_building(bid)
        if (b.type != BUILDING_NONE && b.state != 0) {
            var type = __building_type(__building_main_id(bid))
            if (type >= BUILDING_HOUSE_CRUDE_HUT && type <= BUILDING_HOUSE_PALATIAL_ESTATE) {
                return BUILDING_HOUSE_VACANT_LOT
            }
            return type
        }
    }

    if (terrain.is(tile, TERRAIN_GATEHOUSE)) {
        return BUILDING_MUD_GATEHOUSE
    }
    if (terrain.is(tile, TERRAIN_WALL)) {
        return BUILDING_MUD_WALL
    }
    if (terrain.is(tile, TERRAIN_ROAD)) {
        return terrain.is_plaza_or_earthquake(tile) ? BUILDING_PLAZA : BUILDING_ROAD
    }
    if (terrain.is(tile, TERRAIN_GARDEN)) {
        return BUILDING_GARDENS
    }
    if (terrain.is(tile, TERRAIN_CANAL)) {
        return BUILDING_IRRIGATION_DITCH
    }
    return BUILDING_NONE
}

[es=event_copy_build_from_cursor]
function window_city_on_copy_build_from_cursor(ev) {
    var type = window_city_copy_build_type_from_tile(__ui_screen_city_current_tile())
    if (type != BUILDING_NONE) {
        emit event_city_building_mode{ value: type }
    }
}
