log_info("akhenaten: ui food mill window started")

var FOOD_MILL_INFO_FOOD_SLOTS = 4
var FOOD_MILL_INFO_FIRST_FOOD = RESOURCE_GRAIN
var FOOD_MILL_INFO_LAST_FOOD = RESOURCE_GAMEMEAT

var FOOD_MILL_VARIETY_KEYS = [
    "#food_mill_variety_none",
    "#food_mill_variety_bland",
    "#food_mill_variety_plain",
    "#food_mill_variety_appetizing",
    "#food_mill_variety_tasty"
]

[es=building_info_window]
info_window_food_mill {
    related_buildings [BUILDING_FOOD_MILL]
    ui : {
        background   : outer_panel({size: [29, 17]})
        title        : text({text: "#building_food_mill", pos: [0, 12], size: [px(28), 0], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text : text({pos: [32, 40], wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
        variety      : text({pos: [34, 70], font : FONT_NORMAL_BLACK_ON_LIGHT })
        storing      : text({pos: [34, 86], font : FONT_NORMAL_BLACK_ON_LIGHT })
        free_space   : text({pos: [220, 86], font : FONT_NORMAL_BLACK_ON_LIGHT })
        food0_icon   : resource_icon({pos:[34, 104]})
        food0_text   : text({pos:[68, 111], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon   : resource_icon({pos:[240, 104] })
        food1_text   : text({pos:[274, 111], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon   : resource_icon({pos:[34, 128] })
        food2_text   : text({pos:[68, 135], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon   : resource_icon({pos:[240, 128] })
        food3_text   : text({pos:[274, 135], font: FONT_NORMAL_BLACK_ON_LIGHT })
        workers_panel: inner_panel({pos:[16, 162], size:[27, 4] })
        workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[40, 168] })
        workers_text : text({pos:[70, 174], font: FONT_NORMAL_BLACK_ON_DARK })
        orders       : button({margin:{centerx:-135, bottom:-40}, size:[270, 25], text:"${98.5}", onclick_event: "open_orders_window" })
        button_help  : help_button({})
        button_close : close_button({})
        show_overlay : button({
                               margin:{right:-64, bottom:-40}, size:[23, 23]
                               textfn: building_info_window_text_overlay
                              })
        mothball     : button({
                               margin:{right:-90, bottom:-40}, size:[23, 23]
                               textfn: building_info_window_text_mothball
                              })
    }
}



[es=(info_window_food_mill, init)]
function info_window_food_mill_on_init(window) {
    __log_marker("window_show:info_window_food_mill")
    var mill = city.get_food_mill(window.bid)
    if (!mill) {
        return
    }

    var warning_text = "#building_food_mill_info"
    if (!mill.has_road_access) {
        warning_text = "#food_mill_no_road_access"
    }
    window.warning_text.text = fmt(warning_text)

    var variety = mill.food_variety()
    if (variety < 0) {
        variety = 0
    }
    if (variety > 4) {
        variety = 4
    }
    window.variety.text = fmt("#food_mill_quality_now " + FOOD_MILL_VARIETY_KEYS[variety]
        + " (${types})", { types: variety })

    window.storing.text = fmt("#food_mill_storing ${mill.total_stored()} #food_mill_units", { mill: mill })
    window.free_space.text = fmt("#food_mill_space_for ${mill.free_space()} #food_mill_units", { mill: mill })

    for (var i = 0; i < FOOD_MILL_INFO_FOOD_SLOTS; i++) {
        window["food" + i + "_icon"].image = RESOURCE_NONE
        window["food" + i + "_text"].text = ""
    }

    var food_index = 0
    for (var r = FOOD_MILL_INFO_FIRST_FOOD; r <= FOOD_MILL_INFO_LAST_FOOD; r++) {
        var stored = mill.amount(r)
        if (!stored) {
            continue
        }
        if (food_index >= FOOD_MILL_INFO_FOOD_SLOTS) {
            break
        }

        window["food" + food_index + "_icon"].image = r
        window["food" + food_index + "_text"].text = stored + " " + __loc(23, r)
        food_index++
    }

    window.workers_text.text = mill.num_workers + " " + __loc(8, 12) + " (" + mill.max_workers + " " + __loc(69, 0)
}

[es=(info_window_food_mill, open_orders_window)]
function info_window_food_mill_on_open_orders_window(window) {
    emit event_show_window{ id: "granary_orders_window" }
}
