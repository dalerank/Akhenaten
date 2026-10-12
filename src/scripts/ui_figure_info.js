log_info("akhenaten: ui figure info started")

def_object_info {
    forbidden_figure_types [ FIGURE_NONE, FIGURE_EXPLOSION, FIGURE_MAP_FLAG, FIGURE_ARROW,
                             FIGURE_JAVELIN, FIGURE_BOLT, FIGURE_BALLISTA, FIGURE_CREATURE,
                             FIGURE_FISHING_POINT, FIGURE_FISHING_SPOT, FIGURE_SPEAR, FIGURE_CHARIOR_RACER
                           ]
}

function figure_info_window_sync_tab_selection(window) {
    for (var i = 0; i < __object_info_figure_count(); i++) {
        var btn = window["button_figure" + i]
        if (!btn) {
            break
        }
        btn.selected = (i == city.object_info.figure_selected_index)
    }
}

function figure_info_typename_with_home(f) {
    var home = f.home
    var home_name = (home && home.valid) ? home.name : ""
    if (!home_name) {
        return f.class_name
    }
    return f.class_name + " ( @Y" + home_name + "& )"
}

[es=(figure_info_window, window_info_background)]
function figure_info_window_on_window_info_background(window) {
    var f = city.get_figure(__object_info_figure_id())

    window.name.text = f.name
    window.typename.text = f.class_name

    figure_info_window_update_toolbar(window, f)
    figure_info_window_sync_tab_selection(window)
    figure_info_check_phrase(window)
}

function figure_info_window_update_toolbar(window, f) {
    if (!f.valid) {
        return
    }

    window.show_path.text = (f.draw_mode & e_figure_draw_routing) ? "P" : "p"
    var following = __figure_follow_enabled() && __figure_follow_figure_id() == f.id
     window.show_follow.text = following ? "F" : "f"

    var overlay = f.overlay
    window.show_overlay.enabled = (overlay != OVERLAY_NONE)
    window.show_overlay.text = (city.current_overlay == overlay) ? "V" : "v"
}

function figure_info_window_setup_tabs(window) {
    figure_info_window_sync_tab_selection(window)
    for (var i = 0; i < __object_info_figure_count(); i++) {
        var btn = window["button_figure" + i]
        if (!btn) {
            break
        }
        btn.texture_id = __figure_info_tab_texture(i)
    }
}

function figure_info_window_setup(window, figure_id) {
    figure_info_window_setup_tabs(window)

    var f = city.get_figure(figure_id)
    if (!f.valid) {
        return
    }

    // Prefer the figure's configured portrait; fall back to the type-ordered
    // group 25 slot, which the Cleopatra figures (102-109) never received art for.
    var tid = f.params.first_img("big_image")
    var img = get_image({ tid: tid })
    if (!img) {
        img = get_image({ pack: PACK_UNLOADED, id: 25, offset: f.type })
    }
    window.bigimage.image = img ? img.tid : 0
    window.phrase.text = ""
    f.setup_phrase()
    __figure_info_set_help(figure_id)
}

function figure_info_window_toggle_overlay(figure_id) {
    var f = city.get_figure(figure_id)
    if (!f.valid) {
        return
    }
    var overlay = f.overlay
    if (overlay == OVERLAY_NONE) {
        return
    }
    city.current_overlay = (city.current_overlay == overlay) ? OVERLAY_NONE : overlay
}

[es=ui_window]
figure_info_window {
    ui {
        background     : outer_panel({size [29, 22]})
        inner_panel    : inner_panel({pos [16, 40], size [27, 13] })
        border         : border({border:0, pos : [24, 102], size [px(26), 138] })
        bigimage       : image({pos [30, 108], pack:PACK_UNLOADED, id:25 })
        name           : text({pos [90, 108], text:"${figure.name}", font : FONT_LARGE_BLACK_ON_DARK })
        typename       : text({pos [92, 139], text:"${figure.class_name}", font : FONT_NORMAL_BLACK_ON_DARK })
        phrase         : text({pos [90, 160], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(21), multiline:true })

        button_figure0 : image_button({pos[60 * 0 + 27, 45], size[52, 52], border:true, param1:0, onclick_event:"select_figure" })
        button_figure1 : image_button({pos[60 * 1 + 27, 45], size[52, 52], border:true, param1:1, onclick_event:"select_figure" })
        button_figure2 : image_button({pos[60 * 2 + 27, 45], size[52, 52], border:true, param1:2, onclick_event:"select_figure" })
        button_figure3 : image_button({pos[60 * 3 + 27, 45], size[52, 52], border:true, param1:3, onclick_event:"select_figure" })
        button_figure4 : image_button({pos[60 * 4 + 27, 45], size[52, 52], border:true, param1:4, onclick_event:"select_figure" })
        button_figure5 : image_button({pos[60 * 5 + 27, 45], size[52, 52], border:true, param1:5, onclick_event:"select_figure" })
        button_figure6 : image_button({pos[60 * 6 + 27, 45], size[52, 52], border:true, param1:6, onclick_event:"select_figure" })

        button_help    : help_button({})
        button_close   : close_button({})

        show_path      : button({margin{right:-64, bottom:-40}, size[23, 23], onclick_event: "show_path"})
        show_overlay   : button({margin{right:-90, bottom:-40}, size[23, 23], onclick_event: "show_overlay"})
        show_follow    : button({margin{right:-116, bottom:-40}, size[23, 23], text:"F", tooltip:"#follow_walker", onclick_event: "show_follow"})
    }
}

[es=(figure_info_window, init)]
function figure_info_window_on_init(window) {
    figure_info_window_setup(window, window.figure_id)
}

[es=(figure_info_window, select_figure)]
function figure_info_window_on_select_figure(ev) {
    __object_info_select_figure(ev.param1)
}

[es=(figure_info_window, show_path)]
function figure_info_window_on_show_path(window) {
    var f = city.get_figure(__object_info_figure_id())
    if (!f.valid) {
        return
    }
    f.draw_mode = f.draw_mode ^ e_figure_draw_routing
}

[es=(figure_info_window, show_overlay)]
function figure_info_window_on_show_overlay(window) {
    figure_info_window_toggle_overlay(__object_info_figure_id())
}

[es=(figure_info_window, show_follow)]
function figure_info_window_on_show_follow(window) {
    __figure_follow_start(__object_info_figure_id())
}
