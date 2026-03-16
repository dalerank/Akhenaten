log_info("akhenaten: mods window started")

function mods_window_on_double_click(p) {
    if (!p || !p.text) return
    var modId = p.text
    if (!mods.downloaded(modId)) {
        if (mods.download_progress(modId) === 0)
            mods.download_mod_async(modId)
    } else {
        mods.toggle(modId)
        mods.remount()
    }
}

function mods_window_on_render_item(p) {
    var prefix, name
    if (!mods.downloaded(p.text)) {
        var progress = mods.download_progress(p.text)
        prefix = progress > 0 ? "[" + progress + "] " : "[n/a] "
        name = mods.display_name(p.text)
        if (progress > 0) {
            var num_points = Math.floor((__game_frame() % 90) / 30)
            for (var i = 0; i < num_points; i++) {
                name += "."
            }
        }
    } else {
        prefix = "[" + (mods.enabled(p.text) ? "ON" : "OFF") + "] "
        name = mods.display_name(p.text)
    }

    ui.label(prefix + name, { x: p.x, y: p.y }, p.font)
}

mods_window {
    pos: [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
    allow_rmb_goback : true
    ui {
        background_image : background({pack:PACK_UNLOADED, id:9})
        background     : outer_panel({size[40, 30]})
        title          : header({text:"Mods"
                               font:FONT_LARGE_BLACK_ON_LIGHT, size[px(40), 20]
                               multiline:false, align:"center"
                               margin{top:20}})

        unpack_scripts : large_button({ size[156, 25]
                                        text:"Unpack scripts"
                                        margin{right:-156, top:20}
                                        onclick: __window_mods_unpack_scripts
                                      })

        refresh_mods : large_button({ size[156, 25]
                                      text:"Check on github"
                                      margin{right:-156, top:44}
                                      onclick: __window_mods_refresh_available_list
                                    })

        mods         : scrollable_list({pos[16, 75], size[36, 23], view_items:11,
                                        draw_scrollbar_always:true
                                        onrender_item: mods_window_on_render_item
                                        ondoubleclick_item: mods_window_on_double_click })

        bottom_text  : text({text:"Right click to exit, double click to toggle mod"
                             font:FONT_NORMAL_BLACK_ON_LIGHT, size[px(40), 20]
                             multiline:false
                             align:"center"
                             margin{bottom:-35}})
    }
}

[es=(mods_window, init)]
function mods_window_on_init(window) {
    var n = mods.count()
    window.mods.clear()
    for (var i = 0; i < n; i++) {
        window.mods.add_item(mods.name(i))
    }
}
