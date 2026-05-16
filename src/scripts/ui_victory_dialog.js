log_info("akhenaten: ui victory dialog started")

function victory_dialog_btn_accept() {
    ui.window_city_show()
}

function victory_dialog_continue(months) {
    __scenario_victory_continue_governing(months)
    ui.window_city_show()
    __scenario_victory_reset()
    __game_sound.music_update(1)
}

function victory_dialog_continue_2() {
    victory_dialog_continue(24)
}

function victory_dialog_continue_5() {
    victory_dialog_continue(60)
}

[es=(window_victory_dialog, init)]
function window_victory_dialog_on_init(window) {
    var rank = __scenario_settings.campaign_mission_rank
    var is_custom = scenario.scmode != e_scenario_normal
    var won = __scenario_victory.state == 1
    var next_scenario = rank + 1
    var early_campaign = rank < 10 || is_custom
    var show_continue = rank >= 2 || is_custom

    window.title_early.enabled = won && early_campaign
    window.subtitle_early.enabled = won && early_campaign
    window.next_mission.enabled = won && early_campaign
    window.title_campaign_end.enabled = won && !early_campaign
    window.desc_campaign_end.enabled = won && !early_campaign

    window.btn_accept.enabled = won
    window.btn_continue_2.enabled = won && show_continue
    window.btn_continue_5.enabled = won && show_continue
    window.btn_lost.enabled = !won

    if (won && early_campaign) {
        window.next_mission.text = __loc(32, next_scenario)
    } else if (won && !early_campaign) {
        window.title_campaign_end.text = player.name
    }

    if (won) {
        window.btn_accept.text = early_campaign ? __loc(62, 3) : __loc(62, 27)
    }
}

[es=window]
window_victory_dialog {
    pos:  [(sw(0) - px(34))/2, (sh(0) - px(15))/2]
    draw_underlying: true

    ui {
        background           : outer_panel({size: [34, 15]})
        title_early          : text_center({pos: [0, 16], size: [px(34), 20], text: [62, 0], font: FONT_LARGE_BLACK_ON_LIGHT, enabled: false})
        subtitle_early       : text_center({pos: [0, 47], size: [px(34), 20], text: [62, 2], font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})
        next_mission         : text_center({pos: [0, 66], size: [px(34), 20], text: "", font: FONT_LARGE_BLACK_ON_LIGHT, enabled: false})
        title_campaign_end   : text_center({pos: [0, 16], size: [px(32), 20], text: "", font: FONT_LARGE_BLACK_ON_LIGHT, enabled: false})
        desc_campaign_end    : multiline({pos: [16, 47], size: [480, 120], text: [62, 26], font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})

        btn_accept           : large_button({pos: [32, 112], size: [480, 20], text: [62, 3], font: FONT_NORMAL_BLACK_ON_DARK, enabled: false, onclick: victory_dialog_btn_accept})
        btn_continue_2       : large_button({pos: [32, 144], size: [480, 20], text: [62, 4], font: FONT_NORMAL_BLACK_ON_DARK, enabled: false, onclick: victory_dialog_continue_2})
        btn_continue_5       : large_button({pos: [32, 176], size: [480, 20], text: [62, 5], font: FONT_NORMAL_BLACK_ON_DARK, enabled: false, onclick: victory_dialog_continue_5})
        btn_lost             : large_button({pos: [32, 96], size: [480, 20], text: [62, 6], font: FONT_NORMAL_BLACK_ON_DARK, enabled: false, onclick: victory_dialog_btn_accept})
    }
}
