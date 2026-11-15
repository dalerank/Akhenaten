log_info("akhenaten: enemies info started")

enemy_fast_sword_sounds = {
	enemy_sword_attacking { sound:"enemy_sword_attacking.wav", text: "#enemy_sword_attacking" }
	enemy_sword_marching { sound:"enemy_sword_marching.wav", text: "#enemy_sword_marching" }
	enemy_sword_waiting { sound:"enemy_sword_waiting.wav", text: "#enemy_sword_waiting" }
	enemy_sword_leaving { sound:"enemy_sword_leaving.wav", text: "#enemy_sword_leaving" }
	enemy_sword_no_army { sound:"enemy_sword_no_army.wav", text: "#enemy_sword_no_army" }
	enemy_sword_no_food { sound:"enemy_sword_no_food.wav", text: "#enemy_sword_no_food" }
	enemy_sword_disease { sound:"enemy_sword_disease.wav", text: "#enemy_sword_disease" }
	enemy_sword_need_workers { sound:"enemy_sword_need_workers.wav", text: "#enemy_sword_need_workers" }
	enemy_sword_gods_angry { sound:"enemy_sword_gods_angry.wav", text: "#enemy_sword_gods_angry" }
	enemy_sword_city_is_bad { sound:"enemy_sword_city_is_bad.wav", text: "#enemy_sword_city_is_bad" }
	enemy_sword_low_entertainment { sound:"enemy_sword_low_entertainment.wav", text: "#enemy_sword_low_entertainment" }
	enemy_sword_city_is_good { sound:"enemy_sword_city_is_good.wav", text: "#enemy_sword_city_is_good" }
	enemy_sword_city_is_amazing { sound:"enemy_sword_city_is_amazing.wav", text: "#enemy_sword_city_is_amazing" }
	enemy_sword_for_glory { sound:"enemy_sword_for_glory.wav", text: "#enemy_sword_for_glory" }
}

enemy_archer_sounds = {
	enemy_archer_shooting { sound:"enemy_archer_shooting.wav", text: "#enemy_archer_shooting" }
	enemy_archer_marching { sound:"enemy_archer_marching.wav", text: "#enemy_archer_marching" }
	enemy_archer_waiting { sound:"enemy_archer_waiting.wav", text: "#enemy_archer_waiting" }
	enemy_archer_leaving { sound:"enemy_archer_leaving.wav", text: "#enemy_archer_leaving" }
	enemy_archer_city_will_fall { sound:"enemy_archer_city_will_fall.wav", text: "#enemy_archer_city_will_fall" }
	enemy_archer_arrows_ready { sound:"enemy_archer_arrows_ready.wav", text: "#enemy_archer_arrows_ready" }
	enemy_archer_for_glory { sound:"enemy_archer_for_glory.wav", text: "#enemy_archer_for_glory" }
}

enemy_spearman_sounds = {
	enemy_spearman_shooting { sound:"enemy_spearman_shooting.wav", text: "#enemy_spearman_shooting" }
	enemy_spearman_marching { sound:"enemy_spearman_marching.wav", text: "#enemy_spearman_marching" }
	enemy_spearman_waiting { sound:"enemy_spearman_waiting.wav", text: "#enemy_spearman_waiting" }
	enemy_spearman_leaving { sound:"enemy_spearman_leaving.wav", text: "#enemy_spearman_leaving" }
	enemy_spearman_city_will_fall { sound:"enemy_spearman_city_will_fall.wav", text: "#enemy_spearman_city_will_fall" }
	enemy_spearman_spears_ready { sound:"enemy_spearman_spears_ready.wav", text: "#enemy_spearman_spears_ready" }
	enemy_spearman_for_glory { sound:"enemy_spearman_for_glory.wav", text: "#enemy_spearman_for_glory" }
}

enemy_transport_sounds = {
	enemy_transport_created { sound:"enemy_transport_created.wav", text: "#enemy_transport_created" }
	enemy_transport_sailing { sound:"enemy_transport_sailing.wav", text: "#enemy_transport_sailing" }
	enemy_transport_disembarking { sound:"enemy_transport_disembarking.wav", text: "#enemy_transport_disembarking" }
	enemy_transport_idle { sound:"enemy_transport_idle.wav", text: "#enemy_transport_idle" }
	enemy_transport_no_army { sound:"enemy_transport_no_army.wav", text: "#enemy_transport_no_army" }
	enemy_transport_no_food { sound:"enemy_transport_no_food.wav", text: "#enemy_transport_no_food" }
	enemy_transport_disease { sound:"enemy_transport_disease.wav", text: "#enemy_transport_disease" }
	enemy_transport_need_workers { sound:"enemy_transport_need_workers.wav", text: "#enemy_transport_need_workers" }
	enemy_transport_gods_angry { sound:"enemy_transport_gods_angry.wav", text: "#enemy_transport_gods_angry" }
	enemy_transport_city_is_bad { sound:"enemy_transport_city_is_bad.wav", text: "#enemy_transport_city_is_bad" }
	enemy_transport_low_entertainment { sound:"enemy_transport_low_entertainment.wav", text: "#enemy_transport_low_entertainment" }
	enemy_transport_city_is_good { sound:"enemy_transport_city_is_good.wav", text: "#enemy_transport_city_is_good" }
	enemy_transport_city_is_amazing { sound:"enemy_transport_city_is_amazing.wav", text: "#enemy_transport_city_is_amazing" }
	enemy_transport_for_glory { sound:"enemy_transport_for_glory.wav", text: "#enemy_transport_for_glory" }
}

