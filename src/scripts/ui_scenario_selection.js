log_info("akhenaten: scenario selection window")

function scenario_selection_btn_scores() {
    __scenario_selection_info.scores_or_goals = 0
}

function scenario_selection_btn_goals() {
    __scenario_selection_info.scores_or_goals = 1
}

function window_scenario_selection_btn_start() {
    if (scenario.campaign_scenario_id === -1) {
        return
    }
    __game_start_loaded_file()
}

function window_scenario_selection_on_map_list_click(entry) {
    if (__scenario_selection_info.main_bg_kind === 2) {
        var base = __scenario_selection_info.campaign_first_mission
        var row = entry.user_data | 0
        __game_load_mission(base + row, 0)
    }
}

[es=(window_scenario_selection, main_bg)]
function window_scenario_selection_on_main_bg(ev) {
    var k = __scenario_selection_info.main_bg_kind
    ev.img_cck.enabled = (k === 1)
    ev.img_history.enabled = (k === 2)
    if (k === 1) {
        ev.img_cck.pack = PACK_UNLOADED
        ev.img_cck.id = 15
        ev.img_cck.offset = 0
    }
    if (k === 2) {
        ev.img_history.pack = PACK_UNLOADED
        ev.img_history.id = 33
        ev.img_history.offset = 0
    }
}

function scenario_info_time_suffix(months) {
    if (months >= 24) {
        return String((months / 12) | 0) + __loc(298, 9)
    }
    return String(months) + __loc(148, 15)
}

function scenario_info_goal_line(value, group, id) {
    return String(value) + " " + __loc(group, id)
}

function window_scenario_selection_set_scenario_info_visible(ev, on) {
    ev.info_hdr_mission.enabled = on
    ev.info_line_climate.enabled = on
    ev.info_line_mapsize.enabled = on
    ev.info_line_invasion.enabled = on
    ev.info_line_start_region.enabled = on
    ev.info_hdr_goals.enabled = on
    ev.info_goals_body.enabled = on
    ev.info_time_limit.enabled = on
    ev.info_hdr_monuments.enabled = on
    ev.info_monuments_body.enabled = on
    if (!on) {
        ev.info_goals_body.text = ""
        ev.info_time_limit.text = ""
        ev.info_monuments_body.text = ""
    }
}

[es=(window_scenario_selection, scenario_info)]
function window_scenario_selection_on_scenario_info(ev) {
    var s = __scenario_selection_info
    if (!s.visible) {
        window_scenario_selection_set_scenario_info_visible(ev, false)
        return
    }
    window_scenario_selection_set_scenario_info_visible(ev, true)

    ev.info_line_climate.text = __loc(44, s.climate_id)
    ev.info_line_mapsize.text = __loc(44, s.mapsize_id)
    ev.info_line_invasion.text = __loc(44, s.invasion_id)
    ev.info_line_start_region.text = __loc(2, 6)

    var goal_lines = []
    if (s.is_open_play) {
        goal_lines.push(__loc(145, 0))
    } else {
        if (s.has_culture)
            goal_lines.push(scenario_info_goal_line(s.culture, 44, 129))
        if (s.has_prosperity)
            goal_lines.push(scenario_info_goal_line(s.prosperity, 44, 130))
        if (s.has_monuments)
            goal_lines.push(scenario_info_goal_line(s.monuments, 44, 131))
        if (s.has_kingdom)
            goal_lines.push(scenario_info_goal_line(s.kingdom, 44, 132))
        if (s.has_population)
            goal_lines.push(scenario_info_goal_line(s.population, 44, 133))
        if (s.has_housing) {
            var hid = 20 + s.house_level
            goal_lines.push(scenario_info_goal_line(s.housing, 29, hid))
        }
    }
    ev.info_goals_body.text = goal_lines.join("\n")

    if (!s.is_open_play && s.time_kind == 1) {
        ev.info_time_limit.text = __loc(44, 55) + ":" + scenario_info_time_suffix(s.time_months)
    } else if (!s.is_open_play && s.time_kind == 2) {
        ev.info_time_limit.text = __loc(44, 54) + ":" + scenario_info_time_suffix(s.time_months)
    } else {
        ev.info_time_limit.text = ""
        ev.info_time_limit.enabled = false
    }

    var mon = []
    if (s.mon0 > 0)
        mon.push(__loc(198, s.mon0))
    if (s.mon1 > 0)
        mon.push(__loc(198, s.mon1))
    if (s.mon2 > 0)
        mon.push(__loc(198, s.mon2))
    if (mon.length == 0)
        mon.push(__loc(198, 0))
    ev.info_monuments_body.text = mon.join("\n")
}

window_scenario_selection {
    allow_go_back : true
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : dummy({ size[64, 48] })

        img_cck : image({ pos[0, 0], pack:PACK_UNLOADED, id:15, offset:0, enabled:false })
        img_history : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0, enabled:false })

        scenario_map_list : scrollable_list({
            pos[230, 380]
            size[16, 13]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            view_items:13
            scrollbar_margin_x:10
            draw_scrollbar_always:false
            onclick_item: window_scenario_selection_on_map_list_click
        })

        btn_scores : large_button({ pos[540, 550], size[120, 30], text[44, 221], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false, onclick: scenario_selection_btn_scores })
        btn_goals : large_button({ pos[670, 550], size[120, 30], text[44, 220], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false, onclick: scenario_selection_btn_goals })

        btn_start : image_button({ margin{right:-235, bottom:-185}, pos[440, 550], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: window_scenario_selection_btn_start })

        /* Right panel scenario info (was draw_scenario_info in C++; fed by dispatch_scenario_info_script). */
        info_hdr_mission       : text_center({ pos[545, 203], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK, enabled:false })        
        info_line_climate      : text({ pos[545, 220], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })
        info_line_mapsize      : text({ pos[545, 237], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })
        info_line_invasion     : text({ pos[545, 254], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })
        info_line_start_region : text({ pos[545, 271], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })

        info_hdr_goals         : text_center({ pos[545, 288], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK, enabled:false })
        info_goals_body        : text({ pos[545, 315], size[265, 100], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true, enabled:false })
        info_time_limit        : text({ pos[545, 415], size[265, 17], font:FONT_NORMAL_YELLOW, enabled:false })

        info_hdr_monuments     : text_center({ pos[545, 408], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK, enabled:false })
        info_monuments_body    : text({ pos[545, 425], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true, enabled:false })
    }
}
