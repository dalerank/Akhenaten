log_info("akhenaten: ui lmission briefing window started")

var difficulty_levels = ["very_easy", "easy", "normal", "hard", "very_hard"]
function get_difficulty_label() {
    return "${loc.difficulty_" + difficulty_levels[game.difficulty] + "}"
}

function mission_briefing_ironwill_checked() {
    return game_features.gameopt_ironwill === true
}

function mission_briefing_splash_tid() {
    var offset = 1
    if (scenario.scmode != e_scenario_custom_map && scenario.campaign_scenario_id >= 20) {
        offset = 2
    }
    var gi = get_image({pack: PACK_UNLOADED, id: 18, offset: offset})
    return (gi && gi.tid !== undefined) ? gi.tid : 0
}

function mission_briefing_show(scenario_id, is_review) {
    game.mission_briefing_scenario_id = scenario_id
    game.mission_briefing_is_review = !!is_review
    emit event_show_window{ id: "mission_briefing_window" }
}

[es=window]
mission_briefing_window {
    pos [(sw(0) - px(38))/2, (sh(0) - px(27))/2]

    ui {
        splash           : image({pos[(px(38) - 1024)/2, (px(27) - 768)/2], pack:PACK_UNLOADED, id:18, offset:1 })
        background       : outer_panel({pos[16, 32], size{w:38, h:27} })
        title            : text({pos[32, 48], font : FONT_LARGE_BLACK_ON_LIGHT })
        subtitle         : text({pos[32, 78], font : FONT_NORMAL_BLACK_ON_LIGHT })
        objectives_panel : inner_panel({pos[32, 96], size{w:36, h:6} })
        objectives_label : label({text{group:62, id:10}, pos{x:48, y:104},    font : FONT_NORMAL_WHITE_ON_DARK })

        goal_0           : label({pos[32  + 16, 90  + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_1           : label({pos[288 + 16, 90  + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_2           : label({pos[32  + 16, 112 + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_3           : label({pos[288 + 16, 112 + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_4           : label({pos[32  + 16, 134 + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_5           : label({pos[288 + 16, 134 + 32], body{w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })
        goal_immediate   : label({pos[32 + 16,  136 + 32], body{w:31, h:1}, font : FONT_NORMAL_YELLOW, enabled: false })

        description_panel: inner_panel({pos{x:32, y:200}, size{w:33, h:14} })
        description_text : text({
            pos[40, 200]
            size[px(34), px(14)]
            wrap : px(34)
            text_margin {left: 0, right: 30, top: 3}
            font : FONT_NORMAL_WHITE_ON_DARK
            font_link:FONT_NORMAL_YELLOW
            rich : true
            clip_area : true
        })

        difficulty_label : label({pos[105, 433], size[80, 14], font : FONT_NORMAL_BLACK_ON_LIGHT, textfn: get_difficulty_label })
        back             : image_button({pos[26, 428], size[31, 20], pack:PACK_GENERAL, id:90, offset:8, enabled: false, onclick_event: "go_back"})

        dec_difficulty   : image_button({pos[65, 428], size[17, 17], pack:PACK_GENERAL, id:212, offset:3, onclick_event: "dec_diff" })
        inc_difficulty   : image_button({pos[65 + 18, 428], size[17, 17], pack:PACK_GENERAL, id:212, offset:0, onclick_event: "inc_diff" })

        // Ironwill: set at mission start only (locked while reviewing / mid-run).
        ironwill_check   : checkbox({pos[200, 428], checkedfn: mission_briefing_ironwill_checked, onclick_event: "toggle_ironwill" })
        ironwill_label   : label({pos[226, 433], size[100, 14], font : FONT_NORMAL_BLACK_ON_LIGHT, text: "#ironwill_briefing_label" })

        tocity_label     : label({text{group:62, id:7}, margin{right:-140, bottom:0}, font : FONT_NORMAL_BLACK_ON_LIGHT })
        start_mission    : next_button({ margin{right:-40, bottom:-3}, onclick_event: "start_mission" })
    }
}

[event=event_mission_briefing_show_after_load]
function mission_briefing_on_show_after_load(ev) {
    mission_briefing_show(ev.scenario_id, false)
}

[es=(mission_briefing_window, start_mission)]
function mission_briefing_window_on_start_mission(window) {
    game_mission_options_locked = true
    __game_sound.speech_stop()
    __game_sound.music_update(1)
    ui.window_city_show()
}

[es=(mission_briefing_window, go_back)]
function mission_briefing_window_on_go_back(window) {
    var fork_scenario_id = game.mission_choice_open_scenario_id
    if (!(fork_scenario_id > 0)) {
        return
    }
    __game_sound.speech_stop()
    game_show_mission_choice(fork_scenario_id)
}

[es=(mission_briefing_window, dec_diff)]
function mission_briefing_window_on_dec_diff(window) {
    game_decrease_difficulty_if_allowed()
}

[es=(mission_briefing_window, inc_diff)]
function mission_briefing_window_on_inc_diff(window) {
    game_increase_difficulty_if_allowed()
}

[es=(mission_briefing_window, toggle_ironwill)]
function mission_briefing_window_on_toggle_ironwill(window) {
    if (game.mission_briefing_is_review || game_mission_options_locked) {
        return
    }
    game_features.gameopt_ironwill = !game_features.gameopt_ironwill
}

[es=(mission_briefing_window, init)]
function mission_briefing_window_on_init(window) {
    var scenario_id = game.mission_briefing_scenario_id
    var is_review = game.mission_briefing_is_review
    var text_id = 200 + scenario_id

    window.splash.image = mission_briefing_splash_tid()

    __game_sound.music_stop()
    __game_sound.speech_stop()
    var cfg = get_mission_config(scenario_id)
    var briefing = cfg && cfg.sounds && cfg.sounds.briefing
    if (briefing) {
        __game_sound.speech_play(briefing)
    }

    if (!is_review) {
        game_mission_options_locked = false
    }

    var can_edit_options = !is_review && !game_mission_options_locked
    window.dec_difficulty.enabled = can_edit_options
    window.inc_difficulty.enabled = can_edit_options
    window.ironwill_check.enabled = true
    window.ironwill_check.readonly = !can_edit_options
    window.ironwill_check.darkened = can_edit_options ? 0 : 1

    var city_title = __lang_message_title_text(text_id)
    window.title.text = city_title
    window.subtitle.text = __lang_message_subtitle_text(text_id)
    window.description_text.text = __lang_message_content_text(text_id)

    if (!is_review) {
        __discord_rpc_set_activity(city_title, "")
    }

    var goals = ["goal_0", "goal_1", "goal_2", "goal_3", "goal_4", "goal_5"]
    var gi = 0
    var i
    for (i = 0; i < goals.length; i++) {
        window[goals[i]].enabled = false
        window[goals[i]].text = ""
    }
    function setup_goal(group, tid, value) {
        if (!(value > 0) || gi >= goals.length) {
            return
        }
        var el = window[goals[gi]]
        el.enabled = true
        el.text = __loc(group, tid) + ": " + value
        gi++
    }

    // scenario.*_goal already returns 0 when the criterion is disabled.
    setup_goal(62, 11, scenario.population_goal)
    if (scenario.housing_count_goal > 0 && scenario.housing_level_goal > 0) {
        setup_goal(29, 20 + scenario.housing_level_goal, scenario.housing_count_goal)
    }
    setup_goal(62, 12, scenario.culture_goal)
    setup_goal(62, 13, scenario.prosperity_goal)
    setup_goal(62, 14, scenario.monuments_goal)
    setup_goal(62, 15, scenario.kingdom_goal)

    var goal_tooltip_text = (cfg && cfg.goal_tooltip) ? cfg.goal_tooltip() : ""
    window.goal_immediate.enabled = !!goal_tooltip_text
    window.goal_immediate.text = goal_tooltip_text

    var fork_scenario_id = game.mission_choice_open_scenario_id
    var src = get_mission_config(fork_scenario_id)
    var has_choice = !is_review && fork_scenario_id > 0 && !!src && !!src.choice && src.choice.length > 0
    window.back.enabled = has_choice
}
