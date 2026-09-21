log_info("akhenaten: overlay goods_stock helper started")

function goods_stock_clamp_column(amount) {
    var height = Math.floor(amount / 10)
    if (height < 0) {
        height = 0
    } else if (height > 10) {
        height = 10
    }
    return height
}

function goods_stock_tooltip_key(prefix, amount) {
    if (amount <= 0) {
        return "#" + prefix + "_stocks_none"
    }
    if (amount <= 30) {
        return "#" + prefix + "_stocks_low"
    }
    if (amount <= 70) {
        return "#" + prefix + "_stocks_medium"
    }
    return "#" + prefix + "_stocks_high"
}

function goods_stock_food_amount(house, resource) {
    for (var i = 0; i < 4; i++) {
        if (city.allowed_foods(i) == resource) {
            return house.get_food(i)
        }
    }
    return 0
}

function goods_stock_apply_tooltip(ev, amount, prefix) {
    var house = city.get_house(ev.bid)
    if (!house || house.is_vacant_lot || house.population <= 0) {
        return
    }
    city.overlay_tooltip = goods_stock_tooltip_key(prefix, amount)
}

function goods_stock_apply_column(ev, amount) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0 || amount <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = goods_stock_clamp_column(amount)
}
