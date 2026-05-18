log_info("akhenaten: ui build menu started")

build_menu_widget = {
    ui : {
        item : dummy({size:[-1, 24]}),
    },

    btn_w_add : 128,
    btn_w_start_pos : [0, 110],
    btn_text_w_offset : [8, 3],
    btn_text_w_size : [176, 24],
    btn_w_cost_offset : -82,
    btn_w_tot_margin : 10,
    btn_w_tot_offset : 20,
    y_menu_offsets : [0, 322, 306, 274, 258, 226, 210, 178, 162,  130, 114, 82, 66, 34, 18,
                    -30, -46, -62, -78, -78, -94, -94, -110, -110, 0,   0,   0,  0,  0,  0],
}

[es=(build_menu_widget, draw_background)]
function build_menu_widget_draw_background(window) {
    __ui_window_city_draw_panels()
}
