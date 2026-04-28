log_info("akhenaten: ui lmission briefing window started")

var difficulty_levels = ["very_easy", "easy", "normal", "hard", "very_hard"]
function get_difficulty_label() {
    return "${loc.difficulty_" + difficulty_levels[game.difficulty] + "}"
}

mission_briefing_window {
    pos [(sw(0) - px(38))/2, (sh(0) - px(27))/2],
    ui {
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
        back             : image_button({pos[26, 428], size[31, 20], pack:PACK_GENERAL, id:90, offset:8, enabled: false})

        dec_difficulty   : image_button({pos[65, 428], size[17, 17], pack:PACK_GENERAL, id:212, offset:3, onclick: __game_decrease_difficulty })
        inc_difficulty   : image_button({pos[65 + 18, 428], size[17, 17], pack:PACK_GENERAL, id:212, offset:0, onclick: __game_increase_difficulty })

        tocity_label     : label({text{group:62, id:7}, margin{right:-140, bottom:0}, font : FONT_NORMAL_BLACK_ON_LIGHT })
        start_mission    : next_button({ margin{right:-40, bottom:-3}, onclick_event: "start_mission" })
    }
}

[es=(mission_briefing_window, start_mission)]
function mission_briefing_window_on_draw_foreground(window) {
    var is_review = __mission_briefing_is_review
    var scenario_id = __mission_briefing_scenario_id

    if (!is_review) {
        __game_load_mission(scenario_id, 1)
    }
    __game_sound.speech_stop()
    __game_sound.music_update(1)
    ui.window_city_show()

    city.mission.start_message_shown = true
}

[es=(mission_briefing_window, init)]
function mission_briefing_window_on_init(window) {
    var is_review = __mission_briefing_is_review
    var scenario_id = __mission_briefing_scenario_id
    var text_id = 200 + scenario_id

    window.dec_difficulty.enabled = !is_review
    window.inc_difficulty.enabled = !is_review

    window.title.text = __lang_message_title_text(text_id)
    window.subtitle.text = __lang_message_subtitle_text(text_id)
    window.description_text.text = __lang_message_content_text(text_id)

    var goals = ["goal_0", "goal_1", "goal_2", "goal_3", "goal_4", "goal_5"]
    var gi = 0
    function setup_goal(group, tid, value) {
        var el = window[goals[gi]]
        var enabled = (value > 0)
        el.enabled = enabled
        if (enabled) {
            el.text = __loc(group, tid) + ": " + value
            gi++
        }
    }

    setup_goal(62, 11, city.winning.population)
    setup_goal(29, 20 + city.winning.houselevel, city.winning.housing)
    setup_goal(62, 12, city.winning.culture)
    setup_goal(62, 13, city.winning.prosperity)
    setup_goal(62, 14, city.winning.monument)
    setup_goal(62, 15, city.winning.kingdom)

    var fork_scenario_id = game.mission_choice_open_scenario_id
    var src = mission_choice_config_root(fork_scenario_id)
    var has_choice = !is_review && fork_scenario_id > 0 && !!src && !!src.choice && src.choice.length > 0
    window.back.enabled = has_choice
    if (has_choice) {
        window.back.onclick = function() {
            __game_speech_stop()
            game_show_mission_choice(fork_scenario_id)
        }
    }
}
