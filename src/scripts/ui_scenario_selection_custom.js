log_info("akhenaten: scenario selection — custom maps")

[es=(window_scenario_selection_custom, init)]
function window_scenario_selection_custom_on_init(ev) {
    __scenario_selection_info.dialog = MAP_SELECTION_CUSTOM
    __scenario_selection_info.scores_or_goals = 0
    __scenario_selection_info.campaign_first_mission = -1
    __scenario_selection_info.campaign_sub_dialog = -1
    scenario.campaign_scenario_id = -1
    ev.scenario_map_list.change_file_path("Maps/", "map")
    ev.scenario_map_list.refresh_file_finder()
}

function window_scenario_selection_custom_on_map_list_click(p) {
    if (!p || p.text === "") {
        return
    }

    var base = p.text
    var n = base.length
    var name = (n >= 4 && base.substring(n - 4).toLowerCase() === ".map") ? base : base + ".map"
    __game_load_map(name, 0)
    window_scenario_selection_custom_refresh_info(window_scenario_selection_custom)
}

function window_scenario_selection_custom_btn_start() {
    if (__game_session_last_loaded_kind() !== e_session_custom_map) {
        return
    }
    __game_start_loaded_file()
}

function window_scenario_selection_custom_refresh_side_panel(ev) {
    var e = 0 // __game_window_scenario_selection_custom_has_map_selection()
    //ev.side_custom_title.text = e ? __game_scenario_selection_custom_selected_map_basename() : ""
    ev.side_custom_subtitle.text = e ? __game_scenario_subtitle_display_utf8() : ""
    ev.side_custom_year.text = e ? scenario_selection_format_start_year(scenario.start_year) : ""
}

function scenario_selection_fill_custom_scenario_info() {
    var s = __scenario_selection_info
    s.visible = 1
    s.is_open_play = scenario.is_open_play ? 1 : 0
    s.climate_id = 77 + scenario.climate
    var msz = scenario.map.width
    s.mapsize_id = 121 + ((Math.min(4, Math.max(0, msz - 50) / 30)) | 0)
    s.invasion_id = 112 + ((__game_scenario_invasion_count() / 2) | 0)
    s.culture = scenario_win_criteria_goal(__win_criteria.culture)
    s.prosperity = scenario_win_criteria_goal(__win_criteria.prosperity)
    s.monuments = scenario_win_criteria_goal(__win_criteria.monuments)
    s.kingdom = scenario_win_criteria_goal(__win_criteria.kingdom)
    s.population = scenario_win_criteria_goal(__win_criteria.population)
    s.housing = scenario_win_criteria_goal(__win_criteria.housing_count)
    s.house_level = scenario_win_criteria_goal(__win_criteria.housing_level)
    s.has_culture = (s.culture > 0) ? 1 : 0
    s.has_prosperity = (s.prosperity > 0) ? 1 : 0
    s.has_monuments = (s.monuments > 0) ? 1 : 0
    s.has_kingdom = (s.kingdom > 0) ? 1 : 0
    s.has_population = (s.population > 0) ? 1 : 0
    s.has_housing = (s.housing > 0) ? 1 : 0
    if (__win_criteria.survival_time.enabled) {
        s.time_kind = 1
        s.time_months = __win_criteria.survival_time.years * 12
    } else if (__win_criteria.time_limit.enabled) {
        s.time_kind = 2
        s.time_months = __win_criteria.time_limit.years * 12
    } else {
        s.time_kind = 0
        s.time_months = 0
    }
    s.mon0 = __game_scenario_property_monument_slot(0)
    s.mon1 = __game_scenario_property_monument_slot(1)
    s.mon2 = __game_scenario_property_monument_slot(2)
}

function window_scenario_selection_custom_refresh_info(ev) {
    window_scenario_selection_custom_refresh_side_panel(ev)
    scenario_selection_fill_custom_scenario_info()
    var s = __scenario_selection_info
    if (!s.visible) {
        ev.img_scenario_thumb.enabled = false
        return
    }
    window_scenario_selection_update_mission_thumb(ev, scenario.image_id)
    window_scenario_selection_apply_scenario_info(ev, s)
}

[es=(window_scenario_selection_custom, ui_draw_foreground)]
function window_scenario_selection_custom_on_ui_draw_foreground(ev) {
    window_scenario_selection_custom_refresh_info(ev)
}

window_scenario_selection_custom {
    allow_rmb_goback : true
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : dummy({ size[64, 48] })

        debug_file_schema : text({ pos[345, -120], size[160, 20], text:"", font:FONT_NORMAL_YELLOW })

        img_custom : image({ pos[0, 0], pack:PACK_UNLOADED, id:32, offset:0, enabled:true })
        img_scenario_thumb : image({ pos[78, 36], pack:PACK_UNLOADED, id:28, offset:0, enabled:false })

        scenario_map_list : scrollable_list({
            pos[230, 380]
            size[16, 13]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            view_items:12
            scrollbar_margin_x:10
            draw_scrollbar_always:false
            onclick_item: window_scenario_selection_custom_on_map_list_click
        })

        btn_start : image_button({ margin{right:-235, bottom:-185}, pos[440, 550], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: window_scenario_selection_custom_btn_start })

        /* Was draw_custom_side_panel_info in C++. */
        side_custom_title : text_center({ pos[345, 28], size[265, 36], align:"center", text:"", font:FONT_LARGE_BLACK_ON_DARK, clip_area:true })
        side_custom_subtitle : text_center({ pos[345, 88], size[265, 20], align:"center", text:"", font:FONT_NORMAL_WHITE_ON_DARK })
        side_custom_year : text({ pos[345, 108], size[265, 17], text:"", font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_mission       : text_center({ pos[545, 203], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK })
        info_line_climate      : text({ pos[545, 220], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_mapsize      : text({ pos[545, 237], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_invasion     : text({ pos[545, 254], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_start_region : text({ pos[545, 271], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_goals         : text_center({ pos[545, 288], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK })
        info_goals_body        : text({ pos[545, 315], size[265, 100], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        info_time_limit        : text({ pos[545, 415], size[265, 17], font:FONT_NORMAL_YELLOW })

        info_hdr_monuments     : text_center({ pos[545, 408], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK })
        info_monuments_body    : text({ pos[545, 425], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
    }
}
