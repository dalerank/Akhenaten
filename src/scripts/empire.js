log_info("akhenaten: city econmoic started")

empire_city_options {
    text_group_old_names : 195
    text_group_new_names : 21
}

empire_traders {
    ship_movement_delay : [2, 5]       
    land_movement_delay : [1, 4]
}

empire {
    has_distant_battle : __empire_has_distant_battle
    distant_battle_city : __empire_distant_battle_city

    get_city : function(city_id) {
        if (!city_id) {
            return null
        }

        return {
            id: city_id        
            empire_object: __empire_get_city_empire_object(city_id)
        }
    }
}