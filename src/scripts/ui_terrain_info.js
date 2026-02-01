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

terrain_road_info_window = {
    help_id           : 57 
	ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[28, 5], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 42], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

terrain_wall_info_window = {
    help_id           : 85 
    open_sounds       : [ "Wavs/wall.wav" ] 
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[139, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[139, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

terrain_plaza_info_window = {
    help_id           : 80 
    open_sounds       : [ ] 
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[137, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[137, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

terrain_orerock_info_window = {
    help_id           : 191 
    open_sounds       : [  "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ] 
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 26], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

terrain_rock_info_window = {
    help_id           : 191 
    open_sounds       : [ "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ] 
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 12], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

terrain_floodplain_info_window = {
    help_id           : 45 
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 29], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 55], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}