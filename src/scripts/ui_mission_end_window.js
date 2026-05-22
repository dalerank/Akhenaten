log_info("akhenaten: ui mission end window started")

var INTERMEZZO_MISSION_BRIEFING = 0
var INTERMEZZO_FIRED = 1
var INTERMEZZO_WON = 2

var MISSION_END_STATE_WON = 0
var MISSION_END_STATE_LOST = 1

[es=window]
window_mission_won {
    pos: [(sw(0) - px(38))/2, (sh(0) - px(27))/2]
    draw_underlying: true
    ui {
        background          : outer_panel({size:[34, 18]})
        title               : text({pos:[0, 16], size:[px(34), 20], text:"${62.0}", align:"center", font: FONT_LARGE_BLACK_ON_LIGHT })
        description_panel   : inner_panel({pos:{x:32, y:40}, size:{w:30, h:8},
            ui : {
                culture_header      : text({pos:{x:30, y:10}, text:"${148.0} ${rating.culture}", font: FONT_NORMAL_WHITE_ON_DARK})
                prosperity_header   : text({pos:{x:30, y:30}, text:"${148.1} ${rating.prosperity}", font: FONT_NORMAL_WHITE_ON_DARK})
                monument_header     : text({pos:{x:30, y:50}, text:"${148.2} ${rating.monument}", font: FONT_NORMAL_WHITE_ON_DARK})
                treasury_header     : text({pos:{x:30, y:70}, text:"${148.3} ${city.treasury}", font: FONT_NORMAL_WHITE_ON_DARK})
                population_header   : text({pos:{x:30, y:90}, text:"${148.4} ${rating.kingdom}", font: FONT_NORMAL_WHITE_ON_DARK})
            }
        })
        subtitle            : text({pos:[32, 178], size:[px(32), -1], multiline:true, wrap:px(32), font: FONT_NORMAL_BLACK_ON_LIGHT })
        desc_header         : text({margin:{left:0, bottom:-40}, size:[px(32), 20], align:"center", text:"${13.1}", font: FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

[es=window]
window_mission_lost {
    pos: [(sw(0) - px(34))/2, (sh(0) - px(16))/2]
    draw_underlying: true
    ui {
        background          : outer_panel({size:[34, 16]})
        title               : text({pos:[0, 32], text:"${62.1}", font: FONT_LARGE_BLACK_ON_LIGHT, align:"center", size:[px(32), 20] })
        warning_text        : text({pos:[32, 72], text:"${62.16}", wrap:px(32), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })

        replay_mission      : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"${loc.replay_mission}" })
    }
}

[es=(window_mission_won, init)]
function window_mission_won_on_init(window) {
    var is_custom = scenario.scmode != e_scenario_normal
    var subtitle_id = is_custom ? 20 : scenario.campaign_scenario_id
    window.subtitle.text = __loc(147, subtitle_id)
}

[es=(window_mission_won, go_back)]
function window_mission_won_on_go_back(window) {
    __game_sound.music_stop()
    __game_sound.speech_stop()
    mission_end_advance_to_next_mission()
}

[es=(window_mission_lost, init)]
function window_mission_lost_on_init(window) {
    window.replay_mission.onclick = mission_end_replay_mission
}

function mission_end_replay_mission() {
    __ui_city_planner_reset()
    var is_custom = scenario.scmode != e_scenario_normal
    if (is_custom) {
        __game_load_savegame("autosave_replay.sav")
        ui.window_city_show()
    } else {
        widget_top_menu_clear_state()
        __game_load_mission(scenario.campaign_scenario_id, 1)
    }
}

function mission_end_advance_to_next_mission() {
    var rank = scenario.campaign_mission_rank
    var next_rank = rank + 1
    var completed_id = scenario.campaign_scenario_id
    var savings = city.kingdome.personal_savings
    var is_custom = scenario.scmode != e_scenario_normal

    var next_scenario_id = -1
    if (!is_custom && next_rank < 11) {
        next_scenario_id = __win_criteria.next_mission
        if (!next_scenario_id) {
            next_scenario_id = completed_id + 1
        }
    }

    if (!is_custom) {
        city.kingdome.campaign_carry_personal_savings = savings
    }

    emit event_mission_won { scenario_id: completed_id, next_scenario_id: next_scenario_id }

    scenario.campaign_mission_rank = next_rank
    city.kingdome.player_name = city.kingdome.campaign_player_name
    scenario.has_won = 0
    scenario.continue_months_left = 0
    scenario.continue_months_chosen = 0

    __game_undo_disable()
    city.current_overlay = OVERLAY_NONE
    city.previous_overlay = OVERLAY_NONE

    if (next_rank >= 11 || is_custom) {
        __game_show_main_menu()
        if (!is_custom) {
            __scenario_init()
            __scenario_set_campaign_rank(2)
        }
    } else {
        game_show_mission_choice(next_scenario_id)
    }
}

function mission_end_show(state) {
    __mouse_reset_up_state()

    if (state == MISSION_END_STATE_LOST) {
        __game_intermezzo_show(scenario.campaign_scenario_id, INTERMEZZO_FIRED, "mission_end_open_lost_dialog")
        return
    }

    if (scenario.hide_won_screen) {
        __game_intermezzo_show(scenario.campaign_scenario_id, INTERMEZZO_WON, "mission_end_open_won_dialog")
        return
    }

    var rank = scenario.campaign_mission_rank
    var is_custom = scenario.scmode != e_scenario_normal

    if (!is_custom && rank >= 10) {
        __game_victory_video_show("smk/win_game.smk", 400, 292, "mission_end_after_video")
        return
    }

    game_features.gameopt_victory_video = !game_features.gameopt_victory_video
    var file = game_features.gameopt_victory_video ? "smk/victory_balcony.smk" : "smk/victory_senate.smk"
    __game_victory_video_show(file, 400, 292, "mission_end_after_video")
}

function mission_end_after_video() {
    __game_intermezzo_show(scenario.campaign_scenario_id, INTERMEZZO_WON, "mission_end_open_won_dialog")
}

function mission_end_open_won_dialog() {
    emit event_show_window { id: "window_mission_won" }
}

function mission_end_open_lost_dialog() {
    emit event_show_window { id: "window_mission_lost" }
}
