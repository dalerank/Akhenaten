log_info("akhenaten: city.js started")

city {
    festival {
        __property_getter: __city_get_festival_property
        @selected_god { }
    }

    @population { get: __city_population }
    @rating_kingdom { get: __city_rating_kingdom }
    @num_forts { get: __formation_get_num_forts }
    @current_overlay { get: __city_get_current_overlay, set: __city_set_current_overlay }

    figures {
        __property_getter: __city_get_figures_property
        @enemies { }
        @kingdome_soldiers { }

        remove_figures: __city_remove_figures
    }

    labor {
        __property_getter: __city_get_labor_property
        @unemployment_percentage { }
    }

    rating {
        @culture { get: __city_rating_culture }
        @prosperity { get: __city_rating_prosperity }
        @monument { get: __city_rating_monument }
        @kingdom { get: __city_rating_kingdom }
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

    object_info {
        @building_id { get: __city_get_object_info_building_id }
        @bid { get: __city_get_object_info_building_id }
        @group { get: __city_get_object_info_group }
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
    set_advisor_available : __city_set_advisor_available
    rank_title : __city_rank_title
    rank_salary : __city_rank_salary
    start_foreign_army_invasion : __city_start_foreign_army_invasion
    camera_go_to : __city_camera_go_to
    allowed_foods : __city_allowed_foods
}

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
        @tile { get: function() { return __building_tile(this.id) } }
        total_stored: function() { return __granary_get_total_stored(this.id) }
        amount: function(resource) { return __granary_get_amount(this.id, resource) }
        is_accepting: function(resource) { return __granary_is_accepting(this.id, resource) }
    }
}

city.get_random_house = function() {
    var building_id = __city_get_random_house_id()
    return city.get_house(building_id)
}

city.get_house = function(building_id) {
    return {
        __property_getter: function(property) { return __house_get_property(this.id, property) }

        id: building_id
        @tile { get: function() { return __building_tile(this.id) } }
        @meta_text_id { get: function() { return __building_meta_text_id(this.id) } }
        @population { }
        @tax_coverage { }
        @tax_income_or_storage { }
        @population_room { get: function() { return __house_population_room(this.id) } }
        food: function(index) { return __house_get_food(this.id, index) }
        inv: function(index) { return __house_get_inventory(this.id, index) }
        add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
        add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
    }
}

city.get_bazaar = function(building_id) {
    return {
        id: building_id
        @meta_text_id { get: function() { return __building_meta_text_id(this.id) } }
        @tile { get: function() { return __building_tile(this.id) } }
        resource_amount: function(resource_type) { return __bazaar_resource_amount(this.id, resource_type) }
        idx_amount: function(index) { return __bazaar_idx_amount(this.id, index) }
        idx_accepted: function(index) { return __bazaar_idx_accepted(this.id, index) }
        res_accepted: function(resource_type) { return __bazaar_res_accepted(this.id, resource_type) }
        get_figure: function(slot) { return city.get_figure(__building_get_figure_id(this.id, slot)) }
    }
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

city.get_building = function(building_id) {
    return {
        id: building_id
        __property_getter: function(property) { return __building_get_property(this.id, property) }

        add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
        add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
        has_figure: function(index) { return __building_has_figure(this.id, index) }
        stored_resource: function(resource) { return __building_stored_resource(this.id, resource) }
        get_figure: function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
        mothball_toggle: function() { __building_mothball_toggle(this.id) }
        @tile { get: function() { return __building_tile(this.id) } }
        @type { }
        @num_workers { }
        @max_workers { }
        @has_road_access { }
        @overlay { get: function() { return __building_get_overlay(this.id) } }
        @state { get: function() { return __building_get_state(this.id) } }
        @worker_percentage { get: function() { return calc_percentage(this.num_workers, this.max_workers) } }
        @meta_text_id { get: function() { return __building_meta_text_id(this.id) } }
    }
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