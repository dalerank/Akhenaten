log_info("akhenaten: ui storage yard orders window started")

function storage_yard_order_instruction(storage, resource) {
    var state = storage.resource_state(resource)
    if (state == STORAGE_STATE_ACCEPT) {
        var max_accept = storage.resource_max_accept(resource)
        var label = String(max_accept)
        if (max_accept == 3200) { label = __loc(99, 28) }
        else if (max_accept == 2400) { label = __loc(99, 27) }
        else if (max_accept == 1600) { label = __loc(99, 26) }
        else if (max_accept == 800)  { label = __loc(99, 25) }
        var adv = ""
        if (max_accept == 2400 || max_accept == 1600 || max_accept == 800) { adv = __loc(99, 29) }
        return { text: __loc(99, 18) + " " + label + " " + adv, font: FONT_NORMAL_WHITE_ON_DARK }
    }
    if (state == STORAGE_STATE_REFUSE) {
        return { text: __loc(99, 8), font: FONT_NORMAL_BLACK_ON_DARK }
    }
    if (state == STORAGE_STATE_GET) {
        var max_get = storage.resource_max_get(resource)
        var label = String(max_get)
        if (max_get == 3200) { label = __loc(99, 31) }
        else if (max_get == 2400) { label = __loc(99, 27) }
        else if (max_get == 1600) { label = __loc(99, 26) }
        else if (max_get == 800)  { label = __loc(99, 25) }
        var adv = ""
        if (max_get == 2400 || max_get == 1600 || max_get == 800) { adv = __loc(99, 29) }
        return { text: __loc(99, 19) + " " + label + " " + adv, font: FONT_NORMAL_YELLOW }
    }
    if (state == STORAGE_STATE_EMPTY) {
        return { text: __loc(99, 21), font: FONT_NORMAL_BLACK_ON_DARK }
    }
    return { text: "unknown_storage", font: FONT_NORMAL_BLACK_ON_DARK }
}

function storage_yard_orders_list_on_click_item(p) {
    storage_yard_orders_window.storage_yard.cycle_resource_state(p.user_data)
}

function storage_yard_orders_list_on_render_item(p) {
    var resId = p.user_data
    if (resId === undefined || resId === RESOURCE_NONE || !storage_yard_orders_window.storage_yard) { return }

    ui.resource_icon([p.x + 25, p.y + 2], resId)
    ui.label_ex(__loc(23, resId), [p.x + 85, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, 150)

    var state = storage_yard_orders_window.storage_yard.resource_state(resId)
    if (state == STORAGE_STATE_ACCEPT || state == STORAGE_STATE_GET) {
        if (ui.arw_button([p.x + p.sizex - 60, p.y + 2], false, true)) {
            storage_yard_orders_window.storage_yard.increase_decrease_resource_state(resId, true)
        }
        if (ui.arw_button([p.x + p.sizex - 40, p.y + 2], true, true)) {
            storage_yard_orders_window.storage_yard.increase_decrease_resource_state(resId, false)
        }
    }

    var instr = storage_yard_order_instruction(storage_yard_orders_window.storage_yard, resId)
    ui.label_ex(instr.text, [p.x + p.sizex - 280, p.y], instr.font, UiFlags_AlignYCentered, 220)
}

[es=modal_window]
storage_yard_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(17)) / 2]
    draw_underlying: true
    allow_rmb_goback: true
    storage_yard: null

    ui {
        background   : outer_panel({size[29, 17]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:99, id:3}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
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
            onrender_item: storage_yard_orders_list_on_render_item
            onclick_item: storage_yard_orders_list_on_click_item
        })
        empty_all    : button({pos[80, -1]
                               size[300, 24]
                               margin{bottom:-64}
                               textfn: function() { return storage_yard_orders_window.storage_yard.is_empty_all() ? __loc(99, 5) : __loc(99, 4) }
                               onclick: function() { storage_yard_orders_window.storage_yard.toggle_empty_all() }
                              })

        accept_none  : button({pos[80, -1]
                               size[300, 24]
                               margin{bottom:-38}
                               text:{group:99, id:7}
                               onclick: function() { storage_yard_orders_window.storage_yard.accept_none() }
                              })

        button_help   : help_button({})
        button_close  : close_button({ onclick: window_go_back })
    }
}

[es=(storage_yard_orders_window, init)]
function storage_yard_orders_window_init(window) {
    storage_yard_orders_window.storage_yard = city.get_storage_yard(window.bid)

    window.goods_list.clear()
    for (var name in city.resources.available) {
        var resId = city.resources.available[name]
        window.goods_list.add_item(name, resId)
    }

    var base = {
        panel_blocks: {x: 29, y: 18},
        list_blocks: {x: 27, y: 11},
        view_items: 8,
        info_panel_blocks_y: 21
    }

    var itemsCount = window.goods_list.items_count
    var blocksPerItem = base.list_blocks.y / base.view_items
    var screenBlocksY = Math.floor((sh(0) - px(2)) / 16)
    var maxPanelBlocksY = Math.max(base.panel_blocks.y, screenBlocksY)
    var maxListBlocksY = base.list_blocks.y + (maxPanelBlocksY - base.panel_blocks.y)
    var maxViewItems = Math.max(1, Math.floor(maxListBlocksY / blocksPerItem))
    var targetViewItems = Math.max(1, Math.min(itemsCount, maxViewItems))
    var targetListBlocksY = Math.max(base.list_blocks.y, Math.ceil(targetViewItems * blocksPerItem))
    var targetPanelBlocksY = base.panel_blocks.y + (targetListBlocksY - base.list_blocks.y)

    window.goods_list.view_items = targetViewItems
    window.goods_list.size = [base.list_blocks.x, targetListBlocksY]
    window.background.size = [base.panel_blocks.x, targetPanelBlocksY]

    var offsetx = city.object_info.offset.x
    var offsety = city.object_info.offset.y + px(base.info_panel_blocks_y - targetPanelBlocksY)
    ui.set_window_pos("storage_yard_orders_window", {x: offsetx, y: offsety})
}
