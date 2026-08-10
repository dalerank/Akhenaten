log_info("akhenaten: scenario selection — campaign periods")

[es=(window_scenario_selection_campaign, init)]
function window_scenario_selection_campaign_on_init(ev) {
    window_scenario_selection.campaign_first_mission = -1
    window_scenario_selection.campaign_sub_dialog = -1
    window_scenario_selection.individual_missions = false

    if (window_scenario_selection_campaign.period_selected < 0) {
        window_scenario_selection_campaign.period_selected = 0
    }
    window_scenario_selection_campaign.period_hover = -1
    window_scenario_selection_campaign.active_tab = CAMPAIGN_TAB_CAMPAIGNS

    campaign_period_refresh_ui(ev)
    emit window_scenario_selection_campaign.period_changed { index: window_scenario_selection_campaign.period_selected }
}

function campaign_period_active_index() {
    var h = window_scenario_selection_campaign.period_hover
    if (h >= 0) {
        return h
    }
    return window_scenario_selection_campaign.period_selected
}

function campaign_period_set_selected(index) {
    window_scenario_selection_campaign.period_selected = index
    emit window_scenario_selection_campaign.period_changed { index: index }
}

function campaign_period_select(index) {
    return function() {
        campaign_period_set_selected(index)
    }
}

function campaign_period_hover(index) {
    return function() {
        window_scenario_selection_campaign.period_hover = index
        emit window_scenario_selection_campaign.period_changed { index: index }
    }
}

function campaign_period_unhover() {
    window_scenario_selection_campaign.period_hover = -1
    emit window_scenario_selection_campaign.period_changed {
        index: window_scenario_selection_campaign.period_selected
    }
}

function campaign_period_refresh_ui(ev) {
    var tab = window_scenario_selection_campaign.active_tab
    var campaigns = (tab === CAMPAIGN_TAB_CAMPAIGNS)
    var selected = window_scenario_selection_campaign.period_selected

    ev.tab_individual.selected = (tab === CAMPAIGN_TAB_INDIVIDUAL)
    ev.tab_campaigns.selected = campaigns

    ev.hdr_pharaoh.enabled = campaigns
    ev.hdr_cleopatra.enabled = campaigns
    for (var i = 0; i < CAMPAIGN_PERIOD_COUNT; i++) {
        var btn = ev["camp_" + i]
        btn.enabled = campaigns
        btn.selected = campaigns && (i === selected)
    }

    ev.campaign_hover_thumb.enabled = campaigns
    ev.campaign_hover_subtitle.enabled = campaigns
    ev.campaign_hover_body.enabled = campaigns
    ev.btn_play.enabled = campaigns
    ev.lbl_play.enabled = campaigns
}

[es=(window_scenario_selection_campaign, period_changed)]
function window_scenario_selection_campaign_on_period_changed(ev) {
    campaign_period_refresh_ui(ev)

    if (window_scenario_selection_campaign.active_tab !== CAMPAIGN_TAB_CAMPAIGNS) {
        return
    }

    var h = campaign_period_active_index()
    if (h < 0) {
        ev.campaign_hover_thumb.image = -1
        ev.campaign_hover_subtitle.text = ""
        ev.campaign_hover_body.text = ""
        return
    }

    // Loc group 294 packs each period as title / short blurb / family narrative / locked.
    // Explore History shows the family narrative (offset +2), matching original Pharaoh.
    var thumb = get_image({ pack:PACK_UNLOADED, id:28, offset:h })
    ev.campaign_hover_thumb.image = thumb ? thumb.tid : -1
    ev.campaign_hover_subtitle.text = __loc(294, h * 4)
    ev.campaign_hover_body.text = __loc(294, h * 4 + 2)
}

function campaign_tab_campaigns() {
    window_scenario_selection_campaign.active_tab = CAMPAIGN_TAB_CAMPAIGNS
    emit window_scenario_selection_campaign.period_changed {
        index: window_scenario_selection_campaign.period_selected
    }
}

function campaign_tab_individual() {
    window_scenario_selection_campaign.active_tab = CAMPAIGN_TAB_INDIVIDUAL
    window_scenario_selection.individual_missions = true
    window_scenario_selection.campaign_sub_dialog = -1
    window_show_by_id("window_scenario_selection")
}

