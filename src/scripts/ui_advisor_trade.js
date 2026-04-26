log_info("akhenaten: ui advisor trade started")

function advisor_trade_list_on_click_item(p) {
    if (!p || p.text === undefined || p.text === "") {
        return
    }
    var res = city.resources.id_by_name(p.text)
    if (res === RESOURCE_NONE) {
        return
    }
    show_trade_resource_settings_window(res)
}

function advisor_trade_render_row(res, px, py) {
    var moth = res.mothballed
    var fontMain = moth ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK

    var stored = res.yards_stored
    var properQ = res.stack_proper_quantity(stored)

    ui.resource_icon([px + 8, py - 2], res.type)

    ui.label_ex(__loc(23, res.type), [px + 32, py], fontMain, UiFlags_AlignYCentered, 0)
    ui.label_ex(String(properQ), [px + 186, py], fontMain, UiFlags_AlignYCentered, 60)

    if (res.is_stockpiled) {
        ui.label_ex(__loc(54, 3), [px + 284, py - 2], fontMain, UiFlags_AlignYCentered, 100)
    } else if (moth) {
        ui.label_ex(__loc(18, 5), [px + 284, py - 2], FONT_NORMAL_YELLOW, UiFlags_AlignYCentered, 100)
    }

    var ts = res.trade_status
    var tradeAmt = res.stack_proper_quantity(res.trading_amount)

    switch (ts) {
    case TRADE_STATUS_NONE:
        var can_import = res.can_import
        var can_export = res.can_export
        var could_import = res.could_import
        var could_export = res.could_export
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
        break

    case TRADE_STATUS_IMPORT:
        ui.label(__loc(54, 5) + " " + String(tradeAmt), [px + 254, py - 2], fontMain)
        break

    case TRADE_STATUS_EXPORT:
        ui.label(__loc(54, 6) + " " + String(tradeAmt), [px + 254, py - 2], fontMain)
        break

    case TRADE_STATUS_IMPORT_AS_NEEDED:
        ui.label(__loc(54, 37), [px + 254, py - 2], fontMain)
        break

    case TRADE_STATUS_EXPORT_SURPLUS:
        ui.label(__loc(54, 38), [px + 254, py - 2], fontMain)
    }
}

function advisor_trade_list_on_render_item(p) {
    var resname = p.text
    if (!resname || resname == "") {
        return
    }
    var res = city.resources[resname]
    if (!res) {
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
    allow_rmb_goback : true
    help_id: "message_overseer_commerce"
    ui : baseui(advisor_window_base, {
        advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
            ui : {
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
                    buttons_margin_y:10
                    text_padding_x:0
                    text_padding_y:5
                    draw_scrollbar_always:true
                    onrender_item: advisor_trade_list_on_render_item
                    onclick_item: advisor_trade_list_on_click_item
                })

                goto_empire  : button({pos:[48, 396], size:[200, 24], text:"#trade_overseer_goto_empire", tooltip:"#trade_overseer_goto_empire_hint", onclick: __window_empire_show })
                show_prices  : button({pos:[368, 396], size:[200, 24], text:"#trade_overseer_prices", tooltip:"#trade_overseer_prices_hint", onclick: show_window_by_id("trade_prices_window") })
            }
        })
    })
}

[es=(advisor_trade_window, init)]
function advisor_trade_window_init(window) {
    window.resources_list.clear()
    for (var name in city.resources.available) {
        window.resources_list.add_item(name)
    }
    advisors_toolbar_refresh(window, ADVISOR_TRADE)
}