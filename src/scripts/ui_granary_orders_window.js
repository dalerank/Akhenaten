log_info("akhenaten: ui granary orders window started")

function granary_order_instruction(storage, resource) {
    var state = storage.resource_state(resource)

    function amount_label(amount, loc_full_id) {
        return (amount == 3200) ? __loc(99, loc_full_id) : String(amount)
    }

    var max_accept = storage.resource_max_accept(resource)
    var max_get = storage.resource_max_get(resource)
    switch (state) {
    case STORAGE_STATE_ACCEPT:  return { text: __loc(99, 18) + " " + amount_label(max_accept, 28), font: FONT_NORMAL_WHITE_ON_DARK }
    case STORAGE_STATE_REFUSE:  return { text: __loc(99, 8), font: FONT_NORMAL_BLACK_ON_DARK }
    case STORAGE_STATE_GET:     return { text: __loc(99, 19) + " " + amount_label(max_get, 31), font: FONT_NORMAL_YELLOW }
    case STORAGE_STATE_EMPTY:   return { text: __loc(99, 21), font: FONT_NORMAL_BLACK_ON_DARK }
    default:                    return { text: "unknown_storage", font: FONT_NORMAL_BLACK_ON_DARK }
    }
}

function granary_orders_list_on_click_item(p) {
    granary_orders_window.granary.cycle_resource_state(p.user_data)
}

function granary_orders_list_on_render_item(p) {
    var resId = p.user_data
    var granary = granary_orders_window.granary
    if (resId == RESOURCE_NONE || !granary)
        return

    ui.resource_icon([p.x + 25, p.y + 2], resId)
    ui.label_ex(__loc(23, resId), [p.x + 65, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, 150)

    var state = granary.resource_state(resId)
    if (state == STORAGE_STATE_ACCEPT || state == STORAGE_STATE_GET) {
        if (ui.arw_button([p.x + 340, p.y + 2], false, true, false)) {
            granary.increase_decrease_resource_state(resId, false)
        }

        if (ui.arw_button([p.x + 360, p.y + 2], true, true, false)) {
            granary.increase_decrease_resource_state(resId, true)
        }
    }

    var instr = granary_order_instruction(granary, resId)
    ui.label_ex(instr.text, [p.x + 180, p.y], instr.font, UiFlags_AlignYCentered, 220)
    ui.resource_icon([p.x + 25 + px(23), p.y + 2], resId)

    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 2}, {x: p.sizex - 8, y: p.sizey + 2}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=modal_window]
granary_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(17)) / 2]
    draw_underlying: true
    allow_rmb_goback: true
    granary: null

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
            onrender_item: granary_orders_list_on_render_item
            onclick_item: granary_orders_list_on_click_item
        })
        empty_all    : button({pos[80, -1]
                               size[300, 24]
                               margin{bottom:-64}
                               textfn: function() { return granary_orders_window.granary.is_empty_all() ? __loc(98, 8) : __loc(98, 7) }
                               onclick: function() { granary_orders_window.granary.toggle_empty_all() }
                              })

        accept_none  : button({pos[80, -1]
                               size[300, 24]
                               margin{bottom:-38}
                               text:{group:99, id:7}
                               onclick: function() { granary_orders_window.granary.accept_none() }
                              })

        button_help   : help_button({})
        button_close  : close_button({ onclick: window_go_back })
    }
}

[es=(granary_orders_window, init)]
function granary_orders_window_init(window) {
    granary_orders_window.granary = city.get_granary(city.object_info.bid)

    window.goods_list.clear()
    for (var name in city.resources.available_foods) {
        var resId = city.resources.available_foods[name]
        window.goods_list.add_item(name, resId)
    }

    ui.set_window_pos("granary_orders_window", city.object_info.offset)
}
