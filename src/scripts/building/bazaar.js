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

building_bazaar {
  animations {
    preview {pack:PACK_GENERAL, id:22, }
    base {pack:PACK_GENERAL, id:22, }
    base_work { pack:PACK_GENERAL, id:22, offset:0 }
    fancy { pack:PACK_GENERAL, id:45 }
    fancy_work { pack:PACK_GENERAL, id:45, offset:0 }
    minimap {pack:PACK_GENERAL, id:149, offset:160}
  }

  max_search_distance : 40
  fancy_treshold_desirability : 30
  min_houses_coverage : 50
  overlay : OVERLAY_BAZAAR_ACCESS
  minimal_pick_food_amount : 100

  pick_food_below [600, 400, 200, 100]
  pick_good_below [150, 100, 50, 25]
  max_buyers : 2
  food_variety_target : 2

  building_size : 2
  meta { text_id: 97, help_link:"message_bazaar_history" }
  info_sound : "Wavs/MARKET.WAV"
  cost [ 8, 15, 30, 50, 100 ]
  desirability { value[-2], step[1], step_size[1], range[6] }

  laborers[5]
  fire_risk[4]
  damage_risk[2]

  flags {
    is_food: true
    keeps_visitor_paths: true
  }
}

[es=(building_bazaar, draw_usable_paths)]
function building_bazaar_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
