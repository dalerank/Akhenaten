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
        first_advisor  : image_button({ pos[40, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        second_advisor : image_button({ pos[65, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        third_advisor  : image_button({ pos[96, -1], size[28, 28], pack:PACK_GENERAL, id:106 })

        show_overlay   : button({
                                  margin{right:-64, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_overlay
                                  onclick: building_info_window_toggle_overlay
                                })
        mothball       : button({
                                  margin{right:-90, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_mothball
                                  onclick: building_info_window_toggle_mothball
                                })

        button_help    : help_button({})
        button_close   : close_button({})
    }
}
