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
Bazaar.prototype.unaccept_all_goods = function() { __bazaar_unaccept_all_goods(this.id) }
Bazaar.prototype.toggle_res_accepted = function(resource_type) { __bazaar_toggle_res_accepted(this.id, resource_type) }
Bazaar.prototype.desired_variety = function() { return __bazaar_desired_variety(this.id) }
Bazaar.prototype.min_variety = function() { return __bazaar_min_variety(this.id) }
Bazaar.prototype.set_desired_variety = function(v) { __bazaar_set_desired_variety(this.id, v) }
Bazaar.prototype.set_min_variety = function(v) { __bazaar_set_min_variety(this.id, v) }
Bazaar.prototype.waiting_for_mill_variety = function() { return __bazaar_waiting_for_mill_variety(this.id) }

city.get_bazaar = function(building_id) {
    if (!__building_is_bazaar(building_id)) {
        return null
    }
    return new Bazaar(building_id)
}

[es=(building_bazaar, draw_usable_paths)]
function building_bazaar_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
