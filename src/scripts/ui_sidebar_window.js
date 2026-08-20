log_info("akhenaten: sidebar window started")

sidebar_window_collapsed {
    extra_block {pack:PACK_GENERAL, id:121, offset:2}
    relief_block {pack:PACK_GENERAL, id:121, offset:5}

    expanded_offset_x  : 66
    extra_block_x      : -24

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
                            pos[9, 21+30], pack:PACK_GENERAL, id:108, offset:0, tooltip:[68, 20]
                         })
        build_road     : image_button({
                            pos[9, 21+66], pack:PACK_GENERAL, id:108, offset:4, tooltip:[68, 21]
                         })
        clear_land     : image_button({
                            pos[9, 122], pack:PACK_GENERAL, id:108, offset:8, tooltip:[68, 22]
                         })

        build_food     : image_button({
                            pos[9, 159], pack:PACK_GENERAL, id:108, offset:12, tooltip:[68, 23]
                         })
        build_industry : image_button({
                            pos[9, 193], pack:PACK_GENERAL, id:108, offset:16, tooltip:[68, 24]
                         })
        build_distribution : image_button({
                            pos[9, 228], pack:PACK_GENERAL, id:108, offset:20, tooltip:[68, 25]
                         })

        build_entertainment: image_button({
                            pos[9, 263], pack:PACK_GENERAL, id:108, offset:24, tooltip:[68, 26]
                         })
        build_religion : image_button({
                            pos[9, 296], pack:PACK_GENERAL, id:108, offset:28, tooltip:[68, 27]
                         })
        build_education: image_button({
                            pos[9, 332], pack:PACK_GENERAL, id:108, offset:32, tooltip:[68, 28]
                         })

        build_health   : image_button({
                            pos[9, 368], pack:PACK_GENERAL, id:108, offset:36, tooltip:[68, 29]
                         })
        build_admin    : image_button({
                            pos[9, 404], pack:PACK_GENERAL, id:108, offset:40, tooltip:[68, 30]
                         })
        build_security : image_button({
                            pos[9, 436], pack:PACK_GENERAL, id:108, offset:44, tooltip:[68, 31]
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
        background        : image({pos[0, 30], pack:PACK_GENERAL, id:121})
        build_image       : image({pos[11, 211], pack:PACK_GENERAL, id:117, offset:1})

        show_overlays     : link({
                               pos[4, 30], size[70, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW
                               onrclick_event: "overlays_help"
                            })
        toggle_flat       : link({
                               pos[74, 30], size[50, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW
                               text: "#sidebar_flat_buildings"
                               tooltip: "#TR_TOOLTIP_FLAT_BUILDINGS"})
        collapse          : image_button({pos[128, 30], pack:PACK_GENERAL, id:110, offset:7, tooltip:[68, 10]})

        show_advisors     : advisor_button({pos[16, 173], pack:PACK_GENERAL, id:136, offset:64, tooltip:[68, 41] })
        show_empire       : image_button({pos[90, 173], pack:PACK_GENERAL, id:136, offset:68, tooltip:[68, 42] })

        build_house       : image_button({
                               pos[9, 281], pack:PACK_GENERAL, id:136, offset:0, tooltip:[68, 20]})
        build_road        : image_button({
                               pos[9, 330], pack:PACK_GENERAL, id:136, offset:4, tooltip:[68, 21]
                            })
        clear_land        : image_button({
                               pos[9, 381], pack:PACK_GENERAL, id:136, offset:8, tooltip:[68, 22]
                            })

        build_food        : image_button({
                               pos[46, 281], pack:PACK_GENERAL, id:136, offset:12, tooltip:[68, 23]
                            })
        build_industry    : image_button({
                               pos[46, 330], pack:PACK_GENERAL, id:136, offset:16, tooltip:[68, 24]
                            })
        build_distribution : image_button({
                            pos[46, 381], pack:PACK_GENERAL, id:136, offset:20, tooltip:[68, 25]
                         })

        build_entertainment: image_button({
                            pos[86, 281], pack:PACK_GENERAL, id:136, offset:24, tooltip:[68, 26]
                           })
        build_religion    : image_button({
                             pos[86, 330], pack:PACK_GENERAL, id:136, offset:28, tooltip:[68, 27]
                          })
        build_education   : image_button({
                             pos[86, 381], pack:PACK_GENERAL, id:136, offset:32, tooltip:[68, 28]
                          })

        build_health      : image_button({
                               pos[125, 281], pack:PACK_GENERAL, id:136, offset:36, tooltip:[68, 29]
                            })
        build_admin       : image_button({
                               pos[125, 330], pack:PACK_GENERAL, id:136, offset:40, tooltip:[68, 30]
                            })
        build_security    : image_button({
                               pos[125, 381], pack:PACK_GENERAL, id:136, offset:44, tooltip:[68, 31]
                            })

        show_messages     : image_button({pos[46, 434], pack:PACK_GENERAL, id:136, offset:52, tooltip:[68,33]})
        goto_problem      : image_button({
                               pos[86, 434], pack:PACK_GENERAL, id:136, offset:56, tooltip:[68,34]})
        show_briefing     : image_button({pos[116, 434], pack:PACK_GENERAL, id:136, offset:60, tooltip:[68,35]})
        num_messages      : text({pos[52, 450], shadow:0xff000000, font:FONT_NORMAL_BLACK_ON_DARK, color:0xffffffff })
        undo_btn          : image_button({pos[9, 434], pack:PACK_GENERAL, id:136, offset:48, tooltip:[68,32] })

        extra_background  : inner_panel({pos[0, 480], size[10, 19]})

        nilometer_quality : text({pos[11, 485], size[148, 14], font:FONT_NORMAL_WHITE_ON_DARK, tooltip:"#nilometer_hud_tooltip"})
        nilometer_phase   : text({pos[11, 501], size[148, 14], font:FONT_NORMAL_WHITE_ON_DARK, tooltip:"#nilometer_hud_tooltip"})

        speed_header      : text({pos[11, 485], text:"#sidebar_speed_header", font:FONT_NORMAL_WHITE_ON_DARK})
        speed_current     : text({pos[65, 480 + 28], font:FONT_NORMAL_WHITE_ON_DARK})
        dec_speed         : arrowdown({pos[11, 470 + 30], tiny:false, allow_repeat: true })
        inc_speed         : arrowup({pos[35, 470 + 30], tiny:false, allow_repeat: true })

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

        report_bug        : image_button({pos[114, 480 + 258], path:"pharaoh_general/interface_00086", tooltip:"Report bug", border:3})
    }
}

function sidebar_window_on_mission_briefing_review() {
    mission_briefing_show(scenario.campaign_scenario_id, true)
}

function sidebar_window_draw_background(window) {
    window.build_house.readonly = false
    window.build_house.selected = (BUILDING_MENU_VACANT_HOUSE == window.opened_menu)

    window.build_road.readonly = false
    window.build_road.selected = (BUILDING_MENU_ROAD == window.opened_menu)

    window.clear_land.readonly = false
    window.clear_land.selected = (BUILDING_MENU_CLEAR_LAND == window.opened_menu)

    window.build_food.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_FOOD) == 0)
    window.build_food.selected = (BUILDING_MENU_FOOD == window.opened_menu)

    window.build_industry.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_INDUSTRY) == 0)
    window.build_industry.selected = (BUILDING_MENU_INDUSTRY == window.opened_menu)

    window.build_distribution.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_DISTRIBUTION) == 0)
    window.build_distribution.selected = (BUILDING_MENU_DISTRIBUTION == window.opened_menu)

    window.build_entertainment.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_ENTERTAINMENT) == 0)
    window.build_entertainment.selected = (BUILDING_MENU_ENTERTAINMENT == window.opened_menu)

    window.build_religion.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_RELIGION) == 0)
    window.build_religion.selected = (BUILDING_MENU_RELIGION == window.opened_menu)

    window.build_education.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_EDUCATION) == 0)
    window.build_education.selected = (BUILDING_MENU_EDUCATION == window.opened_menu)

    window.build_health.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_HEALTH) == 0)
    window.build_health.selected = (BUILDING_MENU_HEALTH == window.opened_menu)

    window.build_admin.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_ADMINISTRATION) == 0)
    window.build_admin.selected = (BUILDING_MENU_ADMINISTRATION == window.opened_menu)

    window.build_security.readonly = (building_menu_ctrl.count_items(BUILDING_MENU_SECURITY) == 0)
    window.build_security.selected = (BUILDING_MENU_SECURITY == window.opened_menu)
}

