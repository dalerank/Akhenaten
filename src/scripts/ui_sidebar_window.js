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

        build_house    : image_button({
                            pos[9, 21+30], pack:PACK_GENERAL, id:108, offset:0, tooltip:[68, 20],
                            onclick: window_build_menu_build_house
                         })
        build_road     : image_button({
                            pos[9, 21+66], pack:PACK_GENERAL, id:108, offset:4, tooltip:[68, 21],
                            onclick: window_build_menu_build_road
                         })
        clear_land     : image_button({
                            pos[9, 122], pack:PACK_GENERAL, id:108, offset:8, tooltip:[68, 22],
                            onclick: window_build_menu_clear_land
                         })

        build_food     : image_button({
                            pos[9, 159], pack:PACK_GENERAL, id:108, offset:12, tooltip:[68, 23],
                            onclick: window_build_menu_build_food
                         })
        build_industry : image_button({
                            pos[9, 193], pack:PACK_GENERAL, id:108, offset:16, tooltip:[68, 24],
                            onclick: window_build_menu_build_industry
                         })
        build_distribution : image_button({
                            pos[9, 228], pack:PACK_GENERAL, id:108, offset:20, tooltip:[68, 25],
                            onclick: window_build_menu_build_distribution
                         })

        build_entertainment: image_button({
                            pos[9, 263], pack:PACK_GENERAL, id:108, offset:24, tooltip:[68, 26],
                            onclick: window_build_menu_build_entertainment
                         })
        build_religion : image_button({
                            pos[9, 296], pack:PACK_GENERAL, id:108, offset:28, tooltip:[68, 27],
                            onclick: window_build_menu_build_religion
                         })
        build_education: image_button({
                            pos[9, 332], pack:PACK_GENERAL, id:108, offset:32, tooltip:[68, 28],
                            onclick: window_build_menu_build_education
                         })

        build_health   : image_button({
                            pos[9, 368], pack:PACK_GENERAL, id:108, offset:36, tooltip:[68, 29],
                            onclick: window_build_menu_build_health
                         })
        build_admin    : image_button({
                            pos[9, 404], pack:PACK_GENERAL, id:108, offset:40, tooltip:[68, 30],
                            onclick: window_build_menu_build_admin
                         })
        build_security : image_button({
                            pos[9, 436], pack:PACK_GENERAL, id:108, offset:44, tooltip:[68, 31],
                            onclick: window_build_menu_build_security
                         })
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

        build_house    : image_button({
                            pos[9, 281], pack:PACK_GENERAL, id:136, offset:0, tooltip:[68, 20]
                            onclick: window_build_menu_build_house
                         })
        build_road     : image_button({
                            pos[9, 330], pack:PACK_GENERAL, id:136, offset:4, tooltip:[68, 21],
                            onclick: window_build_menu_build_road
                         })
        clear_land     : image_button({
                            pos[9, 381], pack:PACK_GENERAL, id:136, offset:8, tooltip:[68, 22],
                            onclick: window_build_menu_clear_land
                         })

        build_food     : image_button({
                            pos[46, 281], pack:PACK_GENERAL, id:136, offset:12, tooltip:[68, 23],
                            onclick: window_build_menu_build_food
                         })
        build_industry : image_button({
                            pos[46, 330], pack:PACK_GENERAL, id:136, offset:16, tooltip:[68, 24],
                            onclick: window_build_menu_build_industry
                         })
        build_distribution : image_button({
                            pos[46, 381], pack:PACK_GENERAL, id:136, offset:20, tooltip:[68, 25],
                            onclick: window_build_menu_build_distribution
                         })

        build_entertainment: image_button({
                            pos[86, 281], pack:PACK_GENERAL, id:136, offset:24, tooltip:[68, 26],
                            onclick: window_build_menu_build_entertainment
                         })
        build_religion : image_button({
                            pos[86, 330], pack:PACK_GENERAL, id:136, offset:28, tooltip:[68, 27],
                            onclick: window_build_menu_build_religion
                         })
        build_education: image_button({
                            pos[86, 381], pack:PACK_GENERAL, id:136, offset:32, tooltip:[68, 28],
                            onclick: window_build_menu_build_education
                         })

        build_health   : image_button({
                            pos[125, 281], pack:PACK_GENERAL, id:136, offset:36, tooltip:[68, 29],
                            onclick: window_build_menu_build_health
                         })
        build_admin    : image_button({
                            pos[125, 330], pack:PACK_GENERAL, id:136, offset:40, tooltip:[68, 30],
                            onclick: window_build_menu_build_admin
                         })
        build_security : image_button({
                            pos[125, 381], pack:PACK_GENERAL, id:136, offset:44, tooltip:[68, 31],
                            onclick: window_build_menu_build_security
                         })

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