enemy_warship_sounds = {
	enemy_warship_created { sound:"enemy_warship_created.wav", text: "#enemy_warship_created" }
	enemy_warship_idle { sound:"enemy_warship_idle.wav", text: "#enemy_warship_idle" }
	enemy_warship_pursuing { sound:"enemy_warship_pursuing.wav", text: "#enemy_warship_pursuing" }
	enemy_warship_attacking { sound:"enemy_warship_attacking.wav", text: "#enemy_warship_attacking" }
	enemy_warship_no_army { sound:"enemy_warship_no_army.wav", text: "#enemy_warship_no_army" }
	enemy_warship_no_food { sound:"enemy_warship_no_food.wav", text: "#enemy_warship_no_food" }
	enemy_warship_disease { sound:"enemy_warship_disease.wav", text: "#enemy_warship_disease" }
	enemy_warship_need_workers { sound:"enemy_warship_need_workers.wav", text: "#enemy_warship_need_workers" }
	enemy_warship_gods_angry { sound:"enemy_warship_gods_angry.wav", text: "#enemy_warship_gods_angry" }
	enemy_warship_city_is_bad { sound:"enemy_warship_city_is_bad.wav", text: "#enemy_warship_city_is_bad" }
	enemy_warship_low_entertainment { sound:"enemy_warship_low_entertainment.wav", text: "#enemy_warship_low_entertainment" }
	enemy_warship_city_is_good { sound:"enemy_warship_city_is_good.wav", text: "#enemy_warship_city_is_good" }
	enemy_warship_city_is_amazing { sound:"enemy_warship_city_is_amazing.wav", text: "#enemy_warship_city_is_amazing" }
	enemy_warship_for_glory { sound:"enemy_warship_for_glory.wav", text: "#enemy_warship_for_glory" }
}

// OG enemy_attack_priority / enemy_attack_fallback (figure_data.c:499-511): the first building type in a list
// wins, distance breaks ties within one type; fallback when the chosen list finds nothing reachable.
enemy_attack_rules = {
    priority : {
        food_chain : [BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_BAZAAR, BUILDING_GRANARY_UP,
                      BUILDING_STORAGE_YARD_UP, BUILDING_BAZAAR_UP, BUILDING_GRAIN_FARM, BUILDING_LETTUCE_FARM,
                      BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_CATTLE_RANCH,
                      BUILDING_HENNA_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_FIGS_FARM]

        gold_stores : [BUILDING_TOWN_PALACE, BUILDING_VILLAGE_PALACE, BUILDING_TAX_COLLECTOR_UPGRADED,
                       BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_VILLAGE_PALACE_UP,
                       BUILDING_TOWN_PALACE_UP, BUILDING_CITY_PALACE]

        best_buildings : [BUILDING_VILLAGE_PALACE_UP, BUILDING_TOWN_PALACE_UP, BUILDING_CITY_PALACE,
                          BUILDING_DYNASTY_MANSION, BUILDING_FAMILY_MANSION, BUILDING_PERSONAL_MANSION,
                          BUILDING_HOUSE_PALATIAL_ESTATE, BUILDING_HOUSE_MODEST_ESTATE, BUILDING_HOUSE_STATELY_MANOR,
                          BUILDING_HOUSE_ELEGANT_MANOR, BUILDING_HOUSE_SPACIOUS_MANOR, BUILDING_HOUSE_COMMON_MANOR,
                          BUILDING_HOUSE_FANCY_RESIDENCE, BUILDING_HOUSE_ELEGANT_RESIDENCE,
                          BUILDING_HOUSE_SPACIOUS_RESIDENCE, BUILDING_HOUSE_COMMON_RESIDENCE,
                          BUILDING_HOUSE_SPACIOUS_APARTMENT, BUILDING_HOUSE_MODEST_APARTMENT,
                          BUILDING_HOUSE_SPACIOUS_HOMESTEAD, BUILDING_HOUSE_MODEST_HOMESTEAD,
                          BUILDING_HOUSE_ORDINARY_COTTAGE, BUILDING_HOUSE_ROUGH_COTTAGE,
                          BUILDING_HOUSE_COMMON_SHANTY, BUILDING_HOUSE_MEAGER_SHANTY, BUILDING_HOUSE_STURDY_HUT,
                          BUILDING_HOUSE_CRUDE_HUT]

        troops : [BUILDING_MILITARY_ACADEMY, BUILDING_MILITARY_ACADEMY_2, BUILDING_MILITARY_ACADEMY_3,
                  BUILDING_POLICE_STATION]

        fallback : [BUILDING_VILLAGE_PALACE_UP, BUILDING_TOWN_PALACE_UP, BUILDING_CITY_PALACE,
                    BUILDING_DYNASTY_MANSION, BUILDING_FAMILY_MANSION, BUILDING_PERSONAL_MANSION,
                    BUILDING_HOUSE_PALATIAL_ESTATE, BUILDING_HOUSE_MODEST_ESTATE, BUILDING_HOUSE_STATELY_MANOR,
                    BUILDING_HOUSE_ELEGANT_MANOR, BUILDING_HOUSE_SPACIOUS_MANOR, BUILDING_TOWN_PALACE,
                    BUILDING_VILLAGE_PALACE, BUILDING_SENET_HOUSE, BUILDING_PAVILLION, BUILDING_ORACLE,
                    BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
                    BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_TAX_COLLECTOR_UPGRADED,
                    BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_BANDSTAND, BUILDING_BOOTH,
                    BUILDING_MORTUARY, BUILDING_APOTHECARY, BUILDING_LIBRARY, BUILDING_SCRIBAL_SCHOOL,
                    BUILDING_HOUSE_COMMON_MANOR, BUILDING_HOUSE_FANCY_RESIDENCE, BUILDING_HOUSE_ELEGANT_RESIDENCE,
                    BUILDING_HOUSE_SPACIOUS_RESIDENCE, BUILDING_HOUSE_COMMON_RESIDENCE, BUILDING_PHYSICIAN,
                    BUILDING_POTTERY_WORKSHOP, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
                    BUILDING_STONEMASONS_GUILD, BUILDING_ARTISANS_GUILD, BUILDING_JEWELS_WORKSHOP,
                    BUILDING_WEAPONSMITH, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_GRANARY,
                    BUILDING_STORAGE_YARD, BUILDING_BAZAAR, BUILDING_SHIPWRIGHT, BUILDING_DOCK,
                    BUILDING_FISHING_WHARF, BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH,
                    BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST, BUILDING_CONSERVATORY, BUILDING_JUGGLER_SCHOOL,
                    BUILDING_BULLFIGHT_SCHOOL, BUILDING_DANCE_SCHOOL, BUILDING_MILITARY_ACADEMY,
                    BUILDING_MILITARY_ACADEMY_2, BUILDING_MILITARY_ACADEMY_3, BUILDING_HOUSE_SPACIOUS_APARTMENT,
                    BUILDING_HOUSE_MODEST_APARTMENT, BUILDING_HOUSE_SPACIOUS_HOMESTEAD,
                    BUILDING_HOUSE_MODEST_HOMESTEAD, BUILDING_HOUSE_ORDINARY_COTTAGE, BUILDING_DENTIST,
                    BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_GOLD_MINE,
                    BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE, BUILDING_CLAY_PIT, BUILDING_WOOD_CUTTERS,
                    BUILDING_RESERVED_90, BUILDING_GRAIN_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM,
                    BUILDING_FLAX_FARM, BUILDING_BARLEY_FARM, BUILDING_CATTLE_RANCH, BUILDING_CHICKPEAS_FARM,
                    BUILDING_HENNA_FARM, BUILDING_POLICE_STATION, BUILDING_ARCHITECT_POST, BUILDING_WATER_SUPPLY,
                    BUILDING_WELL, BUILDING_HOUSE_ROUGH_COTTAGE, BUILDING_HOUSE_COMMON_SHANTY,
                    BUILDING_HOUSE_MEAGER_SHANTY, BUILDING_HOUSE_STURDY_HUT, BUILDING_HOUSE_CRUDE_HUT]
    }
}

