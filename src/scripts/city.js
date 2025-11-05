log_info("akhenaten: city.js started")

city {
    use_building: city_use_building
    set_goal_tooltip: scenario_set_goal_tooltip
    set_victory_reason : city_set_victory_reason

    get_granary : function(building_id) {
        return {
            id: building_id        
            amount: function(resource_type) { return __granary_get_amount(building_id, resource_type) }    
            total_stored: function() { return __granary_get_total_stored(building_id) }
        }
    }

    building_is_temple : function(building_id) {
        return __city_building_is_temple(building_id)
    }

    count_active_buildings : function(building_type) {
        return __city_count_active_buildings(building_type)
    }

    set_advisor_available : function(advisor, available) {
        return __city_set_advisor_available(advisor, available)
    }
}

finance { 
    income {
        [property]
        gold_delivered { get: function() { return __city_finance_income(e_finance_value_gold_delivered) } }
    }
}