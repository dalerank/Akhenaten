log_info("akhenaten: building farm started")

building_meadow_farm_tile_offsets = [
    [0, 30], [30, 45], [60, 60], [90, 45], [120, 30]
  ]

  building_floodplain_farm_tile_offsets = [
    [60, 0], [90, 15], [120, 30], [30, 15], [60, 30], [90, 45], [0, 30], [30, 45], [60, 60]
  ]

  building_meadow_farm_grain {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:12 }
    }
    output  {
      resource : RESOURCE_GRAIN
      resource_second : RESOURCE_STRAW
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }
    output_resource_second_rate : 10

    build_menu_text : "Grain Meadow Farm"
    info_sound : "Wavs/farm1.wav"

    building_size : 3
    month_harvest: [MONTH_JANUARY, MONTH_MAY]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_grain {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:12 }
    }
    output  {
      resource : RESOURCE_GRAIN
      resource_second : RESOURCE_STRAW
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }
    output_resource_second_rate : 10

    building_size : 3
    month_harvest: [MONTH_JANUARY, MONTH_MAY]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    info_sound : "Wavs/farm1.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_chickpeas {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:30 }
    }
    output  {
      resource : RESOURCE_CHICKPEAS
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    build_menu_text : "Chickpeas Meadow Farm"
    info_sound : "Wavs/chickfarm.wav"

    building_size : 3
    month_harvest: [MONTH_APRIL]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }


  building_farm_chickpeas {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:30 }
    }

    output {
      resource : RESOURCE_CHICKPEAS
    }

    building_size : 3
    fire_proof : true
    month_harvest: [MONTH_APRIL]
    damage_proof : true
    meta { help_id:90, text_id:182 }
    info_sound : "Wavs/chickfarm.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_lettuce {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:18 }
    }
    output  {
      resource : RESOURCE_LETTUCE
    }

    build_menu_text : "Lettuce Meadow Farm"
    info_sound : "Wavs/lettucefarm.wav"

    building_size : 3
    month_harvest: [MONTH_APRIL]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_lettuce {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:18 }
    }

    output {
      resource : RESOURCE_LETTUCE
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    building_size : 3
    month_harvest: [MONTH_APRIL]
    fire_proof : true
    damage_proof : true
    meta { help_id:91, text_id:113 }
    info_sound : "Wavs/lettucefarm.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_pomegranates {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:24 }
    }
    output  {
      resource : RESOURCE_POMEGRANATES
    }

    build_menu_text : "Pomegranates Meadow Farm"
    info_sound : "Wavs/pomfarm.wav"

    building_size : 3
    month_harvest: [MONTH_JUNE, MONTH_NOVEMBER]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }


    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_pomegranates {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:20 }
      minimap {id:149, offset:160}
      crops { id:100, offset:24 }
    }

    output {
      resource : RESOURCE_POMEGRANATES
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    building_size : 3
    month_harvest: [MONTH_JUNE, MONTH_NOVEMBER]
    fire_proof : true
    damage_proof : true
    meta { help_id:91, text_id:114 }
    info_sound : "Wavs/pomfarm.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }
    cost [ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[12],
    fire_risk[4],
    damage_risk[1]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_barley {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:0 }
    }
    output  {
      resource : RESOURCE_BARLEY
    }

    build_menu_text : "Barley Meadow Farm"
    info_sound : "Wavs/barleyfarm.wav"

    building_size : 3
    month_harvest: [MONTH_FEBRUARY, MONTH_AUGUST]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_barley {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:0 }
    }

    output {
      resource : RESOURCE_BARLEY
    }

    building_size : 3
    fire_proof : true
    month_harvest [MONTH_FEBRUARY, MONTH_AUGUST]
    damage_proof : true
    meta { help_id:89, text_id:181 }
    info_sound : "Wavs/barleyfarm.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_flax {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:36 }
    }
    output  {
      resource : RESOURCE_FLAX
    }
    flags {
      is_farm: true
      is_industry: true
      is_food: true
    }

    build_menu_text : "Flax Meadow Farm"
    info_sound : "Wavs/flaxfarm.wav"

    building_size : 3
    month_harvest: [MONTH_DECEMBER]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_flax {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:36 }
    }

    output {
      resource : RESOURCE_FLAX
    }

    building_size : 3
    fire_proof : true
    damage_proof : true
    month_harvest: [MONTH_DECEMBER]
    meta { help_id: 90, text_id: 115 }
    info_sound : "Wavs/flaxfarm.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
    }

    cost [ 8, 10, 15, 20, 50 ]
    desirability { value[-2], step[1], step_size[1], range[2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

  building_meadow_farm_henna {
    animations : {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:225, offset:0 }
      work { id:225, offset:0, max_frames:1 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:225, offset:1 }
      farmland_watered { id:225, offset:0 }
      minimap {id:149, offset:160}
      crops { id:100, offset:30 }
    }
    output  {
      resource : RESOURCE_HENNA
    }
    flags {
      is_farm: true
      is_industry: true
    }

    build_menu_text : "Henna Meadow Farm"
    info_sound : "Wavs/farm2.wav"

    building_size : 3
    month_harvest: [MONTH_DECEMBER]
    fire_proof : true
    damage_proof : true
    meta { help_id:90, text_id:112 }
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

    needs {
      meadow : true
    }

    cost[ 8, 10, 15, 20, 50 ]
    desirability { value:[-2], step:[1], step_size:[1], range: [2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_meadow_farm_tile_offsets
  }

  building_farm_henna {
    animations {
      _pack { pack:PACK_GENERAL }
      preview { id:37, }
      base { id:37, offset:0 }
      work { id:37, offset:1, max_frames:12 }
      farm_house { id:225 }
      tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
      seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
      harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
      farmland { id:37 }
      minimap { id:149, offset:160 }
      crops { id:100, offset:30 }
    }

    output {
      resource : RESOURCE_HENNA
    }

    building_size : 3
    fire_proof : true
    damage_proof : true
    month_harvest[MONTH_DECEMBER]
    meta { help_id:90, text_id:306 }
    info_sound : "Wavs/farm2.wav"
    progress_max: 2000
    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
    needs {
      meadow : true
    }
    flags {
      is_farm: true
      is_industry: true
    }
    cost [ 8, 10, 15, 20, 50 ]
    desirability { value[-2], step[1], step_size[1], range[2] }
    laborers[10]
    fire_risk[0]
    damage_risk[0]
    tile_offsets : building_floodplain_farm_tile_offsets
  }

building_meadow_farm_figs {
  animations : {
    _pack { pack:PACK_GENERAL }
    preview { id:37, }
    base { id:225, offset:0 }
    work { id:225, offset:0, max_frames:1 }
    farm_house { id:225 }
    tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
    seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
    harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
    farmland { id:225, offset:1 }
    farmland_watered { id:225, offset:0 }
    minimap {id:149, offset:160}
    crops { id:100, offset:6 }
  }
  output  {
    resource : RESOURCE_FIGS
  }

  build_menu_text : "Figs Meadow Farm"
  info_sound : "Wavs/figs_farm.wav"

  building_size : 3
  month_harvest: [MONTH_SEPTEMBER]
  fire_proof : true
  damage_proof : true
  meta { help_id:90, text_id:112 }
  progress_max: 2000
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION

  needs {
    meadow : true
  }
  flags {
    is_farm: true
    is_industry: true
    is_food: true
  }

  cost[ 8, 10, 15, 20, 50 ]
  desirability { value:[-2], step:[1], step_size:[1], range: [2] }
  laborers[10]
  fire_risk[0]
  damage_risk[0]
  tile_offsets : building_meadow_farm_tile_offsets
}

building_farm_figs {
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:37, }
    base { id:37, offset:0 }
    work { id:37, offset:1, max_frames:12 }
    farm_house { id:225 }
    tiling { pack:PACK_SPR_MAIN, id:118, max_frames:12, duration:6 }
    seeding { pack:PACK_SPR_MAIN, id:119, max_frames:12, duration:6 }
    harvesting { pack:PACK_SPR_MAIN, id:120, max_frames:12, duration:6}
    farmland { id:37 }
    minimap {id:149, offset:160}
    crops { id:100, offset:6 }
  }

  output {
    resource : RESOURCE_FIGS,
  }

  building_size : 3
  fire_proof : true
  month_harvest: [MONTH_SEPTEMBER]
  damage_proof : true
  meta { help_id:90, text_id:183 }
  info_sound : "Wavs/figs_farm.wav"
  progress_max: 2000
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION,
  needs {
    meadow : true
  }
  flags {
    is_farm: true
    is_industry: true
    is_food: true
  }

  cost[ 8, 10, 15, 20, 50 ]
  desirability { value:[-2], step:[1], step_size:[1], range: [2] }
  laborers[10]
  fire_risk[0]
  damage_risk[0]
  tile_offsets : building_floodplain_farm_tile_offsets
}

function building_floodplain_farm_on_update_graphic(ev) {
  var farm = city.get_farm(ev.bid)
  if (farm.flood_imminent)
    return

  var progress = farm.progress
         if (progress < 400)  { farm.set_worker(-1, {x:1, y:1})
  } else if (progress < 500)  { farm.set_worker(e_farm_worker_tiling, {x:1, y:0})
  } else if (progress < 600)  { farm.set_worker(e_farm_worker_tiling, {x:2, y:0})
  } else if (progress < 700)  { farm.set_worker(e_farm_worker_tiling, {x:0, y:1})
  } else if (progress < 800)  { farm.set_worker(e_farm_worker_tiling, {x:1, y:1})
  } else if (progress < 900)  { farm.set_worker(e_farm_worker_tiling, {x:2, y:1})
  } else if (progress < 1000) { farm.set_worker(e_farm_worker_seeding, {x:0, y:2})
  } else if (progress < 1100) { farm.set_worker(e_farm_worker_seeding, {x:1, y:2})
  } else if (progress < 1200) { farm.set_worker(e_farm_worker_seeding, {x:2, y:2})
  } else if (progress < 1300) { farm.set_worker(e_farm_worker_harvesting, {x:1, y:0})
  } else if (progress < 1400) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:0})
  } else if (progress < 1500) { farm.set_worker(e_farm_worker_harvesting, {x:0, y:1})
  } else if (progress < 1600) { farm.set_worker(e_farm_worker_harvesting, {x:1, y:1})
  } else if (progress < 1700) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:1})
  } else if (progress < 1800) { farm.set_worker(e_farm_worker_harvesting, {x:0, y:2})
  } else if (progress < 1900) { farm.set_worker(e_farm_worker_harvesting, {x:1, y:2})
  } else                      { farm.set_worker(e_farm_worker_harvesting, {x:2, y:2})
  }
}

