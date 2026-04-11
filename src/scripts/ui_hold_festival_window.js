log_info("akhenaten: ui hold festival started")



hold_festival_window {
    pos [(sw(0) - px(34)) / 2, (sh(0) - px(20)) / 2],
    ui {
        background_image: background({pack:PACK_UNLOADED, id:11})
        background      : outer_panel({size[34, 20]})

        title           : text_center({pos[0, 20], size[px(34), -1], font : FONT_LARGE_BLACK_ON_LIGHT,
                                       text: "${loc.hold_festival_to} ${city.festival_selected_god_name}" })

        god0            : image_button({pos[100 * 0 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 0, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true })
        god1            : image_button({pos[100 * 1 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 1, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true })
        god2            : image_button({pos[100 * 2 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 2, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true })
        god3            : image_button({pos[100 * 3 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 3, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true })
        god4            : image_button({pos[100 * 4 + 30, 66], pack:PACK_UNLOADED, id:21, offset:16 + 4, offset_pressed:5, offset_focused:5, offset_disabled:0, border:true })
        small_festival  : button({margin{centerx:-215, bottom:-140 }, size[430, 26], rich:true})
        middle_festival : button({margin{centerx:-215, bottom:-110 }, size[430, 26], rich:true})
        large_festival  : button({margin{centerx:-215, bottom:-80 }, size[430, 26], rich:true})
        button_ok       : image_button({margin{centerx:20, bottom:-40 }, size[39, 26], pack:PACK_GENERAL, id:96, offset:0 })
        button_cancel   : image_button({margin{centerx:70, bottom:-40 }, size[39, 26], pack:PACK_GENERAL, id:96, offset:4 })
        festival_type   : text({margin{centerx:-115, bottom:-35 }, size[544, -1] })

        button_help     : image_button({margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:0 })
    }
}

[es=(hold_festival_window, init)]
function hold_festival_window_init(window) {
    window.background_image.enabled = __hold_festival_window_has_background()

    if (!city.gods.is_known(city.festival.selected_god)) {
        for (var god = 0; god < 5; god++) {
            if (city.gods.is_known(god)) {
                city.festival.select_god(god)
                break
            }
        }
    }

    var deben_tid = get_image({ pack: PACK_GENERAL, id: 103, offset: 18 }).tid
    var beer_tid = __image_id_resource_icon_int(RESOURCE_BEER)
    var broke = city.finance.is_out_of_money

    window.small_festival.text = __loc(58, 31) + " " + city.festival.small_cost + " @I" + deben_tid
    window.small_festival.darkened = broke
    window.small_festival.onclick = function() { city.festival.select_size(1) }

    window.middle_festival.text = __loc(58, 32) + " " + city.festival.large_cost + " @I" + deben_tid
    window.middle_festival.darkened = broke
    window.middle_festival.onclick = function() { city.festival.select_size(2) }

    window.large_festival.text = __loc(58, 32) + " " + city.festival.grand_cost + " @I" + deben_tid + " " + city.festival.grand_alcohol + "  @I" + beer_tid
    window.large_festival.darkened = broke || city.festival.not_enough_alcohol
    window.large_festival.onclick = function() { city.festival.select_size(3) }

    window.button_ok.onclick = function() { __hold_festival_window_ok() }
    window.button_cancel.onclick = function() { __hold_festival_window_cancel() }
    window.button_help.onclick = function() { ui.window_message_dialog_show("message_overseer_temples") }

    for (var god = 0; god < 5; god++) {
        var btn = window["god" + god]
        if (!city.gods.is_known(god)) {
            btn.darkened = UiFlags_Grayscale
            btn.readonly = true
        }
        ;(function(g, b) {
            b.onclick = function() { city.festival.select_god(g) }
        })(god, btn)
    }
}