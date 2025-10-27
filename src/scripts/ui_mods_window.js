log_info("akhenaten: mods window started")

mods_window {
    ui {
        background   : outer_panel({size[40, 30]})
        title        : header({text:"Mods"
                               font:FONT_LARGE_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                               margin{top:20}})

        mods_panel : dummy({pos[16, 70], size[33, 21]}),
        bottom_text  : text({text[31, 1]
                             font:FONT_NORMAL_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                             margin{bottom:-35}})
    }
}

