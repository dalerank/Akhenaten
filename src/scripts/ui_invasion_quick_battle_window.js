log_info("akhenaten: ui invasion quick battle window started")

function invasion_quick_battle_bribe_feature_on() {
    return game_features.get('gameplay_enhanced_invasion_bribe') === true
}

function invasion_quick_battle_bribe_text() {
    if (!invasion_quick_battle_bribe_feature_on() || __invasion_bribe_allowed(0) != 1) {
        return ""
    }
    var cost = __invasion_bribe_cost(0)
    var tre = city.finance.treasury
    return __loc("#invasion_bribe_cost_line")
        .replace("{cost}", "" + cost)
        .replace("{treasury}", "" + tre)
}

function invasion_quick_battle_strength_text() {
    var p = __invasion_auto_resolve_player_strength()
    var e = __invasion_auto_resolve_enemy_strength()
    return __loc("#invasion_quick_battle_strength")
        .replace("{player}", "" + p)
        .replace("{enemy}", "" + e)
}

function invasion_quick_battle_days_text() {
    var d = __invasion_auto_resolve_head_days_left()
    if (d < 0) {
        return __loc("#invasion_quick_battle_none")
    }
    var n = __invasion_auto_resolve_pending_count()
    var id = __invasion_auto_resolve_head_invasion_id()
    var base = __loc("#invasion_quick_battle_days").replace("{days}", "" + d)
    var head = __loc("#invasion_quick_battle_head")
        .replace("{id}", "" + id)
        .replace("{i}", "1")
        .replace("{n}", "" + n)
    return base + "  " + head
}

[es=(invasion_quick_battle_window, init)]
function invasion_quick_battle_window_init(window) {
    window.btn_bribe.enabled = invasion_quick_battle_bribe_feature_on()
}

[es=modal_window]
invasion_quick_battle_window {
    pos [(sw(0) - px(30)) / 2, (sh(0) - px(14)) / 2]
    allow_rmb_goback : true
    draw_underlying : true

    ui {
        background_image : background({pack:PACK_UNLOADED, id:11})
        background       : outer_panel({size[30, 14]})
        title            : text_center({pos[16, 16], size[px(30) - 32, 20],
                                        text: "#invasion_quick_battle_title",
                                        font: FONT_LARGE_BLACK_ON_LIGHT})

        strength_label   : label({pos[32, 56], font: FONT_NORMAL_BLACK_ON_LIGHT
                                  textfn: invasion_quick_battle_strength_text})
        days_label       : label({pos[32, 80], font: FONT_NORMAL_BLACK_ON_LIGHT
                                  textfn: invasion_quick_battle_days_text})
        hint_label       : text({pos[32, 108], size[px(30) - 64, 40],
                                 text: "#invasion_quick_battle_hint",
                                 font: FONT_NORMAL_BLACK_ON_LIGHT})
        bribe_label      : label({pos[32, 148], font: FONT_NORMAL_BLACK_ON_LIGHT
                                  textfn: invasion_quick_battle_bribe_text})

        btn_resolve      : button({pos[40, 180], size[140, 24],
                                   text: "#invasion_quick_battle_resolve",
                                   font: FONT_NORMAL_BLACK_ON_LIGHT})
        btn_bribe        : button({pos[190, 180], size[140, 24],
                                   text: "#invasion_bribe_button",
                                   font: FONT_NORMAL_BLACK_ON_LIGHT})
        btn_wait         : button({pos[340, 180], size[120, 24],
                                   text: "#invasion_quick_battle_wait",
                                   font: FONT_NORMAL_BLACK_ON_LIGHT})
    }
}

[es=(invasion_quick_battle_window, btn_resolve)]
function invasion_quick_battle_window_on_resolve(window) {
    __invasion_auto_resolve_try_now()
    // C++ already opens the next head window or closes this one — do not yank the queue UI.
    if (__invasion_auto_resolve_pending_count() == 0) {
        ui.window_city_show()
    }
}

[es=(invasion_quick_battle_window, btn_bribe)]
function invasion_quick_battle_window_on_bribe(window) {
    if (!invasion_quick_battle_bribe_feature_on()) {
        return
    }
    // seq 0 = auto-resolve queue head only (same as cost/allowed display).
    if (__invasion_bribe_allowed(0) != 1) {
        return
    }
    var cost = __invasion_bribe_cost(0)
    if (cost <= 0 || city.finance.treasury < cost) {
        return
    }
    if (__invasion_bribe_try(0) == 1) {
        if (__invasion_auto_resolve_pending_count() == 0) {
            ui.window_city_show()
        }
    }
}

[es=(invasion_quick_battle_window, btn_wait)]
function invasion_quick_battle_window_on_wait(window) {
    ui.window_city_show()
}
