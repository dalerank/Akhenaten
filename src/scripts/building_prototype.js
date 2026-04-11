log_info("akhenaten: building_prototype.js loaded")

Building.property.params = { get: function() { return city.get_building_params(this.id) } }

Building.property.des_influence_value = { get: function() { return this.__des_influence_value() } }
Building.property.des_influence_step_size = { get: function() { return this.__des_influence_step_size() } }
Building.property.des_influence_range = { get: function() { return this.__des_influence_range() } }
Building.property.tile = { get: function() { return this.__tile() } }
Building.property.overlay = { get: function() { return this.__overlay() } }
Building.property.state = { get: function() { return this.__state() } }
Building.property.valid = { get: function() { return this.__valid() } }
Building.property.worker_percentage = { get: function() { return this.__worker_percentage() } }
Building.property.meta_text_id = { get: function() { return this.__meta_text_id() } }
Building.property.can_play_animation = { get: function() { return this.__can_play_animation() } }

Building.property.structure_damage = { }
Building.property.collapse_risk = { }
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
Building.property.show_on_problem_overlay = { }
Building.property.deben_storage = { }

Building.prototype.get_figure = function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
