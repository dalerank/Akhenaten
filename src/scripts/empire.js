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

// OG empire_trade_rules + trade_recommends.txt: how much the city keeps before it exports a surplus,
// and the stock IMPORT_AS_NEEDED imports up to. Recomputed once a day.
empire_trade_rules {
    // Traders a city may have in ours at once (OG 3); a route with small limits sends fewer.
    max_traders_per_city : 3
    trader_limit_small : 1500
    trader_limit_medium : 2500

    keep_workshop_amount : 200
    keep_monument_amount : 500
    keep_other_amount : 1000
    stock_cap_small : 10000
    stock_cap_default : 15000
    stock_cap_large : 30000

    recommends [
        { population_below: 1000, food: 600,  pottery: 400,  beer: 400,  linen: 400,  papyrus: 300,  luxury_goods: 200 }
        { population_below: 2500, food: 1200, pottery: 800,  beer: 800,  linen: 800,  papyrus: 600,  luxury_goods: 400 }
        { population_below: 5000, food: 2400, pottery: 1600, beer: 1600, linen: 1600, papyrus: 1200, luxury_goods: 800 }
        { population_below: 0,    food: 4000, pottery: 3000, beer: 3000, linen: 3000, papyrus: 2000, luxury_goods: 1500 }
    ]

    monument_unplaced_needs [
        { monument: 1,  building: BUILDING_SMALL_BENT_PYRAMID,              resource: RESOURCE_STONE,     amount: 4800,   limestone: 19200 }
        { monument: 2,  building: BUILDING_MEDIUM_BENT_PYRAMID,             resource: RESOURCE_STONE,     amount: 21600,  limestone: 43200 }
        { monument: 3,  building: BUILDING_SMALL_MUDBRICK_PYRAMID,          resource: RESOURCE_BRICKS,    amount: 4800,   limestone: 19200 }
        { monument: 4,  building: BUILDING_MEDIUM_MUDBRICK_PYRAMID,         resource: RESOURCE_BRICKS,    amount: 21600,  limestone: 43200 }
        { monument: 5,  building: BUILDING_LARGE_MUDBRICK_PYRAMID,          resource: RESOURCE_BRICKS,    amount: 67200,  limestone: 76800 }
        { monument: 6,  building: BUILDING_MUDBRICK_PYRAMID_COMPLEX,        resource: RESOURCE_BRICKS,    amount: 144000, limestone: 120000 }
        { monument: 7,  building: BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX,  resource: RESOURCE_BRICKS,    amount: 264000, limestone: 160000 }
        { monument: 8,  building: BUILDING_SMALL_STEPPED_PYRAMID,           resource: RESOURCE_STONE,     amount: 4800,   limestone: 0 }
        { monument: 9,  building: BUILDING_MEDIUM_STEPPED_PYRAMID,          resource: RESOURCE_STONE,     amount: 21600,  limestone: 0 }
        { monument: 10, building: BUILDING_LARGE_STEPPED_PYRAMID,           resource: RESOURCE_STONE,     amount: 67200,  limestone: 0 }
        { monument: 11, building: BUILDING_STEPPED_PYRAMID_COMPLEX,         resource: RESOURCE_STONE,     amount: 144000, limestone: 0 }
        { monument: 12, building: BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX,   resource: RESOURCE_STONE,     amount: 264000, limestone: 0 }
        { monument: 13, building: BUILDING_SMALL_PYRAMID,                   resource: RESOURCE_STONE,     amount: 4800,   limestone: 19200 }
        { monument: 14, building: BUILDING_MEDIUM_PYRAMID,                  resource: RESOURCE_STONE,     amount: 21600,  limestone: 43200 }
        { monument: 15, building: BUILDING_LARGE_PYRAMID,                   resource: RESOURCE_STONE,     amount: 67200,  limestone: 76800 }
        { monument: 16, building: BUILDING_PYRAMID_COMPLEX,                 resource: RESOURCE_STONE,     amount: 144000, limestone: 120000 }
        { monument: 17, building: BUILDING_GRAND_PYRAMID_COMPLEX,           resource: RESOURCE_STONE,     amount: 264000, limestone: 160000 }
        { monument: 18, building: BUILDING_SMALL_MASTABA,                   resource: RESOURCE_BRICKS,    amount: 10800,  limestone: 0 }
        { monument: 19, building: BUILDING_MEDIUM_MASTABA,                  resource: RESOURCE_BRICKS,    amount: 24000,  limestone: 0 }
        { monument: 20, building: BUILDING_LARGE_MASTABA,                   resource: RESOURCE_BRICKS,    amount: 42000,  limestone: 0 }
        { monument: 22, building: BUILDING_SMALL_OBELISK,                   resource: RESOURCE_GRANITE,   amount: 10000,  limestone: 0 }
        { monument: 23, building: BUILDING_LARGE_OBELISK,                   resource: RESOURCE_GRANITE,   amount: 20000,  limestone: 0 }
        { monument: 24, building: BUILDING_SUN_TEMPLE,                      resource: RESOURCE_SANDSTONE, amount: 38000,  limestone: 0 }
        { monument: 25, building: BUILDING_MAUSOLEUM,                       resource: RESOURCE_SANDSTONE, amount: 49600,  limestone: 0 }
        { monument: 26, building: BUILDING_MAUSOLEUM,                       resource: RESOURCE_SANDSTONE, amount: 49600,  limestone: 0 }
        { monument: 27, building: BUILDING_MAUSOLEUM,                       resource: RESOURCE_SANDSTONE, amount: 49600,  limestone: 0 }
    ]
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