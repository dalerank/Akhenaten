log_info("akhenaten: overlay tax income started")

[es=city_overlay]
overlay_tax_income {
  id:OVERLAY_TAX_INCOME
  title: "#overlay_tax_income"
  walkers:[FIGURE_TAX_COLLECTOR]
  buildings:[BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED, BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

function tax_income_denarii(house) {
    return Math.floor((house.tax_income_or_storage / 2) * city.finance.tax_percentage / 100)
}

[es=(overlay_tax_income, get_tooltip_for_building)]
function tax_income_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = __loc(66, 43)
        return
    }

    var denarii = tax_income_denarii(house)
    if (denarii > 0) {
        city.overlay_tooltip = denarii + __loc(66, 45)
        return
    }

    if (house.tax_coverage > 0) {
        city.overlay_tooltip = __loc(66, 44)
        return
    }

    city.overlay_tooltip = __loc(66, 43)
}

[es=(overlay_tax_income, get_column_height)]
function tax_income_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(tax_income_denarii(house) / 10)
}
