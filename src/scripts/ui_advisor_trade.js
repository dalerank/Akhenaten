log_info("akhenaten: ui advisor trade started")

function advisor_trade_list_on_click_item(p) {
    if (!p || p.text === undefined || p.text === "") {
        return
    }
    var res = __city_resource_id_by_name(p.text)
    if (res === RESOURCE_NONE) {
        return
    }
    __window_resource_settings_show(res)
}

function advisor_trade_render_row(res, px, py) {
    var moth = __city_resource_is_mothballed(res)
    var fontMain = moth ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK

    var stored = __city_yards_stored(res)
    var properQ = __city_resource_stack_proper_quantity(res, stored)

    ui.resource_icon([px + 8, py - 2], res)

    ui.label_ex(__loc(23, res), [px + 32, py], fontMain, UiFlags_AlignYCentered, 0)
    ui.label_ex(String(properQ), [px + 186, py], fontMain, UiFlags_AlignYCentered, 60)

    if (__city_resource_is_stockpiled(res)) {
        ui.label_ex(__loc(54, 3), [px + 284, py - 2], fontMain, UiFlags_AlignYCentered, 100)
    } else if (moth) {
        ui.label_ex(__loc(18, 5), [px + 284, py - 2], FONT_NORMAL_YELLOW, UiFlags_AlignYCentered, 100)
    }

    var ts = __city_resource_trade_status(res)
    var tradeAmt = __city_resource_stack_proper_quantity(res, __city_resource_trading_amount(res))

    if (ts === TRADE_STATUS_NONE) {
        var can_import = __city_resource_can_import(res, true)
        var can_export = __city_resource_can_export(res, true)
        var could_import = __city_resource_can_import(res, false)
        var could_export = __city_resource_can_export(res, false)
        var statusText = ""
        var statusFont = fontMain
        if (can_import && !can_export) { statusText = __loc(54, 31) }
        else if (!can_import && can_export) { statusText = __loc(54, 32) }
        else if (can_import && can_export) { statusText = __loc(54, 33) }
        else if (could_import && !could_export) { statusText = __loc(54, 34); statusFont = FONT_NORMAL_BLACK_ON_DARK }
        else if (!could_import && could_export) { statusText = __loc(54, 35); statusFont = FONT_NORMAL_BLACK_ON_DARK }
        else if (could_import && could_export) { statusText = __loc(54, 36); statusFont = FONT_NORMAL_BLACK_ON_DARK }
        if (statusText) {
            ui.label(statusText, [px + 254, py - 2], statusFont)
        }
    } else if (ts === TRADE_STATUS_IMPORT) {
        ui.label(__loc(54, 5) + " " + String(tradeAmt), [px + 254, py - 2], fontMain)
    } else if (ts === TRADE_STATUS_EXPORT) {
        ui.label(__loc(54, 6) + " " + String(tradeAmt), [px + 254, py - 2], fontMain)
    } else if (ts === TRADE_STATUS_IMPORT_AS_NEEDED) {
        ui.label(__loc(54, 37), [px + 254, py - 2], fontMain)
    } else if (ts === TRADE_STATUS_EXPORT_SURPLUS) {
        ui.label(__loc(54, 38), [px + 254, py - 2], fontMain)
    }
}

function advisor_trade_list_on_render_item(p) {
    if (!p || p.text === undefined || p.text === "") {
        return
    }
    var res = __city_resource_id_by_name(p.text)
    if (res === RESOURCE_NONE) {
        return
    }
    advisor_trade_render_row(res, p.x, p.y)
    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 4}, {x: p.sizex - 8, y: p.sizey - 4}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=advisor_window]
advisor_trade_window {
    advisor: ADVISOR_TRADE
    ui {
        background   : outer_panel({size[40, 27]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:4, pos:[10, 10]})
        header_label : label({font : FONT_LARGE_BLACK_ON_LIGHT, text:"#trade_overseer", pos:[60, 17]})
        hint_label   : label({font : FONT_NORMAL_BLACK_ON_DARK, text:"#trade_overseer_hint", pos:[60, 40]})

        resources_list : scrollable_list({
            pos:[17, 60]
            size:[36, 21]
            view_items:15
            buttons_size_y:22
            buttons_margin_x:0
            buttons_margin_y:0
            text_padding_x:0
            text_padding_y:5
            draw_scrollbar_always:true
            onrender_item: advisor_trade_list_on_render_item
            onclick_item: advisor_trade_list_on_click_item
        })

        show_prices  : button({pos:[48, 396], size:[200, 24], text:"#trade_overseer_goto_empire", tooltip:"#trade_overseer_goto_empire_hint", onclick: __window_empire_show })
        goto_empireи  : button({pos:[368, 396], size:[200, 24], text:"#trade_overseer_prices", tooltip:"#trade_overseer_prices_hint", onclick: __window_trade_prices_show })
    }
}

[es=(advisor_trade_window, init)]
function advisor_trade_window_init(window) {
    __city_resource_determine_available()
    var n = __city_resources_available_count()
    window.resources_list.clear()
    for (var i = 0; i < n; i++) {
        var rid = __city_resource_available_at(i)
        window.resources_list.add_item(__city_resource_name(rid))
    }
}
