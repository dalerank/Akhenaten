log_info("akhenaten: building_stonemason_guild started")

building_stonemason_guild = {
  animations : {
    preview : { pack:PACK_GENERAL, id:88 },
    base : { pack:PACK_GENERAL, id:88 },
    work : { pos:[73, -12], pack:PACK_GENERAL, id:88, offset:1, max_frames:12, duration:4 },
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  building_size: 2
  meta : { text_id: 173, help_link:"message_construction_guilds" }
  cost: [ 30, 50, 80, 100, 150 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[0], damage_risk: [1]
  max_walkers : 1
  info_advisors [ADVISOR_LABOR]
  flags {
    is_guild: true
    is_industry: true
    work_anim: true
  }
}
