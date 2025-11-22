log_info("akhenaten: ui granary window started")

granary_info_window {
    resource_text_group : 23
    resource_number : 4
    related_buildings [BUILDING_GRANARY, BUILDING_GRANARY_UP]
    ui {
        background   : outer_panel({size[29, 17]})
        title        : text({text: "#granary_info_title", pos[0, 12], size[px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text : text({pos[32, 40], wrap:px(28), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        storing      : text({pos[34, 40], font : FONT_NORMAL_BLACK_ON_LIGHT })
        free_space   : text({pos[220, 40], font : FONT_NORMAL_BLACK_ON_LIGHT })
        food0_icon   : resource_icon({pos:[34, 68]})
        food0_text   : text({pos[68, 75], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon   : resource_icon({pos[240, 68] })
        food1_text   : text({pos[274, 75], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon   : resource_icon({pos[34, 92] })
        food2_text   : text({pos[68, 99], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon   : resource_icon({pos[240, 92] })
        food3_text   : text({pos[274, 99], font: FONT_NORMAL_BLACK_ON_LIGHT })
        workers_panel: inner_panel({pos[16, 142], size[27, 5] })
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 142 + 6] })
        workers_text : text({pos[70, 142 + 12], font: FONT_NORMAL_BLACK_ON_DARK })
        workers_desc : text({pos[70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK })
        orders       : button({margin{centerx:-135, bottom:-40}, size[270, 25], text:"${98.5}"}), 
        button_help  : image_button({margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134 })
        button_close : image_button({margin{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4 })
        show_overlay : button({margin{right:-64, bottom:-40}, size[23, 23]})
        mothball     : button({margin{right:-90, bottom:-40}, size[23, 23]})
    }
}