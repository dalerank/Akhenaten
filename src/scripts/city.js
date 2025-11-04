log_info("akhenaten: city.js started")

city {
    use_building: city_use_building
    set_goal_tooltip: scenario_set_goal_tooltip
}

city.get_granary = function(building_id) {
    return {
        id: building_id
        
        amount: function(resource_type) { return granary_get_amount(building_id, resource_type) }    
        total_stored: function() { return granary_get_total_stored(building_id) }
    }
}