[es=(sidebar_window_expanded, ui_draw_foreground), memory=frame]
function window_build_menu_on_draw(window) {
    sidebar_window_draw_background(window)

    window.show_briefing.readonly = !ui.scenario_mission_briefing_button_enabled()
    var messages = __city_message_count()
    window.show_messages.readonly = (messages <= 0)
    window.num_messages.text = (messages > 0) ? ("" + messages) : ""

    window.undo_btn.readonly = !__ui_game_can_undo()
    window.goto_problem.readonly = !__city_message_problem_area_count()
    window.show_overlays.text = ui.sidebar_overlay_link_text()

    var flat_enabled = !!game_features.gameui_flat_buildings
    var overlay_on = (city.current_overlay != OVERLAY_NONE)
    window.toggle_flat.enabled = flat_enabled
    window.toggle_flat.readonly = false
    window.toggle_flat.darkened = 0
    if (!flat_enabled) {
        __city_flat_buildings_sync()
        window.toggle_flat.text = ""
    } else if (overlay_on) {
        // Visible disabled look while overlay wins; hotkey still toggles the flag.
        window.toggle_flat.readonly = true
        window.toggle_flat.darkened = 1
        window.toggle_flat.text = __city_flat_buildings_active()
            ? "#sidebar_flat_buildings_on"
            : "#sidebar_flat_buildings"
    } else {
        window.toggle_flat.text = __city_flat_buildings_active()
            ? "#sidebar_flat_buildings_on"
            : "#sidebar_flat_buildings"
    }
}

