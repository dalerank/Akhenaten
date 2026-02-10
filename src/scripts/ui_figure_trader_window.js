log_info("akhenaten: ui trader info window started")

figure_trader_info_window {
    related_figures [FIGURE_TRADE_SHIP, FIGURE_TRADE_CARAVAN, FIGURE_TRADE_CARAVAN_DONKEY]
    ui {
        background: outer_panel({ size[29, 19] })
        inner_panel: inner_panel({ pos[16, 40], size[27, 12] })
        //border         : border({border:0, pos : [24, 52], size[px(26), 188] })
        bigimage: image({ pos[26, 50], pack: PACK_UNLOADED, id: 25 })
        name: text({ pos[90, 58], text: "${figure.name}", font: FONT_LARGE_BLACK_ON_DARK })
        typename: text({ pos[92, 86], text: "${figure.class_name} @Y${figure.city_name}&", font: FONT_NORMAL_BLACK_ON_DARK, rich: true, scroll: false })

        action: text({ pos[92, 106], text: "(${figure.action_tip})", font: FONT_NORMAL_YELLOW })
        capacity: text({ pos[92, 130], text: "${loc.trader_capacity} ${figure.capacity}", font: FONT_NORMAL_BLACK_ON_DARK })

        buy: text({ pos[92, 150], text: "${loc.trader_bought}", font: FONT_NORMAL_BLACK_ON_DARK })
        buy_text: text({ pos[150, 150], rich: true, scroll: false })

        sell: text({ pos[92, 170], text: "${loc.trader_sold}", font: FONT_NORMAL_BLACK_ON_DARK })
        sell_text: text({ pos[150, 170], rich: true, scroll: false })

        phrase: text({ pos[90, 200], font: FONT_NORMAL_BLACK_ON_DARK, wrap: px(21), multiline: true, scroll: false })

        button_help: help_button({})
        button_close: close_button({})

        show_path: button({ margin{right: -64, bottom: -40}, size[23, 23] })
    }
}