log_info("akhenaten: ui advisor imperial started")

function rating_advice_text() {
    return __loc(52, (city.rating_kingdom / 5) + 22)
}

function player_rank_text() {
    return __loc(32, player.rank);
}

function salary_rank_text() {
    return __loc(52, player.salary_rank + 4) + " " + player.salary_amount + " " + __loc(52, 3);
}

var SCENARIO_REQ_NOT_ENOUGH = -1
var SCENARIO_REQ_CONFIRM_LEGIONS = -2
var SCENARIO_REQ_NO_LEGIONS_SELECTED = -3
var SCENARIO_REQ_NO_LEGIONS_AVAILABLE = -4

function scenario_request_compute_status(rq) {
    if (!rq.valid) {
        return SCENARIO_REQ_NOT_ENOUGH
    }
    var rid = rq.resource_id
    if (rid === RESOURCE_DEBEN && city.finance.treasury <= rq.raw_amount) {
        return SCENARIO_REQ_NOT_ENOUGH
    }
    var ab = empire.active_battle
    if (rid === RESOURCE_TROOPS && ab.months_until_battle > 0 && !ab.egyptian_months_to_travel_forth) {
        if (city.military.total_batalions <= 0) {
            return SCENARIO_REQ_NO_LEGIONS_AVAILABLE
        }
        if (city.military.kingdome_service_batalions <= 0) {
            return SCENARIO_REQ_NO_LEGIONS_SELECTED
        }
        return SCENARIO_REQ_CONFIRM_LEGIONS
    }
    var stored_in_city = rq.resource.city_stored
    if (stored_in_city < rq.amount_total) {
        return SCENARIO_REQ_NOT_ENOUGH
    }
    return rq.event_id
}

function scenario_request_handle(rq) {
    var index = rq.index
    if (!rq.valid) {
        return
    }
    __city_military_clear_kingdome_service()
    var s = scenario_request_compute_status(rq)
    if (s === SCENARIO_REQ_NO_LEGIONS_AVAILABLE) {
        ui.show_ok("#popup_dialog_no_legions_available")
        return
    }
    if (s === SCENARIO_REQ_NO_LEGIONS_SELECTED) {
        ui.show_ok("#popup_dialog_no_legions_selected")
        return
    }
    if (s === SCENARIO_REQ_CONFIRM_LEGIONS) {
        ui.show_ok("#popup_dialog_send_troops")
        return
    }
    if (s === SCENARIO_REQ_NOT_ENOUGH) {
        ui.show_ok("#popup_dialog_not_enough_goods")
        return
    }
    ui.show_yesno("#popup_dialog_send_goods", function (yes) {
        if (yes) {
            __scenario_request_dispatch(index)
        }
    })
}

