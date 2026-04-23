log_info("akhenaten: city labor started")

function get_labor_category(index) {
    return {
        __property_getter: function(property) { return __city_get_labor_category_property(index, property) }
        @workers_needed { }
        @workers_allocated { }
        @priority { }
    }
}

city.labor = extend(__city_labor, {
    get_category: get_labor_category

    food_production : get_labor_category(LABOR_CATEGORY_FOOD_PRODUCTION)
    industry_commerce : get_labor_category(LABOR_CATEGORY_INDUSTRY_COMMERCE)
    entertainment : get_labor_category(LABOR_CATEGORY_ENTERTAINMENT)
    religion : get_labor_category(LABOR_CATEGORY_RELIGION)
    education : get_labor_category(LABOR_CATEGORY_EDUCATION)
    water_health : get_labor_category(LABOR_CATEGORY_WATER_HEALTH)
    infrastructure : get_labor_category(LABOR_CATEGORY_INFRASTRUCTURE)
    government : get_labor_category(LABOR_CATEGORY_GOVERNMENT)
    military : get_labor_category(LABOR_CATEGORY_MILITARY)
    culture : get_labor_category(LABOR_CATEGORY_CULTURE)
    house : get_labor_category(LABOR_CATEGORY_HOUSE)
})
