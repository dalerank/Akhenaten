log_info("akhenaten: load houses started")

building_house_crude_hut {
  animations {
    _pack { pack: PACK_GENERAL }
    preview{ id: 36 }
    base{ id: 36 }
    house{ id: 26 }
    minimap{ id:148 }
  }

  building_size : 1
  num_types : 2
  planner_update_rule {
    is_draggable : true
  }
  desirability { value[-2], step[1], step_size[1], range: [3] }
  
  fire_risk[3]
  damage_risk: [0]
  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_sturdy_hut {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 26, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range[3] }
  
  fire_risk[3]
  damage_risk[0]
  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_meager_shanty {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 27}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range[2] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_common_shanty {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 27, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range[2] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_rough_cottage {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 28}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  
  fire_risk[5]
  damage_risk[3]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_ordinary_cottage {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 28, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  
  fire_risk[5]
  damage_risk[3]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_modest_homestead {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 29, offset:0}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-1], step[1], step_size[1], range: [1] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_spacious_homestead {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 29, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-1], step[1], step_size[1], range: [1] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_modest_apartment {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 30}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  
  fire_risk[4]
  damage_risk[5]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_spacious_apartment {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 30, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  fire_risk[4]
  damage_risk[5]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_common_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 31}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_spacious_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 31, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  
  fire_risk[4]
  damage_risk[4]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_elegant_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 32}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[1], step[2], step_size[-1], range: [2] }
  
  fire_risk[3]
  damage_risk[5]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_fancy_residence {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 32, offset:2}
    minimap{id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[2], step[1], step_size[-1], range: [2] }
  
  fire_risk[3]
  damage_risk[5]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_common_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 33}
    minimap{id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[3], step[1], step_size[-1], range: [3] }
  
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_spacious_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 33, offset:1}
    minimap{id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[3], step[1], step_size[-1], range: [3] }
  
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_elegant_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 34}
    minimap{id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[4], step[2], step_size[-1], range: [6] }
  
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_stately_manor {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 34, offset:1}
    minimap{id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[4], step[2], step_size[-1], range: [6] }
  
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_modest_estate {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 35}
    minimap{id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[5], step[2], step_size[-1], range: [6] }
  
  fire_risk[2]
  damage_risk[6]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}

building_house_palatial_estate {
  animations {
    _pack { pack: PACK_GENERAL }
    house{id: 35, offset:1}
    minimap{id: 148}
  }

  building_size : 1
  num_types : 1
  desirability { value[5], step[2], step_size[-1], range: [6] }
  
  fire_risk[1]
  damage_risk[7]

  model {
    devolve_desirability[-99,-12,-7,-2,2]
    evolve_desirability[-10,-6,0,4,9]
    entertainment[0,0,0,0,0]
    water[0,1,1,1,2]
    religion[0,0,0,1,1]
    education[0,0,0,0,0]
    food[0,0,1,1,1]
    dentist[0,0,0,0,0]
    physician[0,0,0,0,0]
    health[0,0,0,0,0]
    food_types[0,0,1,1,1]
    pottery[0,0,0,0,0]
    linen[0,0,0,0,0]
    jewelry[0,0,0,0,0]
    beer[0,0,0,0,0]
    crime_risk[0,19,24,28,32]
    crime_risk_base[1,22,22,30,30]
    prosperity[15,15,15,20,25]
    max_people[5,7,9,11,13]
    tax_multiplier[2,1,1,1,1]
    malaria_risk[-120,30,40,50,30]
    disease_risk[-120,20,20,30,40]
  }
}