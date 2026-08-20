log_info("akhenaten: scenario selection — campaign periods")

function campaign_period_last_scenario_id(period) {
    var last_sid = -1
    var i
    for (i = 0; i < 64; i++) {
        var sid = __game_campaign_mission_step_scenario_id(period, i)
        if (sid < 0) {
            break
        }
        last_sid = sid
    }
    return last_sid
}

function campaign_period_is_unlocked(period) {
    if (game_features.gameopt_unlock_all_campaigns) {
        return true
    }
    if (period <= 0) {
        return true
    }
    var prev_last = campaign_period_last_scenario_id(period - 1)
    return prev_last >= 0 && !!__game_mission_scenario_beaten(prev_last)
}

[es=(window_scenario_selection_campaign, init)]
function window_scenario_selection_campaign_on_init(ev) {
    window_scenario_selection.campaign_first_mission = -1
    window_scenario_selection.campaign_sub_dialog = -1
    window_scenario_selection.individual_missions = false

    if (window_scenario_selection_campaign.period_selected < 0) {
        window_scenario_selection_campaign.period_selected = 0
    }
    // Prefer the highest unlocked period so returning players land on current progress.
    var best = 0
    var i
    for (i = 0; i < CAMPAIGN_PERIOD_COUNT; i++) {
        if (campaign_period_is_unlocked(i)) {
            best = i
        }
    }
    if (!campaign_period_is_unlocked(window_scenario_selection_campaign.period_selected)) {
        window_scenario_selection_campaign.period_selected = best
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
        var unlocked = campaign_period_is_unlocked(i)
        btn.enabled = campaigns
        btn.darkened = campaigns && !unlocked ? 1 : 0
        btn.selected = campaigns && (i === selected)
    }

    ev.campaign_hover_thumb.enabled = campaigns
    ev.campaign_hover_subtitle.enabled = campaigns
    ev.campaign_hover_body.enabled = campaigns
    var play_ok = campaigns && campaign_period_is_unlocked(selected)
    ev.btn_play.enabled = campaigns
    ev.btn_play.darkened = play_ok ? 0 : 1
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
    var thumb = get_image({ pack:PACK_UNLOADED, id:28, offset:h })
    ev.campaign_hover_thumb.image = thumb ? thumb.tid : -1
    ev.campaign_hover_subtitle.text = __loc(294, h * 4)
    if (campaign_period_is_unlocked(h)) {
        ev.campaign_hover_body.text = __loc(294, h * 4 + 2)
    } else {
        ev.campaign_hover_body.text = __loc(294, h * 4 + 3)
    }
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
    if (!campaign_period_is_unlocked(index)) {
        ui.show_ok(__loc(294, index * 4 + 3), __loc(294, index * 4))
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
        tab_individual : large_button({ pos[210, 370], size[144, 24], text[294, 38], font:FONT_NORMAL_BLACK_ON_LIGHT })
        tab_campaigns  : large_button({ pos[362, 370], size[144, 24], text[294, 39], font:FONT_NORMAL_BLACK_ON_LIGHT })

        // Original Explore History: Pharaoh section (2-col), then Cleopatra section (2-col) below.
        hdr_pharaoh : text({ pos[210, 420], size[144, 18], text[294, 41], font:FONT_NORMAL_BLACK_ON_LIGHT })
        camp_0 : large_button({ pos[210, 445], size[144, 25], text[294, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 0, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_1 : large_button({ pos[210, 475], size[144, 25], text[294, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 1, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_2 : large_button({ pos[362, 415], size[144, 25], text[294, 8], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 2, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_3 : large_button({ pos[362, 445], size[144, 25], text[294, 12], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 3, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_4 : large_button({ pos[362, 475], size[144, 25], text[294, 16], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 4, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })

        hdr_cleopatra : text({ pos[210, 515], size[144, 18], text[294, 42], font:FONT_NORMAL_BLACK_ON_LIGHT })
        camp_5 : large_button({ pos[210, 530], size[144, 25], text[294, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 5, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_6 : large_button({ pos[210, 560], size[144, 25], text[294, 24], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 6, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_7 : large_button({ pos[362, 530], size[144, 25], text[294, 28], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 7, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })
        camp_8 : large_button({ pos[362, 560], size[144, 25], text[294, 32], font:FONT_NORMAL_BLACK_ON_LIGHT, param1: 8, onclick_event: "select_period", onhover_event: "hover_period", onunhover_event: "unhover_period" })

        campaign_hover_subtitle : text_center({ pos[545, 208], size[265, 22], align:"center", font:FONT_LARGE_BLACK_ON_DARK })
        campaign_hover_body : text({ pos[545, 250], size[265, 200], wrap:px(16), font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, clip_area:true })

        // Exit / Play along the bottom edge of the dialog.
        btn_exit : image_button({ pos[215, 590], size[31, 20], pack:PACK_GENERAL, id:90, offset:8 })
        lbl_exit : text({ pos[250, 592], text[44, 217], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btn_exit_hit : button({ pos[215, 605], size[110, 30], text:"", hbody:false, border:false })

        lbl_play : text({ pos[735, 590], text[294, 37], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btn_play : image_button({ pos[780, 585], size[27, 27], pack:PACK_GENERAL, id:193, offset:4 })
    }
}

[es=(window_scenario_selection_campaign, select_period)]
function window_scenario_selection_campaign_on_select_period(window, ev) {
    campaign_period_set_selected(Math.round(ev.param1))
}

[es=(window_scenario_selection_campaign, hover_period)]
function window_scenario_selection_campaign_on_hover_period(window, ev) {
    window_scenario_selection_campaign.period_hover = Math.round(ev.param1)
    emit window_scenario_selection_campaign.period_changed { index: Math.round(ev.param1) }
}

[es=(window_scenario_selection_campaign, unhover_period)]
function window_scenario_selection_campaign_on_unhover_period(window) {
    window_scenario_selection_campaign.period_hover = -1
    emit window_scenario_selection_campaign.period_changed {
        index: window_scenario_selection_campaign.period_selected
    }
}

[es=(window_scenario_selection_campaign, tab_individual)]
function window_scenario_selection_campaign_on_tab_individual(window) {
    campaign_tab_individual()
}

[es=(window_scenario_selection_campaign, tab_campaigns)]
function window_scenario_selection_campaign_on_tab_campaigns(window) {
    campaign_tab_campaigns()
}

[es=(window_scenario_selection_campaign, btn_exit)]
function window_scenario_selection_campaign_on_btn_exit(window) {
    window_go_back()
}

[es=(window_scenario_selection_campaign, btn_exit_hit)]
function window_scenario_selection_campaign_on_btn_exit_hit(window) {
    window_go_back()
}

[es=(window_scenario_selection_campaign, btn_play)]
function window_scenario_selection_campaign_on_btn_play(window) {
    campaign_btn_play()
}
