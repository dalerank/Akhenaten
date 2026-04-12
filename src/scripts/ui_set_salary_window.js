log_info("akhenaten: ui set salary window started")

function salary_rank_text(rank, _) {
    return city.rank_title(rank) + ": " + city.rank_salary(rank) + " " + __loc(6, 0)
}

function set_salary_window_list_on_click_item(p) {
    city.apply_salary_rank(p.user_data)
    window_go_back()
}

function set_salary_window_list_on_render_item(p) {
    var rank = p.user_data
    var line = salary_rank_text(rank, 0)
    ui.label_ex(line, [p.x + 32, p.y], FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignYCentered, p.sizex - 40)
    if (p.hover) {
        ui.border({x: p.x + 4, y: p.y - 2}, {x: p.sizex - 8, y: p.sizey + 2}, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
    }
}

[es=modal_window]
set_salary_window {
    pos [(sw(0) - px(24))/2, (sh(0) - px(25))/2]
    allow_rmb_goback: true
    draw_underlying: true

    ui {
        background_image : background({pack:PACK_UNLOADED, id:11})
        background       : outer_panel({size[24, 25]})
        resource_icon    : resource_icon({pos[16, 16], resource:RESOURCE_DEBEN})
        title            : text_center({pos[48, 16], size[px(24) - 64, 20], text[52, 15], font: FONT_LARGE_BLACK_ON_LIGHT})
        salary_ranks     : scrollable_list({
                                pos[16, 48]
                                size[22, 15]
                                view_items: 11
                                buttons_size_y: 20
                                buttons_margin_x: 4
                                buttons_margin_y: 12
                                text_padding_x: 0
                                text_padding_y: 0
                                draw_scrollbar_always: false
                                draw_paneling: true
                                onrender_item: set_salary_window_list_on_render_item
                                onclick_item: set_salary_window_list_on_click_item
                            })
        explanation_text : text({pos[16, 304], size[px(22), -1], wrap:px(22), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true})
        btn_cancel       : button({margin{centerx: -80, bottom: -40}, size[160, 20], text[13, 4], font: FONT_NORMAL_BLACK_ON_LIGHT, onclick: window_go_back})
    }
}

[es=(set_salary_window, init)]
function set_salary_window_init(window) {
    window.salary_ranks.clear()
    window.salary_ranks.readonly = city.mission_has_won
    var rank
    for (rank = 0; rank < 11; rank++) {
        window.salary_ranks.add_item("", rank)
    }

    if (!city.mission_has_won) {
        if (player.salary_rank <= city.player_rank) {
            window.explanation_text.text = __loc(52, 76)
        } else {
            window.explanation_text.text = __loc(52, 71)
        }
    } else {
        window.explanation_text.text = __loc(52, 77)
    }
}
