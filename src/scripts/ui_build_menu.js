log_info("akhenaten: ui build menu started")

[es=modal_window]
build_menu_widget = {
    allow_rmb_goback : true

    ui : {
        background : dummy({size:[155, 200]})
        item : dummy({size:[-1, 24]})
    }

    selected_submenu: BUILDING_MENU_VACANT_HOUSE
    pending_submenu: BUILDING_MENU_VACANT_HOUSE

    btn_w_add : 128
    btn_w_start_pos : {x: 0, y: 110}
    btn_text_w_offset : {x: 8, y: 3}
    btn_text_w_size : {x: 176, y: 24}
    btn_w_cost_offset : -82
    btn_w_tot_margin : 10
    btn_w_tot_offset : 20
    y_menu_offsets : [0, 322, 306, 274, 258, 226, 210, 178, 162,  130, 114, 82, 66, 34, 18,
                      -30, -46, -62, -78, -78, -94, -94, -110, -110, 0,   0,   0,  0,  0,  0]
}

build_menu_widget.set_submenu = function(submenu) {
    if (build_menu_widget.selected_submenu == submenu) {
        return
    }
    emit event_build_menu_submenu_changed{ submenu: submenu }
}

build_menu_widget.init_menu = function(submenu) {
    build_menu_widget.set_submenu(submenu)
    emit event_city_building_mode{ value: BUILDING_NONE }

    building_menu_ctrl.update_temple_complexes()

    var submenu = build_menu_widget.selected_submenu
    for (var i = 0; i < building_menu.length; i++) {
        if (building_menu[i].id == submenu) {
            var anim = building_menu[i].anim
            emit event_building_change_mode{ pack: anim.pack, id: anim.id, offset: anim.offset }
        }
    }
}

build_menu_widget.show = function(submenu) {
    build_menu_widget.pending_submenu = submenu

    if (submenu == BUILDING_MENU_VACANT_HOUSE || submenu == BUILDING_MENU_CLEAR_LAND || submenu == BUILDING_MENU_ROAD) {
        build_menu_widget.init_menu(submenu)
        build_menu_widget.button_menu_item(0)
        return
    }

    window_show_by_id("build_menu_widget")
}

[es=(build_menu_widget, init)]
function build_menu_widget_init(window) {
    build_menu_widget.init_menu(build_menu_widget.pending_submenu)
}

[es=(build_menu_widget, go_back)]
function build_menu_widget_go_back(window) {
    build_menu_widget.set_submenu(0)
    emit event_city_building_mode{ value: BUILDING_NONE }
    ui.window_city_show()
}

[event=event_build_menu_submenu_changed]
function build_menu_widget_on_submenu_changed(ev) {
    build_menu_widget.selected_submenu = ev.submenu
}

[es=(build_menu_widget, ui_handle_mouse)]
function build_menu_widget_ui_handle_mouse(window) {
    __ui_widget_sidebar_city_handle_mouse_build_menu()
}

build_menu_widget.item_label = function(type) {
    var submenu = build_menu_widget.selected_submenu
    var is_all_button = (type == BUILDING_MENU_TEMPLES && submenu == BUILDING_MENU_TEMPLES)
                        || (type == BUILDING_MENU_TEMPLE_COMPLEX && submenu == BUILDING_MENU_LARGE_TEMPLES)

    if (is_all_button) {
        return __loc(52, 19)
    }

    var menu_text = __building_static_text(type, "build_menu_text")
    if (menu_text && menu_text.length > 0) {
        return menu_text
    }

    var title = __building_static_text(type, "info_title_id")
    if (title && title.length > 0) {
        return title
    }

    return __loc(28, type)
}

build_menu_widget.button_menu_item = function(item) {
    __ui_screen_city_clear_current_tile()
    var submenu = build_menu_widget.selected_submenu
    var type = building_menu_ctrl.item_type(submenu, item)
    if (__ui_building_is_unique_built(type)) {
        return
    }

    emit event_city_building_mode{ value: type }

    if (building_menu_ctrl.is_submenu(type)) {
        build_menu_widget.set_submenu(type)
        __ui_city_planner_reset()
    } else {
        ui.window_city_show()
    }
}

[es=(build_menu_widget, click_item)]
function build_menu_widget_click_item(window, ev) {
    build_menu_widget.button_menu_item(ev.item)
}

[es=(build_menu_widget, draw_background)]
function build_menu_widget_draw_background(window) {
    __ui_window_city_draw_panels()
}

[es=(build_menu_widget, ui_draw_foreground)]
function build_menu_widget_ui_draw_foreground(window) {
    __ui_window_city_draw()
    __ui_widget_sidebar_city_draw_foreground()

    var x_offset = __ui_widget_sidebar_city_offset_x()
    var btn_w_tot = 256 + build_menu_widget.btn_w_add
    var label_margin = btn_w_tot + build_menu_widget.btn_w_tot_margin
    var submenu = build_menu_widget.selected_submenu
    var num_items = building_menu_ctrl.count_items(submenu)
    var y_offset = build_menu_widget.y_menu_offsets[num_items]
    var item = window.item
    var item_index = -1

    for (var i = 0; i < num_items; i++) {
        item_index = building_menu_ctrl.next_index(submenu, item_index)
        var type = building_menu_ctrl.item_type(submenu, item_index)
        if (!building_menu_ctrl.is_visible(type)) {
            continue
        }

        var label_str = build_menu_widget.item_label(type)
        var btn_pos = {
            x: build_menu_widget.btn_w_start_pos.x + x_offset - label_margin,
            y: build_menu_widget.btn_w_start_pos.y + y_offset + item.size.y * i
        }
        var btn_size = {x: btn_w_tot, y: 20}
        var font = FONT_NORMAL_BLACK_ON_LIGHT
        var btn_flags = UiFlags_PanelSmall

        if (__ui_building_is_unique_built(type)) {
            font = FONT_NORMAL_BLACK_ON_DARK
            btn_flags = btn_flags | UiFlags_Darkened
        }

        var btn_state = __ui_draw_build_menu_button(btn_pos, btn_size, btn_flags)
        if (btn_state == 1) {
            build_menu_widget.button_menu_item(item_index)
        }
        if (btn_state == 2) {
            font = FONT_NORMAL_BLACK_ON_DARK
        }

        __ui_draw_label_ex(label_str, [btn_pos.x + build_menu_widget.btn_text_w_offset.x, btn_pos.y + build_menu_widget.btn_text_w_offset.y],
            font, UiFlags_None, build_menu_widget.btn_text_w_size.x)

        var cost = (type == BUILDING_MENU_FORTS) ? 0 : __building_static_cost(type)
        if (cost > 0) {
            var cost_x = x_offset + build_menu_widget.btn_w_cost_offset - build_menu_widget.btn_w_tot_offset
            var cost_y = y_offset + build_menu_widget.btn_w_start_pos.y + build_menu_widget.btn_text_w_offset.y + item.size.y * i
            __ui_text_abs("" + cost + " " + __loc(6, 0), {x: cost_x, y: cost_y}, font)
        }
    }
}

ui.window_build_menu_show = build_menu_widget.show
