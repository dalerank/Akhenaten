log_info("akhenaten: ui popup dialog started")

// C++-owned autoconfig windows (popup_dialog instances). Not [es=modal_window] —
// shells are registered from C++; these sections are layout only.
window_popup_dialog_yesno {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(10))/2]
    draw_underlying: true
    ui {
        background : outer_panel({size: [30, 10] })
        header     : text({pos:[0, 30], size:[px(30), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        text       : text({pos:[0, 60], size:[px(30), 120], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"
                           multiline:true, wrap:px(30)})
        btn_yes    : image_button({margin:{centerx:-60, bottom:-60}, size:[39, 26], pack:PACK_GENERAL, id:96 })
        btn_no     : image_button({margin:{centerx:20, bottom:-60}, size:[39, 26], pack:PACK_GENERAL, id:96, offset:4 })
        label_tip  : text({margin:{left:20, bottom:-40}, font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})
    }
}

window_popup_dialog_ok {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(10))/2]
    draw_underlying: true
    ui {
        background : outer_panel({size[30, 10] })
        header     : text({pos[0, 30], size[px(30), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        text       : text({pos[0, 60], size[px(30), 120], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"
                           multiline:true, wrap:px(30)})
        btn_yes    : image_button({margin{centerx:-20, bottom:-60}, size[39, 26], pack:PACK_GENERAL, id:96 })
        btn_no     : dummy({pos[0, 0], size[1, 1], enabled: false})
        btn_close  : image_button({margin{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4 })
        label_tip  : text({margin{bottom:-40}, align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT})
    }
}
