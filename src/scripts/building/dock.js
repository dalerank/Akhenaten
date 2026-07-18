log_info("akhenaten: dock_prototype.js loaded")

function Dock(building_id) {
    this.id = building_id
}

Dock.prototype = Object.create(Building.prototype)
Dock.prototype.constructor = Dock

Dock.property.num_ships = { }

Dock.prototype.is_trade_accepted = function(resource) { return __dock_is_trade_accepted(this.id, resource) }
Dock.prototype.toggle_good_accepted = function(resource) { __dock_toggle_good_accepted(this.id, resource) }
Dock.prototype.unaccept_all_goods = function() { __dock_unaccept_all_goods(this.id) }
Dock.prototype.has_trade_ship = function() { return __dock_has_trade_ship(this.id) }
Dock.prototype.count_idle_dockers = function() { return __dock_count_idle_dockers(this.id) }

building_dock = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:49 },
    base : { pack:PACK_TERRAIN, id:49 },
    work_n : { pos:[135, -7], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    work_w : { pos:[100, -7], pack:PACK_SPR_AMBIENT, id:55, offset:1, max_frames:25, duration:8 },
    work_s : { pos:[55, 7], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:4 },
    work_e : { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
  }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  planner_update_rule : {
    relative_orientation: true
  }
  min_houses_coverage : 50
  building_size : 3
  meta : { help_id:82, text_id:101 }
  info_sound : "Wavs/DOCK1.WAV"
  sound_channel : SOUND_CHANNEL_CITY_DOCK
  needs : {
    water_access : true
    shoreline : true
  }
  cost: [ 20, 40, 70, 100, 150 ]
  desirability : { value:[-12], step:[2], step_size:[2], range: [6] }
  laborers:[12], fire_risk:[4], damage_risk: [1]
  flags {
    is_industry: true
  }
}

[es=(building_dock, update_animation)]
function building_dock_on_update_animation(ev) {
    var dock = city.get_dock(ev.bid)
    if (dock.num_ships > 0) {
        dock.play_animation = true
        return
    }
    __map_sprite_animation_set(dock.tile, 1)
    dock.play_animation = false
}

[es=(building_dock, update_graphic)]
function building_dock_on_update_graphic(ev) {
    var dock = city.get_dock(ev.bid)
    if (dock.count_idle_dockers() <= 0) {
        return
    }
    building_wharf_set_orient_animation(dock, "work")
}
