log_info("akhenaten: ui config started")

uioptions = {
    resource_icons  : {pack:PACK_EXPANSION, id:3}
    advisor_icons   : {pack:PACK_GENERAL, id:128, offset:0}
    arrow_button_tiny_down : {pack:PACK_GENERAL, id:212, offset:0}
    arrow_button_tiny_up : {pack:PACK_GENERAL, id:212, offset:3}
    arrow_button_down : {pack:PACK_UNLOADED, id:0, offset:18}
    arrow_button_up : {pack:PACK_UNLOADED, id:0, offset:16}
}

build_menu_widget = {
    ui : {
        item : dummy({size:[-1, 24]}),
    },

    btn_w_add : 128,
    btn_w_start_pos : [0, 110],
    btn_text_w_offset : [0, 3],
    btn_text_w_size : [176, 24],
    btn_w_cost_offset : -82,
    btn_w_tot_margin : 10,
    btn_w_tot_offset : 20,
    y_menu_offsets : [0, 322, 306, 274, 258, 226, 210, 178, 162,  130, 114, 82, 66, 34, 18,
                    -30, -46, -62, -78, -78, -94, -94, -110, -110, 0,   0,   0,  0,  0,  0],
}

trade_prices_window = {
    pos: [(sw(0) - px(56))/2, (sh(0) - px(11))/2],
    next_row_offset : [0, 90], 
    next_item_offset : [42, 0], 
    receive_offset : [0, 50], 
    buyer_offset : [0, 30], 
    next : 18,
    ui : {
        background    : outer_panel({pos:[0, 0], size:[56, 16]}),
        title               : text_center({pos:[0, 12], size:[px(56), 20], text:[54, 21], font : FONT_LARGE_BLACK_ON_LIGHT }),
    
        items                : dummy({pos:[156, 44]}),
        item_button      : dummy({pos:[-7, -7], size:[38, 74]}),

        buyers_pay1      : text({text:[54, 22], pos:[26, 72], font: FONT_NORMAL_BLACK_ON_LIGHT}),
        sellers_receive1 : text({text:[54, 23], pos:[26, 92], font:FONT_NORMAL_BLACK_ON_LIGHT}),

        buyers_pay2      : text({text:[54, 22], pos:[26, 162], font: FONT_NORMAL_BLACK_ON_LIGHT}),
        sellers_receive2 : text({text:[54, 23], pos:[26, 182], font:FONT_NORMAL_BLACK_ON_LIGHT}),

        back          : text_center({pos:[13, -1], margin:{bottom:-35}, text:[13, 1], size:[px(56), 20], font:FONT_NORMAL_BLACK_ON_LIGHT }),
    }
}

display_options_window = {
    pos: [(sw(0) - px(24))/2, (sh(0) - px(21))/2],
    ui : {
        background  : outer_panel({size : [24, 21] }),
        title           : header({pos:[10, 10], size:[px(24), 20], text:[42, 0], align:"center"}),
        
        btnfullscreen : button({pos:[16, 46], size:[224, 20] }),
        videodriver : text({pos:[px(24)/2 + 60, 50]}),

        resolutions : dummy({pos:[16, 70]}),

        save_changes: text({margin:{left:px(24)/2 - 80, bottom:-35}, text:[43, 5]}),
        btnok           : ok_button({margin:{left:px(24)/2 + 10, bottom:-40}}), 
        btncancel   : cancel_button({margin:{left:px(24)/2 + 60, bottom:-40}}), 
  } 
}

