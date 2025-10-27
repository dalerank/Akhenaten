log_info("akhenaten: enemies info started")

enemy_attack_rules = {
    priority : {
        food_chain : [BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_BAZAAR,
                      BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_GRAIN_FARM,
                      BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM]

        gold_stores: [BUILDING_TOWN_PALACE,  BUILDING_VILLAGE_PALACE,
                      BUILDING_TAX_COLLECTOR_UPGRADED, BUILDING_TAX_COLLECTOR]

        best_buildings : [BUILDING_DYNASTY_MANSION,        BUILDING_FAMILY_MANSION,           BUILDING_PERSONAL_MANSION,         BUILDING_HOUSE_PALATIAL_ESTATE,
                          BUILDING_HOUSE_MODEST_ESTATE,    BUILDING_HOUSE_STATELY_MANOR,      BUILDING_HOUSE_ELEGANT_MANOR,      BUILDING_HOUSE_SPACIOUS_MANOR,
                          BUILDING_HOUSE_COMMON_MANOR,     BUILDING_HOUSE_FANCY_RESIDENCE,    BUILDING_HOUSE_ELEGANT_RESIDENCE,  BUILDING_HOUSE_SPACIOUS_RESIDENCE,
                          BUILDING_HOUSE_COMMON_RESIDENCE, BUILDING_HOUSE_SPACIOUS_APARTMENT, BUILDING_HOUSE_MODEST_APARTMENT,   BUILDING_HOUSE_SPACIOUS_HOMESTEAD,
                          BUILDING_HOUSE_MODEST_HOMESTEAD, BUILDING_HOUSE_ORDINARY_COTTAGE,   BUILDING_HOUSE_ROUGH_COTTAGE,      BUILDING_HOUSE_COMMON_SHANTY,
                          BUILDING_HOUSE_MEAGER_SHANTY,    BUILDING_HOUSE_STURDY_HUT,         BUILDING_HOUSE_CRUDE_HUT]

        troops: [BUILDING_MILITARY_ACADEMY, BUILDING_POLICE_STATION]

        simple: [BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS,
                 BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_GROUND, BUILDING_MILITARY_ACADEMY
                 BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP,

                 BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_WATER_LIFT,
                 BUILDING_WELL, BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE,
                 BUILDING_CITY_PALACE, BUILDING_ARCHITECT_POST,

                 BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
                 BUILDING_STONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_LIMESTONE_QUARRY,
                 BUILDING_CLAY_PIT, BUILDING_WOOD_CUTTERS, BUILDING_DOCK, BUILDING_SHIPWRIGHT,

                 BUILDING_BARLEY_FARM, BUILDING_GRAIN_FARM, BUILDING_FLAX_FARM,
                 BUILDING_BREWERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_POTTERY_WORKSHOP,
                 BUILDING_BRICKS_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_JEWELS_WORKSHOP,

                 BUILDING_BAZAAR, BUILDING_TAX_COLLECTOR, BUILDING_FIREHOUSE,
                 BUILDING_POLICE_STATION, BUILDING_FERRY, BUILDING_LOW_BRIDGE,
                 BUILDING_COURTHOUSE,

                 BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA,
                 BUILDING_ORACLE, BUILDING_FESTIVAL_SQUARE,

                 BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_SCRIBAL_SCHOOL,
                 BUILDING_LIBRARY, BUILDING_BANDSTAND, BUILDING_GARDENS
                ]
    }
}

