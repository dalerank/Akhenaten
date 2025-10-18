log_info("akhenaten: load houses started")

building_house_crude_hut {
  animations {
    preview{pack: PACK_GENERAL, id: 36}
    base{pack: PACK_GENERAL, id: 36}
    house{pack: PACK_GENERAL, id: 26}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  planner_update_rule {
    is_draggable : true
  }
  desirability { value[-2], step[1], step_size[1], range: [3] }
  laborers[0], fire_risk[3], damage_risk: [0]
}

building_house_sturdy_hut {
  animations {
    house{pack: PACK_GENERAL, id: 26, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [3] }
  laborers[0], fire_risk[3], damage_risk: [0]
}

building_house_meager_shanty {
  animations {
    house{pack: PACK_GENERAL, id: 27, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_common_shanty {
  animations {
    house{pack: PACK_GENERAL, id: 27, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_rough_cottage {
  animations {
    house{pack: PACK_GENERAL, id: 28, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  laborers[0], fire_risk[5], damage_risk: [3]
}

building_house_ordinary_cottage {
  animations {
    house{pack: PACK_GENERAL, id: 28, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-2], step[1], step_size[1], range: [2] }
  laborers[0], fire_risk[5], damage_risk: [3]
}

building_house_modest_homestead {
  animations {
    house{pack: PACK_GENERAL, id: 29, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-1], step[1], step_size[1], range: [1] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_spacious_homestead {
  animations {
    house{pack: PACK_GENERAL, id: 29, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[-1], step[1], step_size[1], range: [1] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_modest_apartment {
  animations {
    house{pack: PACK_GENERAL, id: 30, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  laborers[0], fire_risk[4], damage_risk: [5]
}

building_house_spacious_apartment {
  animations {
    house{pack: PACK_GENERAL, id: 30, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  laborers[0], fire_risk[4], damage_risk: [5]
}

building_house_common_residence {
  animations {
    house{pack: PACK_GENERAL, id: 31, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_spacious_residence {
  animations {
    house{pack: PACK_GENERAL, id: 31, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[0], step[0], step_size[0], range: [0] }
  laborers[0], fire_risk[4], damage_risk: [4]
}

building_house_elegant_residence {
  animations {
    house{pack: PACK_GENERAL, id: 32, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[1], step[2], step_size[-1], range: [2] }
  laborers[0], fire_risk[3], damage_risk: [5]
}

building_house_fancy_residence {
  animations {
    house{pack: PACK_GENERAL, id: 32, offset:2}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 2
  desirability { value[2], step[1], step_size[-1], range: [2] }
  laborers[0], fire_risk[3], damage_risk: [5]
}

building_house_common_manor {
  animations {
    house{pack: PACK_GENERAL, id: 33, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[3], step[1], step_size[-1], range: [3] }
  laborers[0], fire_risk[2], damage_risk: [6]
}

building_house_spacious_manor {
  animations {
    house{pack: PACK_GENERAL, id: 33, offset:1}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[3], step[1], step_size[-1], range: [3] }
  laborers[0], fire_risk[2], damage_risk: [6]
}

building_house_elegant_manor {
  animations {
    house{pack: PACK_GENERAL, id: 34, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[4], step[2], step_size[-1], range: [6] }
  laborers[0], fire_risk[2], damage_risk: [6]
}

building_house_stately_manor {
  animations {
    house{pack: PACK_GENERAL, id: 34, offset:1}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[4], step[2], step_size[-1], range: [6] }
  laborers[0], fire_risk[2], damage_risk: [6]
}

building_house_modest_estate {
  animations {
    house{pack: PACK_GENERAL, id: 35, offset:0}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[5], step[2], step_size[-1], range: [6] }
  laborers[0], fire_risk[2], damage_risk: [6]
}

building_house_palatial_estate {
  animations {
    house{pack: PACK_GENERAL, id: 35, offset:1}
    minimap{pack: PACK_GENERAL, id:148}
  }
  building_size : 1
  num_types : 1
  desirability { value[5], step[2], step_size[-1], range: [6] }
  laborers[0], fire_risk[1], damage_risk: [7]
}