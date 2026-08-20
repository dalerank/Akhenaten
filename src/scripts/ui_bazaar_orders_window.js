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

function bazaar_orders_variety_enabled() {
    return !!game_features.get("gameplay_enhanced_food_mill")
}

function bazaar_orders_cycle_desired() {
    if (!bazaar_orders_variety_enabled()) {
        return
    }
    var bazaar = city.get_bazaar(city.object_info.bid)
    var next = bazaar.desired_variety() + 1
    if (next > 4) {
        next = 1
    }
    bazaar.set_desired_variety(next)
}

function bazaar_orders_cycle_min() {
    if (!bazaar_orders_variety_enabled()) {
        return
    }
    var bazaar = city.get_bazaar(city.object_info.bid)
    var next = bazaar.min_variety() + 1
    if (next > bazaar.desired_variety()) {
        next = 1
    }
    bazaar.set_min_variety(next)
}

function bazaar_orders_text_desired() {
    if (!bazaar_orders_variety_enabled()) {
        return ""
    }
    var bazaar = city.get_bazaar(city.object_info.bid)
    return __loc("#bazaar_desired_variety") + " " + bazaar.desired_variety()
}

function bazaar_orders_text_min() {
    if (!bazaar_orders_variety_enabled()) {
        return ""
    }
    var bazaar = city.get_bazaar(city.object_info.bid)
    return __loc("#bazaar_min_variety") + " " + bazaar.min_variety()
}

[es=(bazaar_orders_window, click_item)]
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
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(24)) / 2]
    draw_underlying: true
    allow_rmb_goback: true

    ui {
        background   : outer_panel({size[29, 24]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        goods_list   : scrollable_list({
            pos[16, 42]
            size[27, 14]
            view_items: 10
            buttons_size_y: 20
            buttons_margin_x: 0
            buttons_margin_y: 5
            text_padding_x: 0
            text_padding_y: 0
            draw_scrollbar_always: false
            draw_paneling: true
            onrender_item: bazaar_orders_list_on_render_item
            onclick_event: "click_item"
        })
        desired_btn  : button({pos[16, -1], size[200, 24], textfn: bazaar_orders_text_desired, margin{bottom:-64}})
        min_btn      : button({pos[226, -1], size[200, 24], textfn: bazaar_orders_text_min, margin{bottom:-64}})
        accept_none  : button({pos[80, -1], size[300, 24], text:{group:99, id:7}, margin{bottom:-38}})

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

[es=(bazaar_orders_window, desired_btn)]
function bazaar_orders_window_on_desired_btn(window) {
    bazaar_orders_cycle_desired()
}

[es=(bazaar_orders_window, min_btn)]
function bazaar_orders_window_on_min_btn(window) {
    bazaar_orders_cycle_min()
}

[es=(bazaar_orders_window, accept_none)]
function bazaar_orders_window_on_accept_none(window) {
    bazaar_orders_window_accept_none()
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

    var show_variety = bazaar_orders_variety_enabled()
    window.desired_btn.enabled = show_variety
    window.min_btn.enabled = show_variety
}
