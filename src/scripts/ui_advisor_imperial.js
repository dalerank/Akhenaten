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

function imperial_requests_on_click_item(p) {
    if (p.text === "distant") {
        __imperial_dispatch_distant_battle()
        return
    }
    var rq = imperial_visible_request_view(p.user_data)
    scenario_request_handle(rq)
}

function imperial_requests_on_render_item(p) {
    var px = p.x
    var py = p.y
    if (p.text === "distant") {
        ui.resource_icon([px + 7, py + 7], RESOURCE_TROOPS)
        var cityLine = __loc(52, 72) + " " + __loc(21, __imperial_distant_battle_city_name_id())
        ui.label(cityLine, [px + 30, py + 7], FONT_NORMAL_WHITE_ON_DARK)
        var es = __distant_battle_enemy_strength()
        var sid = 75
        if (es < 46) { sid = 73 }
        else if (es < 89) { sid = 74 }
        var monthsLeft = empire.active_battle.months_until_battle
        var strengthLine = __loc(52, sid) + " " + __loc(8, 4) + " " + monthsLeft
        ui.label(strengthLine, [px + 30, py + 25], FONT_NORMAL_WHITE_ON_DARK)
    } else {
        var rq = imperial_visible_request_view(p.user_data)
        if (!rq) {
            return
        }
        ui.resource_icon([px + 7, py + 7], rq.resource)
        var quat = rq.resource.stack_proper_quantity(rq.amount_total)
        var amountLine = String(quat) + " " + __loc(23, rq.resource_id)
        ui.label(amountLine, [px + 30, py + 7], FONT_NORMAL_WHITE_ON_DARK)
        var monthLine = __loc(8, 4) + " " + rq.months + " " + __loc(12, 2)
        ui.label(monthLine, [px + 310, py + 7], FONT_NORMAL_WHITE_ON_DARK)
        var savedLine
        var allowStr
        var allowFont
        if (rq.resource_id === RESOURCE_DEBEN) {
            var treasury = city.finance.treasury
            savedLine = String(treasury) + " " + __loc(52, 44)
            allowStr = (treasury < rq.raw_amount) ? __loc("#ui_unable_to_fulfill_request") : __loc(52, 47)
            allowFont = FONT_NORMAL_WHITE_ON_DARK
        } else {
            var in_yards = rq.resource.yards_stored
            var cityStored = rq.resource.stack_proper_quantity(in_yards)
            savedLine = String(cityStored) + " " + __loc(52, 43)
            allowStr = (cityStored < rq.amount_total) ? __loc("#ui_unable_to_fulfill_request") : __loc(52, 47)
            allowFont = (cityStored < rq.amount_total) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
        }
        ui.label(savedLine, [px + 30, py + 25], FONT_NORMAL_WHITE_ON_DARK)
        ui.label(allowStr, [px + 310, py + 25], allowFont)
    }

    if (p.hover) {
        ui.button_border({ x: px + 2, y: py + 2 }, { x: p.sizex - 4, y: p.sizey - 4 }, false)
    }
}

[es=advisor_window]
advisor_imperial_window {
    advisor: ADVISOR_IMPERIAL
    allow_rmb_goback : true
    help_id: "message_overseer_political"
    ui : baseui(advisor_window_base, {
        advisor_area         : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2], size:[px(40), px(27)]
            ui : {
                background   : outer_panel({size[40, 27]})
                advisor_icon : image({pack:PACK_GENERAL, id:128, offset:2, pos[10, 10] })
                header_label : header({pos[60, 17]})
                rating_label : label({pos[60, 42], font:FONT_NORMAL_BLACK_ON_LIGHT})
                rating_advice : multiline({pos[60, 64], size[px(36), 20], wrap:px(35), font:FONT_NORMAL_BLACK_ON_LIGHT, textfn:rating_advice_text})
                inner_panel  : inner_panel({pos[32, 110], size[36, 13] })

                requests_list : scrollable_list({
                    pos[38, 116]
                    size[35, 14]
                    view_items: 5
                    buttons_size_y: 45
                    buttons_margin_x: 0
                    buttons_margin_y: 0
                    text_padding_x: 0
                    text_padding_y: 0
                    draw_scrollbar_always: false
                    draw_paneling: false
                    onrender_item: imperial_requests_on_render_item
                    onclick_item: imperial_requests_on_click_item
                })

                bottom_panel : inner_panel({pos[64, 324], size[32, 6] })
                player_rank  : header({pos[72, 332], textfn:player_rank_text})

                donate_to_city : button({pos[320, 330], size[250, 20]
                                         text{group:52, id:2}, tooltip:"${68.96}", font:FONT_NORMAL_WHITE_ON_DARK
                                         onclick: show_window_by_id("donate_to_city_window")
                                        })

                send_gift    : button({pos[320, 352], size[250, 20]
                                       text{group:52, id:49}, tooltip:"${68.133}", font:FONT_NORMAL_WHITE_ON_DARK,
                                       onclick: show_window_by_id("gift_to_kingdome_window")
                                      })

                personal_savings : label({pos[72, 374]
                                          textfn:function() { return _eformat( "${52.1} ${city.personal_savings} ${6.0}", { city : city }) }
                                         })
                money_lost   : label({pos[272, 374], textfn: function() { return "0 " + __loc(52, 79) } })
                no_requests  : label({margin{ left:40, centery:0}, text:"#no_requests", font:FONT_NORMAL_WHITE_ON_DARK })

                salary_rank  : button({pos[70, 392], size[500, 24], tooltip[68, 97], textfn:salary_rank_text, font:FONT_NORMAL_WHITE_ON_DARK, onclick: show_window_by_id("set_salary_window") })

                big_text     : text_center({pos[60, 295], size[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
                top_text     : text_center({pos[504, 130], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})
                bot_text     : text_center({pos[504, 230], size[100, 20], font:FONT_NORMAL_BLACK_ON_LIGHT})

                button_help   : help_button({})
            }
        })
    })
}

function imperial_visible_request_view(index) {
    var v = new ScenarioRequest(index)
    if (!v.valid) {
        return null
    }
    v.resource = city_resource_view(v.resource_id)
    return v
}

[es=(advisor_imperial_window, init)]
function advisor_imperial_window_on_init(window) {
    advisors_toolbar_refresh(window, ADVISOR_IMPERIAL)
    window.header_label.text = "Political overseer for " + game.dynasty_name
    window.rating_label.text = __loc(52, 0) + " " + city.rating_kingdom
}

[es=(advisor_imperial_window, ui_draw_foreground)]
function advisor_imperial_window_draw(window) {
    var totalVis = __imperial_visible_request_count()
    var showDistant = empire.has_distant_battle && empire.dispatched_army.state === 0
    var startReqIdx = showDistant ? 1 : 0
    var rowCount = (showDistant ? 1 : 0) + Math.max(0, totalVis - startReqIdx)

    window.no_requests.enabled = (rowCount <= 0)

    var list = window.requests_list
    if (list.items_count !== rowCount) {
        list.clear()
        if (showDistant) {
            list.add_item("distant", 0)
        }
        for (var ix = startReqIdx; ix < totalVis; ix++) {
            list.add_item("request", ix)
        }
    }
}