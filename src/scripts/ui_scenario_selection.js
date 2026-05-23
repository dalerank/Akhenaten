log_info("akhenaten: scenario selection window")

[es=(window_scenario_selection, init)]
function window_scenario_selection_on_init(ev) {
    var list = ev.scenario_map_list
    var MAX_MANUAL_ENTRIES = 300

    list.set_use_file_finder(false)
    list.clear()

    var sub = window_scenario_selection.campaign_sub_dialog
    window_scenario_selection.campaign_first_mission = __game_get_first_mission_in_campaign(sub)
    if (sub !== -1) {
        for (var i = 0; i < MAX_MANUAL_ENTRIES; i++) {
            var sid = __game_campaign_mission_step_scenario_id(sub, i)
            if (sid < 0) {
                continue
            }
            list.add_item(mission_selection_title(sid), list.items_count)
        }
    }
    window_scenario_selection.scores_or_goals = 0
    window_scenario_selection.selected_mission_index = -1
    if (list.items_count > 0) {
        list.select_index(0)
        var base = window_scenario_selection.campaign_first_mission
        __game_load_mission(base, 0)
        window_scenario_selection.selected_mission_index = base
    }

    emit window_scenario_selection.mission_changed { id: scenario.campaign_scenario_id }
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_on_mission_changed(ev) {
    ev.img_scenario_thumb.image = get_image({ pack:PACK_UNLOADED, id:28, offset:scenario.campaign_scenario_id }).tid

    var sub = window_scenario_selection.campaign_sub_dialog
    ev.side_hdr_period.text = __loc(294, sub * 4)
    ev.side_mission_title.text = mission_selection_title(scenario.campaign_scenario_id)
    ev.side_subtitle.text = __lang_message_subtitle_text(200 + scenario.campaign_scenario_id)
    ev.side_year.text = scenario_selection_format_start_year(scenario.start_year)
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_on_update_scores(ev) {
    var sid = scenario.campaign_scenario_id
    if (__game_mission_scenario_beaten(sid)) {
        ev.side_scores_intro.text = __loc(297, sid)
        ev.side_scores_intro.font = FONT_NORMAL_BLACK_ON_DARK

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

        ev.side_scores_body.text = lines.join("\n")
        ev.side_scores_body.font = FONT_NORMAL_BLACK_ON_DARK
    } else {
        ev.side_scores_intro.text = __loc(305, 0)
        ev.side_scores_intro.font = FONT_NORMAL_YELLOW
        ev.side_scores_body.text = ""
    }
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

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_goals_or_scores(ev) {
    var on = window_scenario_selection.scores_or_goals != 1
    ev.btn_scores.text = window_scenario_selection.scores_or_goals ? __loc(44, 220) : __loc(44, 221)

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

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_time_limit(ev) {
    var time_kind = { kind: 0, months: 0 }
    if (__win_criteria.survival_time.enabled) {
        time_kind = { kind: 1, months: __win_criteria.survival_time.years * 12 }
    } else if (__win_criteria.time_limit.enabled) {
        time_kind = { kind: 2, months: __win_criteria.time_limit.years * 12 }
    }

    ev.info_time_limit.text = ""
    ev.info_time_limit.enabled = false

    if (!scenario.is_open_play && time_kind.kind == 1) {
        ev.info_time_limit.text = __loc(44, 55) + ":" + scenario_info_time_suffix(time_kind.months)
        ev.info_time_limit.enabled = true
    } else if (!scenario.is_open_play && time_kind.kind == 2) {
        ev.info_time_limit.text = __loc(44, 54) + ":" + scenario_info_time_suffix(time_kind.months)
        ev.info_time_limit.enabled = true
    }
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_climate(ev) {
    ev.info_line_climate.text = __loc(44, 77 + scenario.climate)
    ev.info_line_mapsize.text = __loc(44, 121 + ((Math.min(4, Math.max(0, scenario.map.width - 50) / 30)) | 0))
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_file_schema(ev) {
    ev.debug_file_schema.text = "Fileschema: " + String(__game_io_file_schema_version())
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_monuments(ev) {
    var mon = []
    if (__scenario_monuments.first > 0)
        mon.push(__loc(198, __scenario_monuments.first))

    if (__scenario_monuments.second > 0)
        mon.push(__loc(198, __scenario_monuments.second))

    if (__scenario_monuments.third > 0)
        mon.push(__loc(198, __scenario_monuments.third))

    if (mon.length == 0)
        mon.push(__loc(198, 0))
    ev.info_monuments_body.text = mon.join("\n")
}

[es=(window_scenario_selection, mission_changed)]
function window_scenario_selection_update_goals(ev) {
    var invasion_id = 112 + ((__game_scenario_invasion_count() / 2) | 0)
    ev.info_line_invasion.text = __loc(44, invasion_id)
    ev.info_line_start_region.text = __loc(2, 6)

    var goal_lines = []
    if (scenario.is_open_play) {
        goal_lines.push(__loc(145, 0))
    } else {
        if (scenario.culture_goal > 0)
            goal_lines.push(scenario_info_goal_line(scenario.culture_goal, 44, 129))
        if (scenario.prosperity_goal > 0)
            goal_lines.push(scenario_info_goal_line(scenario.prosperity_goal, 44, 130))
        if (scenario.monuments_goal > 0)
            goal_lines.push(scenario_info_goal_line(scenario.monuments_goal, 44, 131))
        if (scenario.kingdom_goal > 0)
            goal_lines.push(scenario_info_goal_line(scenario.kingdom_goal, 44, 132))
        if (scenario.population_goal > 0)
            goal_lines.push(scenario_info_goal_line(scenario.population_goal, 44, 133))
        if (scenario.housing_count_goal > 0)
            goal_lines.push(scenario_info_housing_goal_line(scenario.housing_count_goal, 29, scenario.housing_level_goal))
    }
    ev.info_goals_body.text = goal_lines.join("\n")

    var LINE_STEP = 19
    var anchor = ev.info_goals_body.pos
    var y = anchor.y + goal_lines.length * LINE_STEP + 6

    var time_shown = !scenario.is_open_play &&
        (__win_criteria.survival_time.enabled || __win_criteria.time_limit.enabled)
    if (time_shown) {
        ev.info_time_limit.pos = { x: anchor.x, y: y }
        y += LINE_STEP
    }

    ev.info_hdr_monuments.pos = { x: anchor.x, y: y }
    ev.info_monuments_body.pos = { x: anchor.x, y: y + 22 }
}

[es=(window_scenario_selection, show_scores)]
function scenario_selection_btn_scores(ev) {
    window_scenario_selection.scores_or_goals = !window_scenario_selection.scores_or_goals
    window_scenario_selection_update_goals_or_scores(ev)
}

function window_scenario_selection_btn_start() {
    if (scenario.campaign_scenario_id < 0) {
        return
    }
    __game_start_loaded_file()
}

function window_scenario_selection_on_map_list_click(entry) {
    var base = window_scenario_selection.campaign_first_mission
    __game_load_mission(base + entry.user_data | 0, 0)

    emit window_scenario_selection.mission_changed { id: scenario.campaign_scenario_id }
}


[es=window]
window_scenario_selection {
    allow_rmb_goback : true
    scores_or_goals : 1
    campaign_first_mission : -1
    campaign_sub_dialog : -1
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]

    ui {
        background             : dummy({ size[64, 48] })
        img_background         : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0 })

        debug_file_schema      : text({ pos[265, 170], size[160, 20], text:"", font:FONT_NORMAL_BLACK_ON_DARK })
        img_scenario_thumb     : image({ pos[270, 200], pack:PACK_UNLOADED, id:28, offset:0 })

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

        side_hdr_period        : text_center({ pos[545, 165], size[265, 20], align:"center", text:"", font:FONT_NORMAL_BLACK_ON_LIGHT })
        side_mission_title     : text_center({ pos[545, 192], size[265, 36], align:"center", text:"", font:FONT_LARGE_BLACK_ON_DARK, clip_area:true })
        side_subtitle          : text_center({ pos[545, 220], size[265, 20], align:"center", text:"", font:FONT_NORMAL_WHITE_ON_DARK })
        side_year              : text_center({ pos[545, 245], size[265, 17], align:"center", text:"", font:FONT_NORMAL_BLACK_ON_DARK })

        side_scores_intro      : text({ pos[545, 280], size[265, 100], wrap:px(16), text:"", font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        side_scores_body       : text({ pos[545, 280], size[265, 130], wrap:px(16), text:"", font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })

        info_hdr_mission       : text_center({ pos[545, 272], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK })
        info_line_climate      : text({ pos[545, 292], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_mapsize      : text({ pos[545, 312], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_invasion     : text({ pos[545, 332], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_start_region : text({ pos[545, 352], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_goals         : text_center({ pos[545, 377], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK })
        info_goals_body        : text({ pos[545, 404], size[265, 130], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        info_time_limit        : text({ pos[545, 484], size[265, 17], font:FONT_NORMAL_YELLOW })

        info_hdr_monuments     : text_center({ pos[545, 477], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK })
        info_monuments_body    : text({ pos[545, 494], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
    }
}
