log_info("akhenaten: building food mill started")

function FoodMill(building_id) {
    this.id = building_id
}

FoodMill.prototype = Object.create(Building.prototype)
FoodMill.prototype.constructor = FoodMill

FoodMill.prototype.total_stored = function() { return __food_mill_get_total_stored(this.id) }
FoodMill.prototype.amount = function(resource) { return __food_mill_get_amount(this.id, resource) }
FoodMill.prototype.free_space = function() { return __food_mill_get_freespace(this.id) }
FoodMill.prototype.food_variety = function() { return __food_mill_food_variety(this.id) }
FoodMill.prototype.resource_state = function(resource) { return __food_mill_resource_state(this.id, resource) }
FoodMill.prototype.resource_max_accept = function(resource) { return __food_mill_resource_max_accept(this.id, resource) }
FoodMill.prototype.resource_max_get = function(resource) { return __food_mill_resource_max_get(this.id, resource) }
FoodMill.prototype.is_empty_all = function() { return __food_mill_is_empty_all(this.id) }
FoodMill.prototype.toggle_empty_all = function() { __food_mill_toggle_empty_all(this.id) }
FoodMill.prototype.accept_none = function() { __food_mill_accept_none(this.id) }
FoodMill.prototype.cycle_resource_state = function(resource) { __food_mill_cycle_resource_state(this.id, resource) }
FoodMill.prototype.increase_decrease_resource_state = function(resource, increase) {
    __food_mill_increase_decrease_resource_state(this.id, resource, increase)
}

city.get_food_mill = function(building_id) {
    if (!__building_is_food_mill(building_id)) {
        return null
    }
    return new FoodMill(building_id)
}

building_food_mill {
  animations {
    // Temporary: terrain overlay tile; city draw uses green cubes + "MILL" text.
    preview { pack:PACK_TERRAIN, id:21 }
    base { pack:PACK_TERRAIN, id:21 }
    minimap { pack:PACK_GENERAL, id:149, offset:160 }
  }

  building_size : 3
  max_search_distance : 40
  min_workers_percent_for_tasks : 50
  min_houses_coverage : 100
  meta { text_id: 98, help_link:"message_building_granary" }
  info_sound : "Wavs/MARKET.WAV"
  cost [ 40, 60, 100, 150, 250 ]
  desirability { value[-2], step[1], step_size[1], range[4] }
  laborers[12]
  fire_risk[3]
  damage_risk[2]
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
  build_menu_text : "#building_food_mill"
  info_title_id : "#building_food_mill"
  max_capacity_stored : 1600
  max_per_type : 800
  flags {
    is_food: true
    keeps_visitor_paths: true
  }
}

[es=(building_food_mill, draw_usable_paths)]
function building_food_mill_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_food_mill, ghost_preview)]
function building_food_mill_ghost_preview(ev) {
  var pixel = ev.pixel
  // 3x3 isometric footprint (VIEW_OFFSETS 0..8)
  var offsets = [
    [0, 0],
    [-30, 15], [30, 15], [0, 30],
    [-60, 30], [60, 30], [-30, 45], [30, 45], [0, 60]
  ]
  for (var i = 0; i < offsets.length; i++) {
    city_planner.draw_flat_tile(
      { x: pixel.x + offsets[i][0], y: pixel.y + offsets[i][1] },
      COLOR_MASK_GREEN)
  }
}
