log_info("akhenaten: ui_roadblock_orders_window.js loaded")

var roadblock_permission_rows = [
    { perm: epermission_maintenance, label: { group: 64, id: 8 } },
    { perm: epermission_priest, label: { group: 64, id: 27 } },
    { perm: epermission_market, label: { group: 64, id: 26 } },
    { perm: epermission_entertainer, label: { group: 64, id: 15 } },
    { perm: epermission_education, label: { group: 64, id: 29 } },
    { perm: epermission_medicine, label: { group: 64, id: 32 } },
    { perm: epermission_tax_collector, label: { group: 64, id: 7 } },
]

function roadblock_permission_status_text(roadblock, permission) {
    if (roadblock.get_permission(permission)) {
        return { text: __loc(99, 7), font: FONT_NORMAL_WHITE_ON_DARK }
    }
    return { text: __loc(99, 8), font: FONT_NORMAL_BLACK_ON_DARK }
}

function roadblock_orders_list_on_click_item(p) {
    roadblock_orders_window.roadblock.toggle_permission(p.user_data)
}

function roadblock_permission_row(permission) {
    for (var i = 0; i < roadblock_permission_rows.length; i++) {
        if (roadblock_permission_rows[i].perm == permission) {
            return roadblock_permission_rows[i]
        }
    }
    return null
}

function roadblock_orders_list_on_render_item(p) {
    var roadblock = roadblock_orders_window.roadblock
    if (!roadblock) {
        return
    }

    var row = roadblock_permission_row(p.user_data)
    if (!row) {
        return
    }

    ui.label_ex(__loc(row.label.group, row.label.id), [p.x + 32, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, 140)

    var status = roadblock_permission_status_text(roadblock, row.perm)
    ui.label_ex(status.text, [p.x + p.sizex - 132, p.y], status.font, UiFlags_AlignYCentered, 120)

    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 2}, {x: p.sizex - 8, y: p.sizey + 2}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=modal_window]
roadblock_orders_window {
    pos: [(sw(0) - px(29)) / 2, (sh(0) - px(28)) / 2]
    draw_underlying: true
    allow_rmb_goback: true
    roadblock: null

    ui {
        background   : outer_panel({size: [29, 28] }),
        title        : text({pos: [0, 12], size: [px(28), 0], text: {group: 98, id: 5}, font: FONT_LARGE_BLACK_ON_LIGHT, align: "center"}),
        permissions  : scrollable_list({
            pos: [16, 42],
            size: [27, 21],
            view_items: 7,
            buttons_size_y: 22,
            buttons_margin_x: 0,
            buttons_margin_y: 10,
            text_padding_x: 0,
            text_padding_y: 0,
            draw_scrollbar_always: false,
            draw_paneling: true,
            onrender_item: roadblock_orders_list_on_render_item,
            onclick_item: roadblock_orders_list_on_click_item
        }),
        button_help  : help_button({}),
        button_close : close_button({ onclick: window_go_back })
    }
}

[es=(roadblock_orders_window, init)]
function roadblock_orders_window_on_init(window) {
    roadblock_orders_window.roadblock = city.get_roadblock(city.object_info.bid)

    window.permissions.clear()
    for (var i = 0; i < roadblock_permission_rows.length; i++) {
        window.permissions.add_item("perm" + i, roadblock_permission_rows[i].perm)
    }

    ui.set_window_pos("roadblock_orders_window", city.object_info.offset)
}