function campaign_btn_play() {
    var index = window_scenario_selection_campaign.period_selected
    if (index < 0) {
        return
    }
    window_scenario_selection.individual_missions = false
    window_scenario_selection.campaign_sub_dialog = index
    window_show_by_id("window_scenario_selection")
}

[es=window]
window_scenario_selection_campaign {
    period_hover : -1
    period_selected : 0
    active_tab : 0
    allow_rmb_goback : true

    pos [(sw(0) - 1024) / 2, (sh(0) - 768) / 2]
    ui {
        background : dummy({ size[64, 48] })

        img_history : image({ pos[0, 0], pack:PACK_UNLOADED, id:33, offset:0 })

        campaign_hover_thumb : image_queue({ pos[270, 200], size[256, 152], fit:true, fade_ms:280, pack:PACK_UNLOADED, id:28, offset:0 })

        // Button block below portrait (thumb bottom ~352), with clear gap under the frame.
        tab_individual : large_button({ pos[210, 370], size[144, 24], text[294, 38], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_tab_individual })
        tab_campaigns  : large_button({ pos[362, 370], size[144, 24], text[294, 39], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_tab_campaigns })

        // Original Explore History: Pharaoh section (2-col), then Cleopatra section (2-col) below.
        hdr_pharaoh : text({ pos[210, 420], size[144, 18], text[294, 41], font:FONT_NORMAL_BLACK_ON_LIGHT })
        camp_0 : large_button({ pos[210, 445], size[144, 25], text[294, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(0), onhover: campaign_period_hover(0), onunhover: campaign_period_unhover })
        camp_1 : large_button({ pos[210, 475], size[144, 25], text[294, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(1), onhover: campaign_period_hover(1), onunhover: campaign_period_unhover })
        camp_2 : large_button({ pos[362, 415], size[144, 25], text[294, 8], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(2), onhover: campaign_period_hover(2), onunhover: campaign_period_unhover })
        camp_3 : large_button({ pos[362, 445], size[144, 25], text[294, 12], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(3), onhover: campaign_period_hover(3), onunhover: campaign_period_unhover })
        camp_4 : large_button({ pos[362, 475], size[144, 25], text[294, 16], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(4), onhover: campaign_period_hover(4), onunhover: campaign_period_unhover })

        hdr_cleopatra : text({ pos[210, 515], size[144, 18], text[294, 42], font:FONT_NORMAL_BLACK_ON_LIGHT })
        camp_5 : large_button({ pos[210, 530], size[144, 25], text[294, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(5), onhover: campaign_period_hover(5), onunhover: campaign_period_unhover })
        camp_6 : large_button({ pos[210, 560], size[144, 25], text[294, 24], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(6), onhover: campaign_period_hover(6), onunhover: campaign_period_unhover })
        camp_7 : large_button({ pos[362, 530], size[144, 25], text[294, 28], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(7), onhover: campaign_period_hover(7), onunhover: campaign_period_unhover })
        camp_8 : large_button({ pos[362, 560], size[144, 25], text[294, 32], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: campaign_period_select(8), onhover: campaign_period_hover(8), onunhover: campaign_period_unhover })

        campaign_hover_subtitle : text_center({ pos[545, 208], size[265, 22], align:"center", font:FONT_LARGE_BLACK_ON_DARK })
        campaign_hover_body : text({ pos[545, 250], size[265, 200], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })

        // Exit / Play along the bottom edge of the dialog.
        btn_exit : image_button({ pos[215, 590], size[31, 20], pack:PACK_GENERAL, id:90, offset:8, onclick: window_go_back })
        lbl_exit : text({ pos[250, 592], text[44, 217], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btn_exit_hit : button({ pos[215, 605], size[110, 30], text:"", hbody:false, border:false, onclick: window_go_back })

        lbl_play : text({ pos[735, 590], text[294, 37], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btn_play : image_button({ pos[780, 585], size[27, 27], pack:PACK_GENERAL, id:193, offset:4, onclick: campaign_btn_play })
    }
}
