log_info("akhenaten: report bug window started")

[es=window]
report_bug_window {
    pos: [(sw(0) - px(32)) / 2, (sh(0) - px(20)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    sending: false

    ui {
        background: outer_panel({ size: [32, 20] })
        title: text({ pos:[0, 14], size:[px(32), 22], align:"center", font:FONT_LARGE_BLACK_ON_LIGHT, text:"Report Bug" })

        lbl_title: text({ pos:[16, 44], font:FONT_NORMAL_WHITE_ON_DARK, text:"Title" })
        bug_title: input({ pos:[16, 60], size:[30, 2], font:FONT_NORMAL_WHITE_ON_DARK, max_length:120 })

        lbl_body: text({ pos:[16, 95], font:FONT_NORMAL_WHITE_ON_DARK, text:"Description" })
        bug_body: input({ pos:[16, 116], size:[30, 10], font:FONT_NORMAL_WHITE_ON_DARK, max_length:2000, multiline:true })

        status: text({ margin:{bottom:-67}, size:[px(32), 22], align:"center", font:FONT_NORMAL_WHITE_ON_DARK, text:"" })

        lb_submit: label({ margin:{centerx:-70, bottom:-35}, text:"Submit?"})
        btn_submit: ok_button({ margin:{centerx:0, bottom:-40}, text:"", onclick_event:"on_submit" })
        btn_cancel: cancel_button({ margin:{centerx:50, bottom:-40}, onclick: window_go_back })
    }
}

[es=(report_bug_window, on_submit)]
function report_bug_on_submit(window) {
    var t = window.bug_title.value
    var b = window.bug_body.value
    if (!t || t.length === 0) {
        window.status.text = "Please enter a title."
        return
    }
    if (!b || b.length < 10) {
        window.status.text = "Please write a description (at least 10 characters)."
        return
    }
    window.status.text = "Sending..."
    window.btn_submit.enabled = false
    report_bug_window.sending = true
    __game_report_bug(t, b)
}

[es=(report_bug_window, event_report_bug_result)]
function report_bug_on_result(window, ev) {
    report_bug_window.sending = false
    window.btn_submit.enabled = true
    if (ev.ok) {
        window.status.text = "Reported! Thank you."
        window.bug_title.value = ""
        window.bug_body.value = ""
    } else {
        window.status.text = "Error: " + ev.error
    }
}
