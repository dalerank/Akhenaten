log_info("akhenaten: ui bazaar orders window started")

function bazaar_orders_window_accept_none() {
    city.get_bazaar(city.object_info.building_id).unaccept_all_goods()
}

function bazaar_orders_window_close() {
    __city_show_tile_info_for_object_info()
}

bazaar_orders_window {
    ui {
        background   : outer_panel({size[29, 17]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        orders_panel : inner_panel({pos[16, 42], size[27, 11] })
        accept_none  : button({pos[80, -1], size[300, 24], text:{group:99, id:7}, margin{bottom:-38}, onclick: bazaar_orders_window_accept_none })

        item_orders_column : dummy({margin{centerx:0}})
        item_icon_column : dummy({pos[25, 0]})
        item_name_column : dummy({pos[55, 0], font:FONT_NORMAL_WHITE_ON_DARK })
        item_row     : dummy({size[px(11), 20]})
        items_area   : dummy({pos[0, 50]})
        item_icon_column_2 : dummy({pos[px(29) - 40, 0]})

        button_help   : help_button({})
        button_close  : close_button({ onclick: bazaar_orders_window_close })
    }
}
