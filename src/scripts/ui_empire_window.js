log_info("akhenaten: ui empire window common started")

function window_empire_show_checked() {
    var avail = city.is_empire_available()
    if (avail == 1 || scenario.scmode != e_scenario_normal) {
        emit event_show_window{ id: "empire_window" }
        return
    }
    var text = (avail == 0) ? "#not_available_in_this_assignment" : "#not_available_yet"
    city.warnings.show(text)
}

[es=window]
empire_window {
    start_pos : {x: 16, y: 16}
    finish_pos : {x: 32, y: 136}
    map_size : {x: 1200, y: 1600}
    image : {pack:PACK_EMPIRE, id:1}
    bottom_image : {pack:PACK_GENERAL, id:172, offset:3}
    horizontal_bar : {pack:PACK_GENERAL, id:172, offset:1}
    vertical_bar : {pack:PACK_GENERAL, id:172, offset:0}
    cross_bar : {pack:PACK_GENERAL, id:172, offset:2}
    closed_trade_route_hl : {pack:PACK_GENERAL, id:149, offset:211}
    open_trade_route : {pack:PACK_GENERAL, id:149, offset:201}
    open_trade_route_hl : {pack:PACK_GENERAL, id:149, offset:186}

    // Matches scroll_t::drag_source
    drag_source_touch : 0
    drag_source_middle_mouse_pan : 2

    // Immediate-mode trade row layout (dynamic resource lists; not widget-tree children).
    trade_item : {
        size : {x: 120, y: 20}
        button_size : {x: 105, y: 24}
        button_pad : {x: -2, y: -2}
        font : FONT_SMALL_PLAIN
    }
    want_item : {
        size : {x: 110, y: 0}
        button_size : {x: 105, y: 24}
        button_pad : {x: -2, y: -2}
        font : FONT_SMALL_PLAIN
    }

    ui {
        background           : dummy({size[sw(0), sh(0)]})
        city_name            : header({pos[0, 0], size[100, 20], align:"center"})
        button_help          : help_button({pos[0, 0], onclick_event: "help"})
        button_close         : close_button({pos[0, 0], onclick_event: "close"})
        button_advisor       : advisor_button({pos[0, 0], onclick_event: "advisor"})
        button_pause         : button({pos[0, 0], size:[32, 32], ondraw_event: "draw_pause_button", onclick_event: "pause"})

        button_open_trade    : button({pos[0, 0], size:[440, 20], onclick_event: "open_trade"})
        info_tooltip         : text({pos[0, 0], size:[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})

        city_sell_title      : text({text[47, 11], pos[0, 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_sell_items      : dummy({pos[0, 0], size[200, 0], ondraw_event: "draw_city_sell_items"})

        city_buy_title       : text({text[47, 10], pos[0, 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_buy_items       : dummy({pos[0, 0], size[200, 0], ondraw_event: "draw_city_buy_items"})

        city_want_sell_title : text({text[47, 5], pos[0, 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_want_sell_items : dummy({pos[0, 0], ondraw_event: "draw_city_want_sell_items"})

        city_want_buy_title  : text({text[47, 4], pos[0, 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_want_buy_items  : dummy({pos[0, 0], ondraw_event: "draw_city_want_buy_items"})

        // Paint-only: army travel multiline text on top of other UI.
        object_info          : dummy({pos[0, 0], size[0, 0], ondraw_event: "draw_object_info"})
    }

    trade_amount_image : function(extraOffset) {
        return get_image({pack:PACK_GENERAL, id:171, offset: extraOffset })
    }

    adjust_scroll : __empire_map_adjust_scroll

    @selected_city {
        get: function() {
            var obj = this.selected_object
            return (obj && obj.type == EMPIRE_OBJECT_CITY) ? obj.city_id : 0
        }
    }
    @selected_object {
        get: function() {
            var pick = __empire_map_selected_object()
            return pick > 0 ? new EmpireObject(pick - 1) : null
        }
    }

    // Heap skeletons (script load). Draw mutates fields in place — never replace with frame temps.
    screen_bounds : {
        ready : false
        min_pos : {x: 0, y: 0}
        max_pos : {x: 0, y: 0}
    }
    camera : {
        valid : false
        scale : 1
        scale_safe : 1
        clip : {x: 0, y: 0}
        area : {x: 0, y: 0}
        base : {x: 0, y: 0}
        draw_origin : {x: 0, y: 0}
        viewport : {x: 0, y: 0}
        map : {x: 0, y: 0}
    }
    draw_offset : {x: 0, y: 0}
    left_pan_last_pos : {x: 0, y: 0}

    /** Selected city's trade route is deferred and drawn last (on top). */
    deferred_route_city_id : -1

    scroll_remainder_x : 0
    scroll_remainder_y : 0
    left_panning : false
    left_pan_travel : 0
    finished_scroll : 0

    route_state : {
        closed : 0
        closed_selected : 1
        open : 2
        open_selected : 3
    }
}

[es=(empire_window, go_back)]
function empire_window_on_go_back(window) {
    if (empire_window.selected_object) {
        __empire_map_clear_selected_object()
        return
    }
    __scroll_drag_end()
    game.pause_allow = false
    ui.window_city_show()
}

[es=(empire_window, init)]
function empire_window_on_init(window) {
    empire_window.scroll_remainder_x = 0
    empire_window.scroll_remainder_y = 0
    empire_window.left_panning = false
    empire_window.left_pan_travel = 0
    empire_window.left_pan_last_pos.x = 0
    empire_window.left_pan_last_pos.y = 0
    empire_window.finished_scroll = 0
    empire_window.camera.valid = false
    empire_window.screen_bounds.ready = false
}

[es=(empire_window, help)]
function empire_window_on_help(window) {
    ui.window_message_dialog_show("message_world_map")
}

[es=(empire_window, close)]
function empire_window_on_close(window) {
    game.pause_allow = false
    ui.window_city_show()
}

[es=(empire_window, advisor)]
function empire_window_on_advisor(window) {
    game.pause_allow = false
    window_advisors_show_advisor(ADVISOR_TRADE)
}

[es=(empire_window, pause)]
function empire_window_on_pause(window) {
    emit event_toggle_pause{ value: 0 }
}

[es=(empire_window, open_trade)]
function empire_window_on_open_trade(window) {
    ui.show_yesno("#popup_dialog_open_trade", empire_window_confirm_open_trade)
}

[es=(empire_window, draw_background), memory=frame]
function empire_window_draw_background(window) {
    game.pause_allow = !!game_features.gameplay_change_empire_map_runs_simulation
    empire_window_refresh_screen_bounds()
    empire_window_rebuild_camera()
    empire_window_layout_ui(window)
    empire_window_update_selection_ui(window)

    empire_window_draw_map(window)
    empire_window_draw_paneling(window)
}
