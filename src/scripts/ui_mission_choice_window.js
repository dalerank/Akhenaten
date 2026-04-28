log_info("akhenaten: ui mission choice window started")

[console_command=update_mission_next]
function console_command_update_mission_next(args) {
    var scenario_id = parseInt((args && args[0]) || "0", 10)
    game_show_mission_choice(scenario_id)
}

function mission_choice_image_tid(img) {
    if (!img) {
        return 0
    }
    var off = img.offset
    if (off === undefined || off === null) {
        off = 0
    }
    var gi = get_image({pack: img.pack, id: img.id, offset: off})
    if (!gi || gi.tid === undefined) {
        return 0
    }
    return gi.tid
}

function mission_choice_xy(p) {
    if (!p) {
        return [0, 0]
    }
    if (p.x !== undefined && p.y !== undefined) {
        return [p.x, p.y]
    }
    if (p.length !== undefined && p.length >= 2) {
        return [p[0], p[1]]
    }
    return [0, 0]
}

function game_show_mission_choice(scenario_id) {
    if (!__game_mission_is_valid(scenario_id)) {
        __game_show_main_menu()
        return
    }
    var src = mission_choice_config_root(scenario_id)
    var nch = (src && src.choice) ? src.choice.length : 0
    if (!src || !src.choice || src.choice.length === 0) {
        log_info("mission_choice: no choice in config -> load_mission(" + scenario_id + ",1)")
        __game_load_mission(scenario_id, 1)
        return
    }
    game.mission_choice_open_scenario_id = scenario_id
    emit event_show_window{ id:"mission_choice_window" }
}

function mission_choice_config_root(scenario_id) {
    var name = "mission" + scenario_id
    try {
        var m = eval(name)
        return m
    } catch (e) {
        return undefined
    }
}

function mission_choice_mission_config_root() {
    return mission_choice_config_root(game.mission_choice_open_scenario_id)
}

function mission_choice_resolve_text(v) {
    if (v === undefined || v === null) {
        return ""
    }
    if (typeof v === "string") {
        return v
    }
    if (typeof v === "number") {
        return "" + v
    }
    if (v.length !== undefined && v.length >= 2 && typeof v[0] === "number") {
        return __loc(v[0], v[1])
    }
    return ""
}

[es=window]
mission_choice_window {
    pos [(sw(0) - 1024)/2, (sh(0) - 768)/2]
    ui {
        background    : image({pack:PACK_UNLOADED, id:12 })
        image1        : image({})
        image2        : image({})
        title         : text({pos[204, 548], font : FONT_LARGE_BLACK_ON_LIGHT })
        mission_name  : text({pos[214, 580], size[px(32), 20], wrap:px(32), text:"#ui_mission_choice_prompt"})

        point0        : image_button({})
        point1        : image_button({})
        point2        : image_button({})
        point3        : image_button({})
    }
}

[es=(mission_choice_window, init)]
function mission_choice_window_on_init(window) {
    var open_id = game.mission_choice_open_scenario_id
    var src = mission_choice_mission_config_root()
    if (!src) {
        return
    }
    if (!src.choice || src.choice.length === 0) {
        return
    }

    var tBg = mission_choice_image_tid(src.choice_background)
    var t1 = mission_choice_image_tid(src.choice_image1)

    window.background.image = mission_choice_image_tid(src.choice_background)
    window.image1.image = mission_choice_image_tid(src.choice_image1)
    window.image1.pos = mission_choice_xy(src.choice_image1_pos)
    window.image2.image = mission_choice_image_tid(src.choice_image2)
    window.image2.pos = mission_choice_xy(src.choice_image2_pos)
    window.title.text = mission_choice_resolve_text(src.choice_title)

    var n = src.choice.length
    var i = 0
    for (i = 0; i < n; i++) {
        var btn = window["point" + i]
        if (!btn) {
            break
        }
        var pt = src.choice[i]
        var tBtn = mission_choice_image_tid(pt.image)
        btn.image = mission_choice_image_tid(pt.image)
        btn.pos = mission_choice_xy(pt.pos)
        btn.tooltip = mission_choice_resolve_text(pt.tooltip)
        ;(function (point_btn, scenarioId) {
            point_btn.onclick = function () {
                __game_mission_branch_start(scenarioId)
            }
        })(btn, pt.id)
    }
}