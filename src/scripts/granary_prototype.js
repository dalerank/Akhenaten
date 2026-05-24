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
