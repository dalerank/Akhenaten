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

info_window_figure_animal = {
    ui : baseui(figure_info_window, {

    })
}

figure_warship_info_window = {
    ui : {
        background       : outer_panel({size: [29, 23]}),
        name             : text_center({pos: [16, 16], size: [px(27), 20], text:"${figure.class_name}", font : FONT_LARGE_BLACK_ON_DARK }),
        hullstrength_lb  : text({pos: [102, 58], text:"${184.2}" }),
        hullstrength_val : text({pos: [232, 58], text:"" }),
        crewfatique_lb   : text({pos: [102, 88], text:"${184.27}" }),
        crewfatique_val  : text({pos: [232, 88], text:"" }),

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
    ui : baseui(figure_info_window, {
        typename         : text({pos: [92, 139], text:"${figure.class_name} ( @Y${figure.home}& )", font : FONT_NORMAL_BLACK_ON_DARK, rich:true, scroll:false }),
        items            : text({pos: [102, 158], size:[px(29), 20], font : FONT_NORMAL_BLACK_ON_DARK, rich:true, scroll:false }),
        phrase           : text({pos: [90, 180], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(22), multiline:true }),

        debug_stuck      : text({pos: [120, 260], font : FONT_NORMAL_BLACK_ON_DARK, wrap:px(22), multiline:true }),
    })
}

[es=building_info_window_init]
function building_info_window_on_init(window) {
    if (window.mothball) {
        var b = city.get_building(window.bid)
        window.mothball.enabled = b.max_workers && b.max_workers > 0
        window.mothball.tooltip = __loc(54, b.state == 1 ? 16 : 17)
    }
}

function building_info_window_toggle_overlay() {
    var b = city.get_building(city.object_info.bid)
    city.current_overlay = (city.current_overlay == b.overlay) ? OVERLAY_NONE : b.overlay
}

function building_info_window_text_mothball(window) {
    var b = city.get_building(city.object_info.bid)
    return (b.state == 1 ? "x" : "")
}

function building_info_window_text_overlay(window) {
    var b = city.get_building(city.object_info.bid)
    return (city.overlay == b.overlay ? "V" : "v")
}

function building_info_window_toggle_mothball() {
    var b = city.get_building(city.object_info.bid)
    if (b.max_workers) {
        b.mothball_toggle()
    }
}

building_info_window {
    ui {
        background     : outer_panel({size: [29, 17]})
        title          : text({ pos[0, 16], text:"${building.name}", size[px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center" })
        warning_text   : text({ pos[20, 46], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        inner_panel    : inner_panel({
                                        pos[16, 100], size[27, 5]
                                        ui {
                                            workers_img : image({pack:PACK_GENERAL, id:134, offset:14, pos[20, 10] })
                                            workers_text : text({pos[50, 16], text:"${building.num_workers} ${loc.building_employee} ( ${model.laborers}  ${loc.building_employee_needed} )", font: FONT_NORMAL_BLACK_ON_DARK})
                                            workers_desc : text({pos[50, 16 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) })
                                        }
                                    })
        first_advisor  : image_button({ pos[40, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        second_advisor : image_button({ pos[64, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        third_advisor  : image_button({ pos[96, -1], size[28, 28], pack:PACK_GENERAL, id:106 })

        show_overlay   : button({
                                  margin{right:-64, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_overlay
                                  onclick: building_info_window_toggle_overlay
                                })
        mothball       : button({
                                  margin{right:-90, bottom:-40}, size[23, 23]
                                  textfn: building_info_window_text_mothball
                                  onclick: building_info_window_toggle_mothball
                                })

        button_help    : help_button({})
        button_close   : close_button({})
    }
}

info_window_ferry {
    ui : baseui(building_info_window, {
        background  : outer_panel({size: [29, 20]}),
    })
}

info_window_hunting_lodge {
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 20]}),
        resource     : resource_icon({ pos:[10, 10], prop:"${building.output_resource}" }),
        resource_amount : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
    })
}

info_window_mastaba = {
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title         : text({pos: [0, 16], text:"${building.name}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        subtitle      : text({pos: [32, 46], text:"${text.12}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        progress_text : text({pos: [32, 66], size:[px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [32, 96], size:[px(27), -1], wrap:px(27), multiline:true, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        bricks_icon   : resource_icon({pos: [32, 200], resource: RESOURCE_BRICKS }),
        bricks_text   : text({pos: [70, 204], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        clay_icon     : resource_icon({pos: [32, 230], resource: RESOURCE_CLAY }),
        clay_text     : text({pos: [70, 234], size:[px(15), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[260, 215] }),
        workers_text  : text({pos: [290, 219], size:[px(10), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
    }
}

info_window_fishing_wharf = {
    ui : baseui(building_info_window, {
        resource_img : { type : "resource_icon", pos: [32, 186] },
        storage_desc : { type : "text", pos: [62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT },
    })
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

info_window_burning_ruin = {
    open_sounds : [ "wavs/fire.wav" ],
    ui : {
        background    : outer_panel({size: [29, 18]}),
        title               : text({pos: [0, 16], text:"${111.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        warning_text    : text({pos: [0, 46], size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
        subtitle          : text({pos: [32, 66], text:"${111.1}", size: [px(27), -1], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
}

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
        first_advisor : image_button({ pos[42, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        second_advisor: image_button({ pos[64, -1], size[28, 28], pack:PACK_GENERAL, id:106 })
        third_advisor : image_button({ pos[96, -1], size[28, 28], pack:PACK_GENERAL, id:106 })

        show_overlay  : button({
                                margin:{right:-64, bottom:-40}, size[23, 23]
                                textfn:building_info_window_text_overlay
                                onclick: building_info_window_toggle_overlay
                               })

        mothball      : button({
                                 margin:{right:-90, bottom:-40}, size[23, 23]
                                 textfn:building_info_window_text_mothball
                                 onclick: building_info_window_toggle_mothball
                               })

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

health_info_window = {
    ui : baseui(building_info_window, {

    })
}

warshipwharf_info_window = {
    first_advisor       : ADVISOR_MILITARY,
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 16]}),
        resource_icon : resource_icon({pos: [32, 56] }),
        resource_stored : text({pos: [60, 60], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_desc  : text({pos: [70, 116 + 16], font: FONT_NORMAL_BLACK_ON_DARK,  multiline:true, wrap:px(24) }),
    })
}

shipyard_info_window = {
    ui : baseui(building_info_window, {
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

info_window_senet_house = {
    ui : baseui(building_info_window, {
        advice        : text({pos: [36, 164], wrap:400, font : FONT_NORMAL_BLACK_ON_DARK, multiline:true }),
    })
}

info_window_bullfight = {
    ui : baseui(building_info_window, {

    })
}

info_window_gatehouse = {
    ui : baseui(building_info_window, {

    })
}

info_window_milacademy = {
    ui : baseui(building_info_window, {

    })
}


well_info_window = {
    ui : {
        background    : outer_panel({size: [29, 14] }),
        title           : text({pos: [0, 12], size: [px(28), 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center", text:"${loc.well_info_title}"}),
        text          : text({pos: [32, 56], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
    }
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
