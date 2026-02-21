log_info("akhenaten: ui burning ruin info window started")

[es=building_info_window]
info_window_burning_ruin {
    related_buildings [BUILDING_BURNING_RUIN]
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${111.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text  : text({pos: [0, 46], size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle      : text({pos: [32, 66], text:"${111.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=info_window_burning_ruin_init]
function info_window_burning_ruin_on_init(window) {
    var rubble_type = __map_rubble_building_type(window.bid)
    window.warning_text.text = __loc(41, rubble_type)
}