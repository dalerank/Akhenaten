log_info("akhenaten: ui send gift window started")

terrain_info_window = {
    ui : {
        background    : outer_panel({size: [29, 20]}),
        title         : text({pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

terrain_info_road {
    help_id           : 57
	ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[28, 5], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 42], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_road_init]
function terrain_info_road_on_init(window) {

}

terrain_info_wall = {
    help_id           : 85
    open_sounds       : [ "Wavs/wall.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[139, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[139, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_wall_init]
function terrain_info_wall_on_init(window) {

}

terrain_info_plaza = {
    help_id           : 80
    open_sounds       : [ ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[137, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[137, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_plaza_init]
function terrain_info_plaza_on_init(window) {

}

terrain_info_ore_rock = {
    help_id           : 191
    open_sounds       : [  "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 26], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_ore_rock_init]
function terrain_info_ore_rock_on_init(window) {

}

terrain_info_rock = {
    help_id           : 191
    open_sounds       : [ "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 12], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_rock_init]
function terrain_info_rock_on_init(window) {

}

terrain_info_floodplain {
    help_id           : 45
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 29], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 55], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_floodplain_init]
function terrain_info_floodplain_on_init(window) {

}

terrain_info_tree = {
    help_id           : 44
    open_sounds       : [ ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 11], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 43], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_tree_init]
function terrain_info_tree_on_init(window) {

}

terrain_info_rubble {
    open_sounds [ "wavs/fire.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], text:"${140.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text  : text({debug_tag:1, pos: [0, 46], text:"no_text", size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT })
        subtitle      : text({pos: [30, 76], text:"${140.1}", size: [px(26), -1], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=terrain_info_rubble_init]
function terrain_info_rubble_on_init(window) {
    var rubble_type = __map_rubble_building_type_at_grid(window.grid_offset)
    window.warning_text.text = __loc(41, rubble_type)
}