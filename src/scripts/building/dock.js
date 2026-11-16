log_info("akhenaten: dock_prototype.js loaded")

/* Constructor, prototype chain, trade-order methods, toString: native (js_register_dock). */

Dock.property.num_ships = { }
Dock.property.trade_ship = { }

Dock.prototype.has_trade_ship = function() { return this.trade_ship > 0 }
Dock.prototype.trade_ship_moored = function() {
    if (!this.trade_ship) {
        return false
    }
    var ship = city.get_figure(this.trade_ship)
    return ship.valid && ship.action_state == ACTION_112_TRADE_SHIP_MOORED
}

city.get_dock = function(building_id) {
    if (!__building_is_dock(building_id)) {
        return null
    }
    return new Dock(building_id)
}

building_dock = {
  animations : {
    preview : { pack:PACK_TERRAIN, id:49 },
    base : { pack:PACK_TERRAIN, id:49 },
    // OG draw_dock_anim: no ship → ANIM_FISHING_WHARF (= ambient 55), offsets dock_anim 0..3
    wait_n : { pos:[132, -7], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    wait_w : { pos:[115, 25], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:8 },
    wait_s : { pos:[60, 20], pack:PACK_SPR_AMBIENT, id:55, offset:1, max_frames:25, duration:4 },
    wait_e : { pos:[49, -4], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
    // Ship docked → ANIM_DOCK_SHIP (= ambient 56), offsets dock_anim 4..7; OG caps frame at 20
    work_n : { pos:[152, -13], pack:PACK_SPR_AMBIENT, id:56, offset:3, max_frames:20, duration:8 },
    work_w : { pos:[123, 16], pack:PACK_SPR_AMBIENT, id:56, offset:0, max_frames:20, duration:8 },
    work_s : { pos:[65, 14], pack:PACK_SPR_AMBIENT, id:56, offset:1, max_frames:20, duration:4 },
    work_e : { pos:[38, -12], pack:PACK_SPR_AMBIENT, id:56, offset:2, max_frames:20, duration:4 },
    minimap { pack:PACK_GENERAL, id:149, offset:160 }
  }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  planner_update_rule : {
    relative_orientation: true
  }
  min_houses_coverage : 50
  building_size : 3
  meta : { text_id:101, help_link:"message_building_dock" }
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
    no_map_edge_margin: true
    is_industry: true
  }
}

[es=(building_dock, update_animation)]
function building_dock_on_update_animation(ev) {
    var dock = city.get_dock(ev.bid)
    if (!dock) {
        return
    }
    // OG animation_offset: listed_worker_type → workers_then_advance
    dock.play_animation = dock.num_workers > 0
}

[es=(building_dock, update_graphic)]
function building_dock_on_update_graphic(ev) {
    var dock = city.get_dock(ev.bid)
    if (!dock) {
        return
    }
    building_wharf_update_graphic_moored(dock, dock.trade_ship_moored())
}

[es=(building_dock, highlight_waypoints)]
function building_dock_highlight_waypoints(ev) {
    var building = city.get_building(ev.bid)
    __map_highlight_set(building.water_access_tile(0), HIGHLIGHT_GREEN)
    __map_highlight_set(building.water_access_tile(1), HIGHLIGHT_GREEN)
}
