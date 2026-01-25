log_info("akhenaten: city.js started")

city {
    festival {
        __property_getter: __city_get_festival_property
        @selected_god { }        
    }

    @population { get: __city_population }
    @rating_kingdom { get: __city_rating_kingdom }
    @num_forts { get: __formation_get_num_forts }

    figures {
        __property_getter: __city_get_figures_property
        @enemies { }
        @kingdome_soldiers { }

        remove_figures: __city_remove_figures
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
        amount: function(resource_type) { return __granary_get_amount(this.id, resource_type) }    
        total_stored: function() { return __granary_get_total_stored(this.id) }
    }
}

city.get_random_house = function() {
    var building_id = __city_get_random_house_id()
    return {
        id: building_id
        add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
        add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
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
    return {
        id: building_id
        add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
        add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
    }
}

city.get_figure = function(figure_id) {
    return {
        id: figure_id
        @type { get: function() { return __figure_get_type(this.id) } }
        @destination_id { get: function() { return __figure_get_destination_building_id(this.id) } }
        @destination { get: function() { return city.get_building(__figure_get_destination_building_id(this.id)) } }
    }
}

city.get_building = function(building_id) {
    return {
        id: building_id
        add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
        add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
        has_figure: function(index) { return __building_has_figure(this.id, index) }
        get_figure: function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
        @has_road_access : { get: function() { return __building_has_road_access(this.id) } }   
        @worker_percentage : { get: function() { return __building_get_worker_percentage(this.id) } }
        @num_workers : { get: function() { return __building_get_num_workers(this.id) } }
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