log_info("akhenaten: scenario selection — custom maps")

[es=(window_scenario_selection_custom, init)]
function window_scenario_selection_custom_on_init(ev) {
    var list = ev.scenario_map_list
    list.change_file_path("Maps/", "map")
    list.refresh_file_finder()
    if (list.items_count > 0) {
        list.select_index(0)
        window_scenario_selection_custom_on_map_list_click({ text: list.selected_text(0) })
    }
}

function window_scenario_selection_custom_on_map_list_click(p) {
    if (!p || p.text === "") {
        return
    }

    var base = p.text
    var n = base.length
    var name = (n >= 4 && base.substring(n - 4).toLowerCase() === ".map") ? base : base + ".map"
    __game_load_map(name, 0)

    emit window_scenario_selection_custom.mission_changed { id: scenario.campaign_scenario_id }
}

function window_scenario_selection_custom_btn_start() {
    if (scenario.campaign_scenario_id < 0) {
        return
    }
    __game_start_loaded_file()
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_on_mission_changed(ev) {
    ev.img_scenario_thumb.image = get_image({ pack:PACK_UNLOADED, id:28, offset:scenario.campaign_scenario_id }).tid
    ev.side_mission_title.text = mission_selection_title(scenario.campaign_scenario_id)
    ev.side_subtitle.text = scenario.subtitle
    ev.side_year.text = scenario_selection_format_start_year(scenario.start_year)
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_update_climate(ev) {
    window_scenario_selection_update_climate(ev)
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_update_goals(ev) {
    window_scenario_selection_update_goals(ev)
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_update_monuments(ev) {
    window_scenario_selection_update_monuments(ev)
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_update_time_limit(ev) {
    window_scenario_selection_update_time_limit(ev)
}

[es=(window_scenario_selection_custom, mission_changed)]
function window_scenario_selection_custom_update_file_schema(ev) {
    window_scenario_selection_update_file_schema(ev)
}

[es=window]
window_scenario_selection_custom {
    allow_rmb_goback : true

    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background            : dummy({ size[64, 48] })

        debug_file_schema     : text({ pos[265, 170], size[160, 20], text:"", font:FONT_NORMAL_BLACK_ON_DARK })

        img_custom            : image({ pos[0, 0], pack:PACK_UNLOADED, id:32, offset:0, enabled:true })
        img_scenario_thumb    : image({ pos[270, 200], pack:PACK_UNLOADED, id:28, offset:0 })

        scenario_map_list     : scrollable_list({
            pos[210, 360]
            size[16, 15]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            view_items:14
            scrollbar_margin_x:10
            draw_scrollbar_always:false
            onclick_item: window_scenario_selection_custom_on_map_list_click
        })

        btn_start              : image_button({ pos[780, 582], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: window_scenario_selection_custom_btn_start })

        side_mission_title     : text_center({ pos[545, 162], size[265, 36], align:"center", text:"", font:FONT_LARGE_BLACK_ON_DARK, clip_area:true })
        side_subtitle          : text_center({ pos[545, 200], size[265, 20], align:"center", text:"", font:FONT_NORMAL_WHITE_ON_DARK })
        side_year              : text_center({ pos[545, 225], size[265, 17], align:"center", text:"", font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_mission       : text_center({ pos[545, 252], size[265, 17], align:"center", text[44, 10], font:FONT_NORMAL_WHITE_ON_DARK })
        info_line_climate      : text({ pos[545, 272], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_mapsize      : text({ pos[545, 292], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_invasion     : text({ pos[545, 312], size[265, 17], font:FONT_NORMAL_BLACK_ON_DARK })
        info_line_start_region : text({ pos[545, 332], size[265, 17], text[2, 6], font:FONT_NORMAL_BLACK_ON_DARK })

        info_hdr_goals         : text_center({ pos[545, 347], size[265, 17], align:"center", text[44, 127], font:FONT_NORMAL_WHITE_ON_DARK })
        info_goals_body        : text({ pos[545, 374], size[265, 100], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
        info_time_limit        : text({ pos[545, 484], size[265, 17], font:FONT_NORMAL_YELLOW })

        info_hdr_monuments     : text_center({ pos[545, 487], size[265, 17], align:"center", text[41, 48], font:FONT_NORMAL_WHITE_ON_DARK })
        info_monuments_body    : text({ pos[545, 504], size[265, 51], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })
    }
}
