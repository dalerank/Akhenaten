log_info("akhenaten: sidebar window started")

sidebar_window_extra {
  ui {
    background        : inner_panel({pos[0, 480], size[10, 19]})

    speed_header      : text({pos[11, 485], text:"${loc.sidebar_speed_header}", font:FONT_NORMAL_WHITE_ON_DARK})
    speed_current     : text({pos[65, 480 + 28], font:FONT_NORMAL_WHITE_ON_DARK})
    dec_speed         : arrowdown({pos[11, 470 + 30], tiny:false})
    inc_speed         : arrowup({pos[35, 470 + 30], tiny:false})

    unemp_header      : text({pos[11, 480 + 50], text:[68, 135], font:FONT_NORMAL_WHITE_ON_DARK})
    unemp_current     : text({pos[11, 480 + 70], font:FONT_NORMAL_WHITE_ON_DARK})

    population_header : text({pos[11, 480 + 90], font:FONT_NORMAL_WHITE_ON_DARK})
    population_current: text({pos[11, 480 + 110]})

    culture_header    : text({pos[11, 480 + 130], font:FONT_NORMAL_WHITE_ON_DARK})
    culture_current   : text({pos[11, 480 + 150]})

    prosperity_header : text({pos[11, 480 + 170], font:FONT_NORMAL_WHITE_ON_DARK})
    prosperity_current: text({pos[11, 480 + 190]})

    monument_header   : text({pos[11, 480 + 210], font:FONT_NORMAL_WHITE_ON_DARK})
    monument_current  : text({pos[11, 480 + 230]})

    kingdom_header    : text({pos[11, 480 + 250], font:FONT_NORMAL_WHITE_ON_DARK})
    kingdom_current   : text({pos[11, 480 + 270]})
  }
}

sidebar_window_collapsed {
    extra_block {pack:PACK_GENERAL, id:121, offset:1}
    relief_block {pack:PACK_GENERAL, id:121, offset:5}

    expanded_offset_x  : 66
    extra_block_x      : 0

    slider {
        deceleration_offset_x     : 5
        slide_acceleration_millis : 65
        slide_speed_x             : 7
    }

    ui {
        // 68-xx tooltips for buttons
        background     : image({pos[0, 30], pack:PACK_GENERAL, id:121, offset:1})
        expand         : image_button({pos[8, 30], pack:PACK_GENERAL, id:110, offset:10, tooltip:[68, 12]})

        build_house    : image_button({pos[9, 21+30], pack:PACK_GENERAL, id:108, offset:0, tooltip:[68, 20]})
        build_road     : image_button({pos[9, 21+66], pack:PACK_GENERAL, id:108, offset:4, tooltip:[68, 21]})
        clear_land     : image_button({pos[9, 122], pack:PACK_GENERAL, id:108, offset:8, tooltip:[68, 22]})

        build_food     : image_button({pos[9, 159], pack:PACK_GENERAL, id:108, offset:12, tooltip:[68, 23]})
        build_industry : image_button({pos[9, 193], pack:PACK_GENERAL, id:108, offset:16, tooltip:[68, 24]})
        build_distribution : image_button({pos[9, 228], pack:PACK_GENERAL, id:108, offset:20, tooltip:[68, 25]})

        build_entertainment: image_button({pos[9, 263], pack:PACK_GENERAL, id:108, offset:24, tooltip:[68, 26]})
        build_religion : image_button({pos[9, 296], pack:PACK_GENERAL, id:108, offset:28, tooltip:[68, 27]})
        build_education: image_button({pos[9, 332], pack:PACK_GENERAL, id:108, offset:32, tooltip:[68, 28]})

        build_health   : image_button({pos[9, 368], pack:PACK_GENERAL, id:108, offset:36, tooltip:[68, 29]})
        build_admin    : image_button({pos[9, 404], pack:PACK_GENERAL, id:108, offset:40, tooltip:[68, 30]})
        build_security : image_button({pos[9, 436], pack:PACK_GENERAL, id:108, offset:44, tooltip:[68, 31]})
    }
}