window_dinasty_menu = {
    pos: [(sw(0) - px(24))/2, (sh(0) - px(21))/2]
    ui : {
        background_image: background({pack:PACK_UNLOADED, id:31})
        background      : outer_panel({size: [24, 19]})

        title       : text_center({pos:[0, 20], size:[px(24), 20], font:FONT_LARGE_BLACK_ON_LIGHT})
        btnresume   : button({margin:{centerx: -135, top: 40 + 1 * 40}, size:[270, 25], text:[293, 5], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btnexplore  : button({margin:{centerx: -135, top: 40 + 2 * 40}, size:[270, 25], text:[293, 6], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btnload     : button({margin:{centerx: -135, top: 40 + 3 * 40}, size:[270, 25], text:[293, 2], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btncustom   : button({margin:{centerx: -135, top: 40 + 4 * 40}, size:[270, 25], text:[293, 3], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btnback     : button({margin:{centerx: -135, top: 40 + 5 * 40}, size:[270, 25], text:[293, 4], font:FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

window_mission_end = {
    pos: [(sw(0) - px(38))/2, (sh(0) - px(27))/2],
    ui : {
        dummy : dummy({})
    }
}

window_mission_won = {
    pos: [(sw(0) - px(38))/2, (sh(0) - px(27))/2],
    ui : {
        background      : outer_panel({size:[34, 18]}),
      title                 : text({pos:[0, 16], size:[px(34), 20], text:"${62.0}", align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
        description_panel: inner_panel({pos : {x:32, y:40}, size: {w:30, h:8},
            ui : {
                culture_header      : text({pos:{x:30, y:10}, text:"${148.0} ${rating.culture}", font : FONT_NORMAL_WHITE_ON_DARK}),
                prosperity_header : text({pos:{x:30, y:30}, text:"${148.1} ${rating.prosperity}", font : FONT_NORMAL_WHITE_ON_DARK}),
                monument_header     : text({pos:{x:30, y:50}, text:"${148.2} ${rating.monument}", font : FONT_NORMAL_WHITE_ON_DARK}),
                treasury_header     : text({pos:{x:30, y:70}, text:"${148.3} ${city.treasury}", font : FONT_NORMAL_WHITE_ON_DARK}),
                population_header   : text({pos:{x:30, y:90}, text:"${148.4} ${rating.kingdom}", font : FONT_NORMAL_WHITE_ON_DARK}),
            }
        }),
        subtitle            : text({pos:[32, 178], text:"${147.21}", size:[px(32), -1], multiline:true, wrap:px(32), font : FONT_NORMAL_BLACK_ON_LIGHT }),
        desc_header         : text({margin:{left:0, bottom:-40}, size:[px(32), 20], align:"center", text:"${13.1}", font : FONT_NORMAL_BLACK_ON_LIGHT}),
    }
}

window_mission_lost = {
    pos: [(sw(0) - px(34))/2, (sh(0) - px(16))/2],
    ui : {
        background      : outer_panel({size:[34, 16]}),
        title               : text({pos:[0, 32], text:"${62.1}", font : FONT_LARGE_BLACK_ON_LIGHT, align:"center", size:[px(32), 20] }),
        warning_text    : text({pos:[32, 72], text:"${62.16}", wrap:px(32), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

        replay_mission  : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"${loc.replay_mission}"}),  
    }
}

mission_choice_window = {
    pos: [(sw(0) - 1024)/2, (sh(0) - 768)/2],
    ui : {
        background       : image({pack:PACK_UNLOADED, id:12 }),
        image1                   : image({}),
        image2                   : image({}),
        title                        : text({pos:[204, 548], font : FONT_LARGE_BLACK_ON_LIGHT }),
        mission_name         : text({pos:[214, 580], size:[px(32), 20], wrap:px(32), text:"${144.0}"}),

        point0                   : image_button({}),
        point1                   : image_button({}),
        point2                   : image_button({}),
        point3                   : image_button({}),
    }
}

roadblock_info_window = {
    ui : {
        background      : outer_panel({size: [29, 17]}),
        title           : text({pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        button_help     : help_button({}),
        button_close    : close_button({}),
    }
}

granary_orders_window = {
    ui : {
        background    : outer_panel({size: [29, 17]}),
        title         : text({pos: [0, 12], size: [px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        orders_panel  : inner_panel({pos : [16, 42], size: [27, 10] }),
        button_help   : image_button({margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 }),
        button_close  : image_button({margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 }),
        empty_all     : button({pos:[80, -1], size:[300, 24], margin:{bottom:-64} }),
        accept_none   : button({pos:[80, -1], size:[300, 24], text:{group:99, id:7}, margin:{bottom:-38} }),

        item_orders_column : dummy({margin:{centerx:0}}),
        item_arrows_column : dummy({margin:{centerx:-36}}),
        item_icon_column : dummy({pos:[25, 0]}),
        item_row     : dummy({size:[px(13), 20]}),      
        items_area   : dummy({pos:[0, 50]}), 
    }
}

granary_info_window = {
    resource_text_group : 23,
    ui : {
        background : outer_panel({size: [29, 17]}),
        title        : text({text: "#granary_info_title", pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [32, 40], wrap:px(28), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        storing    : text({pos: [34, 40], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        free_space : text({pos: [220, 40], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        food0_icon : resource_icon({pos:[34, 68]}),
        food0_text : text({pos: [68, 75], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food1_icon : resource_icon({pos: [240, 68] }),
        food1_text : text({pos: [274, 75], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food2_icon : resource_icon({pos: [34, 92] }),
        food2_text : text({pos: [68, 99], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food3_icon : resource_icon({pos: [240, 92] }),
        food3_text : text({pos: [274, 99], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_panel: inner_panel({pos: [16, 142], size: [27, 5] }),
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 142 + 6] }),
        workers_text : text({pos: [70, 142 + 12], font: FONT_NORMAL_BLACK_ON_DARK }),
        workers_desc : text({pos: [70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK }),
        orders       : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"${98.5}"}),  
        button_help  : image_button({margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 }),
        button_close : image_button({margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 }),
        show_overlay : button({margin:{right:-64, bottom:-40}, size:[23, 23]}),
        mothball     : button({margin:{right:-90, bottom:-40}, size:[23, 23]}),
    }
}

info_window_vacant_lot = {
    help_id : 128,
    ui : {
        background   : outer_panel({size: [29, 21] }), 
        title          : text({pos: [0, 16], text:"${128.0}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        inner_panel  : inner_panel({pos : [16, 40], size: [27, 13] }),
        describe       : text({pos: [36, 114], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(25) }),

        button_close : close_button({}),
        button_help  : help_button({}),
    }
}

info_window_statue {
    ui {
        background   : outer_panel({size[29, 17] }), // pos/size setup from code
        title        : text({pos[0, 16], text:"${building.name}", size[px(28), px(1)], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos[20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

        button_close : close_button({}),
        button_help  : help_button({}),
    }
}

info_window_water_lift = {
    ui : {
        background   : outer_panel({size: [29, 17] }), // pos/size setup from code
        title          : text({pos: [0, 16], text:"${building.name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

        button_close : close_button({}),
        button_help  : help_button({}),
    }
}

info_window_house = {
    help_id : 56,
    ui : {
        background : outer_panel({size: [29, 23] }), // pos/size setup from code
        title        : text({pos: [0, 16], text:"${house.level_name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        evolve_reason : text({pos: [32, 40], font : FONT_NORMAL_BLACK_ON_LIGHT, rich:true, wrap:px(28), scroll:false }),
        food0_icon : resource_icon({pos: [32, 95] }),
        food0_text : text({pos: [64, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food1_icon : resource_icon({pos: [142, 95] }),
        food1_text : text({pos: [174, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food2_icon : resource_icon({pos: [252, 95] }),
        food2_text : text({pos: [284, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        food3_icon : resource_icon({pos: [362, 95] }),
        food3_text : text({pos: [394, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        good0_icon : resource_icon({pos: [32, 120] }),
        good0_text : text({pos: [64, 124], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        good1_icon : resource_icon({pos: [142, 120] }),
        good1_text : text({pos: [174, 124], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        good2_icon : resource_icon({pos: [252, 120] }),
        good2_text : text({pos: [284, 124], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        good3_icon : resource_icon({pos: [362, 120] }),
        good3_text : text({pos: [394, 124], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        tenants_panel: inner_panel({pos : [16, 148], size: [27, 10] }),
        people_icon  : image({pos: [34, 154], pack:PACK_GENERAL, id:134, offset:13, }),
        people_text  : text({pos: [64, 164], font: FONT_NORMAL_BLACK_ON_DARK, }),
        tax_info     : text({pos: [36, 194], font: FONT_NORMAL_BLACK_ON_DARK, }),
        happiness_info  : text({pos: [36, 214], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) }),
        additional_info : text({pos: [36, 234], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) }),

        button_close : close_button({}),
        button_help  : help_button({}),
    }
}

trade_resource_settings_window = {
    pos : [(sw(0) - px(36)) / 2, (sh(0) - px(15)) / 2],
    ui : {
        background       : outer_panel({size: [36, 15]}),
        icon             : resource_icon({pos: [16, 18] }),
        title            : text_center({pos: [0, 16], size: [px(36), -1], font : FONT_LARGE_BLACK_ON_LIGHT}),

        production_state : text_center({pos: [48, 42], size: [px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT}),
        production_store : text_center({pos: [48, 62], size: [px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT}),

        could_import     : text_center({pos: [46, 92], size: [px(10), 30], font : FONT_NORMAL_BLACK_ON_LIGHT}),
        import_status    : button({pos:[32, 92], size:[px(16), 30], align:"left",
            ui : {
                import_dec   : arrowdown({pos:[px(16) - 51, 3]}),
                import_inc   : arrowup({pos:[px(16) - 28, 3]}),
            }
        }),

        could_export     : text_center({pos: [98 + 216, 101], size: [px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT}),
        export_status    : button({pos:[px(36)/2, 92], size:[px(16), 30], align:"left",
            ui : {
                export_dec   : arrowdown({pos:[px(16) - 51, 3]}),
                export_inc   : arrowup({pos:[px(16) - 28, 3]}),
            }
        }),

        toggle_industry  : button({margin:{centerx:-200}, pos:[-1, 130], size:[400, 30]}),
        stockpile_industry: button({margin:{centerx:-200}, pos:[-1, 168], size:[400, 50], split:true}),

        button_close     : close_button({}),
        button_help      : help_button({}),
    }
}

empty_info_window = {
    ui : {
        //background : { type : "outer_panel",  pos: [48, 48], size: [34, 20]},
    }
}

figure_info_window = {
    ui : {
        background     : outer_panel({size: [29, 22]}),
        inner_panel    : inner_panel({pos : [16, 40], size: [27, 13] }),
        border         : border({border:0, pos : [24, 102], size: [px(26), 138] }),
        bigimage       : image({pos: [30, 108], pack:PACK_UNLOADED, id:25 }),
        name           : text({pos: [90, 108], text:"${figure.name}", font : FONT_LARGE_BLACK_ON_DARK }),
        typename       : text({pos: [92, 139], text:"${figure.class_name}", font : FONT_NORMAL_BLACK_ON_DARK }),
        phrase         : text({pos: [90, 160], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(21), multiline:true }),
        button_figure0 : image_button({pos:[60 * 0 + 27, 45], size:[52, 52], border:true }),
        button_figure1 : image_button({pos:[60 * 1 + 27, 45], size:[52, 52], border:true }),
        button_figure2 : image_button({pos:[60 * 2 + 27, 45], size:[52, 52], border:true }),
        button_figure3 : image_button({pos:[60 * 3 + 27, 45], size:[52, 52], border:true }),
        button_figure4 : image_button({pos:[60 * 4 + 27, 45], size:[52, 52], border:true }),
        button_figure5 : image_button({pos:[60 * 5 + 27, 45], size:[52, 52], border:true }),
        button_figure6 : image_button({pos:[60 * 6 + 27, 45], size:[52, 52], border:true }),

        button_help    : help_button({}),
        button_close   : close_button({}),
        
        show_path      : button({margin:{right:-64, bottom:-40}, size:[23, 23]}),
        show_overlay   : button({margin:{right:-90, bottom:-40}, size:[23, 23]}),
    }
}

info_window_figure_animal = {
    ui : __baseui(figure_info_window, {

    })
}

figure_warship_info_window = {
    ui : {
        background       : outer_panel({size: [29, 23]}),
        name             : text_center({pos: [16, 16], size: [px(27), 20], text:"${figure.class_name}", font : FONT_LARGE_BLACK_ON_DARK }),
        hullstrength_lb  : text({pos: [102, 58], text:"${184.2}" }),
        hullstrength_val : text({pos: [202, 58], text:"" }),
        crewfatique_lb   : text({pos: [102, 88], text:"${184.27}" }),
        crewfatique_val  : text({pos: [202, 88], text:"" }),

        hold_position    : image_button({param1:3, param2:9, pos:[87 * 0 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 0, offset_pressed:0, offset_focused:0, border:true }),
        engage_nearby    : image_button({param1:2, param2:11, pos:[87 * 1 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 1, offset_pressed:0, offset_focused:0, border:true }),
        seek_and_destroy : image_button({param1:4, param2:13, pos:[87 * 2 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 2, offset_pressed:0, offset_focused:0, border:true }),
        repair           : image_button({param1:5, param2:15, pos:[87 * 3 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 3, offset_pressed:0, offset_focused:0, border:true }),
        return_to_wharf  : image_button({param1:1, param2:17, pos:[87 * 4 + 16, 134], pack:PACK_UNLOADED, id:37, offset:0 + 4, offset_pressed:0, offset_focused:0, border:true }),

        inner_panel      : inner_panel({pos : [16, 220], size: [27, 6],
            ui : {
                action_header: text({pos: [10, 10], font : FONT_NORMAL_WHITE_ON_DARK }),
                action_text : text({pos: [10, 30], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(21), multiline:true }),
            }
        }),

        button_help      : help_button({}),
        button_close     : close_button({}),
    }
}

figure_carrier_info_window = {
    ui : __baseui(figure_info_window, {
        typename         : text({pos: [92, 139], text:"${figure.class_name} ( @Y${figure.home}& )", font : FONT_NORMAL_BLACK_ON_DARK, rich:true, scroll:false }),
        items            : text({pos: [102, 158], size:[px(29), 20], font : FONT_NORMAL_BLACK_ON_DARK, rich:true, scroll:false }),
        phrase           : text({pos: [90, 180], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(22), multiline:true }),
    })
}

temple_info_window = {
    ui : {
        background   : outer_panel({ pos: [0, 0], size: [29, 18]}),
        title        : text({ pos: [0, 16], size: [px(29), 13], text:"${building.name}", font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),

        inner_panel  : inner_panel({ pos : [16, 56], size: [27, 4] }),
        workers_img  : image({ pack:PACK_GENERAL, id:134, offset:14, pos:[40, 70] }),
        workers_text : text({ text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers} ${loc.building_employee_needed} )", pos: [70, 74], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_desc : text({ pos: [70, 74 + 16], font: FONT_NORMAL_BLACK_ON_DARK }),
        button_help  : image_button({ margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 }),
        button_close : image_button({ margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 }),
        show_overlay : button({ margin:{right:-64, bottom:-40}, size:[23, 23]}),
        god_image    : image({ pos: [190, 134] }),
        mothball     : button({ margin:{right:-90, bottom:-40}, size:[23, 23]}),
    }
}

temple_complex_info_window = {
    ui : {
        background   : outer_panel({ pos: [0, 0], size: [29, 18]}),
        title        : text({ pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        
        inner_panel  : inner_panel({ pos : [16, 56], size: [27, 4] }),
        workers_img  : image({ pack:PACK_GENERAL, id:134, offset:14, pos:[40, 70] }),
        workers_text : text({ text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", pos: [70, 74], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_desc : text({ pos: [70, 74 + 16], font: FONT_NORMAL_BLACK_ON_DARK }),
        button_help  : image_button({ margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 }),
        button_close : image_button({ margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 }),
        show_overlay : button({ margin:{right:-64, bottom:-40}, size:[23, 23]}),
        god_image    : image({ pos: [190, 134] }),
        mothball     : button({ margin:{right:-90, bottom:-40}, size:[23, 23]}),
    }
}

building_info_window = {
    ui : {
        background     : outer_panel({size: [29, 17]}),
        title          : { type : "text", pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"},
        warning_text   : { type : "text", pos: [20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
        inner_panel    : inner_panel({pos : [16, 100], size: [27, 5],
                                                ui : {
                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                    workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                }
                                          }),
        first_advisor  : { type : "image_button", pos:[40, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
        second_advisor : { type : "image_button", pos:[64, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
        third_advisor  : { type : "image_button", pos:[96, -1], size:[28, 28], pack:PACK_GENERAL, id:106 },
        button_help    : { type : "image_button", margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 },
        button_close   : { type : "image_button", margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 },
        show_overlay   : { type:"generic_button", margin:{right:-64, bottom:-40}, size:[23, 23]},
        mothball       : { type:"generic_button", margin:{right:-90, bottom:-40}, size:[23, 23]},
    }
}

water_supply_info_window = {
    ui : __baseui(building_info_window, {
        background  : outer_panel({size: [29, 20]}),
    })
}

info_window_ferry = {
    ui : __baseui(building_info_window, {
        background  : outer_panel({size: [29, 20]}),
    })
}

info_window_hunting_lodge = {
    ui : __baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        resource     : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        resource_amount : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
    })
}

info_window_bandstand = {
    ui : __baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        title        : text({pos: [0, 16], text:"${building.name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel  : inner_panel({pos : [16, 116], size: [27, 8] }),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play2_text   : text({pos: [32, 182], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 122] }),
        workers_text : text({pos: [70, 130], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
        workers_desc : text({pos: [70, 126 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

info_window_pavilion = {
    ui : __baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        title        : text({pos: [0, 16], text:"${building.name}", size: [px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel  : inner_panel({pos : [16, 116], size: [27, 8] }),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play2_text   : text({pos: [32, 182], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        play3_text   : text({pos: [32, 202], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 122] }),
        workers_text : text({pos: [70, 130], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
        workers_desc : text({pos: [70, 126 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

shrine_info_window = {
    ui : {
        background   : outer_panel({size: [29, 14]}),
        title        : text({pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text : text({pos: [20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        god_image    : image({pos: [190, 94] }),
        show_overlay : button({margin:{right:-64, bottom:-40}, size:[23, 23]}),

        button_help  : help_button({}),
        button_close : close_button({}),
    },

    gods : [
        { type: BUILDING_SHRINE_OSIRIS, image : {pack:PACK_UNLOADED, id:21, offset:21}, title:[161, 0], text:[161, 1] },
        { type: BUILDING_SHRINE_RA, image : {pack:PACK_UNLOADED, id:21, offset:22}, title:[161, 2], text:[161, 3] },
        { type: BUILDING_SHRINE_PTAH, image : {pack:PACK_UNLOADED, id:21, offset:23}, title:[161, 4], text:[161, 5] },
        { type: BUILDING_SHRINE_SETH, image : {pack:PACK_UNLOADED, id:21, offset:24}, title:[161, 6], text:[161, 7] },
        { type: BUILDING_SHRINE_BAST, image : {pack:PACK_UNLOADED, id:21, offset:25}, title:[161, 8], text:[161, 9] },
    ]
}

info_window_mastaba = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${140.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        warning_text  : text({pos: [32, 86], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
    }
}

info_window_booth = {
    ui : __baseui(building_info_window, {
        background   : outer_panel({pos: [0, 0], size: [29, 16]}),
        play_text    : text({pos: [32, 162], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        inner_panel  : inner_panel({pos : [16, 110], size: [27, 6],
                                        ui : {
                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                            workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                            workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                        }
                                  }),
    })
}

info_window_fishing_wharf = {
    ui : __baseui(building_info_window, {
        resource_img : { type : "resource_icon", pos: [32, 186] },
        storage_desc : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
    })
}

info_window_recruiter = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 20]}),
        warning_text  : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        icon_weapon   : resource_icon({pos:[24, 100], resource:RESOURCE_WEAPONS  }),
        storage_state : text({pos: [46, 104], text:"${8.10} ${building.first_material_stored}", font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        progress_desc : { type : "text", pos: [32, 104], font: FONT_NORMAL_BLACK_ON_LIGHT },
        inner_panel   : inner_panel({pos : [16, 125], size: [27, 5],
                                                ui : {
                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                    workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                }
                                          }),
        priority_text : { type : "text", pos: [46, 210], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:50, id:21} },
        tower_text    : text({pos: [74, 232], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:91, id:0} }),
        tower_button  : button({pos: [46, 228], size:[20, 20], font: FONT_NORMAL_BLACK_ON_DARK }),
        fort_text     : text({pos: [74, 252], font: FONT_NORMAL_BLACK_ON_LIGHT, text:{group:89, id:0} }),
        fort_button   : button({pos: [46, 248], size:[20, 20], font: FONT_NORMAL_BLACK_ON_DARK }),
    })
}

info_window_farm = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 18]}),
        resource      : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        workers_desc  : text({ pos: [70, 116], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(23) }),
        farm_desc     : text({ pos: [32, 38], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        farm_state    : text({ pos: [32, 186], font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        flood_info    : text({ pos: [32, 206], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_desc : text({ pos: [32, 226], text:"${text.2} ${farm.progress}% ${text.3} ${text.12} ${farm.fertility}% ${text.13}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
    })
}

info_window_architect_post = {
  ui : __baseui(building_info_window, {

  })
}

info_window_firehouse = {
  ui : __baseui(building_info_window, {

  })
}

ruin_info_window = {
    open_sounds : [ "wavs/fire.wav" ],
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title               : text({pos: [0, 16], text:"${140.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text  : text({pos: [0, 46], size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle          : text({pos: [32, 66], text:"${140.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

info_window_burning_ruin = {
    open_sounds : [ "wavs/fire.wav" ],
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title               : text({pos: [0, 16], text:"${111.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text    : text({pos: [0, 46], size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle          : text({pos: [32, 66], text:"${111.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

info_window_mansion = {
    first_advisor : ADVISOR_IMPERIAL,
    ui : {
        background    : outer_panel({size: [29, 18]}),

        title               : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        first_advisor : image_button({pos:[40, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        warning_text    : text({pos: [20, 46], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        change_salary : button({text:"${player.rank_name} ${player.salary_amount} ${52.3}", margin:{centerx:-200, bottom:-80}, size:[400, 30], font: FONT_NORMAL_BLACK_ON_DARK }),

      button_help   : help_button({}),
      button_close  : close_button({}),
    }
}

info_window_raw_material = {
    ui : __baseui(building_info_window, {
        resource_img  : resource_icon({pos: [14, 14], prop:"${building.output_resource}"}),
        progress_desc : text({pos: [32, 44], text:"${text.2} ${industry.progress} % ${text.3}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_desc  : text({pos: [32, 66], text:"${text.1}", font: FONT_NORMAL_BLACK_ON_LIGHT, wrap:px(27), multiline:true }),
        inner_panel   : inner_panel({pos : [16, 130], size: [27, 5],
                                                ui : {
                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                    workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                }
                                          }),
    })
}

info_window_garden = {
    ui : {
        background    : outer_panel({size: [29, 17]}),
        title             : text({pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        describe        : text({pos: [32, 66], text: "#gardens_describe", wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

info_window_palace = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 18]}),
        resource_img  : resource_icon({pos: [16, 16], resource:RESOURCE_GOLD}),
        inner_panel   : inner_panel({pos : [16, 120], size: [27, 6],
                                                                ui : {
                                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                                    workers_desc : text({pos: [50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                                }
                                                          }),
        vaults_hold   : text({pos: [44, 44], text:"${text.2} ${building.tax_income_or_storage} Db", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_desc  : text({pos: [32, 66], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        text_visit    : text({pos: [90, 252], font: FONT_NORMAL_BLACK_ON_LIGHT, text:"#visit_rating_advisor" }),
        visit_advisor : image_button({pos:[52, 246], size:[28, 28], pack:PACK_GENERAL, id:106 }),
    })
}

info_window_courthouse = {
    ui : __baseui(building_info_window, { 
        background    : outer_panel({size: [29, 17]}),
        vaults_hold   : text({pos: [44, 54], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        state         : text({margin:{left:20, bottom: -80} , font: FONT_NORMAL_BLACK_ON_DARK}),
    })
}

info_window_entertainment = {
    ui : {
        background    : outer_panel({pos: [0, 0], size: [29, 17]}),
        title             : text({ pos: [0, 12], size: [px(29), 25], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text  : text({ pos: [32, 46], wrap:px(26), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel   : inner_panel({ pos : [16, 116], size: [27, 5] }),
        workers_img   : image({ pack:PACK_GENERAL, id:134, offset:14, pos:[40, 126] }),
        workers_text  : text({ pos: [70, 124], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_desc  : text({ pos: [70, 124 + 20], font: FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true }),
        first_advisor : image_button({ pos:[42, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        second_advisor: image_button({ pos:[64, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        third_advisor : image_button({ pos:[96, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        
        show_overlay  : button({ margin:{right:-64, bottom:-40}, size:[23, 23]}),
        mothball      : button({ margin:{right:-90, bottom:-40}, size:[23, 23]}),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

health_info_window = {
    ui : __baseui(building_info_window, {

    })
}

info_window_work_camp = {
    ui : __baseui(building_info_window, {

    })
}

batalion_info_window = {
    ui : {
        background    : outer_panel({size: [34, 24]}),
        title             : text({pos: [0, 16], size: [px(31), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),

        batalion_icon   : image({ pack:PACK_GENERAL, id:127, pos:[30, 30] }),
        morale_img    : image({ pack:PACK_GENERAL, id:54, pos:[30, 50] }),
        describe          : text({pos: [30, 140], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(28) }),

        soldiers_lb   : text({ pos: [100, 60], text:"${138.23}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        soldiers_num  : text({ pos: [290, 60], font: FONT_NORMAL_BLACK_ON_LIGHT }),     

        health_lb     : text({ pos: [100, 80], text:"${138.24}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        health_num    : text({ pos: [290, 80], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        training_lb   : text({ pos: [100, 100], text:"${138.25}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        training_num  : text({ pos: [290, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        morale_lb     : text({ pos: [100, 120], text:"${138.36}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        morale_num    : text({ pos: [290, 120], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        formation_1   : image_button({pos:[86 * 0 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 0, offset_pressed:0, offset_focused:0, border:true }),
        formation_2   : image_button({pos:[86 * 1 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 1, offset_pressed:0, offset_focused:0, border:true }),
        formation_3   : image_button({pos:[86 * 2 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 2, offset_pressed:0, offset_focused:0, border:true }),
        formation_4   : image_button({pos:[86 * 3 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 3, offset_pressed:0, offset_focused:0, border:true }),
        formation_5   : image_button({pos:[86 * 4 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 4, offset_pressed:0, offset_focused:0, border:true }),
        return_to_fort: image_button({pos:[86 * 5 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 7, offset_pressed:0, offset_focused:0, border:true }),

        inner_panel   : inner_panel({pos : [16, 260], size: [32, 5],
                                            ui : {
                                                layout_header : text({pos: [10, 10], font: FONT_NORMAL_WHITE_ON_DARK}),
                                                layout_desc   : text({pos: [10, 10 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(29) }),
                                            }
                                        }),

        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

taxcollector_info_window = {
    ui : {
        background    : outer_panel({size: [29, 17]}),
        title             : text({pos: [0, 12], size: [px(29), 20], text:"${text.0}", font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        deben_icon    : resource_icon({pos: [16, 46], resource:RESOURCE_GOLD}),
        tax_level     : label({pos:[px(29) / 2 + 40, 46], text:"${60.1} ${city.tax_percentage}%", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        dec_tax         : arrowdown({pos:[px(29) / 2 + 170, 38]}),
        inc_tax           : arrowup({pos:[px(29) / 2 + 193, 38]}),
        money_text    : text({pos: [44, 44], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [28, 66], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        building_desc : text({pos: [28, 86], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel   : inner_panel({pos : [16, 136], size: [27, 5] }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[30, 146] }),
        workers_text  : text({pos: [55, 150], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK }),
        workers_desc  : text({pos: [55, 165], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        first_advisor : image_button({pos:[42, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        show_overlay  : button({margin:{right:-64, bottom:-40}, size:[23, 23]}),
        mothball          : button({margin:{right:-90, bottom:-40}, size:[23, 23]}),

        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

dock_info_window = {
    ui : __baseui(building_info_window, {
        background   : outer_panel({size: [29, 16]}),
        orders       : button({margin:{left:100, bottom:-40}, size:[270, 25], text:{group: 98, id: 5}}),
    })
}

warshipwharf_info_window = {
    first_advisor       : ADVISOR_MILITARY,
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 16]}),
        resource_icon : resource_icon({pos: [32, 56] }),
        resource_stored : text({pos: [60, 60], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_desc  : text({pos: [70, 116 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
    })
}

shipyard_info_window = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 18]}),
        warning_text  : text({pos: [28, 40], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel   : inner_panel({pos : [16, 150], size: [27, 5],
                                                                ui : {
                                                                    workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                                    workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                                    workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                                }
                                                            }),
        ready_prod    : text({pos: [30, 110], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
    resource_icon : resource_icon({pos: [32, 130] }),
        resource_stored : text({pos: [60, 130], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
    })
}

scribal_school_info_window = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 17]}),
        resource_icon : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], text:"${23.77} ${stored.papyrus}", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel   : inner_panel({pos : [16, 120], size: [27, 5],
                                                        ui : {
                                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                            workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                            workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                        }
                                                    }),
    })
}

dock_orders_window = {
    parent_offset: [0, -px(4)],
    ui : {
        background   : outer_panel({size: [29, 22]}),
        title          : text({pos: [0, 12], size: [px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        orders_panel : inner_panel({pos : [16, 42], size: [27, 16] }),
        button_help  : image_button({margin:{left:14, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134 }),
        button_close : image_button({margin:{right:-40, bottom:-40}, size:[27, 27], pack:PACK_GENERAL, id:134, offset:4 }),
        accept_none  : button({pos:[80, -1], size:[300, 24], text:{group:99, id:7}, margin:{bottom:-38} }),

        item_orders_column : dummy({margin:{centerx:0}}),
        item_icon_column : dummy({pos:[25, 0]}),
        item_name_column : dummy({pos:[55, 0]}),
        item_row     : dummy({size:[px(13), 20]}),      
        items_area   : dummy({pos:[0, 50]}), 
    }
}

festival_square_info_window = {
    ui : {
        background      : outer_panel({pos: [0, 0], size: [29, 16]}),
        title           : text({text: "#festival_square_info_title", pos: [0, 10], size: [px(29), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning         : text({pos: [32, 36], wrap:px(26), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        workers_panel   : inner_panel({ pos : [16, 96], size: [27, 7] }),
        fest_months_last: text({pos:[32, 112], size: [px(25), 20], text:"${city.months_since_festival} ${8.5} ${58.15}", font:FONT_NORMAL_WHITE_ON_DARK, align:"center"}),
        hold_festival   : button({pos:[60, 134], size:[px(22), 25], font:FONT_NORMAL_WHITE_ON_DARK, text:"${58.16}"}),
        planed_festival : text({pos: [102, 134], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" }),
        festival_advice : text({pos: [36, 164], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true }),

        button_help     : help_button({}),
        button_close    : close_button({}),
    }
}

info_window_tower = {
    ui : __baseui(building_info_window, {

    })
}

info_window_senet_house = {
    ui : __baseui(building_info_window, {
        advice        : text({pos: [36, 164], wrap:400, font : FONT_NORMAL_BLACK_ON_DARK, multiline:true }),
    })
}

info_window_bullfight = {
    ui : __baseui(building_info_window, {

    })
}

info_window_police_station = {
    ui : __baseui(building_info_window, {

    })
}

info_window_gatehouse = {
    ui : __baseui(building_info_window, {

    })
}

info_window_milacademy = {
    ui : __baseui(building_info_window, {

    })
}


well_info_window = {
    ui : {
        background    : outer_panel({size: [29, 14] }),
        title           : text({pos: [0, 12], size: [px(28), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center", text:"${loc.well_info_title}"}),
        text          : text({pos: [32, 56], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

info_window_storageyard_orders = {
    parent_window_offset : [0, -250],
    ui : {
        background    : outer_panel({size:[29, 35] }),
        title         : text_center({text:[99, 3], pos:[10, 10], size:[px(29), 20], font: FONT_LARGE_BLACK_ON_LIGHT}),

      items_panel   : inner_panel({pos:[16, 42], size:[27, 28] }),
      resource_base : dummy({pos: [10, 26] }),
      icon_column   : dummy({pos: [26, 6] }),
      name_column   : dummy({pos: [56, 6] }),
      order_column  : dummy({pos: [px(27)/2, 4], size:[px(27)/2, 20] }),
      increase_column: dummy({pos: [px(27)/2 -13, 6] }),
      decrease_column: dummy({pos: [px(27)/2 -30, 6] }),
      item_row      : dummy({size: [0, 20] }),

      button_help   : help_button({}),
        button_close  : close_button({}),

        empty_all     : button({pos:[80, -1], size:[300, 24], margin:{bottom:-64} }),
        accept_none   : button({pos:[80, -1], size:[300, 24], text:[99, 7], margin:{bottom:-38} }),
    }
}

info_window_storageyard = {
    first_advisor       : ADVISOR_TRADE,
    ui : {
        background    : outer_panel({size: [29, 21] }),
        title         : text({pos: [0, 12], size: [px(27), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
   
        warning_text  : text({pos: [22, 36], wrap:px(28), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        storing       : text({ pos: [24, 90], text:"${loc.granary_storing} ${building.total_stored} ${loc.granary_units}", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        free_space    : text({ pos: [220, 90], text:"${loc.granary_space_for} ${building.free_space} ${loc.granary_units}", font : FONT_NORMAL_BLACK_ON_LIGHT }),
   
        stored_items  : dummy({pos:[0, 110],
        ui : {
                good0_icon : resource_icon({pos: [32, 0] }),
                good0_text : text({pos: [54, 4], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good1_icon : resource_icon({pos: [172, 0] }),
                good1_text : text({pos: [194, 4], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good2_icon : resource_icon({pos: [292, 0] }),
                good2_text : text({pos: [314, 4], font: FONT_NORMAL_BLACK_ON_LIGHT }),
            
                good3_icon : resource_icon({pos: [32, 30] }),
                good3_text : text({pos: [54, 34], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good4_icon : resource_icon({pos: [172, 30] }),
                good4_text : text({pos: [194, 34], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good5_icon : resource_icon({pos: [292, 30] }),
                good5_text : text({pos: [314, 34], font: FONT_NORMAL_BLACK_ON_LIGHT }),
            
                good6_icon : resource_icon({pos: [32, 60] }),
                good6_text : text({pos: [54, 64], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good7_icon : resource_icon({pos: [172, 60] }),
                good7_text : text({pos: [194, 64], font: FONT_NORMAL_BLACK_ON_LIGHT }),
                good8_icon : resource_icon({pos: [292, 60] }),
                good8_text : text({pos: [314, 64], font: FONT_NORMAL_BLACK_ON_LIGHT }),
            }
        }),

        workers_panel : inner_panel({pos : [16, 198], size: [27, 5] }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 203] }),
        workers_text  : text({pos: [70, 208], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_desc  : text({pos: [70, 208 + 16], font: FONT_NORMAL_BLACK_ON_DARK }),
        cartstate_img : resource_icon({pos:[32, 260] }),
        cartstate_desc: text({pos: [72, 260], wrap:px(27), font : FONT_NORMAL_BLACK_ON_DARK, multiline:true }),

        orders        : button({margin:{left:100, bottom:-40}, size:[270, 24], text:"${99.2}"}),
        button_help   : help_button({}),
        button_close  : close_button({}),
        mothball      : button({margin:{right:-90, bottom:-40}, size:[23, 23]}),

        first_advisor : image_button({margin:{left:40, bottom:-40}, size:[28, 28], pack:PACK_GENERAL, id:106 }),
    }
}

window_popup_dialog_yesno = {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(10))/2],
    ui : {
        background : outer_panel({size: [30, 10] }),
        header     : text({pos:[0, 30], size:[px(30), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        text       : text({pos:[0, 60], size:[px(30), 20], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"}),
        btn_yes    : image_button({margin:{centerx:-60, bottom:-60}, size:[39, 26], pack:PACK_GENERAL, id:96 }),
        btn_no     : image_button({margin:{centerx:20, bottom:-60}, size:[39, 26], pack:PACK_GENERAL, id:96, offset:4 }),
        label_tip  : text({margin:{left:20, bottom:-40}, font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"}),
    }
}

window_popup_dialog_ok = {
    pos: [(sw(0) - px(30))/2, (sh(0) - px(10))/2],
    ui : {
        background : outer_panel({size: [30, 10] }),
        header     : text({pos:[0, 30], size:[px(30), 20], font: FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        text       : text({pos:[0, 60], size:[px(30), 20], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"}),
        btn_yes    : image_button({margin:{centerx:-20, bottom:-60}, size:[39, 26], pack:PACK_GENERAL, id:96 }),
        label_tip  : text({margin:{left:20, bottom:-40}, font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"}),
    }
}

minimap_window = {
  draw_size : [73, 111],

    terrain_water : {pack:PACK_GENERAL, id:142},
    terrain_shrub : {pack:PACK_GENERAL, id:143},
    terrain_tree  : {pack:PACK_GENERAL, id:143},
    terrain_marshland : {pack:PACK_GENERAL, id:144},
    terrain_rock  : {pack:PACK_GENERAL, id:145},
    terrain_elevation : {pack:PACK_GENERAL, id:145},
    terrain_meadow : {pack:PACK_GENERAL, id:146},
    terrain_flooplain : {pack:PACK_GENERAL, id:146},
    terrain_road  : {pack:PACK_GENERAL, id:147},
    terrain_wall  : {pack:PACK_GENERAL, id:150},
    terrain_canal : {pack:PACK_GENERAL, id:151},
    terrain_dune  : {pack:PACK_GENERAL, id:211},
    terrain_teal  : {pack:PACK_GENERAL, id:149, offset:200},
    terrain_bright_teal  : {pack:PACK_GENERAL, id:149, offset:170},
    terrain_bright_blue  : {pack:PACK_GENERAL, id:149, offset:170},
    terrain_dark_read  : {pack:PACK_GENERAL, id:149, offset:165},
    terrain_purple: {pack:PACK_GENERAL, id:149, offset:175},
    terrain_light_yellow: {pack:PACK_GENERAL, id:149, offset:180},
    terrain_lilac : {pack:PACK_GENERAL, id:149, offset:195},
    terrain_orange: {pack:PACK_GENERAL, id:149, offset:205},
}

window_warnings = {
    max_items : 5,
    timeout_ms : 15000,
    top_offset : 30,
    message_interval : 25,
    ui : {
        dummy : dummy({})
    }
}

info_window_education = {
    ui : __baseui(building_info_window, {
        background    : outer_panel({size: [29, 17]}),
        resource_icon : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], text:"${23.77} ${stored.papyrus}", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        inner_panel   : inner_panel({pos : [16, 120], size: [27, 5],
                                                        ui : {
                                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                                                            workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                                                            workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
                                                        }
                                                    }),
    })
}

