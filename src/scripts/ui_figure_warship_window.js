log_info("akhenaten: ui figure warship window started")

var WARSHIP_ORDER_GOTO_WHARF = 1
var WARSHIP_ORDER_ENGAGE_NEARBY = 2
var WARSHIP_ORDER_HOLD_POSITION = 3
var WARSHIP_ORDER_SEEK_AND_DESTROY = 4
var WARSHIP_ORDER_REPAIR = 5
var WARSHIP_ORDER_MOVE_TO_TILE = 6

var figure_warship_order_buttons = [
    { id: "hold_position", order: WARSHIP_ORDER_HOLD_POSITION },
    { id: "engage_nearby", order: WARSHIP_ORDER_ENGAGE_NEARBY },
    { id: "seek_and_destroy", order: WARSHIP_ORDER_SEEK_AND_DESTROY },
    { id: "repair", order: WARSHIP_ORDER_REPAIR },
    { id: "return_to_wharf", order: WARSHIP_ORDER_GOTO_WHARF },
]

var figure_warship_order_text_ids = {
    1: { header: 17, text: 18 },
    2: { header: 11, text: 12 },
    3: { header: 9, text: 10 },
    4: { header: 13, text: 14 },
    5: { header: 15, text: 16 },
}

function figure_warship_hull_strength_text_id(ship) {
    var max_dmg = ship.max_damage
    if (max_dmg <= 0) {
        return 3
    }
    var health_pct = 100 - (ship.damage * 100 / max_dmg)
    if (health_pct >= 90) { return 3 }
    if (health_pct >= 70) { return 4 }
    if (health_pct >= 50) { return 5 }
    if (health_pct >= 30) { return 6 }
    if (health_pct >= 10) { return 7 }
    return 8
}

function figure_warship_crew_fatigue_text_id(ship) {
    var fatigue = ship.crew_fatigue
    if (fatigue >= 75) { return 30 }
    if (fatigue >= 40) { return 29 }
    return 28
}

function figure_warship_action_text(order) {
    if (order == WARSHIP_ORDER_MOVE_TO_TILE) {
        return {
            header: __loc("#warship_moving_to_position"),
            text: __loc("#warship_moving_to_position_text"),
        }
    }

    var ids = figure_warship_order_text_ids[order]
    if (!ids) {
        return { header: "", text: "" }
    }
    return { header: __loc(184, ids.header), text: __loc(184, ids.text) }
}

function figure_warship_hovered_order(window) {
    for (var i = 0; i < figure_warship_order_buttons.length; i++) {
        var btn = window[figure_warship_order_buttons[i].id]
        if (btn && btn.hovered) {
            return figure_warship_order_buttons[i].order
        }
    }
    return 0
}

[es=figure_info_window]
figure_warship_info_window {
    related_figures [FIGURE_WARSHIP]

    ui {
        background       : outer_panel({size: [29, 23]}),
        name             : text_center({pos: [16, 16], size: [px(27), 20], text:"${figure.class_name}", font : FONT_LARGE_BLACK_ON_DARK }),
        hullstrength_lb  : text({pos: [102, 58], text:"${184.2}" }),
        hullstrength_val : text({pos: [232, 58], text:"" }),
        crewfatique_lb   : text({pos: [102, 88], text:"${184.27}" }),
        crewfatique_val  : text({pos: [232, 88], text:"" }),

        hold_position    : image_button({param1:3, param2:9, pos:[87 * 0 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 0, offset_pressed:0, offset_focused:0, border:true, onclick_event:"set_order" }),
        engage_nearby    : image_button({param1:2, param2:11, pos:[87 * 1 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 1, offset_pressed:0, offset_focused:0, border:true, onclick_event:"set_order" }),
        seek_and_destroy : image_button({param1:4, param2:13, pos:[87 * 2 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 2, offset_pressed:0, offset_focused:0, border:true, onclick_event:"set_order" }),
        repair           : image_button({param1:5, param2:15, pos:[87 * 3 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 3, offset_pressed:0, offset_focused:0, border:true, onclick_event:"set_order" }),
        return_to_wharf  : image_button({param1:1, param2:17, pos:[87 * 4 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 4, offset_pressed:0, offset_focused:0, border:true, onclick_event:"set_order" }),

        inner_panel      : inner_panel({pos : [16, 220], size: [27, 6],
            ui : {
                action_header: text({pos: [10, 10], font : FONT_NORMAL_WHITE_ON_DARK }),
                action_text : text({pos: [10, 30], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(21), multiline:true }),
            }
        }),

        button_help      : help_button({}),
        button_close     : close_button({}),
        show_follow      : button({margin:{right:-64, bottom:-40}, size:[23, 23], text:"F", tooltip:"#follow_walker", onclick_event: "show_follow"}),
    }
}

[es=(figure_warship_info_window, init)]
function figure_warship_info_window_init(window) {
    var fid = __object_info_figure_id()
    __figure_info_set_help(fid)
    window.name.text = city.get_figure(fid).class_name
}

[es=(figure_warship_info_window, set_order)]
function figure_warship_info_window_on_set_order(window, ev) {
    var ship = city.get_warship(__object_info_figure_id())
    if (!ship.valid) {
        return
    }
    ship.set_order(ev.param1)
    ui.window_city_show()
}

[es=(figure_warship_info_window, show_follow)]
function figure_warship_info_window_on_show_follow(window) {
    __figure_follow_start(__object_info_figure_id())
}

[es=(figure_warship_info_window, window_info_background)]
function figure_warship_info_window_window_info_background(window) {
    var f = city.get_figure(__object_info_figure_id())
    var ship = city.get_warship(f.id)

    window.name.text = f.class_name
    window.hullstrength_val.text = __loc(184, figure_warship_hull_strength_text_id(ship))
    window.crewfatique_val.text = __loc(184, figure_warship_crew_fatigue_text_id(ship))

    window.repair.darkened = ship.damage == 0 ? UiFlags_Grayscale : 0
    window.return_to_wharf.darkened = f.action_state == ACTION_203_WARSHIP_MOORED ? UiFlags_Grayscale : 0

    var order = ship.active_order
    for (var i = 0; i < figure_warship_order_buttons.length; i++) {
        var entry = figure_warship_order_buttons[i]
        window[entry.id].selected = (order == entry.order)
    }

    var hovered_order = figure_warship_hovered_order(window)
    var action = figure_warship_action_text(hovered_order ? hovered_order : order)
    window.action_header.text = action.header
    window.action_text.text = action.text

    var following = __figure_follow_enabled() && __figure_follow_figure_id() == f.id
    window.show_follow.text = following ? "F" : "f"
}
