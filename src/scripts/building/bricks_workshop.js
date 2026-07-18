log_info("akhenaten: building_bricks_workshop started")

building_bricks_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pos:[46, -20], pack:PACK_GENERAL, id:124, offset:1, max_frames:10, duration:5 },
    straw : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    clay : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  input : {
    resource : RESOURCE_CLAY
    resource_second : RESOURCE_STRAW
  }
  output : {
    resource : RESOURCE_BRICKS
  }
  progress_max : 400,
  production_rate : 20,
  production_rate_dcy : [100, 80, 70, 60, 50],
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  meta : { help_id:1, text_id:180 }
  info_sound : "Wavs/brick.wav"
  cost: [ 12, 20, 30, 40, 50 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[2], damage_risk: [3]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
  }
}

[es=(building_bricks_workshop, update_animation)]
function building_bricks_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_CLAY) < 100 || b.stored_resource(RESOURCE_STRAW) < 100) {
        b.play_animation = false
    }
}
