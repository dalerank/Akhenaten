log_info("akhenaten: empire started")

[console_command=empire_route_debug]
function empire_route_debug_toggle(args) {
	empire.route_debug_points = console_tri_state_on_off(args, empire.route_debug_points)
	log_info("empire_route_debug_points: " + empire.route_debug_points)
}

[console_command=distant_battle_test]
function console_command_distant_battle_test(args) {
	var strength = parseInt((args && args[0]) || "50", 10)
	var cityId = parseInt((args && args[1]) || "0", 10)
	if (strength <= 0) {
		strength = 50
	}
	__distant_battle_cheat_setup_test(strength, cityId)
	log_info("distant_battle_test: city_id=ы" + cityId + " strength=" + strength)
}

Object.defineProperty(EmpireCity.prototype, "empire_object", {
    get: function() {
        return new EmpireCityObject(this.id)
    },
    enumerable: true,
    configurable: true
})

Object.defineProperty(EmpireCity.prototype, "is_sieged", {
    get: function() {
        return this.months_under_siege > 0
    },
    enumerable: true,
    configurable: true
})

empire_city_options {
    text_group_old_names : 195
    text_group_new_names : 21
}

// Empire-map city sprites: Pharaoh_General group 169 = empire_bits city block (17 frames).
// Browse as pharaoh_general/empire_bits_00057..00073. Paths preferred; pack/id/offset also OK.
empire_city_images {
    ours              : {path:"pharaoh_general/empire_bits_00057"}
    ours_expanded     : {path:"pharaoh_general/empire_bits_00057"}
    pharaoh_trading   : {path:"pharaoh_general/empire_bits_00063"}
    pharaoh           : {path:"pharaoh_general/empire_bits_00063"}
    egyptian_trading  : {path:"pharaoh_general/empire_bits_00063"}
    egyptian          : {path:"pharaoh_general/empire_bits_00063"}
    foreign_trading   : {path:"pharaoh_general/empire_bits_00066"}
    foreign           : {path:"pharaoh_general/empire_bits_00066"}
}

empire_traders {
    ship_movement_delay [2, 5]
    land_movement_delay [1, 4]
}

empire {
    @luxury_goods_traded_sum { get: __empire_luxury_goods_traded_sum }
    @has_distant_battle { get: __empire_has_distant_battle }
    @id { get: __empire_get_id }
    @is_expanded { get: __empire_is_expanded }

    set_id : __empire_set_id
    set_expanded : __empire_set_expanded
    expand : __empire_expand

    active_battle {
        __property_getter: function(property) { return __game_get_active_battle_property(property) }
        @egyptian_months_to_travel_back { }
        @egyptian_months_to_travel_forth { }
        @egyptian_months_traveled { }
        @enemy_months_traveled { }
        @kingdome_army_is_traveling_forth { }
        @months_until_battle { }
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

    object_slots : 200
    trader_slots : 100

    trade_route_num_points : __empire_trade_route_num_points
    trade_route_point : __empire_trade_route_point
}

empire.get_city_object = function(city_id) {
    return new EmpireCityObject(city_id)
}

empire.get_object = function(object_id) {
    return new EmpireObject(object_id)
}

empire.get_trader = function(index) {
    return new EmpireTrader(index)
}

empire.get_city = function(city_id) {
    return new EmpireCity(city_id)
}