// OG figure/enemy_ships.c + scenario/invasion.c constants of the enemy transport ship.
enemy_transport_rules {
    soldiers_per_ship : 16
    launch_first_wait : 10
    launch_wait_step : 40
    landing_wait : 50
    evade_wait : 100
    evade_ticks : 75
    evade_range : 18
    damaged_percent : 15
    reroute_ticks : 99
    sinking_ticks : 32
    escape_distance : 10
}

// Generic enemy transport (FIGURE_ENEMY_TRANSPORT = 92). Fallback when a nation
// has no dedicated transport enum / console spawn.
figure_enemy_transport_generic = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 92 Enemy Transport; speed from the Hittite row (92 has none).
    category: figure_category_hostile
    max_damage : 100
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

// OG figure/enemy_ships.c, ships_player.h, military.c ship_move and scenario/invasion.c constants of the enemy
// warship.
enemy_warship_rules {
    launch_first_wait : 10
    launch_wait_step : 25
    reroute_ticks : 99
    damaged_percent : 15
    sinking_ticks : 32
    stay_months : 4
    attack_ticks : 50
    patrol_base_ticks : 75
    patrol_random_ticks : 30
    docked_target_reduction : 20
    ram_cooldown : 15
    evade_ticks : 75
    evade_range : 18
    escape_distance : 10
    shoot_ticks : 100
    fast_ram_percent : 20
    slow_speed_percent : 40
    full_speed_max : 18
    mode_change_ticks : 200
    score_land_enemy : 17
    score_boat : 5
    score_transport : 10
    score_loaded_transport : 25
    score_warship : 15
    // OG figure_movement_move_ticks: walk ticks per tick for speed 0..18 (18 = default case).
    speed_cycles : [
        { ticks:[0] }
        { ticks:[0, 0, 0, 1] }
        { ticks:[0, 0, 1] }
        { ticks:[1, 0] }
        { ticks:[1, 1, 0] }
        { ticks:[1, 1, 1, 0] }
        { ticks:[1] }
        { ticks:[1, 1, 1, 2] }
        { ticks:[1, 1, 2] }
        { ticks:[1, 2] }
        { ticks:[2, 2, 1] }
        { ticks:[2, 2, 2, 1] }
        { ticks:[2] }
        { ticks:[2, 2, 2, 3] }
        { ticks:[2, 2, 3] }
        { ticks:[3, 2] }
        { ticks:[3, 3, 2] }
        { ticks:[3, 3, 3, 2] }
        { ticks:[3] }
    ]
    // OG figure_ship_direction_table: row = target heading, column = own heading.
    ram_divisors : [
        { own:[5, 3, 1, 2, 4, 2, 1, 3] }
        { own:[3, 5, 3, 1, 2, 4, 2, 1] }
        { own:[1, 3, 5, 3, 1, 2, 4, 2] }
        { own:[2, 1, 3, 5, 3, 1, 2, 4] }
        { own:[4, 2, 1, 3, 5, 3, 1, 2] }
        { own:[2, 4, 2, 1, 3, 5, 3, 1] }
        { own:[1, 2, 4, 2, 1, 3, 4, 3] }
        { own:[3, 1, 2, 4, 3, 1, 3, 5] }
    ]
}

