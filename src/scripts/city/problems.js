log_info("akhenaten: city problems started")

// OG figure_phrase_city_weights (figure_phrase.c): the weight of each city problem a walker can talk about.
// "below": the first step whose value is above the city's value gives the weight; "above": the first step whose
// value is below it. No step gives calm_weight. OG compares lowest god mood, kingdom rating and entertainment
// with <=, written here as < value + 1.
city_problem_rules {
    calm_weight: 1
    undefended_invasion_weight: 8
    health_below [ { value: 20, weight: 8 }, { value: 30, weight: 6 }, { value: 40, weight: 4 } ]
    food_months_below [ { value: 1, weight: 6 }, { value: 2, weight: 4 } ]
    worker_shortage_above [ { value: 20, weight: 8 }, { value: 10, weight: 6 }, { value: 5, weight: 4 } ]
    lowest_god_mood_below [ { value: 21, weight: 6 }, { value: 31, weight: 4 } ]
    kingdom_below [ { value: 1, weight: 8 }, { value: 20, weight: 6 }, { value: 40, weight: 4 } ]
    unemployment_above [ { value: 17, weight: 8 }, { value: 10, weight: 6 }, { value: 5, weight: 4 } ]
    entertainment_below [ { value: 1, weight: 6 }, { value: 20, weight: 4 } ]
}
