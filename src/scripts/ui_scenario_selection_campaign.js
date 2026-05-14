log_info("akhenaten: scenario selection — campaign periods")

function show_scenario_company(index) {
    return function() {
        window_scenario_selection_select_campaign(index)
    }
}

function campaign_period_hover(index) {
    return function() {
        __scenario_selection_info.period_hover = index
    }
}

function campaign_period_unhover() {
    __scenario_selection_info.period_hover = -1
}

window_scenario_selection_campaign {
    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : outer_panel({ pos[0, 0], size[64, 48], enabled:false })

        img_history : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0, enabled:true })

        hdr_pharaoh : text_center({ pos[220, 361], size[144, 20], align:"center", text[294, 41], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true })
        hdr_cleopatra : text_center({ pos[352, 361], size[144, 20], align:"center", text[294, 42], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true })

        camp_0 : large_button({ pos[210, 261 + 120], size[144, 25], text[294, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(0), onhover: campaign_period_hover(0), onunhover: campaign_period_unhover })
        camp_1 : large_button({ pos[210, 291 + 120], size[144, 25], text[294, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(1), onhover: campaign_period_hover(1), onunhover: campaign_period_unhover })
        camp_2 : large_button({ pos[210, 321 + 120], size[144, 25], text[294, 8], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(2), onhover: campaign_period_hover(2), onunhover: campaign_period_unhover })
        camp_3 : large_button({ pos[210, 351 + 120], size[144, 25], text[294, 12], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(3), onhover: campaign_period_hover(3), onunhover: campaign_period_unhover })
        camp_4 : large_button({ pos[210, 381 + 120], size[144, 25], text[294, 16], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(4), onhover: campaign_period_hover(4), onunhover: campaign_period_unhover })
        camp_5 : large_button({ pos[362, 261 + 120], size[144, 25], text[294, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(5), onhover: campaign_period_hover(5), onunhover: campaign_period_unhover })
        camp_6 : large_button({ pos[362, 291 + 120], size[144, 25], text[294, 24], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(6), onhover: campaign_period_hover(6), onunhover: campaign_period_unhover })
        camp_7 : large_button({ pos[362, 321 + 120], size[144, 25], text[294, 28], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(7), onhover: campaign_period_hover(7), onunhover: campaign_period_unhover })
        camp_8 : large_button({ pos[362, 351 + 120], size[144, 25], text[294, 32], font:FONT_NORMAL_BLACK_ON_LIGHT, enabled:true, onclick: show_scenario_company(8), onhover: campaign_period_hover(8), onunhover: campaign_period_unhover })
    }
}
