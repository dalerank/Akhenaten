log_info("akhenaten: empire started")

empire_city_options {
    text_group_old_names : 195
    text_group_new_names : 21
}

empire_traders {
    ship_movement_delay [2, 5]       
    land_movement_delay [1, 4]
}

empire {
    get_city : function(city_id) {
        if (!city_id) {
            return null
        }
        
        return {
            city_id: city_id        
            @empire_object { get: function() { return __empire_get_city_empire_object(this.city_id) } }
        }
    }
    
    @has_distant_battle { get: __empire_has_distant_battle }
    active_battle {
        __property_getter: function(property) { return __game_get_active_battle_property(property) }
        @egyptian_months_to_travel_back { }
        @kingdome_army_is_traveling_forth { }
        @months_until_distant_battle { }
        @city { }
    }
}