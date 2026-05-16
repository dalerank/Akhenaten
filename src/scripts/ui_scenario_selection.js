log_info("akhenaten: scenario selection window")

__scenario_selection_info = {
    dialog: MAP_SELECTION_CCK_LEGACY,
    visible: 0,
    is_open_play: 0,
    climate_id: 0,
    mapsize_id: 0,
    invasion_id: 0,
    culture: 0,
    prosperity: 0,
    monuments: 0,
    kingdom: 0,
    population: 0,
    housing: 0,
    house_level: 0,
    has_culture: 0,
    has_prosperity: 0,
    has_monuments: 0,
    has_kingdom: 0,
    has_population: 0,
    has_housing: 0,
    time_kind: 0,
    time_months: 0,
    mon0: 0,
    mon1: 0,
    mon2: 0,
    scores_or_goals: 0,
    period_hover: -1,
    main_bg_kind: 0,
    campaign_first_mission: -1,
    campaign_sub_dialog: -1
}

function window_scenario_selection_reset_mission_caches() {
    window_scenario_selection.goal_mission_index = -1
    window_scenario_selection.info_mission_index = -1
    window_scenario_selection.scores_mission_index = -1
}

function window_scenario_selection_update_toggle_buttons(ev) {
    if (__scenario_selection_info.dialog !== MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        return
    }
    var goals_mode = __scenario_selection_info.scores_or_goals === 1
    var have_mission = window_scenario_selection.selected_mission_index >= 0
}

function window_scenario_selection_update_mission_thumb(ev, offset) {
    ev.img_scenario_thumb.enabled = true
    ev.img_scenario_thumb.pack = PACK_UNLOADED
    ev.img_scenario_thumb.id = 28
    ev.img_scenario_thumb.offset = offset
}

[es=(window_scenario_selection, init)]
function window_scenario_selection_on_init(ev) {
    var list = ev.scenario_map_list
    var MAX_MANUAL_ENTRIES = 300
    if (__scenario_selection_info.dialog === MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        __game_scenario_set_mode(e_scenario_normal)
        list.set_use_file_finder(false)
        list.clear()
        var sub = __scenario_selection_info.campaign_sub_dialog
        __scenario_selection_info.campaign_first_mission = __game_get_first_mission_in_campaign(sub)
        if (sub !== -1) {
            for (var i = 0; i < MAX_MANUAL_ENTRIES; i++) {
                var sid = __game_campaign_mission_step_scenario_id(sub, i)
                if (sid < 0) {
                    continue
                }
                var name = __game_campaign_mission_step_map_name_utf8(sub, i)
                if (!name || name.length === 0) {
                    continue
                }
                var row = list.items_count
                list.add_item(name, row)
            }
        }
        __scenario_selection_info.main_bg_kind = 2
        __scenario_selection_info.scores_or_goals = 1
        window_scenario_selection.selected_mission_index = -1
        window_scenario_selection_reset_mission_caches()
        window_scenario_selection_update_mission_thumb(ev, sub)
        if (list.items_count > 0) {
            list.select_index(0)
            var base = __scenario_selection_info.campaign_first_mission
            __game_load_mission(base, 0)
            window_scenario_selection.selected_mission_index = base
        }
        return
    }
    __scenario_selection_info.dialog = MAP_SELECTION_CCK_LEGACY
    __scenario_selection_info.campaign_first_mission = -1
    __scenario_selection_info.campaign_sub_dialog = -1
    __game_scenario_set_mode(e_scenario_custom_map)
    list.set_use_file_finder(true)
    list.change_file_path("Maps/", "map")
}

function window_scenario_selection_btn_start() {
    if (scenario.campaign_scenario_id === -1) {
        return
    }
    __game_start_loaded_file()
}

function window_scenario_selection_on_map_list_click(entry) {
    var base = __scenario_selection_info.campaign_first_mission
    var row = entry.user_data | 0
    __game_load_mission(base + row, 0)
    window_scenario_selection.selected_mission_index = base + row
    window_scenario_selection_reset_mission_caches()
}

function scenario_info_time_suffix(months) {
    if (months >= 24) {
        return String((months / 12) | 0) + __loc(298, 9)
    }
    return String(months) + __loc(148, 15)
}

function scenario_info_goal_line(value, group, id) {
    return __loc(group, id) + "@" + String(value)
}

function scenario_info_housing_goal_line(value, group, id) {
    return String(value) + " " + __loc(group, id)
}

