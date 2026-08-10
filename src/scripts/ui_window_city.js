log_info("akhenaten: ui_window_city started")

window_city {
    ui {
        background : dummy({size:[0, 0]})
    }
}

[es=(window_city, draw_paused_panel)]
function window_city_draw_paused_panel(ev) {
    if (!game.paused) {
        return
    }

    var panel_w = 28 * 16
    var cam = __camera
    var x = cam.offset.x + (((cam.size_pixels.x - panel_w) / 2) | 0)
    var y = 40

    var m = __hotkey_read_mapping(HOTKEY_TOGGLE_PAUSE, false)
    var key_name = ""
    if (m && m.key) {
        key_name = __hotkey_key_display_name(m.key, m.modifiers)
    } else if (m && m.alt_key) {
        key_name = __hotkey_key_display_name(m.alt_key, m.alt_modifiers)
    }

    ui.panel({ x: x, y: y }, { x: 28, y: 3 }, UiFlags_PanelOuter)
    ui.label_ex(_format(__loc("#TR_GAME_PAUSED"), key_name), { x: x, y: 58 }, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, panel_w)
}

[es=event_save_city]
function window_city_on_save_city(ev) {
    if (!ui.window_is("window_city")) {
        return
    }
    if (!game_allows_player_save()) {
        game_toast_ironwill_save_blocked()
        return
    }
    window_show_by_id("file_dialog_save")
}

[es=event_load_city]
function window_city_on_load_city(ev) {
    if (!ui.window_is("window_city")) {
        return
    }
    if (!game_allows_midgame_load()) {
        game_toast_ironwill_load_blocked()
        return
    }
    window_show_by_id("file_dialog_load")
}

// Single-slot quicksave. Ironwill: game_allows_player_save() / midgame load gate.
var QUICKSAVE_FILENAME = "quicksave.svx"

function quicksave_fullpath() {
    return "Save/" + game.dynasty_name + "/" + QUICKSAVE_FILENAME
}

[es=event_quicksave]
function window_city_on_quicksave(ev) {
    if (!ui.window_is("window_city")) {
        return
    }

    if (!game_allows_player_save()) {
        game_toast_ironwill_save_blocked()
        return
    }

    if (!game.write_savegame(QUICKSAVE_FILENAME)) {
        log_warning("Quicksave failed: " + QUICKSAVE_FILENAME)
        city.warnings.show("#quicksave_failed")
        return
    }

    city.warnings.show("#quicksave_ok")
}

[es=event_quickload]
function window_city_on_quickload(ev) {
    if (!ui.window_is("window_city")) {
        return
    }

    if (!game_allows_midgame_load()) {
        game_toast_ironwill_load_blocked()
        return
    }

    // load_savegame calls pre_load() before open — must not call if missing.
    var path = quicksave_fullpath()
    if (!game.file_exists(path)) {
        log_warning("Quickload: no file " + path)
        city.warnings.show("#quicksave_missing")
        return
    }

    if (!game.load_savegame(QUICKSAVE_FILENAME)) {
        log_warning("Quickload failed: " + QUICKSAVE_FILENAME)
        city.warnings.show("#quickload_failed")
        return
    }

    // After load: city window is shown; warning must run post-load.
    city.warnings.show("#quickload_ok")
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
        return terrain.wall_building_type(tile)
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