[es=advisor_window]
advisor_imperial_window {
    advisor: ADVISOR_IMPERIAL
    ui {
        background   : outer_panel({size[40, 27]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:2, pos[10, 10] })
        header_label : header({pos[60, 17], text:"Political overseer for ${player.name}"})
        rating_label : label({pos[60, 42], text:"${52.0} ${rating.kingdom}", font:FONT_NORMAL_BLACK_ON_LIGHT})
        rating_advice : multiline({pos[60, 64], size[px(36), 20], wrap:px(35), font:FONT_NORMAL_BLACK_ON_LIGHT, textfn:rating_advice_text})
        inner_panel  : inner_panel({pos[32, 110], size[36, 13] })

        button_request : dummy({pos[38, 116], size[562, 45],
            ui {
                button_request_icon   : dummy({pos[7, 7]})
                button_request_amount : dummy({pos[30, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_months : dummy({pos[310, 7], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_saved  : dummy({pos[30, 25], font: FONT_NORMAL_WHITE_ON_DARK})
                button_request_allow  : dummy({pos[310, 25], font: FONT_NORMAL_WHITE_ON_DARK})
            }
        })

        bottom_panel : inner_panel({pos[64, 324], size[32, 6] })
        player_rank  : header({pos[72, 332], textfn:player_rank_text})

        donate_to_city : button({pos[320, 330], size[250, 20]
                                 text{group:52, id:2}, tooltip:"${68.96}", font:FONT_NORMAL_WHITE_ON_DARK
                                 onclick: window_donate_to_city_show
                                })

        send_gift    : button({pos[320, 352], size[250, 20]
                               text{group:52, id:49}, tooltip:"${68.133}", font:FONT_NORMAL_WHITE_ON_DARK,
                               onclick: window_gift_to_kingdome_show })

        personal_savings : label({pos[72, 374], text:"${52.1} ${city.personal_savings} ${6.0}" })
        money_lost   : label({pos[272, 374], text:"0 debens lost this year throught theft" })
        no_requests  : label({margin{ centerx:-100, centery:-10}, text:"${52.21}", font:FONT_NORMAL_WHITE_ON_DARK })

        salary_rank  : button({pos[70, 392], size[500, 24], tooltip[68, 97], textfn:salary_rank_text, font:FONT_NORMAL_WHITE_ON_DARK, onclick: show_window_by_id("set_salary_window") })

        big_text     : text_center({pos[60, 295], size[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        top_text     : text_center({pos[504, 130], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
        bot_text     : text_center({pos[504, 230], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
    }
}

function imperial_visible_request_view(index) {
    var v = new ScenarioRequest(index)
    if (!v.valid) {
        return null
    }
    v.resource = city_resource_view(v.resource_id)
    return v
}

[es=(advisor_imperial_window, ui_draw_foreground)]
function advisor_imperial_window_draw(window) {
    var br = window.button_request
    var brp = br.pos
    var sz = br.size
    var icon_off = window.button_request_icon.pos
    var amt_off = window.button_request_amount.pos
    var months_off = window.button_request_months.pos
    var saved_off = window.button_request_saved.pos
    var allow_off = window.button_request_allow.pos
    var startReqIdx = 0
    var showDistant = empire.has_distant_battle && empire.dispatched_army.state === 0

    if (showDistant) {
        var rp = { x: brp.x, y: brp.y }
        var clicked = ui.button({
            text: "",
            pos: rp,
            size: sz,
            font: FONT_NORMAL_WHITE_ON_DARK
        })
        if (clicked) {
            __imperial_dispatch_distant_battle()
        }

        ui.resource_icon([rp.x + icon_off.x, rp.y + icon_off.y], RESOURCE_TROOPS)

        var cityLine = __loc(52, 72) + " " + __loc(21, __imperial_distant_battle_city_name_id())
        ui.label(cityLine, [rp.x + amt_off.x, rp.y + amt_off.y], FONT_NORMAL_WHITE_ON_DARK)

        var es = __distant_battle_enemy_strength()
        var sid = 75
        if (es < 46) { sid = 73 }
        else if (es < 89) { sid = 74 }
        var monthsLeft = empire.active_battle.months_until_battle
        var strengthLine = __loc(52, sid) + " " + __loc(8, 4) + " " + monthsLeft
        ui.label(strengthLine, [rp.x + saved_off.x, rp.y + saved_off.y], FONT_NORMAL_WHITE_ON_DARK)

        startReqIdx = 1
    }

    var totalVis = __imperial_visible_request_count()
    var numReq = totalVis
    if (numReq > 5) { numReq = 5 }

    window.no_requests.enabled = (numReq + startReqIdx <= 0)

    for (var index = startReqIdx; index < numReq; index++) {
        var rq = imperial_visible_request_view(index)
        var rp = { x: brp.x, y: brp.y + index * sz.y }
        var rowClicked = ui.button({ text: "", pos: rp, size: sz, font: FONT_NORMAL_WHITE_ON_DARK })
        if (rowClicked) {
            scenario_request_handle(rq)
        }

        ui.resource_icon([rp.x + icon_off.x, rp.y + icon_off.y], rq.resource)

        var quat = rq.resource.stack_proper_quantity(rq.amount_total)
        var amountLine = String(quat) + " " + __loc(23, rq.resource_id)
        ui.label(amountLine, [rp.x + amt_off.x, rp.y + amt_off.y], FONT_NORMAL_WHITE_ON_DARK)

        var monthLine = __loc(8, 4) + " " + rq.months + " " + __loc(12, 2)
        ui.label(monthLine, [rp.x + months_off.x, rp.y + months_off.y], FONT_NORMAL_WHITE_ON_DARK)

        var savedLine
        var allowStr
        var allowFont
        if (rq.resource_id === RESOURCE_DEBEN) {
            var treasury = city.finance.treasury
            savedLine = String(treasury) + " " + __loc(52, 44)
            allowStr = (treasury < rq.raw_amount) ? __loc(52, 48) : __loc(52, 47)
            allowFont = FONT_NORMAL_WHITE_ON_DARK
        } else {
            var in_yards = rq.resource.yards_stored
            var cityStored = rq.resource.stack_proper_quantity(in_yards)
            savedLine = String(cityStored) + " " + __loc(52, 43)
            allowStr = (cityStored < rq.amount_total) ? __loc(52, 48) : __loc(52, 47)
            allowFont = (cityStored < rq.amount_total) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
        }

        ui.label(savedLine, [rp.x + saved_off.x, rp.y + saved_off.y], FONT_NORMAL_WHITE_ON_DARK)
        ui.label(allowStr, [rp.x + allow_off.x, rp.y + allow_off.y], allowFont)
    }
}