log_info("akhenaten: load houses started")

building_house_crude_hut {
  animations {
    _pack { pack: PACK_GENERAL }
    preview{ id: 36 }
    base{ id: 36 }
    house{ id: 26 }
    minimap{ id:148 }    
  }

  meta { help_id:128, text_id:-1 }

  building_size : 1
  can_merge : true

  variants {
    _1 { pack: PACK_GENERAL, id: 26, offset:0 }
    _2 { pack: PACK_GENERAL, id: 26, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 26, offset:4 }
  }
  
  planner_update_rule {
    is_draggable : true
  }

  desirability { value[-2], step[1], step_size[1], range[3] }
  crime { value[5], step[1], step_size[-1], range[4] }
  labor_caegory : LABOR_CATEGORY_HOUSE

  laborers[0]
  cost [ 5, 10, 20, 40, 50 ]
  
  fire_risk[3]
  damage_risk[0]

  model {
    devolve_desirability[-99,-99,-99,-99,-99]
    evolve_desirability[-10,-10,-10,-10,-10]
    entertainment[0,0,0,0,0]
    water[0,0,0,0,0]
    religion[0,0,0,0,0]
    education[0,0,0,0,0]
    food[0,0,0,0,0]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,0,0,0]
    food_consumption_percentage[30,30,30,30,30]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,20,30,40,50]
    crime_risk_base[1,22,25,35,35]
    prosperity[15,10,5,5,5]
    max_people[5,5,5,5,5]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,40,50,60,70]
    disease_risk[-120,30,40,60,70]
    food_storage_multiplier[4,4,4,4,4]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_sturdy_hut {
  animations {
    _pack { pack: PACK_GENERAL }
    house {id: 26, offset:2 }
    minimap{id:148}
  }
  building_size : 1
  can_merge : true

  variants {
    _1 { pack: PACK_GENERAL, id: 26, offset:2 }
    _2 { pack: PACK_GENERAL, id: 26, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 26, offset:5 }
  }

  desirability { value[-2], step[1], step_size[1], range[3] }
  crime { value[4], step[1], step_size[-1], range[4] }

  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[3]
  damage_risk[0]

  model {
    devolve_desirability[-12,-12,-12,-12,-12]
    evolve_desirability[-7,-6,-5,-5,-5]
    entertainment[0,0,0,0,0]
    water[1,1,1,1,1]
    religion[0,0,0,0,0]
    education[0,0,0,0,0]
    food[0,0,0,0,0]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,0,0,0]
    food_consumption_percentage[32,32,32,32,32]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,27,36,45]
    crime_risk_base[1,22,25,35,35]
    prosperity[20,15,10,10,10]
    max_people[7,7,7,7,7]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,70]
    disease_risk[-120,20,30,50,60]
    food_storage_multiplier[4,4,4,4,4]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_meager_shanty {
  animations {
    _pack { pack: PACK_GENERAL }
    house{ id: 27 }
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 27, offset:0 }
    _2 { pack: PACK_GENERAL, id: 27, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 27, offset:4 }
  }

  desirability { value[-2], step[1], step_size[1], range[2] }
  crime { value[3], step[1], step_size[-1], range[4] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[20]
  damage_risk[0]

  model {
    devolve_desirability[-9,-8,-7,-7,-7]
    evolve_desirability[-2,-1,0,0,0]
    entertainment[0,0,0,0,0]
    water[1,1,1,1,1]
    religion[0,0,0,0,0]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[1,1,1,1,1]
    food_consumption_percentage[34,34,34,34,34]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,18,24,32,40]
    crime_risk_base[1,20,22,30,30]
    prosperity[25,20,15,15,15]
    max_people[9,9,9,9,9]
    tax_multiplier[3,2,1,1,1]
    malaria_risk[-120,20,40,50,60]
    disease_risk[-120,10,20,40,60]
    food_storage_multiplier[4,4,4,4,4]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_common_shanty {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 27, offset:2}

    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 27, offset:2 }
    _2 { pack: PACK_GENERAL, id: 27, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 27, offset:5 }
  }

  desirability { value[-2], step[1], step_size[1], range[2] }
  crime { value[2], step[1], step_size[-1], range[4] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-4,-3,-2,-2,-2]
    evolve_desirability[2,3,4,4,4]
    entertainment[0,0,0,0,0]
    water[1,1,1,1,1]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[1,1,1,1,1]
    food_consumption_percentage[36,36,36,36,36]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,17,21,28,35]
    crime_risk_base[1,20,22,30,30]
    prosperity[30,25,20,20,20]
    max_people[11,11,11,11,11]
    tax_multiplier[3,2,1,1,1]
    malaria_risk[-120,20,30,50,60]
    disease_risk[-120,8,10,30,50]
    food_storage_multiplier[4,4,4,4,4]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_rough_cottage {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 28}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true

  variants {
    _1 { pack: PACK_GENERAL, id: 28, offset:0 }
    _2 { pack: PACK_GENERAL, id: 28, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 28, offset:4 }
  }

  variants_merged_inside {
    _1 { pack: PACK_CUSTOM_HOUSE, id: 0, offset:3 }
  }

  desirability { value[-2], step[1], step_size[1], range[2] }
  crime { value[1], step[1], step_size[-1], range[4] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[5]
  damage_risk[3]

  model {
    devolve_desirability[0,1,2,2,2]
    evolve_desirability[6,7,8,8,9]
    entertainment[0,0,0,0,0]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[1,1,1,1,1]
    food_consumption_percentage[38,38,38,38,38]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,16,19,26,32]
    crime_risk_base[1,17,20,30,30]
    prosperity[35,30,25,25,25]
    max_people[13,13,13,13,13]
    tax_multiplier[3,2,2,2,1]
    malaria_risk[-120,10,0,20,30]
    disease_risk[-120,5,5,20,40]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_ordinary_cottage {
  animations {
    _pack { pack: PACK_GENERAL }
    house {id: 28, offset:2}
    minimap {id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 28, offset:2 }
    _2 { pack: PACK_GENERAL, id: 28, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 28, offset:5 }
  }

  desirability { value[-2], step[1], step_size[1], range[2] }
  crime { value[0], step[1], step_size[-1], range[4] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[0]

  model {
    devolve_desirability[4,6,6,6,7]
    evolve_desirability[10,11,12,12,13]
    entertainment[10,10,10,10,10]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[1,1,1,1,1]
    food_consumption_percentage[40,40,40,40,40]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,15,19,26,32]
    crime_risk_base[1,17,20,30,30]
    prosperity[40,35,30,30,30]
    max_people[15,15,15,15,15]
    tax_multiplier[3,2,2,2,2]
    malaria_risk[-120,5,0,20,30]
    disease_risk[-120,3,0,10,30]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_modest_homestead {
  animations {
    _pack { pack: PACK_GENERAL }
    house { id: 29, offset:0 }
    minimap { id:148 }
  }
  building_size : 1
  can_merge : true
  variants {
    _0 { pack: PACK_GENERAL, id: 29, offset:0 }
    _1 { pack: PACK_GENERAL, id: 29, offset:1 }
    _2 { pack: PACK_CUSTOM_HOUSE, id: 0, offset:0 }
    _3 { pack: PACK_CUSTOM_HOUSE, id: 0, offset:1 }
    _4 { pack: PACK_CUSTOM_HOUSE, id: 0, offset:2 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 29, offset:4 }
  }

  desirability { value[-1], step[1], step_size[1], range[1] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[8,9,10,10,11]
    evolve_desirability[14,15,16,16,17]
    entertainment[12,13,13,15,20]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[1,1,1,1,1]
    food_consumption_percentage[42,42,42,42,42]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,14,17,23,29]
    crime_risk_base[1,15,17,25,25]
    prosperity[45,40,35,35,35]
    max_people[16,16,16,16,16]
    tax_multiplier[4,3,2,2,2]
    malaria_risk[-120,0,0,20,20]
    disease_risk[-120,0,0,10,20]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_spacious_homestead {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 29, offset:2}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 29, offset:2 }
    _2 { pack: PACK_GENERAL, id: 29, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 29, offset:5 }
  }

  desirability { value[-1], step[1], step_size[1], range[1] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[12,13,14,14,15]
    evolve_desirability[18,19,20,20,21]
    entertainment[14,15,16,20,25]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[1,1,1,1,1]
    food_types[1,1,1,1,1]
    food_consumption_percentage[44,44,44,44,44]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,13,17,23,29]
    crime_risk_base[1,15,17,25,25]
    prosperity[55,50,45,45,45]
    max_people[17,17,17,17,17]
    tax_multiplier[4,3,2,2,2]
    malaria_risk[-120,-10,0,0,20]
    disease_risk[-120,-10,0,0,10]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_modest_apartment {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 30}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 30, offset:0 }
    _2 { pack: PACK_GENERAL, id: 30, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 30, offset:4 }
  }

  desirability { value[0], step[0], step_size[0], range[0] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[5]

  model {
    devolve_desirability[16,17,18,18,19]
    evolve_desirability[22,23,25,25,26]
    entertainment[16,18,20,25,30]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[1,1,1,1,1]
    food_types[1,1,1,1,1]
    food_consumption_percentage[46,46,46,46,46]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,12,15,21,27]
    crime_risk_base[1,12,15,20,20]
    prosperity[60,55,50,50,50]
    max_people[18,18,18,18,18]
    tax_multiplier[4,3,3,3,2]
    malaria_risk[-120,-20,-10,0,10]
    disease_risk[-120,-20,-10,0,10]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_spacious_apartment {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 30, offset:2}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 30, offset:2 }
    _2 { pack: PACK_GENERAL, id: 30, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 30, offset:5}
  }

  desirability { value[0], step[0], step_size[0], range[0] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[5]

  model {
    devolve_desirability[19,20,22,22,23]
    evolve_desirability[29,30,32,32,33]
    entertainment[18,22,25,30,35]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[0,0,0,0,0]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[1,1,1,1,1]
    food_consumption_percentage[48,48,48,48,48]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,11,15,21,27]
    crime_risk_base[1,12,15,20,20]
    prosperity[70,60,55,55,55]
    max_people[19,19,19,19,19]
    tax_multiplier[4,3,3,3,2]
    malaria_risk[-120,-30,-20,0,10]
    disease_risk[-120,-30,-20,0,0]
    food_storage_multiplier[5,5,5,5,5]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_common_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 31}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 31, offset:0 }
    _2 { pack: PACK_GENERAL, id: 31, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 31, offset:4 }
  }

  desirability { value[0], step[0], step_size[0], range[0] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[26,27,29,29,30]
    evolve_desirability[37,38,40,40,41]
    entertainment[20,25,30,35,40]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[0,0,0,0,0]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[1,1,1,1,1]
    food_consumption_percentage[50,50,50,50,50]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,10,13,19,25]
    crime_risk_base[1,8,12,15,20]
    prosperity[80,70,60,60,60]
    max_people[80,80,80,80,80]
    tax_multiplier[5,4,3,3,3]
    malaria_risk[-120,-40,-30,-10,0]
    disease_risk[-120,-40,-30,-10,0]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_spacious_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 31, offset:2}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 31, offset:2 }
    _2 { pack: PACK_GENERAL, id: 31, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 31, offset:5 }
  }

  desirability { value[0], step[0], step_size[0], range[0] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[33,34,36,36,37]
    evolve_desirability[45,46,48,48,50]
    entertainment[25,30,35,40,45]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[2,2,2,2,2]
    food_consumption_percentage[52,52,52,52,52]
    pottery[1,1,1,1,1]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,9,13,19,25]
    crime_risk_base[1,8,12,15,20]
    prosperity[90,80,70,70,65]
    max_people[84,84,84,84,84]
    tax_multiplier[5,4,3,3,3]
    malaria_risk[-120,-50,-40,-20,0]
    disease_risk[-120,-50,-40,-20,0]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_elegant_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 32}
    minimap{id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 32, offset:0 }
    _2 { pack: PACK_GENERAL, id: 32, offset:1 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 32, offset:4 }
  }

  desirability { value[1], step[2], step_size[-1], range[2] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[3]
  damage_risk[5]

  model {
    devolve_desirability[40,41,43,43,45]
    evolve_desirability[50,51,53,53,55]
    entertainment[30,35,40,45,50]
    water[2,2,2,2,2]
    religion[1,1,1,1,1]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[2,2,2,2,2]
    food_consumption_percentage[54,54,54,54,54]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,8,11,17,23]
    crime_risk_base[1,5,8,10,15]
    prosperity[100,90,80,75,70]
    max_people[88,88,88,88,88]
    tax_multiplier[6,5,4,4,3]
    malaria_risk[-120,-60,-50,-30,-10]
    disease_risk[-120,-60,-50,-30,-10]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_fancy_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house {id: 32, offset:2}
    minimap {id:148}
  }
  building_size : 1
  can_merge : true
  variants {
    _1 { pack: PACK_GENERAL, id: 32, offset:2 }
    _2 { pack: PACK_GENERAL, id: 32, offset:3 }
  }

  variants_merged {
    _1 { pack: PACK_GENERAL, id: 32, offset:5 }
  }

  desirability { value[2], step[1], step_size[-1], range[2] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[3]
  damage_risk[5]

  model {
    devolve_desirability[45,46,48,48,50]
    evolve_desirability[55,56,58,58,60]
    entertainment[35,40,45,50,55]
    water[2,2,2,2,2]
    religion[2,2,2,2,2]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[2,2,2,2,2]
    food_consumption_percentage[56,56,56,56,56]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[0,0,0,0,0]
    beer[1,1,1,1,1]
    crime_risk[0,7,11,17,23]
    crime_risk_base[1,5,8,10,15]
    prosperity[120,100,90,80,75]
    max_people[92,92,92,92,92]
    tax_multiplier[6,5,4,4,4]
    malaria_risk[-120,-70,-60,-40,-20]
    disease_risk[-120,-70,-60,-40,-20]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }

  flags {
    is_house: true
  }
}

