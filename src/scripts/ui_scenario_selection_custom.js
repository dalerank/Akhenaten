log_info("akhenaten: scenario selection — custom maps")

import ui_scenario_selection

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
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : outer_panel({ pos[0, 0], size[64, 48], enabled:false })

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
