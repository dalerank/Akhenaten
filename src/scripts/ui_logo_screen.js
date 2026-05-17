log_info("akhenaten: logo screen started")

[es=window]
window_logo {
    logo_tick: 0

    ui {
        background: background({ pack: PACK_UNLOADED, id: 7 })
        hint: text_center({ pos: [(sw(0) - px(320))/2, (sh(0) - px(20))/2 + 260], size: [px(320), px(20)], text: [13, 7], font: FONT_SMALL_PLAIN, color: 0xffffffff })
    }
}

[es=(window_logo, init)]
function window_logo_on_init(window) {
    window_logo.logo_tick = 0
    
    if (game.logo_show_patch_message === 2) { // MESSAGE_MISSING_FONTS
        __window_plain_message_dialog_show("#TR_MISSING_FONTS_TITLE", "#TR_MISSING_FONTS_MESSAGE")
    }
}

[es=(window_logo, ui_draw_foreground)]
function window_logo_ui_draw_foreground(window) {
    window_logo.logo_tick = window_logo.logo_tick + 1

    var c = Math.floor(128 + Math.cos(window_logo.logo_tick * 0.03) * 128)
    window.hint.color = (c << 24) + (c << 16) + (c << 8) + c

    if (__mouse.left.went_up || __mouse.right.went_up) {
        __game_show_main_menu_no_restart();
    }
}
