log_info("akhenaten: city_ratings.js loaded")

city.rating = {
    __property_getter: __city_get_rating_property
    @culture {}
    @prosperity {}
    @monument {}
    @kingdom { get: __city_rating_kingdom }
}

city.rating.get_culture_explanation = function() {
	var min_percentage = 100
	var reason = 1
	var ar = city.avg_coverage.average_religion
	if (ar < min_percentage) {
		min_percentage = ar
		reason = 4
	}
	var cov = city.coverage
	if (cov.booth < min_percentage) {
		min_percentage = cov.booth
		reason = 5
	}
	if (cov.library < min_percentage) {
		min_percentage = cov.library
		reason = 2
	}
	if (cov.school < min_percentage) {
		min_percentage = cov.school
		reason = 1
	}
	if (cov.academy < min_percentage) {
		reason = 3
	}

    return reason
}

city.rating.get_monument_explanation = function() {
	var reason
	var fig = city.figures
	if (fig.kingdome_soldiers) {
		reason = 8
	} else if (fig.enemies) {
		reason = 7
	} else if (fig.rioters) {
		reason = 6
	} else {
		var mon = city.rating.monument
		if (mon < 10) {
			reason = 0
		} else if (mon < 30) {
			reason = 1
		} else if (mon < 60) {
			reason = 2
		} else if (mon < 90) {
			reason = 3
		} else if (mon < 100) {
			reason = 4
		} else {
			reason = 5
		}
	}

    return reason
}

function city_ratings_pct(value, total) {
	if (total <= 0) {
		return 0
	}
	return ((100 * value / total) | 0)
}

city.rating.get_prosperity_explanation = function() {
	var change = 0
	var profit = 0
	var unemp = city.labor.unemployment_percentage
	if (unemp < 5) {
		change += 1
	} else if (unemp >= 15) {
		change -= 1
	}

	if (city.finance.has_made_money) {
		change += 5
		profit = 1
	} else {
		change -= 1
	}

	var wages_kingdome = city.finance.wages_kingdome
	var avg_wage = (city.finance.wage_rate_paid_last_year / 12) | 0
	if (avg_wage >= wages_kingdome + 2) {
		change += 1
	} else if (avg_wage < wages_kingdome) {
		change -= 1
	}

	var pop = city.population_stats.current
	var pct_shanties = city_ratings_pct(city.population_stats.people_in_shanties, pop)
	if (pct_shanties > 30) {
		change -= 1
	}

	if (city_ratings_pct(city.population_stats.people_in_manors, pop) > 10) {
		change += 1
	}

	if (city.finance.tribute_not_paid_last_year) {
		change -= 1
	}

	if (city.entertainment.senet_house_plays > 0) {
		change += 1
	}

	var luxury = empire.luxury_goods_traded_sum
	if (luxury > 500) {
		change += 2
	} else if (luxury > 100) {
		change += 1
	}

	var pros = city.rating.prosperity
	var pros_max = city.rating.prosperity_max
	var year = game.simtime_year
	var start_year = scenario.start_year

	var reason
	if (pros <= 0 && year == start_year) {
		reason = 0
	} else if (pros >= pros_max) {
		reason = 1
	} else if (change > 0) {
		reason = 2
	} else if (!profit) {
		reason = 3
	} else if (unemp >= 15) {
		reason = 4
	} else if (avg_wage < wages_kingdome) {
		reason = 5
	} else if (pct_shanties > 30) {
		reason = 6
	} else if (city.finance.tribute_not_paid_last_year) {
		reason = 7
	} else {
		reason = 9
	}

	return reason
}

city.rating.get_kingdom_explanation = function() {
	var salary_delta = city.kingdome.salary_rank - city.kingdome.player_rank
	var kingdom_salary_penalty = 0
	if (city.kingdome.player_rank != 0) {
		if (salary_delta > 0) {
			kingdom_salary_penalty = salary_delta + 1
		}
	} else if (salary_delta > 0) {
        kingdom_salary_penalty = salary_delta
    }

	var tribute_years = city.finance.tribute_not_paid_total_years
	var ign = city.kingdome.kingdom_ignored_request_penalty
	var mile = city.kingdome.kingdom_milestone_penalty
	var kchange = city.kingdome.kingdom_change

	var kingdom_explanation = 0
	if (kingdom_salary_penalty >= 8) {
		kingdom_explanation = 1
	} else if (tribute_years >= 3) {
		kingdom_explanation = 2
	} else if (ign >= 5) {
		kingdom_explanation = 3
	} else if (kingdom_salary_penalty >= 5) {
		kingdom_explanation = 4
	} else if (tribute_years >= 2) {
		kingdom_explanation = 5
	} else if (ign >= 3) {
		kingdom_explanation = 6
	} else if (kingdom_salary_penalty >= 3) {
		kingdom_explanation = 7
	} else if (city.finance.tribute_not_paid_last_year) {
		kingdom_explanation = 8
	} else if (kingdom_salary_penalty >= 2) {
		kingdom_explanation = 9
	} else if (mile) {
		kingdom_explanation = 10
	} else if (kingdom_salary_penalty) {
		kingdom_explanation = 11
	} else if (city.kingdome.kingdom_change == 2) {
		kingdom_explanation = 12
	} else if (city.kingdome.kingdom_change == 1) {
		kingdom_explanation = 13
	} else {
		kingdom_explanation = 0
	}

    return kingdom_explanation
}

