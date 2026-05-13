log_info("akhenaten: scenario selection window")

function show_scenario_company(index) {
    return function() {
        window_scenario_selection_select_campaign(index)
    }
}

window_scenario_selection {
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        /* Layout root for widget margins; not drawn (same pattern as window_dinasty_menu outer_panel). */
        background : outer_panel({ pos[0, 0], size[64, 48], enabled:false })

        /* Fullscreen map-selection art in dialog coordinates (image, not background — matches buttons). */
        img_cck : image({ pos[0, 0], pack:PACK_UNLOADED, id:15, offset:0, enabled:false })
        img_custom : image({ pos[0, 0], pack:PACK_UNLOADED, id:32, offset:0, enabled:false })
        img_history : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0, enabled:false })

        scenario_map_list : scrollable_list({
            pos[16, 210]
            size[16, 16]
            dir:"Maps/"
            file_ext:"map"
            use_file_finder:true
            view_items:15
            scrollbar_margin_x:10
            draw_scrollbar_always:false
        })

        hdr_pharaoh : text_center({ pos[220, 361], size[144, 20], align:"center", text[294, 41], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false })
        hdr_cleopatra : text_center({ pos[352, 361], size[144, 20], align:"center", text[294, 42], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false })

        camp_0 : large_button({ pos[210, 261 + 120], size[144, 25], text[294, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(0) })
        camp_1 : large_button({ pos[210, 291 + 120], size[144, 25], text[294, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(1) })
        camp_2 : large_button({ pos[210, 321 + 120], size[144, 25], text[294, 8], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(2) })
        camp_3 : large_button({ pos[210, 351 + 120], size[144, 25], text[294, 12], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(3) })
        camp_4 : large_button({ pos[210, 381 + 120], size[144, 25], text[294, 16], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(4) })
        camp_5 : large_button({ pos[362, 261 + 120], size[144, 25], text[294, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(5) })
        camp_6 : large_button({ pos[362, 291 + 120], size[144, 25], text[294, 24], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(6) })
        camp_7 : large_button({ pos[362, 321 + 120], size[144, 25], text[294, 28], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(7) })
        camp_8 : large_button({ pos[362, 351 + 120], size[144, 25], text[294, 32], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:false, onclick: show_scenario_company(8) })

        btn_scores : large_button({ pos[340, 400], size[120, 30], text[44, 221], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })
        btn_goals : large_button({ pos[470, 400], size[120, 30], text[44, 220], font:FONT_NORMAL_BLACK_ON_DARK, enabled:false })

        btn_start : image_button({ pos[600, 440], size[27, 27], pack:PACK_GENERAL, id:193, offset:4 })
    }
}
