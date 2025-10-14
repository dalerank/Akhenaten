log_info("akhenaten: ui workshops info window started")

workshop_info_window {
    related_buildings [BUILDING_BREWERY_WORKSHOP, BUILDING_POTTERY_WORKSHOP
                       BUILDING_PAPYRUS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP, BUILDING_CATTLE_RANCH
                       BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP]
    ui {
        background    : outer_panel({size[29, 17] }),
        title         : text({pos[0, 16], size[px(27), 20], text:"${building.name}", font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text  : text({pos[20, 58], wrap:px(27), text:"${text.1}", font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        produce_icon  : resource_icon({pos[16, 16], prop:"${building.output_resource}" })
        ready_prod    : text({pos[38, 40], size[px(27), 20], text:"${text.2} ${industry.progress}% ${text.3}", font : FONT_NORMAL_BLACK_ON_LIGHT })
        workers_panel : inner_panel({pos[16, 116], size[27, 5] })
        workers_text  : text({pos[55, 122 + 10], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) })
        workers_desc  : text({pos[55, 122 + 26], font:FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true })
        workers_img   : image({pos[30, 122 + 6], pack:PACK_GENERAL, id:134, offset:14})
        resource_icon : resource_icon({pos[32, 205], prop:"${building.first_material}" })
        resource_stored : text({pos[55, 210], size[px(27), 20], text:"${text.12} ${building.first_material_stored}", font:FONT_NORMAL_BLACK_ON_LIGHT })
        
        button_help   : help_button({})
        button_close  : close_button({})
        mothball      : button({margin{right:-90, bottom:-40}, size[23, 23]})
    }
}

brickworks_info_window {
    related_buildings [BUILDING_BRICKS_WORKSHOP]
    ui : __baseui(workshop_info_window, {
        background    : outer_panel({size[29, 18] })
        warning_text  : text({pos[32, 58], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })

        resource_icon : resource_icon({pos[32, 205], prop:"${building.first_material}" })
        resource_stored : text({pos[55, 210], size[px(27), 20], text:"${text.14} ${building.first_material_stored}", font:FONT_NORMAL_BLACK_ON_LIGHT })

        resource_icon_b : resource_icon({pos: [32, 225], prop:"${building.second_material}" })
        resource_stored_b : text({pos[55, 230], size[px(27), 20], text:"${text.13} ${building.second_material_stored}", font:FONT_NORMAL_BLACK_ON_LIGHT })
    })
}

bricklayers_guild_info_window = {
    ui : __baseui(workshop_info_window, {

    })
}

carpenters_guild_info_window = {
    ui : __baseui(workshop_info_window, {

    })
}

stonemason_guild_info_window = {
    ui : __baseui(workshop_info_window, {

    })
}