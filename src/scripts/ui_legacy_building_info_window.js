log_info("akhenaten: legacy native/mission info windows started")

function legacy_info_window_play(path) {
    __game_sound.speech_play(path)
}

[es=building_info_window]
info_window_native_hut {
    related_buildings [BUILDING_UNUSED_NATIVE_HUT_88]
    ui {
        background   : outer_panel({ size: [29, 14] })
        title        : text({ pos[0, 12], size[px(29), 13], text:[131, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        describe     : text({ pos[32, 56], wrap:px(27), text:[131, 1], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        button_help  : help_button({})
        button_close : close_button({})
    }
}

[es=(info_window_native_hut, init)]
function info_window_native_hut_on_init(window) {
    legacy_info_window_play("Wavs/empty_land.wav")
}

[es=building_info_window]
info_window_native_meeting {
    related_buildings [BUILDING_UNUSED_NATIVE_MEETING_89]
    ui {
        background   : outer_panel({ size: [29, 14] })
        title        : text({ pos[0, 12], size[px(29), 13], text:[132, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        describe     : text({ pos[32, 56], wrap:px(27), text:[132, 1], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        button_help  : help_button({})
        button_close : close_button({})
    }
}

[es=(info_window_native_meeting, init)]
function info_window_native_meeting_on_init(window) {
    legacy_info_window_play("Wavs/empty_land.wav")
}

[es=building_info_window]
info_window_native_crops {
    related_buildings [BUILDING_UNUSED_NATIVE_CROPS_93]
    ui {
        background   : outer_panel({ size: [29, 14] })
        title        : text({ pos[0, 12], size[px(29), 13], text:[133, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        describe     : text({ pos[32, 56], wrap:px(27), text:[133, 1], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        button_help  : help_button({})
        button_close : close_button({})
    }
}

[es=(info_window_native_crops, init)]
function info_window_native_crops_on_init(window) {
    legacy_info_window_play("Wavs/empty_land.wav")
}

[es=building_info_window]
info_window_mission_post {
    related_buildings [BUILDING_RESERVER_MISSION_POST_80]
    ui : baseui(building_info_window, {
        title        : text({ pos[0, 12], size[px(29), 13], text:[134, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        warning_text : text({ pos[32, 46], wrap:px(27), text:[134, 1], font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=(info_window_mission_post, init)]
function info_window_mission_post_on_init(window) {
    legacy_info_window_play("Wavs/mission.wav")
}