// Generic enemy warship (FIGURE_ENEMY_WARSHIP = 93). Fallback for barbarian /
// console spawn when a nation has no dedicated warship enum.
figure_enemy_warship_generic = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 93 Enemy Warship; speed, ship_steps and ship_moves from the Hittite row (93 has none).
    category: figure_category_hostile
    max_damage : 100
    attack_value : 0
    missile_defense_value : 5
    missile_attack_value : 5
    missile_range : 8
    missile_delay : 35
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 100
    speed : 6
    ship_steps : 3
    ship_moves : 750
}

// barbarian
figure_barbarian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_barbarian_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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

// Barbarian pack has no ship sprites — Hittite transport fallback (E3b).
figure_barbarian_transport_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 92 Enemy Transport; speed from the Hittite row (92 has none).
    category: figure_category_hostile
    max_damage : 100
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

enemy_barbarian = {
    type : ENEMY_0_BARBARIAN 
    warship : FIGURE_ENEMY_WARSHIP
    transport : FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP
    percentage_type1 : 80
    percentage_type2 : 20 
    percentage_type3 : 0
    figure_types : [FIGURE_ENEMY_BARBARIAN_SWORD, FIGURE_ENEMY_BARBARIAN_ARCHER, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

// assyrian
figure_assyrian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_assyrian_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_ASSYRIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_ASSYRIAN, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 44 Assyrian Transport.
    category: figure_category_hostile
    max_damage : 95
    attack_value : 0
    missile_defense_value : 4
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_assyrian_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_ASSYRIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_ASSYRIAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_ASSYRIAN, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 43 (Blank: Assyrian warships have 0 hp and sink at once).
    category: figure_category_hostile
    max_damage : 0
    attack_value : 0
    missile_defense_value : 0
    missile_attack_value : 0
    missile_range : 0
    missile_delay : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 0
    speed : 0
    ship_steps : 0
    ship_moves : 0
}

figure_assyrian_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_ASSYRIAN_WAR_SHIP
    transport : FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP
    percentage_type1 : 40
    percentage_type2 : 50
    percentage_type3 : 10
    figure_types : [FIGURE_ENEMY_ASSYRIAN_ARCHER, FIGURE_ENEMY_ASSYRIAN_SWORD, FIGURE_ENEMY_ASSYRIAN_CHARIOT]
    layout : FORMATION_ENEMY_MOB
}

// canaanite
figure_canaanite_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_canaanite_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_CANAANITE, id:0, max_frames:4 }
        death : { pack:PACK_ENEMY_CANAANITE, id:1, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_CANAANITE, id:2, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 39 Canaanite Transport.
    category: figure_category_hostile
    max_damage : 15
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_canaanite_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_CANAANITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_CANAANITE, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_CANAANITE, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 38 Canaanite Warship.
    category: figure_category_hostile
    max_damage : 80
    attack_value : 80
    missile_defense_value : 1
    missile_attack_value : 15
    missile_range : 7
    missile_delay : 35
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 80
    speed : 7
    ship_steps : 2
    ship_moves : 650
}

figure_canaanite_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_CANAANITE_WAR_SHIP
    transport : FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types : [FIGURE_ENEMY_CANAANITE_ARCHER, FIGURE_ENEMY_CANAANITE_SWORD, FIGURE_NONE]
    layout : FORMATION_ENEMY_MOB
}

// egyptian
// Egyptian transport (FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP = 101). No dedicated
// transport strip in the pack — reuse galera hull frames for E3b.
figure_egyptian_transport_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_EGYPTIAN, id:0, max_frames:4 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:1, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_EGYPTIAN, id:2, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 101 Egyptian Transport Ships.
    category: figure_category_hostile
    max_damage : 75
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_egyptian_galera = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_EGYPTIAN, id:0, max_frames:4 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:1, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_EGYPTIAN, id:2, max_frames:1 }
        idle_ready : { pack:PACK_ENEMY_EGYPTIAN, id:3, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 100 Egyptian Warships.
    category: figure_category_hostile
    max_damage : 300
    attack_value : 100
    missile_defense_value : 5
    missile_attack_value : 5
    missile_range : 8
    missile_delay : 35
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 300
    speed : 6
    ship_steps : 4
    ship_moves : 800
}

figure_egyptian_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_EGYPTIAN, id:4, max_frames:4 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:5, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_EGYPTIAN, id:6, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt row 100 Egyptian Warships.
    category: figure_category_hostile
    max_damage : 300
    attack_value : 100
    missile_defense_value : 5
    missile_attack_value : 5
    missile_range : 8
    missile_delay : 35
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 300
    speed : 6
    ship_steps : 4
    ship_moves : 800
}

