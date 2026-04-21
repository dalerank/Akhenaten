log_info("akhenaten: ui bazaar orders window started")

function bazaar_orders_window_accept_none() {
    log_info("akhenaten: bazaar_orders_window_accept_none")
    city.get_bazaar(city.object_info.bid).unaccept_all_goods()
}

function bazaar_orders_list_on_click_item(p) {
    city.get_bazaar(city.object_info.bid).toggle_res_accepted(p.user_data)
}

function bazaar_orders_list_on_render_item(p) {
    var resId = p.user_data
    if (resId === undefined || resId === RESOURCE_NONE) {
        return
    }
    var bazaar = city.get_bazaar(city.object_info.bid)

    ui.resource_icon([p.x + 25, p.y + 2], resId)
    ui.resource_icon([p.x + 25 + px(23), p.y + 2], resId)

    ui.label_ex(__loc(23, resId), [p.x + 85, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, 150)

    var accepted = bazaar.res_accepted(resId)
    var orderText = accepted ? __loc(97, 8) : __loc(97, 9)
    var orderFont = accepted ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_BLACK_ON_DARK
    ui.label_ex(orderText, [p.x + p.sizex - 132, p.y], orderFont, UiFlags_AlignYCentered, 120)

    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 2}, {x: p.sizex - 8, y: p.sizey + 2}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=modal_window]
bazaar_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(17)) / 2]
    draw_underlying: true
    allow_rmb_goback: true

    ui {
        background   : outer_panel({size[29, 17]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        goods_list   : scrollable_list({
            pos[16, 42]
            size[27, 11]
            view_items: 8
            buttons_size_y: 20
            buttons_margin_x: 0
            buttons_margin_y: 5
            text_padding_x: 0
            text_padding_y: 0
            draw_scrollbar_always: false
            draw_paneling: true
            onrender_item: bazaar_orders_list_on_render_item
            onclick_item: bazaar_orders_list_on_click_item
        })
        accept_none  : button({pos[80, -1], size[300, 24], text:{group:99, id:7}, margin{bottom:-38}, onclick: bazaar_orders_window_accept_none })

        button_help   : help_button({})
        button_close  : close_button({ onclick: window_go_back })
    }
}

[es=(bazaar_orders_window, init)]
function bazaar_orders_window_init(window) {
    ui.set_window_pos("bazaar_orders_window", city.object_info.offset)

    window.goods_list.clear()
    for (var name in city.resources.available_market) {
        var resId = city.resources.available_market[name]
        window.goods_list.add_item(name, resId)
    }
}
