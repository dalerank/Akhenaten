log_info("akhenaten: ui figure info started")

def_object_info {
    forbidden_figure_types [ FIGURE_NONE, FIGURE_EXPLOSION, FIGURE_MAP_FLAG, FIGURE_ARROW,
                             FIGURE_JAVELIN, FIGURE_BOLT, FIGURE_BALLISTA, FIGURE_CREATURE,
                             FIGURE_FISHING_POINT, FIGURE_FISHING_SPOT, FIGURE_SPEAR, FIGURE_CHARIOR_RACER
                           ]
}

figure_info_window {
    ui {
        background     : outer_panel({size [29, 22]})
        inner_panel    : inner_panel({pos [16, 40], size [27, 13] })
        border         : border({border:0, pos : [24, 102], size [px(26), 138] })
        bigimage       : image({pos [30, 108], pack:PACK_UNLOADED, id:25 })
        name           : text({pos [90, 108], text:"${figure.name}", font : FONT_LARGE_BLACK_ON_DARK })
        typename       : text({pos [92, 139], text:"${figure.class_name}", font : FONT_NORMAL_BLACK_ON_DARK })
        phrase         : text({pos [90, 160], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(21), multiline:true })
        
        button_figure0 : image_button({pos[60 * 0 + 27, 45], size[52, 52], border:true })
        button_figure1 : image_button({pos[60 * 1 + 27, 45], size[52, 52], border:true })
        button_figure2 : image_button({pos[60 * 2 + 27, 45], size[52, 52], border:true })
        button_figure3 : image_button({pos[60 * 3 + 27, 45], size[52, 52], border:true })
        button_figure4 : image_button({pos[60 * 4 + 27, 45], size[52, 52], border:true })
        button_figure5 : image_button({pos[60 * 5 + 27, 45], size[52, 52], border:true })
        button_figure6 : image_button({pos[60 * 6 + 27, 45], size[52, 52], border:true })

        button_help    : help_button({})
        button_close   : close_button({})
        
        show_path      : button({margin{right:-64, bottom:-40}, size[23, 23]})
        show_overlay   : button({margin{right:-90, bottom:-40}, size[23, 23]})
    }
}