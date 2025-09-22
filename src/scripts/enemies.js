log_info("akhenaten: enemies info started")

figure_barbarian_fast_sword = {
    animations : {
        walk : { pack:PACK_SPR_MAIN, id:54, max_frames:12 },
        death : { pack:PACK_SPR_MAIN, id:55, max_frames:8, loop:false },
        fire : { pack:PACK_SPR_MAIN, id:56, max_frames:12 },
        attack : { pack:PACK_SPR_MAIN, id:197, max_frames:12 },
    },
    terrain_usage : TERRAIN_USAGE_ANY,
    max_amount : 25,
}

enemy_barbarian = {
    type : ENEMY_0_BARBARIAN 
    percentage_type1 : 100
    percentage_type2 : 0 
    percentage_type3 : 0
    figure_types : [FIGURE_ENEMY_BARBARIAN_FAST_SPEAR, FIGURE_NONE, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

enemy_assyrian = {
    type : ENEMY_1_ASSYRIAN
    percentage_type1 : 40
    percentage_type2 : 60
    percentage_type3 : 0
    figure_types : [FIGURE_ENEMY49_FAST_SWORD, FIGURE_ENEMY51_SPEAR, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

enemy_canaanite = {
    type : ENEMY_2_CANAANITE
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figures : [FIGURE_ENEMY50_SWORD, FIGURE_ENEMY53_AXE, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

enemy_egyptian = {
    type : ENEMY_3_EGYPTIAN
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY50_SWORD, FIGURE_ENEMY48_CHARIOT, FIGURE_NONE]
    layout: FORMATION_ENEMY_MOB
}

enemy_hittite = {
    type : ENEMY_4_HITTITE
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY49_FAST_SWORD, FIGURE_ENEMY52_MOUNTED_ARCHER, FIGURE_NONE]
    layout: FORMATION_ENEMY_MOB
}

enemy_hyksos = {
    type : ENEMY_5_HYKSOS
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY44_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE]
    layout : FORMATION_COLUMN
}

enemy_kushite = {
    type : ENEMY_6_KUSHITE
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY44_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

enemy_libian = {
    type : ENEMY_7_LIBIAN
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY45_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE]
    layout : FORMATION_ENEMY_DOUBLE_LINE
}

enemy_nubian = {
    type : ENEMY_8_NUBIAN
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY45_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

enemy_persian = {
    type : ENEMY_9_PERSIAN
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY44_SWORD, FIGURE_ENEMY46_CAMEL, FIGURE_NONE]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

enemy_phoenician = {
    type : ENEMY_10_PHOENICIAN
    percentage_type1 : 90
    percentage_type2 : 10
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY45_SWORD, FIGURE_ENEMY47_ELEPHANT, FIGURE_NONE]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

enemy_roman = {
    type : ENEMY_11_ROMAN
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_KINGDOME_INFANTRY, FIGURE_NONE, FIGURE_NONE]
    layout: FORMATION_COLUMN
}

enemy_seapeople = {
    type : ENEMY_12_SEAPEOPLE
    percentage_type1 : 100
    percentage_type2 : 0
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_KINGDOME_INFANTRY, FIGURE_NONE, FIGURE_NONE]
    layout: FORMATION_COLUMN
}