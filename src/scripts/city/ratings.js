log_info("akhenaten: city_ratings.js loaded")

// OG culture_records (city_data.c): the culture rating is the lowest of these points; the index of the lowest
// record is the advisor's explanation. Band 0 is coverage up to limits[0], band i is coverage below limits[i],
// past the last limit the last points. The bonus re-bands every record by bonus_limits and adds bonus_points
// for each one bonus_margin below the lowest (OG city_ratings_culture_bonus).
culture_rating {
  records [
    { coverage: "jugglers",  points [5, 15, 25, 40, 55, 75, 100],   limits [0, 20, 40, 60, 80, 100] }
    { coverage: "musicians", points [10, 20, 30, 45, 60, 80, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "dancers",   points [15, 25, 35, 50, 65, 85, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "senet",     points [50, 55, 65, 75, 85, 95, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "zoo",       points [70, 75, 80, 85, 90, 95, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "religion",  points [0, 10, 25, 40, 60, 85, 100],   limits [0, 20, 40, 60, 80, 100] }
    { coverage: "school",    points [40, 45, 50, 60, 75, 85, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "library",   points [60, 65, 70, 75, 80, 90, 100],  limits [0, 20, 40, 60, 80, 100] }
    { coverage: "dentist",   points [15, 20, 25, 35, 50, 65, 100],  limits [0, 20, 40, 60, 80, 90] }
    { coverage: "physician", points [20, 25, 30, 40, 55, 70, 100],  limits [0, 20, 40, 60, 80, 90] }
    { coverage: "mortuary",  points [35, 45, 55, 70, 85, 100, 100], limits [0, 20, 40, 60, 80, 100] }
  ]
  bonus_limits [0, 20, 40, 60, 80, 100]
  bonus_margin : 30
  bonus_points : 5
}

// OG city_ratings_update_prosperity: recomputed in these months; the change is the sum of the terms below.
// Finances compare last year's income with its expenses (the fallback terms add back half of / all of the
// construction). Unemployment below unemployment_low gives its change, otherwise the change of the highest
// limit reached. Wages compare the yearly average wage rate with the kingdom wage (minus ra_oracle_wage_bonus
// with a Ra complex oracle): the first wage_above reached, else the first wage_below undercut. Shares are
// percent of the population.
prosperity_rating {
  months [0, 3, 6, 9]
  finance_profit : 5
  finance_construction_profit : 3
  finance_loss : -8
  finance_construction_loss : -5
  trade : 1
  workers_needed : -1
  unemployment_low : 5
  unemployment_low_change : 2
  unemployment_limits [5, 10, 15, 20]
  unemployment_changes [0, -1, -2, -3]
  food_types_min : 2
  few_food_types_change : -1
  wage_above [6, 1]
  wage_above_changes [2, 1]
  wage_below [-10, -5, 0]
  wage_below_changes [-3, -2, -1]
  ra_oracle_wage_bonus : -2
  huts_share : 95
  huts_change : -1
  manors_share : 10
  manors_change : 2
  tribute_not_paid_change : -1
  senet_change : 1
  completed_monument_change : 1
}

city.rating = {
    __property_getter: __city_get_rating_property
    @culture {}
    @prosperity {}
    @prosperity_max {}
    @monument {}
    @culture_explanation {}
    @prosperity_explanation {}
    @prosperity_trend {}
    @kingdom { get: __city_rating_kingdom }
}

// OG: the index of the lowest culture record (ratings advisor text 53/(9 + index)).
city.rating.get_culture_explanation = function() {
	return city.rating.culture_explanation
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

// OG ratings advisor: recomputes the explanation on open; text 53/(20 + trend) then 53/(20 + reason).
city.rating.get_prosperity_explanation = function() {
	__city_rating_update_prosperity_explanation()
	return { trend: city.rating.prosperity_trend, reason: city.rating.prosperity_explanation }
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

