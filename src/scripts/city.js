log_info("akhenaten: city.js started")

city {
    @population { get: __city_population }
    @health_rating { get: __city_health_rating }
    @workers_diff { get: __city_workers_diff }
    @player_rank { get: __city_player_rank }
    @mission_has_won { get: __city_mission_has_won }
    @rating_kingdom { get: __city_rating_kingdom }
    @num_forts { get: __formation_get_num_forts }
    @current_overlay { get: __city_get_current_overlay, set: __city_set_current_overlay }

    figures {
        __property_getter: __city_get_figures_property
        @enemies { }
        @kingdome_soldiers { }
        @rioters { }

        remove_figures: __city_remove_figures
    }

    labor {
        __property_getter: __city_get_labor_property
        @unemployment_percentage { }
        @workers_available { }
        @workers_needed { }
        @workers_unemployed { }

        get_category: function(index) {
            return {
                __property_getter: function(property) { return __city_get_labor_category_property(index, property) }
                @workers_needed { }
                @workers_allocated { }
                @priority { }
            }
        }
    }

    entertainment {
        __property_getter: __city_get_entertainment_property
        @booth_shows { }
        @bandstand_shows { }
        @pavilion_shows { }
        @senet_house_plays { }
        @venue_needing_shows { }
    }

    population_stats {
        __property_getter: __city_get_population_property
        @current { }
        @people_in_shanties { }
        @people_in_manors { }
        monthly_count: __city_population_monthly_count
        at_month: __city_population_at_month
        at_age: __city_population_at_age
        at_level: __city_population_at_level
        average_age: __city_population_average_age
        yearly_births: __city_population_yearly_births
        yearly_deaths: __city_population_yearly_deaths
    }

    avg_coverage {
        __property_getter: __city_get_avg_coverage_property
        @average_entertainment {}
        @average_religion {}
        @average_education {}
        @average_health {}
    }

    winning {
        @culture { get: __city_winning_culture }
        @prosperity { get: __city_winning_prosperity }
        @monument { get: __city_winning_monuments }
        @kingdom { get: __city_winning_kingdom }
        @population { get: __city_winning_population }
    }

    coverage {
        __property_getter: __city_get_coverage_property
        @booth {}
        @bandstand {}
        @pavilion {}
        @senet_house {}
        @physician {}
        @dentist {}
        @apothecary {}
        @mortuary {}
        @school {}
        @academy {}
        @library {}
        @oracle {}
    }

    houses {
        __property_getter: __city_get_house_demands_property
        @health {}
        @religion {}
        @education {}
        @entertainment {}

        requiring {
            __property_getter: __city_get_house_demands_requiring_property
            @school {}
            @library {}
            @dentist {}
            @physician {}
            @water_supply {}
            @magistrate {}
            @religion {}
        }

        missing {
            __property_getter: __city_get_house_demands_missing_property
            @entertainment {}
            @more_entertainment {}
        }
    }

    taxes {
        __property_getter: __city_get_taxes_property
        @percentage_taxed_people { }
        @estimated_uncollected { }
        @estimated_income { }
    }

    military {
        __property_getter: __city_get_military_property
        @total_soldiers { }
        @total_batalions { }
    }

    sentiment {
        __property_getter: __city_get_sentiment_property
        @value { }
    }

    migration {
        __property_getter: __city_get_migration_property
        @newcomers { }
        @percentage { }
        @no_immigration_cause { }
    }

    object_info {
        __property_getter: __city_get_object_info_property
        @building_id { }
        @bid { }
        @group { }
        @offset { }
    }

    warnings {
        show : __city_show_warning
        show_if_not : function (condition, id) { if (!condition) { __city_show_warning(id) } }
    }

    resources {
        @available { get: __city_resources_available }
        @available_market { get: __city_resources_available_market_goods }

        can_produce : __city_resource_can_produce
        can_import : __city_resource_can_import
        trade_status : __city_resource_trade_status
        count : __city_resources_count
        type : __city_resource_at

        get_name : __city_resource_name
        id_by_name : __city_resource_id_by_name
        set_produce : __city_resource_set_produce
        cycle_trade_import : __city_resource_cycle_trade_import
        cycle_trade_export : __city_resource_cycle_trade_export
        change_trading_amount : __city_resource_change_trading_amount
        toggle_stockpiled : __city_resource_toggle_stockpiled
    }

    gods {
        get_name : __city_god_name
        is_known : __city_god_is_known
        set_known : __city_god_set_known

        at: function(index) {
            return {
                __property_getter: function(property) { return __city_get_god_property(index, property) }
                @is_known {}
                @mood {}
                @wrath_bolts {}
                @happy_ankhs {}
                @months_since_festival {}
                @status {}
                @mood {}
                @happy_anks {}
            }
        }

        least_happy: __city_religion_least_happy_god
    }

    use_building: __city_use_building
    set_goal_tooltip: __scenario_set_goal_tooltip
    set_victory_reason : city_set_victory_reason
    remove_animals : __city_remove_animals
    add_animals_point : __city_add_animals_point
    set_animals_area : __city_set_animals_area
    yards_stored : __city_yards_stored
    building_is_temple : __city_building_is_temple
    building_is_tax_collector : __city_building_is_tax_collector
    count_active_buildings : __city_count_active_buildings
    count_total_buildings : __city_count_total_buildings
    total_housing_buildings : __city_total_housing_buildings
    housing_type_count_at : __city_housing_type_count_at
    houses_demanding_goods_at : __city_houses_demanding_goods_at
    open_housing_capacity : __city_open_housing_capacity
    total_housing_capacity : __city_total_housing_capacity
    count_active_industry : __city_count_industry_active
    count_total_industry : __city_count_industry_total
    set_advisor_available : __city_set_advisor_available
    rank_title : function(rank) { return __loc(52, rank + 4) }
    rank_salary : __city_rank_salary

    kingdome {
        __property_getter: __city_get_kingdome_property
        @salary_rank { }
        @player_rank { }
        @kingdom_change { }
        @kingdom_salary_penalty { }
        @kingdom_milestone_penalty { }
        @kingdom_ignored_request_penalty { }
        @kingdom_explanation { }
    }

    apply_salary_rank : __city_kingdome_apply_salary_rank
    start_foreign_army_invasion : __city_start_foreign_army_invasion
    camera_go_to : __city_camera_go_to
    allowed_foods : __city_allowed_foods
}