figure_egyptian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_egyptian_spearman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
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
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_egyptian_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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

// Egyptian melee specials. Animations TEMP-reuse spearman strips (pack ids 11–13)
// until PACK_ENEMY_EGYPTIAN dump maps real sword/axe groups (ids ≥16). Do not put
// these in enemy_egyptian.figure_types[] without OG percentage confirmation.
figure_egyptian_fast_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
    animations : {
        // TEMP art: spearman walk/death/attack
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 70
    attack_value : 7
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 20
    is_enemy : true
    max_amount : 25
}

figure_egyptian_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
    animations : {
        // TEMP art: spearman walk/death/attack
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 7
    defense_value: 3
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 25
    is_enemy : true
    max_amount : 25
}

figure_egyptian_heavy_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
    animations : {
        // TEMP art: spearman walk/death/attack
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 110
    attack_value : 8
    defense_value: 4
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 35
    is_enemy : true
    max_amount : 25
}

figure_egyptian_axe = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
    animations : {
        // TEMP art: spearman walk/death/attack
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 8
    defense_value: 2
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 25
    is_enemy : true
    max_amount : 25
}

// Camel: OG enemy_rider_action(0,1) — SPEAR in INITIAL, no drown, speed 1.
// TEMP rider art until PACK_ENEMY_EGYPTIAN dump (ids ≥16).
// Not in enemy_egyptian.figure_types[] without OG percentage confirmation.
figure_egyptian_camel = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
    animations : {
        // TEMP art: chariot strips as rider stand-in
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:15, max_frames:12 }
        bow_attack : { pack:PACK_ENEMY_EGYPTIAN, id:15, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 100
    attack_value : 8
    defense_value: 3
    missile_attack_value : 7
    missile_defense_value : 0
    missile_delay : 40
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_egyptian_mounted_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
    animations : {
        // TEMP art: foot archer strips + horse sound from type branch
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:7, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:8, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_EGYPTIAN, id:9, max_frames:12 }
        dagger_attack : { pack:PACK_ENEMY_EGYPTIAN, id:10, max_frames:7 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 60
    attack_value : 6
    defense_value: 2
    missile_attack_value : 7
    missile_defense_value : 0
    missile_delay : 40
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_egyptian_elephant = {
  overlay : OVERLAY_ENEMIES
    animations : {
        // TEMP art: chariot as large-mount stand-in
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:14, max_frames:12, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:15, max_frames:12 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 250
    attack_value : 14
    defense_value: 6
    missile_defense_value : 2
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 40
    is_enemy : true
    max_amount : 10
}

// Kingdom favour-army (55–57). TEMP art = egyptian strips. Spawned when
// invasion kind is KINGDOME (remap of egyptian % slots → javelin/infantry/mounted).
figure_kingdome_javelin = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
    animations : {
        // TEMP art: egyptian spearman
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 60
    attack_value : 6
    defense_value: 3
    missile_attack_value : 6
    missile_delay : 50
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    missile_type : FIGURE_SPEAR
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_kingdome_infantry = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
    animations : {
        // TEMP art: egyptian spearman melee stand-in
        walk : { pack:PACK_ENEMY_EGYPTIAN, id:11, max_frames:12 }
        death : { pack:PACK_ENEMY_EGYPTIAN, id:12, max_frames:8, loop:false }
        attack : { pack:PACK_ENEMY_EGYPTIAN, id:13, max_frames:8 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    category: figure_category_hostile
    max_damage : 90
    attack_value : 8
    defense_value: 4
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 25
    is_enemy : true
    max_amount : 25
}

figure_kingdome_mounted = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
    animations : {
        // TEMP art: egyptian chariot
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
    warship : FIGURE_ENEMY_EGYPTIAN_WARSHIP
    transport : FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_EGYPTIAN_ARCHER, FIGURE_ENEMY_EGYPTIAN_SPEAR, FIGURE_ENEMY_EGYPTIAN_CHARIOT]
    layout: FORMATION_ENEMY_MOB
}

// hittite
figure_hittite_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_hittite_spearman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
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
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_hittite_transport_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 14 Hittite Transport.
    category: figure_category_hostile
    max_damage : 100
    attack_value : 0
    missile_defense_value : 4
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_hittite_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HITTITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_HITTITE, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HITTITE, id:12, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 13 Hittite Warship.
    category: figure_category_hostile
    max_damage : 250
    attack_value : 100
    missile_defense_value : 4
    missile_attack_value : 4
    missile_range : 11
    missile_delay : 35
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 250
    speed : 6
    ship_steps : 3
    ship_moves : 750
}

figure_hittite_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_HITTITE_WAR_SHIP
    transport : FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_HITTITE_ARCHER, FIGURE_ENEMY_HITTITE_SPEARMAN, FIGURE_ENEMY_HITTITE_CHARIOT]
    layout: FORMATION_ENEMY_MOB
}

// hyksos
figure_hyksos_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_hyksos_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HYKSOS, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_HYKSOS, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HYKSOS, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 4 Hyksos Transport.
    category: figure_category_hostile
    max_damage : 100
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_hyksos_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_HYKSOS, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_HYKSOS, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_HYKSOS, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 3 Hyksos Warship.
    category: figure_category_hostile
    max_damage : 300
    attack_value : 100
    missile_defense_value : 5
    missile_attack_value : 6
    missile_range : 9
    missile_delay : 25
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 300
    speed : 6
    ship_steps : 4
    ship_moves : 900
}

