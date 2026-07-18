log_info("akhenaten: ui mission end window started")

var INTERMEZZO_MISSION_BRIEFING = 0
var INTERMEZZO_FIRED = 1
var INTERMEZZO_WON = 2

var MISSION_END_STATE_WON = 0
var MISSION_END_STATE_LOST = 1

var MISSION_WON_DIFFICULTY_KEYS = [
    "#difficulty_very_easy",
    "#difficulty_easy",
    "#difficulty_normal",
    "#difficulty_hard",
    "#difficulty_very_hard"
]

[es=window]
window_mission_won {
    pos: [(sw(0) - px(38))/2, (sh(0) - px(28))/2]
    draw_underlying: true
    ui {
        background          : outer_panel({size:[38, 28]})
        title               : text({pos:[0, 16], size:[px(38), 20], text:{group:62, id:0}, align:"center", font: FONT_LARGE_BLACK_ON_LIGHT })
        description_panel   : inner_panel({pos:{x:32, y:48}, size:{w:34, h:7}})
        victory_text        : text({pos:[48, 56], size:[px(32), px(6)], multiline:true, wrap:px(32), font: FONT_NORMAL_WHITE_ON_DARK })

        culture_line        : text({pos:[48, 180], text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        prosperity_line     : text({pos:[48, 200], text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        kingdom_line        : text({pos:[48, 220], text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        funds_line          : text({pos:[48, 240], text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        population_line     : text({pos:[48, 260], text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })

        monuments_header    : text({pos:[320, 180], text:{group:148, id:6}, font: FONT_NORMAL_BLACK_ON_LIGHT })
        monuments_list      : text({pos:[320, 200], size:[px(16), -1], multiline:true, wrap:px(16), text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })

        months_line         : text({pos:[0, 320], size:[px(38), 20], align:"center", text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        difficulty_line     : text({pos:[0, 340], size:[px(38), 20], align:"center", text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        score_line          : text({pos:[0, 360], size:[px(38), 20], align:"center", text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        compare_line        : text({pos:[32, 388], size:[px(34), -1], multiline:true, wrap:px(34), align:"center", text:"", font: FONT_NORMAL_BLACK_ON_LIGHT })
        continue_hint       : text({margin:{left:0, bottom:-40}, size:[px(38), 20], align:"center", text:{group:13, id:1}, font: FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

[es=window]
window_mission_lost {
    pos: [(sw(0) - px(34))/2, (sh(0) - px(16))/2]
    draw_underlying: true
    ui {
        background          : outer_panel({size:[34, 16]})
        title               : text({pos:[0, 32], text:{group:62, id:1}, font: FONT_LARGE_BLACK_ON_LIGHT, align:"center", size:[px(32), 20] })
        warning_text        : text({pos:[32, 72], text:{group:62, id:16}, wrap:px(32), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })

        replay_mission      : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"#replay_mission" })
    }
}

function mission_won_completion_months() {
    var years = game.simtime.year - scenario.start_year
    if (years < 0) {
        years = 0
    }
    return years * 12 + game.simtime.month + 1
}

function mission_won_calc_score(funds, population, culture, prosperity, kingdom, months, difficulty) {
    if (months < 1) {
        months = 1
    }
    var score = (difficulty + 1.0) / 3.0
        * ((funds / (months / 30.0))
           + population * 0.002 * (culture + prosperity + kingdom))
    if (score < 0) {
        score = 0
    }
    return score | 0
}

function mission_won_difficulty_label(diff) {
    if (diff < 0 || diff >= MISSION_WON_DIFFICULTY_KEYS.length) {
        diff = 2
    }
    return __loc(MISSION_WON_DIFFICULTY_KEYS[diff])
}

function mission_won_erected_monuments_text() {
    var n = __city_monuments_list_refresh()
    var names = []
    for (var i = 0; i < n; i++) {
        var bid = __city_monuments_list_id_at(i)
        if (!bid) {
            continue
        }
        var monument = city.get_monument(bid)
        if (!monument || monument.phase() != -1) {
            continue
        }
        var name = __building_display_name(bid)
        if (name && name.length > 0) {
            names.push(name)
        }
    }
    return names.join("\n")
}

function mission_won_compare_text(scenario_id, new_score) {
    if (!__game_mission_scenario_beaten(scenario_id)) {
        return ""
    }
    var prev_score = __game_player_scenario_record_score(scenario_id)
    if (new_score > prev_score) {
        return __loc(148, 12)
    }
    if (new_score < prev_score) {
        return __loc(148, 11)
    }
    return ""
}

[es=(window_mission_won, init)]
function window_mission_won_on_init(window) {
    __log_marker("window_show:window_mission_won")
    var is_custom = scenario.scmode != e_scenario_normal
    var subtitle_id = is_custom ? 53 : scenario.campaign_scenario_id
    window.victory_text.text = __loc(147, subtitle_id)

    var culture = city.rating.culture
    var prosperity = city.rating.prosperity
    var kingdom = city.rating.kingdom
    var funds = city.finance.treasury
    var population = city.population
    var months = mission_won_completion_months()
    var difficulty = game.difficulty
    var score = mission_won_calc_score(funds, population, culture, prosperity, kingdom, months, difficulty)

    // Win-screen labels match the original dialog (no "was"); group 298 is for score panels.
    window.culture_line.text = __loc("#mission_won_culture_rating") + " " + String(culture)
    window.prosperity_line.text = __loc("#mission_won_prosperity_rating") + " " + String(prosperity)
    window.kingdom_line.text = __loc("#mission_won_kingdom_rating") + " " + String(kingdom)
    window.funds_line.text = __loc(148, 5) + " " + String(funds)
    window.population_line.text = __loc("#mission_won_population") + " " + String(population)

    window.monuments_list.text = mission_won_erected_monuments_text()

    window.months_line.text = __loc(148, 7) + " " + String(months) + " " + __loc(148, 15)
    window.difficulty_line.text = __loc(148, 8) + " " + mission_won_difficulty_label(difficulty)
    window.score_line.text = __loc(148, 9) + " " + String(score)
    window.compare_line.text = mission_won_compare_text(scenario.campaign_scenario_id, score)
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

    if (scenario.scmode != e_scenario_custom_map) {
        city.kingdome.campaign_carry_personal_savings = savings
    }

    var next_scenario_id = -1
    if (mission_has_post_victory_choice(completed_id)) {
        next_scenario_id = completed_id
    } else {
        next_scenario_id = mission_end_compute_next_scenario_id(completed_id)
    }

    emit event_mission_won { scenario_id: completed_id, next_scenario_id: next_scenario_id }

    if (scenario.scmode != e_scenario_custom_map) {
        __game_player_record_mission_win(completed_id)
    }

    scenario.campaign_mission_rank = next_rank
    city.kingdome.player_name = city.kingdome.campaign_player_name
    scenario.has_won = 0
    scenario.continue_months_left = 0
    scenario.continue_months_chosen = 0

    __game_undo_disable()
    city.current_overlay = OVERLAY_NONE
    city.previous_overlay = OVERLAY_NONE

    if (next_scenario_id == -1) {
        emit event_show_main_menu{ play_intro: true }
        if (scenario.scmode != e_scenario_custom_map) {
            __scenario_init()
            scenario.campaign_mission_rank = 2
        }
    } else if (mission_has_post_victory_choice(completed_id)) {
        game_show_mission_choice(completed_id, completed_id)
    } else {
        game_show_mission_choice(next_scenario_id, completed_id)
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

    if (mission_end_compute_next_scenario_id(scenario.campaign_scenario_id) == -1
        && scenario.scmode != e_scenario_custom_map) {
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
