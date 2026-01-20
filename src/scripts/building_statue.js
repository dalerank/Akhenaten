log_info("akhenaten: building statue started")

building_small_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 61, offset:1}
      {pack: PACK_GENERAL, id: 61, offset:5}
      {pack: PACK_EXPANSION, id: 37, offset:1}
      {pack: PACK_EXPANSION, id: 37, offset:5}
      {pack: PACK_TEMPLE_RA, id: 1, offset:27}
    ]
    meta : {
      help_id:79
      text_id:80
    }
    building_size : 1
    cost : [ 3, 5, 8, 13, 21 ]
    desirability : { value:[3], step:[1], step_size:[-1], range: [3] }
  }
  
  building_medium_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 8, offset:1},
      {pack: PACK_GENERAL, id: 8, offset:5},
      {pack: PACK_EXPANSION, id: 36, offset:1},
      {pack: PACK_EXPANSION, id: 36, offset:5},
    ]
    meta : {
      help_id:79
      text_id:80
    }
    building_size : 2
    cost : [ 12, 18, 24, 30, 50 ]
    desirability : { value:[10], step:[1], step_size:[-2], range: [4] }
  }
  
  building_large_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 7, offset:1},
      {pack: PACK_GENERAL, id: 7, offset:5},
      {pack: PACK_EXPANSION, id: 35, offset:1},
      {pack: PACK_EXPANSION, id: 35, offset:5},
    ]
    meta : {
      help_id:79
      text_id:80
    }
    building_size : 3
    cost : [ 30, 45, 60, 90, 150 ]
    desirability : { value:[14], step:[2], step_size:[-2], range: [5] }
  }