figure_hyksos_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_HYKSOS_WAR_SHIP
    transport : FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP
    percentage_type1 : 50
    percentage_type2 : 40
    percentage_type3 : 10
    figure_types: [FIGURE_ENEMY_HYKSOS_ARCHER, FIGURE_ENEMY_HYKSOS_SWORDMAN, FIGURE_ENEMY_HYKSOS_CHARIOT]
    layout : FORMATION_COLUMN
}

// kushite
figure_kushite_spearman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
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
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_kushite_axeman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_KUSHITE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_KUSHITE, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_KUSHITE, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 24 Kushite Transport Ships.
    category: figure_category_hostile
    max_damage : 50
    attack_value : 0
    missile_defense_value : 1
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_kushite_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_KUSHITE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_KUSHITE, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_KUSHITE, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 23 Kushite Warships.
    category: figure_category_hostile
    max_damage : 200
    attack_value : 100
    missile_defense_value : 3
    missile_attack_value : 4
    missile_range : 8
    missile_delay : 45
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 200
    speed : 6
    ship_steps : 3
    ship_moves : 1000
}

figure_kushite_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_KUSHITE_WAR_SHIP
    transport : FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP
    // F1: figure_types[2] is FIGURE_NONE, so the original 20% third-contingent share
    // never spawned. Folded into the axemen (type2) so the army spawns full strength.
    // F2 done: FIGURE_ENEMY_KUSHITE_CHARIOT now has a class, so re-adding a chariot
    // contingent here is purely a data decision — set figure_types[2] and a
    // percentage_type3 once the original share is confirmed.
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_KUSHITE_SPEARMAN, FIGURE_ENEMY_KUSHITE_AXEMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

// libian
figure_libian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
    animations : {
        walk : { pack:PACK_ENEMY_LIBIAN, id:0, max_frames:12 }
        death : { pack:PACK_ENEMY_LIBIAN, id:1, max_frames:8, loop:false }
        bow_attack : { pack:PACK_ENEMY_LIBIAN, id:2, max_frames:12, duration:3, loop:false }
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_libian_sword = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_LIBIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_LIBIAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_LIBIAN, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 29 Libyan Transport.
    category: figure_category_hostile
    max_damage : 20
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_libian_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_LIBIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_LIBIAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_LIBIAN, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 28 Libyan Warship.
    category: figure_category_hostile
    max_damage : 150
    attack_value : 100
    missile_defense_value : 0
    missile_attack_value : 3
    missile_range : 8
    missile_delay : 25
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 150
    speed : 7
    ship_steps : 2
    ship_moves : 900
}

figure_libian_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_LIBIAN_WAR_SHIP
    transport : FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    army_title [37, 33]
    figure_types: [FIGURE_ENEMY_LIBIAN_ARCHER, FIGURE_ENEMY_LIBIAN_SWORDMAN, FIGURE_NONE]
    layout : FORMATION_ENEMY_DOUBLE_LINE
}

// nubian
figure_nubian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_nubian_axeman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_NUBIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_NUBIAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_NUBIAN, id:9, max_frames:1 }
        big_image : { pack:PACK_UNLOADED, id:25, offset:44 }
    }

    // OG Figure_model_Normal.txt enemy row 34 Nubian Transport Ships.
    category: figure_category_hostile
    max_damage : 20
    attack_value : 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 6 (figure_movement_move_ticks).
    move_cycle : [1]
}

figure_nubian_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_NUBIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_NUBIAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_NUBIAN, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 33 Nubian Warships.
    category: figure_category_hostile
    max_damage : 100
    attack_value : 100
    missile_defense_value : 2
    missile_attack_value : 3
    missile_range : 6
    missile_delay : 50
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 100
    speed : 7
    ship_steps : 2
    ship_moves : 700
}

figure_nubian_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_NUBIAN_WAR_SHIP
    transport : FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP
    // F1: figure_types[2] is FIGURE_NONE, so the original 20% third-contingent share
    // never spawned. Folded into the axemen (type2) so the army spawns full strength.
    // F2 done: FIGURE_ENEMY_NUBIAN_CHARIOT now has a class, so re-adding a chariot
    // contingent here is purely a data decision — set figure_types[2] and a
    // percentage_type3 once the original share is confirmed.
    percentage_type1 : 60
    percentage_type2 : 40
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_NUBIAN_ARCHER, FIGURE_ENEMY_NUBIAN_AXEMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_DOUBLE_LINE
}

// persian
figure_persian_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_persian_spearman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
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
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_persian_transport_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_PERSIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_PERSIAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_PERSIAN, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 59 Persian Transport.
    category: figure_category_hostile
    max_damage : 86
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 5 (figure_movement_move_ticks).
    move_cycle : [1, 1, 1, 0]
}

figure_persian_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_PERSIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_PERSIAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_PERSIAN, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 58 Persian Warships.
    category: figure_category_hostile
    max_damage : 350
    attack_value : 110
    missile_defense_value : 6
    missile_attack_value : 8
    missile_range : 6
    missile_delay : 20
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 350
    speed : 5
    ship_steps : 5
    ship_moves : 850
}