function scenario_selection_format_start_year(y) {
    if (y >= 0) {
        if (game.locale_year_before_ad) {
            return String(y) + " " + __loc(20, 1)
        }
        return __loc(20, 1) + " " + String(y)
    }
    return String(-y) + " " + __loc(20, 0)
}

function scenario_selection_score_months_suffix(m) {
    if (m >= 24) {
        return String((m / 12) | 0) + __loc(298, 9)
    }
    return String(m) + __loc(148, 15)
}

function scenario_selection_scores_lines_beaten(sid) {
    var lines = []
    lines.push(__loc(298, 6) + " " + scenario_selection_score_months_suffix(__game_player_scenario_record_completion_months(sid)))
    lines.push(__loc(298, 4) + " " + String(__game_player_scenario_record_final_population(sid)))
    lines.push(__loc(298, 5) + " " + String(__game_player_scenario_record_final_funds(sid)))
    lines.push(__loc(298, 0) + " " + String(__game_player_scenario_record_rating_culture(sid)))
    lines.push(__loc(298, 1) + " " + String(__game_player_scenario_record_rating_prosperity(sid)))
    lines.push(__loc(298, 3) + " " + String(__game_player_scenario_record_rating_kingdom(sid)))
    var diff = __game_player_scenario_record_difficulty(sid)
    lines.push(__loc(298, 7) + " " + __loc(153, 1 + diff))
    lines.push(__loc(298, 8) + " " + String(__game_player_scenario_record_score(sid)))
    return lines.join("\n")
}

[es=(window_scenario_selection, ui_draw_foreground)]
function window_scenario_selection_on_update_header(ev) {
    if (__scenario_selection_info.dialog !== MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        return
    }
    if (window_scenario_selection.selected_mission_index == window_scenario_selection.info_mission_index) {
        return
    }
    window_scenario_selection.info_mission_index = window_scenario_selection.selected_mission_index

    var sub = __scenario_selection_info.campaign_sub_dialog
    window_scenario_selection_update_mission_thumb(ev, sub)
    ev.side_hdr_period.text = __loc(294, sub * 4)
    ev.side_mission_title.text = __game_scenario_selection_mission_title_trimmed()
    ev.side_subtitle.text = __game_scenario_subtitle_display_utf8()
    ev.side_year.text = scenario_selection_format_start_year(scenario.start_year)
    if (__scenario_selection_info.scores_or_goals !== 0) {
        ev.side_scores_intro.text = ""
        ev.side_scores_body.text = ""
        return
    }
}

[es=(window_scenario_selection, ui_draw_foreground)]
function window_scenario_selection_on_update_scores(ev) {
    if (__scenario_selection_info.scores_or_goals !== 0) {
        return
    }
    if (window_scenario_selection.selected_mission_index == window_scenario_selection.scores_mission_index) {
        return
    }
    window_scenario_selection.scores_mission_index = window_scenario_selection.selected_mission_index

    if (__game_mission_scenario_beaten(scenario.campaign_scenario_id)) {
        ev.side_scores_intro.text = __loc(297, scenario.campaign_scenario_id)
        ev.side_scores_intro.font = FONT_NORMAL_BLACK_ON_DARK
        ev.side_scores_body.text = scenario_selection_scores_lines_beaten(scenario.campaign_scenario_id)
        ev.side_scores_body.font = FONT_NORMAL_BLACK_ON_DARK
    } else {
        ev.side_scores_intro.text = __loc(305, 0)
        ev.side_scores_intro.font = FONT_NORMAL_YELLOW
        ev.side_scores_body.text = ""
    }
}

function scenario_selection_fill_campaign_scenario_info() {
    var s = __scenario_selection_info
    if (window_scenario_selection.selected_mission_index < 0) {
        s.visible = 0
        return
    }
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
    s.mon0 = __scenario_monuments.first
    s.mon1 = __scenario_monuments.second
    s.mon2 = __scenario_monuments.third
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

    ev.side_scores_intro.enabled = !on
    ev.side_scores_body.enabled = !on
}

