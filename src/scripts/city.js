log_info("akhenaten: city.js started")

city {
    [property]
    festival_selected_god { get: __city_festival_selected_god }
    
    use_building: city_use_building
    set_goal_tooltip: scenario_set_goal_tooltip
    set_victory_reason : city_set_victory_reason
    remove_animals : __city_remove_animals
    add_animals_point : __city_add_animals_point
    set_animals_area : __city_set_animals_area
    yards_stored : __city_yards_stored
    building_is_temple : __city_building_is_temple
    building_is_tax_collector : __city_building_is_tax_collector
    count_active_buildings : __city_count_active_buildings
    count_total_buildings : __city_count_total_buildings
    set_advisor_available : __city_set_advisor_available
    rank_title : __city_rank_title
    rank_salary : __city_rank_salary

    get_granary : function(building_id) {
        return {
            id: building_id        
            amount: function(resource_type) { return __granary_get_amount(building_id, resource_type) }    
            total_stored: function() { return __granary_get_total_stored(building_id) }
        }
    }

    get_random_house : function() {
        var building_id = __city_get_random_house_id()
        return {
            id: building_id
            add_fire_damage: function(damage) { __building_add_fire_damage(building_id, damage) }
        }
    }

    create_good_request : function(tag_id, resource, amount, months_initial) {
        __city_create_good_request(tag_id, resource, amount, months_initial)
        return {
            tag_id: tag_id
            months_initial: months_initial
            execute: function() { __city_request_execute(tag_id) }
        }
    }

    create_trade_city_under_siege : function(tag_id, months_initial) {
        __city_event_create_trade_city_under_siege(tag_id, months_initial)
        return {
            tag_id: tag_id
            months_initial: months_initial
            set_reasons: function(r1, r2, r3, r4) { __city_request_set_reasons(tag_id, r1, r2, r3, r4) }
            execute: function() { __city_request_execute(tag_id) }
        }
    }
}

finance { 
    income {
        [property]
        gold_delivered { get: function() { return __city_finance_income(e_finance_value_gold_delivered) } }
    }
}

crime {
    
}