building_house_common_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 33}
    minimap{id:148}
  }
  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 33, offset:0 }
  }
  desirability { value[3], step[1], step_size[-1], range[3] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[47,48,50,50,52]
    evolve_desirability[60,61,63,63,65]
    entertainment[40,45,50,55,60]
    water[2,2,2,2,2]
    religion[2,2,2,2,2]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[1,1,1,1,1]
    food_types[2,2,2,2,2]
    food_consumption_percentage[58,58,58,58,58]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[1,1,1,1,1]
    beer[1,1,1,1,1]
    crime_risk[0,6,8,15,21]
    crime_risk_base[1,5,8,10,15]
    prosperity[650,600,500,450,450]
    max_people[100,100,100,100,100]
    tax_multiplier[13,12,10,10,11]
    malaria_risk[-120,-80,-70,-50,-30]
    disease_risk[-120,-80,-70,-50,-30]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}

building_house_spacious_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 33, offset:1}
    minimap{id:148}
  }
  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 33, offset:1 }
  }
  desirability { value[3], step[1], step_size[-1], range[3] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[50,51,53,53,55]
    evolve_desirability[64,66,68,68,70]
    entertainment[45,50,55,60,65]
    water[2,2,2,2,2]
    religion[2,2,2,2,2]
    education[1,1,1,1,1]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[2,2,2,2,2]
    food_types[2,2,2,2,2]
    food_consumption_percentage[60,60,60,60,60]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[1,1,1,1,1]
    beer[1,1,1,1,1]
    crime_risk[0,5,8,15,21]
    crime_risk_base[1,5,8,10,15]
    prosperity[750,700,600,600,550]
    max_people[108,108,108,108,108]
    tax_multiplier[14,13,11,10,11]
    malaria_risk[-120,-90,-80,-60,-40]
    disease_risk[-120,-90,-80,-60,-40]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}

