log_info("akhenaten: ui building info window started")

function building_info_window_toggle_overlay() {
    var b = city.get_building(city.object_info.bid)
    city.current_overlay = (city.current_overlay == b.overlay) ? OVERLAY_NONE : b.overlay
}

function building_info_window_text_mothball(window) {
    var b = city.get_building(city.object_info.bid)
    return (b.state == 1 ? "x" : "")
}

function building_info_window_text_overlay(window) {
    var b = city.get_building(city.object_info.bid)
    return (city.current_overlay == b.overlay ? "V" : "v")
}

function building_info_window_toggle_mothball() {
    var b = city.get_building(city.object_info.bid)
    if (b.max_workers) {
        b.mothball_toggle()
    }
}

function building_info_window_set_advisor_button(btn, advisor, show) {
    if (!btn) {
        return
    }
    btn.enabled = !!show
    if (!show) {
        return
    }
    var frame = (advisor - 1) * 3
    if (frame <= 0) {
        return
    }
    var portrait = get_image({pack:PACK_GENERAL, id:106, offset:frame})
    btn.image = portrait.tid
}

function building_info_window_setup_advisors(window) {
    var oi = city.object_info
    var advisors = [oi.go_to_advisor_first, oi.go_to_advisor_left_a, oi.go_to_advisor_left_b]
    var slots = ["first_advisor", "second_advisor", "third_advisor"]

    for (var i = 0; i < slots.length; i++) {
        var btn = window[slots[i]]
        if (!btn) {
            continue
        }
        var advisor = advisors[i]
        var show = advisor && city.is_advisor_available(advisor)
        building_info_window_set_advisor_button(btn, advisor, show)
    }
}

function building_info_window_show_advisor(slot) {
    var oi = city.object_info
    var advisors = [oi.go_to_advisor_first, oi.go_to_advisor_left_a, oi.go_to_advisor_left_b]
    var advisor = advisors[slot]
    if (advisor && city.is_advisor_available(advisor)) {
        window_advisors_show_advisor(advisor)
    }
}

building_info_window {
    ui {
        background     : outer_panel({size: [29, 17]})
        title          : text({ pos[0, 16], text:"${building.name}", size[px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        warning_text   : text({ pos[20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        inner_panel    : inner_panel({
                                        pos[16, 100], size[27, 5]
                                        ui {
                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos[20, 10] })
                                            workers_text : text({pos[50, 16], text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", font: FONT_NORMAL_BLACK_ON_DARK})
                                            workers_desc : text({pos[50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) })
                                        }
                                    })
        first_advisor  : image_button({ margin:{left:40, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:0, onclick_event:"show_advisor", enabled:false })
        second_advisor : image_button({ margin:{left:65, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:1, onclick_event:"show_advisor", enabled:false })
        third_advisor  : image_button({ margin:{left:96, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:2, onclick_event:"show_advisor", enabled:false })

        show_overlay   : button({
                                  margin{right:-64, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_overlay
                                })
        mothball       : button({
                                  margin{right:-90, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_mothball
                                })

        button_help    : help_button({})
        button_close   : close_button({})
    }
}


// Child windows tagged [es=building_info_window] fall back to these handlers.
[es=(building_info_window, init)]
function building_info_window_on_init(window) {
    building_info_window_setup_advisors(window)
}

[es=(building_info_window, show_advisor)]
function building_info_window_on_show_advisor(ev) {
    building_info_window_show_advisor(ev.param1)
}

[es=(building_info_window, show_overlay)]
function building_info_window_on_show_overlay(window) {
    building_info_window_toggle_overlay()
}

[es=(building_info_window, mothball)]
function building_info_window_on_mothball(window) {
    building_info_window_toggle_mothball()
}
