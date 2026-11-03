log_info("akhenaten: building temple complex started")

var TEMPLE_COMPLEX_UPGRADE_ALTAR = 1
var TEMPLE_COMPLEX_UPGRADE_ORACLE = 2

function TempleComplex(building_id) {
    this.id = building_id
}

TempleComplex.prototype = Object.create(Building.prototype)
TempleComplex.prototype.constructor = TempleComplex

TempleComplex.property.temple_complex_upgrades = { }

TempleComplex.prototype.has_upgrade = function(upgrade) {
    return (this.temple_complex_upgrades & upgrade) != 0
}

building_temple_complex_osiris {
    animations : {
      _pack { pack:PACK_TEMPLE_NILE }
      preview { pack:PACK_GENERAL, id:42}
      main_n { id:1, offset:3 }
      main_w { id:3, offset:0 }
      main_e { id:1, offset:0 }
      main_s { id:3, offset:3 }
      oracle_n { id:2 }
      oracle_w { id:2, offset:3 }
      altar_n { id:3 }
      altar_w { id:3, offset:3 }
      tiles_0 { id:4 }
      tiles_1 { id:4, offset:1 }
      tiles_2 { id:4, offset:2 }
      tiles_3 { id:4, offset:3 }
      statue_1 { id:5 }
      statue_2n { id:6 }
      statue_2e { id:6, offset:2 }
      statue_2s { id:6, offset:4 }
      statue_2w { id:6, offset:6 }
    }

    building_size : 3
    planner_update_rule : {
      unique_building : true
    }

    min_houses_coverage : 50
    spawn_delays : [3, 7, 10, 15, 20]
    damage_proof : true
    fire_proof : true
    labor_category : LABOR_CATEGORY_RELIGION
    cost [ 400, 800, 1200, 1500, 2000 ]
    desirability { value[20], step[2], step_size[-4], range[6] }
    laborers[50]
    fire_risk[0]
    damage_risk[2]

    allowed_altar [ BUILDING_TEMPLE_COMPLEX_ALTAR_AMON ]
    allowed_oracle [ BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH ]

    flags {
      is_temple_complex: true
      is_religion: true
      keeps_visitor_paths: true
    }
  }

  building_temple_complex_altar_amon {
    // BUILDING_TEMPLE_COMPLEX_ALTAR_AMON
    animations  {
      _pack { pack:PACK_TEMPLE_NILE }
      preview { id:7}
      base_n  { id:2, offset:3 }
      base_w  { id:2 }
      base_e  { id:2, offset:0 }
      base_s  { id:2, offset:3 }
      fancy_n { id:7, offset:0 }
      fancy_w { id:7, offset:1 }
    }
    build_menu_text [ 189, 4 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      altar : true
    }
    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_oracle_thoth {
    // BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH
    animations {
      _pack { pack:PACK_TEMPLE_NILE }
      preview { id:7, offset:2 }
      base_n  { id:3, offset:3 }
      base_w  { id:1, offset:0 }
      base_e  { id:3 }
      base_s  { id:1, offset:3 }
      fancy_n { id:7, offset:2 }
      fancy_w { id:7, offset:3 }
    }
    build_menu_text [ 189, 5 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      oracle : true
    }

    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_seth {
    animations {
      _pack { pack:PACK_TEMPLE_SETH }
      preview { pack:PACK_GENERAL, id:42}
      main_n { id:1, offset:3 }
      main_w { id:3, offset:0 }
      main_e { id:1, offset:0 }
      main_s { id:3, offset:3 }
      oracle_n { id:2 }
      oracle_w { id:2, offset:3 }
      altar_n { id:3 }
      altar_w { id:3, offset:3 }
      tiles_0 { id:4 }
      tiles_1 { id:4, offset:1 }
      tiles_2 { id:4, offset:2 }
      tiles_3 { id:4, offset:3 }
      statue_1 { id:5 }
      statue_2n { id:6 }
      statue_2e { id:6, offset:2 }
      statue_2s { id:6, offset:4 }
      statue_2w { id:6, offset:6 }
    }

    building_size : 3,
    planner_update_rule {
      unique_building : true
    }

    min_houses_coverage : 50
    spawn_delays : [3, 7, 10, 15, 20]
    damage_proof : true
    fire_proof : true
    labor_category : LABOR_CATEGORY_RELIGION
    cost [ 400, 800, 1200, 1500, 2000 ]
    desirability { value[20], step[2], step_size[-4], range[6] }
    laborers[50]
    fire_risk[0]
    damage_risk[2]

    allowed_altar [ BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS ]
    allowed_oracle [ BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET ]

    flags {
      is_temple_complex: true
      is_religion: true
      keeps_visitor_paths: true
    }
  }

  building_temple_complex_altar_anubis {
    // BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS
    animations  {
      _pack { pack:PACK_TEMPLE_SETH }
      preview { id:7 }
      base_n  { id:2, offset:3 }
      base_w  { id:2, offset:0 }
      base_e  { id:2, offset:0 }
      base_s  { id:2, offset:3 }
      fancy_n { id:7, offset:1 }
      fancy_w { id:7, offset:0 }
      fancy_e { id:7, offset:0 }
      fancy_s { id:7, offset:1 }
    }
    build_menu_text [ 189, 6 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      altar : true
    }
    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_oracle_sekhmet {
    // BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET
    animations {
      _pack { pack:PACK_TEMPLE_SETH }
      preview { id:7, offset:2 }
      base_n  { id:3, offset:3 }
      base_w  { id:1, offset:0 }
      base_e  { id:3 }
      base_s  { id:1, offset:3 }
      fancy_n { id:7, offset:3 }
      fancy_w { id:7, offset:2 }
      fancy_e { id:7, offset:2 }
      fancy_s { id:7, offset:3 }
    }
    build_menu_text [ 189, 7 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      oracle : true
    }

    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_ra {
    animations {
      _pack { pack:PACK_TEMPLE_RA }
      preview { pack:PACK_GENERAL, id:42}
      main_n { id:1, offset:3 }
      main_w { id:3, offset:0 }
      main_e { id:1, offset:0 }
      main_s { id:3, offset:3 }
      oracle_n { id:2 }
      oracle_w { id:2, offset:3 }
      altar_n { id:3 }
      altar_w { id:3, offset:3 }
      tiles_0 { id:4 }
      tiles_1 { id:4, offset:1 }
      tiles_2 { id:4, offset:2 }
      tiles_3 { id:4, offset:3 }
      statue_1 { id:5 }
      statue_2n { id:6 }
      statue_2e { id:6, offset:2 }
      statue_2s { id:6, offset:4 }
      statue_2w { id:6, offset:6 }
    }

    building_size : 3
    planner_update_rule {
      unique_building : true
    }

    min_houses_coverage : 50
    spawn_delays : [3, 7, 10, 15, 20]
    damage_proof : true
    fire_proof : true
    labor_category : LABOR_CATEGORY_RELIGION
    cost [ 400, 800, 1200, 1500, 2000 ]
    desirability { value[20], step[2], step_size[-4], range[6] }
    laborers[50]
    fire_risk[0]
    damage_risk[2]

    allowed_altar [ BUILDING_TEMPLE_COMPLEX_ALTAR_SEBEK ]
    allowed_oracle [ BUILDING_TEMPLE_COMPLEX_ORACLE_MIN ]

    flags {
      is_temple_complex: true
      is_religion: true
      keeps_visitor_paths: true
    }
  }

  building_temple_complex_altar_sebek {
    animations  {
      _pack { pack:PACK_TEMPLE_RA }
      preview { id:7}
      base_n  { id:2, offset:3 }
      base_w  { id:2 }
      base_e  { id:2, offset:0 }
      base_s  { id:2, offset:3 }
      fancy_n { id:7, offset:1 }
      fancy_w { id:7, offset:0 }
      fancy_e { id:7, offset:0 }
      fancy_s { id:7, offset:1 }
    }
    build_menu_text [ 189, 0 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      altar : true
    }
    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_oracle_min {
    animations {
      _pack { pack:PACK_TEMPLE_RA }
      preview { id:7, offset:2 }

      base_n  { id:3, offset:3 }
      base_w  { id:1, offset:0 }
      base_e  { id:3, offset:0 }
      base_s  { id:1, offset:3 }

      fancy_n { id:7, offset:3 }
      fancy_w { id:7, offset:2 }
      fancy_e { id:7, offset:2 }
      fancy_s { id:7, offset:3 }
    }
    build_menu_text [ 189, 1 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      oracle : true
    }

    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_ptah {
    animations {
      _pack { pack:PACK_TEMPLE_PTAH }
      preview { pack:PACK_GENERAL, id:42}
      main_n { id:1, offset:3 }
      main_w { id:3, offset:0 }
      main_e { id:1, offset:0 }
      main_s { id:3, offset:3 }
      oracle_n { id:2 }
      oracle_w { id:2, offset:3 }
      altar_n { id:3 }
      altar_w { id:3, offset:3 }
      tiles_0 { id:4 }
      tiles_1 { id:4, offset:1 }
      tiles_2 { id:4, offset:2 }
      tiles_3 { id:4, offset:3 }
      statue_1 { id:5 }
      statue_2n { id:6 }
      statue_2e { id:6, offset:2 }
      statue_2s { id:6, offset:4 }
      statue_2w { id:6, offset:6 }
    }

    building_size : 3
    planner_update_rule {
      unique_building : true
    }

    min_houses_coverage : 50
    spawn_delays : [3, 7, 10, 15, 20]
    damage_proof : true
    fire_proof : true
    labor_category : LABOR_CATEGORY_RELIGION
    cost [ 400, 800, 1200, 1500, 2000 ]
    desirability { value[20], step[2], step_size[-4], range[6] }
    laborers[50]
    fire_risk[0]
    damage_risk[2]

    allowed_altar [ BUILDING_TEMPLE_COMPLEX_ALTAR_MAAT ]
    allowed_oracle [ BUILDING_TEMPLE_COMPLEX_ORACLE_HORUS ]

    flags {
      is_temple_complex: true
      is_religion: true
      keeps_visitor_paths: true
    }
  }

  building_temple_complex_altar_maat {
    animations  {
      _pack { pack:PACK_TEMPLE_RA }
      preview { id:7}
      base_n  { id:2, offset:3 }
      base_w  { id:2 }
      base_e  { id:2, offset:0 }
      base_s  { id:2, offset:3 }
      fancy_n { id:7, offset:1 }
      fancy_w { id:7, offset:0 }
      fancy_e { id:7, offset:0 }
      fancy_s { id:7, offset:1 }
    }
    build_menu_text [ 189, 2 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      altar : true
    }
    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_oracle_horus {
    animations {
      _pack { pack:PACK_TEMPLE_PTAH }
      preview { id:7, offset:2 }
      base_n  { id:3, offset:3 }
      base_w  { id:1, offset:0 }
      base_e  { id:3 }
      base_s  { id:1, offset:3 }
      fancy_n { id:7, offset:3 }
      fancy_w { id:7, offset:2 }
      fancy_e { id:7, offset:2 }
      fancy_s { id:7, offset:3 }
    }
    build_menu_text [ 189, 3 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      oracle : true
    }

    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_bast {
    animations {
      _pack { pack:PACK_TEMPLE_BAST }
      preview { pack:PACK_GENERAL, id:42}
      main_n { id:1, offset:3 }
      main_w { id:1 }
      main_e { id:3 }
      main_s { id:3 }
      oracle_n { id:2 }
      oracle_w { id:2, offset:3 }
      altar_n { id:3 }
      altar_w { id:3, offset:3 }
      tiles_0 { id:4 }
      tiles_1 { id:4, offset:1 }
      tiles_2 { id:4, offset:2 }
      tiles_3 { id:4, offset:3 }
      statue_1 { id:5 }
      statue_2n { id:6 }
      statue_2e { id:6, offset:2 }
      statue_2s { id:6, offset:4 }
      statue_2w { id:6, offset:6 }
    }

    building_size : 3
    planner_update_rule {
      unique_building : true
    }

    min_houses_coverage : 50
    spawn_delays : [3, 7, 10, 15, 20]
    labor_category : LABOR_CATEGORY_RELIGION
    // Pharaoh_Model_* Large Temple to Bast (CST / DRI)
    cost [ 400, 1600, 2000, 2400, 3000 ]
    desirability { value[20], step[2], step_size[-4], range[6] }
    laborers[50]
    fire_risk[0]
    damage_risk [ 2, 8, 10, 12, 15 ]

    // OG Bast complex bonuses (citywide while the complex stands)
    food_consumption_pct : 80
    goods_consumption_pct : 80
    service_decay_skip_odd_months : 1
    hathor_sentiment_bonus : 10
    isis_health_bonus : 10

    allowed_altar [ BUILDING_TEMPLE_COMPLEX_ALTAR_ISIS ]
    allowed_oracle [ BUILDING_TEMPLE_COMPLEX_ORACLE_HATHOR ]

    flags {
      is_temple_complex: true
      is_religion: true
      keeps_visitor_paths: true
    }
  }

  building_temple_complex_altar_isis {
    animations  {
      _pack { pack:PACK_TEMPLE_BAST }
      preview { id:7}
      base_n  { id:2, offset:3 }
      base_w  { id:2 }
      base_e  { id:2, offset:0 }
      base_s  { id:2, offset:3 }
      fancy_n { id:7, offset:1 }
      fancy_w { id:7, offset:0 }
      fancy_e { id:7, offset:0 }
      fancy_s { id:7, offset:1 }
    }
    build_menu_text [ 189, 8 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      altar : true
    }
    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

  building_temple_complex_oracle_hathor {
    animations {
      _pack { pack:PACK_TEMPLE_BAST }
      preview { id:7, offset:2 }
      base_n  { id:3, offset:3 }
      base_w  { id:1, offset:0 }
      base_e  { id:3 }
      base_s  { id:1, offset:3 }
      fancy_n { id:7, offset:3 }
      fancy_w { id:7, offset:2 }
      fancy_e { id:7, offset:2 }
      fancy_s { id:7, offset:3 }
    }
    build_menu_text [ 189, 9 ]

    building_size : 3
    labor_category : LABOR_CATEGORY_RELIGION
    needs {
      oracle : true
    }

    damage_proof : true
    fire_proof : true
    cost [ 180, 250, 300, 500, 800 ]
  }

[es=(building_temple_complex_osiris, spawn_figure)]
function building_temple_complex_osiris_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_temple_complex_osiris, FIGURE_PRIEST, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_complex_ra, spawn_figure)]
function building_temple_complex_ra_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_temple_complex_ra, FIGURE_PRIEST, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_complex_ptah, spawn_figure)]
function building_temple_complex_ptah_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_temple_complex_ptah, FIGURE_PRIEST, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_complex_seth, spawn_figure)]
function building_temple_complex_seth_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_temple_complex_seth, FIGURE_PRIEST, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_complex_bast, spawn_figure)]
function building_temple_complex_bast_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_temple_complex_bast, FIGURE_PRIEST, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_complex_osiris, draw_usable_paths)]
function building_temple_complex_osiris_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_temple_complex_ra, draw_usable_paths)]
function building_temple_complex_ra_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_temple_complex_ptah, draw_usable_paths)]
function building_temple_complex_ptah_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_temple_complex_seth, draw_usable_paths)]
function building_temple_complex_seth_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_temple_complex_bast, draw_usable_paths)]
function building_temple_complex_bast_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}