building_house_elegant_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 34}
    minimap{id:148}
  }
  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 34, offset:0 }
  }

  desirability { value[4], step[2], step_size[-1], range[6] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[55,57,60,60,62]
    evolve_desirability[70,72,74,74,76]
    entertainment[50,55,60,65,70]
    water[2,2,2,2,2]
    religion[3,2,3,3,3]
    education[2,2,2,2,2]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[2,2,2,2,2]
    food_types[2,2,2,2,2]
    food_consumption_percentage[62,62,62,62,62]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[1,1,1,1,1]
    beer[1,1,1,1,1]
    crime_risk[0,4,8,13,19]
    crime_risk_base[1,1,5,5,10]
    prosperity[850,800,700,700,650]
    max_people[116,116,116,116,116]
    tax_multiplier[15,14,12,12,12]
    malaria_risk[-120,-100,-90,-70,-50]
    disease_risk[-120,-100,-90,-70,-50]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}

building_house_stately_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 34, offset:1}
    minimap{id:148}
  }
  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 34, offset:1 }
  }

  desirability { value[4], step[2], step_size[-1], range[6] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[64,66,68,68,70]
    evolve_desirability[75,77,80,80,82]
    entertainment[55,60,70,75,80]
    water[2,2,2,2,2]
    religion[3,3,3,3,3]
    education[2,2,2,2,2]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[2,2,2,2,2]
    food_types[2,2,2,2,2]
    food_consumption_percentage[64,64,64,64,64]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[1,1,1,1,1]
    beer[1,1,1,1,1]
    crime_risk[0,3,5,13,19]
    crime_risk_base[1,1,5,5,10]
    prosperity[950,900,800,800,750]
    max_people[124,124,124,124,124]
    tax_multiplier[16,15,13,12,12]
    malaria_risk[-120,-110,-100,-80,-60]
    disease_risk[-120,-110,-100,-80,-60]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}

