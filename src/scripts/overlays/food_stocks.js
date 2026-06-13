log_info("akhenaten: overlay food_stocks started")

[es=city_overlay]
overlay_food_stocks {
  id:OVERLAY_FOOD_STOCKS
  title: "#overlay_food_stocks"
  walkers:[FIGURE_MARKET_TRADER, FIGURE_MARKET_BUYER]
  buildings:[BUILDING_BAZAAR, BUILDING_FISHING_WHARF, BUILDING_GRANARY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}

  tooltips {
    not_provided { values:[ "#food_stocks_not_provided" ] }
    none { values:[ "#food_stocks_none" ] }
    low { values:[ "#food_stocks_low" ] }
    medium { values:[ "#food_stocks_medium" ] }
    high { values:[ "#food_stocks_high" ] }
  }
}

function food_stocks_is_food_resource(resource) {
    return resource >= RESOURCE_GRAIN && resource <= RESOURCE_GAMEMEAT
}

function food_stocks_total(house) {
    var stocks = 0
    for (var i = 0; i < 4; i++) {
        stocks += house.food(i)
    }
    return stocks
}

function food_stocks_column_height_for_house(house) {
    if (!house.model.food_types) {
        return -1
    }

    var pct = Math.calc_percentage(food_stocks_total(house), house.population)
    if (pct <= 0) {
        return 10
    }
    if (pct < 100) {
        return 5
    }
    if (pct <= 200) {
        return 1
    }
    return -1
}

[es=(overlay_food_stocks, show_figure)]
function food_stocks_show_figure(ev) {
    var fig = city.get_figure(ev.fid)
    if (!fig.valid) {
        city.overlay_show_figure = 0
        return
    }

    if (fig.type == FIGURE_MARKET_BUYER || fig.type == FIGURE_MARKET_TRADER
        || fig.type == FIGURE_DELIVERY_BOY || fig.type == FIGURE_FISHING_BOAT) {
        city.overlay_show_figure = 1
        return
    }

    if (fig.type == FIGURE_CART_PUSHER) {
        city.overlay_show_figure = food_stocks_is_food_resource(fig.resource) ? 1 : 0
        return
    }

    city.overlay_show_figure = 0
}

[es=(overlay_food_stocks, get_tooltip_for_building)]
function food_stocks_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        return
    }

    var tooltip_key = bazaar_access_food_tooltip_key(house)
    if (tooltip_key) {
        city.overlay_tooltip = tooltip_key
    }
}

[es=(overlay_food_stocks, get_column_height)]
function food_stocks_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = food_stocks_column_height_for_house(house)
}
