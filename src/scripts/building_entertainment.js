log_info("akhenaten: building entertainment started")

building_juggler_school {
    animations {
      _pack { pack: PACK_GENERAL }
      preview { id:46 }
      base { id:46 }
      work { pos : [33, -38], id:46, offset:1, max_frames:14, duration:3 }
    }
  
    spawn_delay_100_percent : 7   // ~4 жонглера в месяц
    spawn_delay_75_percent : 15   // 2 жонглера в месяц
    spawn_delay_50_percent : 30   // 1 жонглер в месяц
    spawn_delay_25_percent : 60   // 1 жонглер за 2 месяца
    spawn_delay_default : 90      // 1 жонглер за 3 месяца (для 1-24% работников)
    meta { text_id:77, help_link:"message_building_booth" }
  
    building_size : 2
    min_houses_coverage : 50
    cost [ 10, 20, 50, 100, 200 ]
    desirability { value[-3], step[1], step_size[1], range[3] }
    laborers[5]
    fire_risk[4]
    damage_risk[2]
    flags {
      is_entertainment: true
    }
  }

  building_dancer_school {
    animations {
      _pack { pack: PACK_GENERAL }
      preview { id:52 }
      base { id:52 }
      work { pos[104, 0], pack:PACK_SPR_AMBIENT, id:6, offset:0, max_frames:35, duration:2, internal_offset:true }
    }
  
    overlay : OVERLAY_ENTERTAINMENT
    min_houses_coverage : 50
    building_size : 4
    meta { help_id:75, text_id:76 }
    cost [ 30, 50, 100, 150, 200 ]
    desirability { value[-3], step[1], step_size[1], range[3] }
    laborers[10]
    fire_risk[4]
    damage_risk[2]
    flags {
      is_entertainment: true
    }
  }

  building_pavilion = {
    animations : {
      base : { pos:[0, 0], pack:PACK_GENERAL, id:48 },
      square : { pos:[0, 0], pack:PACK_GENERAL, id:50 },
      stand_sn_s : { pack:PACK_GENERAL, id:92, offset:0},
      stand_sn_n : { pack:PACK_GENERAL, id:92, offset:1},
      stand_sn_e : { pack:PACK_GENERAL, id:92, offset:2},
      juggler : { pos : [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
      dancer : { pos : [65, 0], pack:PACK_SPR_AMBIENT, id:6, offset:0, max_frames:35 },
      musician_sn : { pos : [50, 0], pack:PACK_SPR_AMBIENT, id:9, max_frames : 11 },
      musician_we : { pos : [48, 4], pack:PACK_SPR_AMBIENT, id:10, max_frames : 11 },
      booth : { pos:[0, 0], pack:PACK_GENERAL, id:114 },
    },
    preview_dir_0 : { stand:[-30, 15], stand_b:[90, 45], stand_e:[60, 60], booth:[-60, 30] },
    preview_dir_1 : { stand:[30, 45], stand_b:[0, 0], stand_e:[-30, 15], booth:[30, 75] },
    preview_dir_2 : { stand:[0, 30], stand_b:[0, 90], stand_e:[-30, 75], booth:[90, 45], stand_b_img:2, stand_e_img:2 },
    preview_dir_3 : { stand:[-60, 60], stand_b:[90, 45], stand_e:[60, 30], booth:[0, 90], stand_b_img:2, stand_e_img:2 },
    preview_dir_4 : { stand:[0, 60], stand_b:[-60, 30], stand_e:[-90, 45], booth:[0, 90] },
    preview_dir_5 : { stand:[-60, 30], stand_b:[30, 75], stand_e:[0, 90], booth:[-90, 45] },
    preview_dir_6 : { stand:[-90, 45], stand_b:[30, 15], stand_e:[0, 0], booth:[-30, 75], stand_b_img : 2, stand_e_img : 2 },
    preview_dir_7 : { stand:[-30, 15], stand_b:[-60, 60], stand_e:[-90, 45], booth:[60, 30], stand_b_img : 2, stand_e_img : 2 },
  
    place_dir_0 : [
      {type: BUILDING_GARDENS, offset:[1, 2]},
      {type: BUILDING_GARDENS, offset:[3, 2]},
      {type: BUILDING_PAVILLION, offset:[0, 0]},
      {type: BUILDING_BANDSTAND, offset:[3, 0], main:true},
      {type: BUILDING_BANDSTAND, offset:[3, 1], main:false},
      {type: BUILDING_BOOTH, offset:[0, 2], main:false}
    ],
  
    place_dir_1 : [
      {type: BUILDING_GARDENS, offset:[2, 2]},
      {type: BUILDING_GARDENS, offset:[0, 2]},
      {type: BUILDING_PAVILLION, offset:[2, 0]},
      {type: BUILDING_BANDSTAND, offset:[0, 0], main:true},
      {type: BUILDING_BANDSTAND, offset:[0, 1], main:false},
      {type: BUILDING_BOOTH, offset:[3, 2], main:false}
    ],
  
    place_dir_2 : [
      {type: BUILDING_GARDENS, offset:[3, 0]},
      {type: BUILDING_GARDENS, offset:[3, 3]},
      {type: BUILDING_PAVILLION, offset:[1, 0]},
      {type: BUILDING_BANDSTAND, offset:[1, 3], main:true},
      {type: BUILDING_BANDSTAND, offset:[2, 3], main:false},
      {type: BUILDING_BOOTH, offset:[3, 1], main:false}
    ],
  
    place_dir_3 : [
      {type: BUILDING_GARDENS, offset:[3, 3]},
      {type: BUILDING_GARDENS, offset:[1, 0]},
      {type: BUILDING_PAVILLION, offset:[1, 2]},
      {type: BUILDING_BANDSTAND, offset:[2, 0], main:true},
      {type: BUILDING_BANDSTAND, offset:[3, 0], main:false},
      {type: BUILDING_BOOTH, offset:[3, 2], main:false}
    ],
  
    place_dir_4 : [
      {type: BUILDING_GARDENS, offset:[3, 3]},
      {type: BUILDING_GARDENS, offset:[0, 3]},
      {type: BUILDING_PAVILLION, offset:[2, 1]},
      {type: BUILDING_BANDSTAND, offset:[0, 1], main:true},
      {type: BUILDING_BANDSTAND, offset:[0, 2], main:false},
      {type: BUILDING_BOOTH, offset:[2, 3], main:false}
    ],
  
    place_dir_5 : [
      {type: BUILDING_GARDENS, offset:[1, 3]},
      {type: BUILDING_GARDENS, offset:[3, 3]},
      {type: BUILDING_PAVILLION, offset:[0, 1]},
      {type: BUILDING_BANDSTAND, offset:[3, 1], main:true},
      {type: BUILDING_BANDSTAND, offset:[3, 2], main:false},
      {type: BUILDING_BOOTH, offset:[0, 3], main:false}
    ],
  
    place_dir_6 : [
      {type: BUILDING_GARDENS, offset:[2, 0]},
      {type: BUILDING_GARDENS, offset:[2, 2]},
      {type: BUILDING_PAVILLION, offset:[0, 2]},
      {type: BUILDING_BANDSTAND, offset:[0, 0], main:false},
      {type: BUILDING_BANDSTAND, offset:[1, 0], main:true},
      {type: BUILDING_BOOTH, offset:[2, 3], main:false}
    ],
  
    place_dir_7 : [
      {type: BUILDING_GARDENS, offset:[0, 3]},
      {type: BUILDING_GARDENS, offset:[2, 1]},
      {type: BUILDING_PAVILLION, offset:[0, 0]},
      {type: BUILDING_BANDSTAND, offset:[1, 3], main:false},
      {type: BUILDING_BANDSTAND, offset:[2, 3], main:true},
      {type: BUILDING_BOOTH, offset:[2, 0], main:false}
    ]
  
    min_houses_coverage : 100
    meta { help_id: 73, text_id: 74 }
    building_size : 4
    cost [ 100, 200, 300, 500, 800 ]
    desirability { value[6], step[1], step_size[-1], range[6] }
    laborers [20]
    fire_risk [4]
    damage_risk [4]

    flags {
      is_entertainment: true
    }
  }

  building_bandstand {
    animations {
      _pack { pack: PACK_GENERAL }
      booth { id:114 }
      square { id:58}
      stand_sn_s { id:92, offset:0 }
      stand_sn_n { id:92, offset:1 }
      stand_we_w { id:92, offset:2 }
      stand_we_e { id:92, offset:3 }
  
      juggler { pos[35, 15], pack:PACK_SPR_AMBIENT, id:7, max_frames:26, duration:2, internal_offset:true }
      musician_sn { pos[-10, -36], pack:PACK_SPR_AMBIENT, id:10, max_frames : 11, duration:3 }
      musician_we { pos[30, 10], pack:PACK_SPR_AMBIENT, id:9, max_frames : 11, duration:3, internal_offset:true }
    }
  
    overlay : OVERLAY_BANDSTAND
    labor_category : LABOR_CATEGORY_ENTERTAINMENT
    min_houses_coverage : 100
    fire_proof: true
    meta { help_id:72, text_id:71 }
    building_size : 3
    cost [ 30, 50, 100, 150, 200 ]
    desirability { value[4], step[1], step_size[-1], range[4] }
    laborers[12], fire_risk[4], damage_risk[3]
    flags {
      is_entertainment: true
    }
  }

  building_booth {
    animations {
      booth { pack:PACK_GENERAL, id:114 },
      square { pack:PACK_GENERAL, id:112 },
      juggler { pos [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
    }
  
    min_houses_coverage : 100
    labor_category : LABOR_CATEGORY_ENTERTAINMENT
    meta { help_id:71, text_id:72 }
    building_size : 2
    cost [ 10, 20, 40, 80, 150 ]
    desirability { value[2], step[1], step_size[-1], range[2] }
  
    laborers[8]
    fire_risk[4]
    damage_risk[2]
    flags {
      is_entertainment: true
    }
  }

  building_senet_house = {
    animations : {
      preview : { pack:PACK_GENERAL, id:17 },
      base : { pack:PACK_GENERAL, id:17 },
      work : { pos:[30, -35], pack:PACK_GENERAL, id:17, offset:1, max_frames:18, duration:5 },
    }
    input : {
      resource : RESOURCE_BEER
    }
    meta : { help_id:74, text_id:73 }
    building_size : 4
    labor_category : LABOR_CATEGORY_ENTERTAINMENT
    cost : [ 300, 400, 500, 700, 1000 ]
    desirability : { value:[-6], step:[1], step_size:[2], range: [3] }
    crime : { value:[5], step:[1], step_size:[1], range: [3] }
    laborers:[25], fire_risk:[1], damage_risk: [1]
    flags {
      is_entertainment: true
    }
  }

  building_bullfight_school = {
    animations : {
      preview : { pack:PACK_CUSTOM, id:0 },
      base : { pack:PACK_CUSTOM, id:0 },
    }
    meta : { help_id:75, text_id:78 }
    building_size : 2
    cost: [ 50, 80, 100, 150, 200 ]
    desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
    laborers:[15], fire_risk:[4], damage_risk: [3]
    flags {
      is_entertainment: true
    }
  }

  building_zoo {
    animations {
      preview : { pos : [30, 28], pack:PACK_GENERAL, id:49 },
      base : { pos : [30, 28], pack:PACK_GENERAL, id:49 },
      work : { pos : [25, -12], pack:PACK_GENERAL, id:49, offset:1, max_frames:19, can_reverse:true, duration:3 },
    }
    meta : { help_id:75, text_id:79 }
    building_size : 3
    cost : [ 100, 200, 300, 500, 800 ]
    desirability : { value:[-6], step:[1], step_size:[1], range: [3] }
    laborers:[20], fire_risk:[4], damage_risk: [3]
    flags {
      is_entertainment: true
    }
  }