log_info("akhenaten: building farm started")

// prototype for farm buildings

function Farm(building_id) {
  this.id = building_id
}

Farm.prototype = Object.create(Building.prototype)
Farm.prototype.constructor = Farm

Farm.property.flood_imminent = { }
Farm.property.progress = { }
Farm.property.is_floodplain = { }

Farm.prototype.set_worker = function(action, coords) {
  __farm_set_worker(this.id, action, coords)
}

Farm.prototype.requested_workers = function() {
  return __farm_requested_workers(this.id)
}

// end prototype for farm buildings

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM

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
    sound_channel : SOUND_CHANNEL_CITY_CHICKFARM
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

var building_farm_required_valid_tiles = 4

function building_farm_footprint_check(tile, size) {
  var orientation = Math.floor(__camera.orientation / 2)
  var num_tiles = size * size
  var tiles = []
  var blocked = 0
  var valid_tiles = 0

  for (var i = 0; i < num_tiles; i++) {
    var offset = city.planner.tile_grid_offset(orientation, i)
    var check_tile = __map_tile_shift_offset(tile, offset)
    var tile_blocked = (__building_at(check_tile.x, check_tile.y) != 0) || __map_has_figure_at(check_tile)
    tiles.push({ tile: check_tile, blocked: tile_blocked })
    if (tile_blocked) {
      blocked++
    }
    if (terrain.is(check_tile, TERRAIN_MEADOW | TERRAIN_FLOODPLAIN)) {
      valid_tiles++
    }
  }

  if (blocked > 0) {
    return { blocked: true, tiles: tiles }
  }

  if (valid_tiles < building_farm_required_valid_tiles) {
    tiles = []
    for (var i = 0; i < num_tiles; i++) {
      var offset = city.planner.tile_grid_offset(orientation, i)
      var check_tile = __map_tile_shift_offset(tile, offset)
      var is_valid = terrain.is(check_tile, TERRAIN_MEADOW | TERRAIN_FLOODPLAIN)
      tiles.push({ tile: check_tile, blocked: !is_valid })
    }
    return { blocked: true, tiles: tiles }
  }

  return { blocked: false, tiles: tiles }
}

function building_farm_draw_partially_blocked(tiles) {
  for (var i = 0; i < tiles.length; i++) {
    var entry = tiles[i]
    var pixel = city.planner.tile_to_pixel(entry.tile)
    var color = entry.blocked ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30
    city.planner.draw_flat_tile(pixel, color)
  }
}

function building_farm_get_image(type, tile) {
  var params = city.get_building_params_by_type(type)
  if (terrain.is(tile, TERRAIN_FLOODPLAIN)) {
    var base = params.first_img("farmland")
    var fert = __fertility_for_farm_at_tile(tile.x, tile.y)
    var fertility_index = Math.min(7, Math.max(0, Math.floor(fert / 12)))
    return base + fertility_index
  }
  return params.first_img("farm_house")
}

function building_farm_draw_crops(type, progress, tile, point) {
  var params = city.get_building_params_by_type(type)
  var image_crops = params.first_img("crops")
  var is_floodplain = terrain.is(tile, TERRAIN_FLOODPLAIN)
  var offsets = is_floodplain ? building_floodplain_farm_tile_offsets : building_meadow_farm_tile_offsets
  var step = is_floodplain ? 200 : 400
  for (var i = 0; i < offsets.length; i++) {
    var growth = Math.min(5, Math.max(0, Math.floor((progress - i * step) / 100)))
    city.planner.draw_from_below(
      { x: point.x + offsets[i][0], y: point.y + offsets[i][1] },
      image_crops + growth
    )
  }
}

function building_farm_ghost_preview(ev) {
  var params = city.get_building_params_by_type(city.planner.build_type)
  var check = building_farm_footprint_check(ev.end, params.building_size)
  if (check.blocked) {
    building_farm_draw_partially_blocked(check.tiles)
    return
  }

  var ghost_pixel = { x: ev.pixel.x - 60, y: ev.pixel.y + 30 }
  var image_id = building_farm_get_image(city.planner.build_type, ev.end)
  city.planner.draw_ghost(ghost_pixel, image_id)
  building_farm_draw_crops(city.planner.build_type, 0, ev.end, ghost_pixel)
}

function building_farm_finalize_check(ev) {
  var params = city.get_building_params_by_type(city.planner.build_type)
  var orientation = Math.floor(__camera.orientation / 2)
  var num_tiles = params.building_size * params.building_size
  var meadow_tiles = 0
  var blocked_tiles = 0

  for (var i = 0; i < num_tiles; i++) {
    var offset = city.planner.tile_grid_offset(orientation, i)
    var check_tile = __map_tile_shift_offset(ev.start, offset)
    var tile_blocked = (__building_at(check_tile.x, check_tile.y) != 0) || __map_has_figure_at(check_tile)
    if (tile_blocked) {
      blocked_tiles++
    }
    if (terrain.is(check_tile, TERRAIN_MEADOW | TERRAIN_FLOODPLAIN)) {
      meadow_tiles++
    }
  }

  if (blocked_tiles > 0) {
    city.planner.set_warning("Some tiles blocked")
    city.planner.finalize_check_result = CAN_NOT_PLACE
    return
  }

  if (meadow_tiles < building_farm_required_valid_tiles) {
    city.planner.set_warning("Need more meadow tiles")
    city.planner.finalize_check_result = CAN_NOT_PLACE
    return
  }

  city.planner.finalize_check_result = ev.state
}

