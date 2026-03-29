log_info("akhenaten: empire started")

[console_command=empire_route_debug]
function empire_route_debug_toggle(args) {
	empire.route_debug_points = console_tri_state_on_off(args, empire.route_debug_points)
	log_info("empire_route_debug_points: " + empire.route_debug_points)
}

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

        @path_length { get: function() { return __distant_battle_army_path_length() } }
        path_point : __distant_battle_army_path_point
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

    route_debug_points : false
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
        @type { get: function() { return __empire_city_type(this.city_id) } }
        @is_open { get: function() { return __empire_city_is_open(this.city_id) } }

        city_buys_resource : function(resource) { return __empire_city_buys_resource(this.city_id, resource) }
        city_sells_resource : function(resource) { return __empire_city_sells_resource(this.city_id, resource) }
        trade_route_limit : function(resource) { return __empire_trade_route_limit(this.city_id, resource) }
        trade_route_traded : function(resource) { return __empire_trade_route_traded(this.city_id, resource) }
        stack_proper_quantity : function(resource, quantity) { return __city_resource_stack_proper_quantity(resource, quantity) }
    }
}