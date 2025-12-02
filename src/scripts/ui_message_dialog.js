log_info("akhenaten: message dialog window started")

// General message dialog (MESSAGE_TYPE_GENERAL, TYPE_MANUAL, TYPE_ABOUT, TYPE_MISSION)
message_dialog_window_general {
    pos [0, 0]
    help_id: ""
    
    ui {
        background : outer_panel({size: [30, 20], enabled: false})
        
        title         : text({pos: [0, 14], size: [px(30), 20], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, enabled: false})
        subtitle      : text({pos: [0, 0], size: [px(30), 20], font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})
        
        content_panel : inner_panel({pos: [16, 48], size: [28, 16], enabled: false})
        content_text  : text({pos: [24, 54], size: [px(28), px(16)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, enabled: false})
        
        button_help   : help_button({})
        button_close  : close_button({})

        button_help    : image_button({pos: [0, 0], size: [18, 27], pack: GROUP_CONTEXT_ICONS, id: 0, enabled: false})
        button_advisor : image_button({pos: [0, 0], size: [27, 27], pack: GROUP_MESSAGE_ADVISOR_BUTTONS, id: 0, enabled: false})

        
        video_area       : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        image_background : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        
        // Bottom panel for video/image modes
        bottom_panel    : outer_panel({pos: [32, 336], size: [26, 28], enabled: false})
        bottom_title    : text({pos: [8, 414], size: [400, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})
        bottom_content  : inner_panel({pos: [40, 344], size: [25, 6], enabled: false})
        bottom_text     : text({pos: [48, 368], size: [384, 96], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, enabled: false})
    }
}

// Disaster message dialog (MESSAGE_TYPE_DISASTER)
message_dialog_window_disaster {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {
        button_go_to_problem : image_button({pos: [0, 0], size: [27, 27], pack: GROUP_SIDEBAR_BUTTONS, id: 52, enabled: false})
    })
}

// Imperial message dialog (MESSAGE_TYPE_IMPERIAL)
message_dialog_window_imperial {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {

    })
}

// Emigration message dialog (MESSAGE_TYPE_EMIGRATION)
message_dialog_window_emigration {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {

    })
}

// Tutorial message dialog (MESSAGE_TYPE_TUTORIAL)
message_dialog_window_tutorial {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {

    })
}

// Trade change message dialog (MESSAGE_TYPE_TRADE_CHANGE)
message_dialog_window_trade_change {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {

    })
}

// Price change message dialog (MESSAGE_TYPE_PRICE_CHANGE)
message_dialog_window_price_change {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {

    })
}

// Invasion message dialog (MESSAGE_TYPE_INVASION)
message_dialog_window_invasion {
    pos [0, 0]
    help_id: ""
    
    ui :_baseui(message_dialog_window_general, {
        button_go_to_problem : image_button({pos: [0, 0], size: [27, 27], pack: GROUP_SIDEBAR_BUTTONS, id: 52, enabled: false})
    })
}