sidebar_window_expanded {
    def_image {pack:PACK_GENERAL, id:117, offset:1 }
    extra_block {pack:PACK_GENERAL, id:121, offset:2}
    relief_block {pack:PACK_GENERAL, id:121, offset:4}

    extra_block_x      : -24
    expanded_offset_x  : 186

    slider {
        deceleration_offset_x : 125
        slide_acceleration_millis : 65
        slide_speed_x      : 7
    }

    ui {
        // 68-xx tooltips for buttons
        background     : image({pos[0, 30], pack:PACK_GENERAL, id:121})
        build_image    : image({pos[11, 211]})

        show_overlays  : link({
                            pos[4, 30], size[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW
                            onclick: ui.window_overlay_menu_show
                            onrclick: window_city_overlays_right_click
                         })
        collapse       : image_button({pos[128, 30], pack:PACK_GENERAL, id:110, offset:7, tooltip:[68, 10]})

        show_advisors  : advisor_button({pos[16, 173], pack:PACK_GENERAL, id:136, offset:64, tooltip:[68, 41], onclick: window_advisors_show_checked })
        show_empire    : image_button({pos[90, 173], pack:PACK_GENERAL, id:136, offset:68, tooltip:[68, 42], onclick: window_empire_show_checked })

        build_house    : image_button({param1:333, pos[9, 281], pack:PACK_GENERAL, id:136, offset:0, tooltip:[68, 20]})
        build_road     : image_button({pos[9, 330], pack:PACK_GENERAL, id:136, offset:4, tooltip:[68, 21]})
        clear_land     : image_button({pos[9, 381], pack:PACK_GENERAL, id:136, offset:8, tooltip:[68, 22]})

        build_food     : image_button({pos[46, 281], pack:PACK_GENERAL, id:136, offset:12, tooltip:[68, 23]})
        build_industry : image_button({pos[46, 330], pack:PACK_GENERAL, id:136, offset:16, tooltip:[68, 24]})
        build_distribution : image_button({pos[46, 381], pack:PACK_GENERAL, id:136, offset:20, tooltip:[68, 25]})

        build_entertainment: image_button({pos[86, 281], pack:PACK_GENERAL, id:136, offset:24, tooltip:[68, 26]})
        build_religion : image_button({pos[86, 330], pack:PACK_GENERAL, id:136, offset:28, tooltip:[68, 27]})
        build_education: image_button({pos[86, 381], pack:PACK_GENERAL, id:136, offset:32, tooltip:[68, 28]})

        build_health   : image_button({pos[125, 281], pack:PACK_GENERAL, id:136, offset:36, tooltip:[68, 29]})
        build_admin    : image_button({pos[125, 330], pack:PACK_GENERAL, id:136, offset:40, tooltip:[68, 30]})
        build_security : image_button({pos[125, 381], pack:PACK_GENERAL, id:136, offset:44, tooltip:[68, 31]})

        show_messages  : image_button({pos[46, 434], pack:PACK_GENERAL, id:136, offset:52, tooltip:[68,33]})
        goto_problem   : image_button({
                            pos[86, 434], pack:PACK_GENERAL, id:136, offset:56, tooltip:[68,34]
                            onclick: window_city_show_problem_area
                         })
        show_briefing  : image_button({pos[116, 434], pack:PACK_GENERAL, id:136, offset:60, tooltip:[68,35]})
        num_messages   : text({pos[52, 450], shadow:0xff000000, font:FONT_NORMAL_BLACK_ON_DARK, color:0xffffffff })
        undo_btn       : image_button({pos[9, 434], pack:PACK_GENERAL, id:136, offset:48, tooltip:[68,32]})
    }
}

function window_city_show_problem_area() {
    var tile = __city_message_next_problem_area_grid_offset()
    if (tile.x >= 0 && tile.y >= 0) {
        city.camera_go_to(tile)
        ui.window_city_show()
    }
}

function window_city_overlays_right_click() {
    ui.window_message_dialog_show("message_overlay_selector")
}