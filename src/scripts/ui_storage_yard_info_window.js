log_info("akhenaten: ui_storage_yard_info_window.js loaded")

var STORAGE_YARD_FIGURE_STATE_ALIVE = 1

[es=building_info_window]
info_window_storageyard {
    first_advisor       : ADVISOR_TRADE
    related_buildings [BUILDING_STORAGE_YARD, BUILDING_STORAGE_YARD_UP, BUILDING_STORAGE_ROOM]
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

        orders        : button({margin:{left:100, bottom:-40}, size:[270, 24], text:"${99.2}", onclick_event: "open_orders_window" }),

        button_help   : help_button({}),
        button_close  : close_button({}),
        mothball      : button({margin:{right:-90, bottom:-40}, size:[23, 23], textfn:building_info_window_text_mothball, onclick: building_info_window_toggle_mothball }),

        first_advisor : image_button({margin:{left:40, bottom:-40}, size:[28, 28], pack:PACK_GENERAL, id:106 }),
    }
}

[es=(info_window_storageyard, init)]
function info_window_storageyard_on_init(window) {
    var b = city.get_building(window.bid)

    var slot
    for (slot = 0; slot < 9; slot++) {
        window["good" + slot + "_icon"].image = RESOURCE_NONE
        window["good" + slot + "_text"].text = ""
    }

    var av = city.resources.available
    var gidx = 0
    for (var resName in av) {
        var rtype = av[resName]
        var loads = b.stored_resource(rtype)
        if (loads) {
            window["good" + gidx + "_icon"].image = rtype
            window["good" + gidx + "_text"].text = loads + " " + __loc(23, rtype)
            gidx++
            if (gidx >= 9) {
                break
            }
        }
    }
}

[es=(info_window_storageyard, init)]
function storage_yard_info_on_init_workers_info(window) {
    var grp = city.object_info.group
    var b = city.get_building(window.bid)
    var fig = b.get_figure(BUILDING_SLOT_SERVICE)

    if (fig.id && fig.state == STORAGE_YARD_FIGURE_STATE_ALIVE) {
        ev.cartstate_img.image = fig.resource
        ev.cartstate_desc.text = __loc(grp, 17)
    } else if (b.num_workers > 0) {
        ev.cartstate_img.image = RESOURCE_NONE
        ev.cartstate_desc.text = __loc(grp, 15)
    }
}


[es=(info_window_storageyard, open_orders_window)]
function info_window_storageyard_on_open_orders_window(window) {
    window_building_distribution_set_bid(window.bid)
    emit event_show_window{ id:"storage_yard_orders_window" }
}

