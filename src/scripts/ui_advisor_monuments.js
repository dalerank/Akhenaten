log_info("akhenaten: ui advisor monuments started")

var MONUMENT_PHASE_FINISHED = -1

function monuments_advisor_status_line(bid) {
    var phase = __building_monument_phase_code(bid)
    if (phase === MONUMENT_PHASE_FINISHED) {
        return __loc(5, 32)
    }
    var pct = __building_monument_material_pct_min(bid)
    var totalPh = __building_monument_phases_total(bid)
    return String(phase) + " / " + String(totalPh) + "    " + String(pct) + "%"
}

function monuments_advisor_on_render_item(p) {
    var px = p.x
    var py = p.y
    var bid = p.user_data
    var title = __building_display_name(bid)
    ui.label(title, [px + 10, py + 7], FONT_NORMAL_WHITE_ON_DARK)
    ui.label(monuments_advisor_status_line(bid), [px + 10, py + 25], FONT_NORMAL_BLACK_ON_DARK)
    if (p.hover) {
        ui.button_border({ x: px + 2, y: py + 2 }, { x: p.sizex - 4, y: p.sizey - 4 }, false)
    }
}

function monuments_advisor_on_click_item(p) {
    var bid = p.user_data
    city.camera_go_to(__building_tile(bid))
    ui.window_city_show()
}

[es=advisor_window]
advisor_monuments_window {
    advisor: ADVISOR_MONUMENTS
    allow_rmb_goback : true
    help_id: "message_overseer_monuments"
    ui : baseui(advisor_window_base, {
        advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
			ui : {
                background    : outer_panel({size[40, 27]})
                advisor_icon  : image({pack:PACK_GENERAL, id:128, offset:12, pos[10, 10] })
                title         : text({pos[60, 12], text{group:4, id:13}, font:FONT_LARGE_BLACK_ON_LIGHT })
                rating_line   : label({pos[60, 42], text:"${148.2} ${city.rating.monument}", font:FONT_NORMAL_BLACK_ON_LIGHT})
                inner_panel   : inner_panel({pos[32, 70], size[36, 17]})

                monuments_list : scrollable_list({
                    pos[38, 76]
                    size[35, 16]
                    view_items: 6
                    buttons_size_y: 45
                    buttons_margin_x: 0
                    buttons_margin_y: 0
                    text_padding_x: 0
                    text_padding_y: 0
                    draw_scrollbar_always: false
                    draw_paneling: false
                    onrender_item: monuments_advisor_on_render_item
                    onclick_item: monuments_advisor_on_click_item
                })

                no_monuments : label({margin{ centerx:-100, centery:-40}, text:"${53.69}", font:FONT_NORMAL_WHITE_ON_DARK })
            }
        })
    })
}

[es=(advisor_monuments_window, init)]
function advisor_monuments_window_init(window) {
    advisors_toolbar_refresh(window, ADVISOR_MONUMENTS)
}

[es=(advisor_monuments_window, ui_draw_foreground)]
function advisor_monuments_window_draw(window) {
    var n = __city_monuments_list_refresh()
    window.no_monuments.enabled = (n <= 0)

    var list = window.monuments_list
    if (list.items_count !== n) {
        list.clear()
        for (var i = 0; i < n; i++) {
            list.add_item("monument", __city_monuments_list_id_at(i))
        }
    }
}
