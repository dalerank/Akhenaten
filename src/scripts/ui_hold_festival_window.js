log_info("akhenaten: ui hold festival started")

[es=window]
hold_festival_window {
    pos [(sw(0) - px(34)) / 2, (sh(0) - px(20)) / 2]
    needs_sync : true
    allow_rmb_goback : true
    draw_underlying: true
    on_close_cb : null

    ui {
        background_image: background({pack:PACK_UNLOADED, id:11})
        background      : outer_panel({size[34, 20]})

        title           : text_center({pos[0, 20], size[px(34), -1], font : FONT_LARGE_BLACK_ON_LIGHT })

        god0            : image_button({pos[100 * 0 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 0, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true, onclick_event: "festival_select_god_0"})
        god1            : image_button({pos[100 * 1 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 1, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true, onclick_event: "festival_select_god_1"})
        god2            : image_button({pos[100 * 2 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 2, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true, onclick_event: "festival_select_god_2"})
        god3            : image_button({pos[100 * 3 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 3, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true, onclick_event: "festival_select_god_3"})
        god4            : image_button({pos[100 * 4 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 4, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true, onclick_event: "festival_select_god_4"})
        small_festival  : button({margin{centerx:-215, bottom:-140 }, size[430, 26], rich:true, onclick_event: "festival_select_small"})
        middle_festival : button({margin{centerx:-215, bottom:-110 }, size[430, 26], rich:true, onclick_event: "festival_select_middle"})
        large_festival  : button({margin{centerx:-215, bottom:-80 }, size[430, 26], rich:true, onclick_event: "festival_select_grand"})
        button_ok       : image_button({margin{centerx:20, bottom:-40 }, size[39, 26], pack:PACK_GENERAL, id:96, offset:0, onclick_event: "festival_schedule_ok"})
        button_cancel   : image_button({margin{centerx:70, bottom:-40 }, size[39, 26], pack:PACK_GENERAL, id:96, offset:4, onclick: window_go_back })
        festival_type   : text({margin{centerx:-115, bottom:-35 }, size[544, -1] })

        button_help     : image_button({margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:0 })
    }
}

hold_festival_window.show = function(with_background, on_close_cb) {
    hold_festival_window.on_close_cb = on_close_cb
    emit event_show_window{ id:"hold_festival_window" }
}

[es=(hold_festival_window, init)]
function hold_festival_window_init(window) {
    window.background_image.enabled = false

    city.festival.calculate_costs()

    var deben_tid = get_image({ pack: PACK_GENERAL, id: 103, offset: 18 }).tid
    var beer_tid = __image_id_resource_icon_int(RESOURCE_BEER)
    var is_out_of_money = city.finance.is_out_of_money

    window.small_festival.text = __loc(58, 31) + " " + city.festival.small_cost + " @I" + deben_tid
    window.small_festival.darkened = is_out_of_money

    window.middle_festival.text = __loc(58, 32) + " " + city.festival.large_cost + " @I" + deben_tid
    window.middle_festival.darkened = is_out_of_money

    window.large_festival.text = __loc(58, 32) + " " + city.festival.grand_cost + " @I" + deben_tid + " " + city.festival.grand_alcohol + "  @I" + beer_tid
    window.large_festival.darkened = is_out_of_money || city.festival.not_enough_alcohol
    window.button_help.onclick = function() { ui.window_message_dialog_show("message_overseer_temples") }

    window.needs_sync = true
}

[es=(hold_festival_window, init)]
function hold_festival_window_setup_god_buttons(window) {
    for (var god = 0; god < 5; god++) {
        var btn = window["god" + god]
        if (!city.gods.is_known(god)) {
            btn.darkened = UiFlags_Grayscale
            btn.readonly = true
        }
    }
}

[es=(hold_festival_window, festival_schedule_ok)]
function hold_festival_window_festival_schedule_ok(ev) {
    if (!city.finance.is_out_of_money) {
        city.festival.schedule()
    }
    if (hold_festival_window.on_close_cb) {
        hold_festival_window.on_close_cb()
    }
    window_go_back()
}

[es=(hold_festival_window, festival_select_god_0)]
function hold_festival_window_festival_select_god_0(ev) {
    city.festival.select_god(0)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_god_1)]
function hold_festival_window_festival_select_god_1(ev) {
    city.festival.select_god(1)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_god_2)]
function hold_festival_window_festival_select_god_2(ev) {
    city.festival.select_god(2)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_god_3)]
function hold_festival_window_festival_select_god_3(ev) {
    city.festival.select_god(3)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_god_4)]
function hold_festival_window_festival_select_god_4(ev) {
    city.festival.select_god(4)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_small)]
function hold_festival_window_festival_select_small(ev) {
    city.festival.select_size(1)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_middle)]
function hold_festival_window_festival_select_middle(ev) {
    city.festival.select_size(2)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, festival_select_grand)]
function hold_festival_window_festival_select_grand(ev) {
    city.festival.select_size(3)
    hold_festival_window.needs_sync = true
}

[es=(hold_festival_window, draw_background)]
function hold_festival_window_draw_background(window) {
    if (!hold_festival_window.needs_sync) {
        return
    }
    for (var god = 0; god < 5; god++) {
        var btn = window["god" + god]
        if (!city.gods.is_known(god)) {
            btn.selected = false
            continue
        }
        btn.selected = (god === city.festival.selected_god)
    }

    var short_name = city.gods.get_name(city.festival.selected_god)
    window.title.text = "${loc.hold_festival_to} " + __loc("#" + short_name.toLowerCase())
    window.festival_type.text = __loc(58, 30 + city.festival.selected_size)
    hold_festival_window.needs_sync = false
}