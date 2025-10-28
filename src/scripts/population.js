log_info("akhenaten: population started")

city_population_rules {
    births_per_age_decennium [0, 3, 16, 9, 2, 0, 0, 0, 0, 0]

    milestones [
        {pop:100, message: "#message_population_100"}
        {pop:500, message: "#message_population_500"}
        {pop:1000, message: "#message_population_1000"}
        {pop:2000, message: "#message_population_2000"}
        {pop:3000, message: "#message_population_3000"}
        {pop:5000, message: "#message_population_5000"}
        {pop:10000, message: "#message_population_10000"}
        {pop:15000, message: "#message_population_15000"}
        {pop:20000, message: "#message_population_20000"}
        {pop:25000, message: "#message_population_25000"}
    ]
}