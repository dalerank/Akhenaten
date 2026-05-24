log_info("akhenaten: ui_dock_orders_window.js loaded")

function dock_order_instruction(dock, resource) {
    if (dock.is_trade_accepted(resource)) {
        return { text: "Trade", font: FONT_NORMAL_WHITE_ON_DARK }
    }
    return { text: "Don't trade", font: FONT_NORMAL_BLACK_ON_DARK }
}

function dock_orders_window_accept_none() {
    dock_orders_window.dock.unaccept_all_goods()
}

function dock_orders_list_on_click_item(p) {
    dock_orders_window.dock.toggle_good_accepted(p.user_data)
}

function dock_orders_list_on_render_item(p) {
    var resId = p.user_data
    var dock = dock_orders_window.dock
    if (resId == RESOURCE_NONE || !dock) {
        return
    }

    ui.resource_icon([p.x + 25, p.y + 2], resId)
    ui.label_ex(__loc(23, resId), [p.x + 85, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, 150)

    var instr = dock_order_instruction(dock, resId)
    ui.label_ex(instr.text, [p.x + p.sizex - 132, p.y], instr.font, UiFlags_AlignYCentered, 120)

    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 2}, {x: p.sizex - 8, y: p.sizey + 2}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=modal_window]
dock_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(22)) / 2]
    draw_underlying: true
    allow_rmb_goback: true
    dock: null

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
            onrender_item: dock_orders_list_on_render_item
            onclick_item: dock_orders_list_on_click_item
        })
        accept_none  : button({pos[80, -1], size[300, 24], text:{group:99, id:7}, margin{bottom:-38}, onclick: dock_orders_window_accept_none })

        button_help   : help_button({})
        button_close  : close_button({ onclick: window_go_back })
    }
}

[es=(dock_orders_window, init)]
function dock_orders_window_init(window) {
    dock_orders_window.dock = city.get_dock(city.object_info.bid)

    window.goods_list.clear()
    for (var name in city.resources.available) {
        var resId = city.resources.available[name]
        if (__city_resource_trade_status(resId) == TRADE_STATUS_NONE) {
            continue
        }
        window.goods_list.add_item(name, resId)
    }

    ui.set_window_pos("dock_orders_window", city.object_info.offset)
}