function city_resource_view(resource_id) {
    return {
        type: resource_id
        name: __city_resource_name(resource_id)
        @can_produce { get: function() { return __city_resource_can_produce(resource_id) } }
        @can_import { get: function() { return __city_resource_can_import(resource_id, true) } }
        @can_export { get: function() { return __city_resource_can_export(resource_id, true) } }
        @could_import { get: function() { return __city_resource_can_import(resource_id, false) } }
        @could_export { get: function() { return __city_resource_can_export(resource_id, false) } }
        @trading_amount { get: function() { return __city_resource_trading_amount(resource_id) } }
        @trade_status { get: function() { return __city_resource_trade_status(resource_id) } }
        @yards_stored { get: function() { return __city_yards_stored(resource_id) } }
        @city_stored { get: function() { return __city_resource_stored(resource_id) } }
        @count_active_industry { get: function() { return __city_count_industry_active(resource_id) } }
        @count_total_industry { get: function() { return __city_count_industry_total(resource_id) } }
        @mothballed { get: function() { return __city_resource_is_mothballed(resource_id) } }
        @is_stockpiled { get: function() { return __city_resource_is_stockpiled(resource_id) } }
        @price_buy { get: function() { return __trade_price_buy(resource_id) } }
        @price_sell { get: function() { return __trade_price_sell(resource_id) } }
        stack_proper_quantity: function(value) { return __city_resource_stack_proper_quantity(resource_id, value) }
    }
}

