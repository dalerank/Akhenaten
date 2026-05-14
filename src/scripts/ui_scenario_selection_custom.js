log_info("akhenaten: scenario selection — custom maps")

[es=(window_scenario_selection_custom, init)]
function window_scenario_selection_custom_on_init(ev) {
    __scenario_selection_info.scores_or_goals = 0
    scenario.campaign_scenario_id = -1
    ev.scenario_map_list.enabled = true
    ev.scenario_map_list.change_file_path("Maps/", "map")
    ev.scenario_map_list.refresh_file_finder()
}

function window_scenario_selection_custom_on_map_list_click(p) {
    if (!p || p.text === "") {
        return
    }
    /* Same row data as C++ `onclick_item` path: `text` is FILE_NO_EXT (basename without `.map`). */
    var base = p.text
    var n = base.length
    var name = (n >= 4 && base.substring(n - 4).toLowerCase() === ".map") ? base : base + ".map"
    __game_load_map(name, 0)
}

function window_scenario_selection_custom_btn_start() {
    if (__game_session_last_loaded_kind() !== e_session_custom_map) {
        return
    }
    __game_start_loaded_file()
}

[es=(window_scenario_selection_custom, scenario_info)]
function window_scenario_selection_custom_on_scenario_info(ev) {
    window_scenario_selection_on_scenario_info(ev)
}

window_scenario_selection_custom {
    allow_go_back : true
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : dummy({ size[64, 48] })

        img_custom : image({ pos[0, 0], pack:PACK_UNLOADED, id:32, offset:0, enabled:true })

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