function window_scenario_selection_apply_scenario_info(ev, s) {
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
            goal_lines.push(scenario_info_housing_goal_line(s.housing, 29, hid))
        }
    }
    ev.info_goals_body.text = goal_lines.join("\n")

    if (!s.is_open_play && s.time_kind == 1) {
        ev.info_time_limit.text = __loc(44, 55) + ":" + scenario_info_time_suffix(s.time_months)
        ev.info_time_limit.enabled = true
    } else if (!s.is_open_play && s.time_kind == 2) {
        ev.info_time_limit.text = __loc(44, 54) + ":" + scenario_info_time_suffix(s.time_months)
        ev.info_time_limit.enabled = true
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

[es=(window_scenario_selection, show_scores)]
function scenario_selection_btn_scores(ev) {
    __scenario_selection_info.scores_or_goals = !__scenario_selection_info.scores_or_goals
    ev.btn_scores.text = __scenario_selection_info.scores_or_goals ? __loc(44, 220) : __loc(44, 221)
    window_scenario_selection_reset_mission_caches()
}

[es=(window_scenario_selection, ui_draw_foreground)]
function window_scenario_selection_on_update_ui_state(ev) {
    if (__scenario_selection_info.dialog !== MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        return
    }
    var goals_mode = __scenario_selection_info.scores_or_goals === 1
    window_scenario_selection_set_scenario_info_visible(ev, goals_mode)
    window_scenario_selection_update_toggle_buttons(ev)
}

[es=(window_scenario_selection, ui_draw_foreground)]
function window_scenario_selection_on_update_goals(ev) {
    if (__scenario_selection_info.scores_or_goals !== 1) {
        return
    }
    if (window_scenario_selection.selected_mission_index < 0) {
        return
    }
    if (window_scenario_selection.selected_mission_index == window_scenario_selection.goal_mission_index) {
        return
    }
    window_scenario_selection.goal_mission_index = window_scenario_selection.selected_mission_index

    scenario_selection_fill_campaign_scenario_info()
    ev.debug_file_schema.text = "Fileschema: " + String(__game_io_file_schema_version())
    var s = __scenario_selection_info
    if (!s.visible) {
        return
    }

    window_scenario_selection_apply_scenario_info(ev, s)
}

window_scenario_selection {
    allow_rmb_goback : true
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    selected_mission_index : -1
    info_mission_index : -1
    goal_mission_index : -1
    scores_mission_index : -1

    ui {
        background             : dummy({ size[64, 48] })
        img_background         : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0 })

        debug_file_schema      : text({ pos[265, 170], size[160, 20], text:"", font:FONT_NORMAL_BLACK_ON_DARK })
        img_scenario_thumb     : image({ pos[270, 200], pack:PACK_UNLOADED, id:28, offset:0, enabled:false })

        scenario_map_list      : scrollable_list({
            pos[210, 360]
            size[16, 15]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            view_items:14
            scrollbar_margin_x:10
            draw_scrollbar_always:false
            onclick_item: window_scenario_selection_on_map_list_click
        })

        btn_scores             : large_button({ pos[550, 542], size[240, 30], text[44, 221], body:2, font:FONT_NORMAL_BLACK_ON_DARK, onclick_event: "show_scores" })
        btn_start              : image_button({ pos[780, 582], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: window_scenario_selection_btn_start })

        /* Left column (was native draw_side_panel_info in C++). */
        side_hdr_period        : text_center({ pos[545, 165], size[265, 20], align:"center", text:"", font:FONT_NORMAL_BLACK_ON_LIGHT })
        side_mission_title     : text_center({ pos[545, 192], size[265, 36], align:"center", text:"", font:FONT_LARGE_BLACK_ON_DARK, clip_area:true })
        side_subtitle          : text_center({ pos[545, 220], size[265, 20], align:"center", text:"", font:FONT_NORMAL_WHITE_ON_DARK })
        side_year              : text_center({ pos[545, 245], size[265, 17], align:"center", text:"", font:FONT_NORMAL_BLACK_ON_DARK })

        side_scores_intro      : text({ pos[545, 280], size[265, 100], wrap:px(16), text:"", font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        side_scores_body       : text({ pos[545, 280], size[265, 130], wrap:px(16), text:"", font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })

        /* Right panel scenario info. */
        info_hdr_mission       : text_center({ pos[545, 272], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK })
        info_line_climate      : text({ pos[545, 292], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_mapsize      : text({ pos[545, 312], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_invasion     : text({ pos[545, 332], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_start_region : text({ pos[545, 352], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_goals         : text_center({ pos[545, 377], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK })
        info_goals_body        : text({ pos[545, 404], size[265, 100], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        info_time_limit        : text({ pos[545, 484], size[265, 17], font:FONT_NORMAL_YELLOW })

        info_hdr_monuments     : text_center({ pos[545, 477], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK })
        info_monuments_body    : text({ pos[545, 494], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
    }
}
