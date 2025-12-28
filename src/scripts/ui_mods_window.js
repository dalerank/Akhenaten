log_info("akhenaten: mods window started")

mods_window {
    pos: [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
    allow_rmb_goback : true
    ui {
        background   : outer_panel({size[40, 30]})
        title        : header({text:"Mods"
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

        mods         : scrollable_list({pos[16, 75], size[36, 23], view_items:11, draw_scrollbar_always:true })
        bottom_text  : text({text:"Right click to exit, double click to toggle mod"
                             font:FONT_NORMAL_BLACK_ON_LIGHT, size[px(40), 20]
                             multiline:false
                             align:"center"
                             margin{bottom:-35}})
    }
}
