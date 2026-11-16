log_info("akhenaten: ui advisor fleet started")

// Layout and texts of OG advisors_fleet.c; the navy state and the button actions live in
// city_fleet_advisor.cpp (__fleet_*), ships are addressed by their 1-based index.

var FLEET_LIST_X = 38
var FLEET_LIST_Y = 76
var FLEET_ROWS_Y = 83
var FLEET_FORT_BUTTONS = "pharaoh_general/paneling_00531"
var FLEET_BUTTON_GO_TO = 0
var FLEET_BUTTON_RETURN = 1
var FLEET_BUTTON_AT_HOME = 2
var FLEET_BUTTON_IN_SERVICE = 3
var FLEET_BUTTON_NOT_IN_SERVICE = 4
var FLEET_BUTTON_NO_SERVICE = 5

var FLEET_DISPATCH_SEVERAL_REQUESTS = 2

var advisor_fleet_window_ref = null

function advisor_fleet_button_image(offset) {
    var img = get_image(FLEET_FORT_BUTTONS)
    img.tid += offset
    return img
}

function advisor_fleet_service_popup(popup) {
    if (popup > 0) {
        ui.show_ok(__loc(5, popup), __loc(5, popup + 1))
    }
}

function advisor_fleet_ships_on_render_item(p) {
    var index = p.user_data
    if (!__fleet_ship_id(index)) {
        return
    }
    var x = p.x - FLEET_LIST_X
    var row_y = p.y + (FLEET_ROWS_Y - FLEET_LIST_Y)

    ui.image(get_image({pack:PACK_GENERAL, id:79}), vec2i(x + 48, row_y - 1))
    ui.label(__loc(51, 20), vec2i(x + 100, row_y), FONT_NORMAL_WHITE_ON_DARK)
    ui.label_ex(__loc(184, __fleet_ship_crew_text(index)), vec2i(x + 140, row_y + 8), FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered, 150)
    ui.label_ex(__loc(184, __fleet_ship_hull_text(index)), vec2i(x + 273, row_y + 8), FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered, 150)

    if (!__fleet_ship_free(index)) {
        ui.label(__loc(51, 29), vec2i(x + 500, row_y + 3), FONT_NORMAL_BLACK_ON_DARK)
        return
    }

    if (ui.button({text:"", pos:[x + 440, row_y], size:[30, 30]}) == ui.button_clicked) {
        city.camera_go_to(__fleet_ship_tile(index))
        ui.window_city_show()
        return
    }
    ui.image(advisor_fleet_button_image(FLEET_BUTTON_GO_TO), vec2i(x + 443, row_y + 3))

    if (ui.button({text:"", pos:[x + 500, row_y], size:[30, 30]}) == ui.button_clicked) {
        __fleet_ship_return_to_dock(index)
    }
    var at_dock = __fleet_ship_at_dock(index)
    ui.image(advisor_fleet_button_image(at_dock ? FLEET_BUTTON_AT_HOME : FLEET_BUTTON_RETURN), vec2i(x + 503, row_y + 3))

    if (ui.button({text:"", pos:[x + 560, row_y], size:[30, 30]}) == ui.button_clicked) {
        advisor_fleet_service_popup(__fleet_ship_toggle_service(index))
        advisor_fleet_window_refresh_status(advisor_fleet_window_ref)
    }
    var service = FLEET_BUTTON_NO_SERVICE
    if (__fleet_requested_by_sea()) {
        service = __fleet_ship_in_service(index) ? FLEET_BUTTON_IN_SERVICE : FLEET_BUTTON_NOT_IN_SERVICE
    }
    ui.image(advisor_fleet_button_image(service), vec2i(x + 563, row_y + 3))
}

