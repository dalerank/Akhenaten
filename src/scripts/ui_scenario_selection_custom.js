log_info("akhenaten: scenario selection — custom maps")


__scenario_selection_info = {
    dialog: MAP_SELECTION_CCK_LEGACY
    visible: 0
    is_open_play: 0
    climate_id: 0
    mapsize_id: 0
    invasion_id: 0
    culture: 0
    prosperity: 0
    monuments: 0
    kingdom: 0
    population: 0
    housing: 0
    house_level: 0
    has_culture: 0
    has_prosperity: 0
    has_monuments: 0
    has_kingdom: 0
    has_population: 0
    has_housing: 0
    time_kind: 0
    time_months: 0
    mon0: 0
    mon1: 0
    mon2: 0
    scores_or_goals: 0
    period_hover: -1
    main_bg_kind: 0
    campaign_first_mission: -1
    campaign_sub_dialog: -1
}

[es=(window_scenario_selection_custom, init)]
function window_scenario_selection_custom_on_init(ev) {
    __scenario_selection_info.dialog = MAP_SELECTION_CUSTOM
    __scenario_selection_info.scores_or_goals = 0
    __scenario_selection_info.campaign_first_mission = -1
    __scenario_selection_info.campaign_sub_dialog = -1
    scenario.campaign_scenario_id = -1
    ev.scenario_map_list.change_file_path("Maps/", "map")
    ev.scenario_map_list.refresh_file_finder()
    ev.side_mission_desc.enabled = false
}

function window_scenario_selection_custom_on_map_list_click(p) {
    if (!p || p.text === "") {
        return
    }

    var base = p.text
    var n = base.length
    var name = (n >= 4 && base.substring(n - 4).toLowerCase() === ".map") ? base : base + ".map"
    __game_load_map(name, 0)
    window_scenario_selection_custom.selected_mission_name = name
}

function window_scenario_selection_custom_btn_start() {
    if (__game_session_last_loaded_kind() !== e_session_custom_map) {
        return
    }
    __game_start_loaded_file()
}

function window_scenario_selection_custom_refresh_side_panel(ev) {
    var config = get_mission_config(scenario.campaign_scenario_id)
    var e = 0 // __game_window_scenario_selection_custom_has_map_selection()
    ev.side_mission_title.text = config.selection_title
    ev.side_subtitle.text = config.selection_subtitle
    ev.side_year.text = config.selection_year
    ev.side_mission_desc.text = config.selection_text
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
    s.mon0 = __scenario_monuments.first
    s.mon1 = __scenario_monuments.second
    s.mon2 = __scenario_monuments.third
}

[es=(window_scenario_selection_custom, ui_draw_foreground)]
function window_scenario_selection_custom_update_mission_thumb(ev) {
    ev.img_scenario_thumb.image = get_image({ pack:PACK_UNLOADED, id:28, offset:scenario.image_id }).tid
}

function window_scenario_selection_custom_refresh_info(ev) {
    window_scenario_selection_custom_refresh_side_panel(ev)
    scenario_selection_fill_custom_scenario_info()
    var s = __scenario_selection_info
    window_scenario_selection_apply_scenario_info(ev, s)
}

[es=(window_scenario_selection_custom, ui_draw_foreground)]
function window_scenario_selection_custom_on_ui_draw_foreground(ev) {
    window_scenario_selection_custom_refresh_info(ev)
}

[es=(window_scenario_selection_custom, toggle_desc)]
function window_scenario_selection_custom_toggle_desc(window) {
    window.side_mission_desc.enabled = !window.side_mission_desc.enabled
    var desc_enabled = window.side_mission_desc.enabled

    window.info_hdr_mission.enabled = !desc_enabled
    window.info_line_climate.enabled = !desc_enabled
    window.info_line_mapsize.enabled = !desc_enabled
    window.info_line_invasion.enabled = !desc_enabled
    window.info_line_start_region.enabled = !desc_enabled

    window.info_hdr_goals.enabled = !desc_enabled
    window.info_goals_body.enabled = !desc_enabled
    window.info_time_limit.enabled = !desc_enabled

    window.info_hdr_monuments.enabled = !desc_enabled
    window.info_monuments_body.enabled = !desc_enabled
}

window_scenario_selection_custom {
    allow_rmb_goback : true
    selected_mission_name : ""
    region_mission_name : ""
    thumb_mission_name : ""

    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background            : dummy({ size[64, 48] })

        debug_file_schema     : text({ pos[345, -120], size[160, 20], text:"", font:FONT_NORMAL_YELLOW })

        img_custom            : image({ pos[0, 0], pack:PACK_UNLOADED, id:32, offset:0, enabled:true })
        img_scenario_thumb    : image({ pos[270, 180], pack:PACK_UNLOADED, id:28, offset:0, enabled:false })

        scenario_map_list     : scrollable_list({
            pos[210, 360]
            size[16, 15]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            
            view_items:14
            scrollbar_margin_x:-38
            draw_scrollbar_always:false
            onclick_item: window_scenario_selection_custom_on_map_list_click
        })

        btn_start              : image_button({ pos[780, 582], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: window_scenario_selection_custom_btn_start })

        side_mission_title     : text_center({ pos[545, 160], size[265, 36], align:"center", text:"title", font:FONT_LARGE_BLACK_ON_DARK, clip_area:true })
        side_subtitle          : text_center({ pos[545, 190], size[265, 20], align:"center", text:"subtitle", font:FONT_NORMAL_WHITE_ON_DARK })
        side_year              : text_center({ pos[545, 195], size[265, 17], align:"center", text:"year", font:FONT_NORMAL_BLACK_ON_DARK })
        side_mission_desc      : text_center({ pos[545, 223], size[265, 20], multiline:true, text:"description", font:FONT_NORMAL_WHITE_ON_DARK })

        btn_toggle_desc        : image_button({ pos[745, 525], size[62, 36], border:3, pack:PACK_GENERAL, id:136, offset:68, onclick_event: "toggle_desc" })

        info_hdr_mission       : text_center({ pos[545, 223], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK })
        info_line_climate      : text({ pos[545, 240], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_mapsize      : text({ pos[545, 257], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_invasion     : text({ pos[545, 274], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_start_region : text({ pos[545, 291], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_goals         : text_center({ pos[545, 308], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK })
        info_goals_body        : text({ pos[545, 335], size[265, 100], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        info_time_limit        : text({ pos[545, 535], size[265, 17], font:FONT_NORMAL_YELLOW })

        info_hdr_monuments     : text_center({ pos[545, 458], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK })
        info_monuments_body    : text({ pos[545, 475], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
    }
}
