log_info("akhenaten: city festival started")

function city_festival_get_advice() {
    var m = city.festival.months_since_festival
    if (m <= 1) return 0
    if (m <= 6) return 1
    if (m <= 12) return 2
    if (m <= 18) return 3
    if (m <= 24) return 4
    if (m <= 30) return 5
    return 6
}

city.festival = {
    __property_getter: __city_get_festival_property
    @selected_god { }
    @selected_size { }
    @small_cost { }
    @large_cost { }
    @grand_cost { }
    @grand_alcohol { }
    @not_enough_alcohol { }
    @months_since_festival { }
    @is_planned { get: __city_festival_is_planned }

    get_advice: city_festival_get_advice
    select_god: __city_festival_select_god
    select_size: __city_festival_select_size
    schedule: __city_festival_schedule
}
