log_info("akhenaten: building_zoo started")

building_zoo {
  animations {
    // Dump: base frame 358×218 → isometric_size (360/60)=6. Ref: tmp/zoo_sprite/base_frame.png
    // Work frames = pack offsets 1+ (animals/water); count not in single export — verify in-game.
    preview : { pack:PACK_EXPANSION, id:6 },
    base : { pack:PACK_EXPANSION, id:6 },
    work : { pack:PACK_EXPANSION, id:6, offset:1, max_frames:19, can_reverse:true, duration:3 },
  }
  overlay_anims {
    // Stack icons near courtyard pots (SE of main building / by water cage)
    gamemeat {
      pos:[90, 70]
      pack:PACK_GENERAL
      id:205
      resource: RESOURCE_GAMEMEAT
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
    straw {
      pos:[100, 78]
      pack:PACK_GENERAL
      id:206
      resource: RESOURCE_STRAW
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
  }
  input : {
    resource : RESOURCE_GAMEMEAT
    resource_second : RESOURCE_STRAW
  }
  meta : { text_id:308, help_link:"message_building_zoo" }
  building_size : 6
  labor_category : LABOR_CATEGORY_ENTERTAINMENT
  cost : [ 500, 1500, 2000, 2200, 2600 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [3] }
  laborers:[30], fire_risk:[4], damage_risk: [3]
  flags {
    is_entertainment: true
  }
}

[es=(building_zoo, on_place_checks)]
function building_zoo_on_place_checks(ev) {
  var straw = city.resources.straw
  var meat = city.resources.gamemeat
  var straw_ok = straw.can_produce || straw.can_import || straw.could_import
  var meat_ok = meat.can_produce || meat.can_import || meat.could_import

  if (straw_ok && meat_ok) {
    city.warnings.show_if_not(straw.yards_stored > 0 || straw.count_active_industry > 0, "#building_needs_straw")
    city.warnings.show_if_not(meat.yards_stored > 0 || meat.count_active_industry > 0, "#building_needs_game_meat")
  }
}

[es=(building_zoo, update_day)]
function building_zoo_update_day(ev) {
  var zoo = city.get_entertainment_building(ev.bid)
  if (!zoo) {
    return
  }
  zoo.num_shows = 0
  if (zoo.juggler_visited > 0) {
    zoo.juggler_visited = zoo.juggler_visited - 1
    zoo.num_shows = zoo.num_shows + 1
  }
}

[es=(building_zoo, update_graphic)]
function building_zoo_update_graphic(ev) {
  var zoo = city.get_entertainment_building(ev.bid)
  if (!zoo) {
    return
  }
  // Work frames are animals/water — only play while cages are occupied.
  var animkey = (zoo.play_animation && zoo.juggler_visited > 0) ? "work" : "none"
  zoo.set_animation(animkey)
}
