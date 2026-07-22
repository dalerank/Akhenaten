log_info("akhenaten: ui bazaar orders window started")

var bazaar_orders_all_goods = [
    RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE, RESOURCE_CHICKPEAS,
    RESOURCE_POMEGRANATES, RESOURCE_FIGS, RESOURCE_FISH, RESOURCE_GAMEMEAT,
    RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS
]

// set of resources this city can actually stock in the bazaar
var bazaar_orders_available_goods = {}

function bazaar_orders_good_available(resId) {
    return bazaar_orders_available_goods[resId] === true
}

function bazaar_orders_window_accept_none() {
    log_info("akhenaten: bazaar_orders_window_accept_none")
    city.get_bazaar(city.object_info.bid).unaccept_all_goods()
}

function bazaar_orders_list_on_click_item(p) {
    if (!bazaar_orders_good_available(p.user_data)) {
        return
    }
    city.get_bazaar(city.object_info.bid).toggle_res_accepted(p.user_data)
}

function bazaar_orders_list_on_render_item(p) {
    var resId = p.user_data
    if (resId === undefined || resId === RESOURCE_NONE) {
        return
    }
    var bazaar = city.get_bazaar(city.object_info.bid)
    var available = bazaar_orders_good_available(resId)

    if (available) {
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
    } else {
        // good not produced/imported in this city: grayed out, non-clickable
        ui.resource_icon_flags([p.x + 25, p.y + 2], resId, UiFlags_Grayscale)
        ui.resource_icon_flags([p.x + 25 + px(23), p.y + 2], resId, UiFlags_Grayscale)

        ui.label_ex(__loc(23, resId), [p.x + 85, p.y], FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignYCentered, 150)
    }
}

[es=modal_window]
bazaar_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(22)) / 2]
    draw_underlying: true
    allow_rmb_goback: true

    ui {
        background   : outer_panel({size[29, 22]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        goods_list   : scrollable_list({
            pos[16, 42]
            size[27, 16]
            view_items: 12
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

    bazaar_orders_available_goods = {}
    for (var availName in city.resources.available_market) {
        bazaar_orders_available_goods[city.resources.available_market[availName]] = true
    }

    window.goods_list.clear()
    for (var i = 0; i < bazaar_orders_all_goods.length; ++i) {
        var resId = bazaar_orders_all_goods[i]
        window.goods_list.add_item(__loc(23, resId), resId)
    }
}
