log_info("akhenaten: ui lmission briefing window started")

mission_briefing_window = {
    pos: [(sw(0) - px(38))/2, (sh(0) - px(27))/2],
    ui : {
        background       : outer_panel({pos:[16, 32], size : {w:38, h:27} }),
        title            : text({pos:[32, 48], font : FONT_LARGE_BLACK_ON_LIGHT }),
        subtitle         : text({pos:[32, 78], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        objectives_panel : inner_panel({pos:[32, 96], size: {w:36, h:6} }),
        objectives_label : label({text : {group:62, id:10}, pos : {x:48, y:104},    font : FONT_NORMAL_WHITE_ON_DARK }),
        
        goal_0           : label({pos:[32  + 16, 90  + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_1           : label({pos:[288 + 16, 90  + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_2           : label({pos:[32  + 16, 112 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_3           : label({pos:[288 + 16, 112 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_4           : label({pos:[32  + 16, 134 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_5           : label({pos:[288 + 16, 134 + 32], body : {w:15, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        goal_immediate   : label({pos:[32 + 16,  136 + 32], body : {w:31, h:1}, font : FONT_NORMAL_YELLOW, enabled: false }),
        
        description_panel: inner_panel({pos : {x:32, y:200}, size: {w:33, h:14} }),
        description_text : text({
            pos: [40, 200], 
            size:[px(34), px(14)], 
            wrap:px(34), 
            text_margin: {left: 0, right: 30, top: 3},
            font : FONT_NORMAL_WHITE_ON_DARK, 
            font_link:FONT_NORMAL_YELLOW, 
            rich:true, 
            clip_area:true 
        }),
        difficulty_label : label({pos:[105, 433], size:[80, 14], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        back             : image_button({pos:[26, 428], size:[31, 20], pack:PACK_GENERAL, id:90, offset:8}),

        dec_difficulty   : image_button({pos:[65, 428], size:[17, 17], pack:PACK_GENERAL, id:212, offset:0 }),
        inc_difficulty   : image_button({pos:[65 + 18, 428], size:[17, 17], pack:PACK_GENERAL, id:212, offset:3}),

        tocity_label     : label({text : {group:62, id:7}, margin:{right:-140, bottom:0}, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        start_mission    : next_button({ margin:{right:-40, bottom:-3} }),
    }
}
