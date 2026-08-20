log_info("akhenaten: statue info window started")

[es=building_info_window]
info_window_statue {
    related_buildings [	BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE ]
    ui {
        background   : outer_panel({size[29, 17] }), // pos/size setup from code
        title        : text({pos[0, 16], text:"${building.name}", size[px(28), px(1)], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos[20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

        button_close : close_button({}),
        button_help  : help_button({}),
    }
}

[es=(info_window_statue, init)]
function info_window_statue_on_init(window) {

}

[es=building_info_window]
info_window_triumphal_arch {
    related_buildings [BUILDING_RESERVED_TRIUMPHAL_ARCH_56]
    help_id : "message_building_garden_plaze_statue"
    ui {
        background   : outer_panel({ size: [29, 14] })
        title        : text({ pos[0, 12], size[px(29), 13], text:[80, 2], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        describe     : text({ pos[32, 56], wrap:px(27), text:[80, 3], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        button_help  : help_button({})
        button_close : close_button({})
    }
}

[es=(info_window_triumphal_arch, init)]
function info_window_triumphal_arch_on_init(window) {
    __game_sound.speech_play("Wavs/statue.wav")
}
