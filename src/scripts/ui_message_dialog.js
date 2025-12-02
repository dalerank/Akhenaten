log_info("akhenaten: message dialog window started")

message_dialog_window {
    pos [0, 0]
    help_id: ""
    
    ui {
        background : outer_panel({size: [30, 20], enabled: false})
        
        title : text({pos: [0, 14], size: [px(30), 20], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, enabled: false})
        
        content_panel : inner_panel({pos: [16, 48], size: [28, 16], enabled: false})
        content_text : text({pos: [24, 54], size: [px(28), px(16)], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, enabled: false})
        
        button_back : image_button({pos: [16, 0], size: [31, 20], pack: PACK_GENERAL, id: 90, offset: 8, enabled: false})
        button_close : image_button({pos: [0, 0], size: [24, 24], pack: GROUP_CONTEXT_ICONS, id: 4, enabled: false})
        button_help : image_button({pos: [0, 0], size: [18, 27], pack: GROUP_CONTEXT_ICONS, id: 0, enabled: false})
        button_advisor : image_button({pos: [0, 0], size: [27, 27], pack: GROUP_MESSAGE_ADVISOR_BUTTONS, id: 0, enabled: false})
        button_go_to_problem : image_button({pos: [0, 0], size: [27, 27], pack: GROUP_SIDEBAR_BUTTONS, id: 52, enabled: false})
        
        video_area : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        image_background : dummy({pos: [32, 28], size: [416, 312], enabled: false})
        
        // Bottom panel for video/image modes
        bottom_panel : outer_panel({pos: [32, 336], size: [26, 28], enabled: false})
        bottom_title : text({pos: [8, 414], size: [400, 20], align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, enabled: false})
        bottom_content : inner_panel({pos: [40, 344], size: [25, 6], enabled: false})
        bottom_text : text({pos: [48, 368], size: [384, 96], font: FONT_NORMAL_WHITE_ON_DARK, rich: true, enabled: false})
    }
}