figure_persian_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_PERSIAN_WAR_SHIP
    transport : FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_PERSIAN_ARCHER, FIGURE_ENEMY_PERSIAN_SPEARMAN, FIGURE_ENEMY_PERSIAN_CHARIOT]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

// phoenician
figure_phoenician_spearman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_spearman_sounds
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
    attack_distance : 3
    is_enemy : true
    max_amount : 25
}

figure_phoenician_swordman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_PHOENICIAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_PHOENICIAN, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 54 Phoenician Transport.
    category: figure_category_hostile
    max_damage : 90
    attack_value : 0
    missile_defense_value : 4
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 5 (figure_movement_move_ticks).
    move_cycle : [1, 1, 1, 0]
}

figure_phoenician_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_PHOENICIAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_PHOENICIAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_PHOENICIAN, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 53 Phoenician Warships.
    category: figure_category_hostile
    max_damage : 350
    attack_value : 110
    missile_defense_value : 6
    missile_attack_value : 8
    missile_range : 6
    missile_delay : 20
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 350
    speed : 5
    ship_steps : 5
    ship_moves : 850
}

figure_phoenician_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_PHOENICIAN_WAR_SHIP
    transport : FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP
    // F1: figure_types[2] is FIGURE_NONE, so the original 10% third-contingent share
    // never spawned. Folded into the swordsmen (type2) so the army spawns full strength.
    // F2 done: FIGURE_ENEMY_PHOENICIAN_CHARIOT now has a class, so re-adding a chariot
    // contingent here is purely a data decision — set figure_types[2] and a
    // percentage_type3 once the original share is confirmed.
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_PHOENICIAN_SPEARMAN, FIGURE_ENEMY_PHOENICIAN_SWORDMAN, FIGURE_NONE]
    layout: FORMATION_ENEMY_WIDE_COLUMN
}

// roman
figure_roman_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_roman_legioner = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_ROMAN, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_ROMAN, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_ROMAN, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 49 Roman Transport.
    category: figure_category_hostile
    max_damage : 60
    attack_value : 0
    missile_defense_value : 3
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 4 (figure_movement_move_ticks).
    move_cycle : [1, 1, 0]
}

figure_roman_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_ROMAN, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_ROMAN, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_ROMAN, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 48 Roman Warships.
    category: figure_category_hostile
    max_damage : 320
    attack_value : 110
    missile_defense_value : 5
    missile_attack_value : 5
    missile_range : 6
    missile_delay : 30
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 320
    speed : 4
    ship_steps : 3
    ship_moves : 700
}

figure_roman_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_ROMAN_WAR_SHIP
    transport : FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP
    percentage_type1 : 50
    percentage_type2 : 50
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_ROMAN_ARCHER, FIGURE_ENEMY_ROMAN_LEGIONER, FIGURE_NONE]
    layout: FORMATION_COLUMN
}

// seapeople
figure_seapeople_archer = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_archer_sounds
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
    missile_type : FIGURE_SPEAR
    attack_distance : 5
    is_enemy : true
    max_amount : 25
}