[es=sidebar_window_draw]
function window_build_menu_on_draw(window) {
    window.build_house.readonly = false
    window.build_house.selected = (BUILDING_MENU_VACANT_HOUSE == window.opened_menu)

    window.build_road.readonly = false
    window.build_road.selected = (BUILDING_MENU_ROAD == window.opened_menu)

    window.clear_land.readonly = false
    window.clear_land.selected = (BUILDING_MENU_CLEAR_LAND == window.opened_menu)

    window.build_food.readonly = (ui.building_menu_items(BUILDING_MENU_FOOD) == 0)
    window.build_food.selected = (BUILDING_MENU_FOOD == window.opened_menu)

    window.build_industry.readonly = (ui.building_menu_items(BUILDING_MENU_INDUSTRY) == 0)
    window.build_industry.selected = (BUILDING_MENU_INDUSTRY == window.opened_menu)

    window.build_distribution.readonly = (ui.building_menu_items(BUILDING_MENU_DISTRIBUTION) == 0)
    window.build_distribution.selected = (BUILDING_MENU_DISTRIBUTION == window.opened_menu)

    window.build_entertainment.readonly = (ui.building_menu_items(BUILDING_MENU_ENTERTAINMENT) == 0)
    window.build_entertainment.selected = (BUILDING_MENU_ENTERTAINMENT == window.opened_menu)

    window.build_religion.readonly = (ui.building_menu_items(BUILDING_MENU_RELIGION) == 0)
    window.build_religion.selected = (BUILDING_MENU_RELIGION == window.opened_menu)

    window.build_education.readonly = (ui.building_menu_items(BUILDING_MENU_EDUCATION) == 0)
    window.build_education.selected = (BUILDING_MENU_EDUCATION == window.opened_menu)

    window.build_health.readonly = (ui.building_menu_items(BUILDING_MENU_HEALTH) == 0)
    window.build_health.selected = (BUILDING_MENU_HEALTH == window.opened_menu)

    window.build_admin.readonly = (ui.building_menu_items(BUILDING_MENU_ADMINISTRATION) == 0)
    window.build_admin.selected = (BUILDING_MENU_ADMINISTRATION == window.opened_menu)

    window.build_security.readonly = (ui.building_menu_items(BUILDING_MENU_SECURITY) == 0)
    window.build_security.selected = (BUILDING_MENU_SECURITY == window.opened_menu)
}

function window_city_show_problem_area() {
    var tile = __city_message_next_problem_area_grid_offset()
    if (tile.x >= 0 && tile.y >= 0) {
        city.camera_go_to(tile)
        ui.window_city_show()
    }
}

function window_build_menu_build_house() {
    ui.sidebar_set_type(BUILDING_MENU_VACANT_HOUSE)
    ui.window_build_menu_show(BUILDING_MENU_VACANT_HOUSE)
}

function window_city_overlays_right_click() {
    ui.window_message_dialog_show("message_overlay_selector")
}

function window_build_menu_build_road() {
    ui.sidebar_set_type(BUILDING_MENU_ROAD)
    ui.window_build_menu_show(BUILDING_MENU_ROAD)
}

function window_build_menu_clear_land() {
    ui.sidebar_set_type(BUILDING_MENU_CLEAR_LAND)
    ui.window_build_menu_show(BUILDING_MENU_CLEAR_LAND)
}

function window_build_menu_build_food() {
    ui.sidebar_set_type(BUILDING_MENU_FOOD)
    ui.window_build_menu_show(BUILDING_MENU_FOOD)
}

function window_build_menu_build_industry() {
    ui.sidebar_set_type(BUILDING_MENU_INDUSTRY)
    ui.window_build_menu_show(BUILDING_MENU_INDUSTRY)
}

function window_build_menu_build_distribution() {
    ui.sidebar_set_type(BUILDING_MENU_DISTRIBUTION)
    ui.window_build_menu_show(BUILDING_MENU_DISTRIBUTION)
}

function window_build_menu_build_entertainment() {
    ui.sidebar_set_type(BUILDING_MENU_ENTERTAINMENT)
    ui.window_build_menu_show(BUILDING_MENU_ENTERTAINMENT)
}

function window_build_menu_build_religion() {
    ui.sidebar_set_type(BUILDING_MENU_RELIGION)
    ui.window_build_menu_show(BUILDING_MENU_RELIGION)
}

function window_build_menu_build_education() {
    ui.sidebar_set_type(BUILDING_MENU_EDUCATION)
    ui.window_build_menu_show(BUILDING_MENU_EDUCATION)
}

function window_build_menu_build_health() {
    ui.sidebar_set_type(BUILDING_MENU_HEALTH)
    ui.window_build_menu_show(BUILDING_MENU_HEALTH)
}

function window_build_menu_build_admin() {
    ui.sidebar_set_type(BUILDING_MENU_ADMINISTRATION)
    ui.window_build_menu_show(BUILDING_MENU_ADMINISTRATION)
}

function window_build_menu_build_security() {
    ui.sidebar_set_type(BUILDING_MENU_SECURITY)
    ui.window_build_menu_show(BUILDING_MENU_SECURITY)
}