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
    @months_since_festival { }
    @is_planned { get: __city_festival_is_planned }

    small_cost: 0
    large_cost: 0
    grand_cost: 0
    grand_alcohol: 0
    not_enough_alcohol: false

    get_advice: city_festival_get_advice
    select_god: __city_festival_select_god
    months_till_next: __city_festival_months_till_next
}

city.festival.calculate_costs = function() {
    var population = city.population

    city.festival.small_cost = Math.floor(population / 20) + 10
    city.festival.large_cost = Math.floor(population / 10) + 20
    city.festival.grand_cost = Math.floor(population / 5) + 40
    city.festival.grand_alcohol = Math.floor(population / 50) + 1
    city.festival.not_enough_alcohol = city.yards_stored(RESOURCE_BEER) < city.festival.grand_alcohol

    if (city.festival.not_enough_alcohol && city.festival.selected_size === 3) {
        __city_festival_select_size(2)
    }
}

city.festival.select_size = function(size) {
    city.festival.calculate_costs()
    if (size === 3 && city.festival.not_enough_alcohol) {
        return false
    }
    __city_festival_select_size(size)
    return true
}

city.festival.schedule = function() {
	city.festival.calculate_costs()
	var population = city.population
	var size = city.festival.selected_size
	var cost = 0
	var months = 0
	if (size === 1) {
		cost = city.festival.small_cost
		months = 1 + Math.floor(population / 1000) + 1
	} else if (size === 2) {
		cost = city.festival.large_cost
		months = 2 + Math.floor(population / 1500) + 1
	} else if (size === 3) {
		cost = city.festival.grand_cost
		months = 3 + Math.floor(population / 2000) + 1
	}
	var beer = (size === 3) ? city.festival.grand_alcohol : 0
	__city_festival_schedule(city.festival.selected_god, city.festival.selected_size, months, cost, beer)
}
