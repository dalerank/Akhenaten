log_info("akhenaten: records window started")

records_window {
    ui {
        background   : outer_panel({size[40, 30]})
        title        : header({text[296, 0]
                               font:FONT_LARGE_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                               margin{top:20}})

        records_panel : dummy({pos[16, 70], size[33, 21]}),
        bottom_text  : text({text[31, 1]
                             font:FONT_NORMAL_BLACK_ON_LIGHT, size[px(40), 20], multiline:false, align:"center"
                             margin{bottom:-35}})
    }
}

