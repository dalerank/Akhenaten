log_info("akhenaten: loading building_fishing_wharf")

building_fishing_wharf {
  animations {
    preview { pack:PACK_TERRAIN, id:18 },
    base { pack:PACK_TERRAIN, id:18 },
    work_n { pos:[65, 0], pack:PACK_SPR_AMBIENT, id:46, offset:0, max_frames:24, duration:1 },
    work_w { pos:[80, 7], pack:PACK_SPR_AMBIENT, id:46, offset:0, max_frames:24, duration:3 },
    work_s { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:46, offset:2, max_frames:24, duration:4 },
    work_e { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:46, offset:3, max_frames:24, duration:4 },
    wait_n { pos:[85, 20], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    wait_w { pos:[85, 7], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:3 },
    wait_s { pos:[50, 17], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
    wait_e { pos:[55, -27], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:4 },
    minimap{pack:PACK_GENERAL, id:149, offset:160}
  }
  output {
    resource : RESOURCE_FISH
  }
  building_size : 2
  planer_update_rule {
    relative_orientation: 1
  }
  meta { help_id: 84, text_id: 102 }
  info_sound : "Wavs/shipyrd_r.wav"
  needs {
    water_access : true
    shoreline : true
  }
  flags {
    is_food: true
  }
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
  min_houses_coverage : 100
  cost [40, 70, 100, 150, 300 ]
  desirability { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers[6]
  fire_risk[4]
  damage_risk[1]
  max_storage: 400
  wait_time_multiplier: 5
  wait_time_base: 102
}

[es=(building_fishing_wharf, update_graphic)]
function building_fishing_wharf_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    if (!building.can_play_animation) {
        building.set_animation("none")
        return
    }

    var boat = building.get_figure(BUILDING_SLOT_BOAT)
    if (!boat.valid) {
        building.set_animation("none")
        return
    }

    var base = building.params.first_img("base")
    var image = __map_image_at(building.tile)
    var suffix = building_wharf_orient_suffix(image, base)

    if (boat.action_state != ACTION_194_FISHING_BOAT_AT_WHARF) {
        building.set_animation("wait" + suffix)
        return
    }

    var cart = building.get_figure(BUILDING_SLOT_CARTPUSHER)
    if (cart.valid) {
        building.set_animation("none")
        return
    }

    building.set_animation("work" + suffix)
}