function building_floodplain_farm_on_update_graphic(ev) {
  var farm = city.get_farm(ev.bid)
  if (!farm || farm.flood_imminent)
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
  if (!farm) {
    return
  }
  var progress = farm.progress
  if (progress < 100)  { farm.set_worker(-1, {x:1, y:1})
  } else if (progress < 400)  { farm.set_worker(e_farm_worker_tiling, {x:0, y:1})
  } else if (progress < 800)  { farm.set_worker(e_farm_worker_seeding, {x:1, y:2})
  } else if (progress < 1200) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:2})
  } else if (progress < 1600) { farm.set_worker(e_farm_worker_harvesting, {x:2, y:1})
  } else                      { farm.set_worker(e_farm_worker_harvesting, {x:2, y:0})
  }
}

[es=(building_meadow_farm_grain, update_graphic)]
function building_meadow_farm_grain_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_grain, update_graphic)]
function building_farm_grain_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_chickpeas, update_graphic)]
function building_meadow_farm_chickpeas_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_chickpeas, update_graphic)]
function building_farm_chickpeas_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_lettuce, update_graphic)]
function building_meadow_farm_lettuce_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_lettuce, update_graphic)]
function building_farm_lettuce_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_pomegranates, update_graphic)]
function building_meadow_farm_pomegranates_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_pomegranates, update_graphic)]
function building_farm_pomegranates_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_barley, update_graphic)]
function building_meadow_farm_barley_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_barley, update_graphic)]
function building_farm_barley_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_flax, update_graphic)]
function building_meadow_farm_flax_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_flax, update_graphic)]
function building_farm_flax_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_henna, update_graphic)]
function building_meadow_farm_henna_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_henna, update_graphic)]
function building_farm_henna_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_figs, update_graphic)]
function building_meadow_farm_figs_on_update_graphic(ev) {
  building_meadow_farm_on_update_graphic(ev)
}

[es=(building_farm_figs, update_graphic)]
function building_farm_figs_on_update_graphic(ev) {
  building_floodplain_farm_on_update_graphic(ev)
}

[es=(building_meadow_farm_grain, ghost_preview)]
function building_meadow_farm_grain_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_grain, ghost_preview)]
function building_farm_grain_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_chickpeas, ghost_preview)]
function building_meadow_farm_chickpeas_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_chickpeas, ghost_preview)]
function building_farm_chickpeas_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_lettuce, ghost_preview)]
function building_meadow_farm_lettuce_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_lettuce, ghost_preview)]
function building_farm_lettuce_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_pomegranates, ghost_preview)]
function building_meadow_farm_pomegranates_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_pomegranates, ghost_preview)]
function building_farm_pomegranates_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_barley, ghost_preview)]
function building_meadow_farm_barley_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_barley, ghost_preview)]
function building_farm_barley_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_flax, ghost_preview)]
function building_meadow_farm_flax_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_flax, ghost_preview)]
function building_farm_flax_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_henna, ghost_preview)]
function building_meadow_farm_henna_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_henna, ghost_preview)]
function building_farm_henna_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_figs, ghost_preview)]
function building_meadow_farm_figs_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_farm_figs, ghost_preview)]
function building_farm_figs_ghost_preview(ev) {
  building_farm_ghost_preview(ev)
}

[es=(building_meadow_farm_grain, finalize_check)]
function building_meadow_farm_grain_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_grain, finalize_check)]
function building_farm_grain_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_chickpeas, finalize_check)]
function building_meadow_farm_chickpeas_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_chickpeas, finalize_check)]
function building_farm_chickpeas_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_lettuce, finalize_check)]
function building_meadow_farm_lettuce_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_lettuce, finalize_check)]
function building_farm_lettuce_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_pomegranates, finalize_check)]
function building_meadow_farm_pomegranates_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_pomegranates, finalize_check)]
function building_farm_pomegranates_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_barley, finalize_check)]
function building_meadow_farm_barley_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_barley, finalize_check)]
function building_farm_barley_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_flax, finalize_check)]
function building_meadow_farm_flax_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_flax, finalize_check)]
function building_farm_flax_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_henna, finalize_check)]
function building_meadow_farm_henna_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_henna, finalize_check)]
function building_farm_henna_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_meadow_farm_figs, finalize_check)]
function building_meadow_farm_figs_finalize_check(ev) { building_farm_finalize_check(ev) }

[es=(building_farm_figs, finalize_check)]
function building_farm_figs_finalize_check(ev) { building_farm_finalize_check(ev) }