city.resources.grain = city_resource_view(RESOURCE_GRAIN)
city.resources.meat = city_resource_view(RESOURCE_MEAT)
city.resources.lettuce = city_resource_view(RESOURCE_LETTUCE)
city.resources.chickpeas = city_resource_view(RESOURCE_CHICKPEAS)
city.resources.pomegranates = city_resource_view(RESOURCE_POMEGRANATES)
city.resources.figs = city_resource_view(RESOURCE_FIGS)
city.resources.fish = city_resource_view(RESOURCE_FISH)
city.resources.gamemeat = city_resource_view(RESOURCE_GAMEMEAT)
city.resources.straw = city_resource_view(RESOURCE_STRAW)
city.resources.weapons = city_resource_view(RESOURCE_WEAPONS)
city.resources.clay = city_resource_view(RESOURCE_CLAY)
city.resources.bricks = city_resource_view(RESOURCE_BRICKS)
city.resources.pottery = city_resource_view(RESOURCE_POTTERY)
city.resources.barley = city_resource_view(RESOURCE_BARLEY)
city.resources.beer = city_resource_view(RESOURCE_BEER)
city.resources.flax = city_resource_view(RESOURCE_FLAX)
city.resources.linen = city_resource_view(RESOURCE_LINEN)
city.resources.gems = city_resource_view(RESOURCE_GEMS)
city.resources.luxury_goods = city_resource_view(RESOURCE_LUXURY_GOODS)
city.resources.timber = city_resource_view(RESOURCE_TIMBER)
city.resources.gold = city_resource_view(RESOURCE_GOLD)
city.resources.reeds = city_resource_view(RESOURCE_REEDS)
city.resources.papyrus = city_resource_view(RESOURCE_PAPYRUS)
city.resources.stone = city_resource_view(RESOURCE_STONE)
city.resources.limestone = city_resource_view(RESOURCE_LIMESTONE)
city.resources.granite = city_resource_view(RESOURCE_GRANITE)
city.resources.chariots = city_resource_view(RESOURCE_CHARIOTS)
city.resources.copper = city_resource_view(RESOURCE_COPPER)
city.resources.sandstone = city_resource_view(RESOURCE_SANDSTONE)
city.resources.oil = city_resource_view(RESOURCE_OIL)
city.resources.henna = city_resource_view(RESOURCE_HENNA)
city.resources.paint = city_resource_view(RESOURCE_PAINT)
city.resources.lamps = city_resource_view(RESOURCE_LAMPS)
city.resources.marble = city_resource_view(RESOURCE_MARBLE)

city.get_battalion_by_index = function(index) {
    return {
        index: index
        __property_getter: function(property) { return __city_get_battalion_property(this.index, property) }
        @batalion_id { }
        @figure_type { }
        @num_figures { }
        @morale      { }
        @experience  { }
        @is_at_fort  { }
        @in_distant_battle {}
        @empire_service { }

        return_home: function() { __formation_batalion_idx_return_to_fort(this.index) }
        set_empire_service: function(v) { __formation_batalion_idx_set_empire_service(this.index, v) }
    }
}

city.get_granary = function(building_id) {
    return {
        id: building_id
        @tile { get: __building_tile }
        total_stored: function() { return __granary_get_total_stored(this.id) }
        amount: function(resource) { return __granary_get_amount(this.id, resource) }
        is_accepting: function(resource) { return __granary_is_accepting(this.id, resource) }
    }
}

city.get_random_house = function() {
    var building_id = __city_get_random_house_id()
    return city.get_house(building_id)
}

