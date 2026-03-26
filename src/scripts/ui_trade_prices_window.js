log_info("akhenaten: ui trade prices window started")

function trade_prices_vec_add(a, b) {
    return [a[0] + b[0], a[1] + b[1]]
}

[es=modal_window]
trade_prices_window {
    pos: [(sw(0) - px(56))/2, (sh(0) - px(11))/2]
    draw_underlying: true
    next_row_offset : [0, 90]
    next_item_offset : [42, 0]
    receive_offset : [0, 50]
    buyer_offset : [0, 30]
    next : 18
    allow_rmb_goback : true

    ui {
        background       : outer_panel({pos:[0, 0], size:[56, 16]})
        title            : text_center({pos:[0, 12], size:[px(56), 20], text:[54, 21], font : FONT_LARGE_BLACK_ON_LIGHT })

        items            : dummy({pos:[156, 44]})
        item_button      : dummy({pos:[-7, -7], size:[38, 74]})

        buyers_pay1      : text({text:[54, 23], pos:[26, 72], font: FONT_NORMAL_BLACK_ON_LIGHT})
        sellers_receive1 : text({text:[54, 22], pos:[26, 92], font:FONT_NORMAL_BLACK_ON_LIGHT})

        buyers_pay2      : text({text:[54, 23], pos:[26, 162], font: FONT_NORMAL_BLACK_ON_LIGHT})
        sellers_receive2 : text({text:[54, 22], pos:[26, 182], font:FONT_NORMAL_BLACK_ON_LIGHT})

        back             : label({margin:{bottom:-35}, size:[px(56), 20], align:"center", text:[13, 1], font:FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

[es=(trade_prices_window, ui_draw_foreground)]
function trade_prices_window_ui_draw_foreground(window) {
    var items_base = [156, 44]
    var item_button_pos = [-7, -7]
    var item_button_size = [38, 74]
    var next_row_offset = [0, 90]
    var next_item_offset = [42, 0]
    var receive_offset = [0, 50]
    var buyer_offset = [0, 30]
    var next = 18

    var start_i = 0
    var items_pos = items_base.slice()
    var current_pos = items_base.slice()

    for (var i = RESOURCE_GRAIN; (start_i + i) < RESOURCE_DEBEN; i++) {
        if (i >= next) {
            start_i += next
            i = RESOURCE_NONE
            items_pos = trade_prices_vec_add(items_pos, next_row_offset)
            current_pos = items_pos.slice()
        }

        var resource = start_i + i
        if (resource === RESOURCE_UNUSED12) {
            continue
        }

        ui.resource_icon(current_pos, resource)

        var btn_pos = trade_prices_vec_add(current_pos, item_button_pos)
        ui.button({ text: "", pos: btn_pos, size: item_button_size, font: FONT_NORMAL_BLACK_ON_LIGHT, body: false, tooltip: __loc(23, resource) })

        var res_name = city.resources.get_name(resource)
        var res = city.resources[res_name]
        ui.label(String(res.price_buy), trade_prices_vec_add(current_pos, buyer_offset), FONT_NORMAL_BLACK_ON_LIGHT)
        ui.label(String(res.price_sell), trade_prices_vec_add(current_pos, receive_offset), FONT_NORMAL_BLACK_ON_LIGHT)

        current_pos = trade_prices_vec_add(current_pos, next_item_offset)
    }
}

[es=(trade_prices_window, go_back)]
function trade_prices_window_go_back(window) {
    window_go_back()
}


