log_info("akhenaten: ui empire trade panel started")

function empire_window_draw_trade_resource_row(offset, resource, tradeNow, tradeMax, layout) {
    var ox = offset.x
    var oy = offset.y
    ui.resource_icon_flags({ x: ox + 1, y: oy + 1 }, resource, UiFlags_Outline)

    var text = "0"
    if (tradeNow < 0) {
        text = String(tradeMax)
    } else {
        text = String(tradeNow) + " " + __loc(47, 12) + " " + String(tradeMax)
    }

    var clicked = ui.button({
        text: text,
        pos: { x: ox + layout.button_pad.x, y: oy + layout.button_pad.y },
        size: layout.button_size,
        font: layout.font,
        flags: UiFlags_NoBody,
        tooltip: __loc(23, resource)
    })
    if (clicked == ui.button_clicked) {
        show_trade_resource_settings_window(resource)
    }
    var img = null
    switch (tradeMax) {
    case 1500:
    case 15:
        img = empire_window.trade_amount_image(0)
        if (img) {
            ui.image(img, { x: ox + 21, y: oy - 1 })
        }
        break
    case 2500:
    case 25:
        img = empire_window.trade_amount_image(1)
        if (img) {
            ui.image(img, { x: ox + 17, y: oy - 1 })
        }
        break
    case 4000:
    case 40:
        img = empire_window.trade_amount_image(2)
        if (img) {
            ui.image(img, { x: ox + 13, y: oy - 1 })
        }
        break
    }
}

/** mode: "sell" | "buy". show_traded false → want list (tradeNow = -1). */
function empire_window_draw_trade_resource_list(elm, layout, city, mode, show_traded) {
    if (!city || !elm || !layout) {
        return
    }

    var itemW = layout.size.x
    var itemH = layout.size.y
    var wrap = itemH > 0
    var index = 0
    var row_y = elm.screen_pos.y
    var panelW = elm.size.x

    for (var r = RESOURCE_GRAIN; r <= RESOURCE_MARBLE; r++) {
        var include = (mode == "sell") ? city.city_sells_resource(r) : city.city_buys_resource(r)
        if (!include) {
            continue
        }

        var tradeMax = city.trade_route_limit(r)
        var tradeNow = -1
        if (show_traded) {
            var traded = city.trade_route_traded(r)
            tradeNow = tradeMax < traded ? tradeMax : traded
            tradeNow = __city_resource_stack_proper_quantity(r, tradeNow)
        }
        tradeMax = __city_resource_stack_proper_quantity(r, tradeMax)

        var pos
        if (wrap) {
            var local_x = itemW * index
            pos = { x: elm.screen_pos.x + local_x, y: row_y }
            empire_window_draw_trade_resource_row(pos, r, tradeNow, tradeMax, layout)
            index++
            if (local_x > panelW) {
                row_y += itemH
                index = 0
            }
        } else {
            pos = {
                x: elm.screen_pos.x + itemW * index,
                y: elm.screen_pos.y + itemH * index
            }
            empire_window_draw_trade_resource_row(pos, r, tradeNow, tradeMax, layout)
            index++
        }
    }
}

[es=(empire_window, draw_city_want_sell_items), memory=frame]
function empire_window_es_draw_city_want_sell_items(window) {
    var city = empire.get_city(empire_window.selected_city)
    empire_window_draw_trade_resource_list(window[window.active_id], empire_window.want_item, city, "sell", false)
}

[es=(empire_window, draw_city_want_buy_items), memory=frame]
function empire_window_es_draw_city_want_buy_items(window) {
    var city = empire.get_city(empire_window.selected_city)
    empire_window_draw_trade_resource_list(window[window.active_id], empire_window.want_item, city, "buy", false)
}

[es=(empire_window, draw_city_sell_items), memory=frame]
function empire_window_es_draw_city_sell_items(window) {
    var city = empire.get_city(empire_window.selected_city)
    empire_window_draw_trade_resource_list(window[window.active_id], empire_window.trade_item, city, "sell", true)
}

[es=(empire_window, draw_city_buy_items), memory=frame]
function empire_window_es_draw_city_buy_items(window) {
    var city = empire.get_city(empire_window.selected_city)
    empire_window_draw_trade_resource_list(window[window.active_id], empire_window.trade_item, city, "buy", true)
}

