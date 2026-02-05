log_info("akhenaten: ui bazaar window started")

[es=building_info_window]
bazaar_info_window {
    related_buildings [BUILDING_BAZAAR, BUILDING_BAZAAR_UP]
    ui {
        background   : outer_panel({size[29, 17]})
        title        : text({text: "#bazaar_info_title", pos[0, 10], size: [16 * 29, 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text : text({pos[32, 36], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true})

        food0_icon   : resource_icon({pos[32, 85]})
        food0_text   : text({pos: [64, 90], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon   : resource_icon({pos[142, 85] })
        food1_text   : text({pos[174, 90], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon   : resource_icon({pos[252, 85] })
        food2_text   : text({pos[284, 90], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon   : resource_icon({pos[362, 85] })
        food3_text   : text({pos[394, 90], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good0_icon   : resource_icon({pos[32, 110] })
        good0_text   : text({pos[64, 114], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good1_icon   : resource_icon({pos[142, 110] })
        good1_text   : text({pos[174, 114], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good2_icon   : resource_icon({pos[252, 110] })
        good2_text   : text({pos[284, 114], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good3_icon   : resource_icon({pos[362, 110] })
        good3_text   : text({pos[394, 114], font: FONT_NORMAL_BLACK_ON_LIGHT })

        workers_panel: inner_panel({pos[16, 136], size[27, 4] })
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 142 + 6] })
        workers_text : text({pos[70, 142 + 12], text:"${building.num_workers} ${8.12} ( ${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) })
        workers_desc : text({pos[70, 142 + 26], font: FONT_NORMAL_BLACK_ON_DARK })
        orders       : button({margin{left:100, bottom:-40}, size[270, 25], text:"${98.5}", onclick:__window_bazaar_orders_show })
        show_overlay : button({margin{right:-64, bottom:-40}, size[23, 23]})
        mothball     : button({margin{right:-90, bottom:-40}, size[23, 23]})

        button_help  : help_button({})
        button_close : close_button({})
    }
}

bazaar_orders_window {
    ui {
        background   : outer_panel({size[29, 17]}),
        title        : text({pos[0, 12], size[px(28), 0], text:{group:98, id:5}, font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        orders_panel : inner_panel({pos[16, 42], size[27, 11] })
        accept_none  : button({pos[80, -1], size[300, 24], text:{group:99, id:7}, margin{bottom:-38} })

        item_orders_column : dummy({margin{centerx:0}})
        item_icon_column : dummy({pos[25, 0]})
        item_name_column : dummy({pos[55, 0], font:FONT_NORMAL_WHITE_ON_DARK })
        item_row     : dummy({size[px(11), 20]})
        items_area   : dummy({pos[0, 50]})
        item_icon_column_2 : dummy({pos[px(29) - 40, 0]})

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

[es=bazaar_info_window_init]
function bazaar_info_window_init(window) {
    var bazaar = city.get_bazaar(window.bid)
    var meta_text_id = bazaar.meta_text_id
    var reason = { group: 0, id: 0 }


    if (bazaar.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (bazaar.num_workers <= 0) {
        reason = { group: meta_text_id, id: 2 }
    }

    if (reason.group) {
        window.workers_desc.text = ""
        window.workers_desc.text = __loc(reason.group, reason.id)
    }
}

[es=bazaar_info_window_init]
function bazaar_info_window_init_warning_text(window) {
    var bazaar = city.get_bazaar(window.bid)
    var meta_text_id = bazaar.meta_text_id

    var warning_text = ""
    var amount = bazaar.idx_amount(0) || bazaar.idx_amount(1) || bazaar.idx_amount(2) || bazaar.idx_amount(3)
    if (amount > 0) {
        var buyer = bazaar.get_figure(BUILDING_SLOT_MARKET_BUYER)
        var trader = bazaar.get_figure(BUILDING_SLOT_SERVICE)

        if (buyer.valid && trader.valid) {
            warning_text = __loc(meta_text_id, 1)
        } else if (buyer.valid) {
            warning_text = __loc(meta_text_id, 10)
        } else if (trader.valid) {
            var state = (trader.action_state == ACTION_126_ROAMER_RETURNING) ? 12 : 11
            warning_text = __loc(meta_text_id, state)
        }
    } else {
       warning_text = __loc(meta_text_id, 4)
    }

    window.warning_text.text = warning_text
}

[es=bazaar_info_window_init]
function bazaar_info_window_draw_foods(window) {
    var bazaar = city.get_bazaar(window.bid)

    function draw_food(bazaar, index, icon, text) {
        var resource = city.allowed_foods(index)
        icon.image = resource
        text.text = (resource != RESOURCE_NONE) ? (" " + bazaar.resource_amount(resource)) : ""
        text.font = bazaar.idx_accepted(index) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW
    }

    draw_food(bazaar, 0, window.food0_icon, window.food0_text)
    draw_food(bazaar, 1, window.food1_icon, window.food1_text)
    draw_food(bazaar, 2, window.food2_icon, window.food2_text)
    draw_food(bazaar, 3, window.food3_icon, window.food3_text)
}

[es=bazaar_info_window_init]
function bazaar_info_window_draw_goods(window) {
    var bazaar = city.get_bazaar(window.bid)

    function draw_good(bazaar, resource, index, icon, text) {
        icon.image = resource
        text.font = bazaar.idx_accepted(index) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW
        text.text = bazaar.resource_amount(resource)
    }

    draw_good(bazaar, RESOURCE_POTTERY, 4, window.good0_icon, window.good0_text)
    draw_good(bazaar, RESOURCE_LUXURY_GOODS, 5, window.good1_icon, window.good1_text)
    draw_good(bazaar, RESOURCE_LINEN, 6, window.good2_icon, window.good2_text)
    draw_good(bazaar, RESOURCE_BEER, 7, window.good3_icon, window.good3_text)
}