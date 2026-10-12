log_info("akhenaten: ui widgets started")

uioptions {
    resource_icons  : {pack:PACK_EXPANSION, id:3}
    advisor_icons   : {pack:PACK_GENERAL, id:128, offset:0}
    arrow_button_tiny_down : {pack:PACK_GENERAL, id:212, offset:0}
    arrow_button_tiny_up : {pack:PACK_GENERAL, id:212, offset:3}
    arrow_button_down : {pack:PACK_UNLOADED, id:0, offset:18}
    arrow_button_up : {pack:PACK_UNLOADED, id:0, offset:16}
}

empty_info_window = {
    ui : {
        //background : { type : "outer_panel",  pos: [48, 48], size: [34, 20]},
    }
}

[es=ui_window]
info_window_hunting_lodge {
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        resource     : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        resource_amount : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
    })
}

[es=ui_window]
info_window_pyramid = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        stone_icon    : resource_icon({pos: [32, 200], resource: RESOURCE_STONE }),
        stone_text    : text({pos: [70, 204], size:[px(12), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        limestone_icon: resource_icon({pos: [180, 200], resource: RESOURCE_LIMESTONE }),
        limestone_text: text({pos: [218, 204], size:[px(12), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [32, 230], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [70, 234], size:[px(12), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[260, 215] }),
        workers_text  : text({pos: [290, 219], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_sphinx = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [70, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        paint_icon    : resource_icon({pos: [32, 230], resource: RESOURCE_PAINT }),
        paint_text    : text({pos: [70, 234], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        clay_icon     : resource_icon({pos: [180, 230], resource: RESOURCE_CLAY }),
        clay_text     : text({pos: [218, 234], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[260, 200] }),
        workers_text  : text({pos: [290, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_sun_temple = {
    ui : {
        background    : outer_panel({size: [29, 16]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [70, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        sandstone_icon: resource_icon({pos: [180, 200], resource: RESOURCE_SANDSTONE }),
        sandstone_text: text({pos: [218, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_mausoleum = {
    ui : {
        background    : outer_panel({size: [29, 16]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(20), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_pct  : text({pos: [200, 66], size:[px(8), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [70, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        sandstone_icon: resource_icon({pos: [180, 200], resource: RESOURCE_SANDSTONE }),
        sandstone_text: text({pos: [218, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_caesareum = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(20), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_pct  : text({pos: [200, 66], size:[px(8), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        marble_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_MARBLE }),
        marble_text   : text({pos: [70, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [150, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [188, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        granite_icon  : resource_icon({pos: [268, 200], resource: RESOURCE_GRANITE }),
        granite_text  : text({pos: [306, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_alexandria_library = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(20), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_pct  : text({pos: [200, 66], size:[px(8), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        marble_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_MARBLE }),
        marble_text   : text({pos: [70, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [150, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [188, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        copper_icon   : resource_icon({pos: [268, 200], resource: RESOURCE_COPPER }),
        copper_text   : text({pos: [306, 204], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=ui_window]
info_window_pharos_lighthouse = {
    ui : {
        background    : outer_panel({size: [29, 16]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(20), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        progress_pct  : text({pos: [200, 66], size:[px(8), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        marble_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_MARBLE }),
        marble_text   : text({pos: [70, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        timber_icon   : resource_icon({pos: [180, 200], resource: RESOURCE_TIMBER }),
        timber_text   : text({pos: [218, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

ruin_info_window {
    open_sounds [ "wavs/fire.wav" ]
    ui {
        background    : outer_panel({size[29, 18]}),
        title         : text({pos[0, 16], text:"${140.0}", size[px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text  : text({pos[0, 46], size[px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle      : text({pos[32, 66], text:"${140.1}", size[px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

[es=ui_window]
info_window_burning_ruin = {
    open_sounds : [ "wavs/fire.wav" ],
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title               : text({pos: [0, 16], text:"${111.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text    : text({pos: [0, 46], size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle          : text({pos: [32, 66], text:"${111.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

[es=building_info_window]
info_window_entertainment {
    related_buildings [BUILDING_JUGGLER_SCHOOL, BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL]
    ui {
        background    : outer_panel({ size[29, 17]})
        title         : text({ pos[0, 12], size[px(29), 25], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})

        warning_text  : text({ pos[32, 46], wrap:px(26), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        inner_panel   : inner_panel({ pos[16, 116], size[27, 5] })
        workers_img   : image({ pack:PACK_GENERAL, id:134, offset:14, pos[40, 126] })
        workers_text  : text({ pos[70, 124], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        workers_desc  : text({ pos[70, 124 + 20], font: FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true })
        first_advisor : image_button({ margin:{left:42, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:0, onclick_event:"show_advisor" })
        second_advisor: image_button({ margin:{left:64, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:1, onclick_event:"show_advisor" })
        third_advisor : image_button({ margin:{left:96, bottom:-40}, size[28, 28], pack:PACK_GENERAL, id:106, param1:2, onclick_event:"show_advisor" })

        show_overlay  : button({
                                margin:{right:-64, bottom:-40}, size[23, 23]
                                textfn:building_info_window_text_overlay
                               })

        mothball      : button({
                                 margin:{right:-90, bottom:-40}, size[23, 23]
                                 textfn:building_info_window_text_mothball
                               })

        button_help   : help_button({})
        button_close  : close_button({})
    }
}



health_info_window = {
    ui : baseui(building_info_window, {

    })
}

minimap_window {
    draw_size [73, 111]

    terrain_water {pack:PACK_GENERAL, id:142},
    terrain_shrub {pack:PACK_GENERAL, id:143},
    terrain_tree  {pack:PACK_GENERAL, id:143},
    terrain_marshland {pack:PACK_GENERAL, id:144},
    terrain_rock  {pack:PACK_GENERAL, id:145},
    terrain_elevation {pack:PACK_GENERAL, id:145},
    terrain_meadow {pack:PACK_GENERAL, id:146},
    terrain_flooplain {pack:PACK_GENERAL, id:146},
    terrain_road  {pack:PACK_GENERAL, id:147},
    terrain_bridge {pack:PACK_GENERAL, id:149, offset:170},
    terrain_wall  {pack:PACK_GENERAL, id:150},
    terrain_canal {pack:PACK_GENERAL, id:151},
    terrain_dune  {pack:PACK_GENERAL, id:211},
    terrain_teal  {pack:PACK_GENERAL, id:149, offset:200},
    terrain_bright_teal  {pack:PACK_GENERAL, id:149, offset:170},
    terrain_bright_blue  {pack:PACK_GENERAL, id:149, offset:170},
    terrain_dark_read  {pack:PACK_GENERAL, id:149, offset:165},
    terrain_purple {pack:PACK_GENERAL, id:149, offset:175},
    terrain_light_yellow {pack:PACK_GENERAL, id:149, offset:180},
    terrain_lilac  {pack:PACK_GENERAL, id:149, offset:195},
    terrain_orange {pack:PACK_GENERAL, id:149, offset:205},
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
