log_info("akhenaten: ui_tax_collector_window.js loaded")

function taxcollector_info_window_tax_level_text() {
    return __loc(60, 1) + " " + city.finance.tax_percentage + "%"
}

[es=building_info_window]
taxcollector_info_window {
    first_advisor : ADVISOR_FINANCIAL
    related_buildings [BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED]
    ui : {
        background    : outer_panel({size: [29, 17]}),
        title         : text({pos: [0, 12], size: [px(29), 20], text:"${text.0}", font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"}),
        deben_icon    : resource_icon({pos: [16, 46], resource:RESOURCE_GOLD}),
        tax_level     : label({pos:[px(29) / 2 + 40, 46], textfn: taxcollector_info_window_tax_level_text, font : FONT_NORMAL_BLACK_ON_LIGHT }),
        dec_tax       : arrowdown({pos:[px(29) / 2 + 170, 38], onclick: function() { emit event_finance_change_tax{ value: -1 } } }),
        inc_tax       : arrowup({pos:[px(29) / 2 + 193, 38], onclick: function() { emit event_finance_change_tax{ value: 1 } } }),
        money_text    : text({pos: [44, 44], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT }),
        warning_text  : text({pos: [28, 66], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        building_desc : text({pos: [28, 86], text:"${text.1}", wrap:px(27), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        inner_panel   : inner_panel({pos : [16, 136], size: [27, 5] }),
        workers_img   : image({pack:PACK_GENERAL, id:134, offset:14, pos:[30, 146] }),
        workers_text  : text({pos: [55, 150], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK }),
        workers_desc  : text({pos: [55, 165], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
        first_advisor : image_button({pos:[42, -1], size:[28, 28], pack:PACK_GENERAL, id:106 }),
        show_overlay  : button({
                                margin:{right:-64, bottom:-40}, size:[23, 23]
                                textfn: building_info_window_text_overlay
                                onclick: building_info_window_toggle_overlay
                               })

        mothball      : button({
                                margin:{right:-90, bottom:-40}, size:[23, 23]
                                textfn: building_info_window_text_mothball
                                onclick: building_info_window_toggle_mothball
                               })

        button_help   : help_button({}),
        button_close  : close_button({}),
    }
}

[es=(taxcollector_info_window, init)]
function taxcollector_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    var g = b.meta_text_id
    var amount = game_features.gameplay_change_new_tax_collection_system ? b.deben_storage : b.tax_income_or_storage
    window.money_text.text = __loc(g, 2) + " " + amount + " " + __loc(8, 0)

    var reason = b.has_road_access ? { group: g, id: 0 } : { group: 69, id: 25 }
    window.warning_text.text = __loc(reason.group, reason.id)

    var wid = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6, 5])
    window.workers_desc.text = __loc(g, wid)
}
