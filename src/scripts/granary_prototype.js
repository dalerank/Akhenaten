log_info("akhenaten: granary_prototype.js loaded")

function Granary(building_id) {
    this.id = building_id
}

Granary.prototype = Object.create(Building.prototype)
Granary.prototype.constructor = Granary

Granary.prototype.total_stored = function() { return __granary_get_total_stored(this.id) }
Granary.prototype.amount = function(resource) { return __granary_get_amount(this.id, resource) }
Granary.prototype.free_space = function() { return __granary_get_freespace(this.id) }
Granary.prototype.is_accepting = function(resource) { return __granary_is_accepting(this.id, resource) }
Granary.prototype.is_empty_all = function() { return __granary_is_empty_all(this.id) }
Granary.prototype.resource_state = function(resource) { return __granary_resource_state(this.id, resource) }
Granary.prototype.resource_max_accept = function(resource) { return __granary_resource_max_accept(this.id, resource) }
Granary.prototype.resource_max_get = function(resource) { return __granary_resource_max_get(this.id, resource) }
Granary.prototype.toggle_empty_all = function() { __granary_toggle_empty_all(this.id) }
Granary.prototype.accept_none = function() { __granary_accept_none(this.id) }
Granary.prototype.cycle_resource_state = function(resource) { __granary_cycle_resource_state(this.id, resource) }
Granary.prototype.increase_decrease_resource_state = function(resource, increase) { __granary_increase_decrease_resource_state(this.id, resource, increase) }
