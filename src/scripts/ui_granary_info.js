log_info("akhenaten: ui granary window started")

var GRANARY_INFO_FOOD_SLOTS = 4
var GRANARY_INFO_FIRST_FOOD = RESOURCE_GRAIN
var GRANARY_INFO_LAST_FOOD = RESOURCE_GAMEMEAT

[es=building_info_window]
info_window_granary {
    related_buildings [BUILDING_GRANARY, BUILDING_GRANARY_UP]
    ui : {
        background   : outer_panel({size: [29, 17]})
        title        : text({text: "#granary_info_title", pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text : text({pos: [32, 40], wrap:px(28), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        storing      : text({pos: [34, 60], font : FONT_NORMAL_BLACK_ON_LIGHT })
        free_space   : text({pos: [220, 60], font : FONT_NORMAL_BLACK_ON_LIGHT })
        food0_icon   : resource_icon({pos:[34, 68]})
        food0_text   : text({pos:[68, 75], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon   : resource_icon({pos:[240, 68] })
        food1_text   : text({pos:[274, 75], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon   : resource_icon({pos:[34, 92] })
        food2_text   : text({pos:[68, 99], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon   : resource_icon({pos:[240, 92] })
        food3_text   : text({pos:[274, 99], font: FONT_NORMAL_BLACK_ON_LIGHT })
        workers_panel: inner_panel({pos:[16, 142], size:[27, 5] })
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 148] })
        workers_text : text({pos:[70, 154], font: FONT_NORMAL_BLACK_ON_DARK })
        workers_desc : text({pos:[70, 168], font: FONT_NORMAL_BLACK_ON_DARK })
        orders       : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"${98.5}", onclick_event: "open_orders_window" })
        button_help  : help_button({})
        button_close : close_button({})
        show_overlay : button({
                               margin:{right:-64, bottom:-40}, size:[23, 23]
                               textfn: building_info_window_text_overlay
                               onclick: building_info_window_toggle_overlay
                              })
        mothball     : button({
                               margin:{right:-90, bottom:-40}, size:[23, 23]
                               textfn: building_info_window_text_mothball
                               onclick: building_info_window_toggle_mothball
                              })
    }
}

[es=(info_window_granary, init)]
function info_window_granary_on_init(window) {
    __log_marker("window_show:info_window_granary")
    var b = city.get_building(window.bid)
    var granary = city.get_granary(window.bid)

    window_building_distribution_set_bid(window.bid)

    var warning_text = ""
    if (!b.has_road_access) {
        warning_text ="#granary_no_road_access"
    } else if (scenario.kingdom_supplies_grain) {
        warning_text = "#granary_kingdom_supplies_grain"
    }
    window.warning_text.text = fmt(warning_text)

    window.storing.text = fmt("#granary_storing ${granary.total_stored()} #granary_units", { granary: granary })
    window.free_space.text = fmt("#granary_space_for ${granary.free_space()} #granary_units", { granary: granary })

    for (var i = 0; i < GRANARY_INFO_FOOD_SLOTS; i++) {
        window["food" + i + "_icon"].image = RESOURCE_NONE
        window["food" + i + "_text"].text = ""
    }

    var food_index = 0
    for (var r = GRANARY_INFO_FIRST_FOOD; r <= GRANARY_INFO_LAST_FOOD; r++) {
        var stored = granary.amount(r)
        if (!stored) {
            continue
        }

        window["food" + food_index + "_icon"].image = r
        window["food" + food_index + "_text"].text = stored + " " + __loc(23, r)
        food_index++
    }

    window.workers_text.text = b.num_workers + " " + __loc(8, 12) + " (" + b.max_workers + " " + __loc(69, 0)
}

[es=(info_window_granary, open_orders_window)]
function info_window_granary_on_open_orders_window(window) {
    window_building_distribution_set_bid(window.bid)
    __window_granary_orders_show()
}