[es=(sidebar_window_expanded, show_overlays)]
function sidebar_window_expanded_show_overlays(window) {
    emit event_show_window{ id: "overlay_menu_widget" }
}

[es=(sidebar_window_expanded, overlays_help)]
function sidebar_window_expanded_overlays_help(window) {
    ui.window_message_dialog_show("message_overlay_selector")
}

[es=(sidebar_window_expanded, show_messages)]
function sidebar_window_expanded_show_messages(window) {
    emit event_show_window{ id: "message_list_window" }
}

[es=(sidebar_window_expanded, report_bug)]
function sidebar_window_expanded_report_bug(window) {
    emit event_show_window{ id: "report_bug_window" }
}

[es=(sidebar_window_expanded, dec_speed)]
function sidebar_window_expanded_dec_speed(window) {
    emit event_change_gamespeed{ increase: false }
}

[es=(sidebar_window_expanded, inc_speed)]
function sidebar_window_expanded_inc_speed(window) {
    emit event_change_gamespeed{ increase: true }
}

function sidebar_window_toggle_flat_buildings() {
    __city_flat_buildings_toggle()
}

[es=(sidebar_window_collapsed, ui_draw_foreground)]
function window_build_menu_on_draw_foreground(window) {
    sidebar_window_draw_background(window)
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

// --- ES sidebar click handlers ---
[es=(sidebar_window_collapsed, build_house)]
function sidebar_window_collapsed_on_build_house(window) {
    window_build_menu_build_house()
}

[es=(sidebar_window_collapsed, build_road)]
function sidebar_window_collapsed_on_build_road(window) {
    window_build_menu_build_road()
}

[es=(sidebar_window_collapsed, clear_land)]
function sidebar_window_collapsed_on_clear_land(window) {
    window_build_menu_clear_land()
}

[es=(sidebar_window_collapsed, build_food)]
function sidebar_window_collapsed_on_build_food(window) {
    window_build_menu_build_food()
}

[es=(sidebar_window_collapsed, build_industry)]
function sidebar_window_collapsed_on_build_industry(window) {
    window_build_menu_build_industry()
}

[es=(sidebar_window_collapsed, build_distribution)]
function sidebar_window_collapsed_on_build_distribution(window) {
    window_build_menu_build_distribution()
}

[es=(sidebar_window_collapsed, build_entertainment)]
function sidebar_window_collapsed_on_build_entertainment(window) {
    window_build_menu_build_entertainment()
}

[es=(sidebar_window_collapsed, build_religion)]
function sidebar_window_collapsed_on_build_religion(window) {
    window_build_menu_build_religion()
}

[es=(sidebar_window_collapsed, build_education)]
function sidebar_window_collapsed_on_build_education(window) {
    window_build_menu_build_education()
}

[es=(sidebar_window_collapsed, build_health)]
function sidebar_window_collapsed_on_build_health(window) {
    window_build_menu_build_health()
}

[es=(sidebar_window_collapsed, build_admin)]
function sidebar_window_collapsed_on_build_admin(window) {
    window_build_menu_build_admin()
}

[es=(sidebar_window_collapsed, build_security)]
function sidebar_window_collapsed_on_build_security(window) {
    window_build_menu_build_security()
}

[es=(sidebar_window_expanded, build_house)]
function sidebar_window_expanded_on_build_house(window) {
    window_build_menu_build_house()
}

[es=(sidebar_window_expanded, build_road)]
function sidebar_window_expanded_on_build_road(window) {
    window_build_menu_build_road()
}

[es=(sidebar_window_expanded, clear_land)]
function sidebar_window_expanded_on_clear_land(window) {
    window_build_menu_clear_land()
}

[es=(sidebar_window_expanded, build_food)]
function sidebar_window_expanded_on_build_food(window) {
    window_build_menu_build_food()
}

[es=(sidebar_window_expanded, build_industry)]
function sidebar_window_expanded_on_build_industry(window) {
    window_build_menu_build_industry()
}

[es=(sidebar_window_expanded, build_distribution)]
function sidebar_window_expanded_on_build_distribution(window) {
    window_build_menu_build_distribution()
}

[es=(sidebar_window_expanded, build_entertainment)]
function sidebar_window_expanded_on_build_entertainment(window) {
    window_build_menu_build_entertainment()
}

[es=(sidebar_window_expanded, build_religion)]
function sidebar_window_expanded_on_build_religion(window) {
    window_build_menu_build_religion()
}

[es=(sidebar_window_expanded, build_education)]
function sidebar_window_expanded_on_build_education(window) {
    window_build_menu_build_education()
}

[es=(sidebar_window_expanded, build_health)]
function sidebar_window_expanded_on_build_health(window) {
    window_build_menu_build_health()
}

[es=(sidebar_window_expanded, build_admin)]
function sidebar_window_expanded_on_build_admin(window) {
    window_build_menu_build_admin()
}

[es=(sidebar_window_expanded, build_security)]
function sidebar_window_expanded_on_build_security(window) {
    window_build_menu_build_security()
}

[es=(sidebar_window_expanded, toggle_flat)]
function sidebar_window_expanded_on_toggle_flat(window) {
    sidebar_window_toggle_flat_buildings()
}

[es=(sidebar_window_expanded, collapse)]
function sidebar_window_expanded_on_collapse(window) {
    __ui_sidebar_expanded_collapse()
}

[es=(sidebar_window_expanded, show_advisors)]
function sidebar_window_expanded_on_show_advisors(window) {
    window_advisors_show_checked()
}

[es=(sidebar_window_expanded, show_empire)]
function sidebar_window_expanded_on_show_empire(window) {
    window_empire_show_checked()
}

[es=(sidebar_window_expanded, goto_problem)]
function sidebar_window_expanded_on_goto_problem(window) {
    window_city_show_problem_area()
}

[es=(sidebar_window_expanded, show_briefing)]
function sidebar_window_expanded_on_show_briefing(window) {
    sidebar_window_on_mission_briefing_review()
}

[es=(sidebar_window_expanded, undo_btn)]
function sidebar_window_expanded_on_undo_btn(window) {
    __ui_game_undo_perform()
}

