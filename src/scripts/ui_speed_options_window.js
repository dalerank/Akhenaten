log_info("akhenaten: ui speed options window started")

speed_options_window {
    pos [(sw(0) - px(20))/2, (sh(0) - px(14))/2]
    
    ui {
        background         : outer_panel({size[20, 14]})
        title              : header({pos[0, 16], size[px(20), 20], text[45, 0], align:"center"})
        
        game_speed_label   : text({text[45, 2], pos[32, 66], font: FONT_SMALL_PLAIN})
        game_speed_value   : text({pos[248, 66], font: FONT_SMALL_PLAIN})

        arrow_game_down    : arrowdown({pos[192, 60], tiny:false})
        arrow_game_up      : arrowup({pos[216, 60], tiny:false})
        
        scroll_speed_label : text({text[45, 3], pos[32, 102], font: FONT_SMALL_PLAIN})
        scroll_speed_value : text({pos[248, 102], font: FONT_SMALL_PLAIN})

        arrow_scroll_down  : arrowdown({pos[192, 96], tiny:false})
        arrow_scroll_up    : arrowup({pos[216, 96], tiny:false})
        
        btn_ok             : button({margin{centerx: -96, bottom: -34}, size[192, 24], text[45, 4], font: FONT_NORMAL_BLACK_ON_DARK})
        btn_cancel         : button({margin{centerx: -96, bottom: -60}, size[192, 24], text[45, 1], font: FONT_NORMAL_BLACK_ON_DARK})
    }
}