[es=advisor_window]
advisor_fleet_window {
    advisor: ADVISOR_FLEET
    allow_rmb_goback : true
    help_id: "message_overseer_military"
    ui : baseui(advisor_window_base, {
        advisor_area            : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2], size:[px(40), px(26)]
            ui : {
                background   : outer_panel({size[40, 26]})

                title        : text({pos[60, 12], text{group:51, id:19}, font : FONT_LARGE_BLACK_ON_LIGHT })
                advisor_icon : image({pack:PACK_GENERAL, id:128, offset:1, pos[10, 10] })

                h_go_to_1    : text({text{group:51, id:1}, pos[423, 43], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_go_to_2    : text({text{group:51, id:20}, pos[423, 58], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_return_1   : text({text{group:51, id:3}, pos[480, 43], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_return_2   : text({text{group:51, id:21}, pos[480, 58], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_hull_1     : text({text{group:51, id:22}, pos[315, 43], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_hull_2     : text({text{group:51, id:23}, pos[300, 58], font:FONT_NORMAL_BLACK_ON_LIGHT})
                h_crew       : text({text{group:51, id:24}, pos[170, 58], font:FONT_NORMAL_BLACK_ON_LIGHT})

                dispatch_btn : button({text:"", pos[545, 35], size[75, 35], onclick_event: "dispatch_now"})
                dispatch_1   : text({text{group:51, id:30}, pos[550, 40], font:FONT_NORMAL_BLACK_ON_LIGHT})
                dispatch_2   : text({text{group:51, id:31}, pos[550, 54], font:FONT_NORMAL_BLACK_ON_LIGHT})
                kingdom_1    : text({text{group:51, id:5}, pos[550, 43], font:FONT_NORMAL_BLACK_ON_LIGHT})
                kingdom_2    : text({text{group:51, id:6}, pos[550, 58], font:FONT_NORMAL_BLACK_ON_LIGHT})

                inner_panel  : inner_panel({pos[32, 70], size[36, 17]})

                ships_list   : scrollable_list({
                    pos[38, 76]
                    size[35, 17]
                    view_items: 6
                    buttons_size_y: 44
                    buttons_margin_x: 0
                    buttons_margin_y: 0
                    text_padding_x: 0
                    text_padding_y: 0
                    draw_scrollbar_always: false
                    draw_paneling: false
                    onrender_item: advisor_fleet_ships_on_render_item
                })

                no_ships_text: text({text{group:51, id:25}, pos[64, 200], size[496, -1], multiline:true, font:FONT_NORMAL_BLACK_ON_DARK })

                navy_bullet  : image({path:"pharaoh_general/paneling_00047", pos[50, 349]})
                navy_text    : text({pos[70, 348], font:FONT_NORMAL_BLACK_ON_LIGHT})
                threat_bullet_alone : image({path:"pharaoh_general/paneling_00047", pos[50, 359]})
                threat_text_alone   : text({pos[70, 358], font:FONT_NORMAL_BLACK_ON_LIGHT})
                threat_bullet: image({path:"pharaoh_general/paneling_00047", pos[50, 369]})
                threat_text  : text({pos[70, 368], font:FONT_NORMAL_BLACK_ON_LIGHT})
                request_bullet : image({path:"pharaoh_general/paneling_00047", pos[50, 389]})
                request_text : text({pos[70, 388], font:FONT_NORMAL_BLACK_ON_LIGHT})

                army_btn     : image_button({pos[532, 347], size[80, 48], pack:PACK_GENERAL, id:4, offset:0, tooltip:[68, 143], param1: ADVISOR_MILITARY, onclick_event: "show_advisor" })

                button_help  : help_button({})
            }
        })
    })
}

function advisor_fleet_amount_text(count, singular_id) {
    return count + " " + __loc(8, count == 1 ? singular_id : singular_id + 1)
}

function advisor_fleet_window_refresh_status(window) {
    if (!window) {
        return
    }
    var warships = __fleet_total_warships()
    var transports = __fleet_total_transports()
    var threat = __loc(51, __fleet_threat_text())
    var request = __loc(51, __fleet_request_text())

    var has_ships = warships > 0
    var navy = ""
    if (has_ships) {
        navy = advisor_fleet_amount_text(warships, 50)
        if (transports > 0) {
            navy += __loc(51, 32) + advisor_fleet_amount_text(transports, 58)
        }
    }
    window.navy_bullet.enabled = has_ships
    window.navy_text.enabled = has_ships
    window.navy_text.text = navy
    window.threat_bullet_alone.enabled = !has_ships
    window.threat_text_alone.enabled = !has_ships
    window.threat_text_alone.text = threat
    window.threat_bullet.enabled = has_ships
    window.threat_text.enabled = has_ships
    window.threat_text.text = threat
    window.request_text.text = request

    var dispatch = __fleet_any_in_service()
    window.dispatch_btn.enabled = dispatch
    window.dispatch_1.enabled = dispatch
    window.dispatch_2.enabled = dispatch
    window.kingdom_1.enabled = !dispatch
    window.kingdom_2.enabled = !dispatch

    window.no_ships_text.enabled = !has_ships
    window.ships_list.enabled = has_ships
}

function advisor_fleet_window_refresh(window) {
    if (!window) {
        return
    }
    advisor_fleet_window_refresh_status(window)
    var warships = __fleet_total_warships()
    var list = window.ships_list
    list.clear()
    for (var i = 1; i <= warships; i++) {
        list.add_item("ship", i)
    }
}

[es=(advisor_fleet_window, dispatch_now)]
function advisor_fleet_window_on_dispatch_now(window) {
    var result = __fleet_dispatch_now()
    if (result == FLEET_DISPATCH_SEVERAL_REQUESTS) {
        window_advisors_show_advisor(ADVISOR_KINGDOM)
        ui.show_ok(__loc(5, 102), __loc(5, 103))
        return
    }
    advisor_fleet_window_refresh(window)
}

[es=(advisor_fleet_window, init)]
function advisor_fleet_window_init(window) {
    advisor_fleet_window_ref = window
    advisor_fleet_window_refresh(window)
    advisors_toolbar_refresh(window, ADVISOR_FLEET)
}
