log_info("akhenaten: ui batalion info window started")

batalion_info_window {
    ui {
        background    : outer_panel({size [34, 24]}),
        title         : text({pos[0, 16], size [px(31), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),

        batalion_icon : image({ pack:PACK_GENERAL, id:127, pos[30, 30] }),
        morale_img    : image({ pack:PACK_GENERAL, id:54, pos[30, 50] }),
        describe      : text({pos[30, 140], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(28) }),

        soldiers_lb   : text({ pos[100, 60], text:"${138.23}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        soldiers_num  : text({ pos[290, 60], font: FONT_NORMAL_BLACK_ON_LIGHT }),     

        health_lb     : text({ pos[100, 80], text:"${138.24}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        health_num    : text({ pos[290, 80], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        training_lb   : text({ pos[100, 100], text:"${138.25}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        training_num  : text({ pos[290, 100], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        morale_lb     : text({ pos[100, 120], text:"${138.36}", font: FONT_NORMAL_BLACK_ON_LIGHT }),
        morale_num    : text({ pos[290, 120], font: FONT_NORMAL_BLACK_ON_LIGHT }),

        formation_1   : image_button({pos[86 * 0 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 0, offset_pressed:0, offset_focused:0, border:true }),
        formation_2   : image_button({pos[86 * 1 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 1, offset_pressed:0, offset_focused:0, border:true }),
        formation_3   : image_button({pos[86 * 2 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 2, offset_pressed:0, offset_focused:0, border:true }),
        formation_4   : image_button({pos[86 * 3 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 3, offset_pressed:0, offset_focused:0, border:true }),
        formation_5   : image_button({pos[86 * 4 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 7, offset_pressed:0, offset_focused:0, border:true }),
        return_to_fort: image_button({pos[86 * 5 + 16, 174], pack:PACK_UNLOADED, id:34, offset:0 + 4, offset_pressed:0, offset_focused:0, border:true }),

        inner_panel   : inner_panel({pos[16, 260], size[32, 5],
                                            ui : {
                                                layout_header : text({pos[10, 10], font: FONT_NORMAL_WHITE_ON_DARK}),
                                                layout_desc   : text({pos[10, 10 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(29) }),
                                            }
                                        }),

        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}