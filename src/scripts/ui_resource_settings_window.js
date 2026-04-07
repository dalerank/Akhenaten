log_info("akhenaten: ui resource settings window started")

[es=window]
trade_resource_settings_window {
    resource : null
    draw_underlying: true
    allow_rmb_goback: true

    pos [(sw(0) - px(36)) / 2, (sh(0) - px(15)) / 2]
    ui {
        background       : outer_panel({size [36, 15]})
        icon             : resource_icon({pos [16, 18] })
        title            : text_center({pos [0, 16], size[px(36), -1], font : FONT_LARGE_BLACK_ON_LIGHT})

        production_state : text_center({pos[48, 42], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})
        production_store : text_center({pos[48, 62], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})

        could_import     : text_center({pos[46, 92], size[px(10), 30], font : FONT_NORMAL_BLACK_ON_LIGHT})
        import_status    : button({
            onclick      : resource_settings_cycle_trade_import
            pos[32, 92], size[px(16), 30], align:"left"
            ui {
                import_dec   : arrowdown({pos[px(16) - 51, 3], onclick: resource_settings_amount_import_dec})
                import_inc   : arrowup({pos[px(16) - 28, 3], onclick: resource_settings_amount_import_inc})
            }
        })

        could_export     : text_center({pos[98 + 216, 101], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})
        export_status    : button({pos[px(36)/2, 92], size[px(16), 30], align:"left"
            onclick: resource_settings_cycle_trade_export
            ui {
                export_dec   : arrowdown({pos[px(16) - 51, 3], onclick: resource_settings_trading_amount_export_dec})
                export_inc   : arrowup({pos[px(16) - 28, 3], onclick: resource_settings_amount_export_inc})
            }
        })

        toggle_industry  : button({margin{centerx:-200}, pos[-1, 130], size[400, 30], onclick: resource_setting_stoggle_industry})
        stockpile_industry: button({margin{centerx:-200}, pos[-1, 168], size[400, 50], split:true, onclick: resource_settings_toggle_stockpiled})

        button_close     : close_button({onclick: window_go_back})
        button_help      : help_button({onclick: show_window_by_id("message_game_concept_industry")})
    }
}

function show_trade_resource_settings_window(resource) {
    trade_resource_settings_window.resource = resource
    emit event_show_window{ id:"trade_resource_settings_window" }
}

function resource_settings_cycle_trade_import(ev) {
    city.resources.cycle_trade_import(trade_resource_settings_window.resource)
}

function resource_setting_stoggle_industry(ev) {
    emit event_toggle_industry_mothballed{ resource: trade_resource_settings_window.resource }
}

function resource_settings_amount_import_dec(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, -100)
}

function resource_settings_amount_import_inc(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, 100)
}

function resource_settings_cycle_trade_export(ev) {
    city.resources.cycle_trade_export(trade_resource_settings_window.resource)
}

function resource_settings_trading_amount_export_dec(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, -100)
}

function resource_settings_amount_export_inc(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, 100)
}

function resource_settings_toggle_stockpiled(ev) {
    city.resources.toggle_stockpiled(trade_resource_settings_window.resource)
}

function resource_settings_production_state_text(resource_id) {
    if (!city.resources.can_produce(resource_id)) {
        return __loc(54, 25)
    }
    var total = city.count_total_industry(resource_id)
    var active = city.count_active_industry(resource_id)
    if (total <= 0) {
        return __loc(54, 7)
    }
    if (__city_resource_is_mothballed(resource_id)) {
        return "" + total + " " + __loc(54, 10 + (total > 1 ? 1 : 0))
    }
    if (total === active) {
        return "" + total + " " + __loc(54, 8 + (total > 1 ? 1 : 0))
    }
    var not_works = total - active
    return "" + active + " " + __loc(54, 12) + ", " + not_works + " " + __loc(54, 13 + (not_works > 0 ? 1 : 0))
}

[es=(trade_resource_settings_window, init)]
function trade_resource_settings_window_on_init(window) {
    if (window.resource !== undefined && window.resource !== null) {
        trade_resource_settings_window.resource = window.resource
    }
    var rid = trade_resource_settings_window.resource
    window.production_state.text = resource_settings_production_state_text(rid)

    window.icon.image = rid
    window.title.text = city.resources.get_name(rid)

    var stored = city.yards_stored(rid)
    window.production_store.text = fmt("${stored} ${unit} ${stored_in_city}", { stored: stored, unit: __loc(8, 10), stored_in_city: __loc(54, 15)})
}

[es=(trade_resource_settings_window, draw_background)]
function trade_resource_settings_window_draw_background(window) {
    var rid = trade_resource_settings_window.resource
    if (rid === null || rid === undefined) {
        return
    }

    var res = city_resource_view(rid)
    var can_import = res.can_import
    var can_export = res.can_export
    var could_import = res.could_import
    var trade_status = res.trade_status
    var trading_amount = 0
    if (trade_status === TRADE_STATUS_EXPORT || trade_status === TRADE_STATUS_IMPORT) {
        trading_amount = res.stack_proper_quantity(res.trading_amount)
    }

    window.import_dec.enabled = false
    window.import_inc.enabled = false
    window.could_import.enabled = false
    window.import_status.enabled = false
    if (!can_import) {
        window.could_import.text = could_import ? __loc(54, 34) : __loc(54, 41)
        window.could_import.enabled = true
    } else {
        window.import_status.enabled = true
        switch (trade_status) {
        default:
            window.import_status.text = __loc(54, 39)
            break
        case TRADE_STATUS_IMPORT_AS_NEEDED:
            window.import_status.text = __loc(54, 43)
            break
        case TRADE_STATUS_IMPORT:
            window.import_status.text = __loc(54, 19) + " " + trading_amount
            window.import_dec.enabled = true
            window.import_inc.enabled = true
            break
        }
    }

    window.could_export.enabled = false
    window.export_dec.enabled = false
    window.export_inc.enabled = false
    window.export_status.enabled = false
    if (!can_export) {
        window.could_export.text = could_import ? __loc(54, 35) : __loc(54, 42)
        window.could_export.enabled = true
    } else {
        window.export_status.enabled = true
        switch (trade_status) {
        default:
            window.export_status.text = __loc(54, 40)
            break
        case TRADE_STATUS_EXPORT_SURPLUS:
            window.export_status.text = __loc(54, 44)
            break
        case TRADE_STATUS_EXPORT:
            window.export_status.text = __loc(54, 20) + " " + trading_amount
            window.export_dec.enabled = true
            window.export_inc.enabled = true
            break
        }
    }

    window.toggle_industry.enabled = (res.count_total_industry > 0)
    window.toggle_industry.text = res.mothballed ? __loc(54, 17) : __loc(54, 16)

    if (res.is_stockpiled) {
        window.stockpile_industry.text = __loc(54, 26) + "\n" + __loc(54, 27)
    } else {
        window.stockpile_industry.text = __loc(54, 28) + "\n" + __loc(54, 29)
    }
}
