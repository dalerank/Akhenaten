log_info("akhenaten: overlay brewery started")

[es=city_overlay]
overlay_brewery {
  id:OVERLAY_BREWERY
  walkers:[]
  buildings:[]
}

[es=(overlay_brewery, get_tooltip_for_building)]
function brewery_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#beer_stocks_high"
        return
    }

    var beer = house.inv(3)
    if (beer <= 0) {
        city.overlay_tooltip = "#beer_stocks_none"
    } else if (beer <= 30) {
        city.overlay_tooltip = "#beer_stocks_low"
    } else if (beer <= 70) {
        city.overlay_tooltip = "#beer_stocks_medium"
    } else {
        city.overlay_tooltip = "#beer_stocks_high"
    }
}

[es=(overlay_brewery, get_column_height)]
function brewery_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    var height = house.inv(3) / 10
    if (height < 0) {
        height = 0
    } else if (height > 10) {
        height = 10
    }
    city.overlay_column_height = height
}
