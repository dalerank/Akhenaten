log_info("akhenaten: messages window started")

message_list_window {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(22))/2]
    read_icon : {pack:PACK_GENERAL, id:90, offset:14}
    num_messages_in_view : 12
    ui {
        background    : outer_panel({size:[30, 22]})
        title         : header({pos[10, 10], size[px(30), 20], text[63, 0], align:"center"})
        
        messages_area : inner_panel({pos[16, 42], size[26, 16]})
        message_row   : dummy({pos[0, 0], size[px(13), 20]})
        message_read_icon : dummy({pos[0, 0]})
        message_month : text({pos[42, 0]})
        message_year : text({pos[78, 0]})
        message_title : text({pos[190, 0], size[px(13), 20]})

        help_text     : text({margin{left:50, bottom:-45}, size[16 * 26 - 100, -1], text[63, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, multiline:true, wrap:16 * 26 - 100})
        empty_text    : text({margin{left:32, centery:-20}, size[16 * 26 - 48, -1], text[63, 1], enabled:false, font:FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:16 * 26 - 48})
        
        btnhelp       : help_button({})
        btnclose      : close_button({tooltip:"#exit_this_panel"})
    }
}