figure_seapeople_axeman = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_fast_sword_sounds
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
  overlay : OVERLAY_ENEMIES
    sounds: enemy_transport_sounds
    animations : {
        swim : { pack:PACK_ENEMY_SEAPEOPLE, id:7, max_frames:4 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:8, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_SEAPEOPLE, id:9, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 9 Sea People Transport Ships.
    category: figure_category_hostile
    max_damage : 150
    attack_value : 0
    missile_defense_value : 5
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    // OG speed 4 (figure_movement_move_ticks).
    move_cycle : [1, 1, 0]
}

figure_seapeople_war_ship = {
  overlay : OVERLAY_ENEMIES
    sounds: enemy_warship_sounds
    animations : {
        swim : { pack:PACK_ENEMY_SEAPEOPLE, id:10, max_frames:4 }
        death : { pack:PACK_ENEMY_SEAPEOPLE, id:11, max_frames:11, duration:3, loop:false }
        bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
        idle : { pack:PACK_ENEMY_SEAPEOPLE, id:12, max_frames:1 }
    }

    // OG Figure_model_Normal.txt enemy row 8 Sea People Warships.
    category: figure_category_hostile
    max_damage : 400
    attack_value : 120
    missile_defense_value : 7
    missile_attack_value : 8
    missile_range : 6
    missile_delay : 15
    terrain_usage : TERRAIN_USAGE_ANY
    is_enemy : true
    max_amount : 25
    hit_points : 400
    speed : 5
    ship_steps : 5
    ship_moves : 850
}

figure_seapeople_chariot = {
  overlay : OVERLAY_ENEMIES
    sounds {
        enemy_chariot_attacking { sound:"enemy_chariot_attacking.wav", text: "#enemy_chariot_attacking" }
        enemy_chariot_marching { sound:"enemy_chariot_marching.wav", text: "#enemy_chariot_marching" }
        enemy_chariot_waiting { sound:"enemy_chariot_waiting.wav", text: "#enemy_chariot_waiting" }
        enemy_chariot_leaving { sound:"enemy_chariot_leaving.wav", text: "#enemy_chariot_leaving" }
        enemy_chariot_city_will_fall { sound:"enemy_chariot_city_will_fall.wav", text: "#enemy_chariot_city_will_fall" }
        enemy_chariot_no_match { sound:"enemy_chariot_no_match.wav", text: "#enemy_chariot_no_match" }
        enemy_chariot_for_glory { sound:"enemy_chariot_for_glory.wav", text: "#enemy_chariot_for_glory" }
    }
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
    warship : FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP
    transport : FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP
    // F1: figure_types[2] is FIGURE_NONE, so the original 10% third-contingent share
    // never spawned. Folded into the swordsmen (type2) so the army spawns full strength.
    // F2 done: FIGURE_ENEMY_SEAPEOPLE_CHARIOT now has a class, so re-adding a chariot
    // contingent here is purely a data decision — set figure_types[2] and a
    // percentage_type3 once the original share is confirmed.
    percentage_type1 : 80
    percentage_type2 : 20
    percentage_type3 : 0
    figure_types: [FIGURE_ENEMY_SEAPEOPLE_ARCHER, FIGURE_ENEMY_SEAPEOPLE_SWORDMAN, FIGURE_NONE]
    layout: FORMATION_COLUMN
}

figure_bedouin = {
  overlay : OVERLAY_ENEMIES
    animations : {
        walk : { pack:PACK_SPR_AMBIENT, id:13, max_frames:12 }
        death : { pack:PACK_SPR_AMBIENT, id:14, max_frames:8, loop:false }
        attack : { pack:PACK_SPR_AMBIENT, id:15, max_frames:12 }
    }

    category: figure_category_hostile
    max_damage : 70
    attack_value : 12
    defense_value: 0
    missile_defense_value : 0
    terrain_usage : TERRAIN_USAGE_ANY
    interval_attack_delay : 25
    is_enemy : true
    move_cycle : [1, 1, 2]
}

enemy_bedouin = {
    percentage_type1 : 100
    percentage_type2 : 0
    percentage_type3 : 0
    figure_types: [FIGURE_BEDOUIN, FIGURE_BEDOUIN, FIGURE_BEDOUIN]
    layout: FORMATION_ENEMY_MOB
}

// Message phrases of an EVENT_INVADER_* invasion. warnings: the announcement, then the reminders at
// 24 / 12 / 6 / 1 months left. low_kingdom replaces no_reason when the invasion comes from a favour event.
// disembarked: the transport landing alert, -1 when the invader has none (OG scenario_invasion_landing_message).
invader_enemy = {
    phrases : {
        title : PHRASE_foreign_army_attacks_you_title
        warnings : [PHRASE_foreign_army_attacks_you_initial_announcement, PHRASE_foreign_army_attacks_you_2year_reminder,
                    PHRASE_foreign_army_attacks_you_1year_reminder, PHRASE_foreign_army_attacks_you_6month_warning,
                    PHRASE_foreign_army_attacks_you_1month_Warning]
        city_attacked : PHRASE_foreign_army_attacks_you_city_attacked_alert
        no_reason : PHRASE_foreign_army_attacks_you_no_reason_A
        low_kingdom : PHRASE_foreign_army_attacks_you_no_reason_A
        disembarked : PHRASE_foreign_army_attacks_you_disembarked_alert
    }
}

invader_egypt = {
    phrases : {
        title : PHRASE_eg_city_attacks_you_title
        warnings : [PHRASE_eg_city_attacks_you_initial_announcement, PHRASE_eg_city_attacks_you_2year_reminder,
                    PHRASE_eg_city_attacks_you_1year_reminder, PHRASE_eg_city_attacks_you_6month_warning,
                    PHRASE_eg_city_attacks_you_1month_warning]
        city_attacked : PHRASE_eg_city_attacks_you_city_attacked_alert
        no_reason : PHRASE_eg_city_attacks_you_no_reason_A
        low_kingdom : PHRASE_eg_city_attacks_you_because_of_low_kingdom
        disembarked : PHRASE_eg_city_attacks_you_disembarked_alert
    }
}

invader_pharaoh = {
    phrases : {
        title : PHRASE_pharaoh_attacks_you_title
        warnings : [PHRASE_pharaoh_attacks_you_initial_announcement, PHRASE_pharaoh_attacks_you_2year_reminder,
                    PHRASE_pharaoh_attacks_you_1year_reminder, PHRASE_pharaoh_attacks_you_6month_warning,
                    PHRASE_pharaoh_attacks_you_1month_warning]
        city_attacked : PHRASE_pharaoh_attacks_you_city_attacked_alert
        no_reason : PHRASE_pharaoh_attacks_you_no_reason_A
        low_kingdom : PHRASE_pharaoh_attacks_you_because_of_low_kingdom
        disembarked : -1
    }
}

invader_bedouins = {
    phrases : {
        title : PHRASE_bedouin_attacks_you_title
        warnings : [PHRASE_bedouin_attacks_you_initial_announcement, PHRASE_bedouin_attacks_you_2year_reminder,
                    PHRASE_bedouin_attacks_you_1year_reminder, PHRASE_bedouin_attacks_you_6month_warning,
                    PHRASE_bedouin_attacks_you_1month_warning]
        city_attacked : PHRASE_bedouin_attacks_you_city_attacked_alert
        no_reason : PHRASE_bedouin_attacks_you_no_reason_A
        low_kingdom : PHRASE_bedouin_attacks_you_no_reason_A
        disembarked : PHRASE_bedouin_attacks_you_disembarked_alert
    }
}
