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
    @has_distant_battle { get: __empire_has_distant_battle }
    active_battle {
        __property_getter: function(property) { return __game_get_active_battle_property(property) }
        @egyptian_months_to_travel_back { }
        @kingdome_army_is_traveling_forth { }
        @months_until_distant_battle { }
        @city { }
    }

    ourcity {
        __property_getter: function(property) { return __empire_get_ourcity_property(property) }
        @id {}
        @pos {}
        @type {}
    }

    dispatched_army {
        __property_getter: function(property) { return __empire_get_dispatched_army_property(property) }
        @state {}
        @pos {}
    }
}

empire.get_city_object = function(city_id) {
    return {
        city_id: city_id        
        __property_getter: function(property) { return __empire_get_city_object_property(this.city_id, property) }        
        @id {}
        @pos {}
        @type {}
    }
}

empire.get_city = function(city_id) {
    return {
        city_id: city_id        
        @empire_object { get: function() { return empire.get_city_object(this.city_id) } }
    }
}