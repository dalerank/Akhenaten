log_info("akhenaten: health started")

city_health_rules {
    coverage_factor: 0.01
    mortuary_points: 25
    physician_points: 15
    food_points: 10
    second_food_points: 5
    third_food_points: 5
    physician_and_food_points: 40
    monthly_step: 2

    population_bonus [
        { pop: 200, bonus: 100 }
        { pop: 400, bonus: 90 }
        { pop: 600, bonus: 80 }
        { pop: 800, bonus: 70 }
        { pop: 1000, bonus: 60 }
        { pop: 1100, bonus: 50 }
        { pop: 1200, bonus: 40 }
        { pop: 1300, bonus: 30 }
        { pop: 1400, bonus: 20 }
        { pop: 1500, bonus: 10 }
    ]
}
