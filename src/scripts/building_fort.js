log_info("akhenaten: building fort started")

base_fort_ghost {
    main_view_offset [[-55, 20], [-55, -35], [-55, -35], [-60, -40]]
    ground_view_offset [[35, 65], [5, -70], [-200, -55], [-180, 46]]
    ground_check_offset [[3, -1], [4, -1], [4, 0], [3,  0]
                            [-1,-4], [0, -4], [0,-3], [-1,-3]
                            [-4, 0], [-3, 0], [-3,1], [-4, 1]
                            [0,  3], [1,  3], [1, 4], [0,  4]] 
}
  
building_fort_charioteers {
    animations {
        _pack {pack: PACK_GENERAL}
        base {id: 66}
        ground {id: 66, offset:1}
        picture {id: 66, offset:3, pos[93, -21]}
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta { help_id:87, text_id:89 }
    cost [ 500, 700, 900, 1300, 2000 ]
    desirability { value[-20], step[2], step_size[2], range[6] }
    flags {
        is_fort: true
        is_military: true
    }
}
  
building_fort_infantry {
    animations {
        _pack { pack: PACK_GENERAL }
        base { id: 66}
        ground { id: 66, offset:1}
        picture { id: 66, offset:4, pos:[93, -21]}
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta { help_id:87, text_id:89 }
    cost [ 200, 300, 500, 800, 1200 ]
    desirability { value[-20], step[2], step_size[2], range [6] }
    flags {
        is_fort: true
        is_military: true
    }
}

building_fort_archers = {
    animations : {
        base: {pack: PACK_GENERAL, id: 66},
        ground: {pack: PACK_GENERAL, id: 66, offset:1},
        picture: {pack: PACK_GENERAL, id: 66, offset:2, pos:[93, -21]},
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta : { help_id:87, text_id:89 }
    cost : [ 200, 300, 500, 800, 1200 ]
    desirability : { value:[-20], step:[2], step_size:[2], range: [6] }
    flags {
        is_fort: true
        is_military: true
    }
}

building_fort_ground = {
    labor_category : LABOR_CATEGORY_MILITARY,
    building_size : 4,
    fire_proof : 1,
    damage_proof : 1,
    desirability : { value:[-20], step:[2], step_size:[2], range: [6] }
    fire_risk:[0], damage_risk: [0]
    flags {
        is_fort: true
        is_military: true
    }
}