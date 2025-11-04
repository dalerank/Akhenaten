log_info("akhenaten: city.js started")

city {
    use_building: city_use_building
    set_goal_tooltip: scenario_set_goal_tooltip
    set_victory_reason : city_set_victory_reason
}

city.get_granary = function(building_id) {
    return {
        id: building_id        
        amount: function(resource_type) { return granary_get_amount(building_id, resource_type) }    
        total_stored: function() { return granary_get_total_stored(building_id) }
    }
}

finance {
    income {
        [property]
        gold_delivered { get: function() { return __city_finance_income(e_finance_value_gold_delivered) } }
    }
}