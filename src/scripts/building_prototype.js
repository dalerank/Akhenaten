log_info("akhenaten: building_prototype.js loaded")

function def_building_get(name, get) {
    Object.defineProperty(Building.prototype, name, {
        get: get
        enumerable: true
        configurable: true
    })
}

function def_building_native(name, fn) {
    def_building_get(name, function() { return fn(this.id) })
}

def_building_get("params", function() { return city.get_building_params(this.id) })

def_building_native("des_influence_value", __building_des_influence_value)
def_building_native("des_influence_step_size", __building_des_influence_step_size)
def_building_native("des_influence_range", __building_des_influence_range)
def_building_native("tile", __building_tile)
def_building_native("overlay", __building_get_overlay)
def_building_native("state", __building_get_state)
def_building_native("valid", __building_is_valid)
def_building_native("worker_percentage", __building_get_worker_percentage)
def_building_native("meta_text_id", __building_meta_text_id)

Building.prototype.des_influence_value = { get: function() { return __building_des_influence_value(this.id) } }
Building.prototype.des_influence_step_size = { get: function() { return __building_des_influence_step_size(this.id) } }
Building.prototype.des_influence_range = { get: function() { return __building_des_influence_range(this.id) } }
Building.prototype.tile = { get: function() { return __building_tile(this.id) } }
Building.prototype.overlay = { get: function() { return __building_get_overlay(this.id) } }
Building.prototype.state = { get: function() { return __building_get_state(this.id) } }
Building.prototype.valid = { get: function() { return __building_is_valid(this.id) } }
Building.prototype.worker_percentage = { get: function() { return __building_get_worker_percentage(this.id) } }
Building.prototype.meta_text_id = { get: function() { return __building_meta_text_id(this.id) } }

Building.prototype.get_figure = function(index) { return city.get_figure(__building_get_figure_id(this.id, index)) }
Building.prototype.add_fire_damage = function(damage) { __building_add_fire_damage(this.id, damage) }
Building.prototype.add_collapse_damage = function(damage) { __building_add_collapse_damage(this.id, damage) }
Building.prototype.add_structure_damage = function(damage) { __building_add_structure_damage(this.id, damage) }
Building.prototype.has_figure = function(index) { return __building_has_figure(this.id, index) }
Building.prototype.stored_resource = function(resource) { return __building_stored_resource(this.id, resource) }
Building.prototype.mothball_toggle = function() { return __building_mothball_toggle(this.id) }
Building.prototype.can_play_animation = function() { return __building_can_play_animation(this.id) }
Building.prototype.set_animation = function(animkey) { __building_set_animation(this.id, animkey) }
Building.prototype.common_spawn_roamer = function(figure_type, min_houses_coverage, action) { return __building_common_spawn_roamer(this.id, figure_type, min_houses_coverage, action) }
