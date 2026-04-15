log_info("akhenaten: city_monuments.js started")

[es=(city_monuments, advance_year)]
function city_update_yearly_monument_rating() {
	var y = city.rating.monument_years_of_monument
	var ncr = city.rating.monument_num_criminals
	var nri = city.rating.monument_num_rioters
	var db = city.rating.monument_destroyed_buildings
	var m = city.rating.monument

	var change = y < 2 ? 2 : 5
	if (ncr) {
		change -= 1
	}
	if (nri) {
		change -= 5
	}
	if (db) {
		change -= db
	}

	var new_years = (nri || db) ? 0 : (y + 1)

	var city_pop = city.population
	var max_pop_limit = city_pop < 4000 ? city_pop : 4000
	var cap_part = (max_pop_limit / 1000) | 0
	if (cap_part < 1) {
		cap_part = 1
	}
	var monument_ratings_cap = cap_part * 25

	var new_m = m + change
	if (new_m < 0) {
		new_m = 0
	}

	if (new_m > monument_ratings_cap) {
		new_m = monument_ratings_cap
	}

	__city_ratings_apply_monument_yearly(new_m, new_years, expl)
}