function empire_window_layout_ui(window) {
    var sb = empire_window.screen_bounds
    if (!sb.ready) {
        return
    }
    var centerX = ((sb.min_pos.x + sb.max_pos.x) / 2) | 0
    var width = sb.max_pos.x - sb.min_pos.x
    var infoTop = sb.max_pos.y - 121
    var openTradeTop = sb.max_pos.y - 40
    var infoTooltipTop = sb.max_pos.y - 60
    var sellItemsTop = sb.max_pos.y - 90
    var buyItemsTop = sb.max_pos.y - 90

    window.city_name.pos = { x: sb.min_pos.x, y: infoTop - 1 }
    window.city_name.size = { x: width, y: 20 }

    window.button_help.pos = { x: sb.min_pos.x + 16, y: openTradeTop }
    window.button_close.pos = { x: sb.max_pos.x - 40, y: openTradeTop }
    window.button_advisor.pos = { x: sb.min_pos.x + 16, y: infoTop }
    window.button_pause.pos = { x: sb.max_pos.x - 48, y: infoTop - 2 }

    window.button_open_trade.pos = { x: centerX - 220, y: openTradeTop }
    window.info_tooltip.pos = { x: centerX - 200, y: infoTooltipTop }

    window.city_sell_title.pos = { x: centerX + 250, y: infoTop }
    window.city_sell_items.pos = { x: centerX + 100, y: sellItemsTop }

    window.city_buy_title.pos = { x: centerX - 300, y: infoTop }
    window.city_buy_items.pos = { x: centerX - 430, y: buyItemsTop }

    window.city_want_sell_title.pos = { x: centerX - 220, y: buyItemsTop }
    window.city_want_sell_items.pos = { x: centerX - 170, y: sellItemsTop }

    window.city_want_buy_title.pos = { x: centerX - 220, y: buyItemsTop + 20 }
    window.city_want_buy_items.pos = { x: centerX - 170, y: buyItemsTop + 20 }
}

function empire_window_clear_city_trade_ui(w) {
    w.city_sell_title.enabled = false
    w.city_sell_items.enabled = false
    w.city_buy_title.enabled = false
    w.city_buy_items.enabled = false
    w.city_want_sell_title.enabled = false
    w.city_want_sell_items.enabled = false
    w.city_want_buy_title.enabled = false
    w.city_want_buy_items.enabled = false
}

function empire_window_city_is_trading_type(type) {
    return type == EMPIRE_CITY_PHARAOH_TRADING
        || type == EMPIRE_CITY_EGYPTIAN_TRADING
        || type == EMPIRE_CITY_FOREIGN_TRADING
}

function empire_window_sync_city_info_ui(window) {
    var city = empire.get_city(empire_window.selected_city)
    if (!city) {
        return
    }

    var is_open = !!city.is_open
    switch (city.type) {
    case EMPIRE_CITY_OURS:
        window.info_tooltip.text = __loc(47, 1)
        break
    case EMPIRE_CITY_PHARAOH:
        window.info_tooltip.text = __loc(47, 19)
        break
    case EMPIRE_CITY_EGYPTIAN:
        window.info_tooltip.text = __loc(47, 13)
        break
    case EMPIRE_CITY_FOREIGN:
        window.info_tooltip.text = __loc(47, 0)
        break
    case EMPIRE_CITY_PHARAOH_TRADING:
    case EMPIRE_CITY_EGYPTIAN_TRADING:
    case EMPIRE_CITY_FOREIGN_TRADING:
        window.city_sell_title.enabled = is_open
        window.city_sell_items.enabled = is_open
        window.city_buy_title.enabled = is_open
        window.city_buy_items.enabled = is_open
        window.city_want_sell_title.enabled = !is_open
        window.city_want_sell_items.enabled = !is_open
        window.city_want_buy_title.enabled = !is_open
        window.city_want_buy_items.enabled = !is_open
        break
    }
}

function empire_window_sync_object_info_ui(window) {
    empire_window_clear_city_trade_ui(window)
    window.info_tooltip.text = ""

    var obj = empire_window.selected_object
    if (!obj) {
        window.info_tooltip.text = __loc(47, 9)
        return
    }

    if (obj.type == EMPIRE_OBJECT_CITY) {
        empire_window_sync_city_info_ui(window)
    }
}

function empire_window_confirm_open_trade() {
    var city = empire.get_city(empire_window.selected_city)
    if (!city || city.is_sieged) {
        return
    }

    city.is_open = true
    city.empire_object.trade_route_open = 1
    emit event_finance_request{ type: efinance_request_construction, deben: city.cost_to_open }
    emit event_show_window{ id: "trade_opened_window" }
}

function empire_window_update_selection_ui(window) {
    var city = null
    var cityId = empire_window.selected_city
    if (cityId) {
        city = empire.get_city(cityId)
    }

    window.city_name.text = city ? city.name : ""
    window.button_help.enabled = !!city
    window.button_close.enabled = true
    window.button_advisor.enabled = !!city

    var may_open_trade = city && !city.is_open && city.can_trade
    window.button_open_trade.enabled = may_open_trade
    if (may_open_trade) {
        window.button_open_trade.text = __loc("#debens") + " " + city.cost_to_open + " "
            + __loc(47, 6 + (city.is_sea_trade ? 1 : 0))
    }

    empire_window_sync_object_info_ui(window)
}
