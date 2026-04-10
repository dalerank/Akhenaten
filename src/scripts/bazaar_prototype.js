log_info("akhenaten: bazaar_prototype.js loaded")

function Bazaar(building_id) {
    this.id = building_id
}

Bazaar.prototype = Object.create(Building.prototype)
Bazaar.prototype.constructor = Bazaar

Bazaar.prototype.resource_amount = function(resource_type) { return __bazaar_resource_amount(this.id, resource_type) }
Bazaar.prototype.idx_amount = function(index) { return __bazaar_idx_amount(this.id, index) }
Bazaar.prototype.idx_accepted = function(index) { return __bazaar_idx_accepted(this.id, index) }
Bazaar.prototype.res_accepted = function(resource_type) { return __bazaar_res_accepted(this.id, resource_type) }
