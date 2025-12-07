log_info("akhenaten: message dialog window started")

// General message dialog (MESSAGE_TYPE_GENERAL, TYPE_MANUAL, TYPE_ABOUT, TYPE_MISSION)
message_dialog_window_general {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui {
        background     : outer_panel({size: [30, 20]})
        
        title          : text({pos: [0, 14], size: [px(30), 20], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT})
        subtitle       : text({pos: [0, 0], size: [px(30), 20], font: FONT_NORMAL_BLACK_ON_LIGHT})
        
        content_panel  : inner_panel({pos[16, 48], size[28, 14]})
        content_text   : text({pos[16, 48], size[px(28), px(14)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, clip_area: true})
        
        button_help    : help_button({})
        button_close   : close_button({})

        button_advisor : image_button({pos: [0, 0], size: [27, 27], pack:PACK_GENERAL, id:106, enabled: false})
        
        video_area     : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        image_background : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        
        // Bottom panel for video/image modes
        bottom_panel   : outer_panel({pos: [32, 336], size: [26, 28], enabled: false})
        bottom_title   : text({pos: [8, 414], size: [400, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})
        bottom_content : inner_panel({pos: [40, 344], size: [25, 6], enabled: false})
        bottom_text    : text({pos: [48, 368], size: [384, 96], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, enabled: false})
    }
}

// Disaster message dialog (MESSAGE_TYPE_DISASTER)
message_dialog_window_disaster {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui : __baseui(message_dialog_window_general, {
        content_panel  : inner_panel({pos: [16, 48], size: [28, 13]})
        content_text   : text({pos: [24, 54], size: [px(28), px(34)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, clip_area: true})
        
        button_go_to_problem : image_button({ margin:{ bottom:-60, centerx:-87 }, size[27, 27], pack:PACK_GENERAL, id:136, offset:17*3+1  })
        button_go_to_problem_text : text({ margin:{ bottom:-40, centerx:-40 }, size[-1, 20], font: FONT_NORMAL_BLACK_ON_LIGHT, text: "#goto_site_of_event"})
    })
}

// Imperial message dialog (MESSAGE_TYPE_IMPERIAL)
message_dialog_window_imperial {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui : __baseui(message_dialog_window_general, {
        content_panel  : inner_panel({pos[16, 48], size[28, 14]}),
        content_text   : text({pos[24, 54], size[px(28), px(14)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, clip_area: true})
    })
}

// Emigration message dialog (MESSAGE_TYPE_EMIGRATION)
message_dialog_window_emigration {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {

    })
}

// Tutorial message dialog (MESSAGE_TYPE_TUTORIAL)
message_dialog_window_tutorial {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {

    })
}

// Trade change message dialog (MESSAGE_TYPE_TRADE_CHANGE)
message_dialog_window_trade_change {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {

    })
}

// Price change message dialog (MESSAGE_TYPE_PRICE_CHANGE)
message_dialog_window_price_change {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {

    })
}

// Invasion message dialog (MESSAGE_TYPE_INVASION)
message_dialog_window_invasion {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {
        button_go_to_problem : image_button({pos: [0, 0], size: [27, 27], pack:PACK_GENERAL, id:136, enabled: false})
    })
}

// God message dialog (messages from gods)
message_dialog_window_god {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(28))/2]
    help_id: ""

    god_images {
        osiris { pack:PACK_UNLOADED, id:16, offset:18 }
        ra     { pack:PACK_UNLOADED, id:16, offset:19 }
        seth   { pack:PACK_UNLOADED, id:16, offset:20 }
        bast   { pack:PACK_UNLOADED, id:16, offset:21 }
        ptah   { pack:PACK_UNLOADED, id:16, offset:22 }
    }
    
    ui : __baseui(message_dialog_window_general, {
        background     : outer_panel({size: [30, 28]}) 
        title          : text({margin{ bottom:-36 }, size [px(30), 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT})
        content_panel  : inner_panel({ margin{ left:8, bottom:-px(14) }, size [29, 11]})
        god_image_area : dummy({ margin{ top:px(2) }, size [px(29), px(10)]})
        content_text   : text({ margin{ left:16, bottom:-px(13) }, size [px(28), px(12)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, clip_area: true})
    })
}

// Image message dialog (messages with background images)
message_dialog_window_image {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(20))/2]
    help_id: ""
    
    ui :__baseui(message_dialog_window_general, {

    })
}

