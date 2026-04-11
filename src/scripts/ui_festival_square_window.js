log_info("akhenaten: ui festival square window started")

function festival_square_info_update_festival_state(window) {
    var festivalTextIffs = [0, 10, 20, 31]

    if (__city_festival_is_planned()) {
        var size = __city_festival_selected_size()
        var monthsLeft = __city_festival_months_till_next()
        var plannedMonth = (__game_simtime_month() + monthsLeft) % 12
        var baseIdx = (size >= 0 && size < festivalTextIffs.length) ? festivalTextIffs[size] : festivalTextIffs[festivalTextIffs.length - 1]

        window.hold_festival.enabled = false
        window.planed_festival.text = __loc(58, 34) + " " + __loc(160, plannedMonth)
        window.festival_advice.text = __loc(295, baseIdx + monthsLeft - 1)
        return
    }

    window.planed_festival.text = ""
    window.hold_festival.enabled = true
    window.hold_festival.text = __loc(58, 16)
    window.festival_advice.text = __loc(58, 18 + __city_festival_get_advice())
}

[es=building_info_window]
festival_square_info_window {
    related_buildings [BUILDING_FESTIVAL_SQUARE]
    ui {
        background      : outer_panel({pos[0, 0], size[29, 16]}),
        title           : text({text: "#festival_square_info_title", pos[0, 10], size[px(29), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning         : text({pos[32, 36], wrap:px(26), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        workers_panel   : inner_panel({ pos[16, 96], size[27, 7] }),
        fest_months_last: text({pos[32, 112], size[px(25), 20], text:"${city.months_since_festival} ${8.5} ${58.15}", font:FONT_NORMAL_WHITE_ON_DARK, align:"center"}),
        hold_festival   : button({pos[60, 134], size:[px(22), 25], font:FONT_NORMAL_WHITE_ON_DARK, text:"${58.16}"}),
        planed_festival : text({pos[102, 134], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" }),
        festival_advice : text({pos[36, 164], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true }),

        button_help     : help_button({}),
        button_close    : close_button({}),
    }
}

[es=(festival_square_info_window, init)]
function festival_square_info_window_init(window) {
    window.hold_festival.onclick = function() {
        if (__city_festival_is_planned()) {
            return
        }
        __hold_festival_window_show(false, function() {
            festival_square_info_update_festival_state(window)
        })
    }
    festival_square_info_update_festival_state(window)
}
