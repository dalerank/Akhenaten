log_info("akhenaten: ui_roadblock_info_window.js loaded")

[es=building_info_window]
info_window_roadblock {
    related_buildings [BUILDING_ROADBLOCK]
    ui : {
        background    : outer_panel({size: [29, 17] }),
        title         : text({pos: [0, 12], size: [px(28), 0], font: FONT_LARGE_BLACK_ON_LIGHT, align: "center"}),
        warning_text  : text({pos: [32, 56], wrap: px(27), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline: true}),
        orders        : button({
            margin: {left: 80, bottom: -34},
            size: [304, 20],
            text: "${98.5}",
            onclick_event: "open_orders_window"
        }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=(info_window_roadblock, init)]
function info_window_roadblock_on_init(window) {
    var b = city.get_building(window.bid)
    window.title.text = __loc(b.meta_text_id, 0)
    window.warning_text.text = __loc(b.meta_text_id, 1)
}

[es=(info_window_roadblock, open_orders_window)]
function info_window_roadblock_on_open_orders_window(window) {
    emit event_show_window{ id: "roadblock_orders_window" }
}
