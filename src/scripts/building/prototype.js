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
Building.property.curse_days_left = { }
Building.property.common_health = { }
Building.property.disease_days = { }
Building.property.can_play_animation = { get: function() { return this.__can_play_animation() } }
Building.property.is_fancy = { get: function() { return this.__is_fancy() } }
Building.property.is_output_resourece_mothballed = { get: function() { return __city_resource_is_mothballed(this.output_resource_id) } }

Building.property.stored_clay = { get: function() { return this.stored_resource(RESOURCE_CLAY) } }
Building.property.stored_straw = { get: function() { return this.stored_resource(RESOURCE_STRAW) } }
Building.property.first_material_stored = { get: function() { return __building_first_material_stored(this.id) } }

Building.property.has_road_access = { }
Building.property.has_water_access = { }
Building.property.spawned_worker_this_month = { }
Building.property.num_workers = { }
Building.property.max_workers = { }
Building.property.type = { }
Building.property.orientation = { }
Building.property.prev_part_building_id = { }
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
Building.property.is_protected_by_police = { get: function() { return __building_is_protected_by_police(this.id) } }

Building.prototype.get_figure = function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
