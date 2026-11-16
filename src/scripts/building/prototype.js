log_info("akhenaten: building_prototype.js loaded")

Building.property.params = { get: function() { return city.get_building_params(this.id) } }

Building.property.des_influence_value = { get: function() { return this.__des_influence_value() } }
Building.property.des_influence_step_size = { get: function() { return this.__des_influence_step_size() } }
Building.property.des_influence_range = { get: function() { return this.__des_influence_range() } }
Building.property.crime_influence_value = { get: function() { return this.__crime_influence_value() } }
Building.property.tile = { get: function() { return this.__tile() } }
Building.property.overlay = { get: function() { return this.__overlay() } }
Building.property.state = { get: function() { return this.__state() } }
Building.property.valid = { get: function() { return this.__valid() } }
Building.property.worker_percentage = { get: function() { return this.__worker_percentage() } }
Building.property.output_resource_id = { get: function() { return this.__output_resource_id() } }
Building.property.meta_text_id = { get: function() { return this.__meta_text_id() } }
Building.property.can_play_animation = { get: function() { return this.play_animation } }
Building.property.is_fancy = { get: function() { return this.__is_fancy() } }
Building.property.is_output_resourece_mothballed = { get: function() { return __city_resource_is_mothballed(this.output_resource_id) } }

Building.property.stored_clay = { get: function() { return this.stored_resource(RESOURCE_CLAY) } }
Building.property.stored_straw = { get: function() { return this.stored_resource(RESOURCE_STRAW) } }
Building.property.first_material_stored = { get: function() { return __building_first_material_stored(this.id) } }
Building.property.second_material = { }

Building.property.curse_days_left = { }
Building.property.common_health = { }
Building.property.disease_days = { }
Building.property.name = { }
Building.property.has_road_access = { }
Building.property.road_network_id = { }
Building.property.distance_from_entry = { }
Building.property.has_water_access = { }
Building.property.has_well_access = { }
Building.property.spawned_worker_this_month = { }
Building.property.play_animation = { }
Building.property.destroy_reason = { }
Building.property.num_workers = { }
Building.property.max_workers = { }
Building.property.type = { }
Building.property.orientation = { }
Building.property.size = { }
Building.property.prev_part_building_id = { }
Building.property.is_main = { get: function() { return !this.prev_part_building_id } }
Building.property.produce_uptick = { }
Building.property.progress_before = { }
Building.property.progress = { }
Building.property.progress_max = { }
Building.property.next_part_building_id = { }
Building.property.structure_damage = { }
Building.property.collapse_risk = { }
Building.property.malaria_risk = { }
Building.property.fire_risk = { }
Building.property.fire_duration = { }
Building.property.health_proof = { }
Building.property.fire_proof = { }
Building.property.damage_proof = { }
Building.property.formation_id = { }
Building.property.has_plague = { }
Building.property.desirability = { }
Building.property.is_adjacent_to_water = { }
Building.property.storage_id = { }
Building.property.houses_covered = { }
Building.property.show_on_problem_overlay = { }
Building.property.deben_storage = { }
Building.property.tax_income_or_storage = { }
Building.property.figure_spawn_delay = { }
Building.property.residents_served_this_month = { }
Building.property.buildings_served_this_month = { }
Building.property.buildings_served_this_year = { }
Building.property.total_buildings_served = { }
Building.property.months_active = { }
Building.property.is_protected_by_police = { get: function() { return __building_is_protected_by_police(this.id) } }

Building.prototype.get_figure = function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
Building.prototype.draw_usable_paths = function() { __building_draw_usable_paths(this.id) }
Building.prototype.water_access_tile = function(index) { return __building_water_access_tile(this.id, index) }
Building.prototype.water_output_tile = function(index) { return __building_water_output_tile(this.id, index) }
Building.prototype.spawn_delay_by_workers = function(delays, pct) {
    if (pct === undefined) {
        pct = this.worker_percentage
    }
    if (pct >= 100) return delays[0]
    if (pct >= 75) return delays[1]
    if (pct >= 50) return delays[2]
    if (pct >= 25) return delays[3]
    return delays[4]
}
// OG spawn_service_walker: one living walker, day counter (uint8 wrap) by worker percentage.
Building.prototype.spawn_service_walker = function(params, figure_type, action) {
    this.check_labor_problem()
    if (this.has_figure(BUILDING_SLOT_SERVICE) || !this.has_road_access) {
        return
    }

    this.common_spawn_labor_seeker(params.min_houses_coverage)

    // OG spawn_water_supply halves the share of workers on low desirability; a share of 0 sends nobody.
    var pct = this.worker_percentage
    if (params.workers_halved) {
        pct = (pct / 2) | 0
    }
    if (pct <= 0) {
        return
    }

    // Without spawn_delays the building uses OG delays_fast, the C++ figure_spawn_timer table.
    var delay = params.spawn_delays ? this.spawn_delay_by_workers(params.spawn_delays, pct) : this.figure_spawn_timer()
    this.figure_spawn_delay = (this.figure_spawn_delay + 1) & 0xff
    if (this.figure_spawn_delay <= delay) {
        return
    }

    this.figure_spawn_delay = 0
    this.create_roaming_figure(figure_type, action, BUILDING_SLOT_SERVICE)
}
Building.prototype.highlight_waypoints = function() { __building_highlight_waypoints(this.id) }
