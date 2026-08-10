log_info("akhenaten: building industry office started")

building_industry_office {
  animations {
    // Temporary: terrain overlay tile; city draw uses green cubes + "OFFICE" text.
    preview { pack:PACK_TERRAIN, id:21 }
    base { pack:PACK_TERRAIN, id:21 }
    minimap { pack:PACK_GENERAL, id:149, offset:160 }
  }

  input {
    resource : RESOURCE_PAPYRUS
  }

  building_size : 2
  management_radius : 7
  max_storage_amount : 100
  meta { help_id: 2, text_id: 97 }
  info_sound : "Wavs/forum.WAV"
  cost [ 25, 40, 70, 120, 200 ]
  desirability { value[2], step[1], step_size[-1], range[3] }
  laborers[10]
  fire_risk[3]
  damage_risk[2]
  labor_category : LABOR_CATEGORY_GOVERNMENT
  build_menu_text : "#building_industry_office"
  info_title_id : "#building_industry_office"
  flags {
    is_administration: true
  }
}

function IndustryOffice(building_id) {
  this.id = building_id
}

IndustryOffice.prototype = Object.create(Building.prototype)
IndustryOffice.prototype.constructor = IndustryOffice

IndustryOffice.prototype.is_management_active = function() {
  return __building_industry_office_is_active(this.id)
}

IndustryOffice.prototype.management_radius = function() {
  return __building_industry_office_radius(this.id)
}

IndustryOffice.prototype.managed_ids = function() {
  return __building_industry_office_managed_ids(this.id)
}

IndustryOffice.prototype.managed_count = function() {
  var ids = this.managed_ids()
  return ids ? ids.length : 0
}

IndustryOffice.prototype.mothball_all = function() {
  return __building_industry_office_mothball_all(this.id, true)
}

IndustryOffice.prototype.unmothball_all = function() {
  return __building_industry_office_mothball_all(this.id, false)
}

city.get_industry_office = function(building_id) {
  var b = city.get_building(building_id)
  if (!b || b.type != BUILDING_INDUSTRY_OFFICE) {
    return null
  }
  return new IndustryOffice(building_id)
}

[es=(building_industry_office, on_place_checks)]
function building_industry_office_on_place_checks(ev) {
  var papyrus = city.resources.papyrus
  var has_supply = (papyrus.count_active_industry > 0) || (papyrus.yards_stored > 0)
  if (has_supply) {
    return
  }

  city.warnings.show("#needs_papyrus")
  city.warnings.show_if_not(papyrus.can_produce, "#build_papyrus_maker")
  city.warnings.show_if_not(papyrus.can_import, "#import_papyrus_overseer")
  city.warnings.show_if_not(papyrus.trade_status == TRADE_STATUS_IMPORT, "#import_papyrus_trade_route")
}

[es=(building_industry_office, update_month)]
function building_industry_office_update_month(ev) {
  var building = city.get_building(ev.bid)
  var stored = building.stored_resource(RESOURCE_PAPYRUS)
  if (stored <= 0) {
    return
  }

  var want_spent = Math.floor(building.num_workers * 50 / 100)
  var spent = Math.min(stored, want_spent)
  building.consume_resource(RESOURCE_PAPYRUS, spent)
}

[es=(building_industry_office, ghost_preview)]
function building_industry_office_ghost_preview(ev) {
  var pixel = ev.pixel
  var radius = building_industry_office.management_radius || 7
  var size = building_industry_office.building_size || 2
  var overlay = get_image({ pack: PACK_TERRAIN, id: 21 }).tid
  var pixels = __camera_tile_range_pixels(city_planner.end, size, radius)
  for (var i = 0; i < pixels.length; i++) {
    city_planner.draw_overlay_tile(pixels[i], overlay, COLOR_MASK_BLUE, 1.0)
  }

  var offsets = [
    [0, 0],
    [-30, 15], [30, 15],
    [0, 30]
  ]
  for (var j = 0; j < offsets.length; j++) {
    city_planner.draw_flat_tile(
      { x: pixel.x + offsets[j][0], y: pixel.y + offsets[j][1] },
      COLOR_MASK_GREEN)
  }
}