city.get_house_model = function(level) {
    return {
        __property_getter: function(property) { return __house_model_property(this.level, property) }

        level: level
        @devolve_desirability { }
        @evolve_desirability { }
        @entertainment { }
        @water { }
        @food_types { }
        @pottery { }
        @linen { }
        @jewelry { }
        @beer { }
        @religion { }
        @education { }
        @health { }
        @dentist { }
        @physician { }
        @fancy_bazaar { }
    }
}

city.get_grid_area = function(tile, size, radius) {
    return __map_grid_get_area(tile, size, radius)
}

city.get_house = function(building_id) {
    return new House(building_id)
}

city.get_bazaar = function(building_id) {
    return new Bazaar(building_id)
}

city.create_good_request = function(obj) {
    __city_create_good_request(obj)
    return {
        tag_id: obj.tag_id
        execute: function() { __city_request_execute(this.tag_id) }
    }
}

city.create_trade_city_under_siege = function(tag_id, months_initial) {
    __city_event_create_trade_city_under_siege(tag_id, months_initial)
    return {
        tag_id: tag_id
        set_reasons: function(r1, r2, r3, r4) { __city_request_set_reasons(this.tag_id, r1, r2, r3, r4) }
        execute: function() { __city_request_execute(this.tag_id) }
    }
}

city.create_foreign_army_attack_warning = function(obj) {
    __city_event_create_foreign_army_attack_warning(obj)
    return {
        tag_id: obj.tag_id
        set_location_fields: function(l1, l2, l3, l4) { __city_request_set_location_fields(this.tag_id, l1, l2, l3, l4) }
        set_reasons: function(r1, r2, r3, r4) { __city_request_set_reasons(this.tag_id, r1, r2, r3, r4) }
        set_sender_faction: function(sender_faction) { __city_request_set_sender_faction(this.tag_id, sender_faction) }
        set_image: function(image) { __city_request_set_image(this.tag_id, image) }
        execute: function() { __city_request_execute(this.tag_id) }
    }
}

city.get_random_building = function() {
    var building_id = __city_get_random_building_id()
    return city.get_building(building_id)
}

city.get_figure = function(figure_id) {
    return {
        id: figure_id
        @type { get: function() { return __figure_get_type(this.id) } }
        @valid { get: function() { return __figure_is_valid(this.id) } }
        @action_state { get: function() { return __figure_get_action_state(this.id) } }
        @destination_id { get: function() { return __figure_get_destination_building_id(this.id) } }
        @destination { get: function() { return city.get_building(__figure_get_destination_building_id(this.id)) } }
    }
}

city.get_random_building_by_type = function(type) {
    var building_id = __city_get_random_building_id_by_type(type)
    return city.get_building(building_id)
}

city.get_building_at = function(x, y) {
    return city.get_building(__building_at(x, y))
}

city.get_farm = function(building_id) {
    return {
        id: building_id
        __property_getter: function(property) { return __farm_get_property(this.id, property) }
        @flood_imminent { }
        @progress { }
        @is_floodplain { }

        set_worker: function(action, coords) { __farm_set_worker(this.id, action, coords) }
    }
}

city.get_building_params = function(building_id) {
    return {
        id: building_id
        __property_getter: function(property) { return __building_get_params_property(this.id, property) }

        @min_houses_coverage { }
    }
}

city.get_building = function(building_id) {
    return new Building(building_id)
}

city.create_distant_battle = function(obj) {
    __city_event_create_distant_battle(obj)
    return {
        tag_id: obj.tag_id
        set_location_fields: function(l1, l2, l3, l4) { __city_request_set_location_fields(this.tag_id, l1, l2, l3, l4) }
        set_reasons: function(r1, r2, r3, r4) { __city_request_set_reasons(this.tag_id, r1, r2, r3, r4) }
        set_image: function(image) { __city_request_set_image(this.tag_id, image) }
        set_param: function(param, value) { __city_request_set_param(this.tag_id, param, value) }
        execute: function() { __city_request_execute(this.tag_id) }
    }
}

crime {

}