function building_meadow_farm_on_update_graphic(ev) {
  var farm = city.get_farm(ev.bid)
  var progress = farm.progress
  if (progress < 100)  { farm.set_worker(-1, {x:1, y:1})
  } else if (progress < 400)  { farm.set_worker(e_farm_worker_tiling, {x:0, y:1})
  } else if (progress < 800)  { farm.set_worker(e_farm_worker_seeding, {x:1, y:2})
  } else if (progress < 1200) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:2})
  } else if (progress < 1600) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:1})
  } else                      { farm.set_worker(e_farm_worker_harvesting, {x:2, y:0})
  }
}

[es=building_meadow_farm_grain_update_graphic]
function building_meadow_farm_grain_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_grain_update_graphic]
function building_farm_grain_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_chickpeas_update_graphic]
function building_meadow_farm_chickpeas_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_chickpeas_update_graphic]
function building_farm_chickpeas_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_lettuce_update_graphic]
function building_meadow_farm_lettuce_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_lettuce_update_graphic]
function building_farm_lettuce_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_pomegranates_update_graphic]
function building_meadow_farm_pomegranates_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_pomegranates_update_graphic]
function building_farm_pomegranates_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_barley_update_graphic]
function building_meadow_farm_barley_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_barley_update_graphic]
function building_farm_barley_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_flax_update_graphic]
function building_meadow_farm_flax_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_flax_update_graphic]
function building_farm_flax_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_henna_update_graphic]
function building_meadow_farm_henna_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_henna_update_graphic]
function building_farm_henna_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=building_meadow_farm_figs_update_graphic]
function building_meadow_farm_figs_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=building_farm_figs_update_graphic]
function building_farm_figs_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}