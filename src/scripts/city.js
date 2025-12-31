log_info("akhenaten: city.js started")

city {
    festival {
        __property_getter: function(property) { return __city_get_festival_property(property) }
        @selected_god { }        
    }
    @population { get: __city_population }
    @rating_kingdom { get: __city_rating_kingdom }
    @num_forts { get: __formation_get_num_forts }

    figures {
        __property_getter: function(property) { return __city_get_figures_property(property) }
        @enemies { }
        @kingdome_soldiers { }
    }
    
    military {
        __property_getter: function(property) { return __city_get_military_property(property) }
        @total_soldiers { }
        @total_batalions { }
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
    
    get_battalion : function(index) { 
        return {
            id: index
            __property_getter: function(property) { return __city_get_battalion_property(this.id, property) }
            @batalion_id { }
            @figure_type { }
            @num_figures { }
            @morale      { }
            @experience  { }
            @is_at_fort  { }
            @in_distant_battle {}

            return_home: function() { __formation_batalion_return_to_fort(this.id) }
        }
    }

    get_granary : function(building_id) {
        return {
            id: building_id        
            amount: function(resource_type) { return __granary_get_amount(this.id, resource_type) }    
            total_stored: function() { return __granary_get_total_stored(this.id) }
        }
    }

    get_random_house : function() {
        var building_id = __city_get_random_house_id()
        return {
            id: building_id
            add_fire_damage: function(damage) { __building_add_fire_damage(this.id, damage) }
            add_collapse_damage: function(damage) { __building_add_collapse_damage(this.id, damage) }
        }
    }

    create_good_request : function(obj) {
        __city_create_good_request(obj)
        return {
            tag_id: obj.tag_id
            execute: function() { __city_request_execute(this.tag_id) }
        }
    }

    create_trade_city_under_siege : function(tag_id, months_initial) {
        __city_event_create_trade_city_under_siege(tag_id, months_initial)
        return {
            tag_id: tag_id
            set_reasons: function(r1, r2, r3, r4) { __city_request_set_reasons(this.tag_id, r1, r2, r3, r4) }
            execute: function() { __city_request_execute(this.tag_id) }
        }
    }

    create_foreign_army_attack_warning : function(obj) {
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

    create_distant_battle : function(obj) {
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
}

finance { 
    income {
        @gold_delivered { get: function() { return __city_finance_income(e_finance_value_gold_delivered) } }
    }
}

crime {
    
}