// barbarian
figure_barbarian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_BARBARIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_BARBARIAN, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_BARBARIAN, id:2, max_frames:12, loop: false }
        big_image : { pack:PACK_UNLOADED, id:25, offset:55 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 3
    missile_attack_value : 6
    missile_delay : 50  
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_barbarian_sword = {
    animations : {
        walk : { pack:PACK_ENEMY_BARBARIAN, id:3, max_frames:12 }
        death : { pack:PACK_ENEMY_BARBARIAN, id:4, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_BARBARIAN, id:5, max_frames:8, duration:3 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:54 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 4
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 25
    is_enemy : true
    max_amount : 25
}

enemy_barbarian = {
    type : ENEMY_0_BARBARIAN 
    percentage_type1 : 80
    percentage_type2 : 20 
    percentage_type3 : 0
    figure_types : [FIGURE_ENEMY_BARBARIAN_SWORD, FIGURE_ENEMY_BARBARIAN_ARCHER, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

// assyrian
figure_assyrian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_ASSYRIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_ASSYRIAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_ASSYRIAN, id:3, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:54 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 2
    missile_attack_value : 6
    missile_delay : 50  
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_assyrian_sword = {
    animations : {
        walk : { pack:PACK_ENEMY_ASSYRIAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_ASSYRIAN, id:6, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:55 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 3
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_assyrian_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_ASSYRIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_ASSYRIAN, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_assyrian_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_ASSYRIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_ASSYRIAN, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_assyrian_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_ASSYRIAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_ASSYRIAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_ASSYRIAN, id:15, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 4
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_assyrian = {
    type : ENEMY_1_ASSYRIAN
    percentage_type1 : 40
    percentage_type2 : 50
    percentage_type3 : 10
    figure_types : [FIGURE_ENEMY_ASSYRIAN_ARCHER, FIGURE_ENEMY_ASSYRIAN_SWORD, FIGURE_ENEMY_ASSYRIAN_CHARIOT]
    layout : FORMATION_ENEMY_MOB
}

// canaanite
figure_canaanite_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_CANAANITE, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_CANAANITE, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_CANAANITE, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_CANAANITE, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 2
    missile_attack_value : 6
    missile_delay : 50 
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_canaanite_sword = {
    animations : {
        walk : { pack:PACK_ENEMY_CANAANITE, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_CANAANITE, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_CANAANITE, id:6, max_frames:10 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 4
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_canaanite_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_CANAANITE, id:0, max_frames:4 }
        death : { pack:PACK_ENEMY_CANAANITE, id:1, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_CANAANITE, id:2, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_canaanite_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_CANAANITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_CANAANITE, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_CANAANITE, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_canaanite_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_CANAANITE, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_CANAANITE, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_CANAANITE, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_CANAANITE, id:16, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 1
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_canaanite = {
    type : ENEMY_2_CANAANITE
    percentage_type1 : 50
    percentage_type2 : 40
    percentage_type3 : 10
    figure_types : [FIGURE_ENEMY_CANAANITE_ARCHER, FIGURE_ENEMY_CANAANITE_SWORD, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

// egyptian
figure_egyptian_galera = {
    animations : {
        swim : { pack:PACK_ENEMY_EGYPTIAN, id:0, max_frames:4 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:1, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_EGYPTIAN, id:2, max_frames:1 }
        idle_ready : { pack:PACK_ENEMY_EGYPTIAN, id:3, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_egyptian_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_EGYPTIAN, id:4, max_frames:4 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:5, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_EGYPTIAN, id:6, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_egyptian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:7, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:8, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_EGYPTIAN, id:9, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_EGYPTIAN, id:10, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 2
    missile_attack_value : 6
    missile_defense_value : 0
    missile_delay : 50 
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_egyptian_spearman = {
    animations : {
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 3
    missile_attack_value : 6
    missile_delay : 50 
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    is_enemy : true
    max_amount : 25
}

figure_egyptian_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:15, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 4
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_egyptian = {
    type : ENEMY_3_EGYPTIAN
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_EGYPTIAN_ARCHER, FIGURE_ENEMY_EGYPTIAN_SPEAR, FIGURE_ENEMY_EGYPTIAN_CHARIOT]
    layout: FORMATION_ENEMY_MOB
}

// hittite
figure_hittite_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_HITTITE, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_HITTITE, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_HITTITE, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_HITTITE, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_hittite_spearman = {
    animations : {
        walk : { pack:PACK_ENEMY_HITTITE, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_HITTITE, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_HITTITE, id:6, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }
    terrain_usage : TERRAIN_USAGE_ANY
    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 3
    missile_defense_value : 0
    missile_type : FIGURE_SPEAR
    is_enemy : true
    max_amount : 25
}

figure_hittite_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_hittite_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_hittite_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_HITTITE, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_HITTITE, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_HITTITE, id:15, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 1
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_hittite = {
    type : ENEMY_4_HITTITE
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_HITTITE_ARCHER, FIGURE_ENEMY_HITTITE_SPEARMAN, FIGURE_ENEMY_HITTITE_CHARIOT]
    layout: FORMATION_ENEMY_MOB
}

// hyksos
figure_hyksos_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_HYKSOS, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_HYKSOS, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_HYKSOS, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_HYKSOS, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 1
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_hyksos_sword = {
    animations : {
        walk : { pack:PACK_ENEMY_HYKSOS, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_HYKSOS, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_HYKSOS, id:6, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 2
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_hyksos_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_HYKSOS, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HYKSOS, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_HYKSOS, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_hyksos_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_HYKSOS, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_HYKSOS, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_HYKSOS, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_hyksos_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_HYKSOS, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_HYKSOS, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_HYKSOS, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_HYKSOS, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_hyksos = {
    type : ENEMY_5_HYKSOS
    percentage_type1 : 50
    percentage_type2 : 40
    percentage_type3 : 10
    figure_types: [FIGURE_ENEMY_HYKSOS_ARCHER, FIGURE_ENEMY_HYKSOS_SWORDMAN, FIGURE_ENEMY_HYKSOS_CHARIOT]
    layout : FORMATION_COLUMN
}

// kushite
figure_kushite_spearman = {
    animations : {
        walk : { pack:PACK_ENEMY_KUSHITE, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_KUSHITE, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_KUSHITE, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_KUSHITE, id:2, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 4
    missile_attack_value : 6
    missile_delay : 50 
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    is_enemy : true
    max_amount : 25
}

figure_kushite_axeman = {
    animations : {
        walk : { pack:PACK_ENEMY_KUSHITE, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_KUSHITE, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_KUSHITE, id:6, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_kushite_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_KUSHITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_KUSHITE, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_KUSHITE, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_kushite_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_KUSHITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_KUSHITE, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_KUSHITE, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_kushite_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_KUSHITE, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_KUSHITE, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_KUSHITE, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_KUSHITE, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 1
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_kushite = {
    type : ENEMY_6_KUSHITE
    percentage_type1 : 50
    percentage_type2 : 30
    percentage_type3 : 20
    figure_types: [FIGURE_ENEMY_KUSHITE_SPEARMAN, FIGURE_ENEMY_KUSHITE_AXEMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

// libian
figure_libian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_LIBIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_LIBIAN, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_LIBIAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_LIBIAN, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_libian_sword = {
    animations : {
        walk : { pack:PACK_ENEMY_LIBIAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_LIBIAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_LIBIAN, id:6, max_frames:10 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_libian_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_LIBIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_LIBIAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_LIBIAN, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_libian_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_LIBIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_LIBIAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_LIBIAN, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_libian_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_LIBIAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_LIBIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_LIBIAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_LIBIAN, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 4
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_libian = {
    type : ENEMY_7_LIBIAN
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    army_title [37, 33]
    figure_types: [FIGURE_ENEMY_LIBIAN_ARCHER, FIGURE_ENEMY_LIBIAN_SWORDMAN, FIGURE_NONE]
    layout : FORMATION_ENEMY_DOUBLE_LINE
}

// nubian
figure_nubian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_NUBIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_NUBIAN, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_NUBIAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_NUBIAN, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    defense_value: 1
    missile_delay : 50 
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_nubian_axeman = {
    animations : {
        walk : { pack:PACK_ENEMY_NUBIAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_NUBIAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_NUBIAN, id:6, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_nubian_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_NUBIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_NUBIAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_NUBIAN, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_nubian_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_NUBIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_NUBIAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_NUBIAN, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_nubian_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_NUBIAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_NUBIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_NUBIAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_NUBIAN, id:16, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_nubian = {
    type : ENEMY_8_NUBIAN
    percentage_type1 : 60
    percentage_type2 : 20
    percentage_type3 : 20
    figure_types: [FIGURE_ENEMY_NUBIAN_ARCHER, FIGURE_ENEMY_NUBIAN_AXEMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

// persian
figure_persian_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_PERSIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_PERSIAN, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_PERSIAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_PERSIAN, id:3, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 1
    missile_attack_value : 6
    missile_delay : 50 
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_persian_spearman = {
    animations : {
        walk : { pack:PACK_ENEMY_PERSIAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_PERSIAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_PERSIAN, id:6, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_persian_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_PERSIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_PERSIAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_PERSIAN, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_persian_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_PERSIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_PERSIAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_PERSIAN, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_persian_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_PERSIAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_PERSIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_PERSIAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_PERSIAN, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_persian = {
    type : ENEMY_9_PERSIAN
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_PERSIAN_ARCHER, FIGURE_ENEMY_PERSIAN_SPEARMAN, FIGURE_ENEMY_PERSIAN_CHARIOT]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

// phoenician
figure_phoenician_spearman = {
    animations : {
        walk : { pack:PACK_ENEMY_PHOENICIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_PHOENICIAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_PHOENICIAN, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 1
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    is_enemy : true
    max_amount : 25
}

figure_phoenician_swordman = {
    animations : {
        walk : { pack:PACK_ENEMY_PHOENICIAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_PHOENICIAN, id:6, max_frames:9 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }
    terrain_usage : TERRAIN_USAGE_ANY
    max_amount : 25
}

figure_phoenician_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_PHOENICIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_PHOENICIAN, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_phoenician_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_PHOENICIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_PHOENICIAN, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_phoenician_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_PHOENICIAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_PHOENICIAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_PHOENICIAN, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_phoenician = {
    type : ENEMY_10_PHOENICIAN
    percentage_type1 : 80
    percentage_type2 : 10
    percentage_type3 : 10
    figure_types: [FIGURE_ENEMY_PHOENICIAN_SPEARMAN, FIGURE_ENEMY_PHOENICIAN_SWORDMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

// roman
figure_roman_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_ROMAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_ROMAN, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_ROMAN, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_ROMAN, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    defense_value: 1
    missile_attack_value : 6
    missile_delay : 50 
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_roman_legioner = {
    animations : {
        walk : { pack:PACK_ENEMY_ROMAN, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_ROMAN, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_ROMAN, id:6, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_roman_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_ROMAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_ROMAN, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_ROMAN, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_roman_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_ROMAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_ROMAN, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_ROMAN, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_roman_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_ROMAN, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_ROMAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_ROMAN, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_ROMAN, id:16, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_roman = {
    type : ENEMY_11_ROMAN
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_ROMAN_ARCHER, FIGURE_ENEMY_ROMAN_LEGIONER, FIGURE_NONE]
    layout: FORMATION_COLUMN
}

// seapeople
figure_seapeople_archer = {
    animations : {
        walk : { pack:PACK_ENEMY_SEAPEOPLE, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:1, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_SEAPEOPLE, id:2, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_SEAPEOPLE, id:3, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 50
    attack_value : 6
    missile_attack_value : 6
    missile_delay : 50 
    defense_value: 1
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_ARROW
    is_enemy : true
    max_amount : 25
}

figure_seapeople_axeman = {
    animations : {
        walk : { pack:PACK_ENEMY_SEAPEOPLE, id:4, max_frames:12 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:5, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_SEAPEOPLE, id:6, max_frames:9 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_seapeople_transport_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_SEAPEOPLE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:8, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_SEAPEOPLE, id:9, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_seapeople_war_ship = {
    animations : {
        swim : { pack:PACK_ENEMY_SEAPEOPLE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:11, max_frames:11, loop:false }
        idle : { pack:PACK_ENEMY_SEAPEOPLE, id:12, max_frames:1 }
    }

    category: figure_category_hostile
    max_damage : 290
    attack_value : 17
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

figure_seapeople_chariot = {
    animations : {
        walk : { pack:PACK_ENEMY_SEAPEOPLE, id:13, max_frames:12 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_SEAPEOPLE, id:15, max_frames:12 }
        attack2 : { pack:PACK_ENEMY_SEAPEOPLE, id:16, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 120
    attack_value : 9
    defense_value: 3
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
}

enemy_seapeople = {
    type : ENEMY_12_SEAPEOPLE
    percentage_type1 : 80
    percentage_type2 : 10
    percentage_type3 : 10
    figure_types: [FIGURE_ENEMY_SEAPEOPLE_ARCHER, FIGURE_ENEMY_SEAPEOPLE_SWORDMAN, FIGURE_NONE]
    layout: FORMATION_COLUMN
}