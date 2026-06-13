log_info("akhenaten: overlay bazaar_access started")

[es=city_overlay]
overlay_bazaar_access {
  id:OVERLAY_BAZAAR_ACCESS
  title: "#overlay_bazaar_access"
  walkers:[FIGURE_MARKET_BUYER, FIGURE_MARKET_TRADER]
  buildings:[BUILDING_BAZAAR, BUILDING_ROADBLOCK, BUILDING_GRANARY]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

function bazaar_access_food_stocks(house) {
    var stocks = 0
    for (var i = 0; i < 4; i++) {
        stocks += house.food(i)
    }
    return stocks
}

function bazaar_access_food_tooltip_key(house) {
    if (house.population <= 0) {
        return null
    }

    if (!house.model.food_types) {
        return "#food_stocks_not_provided"
    }

    var stocks_per_pop = Math.calc_percentage(bazaar_access_food_stocks(house), house.population)
    if (stocks_per_pop <= 0) {
        return "#food_stocks_none"
    } else if (stocks_per_pop < 100) {
        return "#food_stocks_low"
    } else if (stocks_per_pop <= 200) {
        return "#food_stocks_medium"
    }
    return "#food_stocks_high"
}

[es=(overlay_bazaar_access, get_tooltip_for_building)]
function bazaar_access_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        return
    }

    var tooltip_key = bazaar_access_food_tooltip_key(house)
    if (tooltip_key) {
        city.overlay_tooltip = tooltip_key
    }
}

[es=(overlay_bazaar_access, get_column_height)]
function bazaar_access_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    var height = house.bazaar_access / 10
    if (height < 0) {
        height = 0
    } else if (height > 8) {
        height = 8
    }
    city.overlay_column_height = height
}
