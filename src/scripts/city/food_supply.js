log_info("akhenaten: city food supply started")

// OG city/food_supply.c (city_resource_food_supply_percentage) constants.
city_food_supply_rules {
    food_farms [
        BUILDING_GRAIN_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_FIGS_FARM,
        BUILDING_GRAIN_MEADOW_FARM, BUILDING_LETTUCE_MEADOW_FARM, BUILDING_POMEGRANATES_MEADOW_FARM,
        BUILDING_CHICKPEAS_MEADOW_FARM, BUILDING_FIGS_MEADOW_FARM
    ]
    farm_produce_per_worker_pct : 16
    farm_fertility_max : 99
    farm_produce_scale : 10
    floodplain_farm_food_factor : 48
    meadow_farm_food_factor : 64
    harvest_food_divisor : 10
    ranch_food_factor : 16
    ranch_food_divisor : 4
    ranch_food_percentage : 80
    import_amount_per_load : 100
    months_per_year : 12
    food_per_cart : 100
    consumption_percentage : 25
    blessed_consumption_percentage : 20
}