building_house_modest_estate {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 35}
    minimap{id:148}
  }
  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 35, offset:0 }
  }

  desirability { value[5], step[2], step_size[-1], range[6] }
  labor_caegory : LABOR_CATEGORY_HOUSE
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[65,67,70,70,72]
    evolve_desirability[85,87,90,90,92]
    entertainment[65,72,80,85,90]
    water[2,2,2,2,2]
    religion[3,3,3,3,3]
    education[2,2,2,2,2]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[2,2,2,2,2]
    food_types[2,2,2,2,2]
    food_consumption_percentage[66,66,66,66,66]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[2,2,2,2,2]
    beer[1,1,1,1,1]
    crime_risk[0,2,4,12,18]
    crime_risk_base[1,1,5,5,10]
    prosperity[2000,1900,1600,1600,1500]
    max_people[184,184,184,184,184]
    tax_multiplier[17,16,15,15,15]
    malaria_risk[-120,-120,-110,-90,-70]
    disease_risk[-120,-120,-110,-90,-70]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}

building_house_palatial_estate {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 35, offset:1}
    minimap{id: 148}
  }

  building_size : 1
  can_merge : false
  variants {
    _1 { pack: PACK_GENERAL, id: 35, offset:1 }
  }

  desirability { value[5], step[2], step_size[-1], range[6] }
  labor_category : LABOR_CATEGORY_HOUSE
  fire_risk[1]
  damage_risk[7]

  model {
    devolve_desirability[80,82,85,85,87]
    evolve_desirability[100,100,100,100,100]
    entertainment[75,83,90,95,100]
    water[2,2,2,2,2]
    religion[3,3,3,3,3]
    education[2,2,2,2,2]
    food[1,1,1,1,1]
    dentist[1,1,1,1,1]
    physician[1,1,1,1,1]
    health[2,2,2,2,2]
    food_types[2,3,3,3,3]
    food_consumption_percentage[68,68,68,68,68]
    pottery[1,1,1,1,1]
    linen[1,1,1,1,1]
    jewelry[2,2,2,2,2]
    beer[1,1,1,1,1]
    crime_risk[0,1,3,10,15]
    crime_risk_base[1,1,5,5,10]
    prosperity[2300,2200,1900,1900,1800]
    max_people[200,200,200,200,200]
    tax_multiplier[18,17,16,16,15]
    malaria_risk[-120,-120,-120,-100,-80]
    disease_risk[-120,-120,-120,-100,-80]
    food_storage_multiplier[6,6,6,6,6]
    devolve_delay[2,2,2,2,2]
    entertainment_juggler_divider[50,50,50,50,50]
    entertainment_musician_divider[40,40,40,40,40]
    entertainment_dancer_divider[30,30,30,30,30]
    entertainment_senet_divider[25,25,25,25,25]
    unreachable_ticks_devolve_threshold[2,2,2,2,2]
    unreachable_ticks_block_evolve_threshold[0,0,0,0,0]
    days_without_food_devolve_threshold[3,3,3,3,3]
  }
  flags {
    is_house: true
  }
}