log_info("akhenaten: figures info started")

import figure.prototype
import figure.figure_params
import figure.phrase
import figure.phrase_speech
import figure.festival_priest
import figure.ostrich_hunter
import figure.antelope_hunter
import figure.birds_hunter
import figure.architector
import figure.bricklayer
import figure.bubbles
import figure.carpenter
import figure.caravan_donkey
import figure.trade_caravan
import figure.cartpusher
import figure.constable
import figure.dancer
import figure.musician
import figure.juggler
import figure.senet_player
import figure.delivery_boy
import figure.dentist
import figure.docker
import figure.drunkard
import figure.embalmer
import figure.emigrant
import figure.enemy_chariot
import figure.enemy_archer
import figure.enemy_fast_sword
import figure.enemy_spearman
import figure.enemy_transport
import figure.enemy_warship
import figure.ferry_boat
import figure.fishing_boat
import figure.fireman
import figure.flotsam
import figure.frog
import figure.funeral_walker
import figure.governor
import figure.herbalist
import figure.homeless
import figure.immigrant
import figure.labor_seeker
import figure.librarian
import figure.lumberjack
import figure.magistrate
import figure.market_buyer
import figure.market_trader
import figure.mummy
import figure.noble
import figure.pharaoh
import figure.physician
import figure.plagued_citizen
import figure.priest
import figure.protestor
import figure.reed_gatherer
import figure.rioter
import figure.robber
import figure.scriber
import figure.academy_scriber
import figure.slave
import figure.soldier
import figure.stonemason
import figure.storageyard_cart
import figure.tax_collector
import figure.teacher
import figure.tomb_artisan
import figure.tomb_robber
import figure.tower_sentry
import figure.trade_ship
import figure.transport_ship
import figure.warship
import figure.water_carrier
import figure.worker
import figure.zookeeper

// Spot offsets of the 16 figures of a formation, per layout (OG enemy_formation_layout_offsets, figure_data.c).
// chariot_spots: the wider double line of chariot batalions (OG soldier_layout_offset).
formation_layouts = [
    { layout: FORMATION_COLUMN, hint: "column",
      spots: [[0,0], [1,0], [0,1], [1,1], [-1,0], [-1,1], [0,-1], [1,-1], [-1,-1], [2,-1], [2,0], [2,1], [0,2], [1,2], [-1,2], [2,2]] }
    { layout: FORMATION_DOUBLE_LINE_1, hint: "double line, first rank",
      spots: [[0,0], [0,1], [-1,0], [1,0], [-1,1], [1,1], [-2,0], [-2,1], [2,0], [2,1], [-3,0], [-3,1], [3,0], [3,1], [-4,0], [-4,1]],
      chariot_spots: [[0,0], [0,2], [-2,0], [2,0], [-2,2], [2,2], [-4,0], [-4,2], [4,0], [4,2], [-6,0], [-6,2], [6,0], [6,2], [-8,0], [-8,2]] }
    { layout: FORMATION_DOUBLE_LINE_2, hint: "double line, second rank",
      spots: [[0,0], [0,-1], [0,1], [1,0], [1,-1], [1,1], [0,-2], [1,-2], [0,2], [1,2], [0,-3], [1,-3], [0,3], [1,3], [0,-4], [1,-4]],
      chariot_spots: [[0,0], [0,-2], [0,2], [2,0], [2,-2], [2,2], [0,-4], [2,-4], [0,4], [2,4], [0,-6], [2,-6], [0,6], [2,6], [0,-8], [2,-8]] }
    { layout: FORMATION_SINGLE_LINE_1, hint: "single line, first rank",
      spots: [[0,0], [2,0], [-2,0], [1,1], [-1,1], [3,1], [-3,1], [4,0], [-4,0], [5,1], [6,0], [-5,1], [-6,0], [7,1], [8,0], [-7,1]] }
    { layout: FORMATION_SINGLE_LINE_2, hint: "single line, second rank",
      spots: [[0,0], [0,-2], [0,2], [1,-1], [1,1], [1,-3], [1,3], [0,-4], [0,4], [1,-5], [0,-6], [1,5], [0,6], [1,-7], [0,-8], [1,7]] }
    { layout: FORMATION_TORTOISE, hint: "tortoise; also the herd spawn spots (OG layout 5)",
      spots: [[0,0], [0,-1], [1,0], [0,1], [-1,0], [1,-1], [1,1], [-1,1], [-1,-1], [1,-1], [1,1], [-1,1], [-1,-1], [1,0], [-1,0], [0,0]] }
    { layout: FORMATION_MOP_UP, hint: "mop up",
      spots: [[0,0], [1,0], [0,1], [1,1], [2,0], [2,1], [1,2], [0,2], [2,2], [3,0], [3,1], [3,2], [1,3], [2,3], [0,3], [3,3]] }
    { layout: FORMATION_AT_REST, hint: "at rest",
      spots: [[0,0], [1,0], [0,1], [1,1], [2,0], [2,1], [1,2], [0,2], [2,2], [3,0], [3,1], [3,2], [1,3], [2,3], [0,3], [3,3]] }
    { layout: FORMATION_ENEMY_MOB, hint: "enemy mob",
      spots: [[0,0], [1,-1], [0,1], [0,0], [1,0], [-1,1], [2,1], [-1,-1], [1,-1], [0,1], [1,0], [0,2], [1,1], [-1,1], [1,-2], [-1,1]] }
    { layout: FORMATION_HERD, hint: "herd roaming spots, every animal herd",
      spots: [[0,0], [2,1], [-1,-1], [1,1], [1,0], [-1,1], [3,1], [-2,-1], [0,2], [-4,0], [-1,3], [0,3], [1,4], [4,0], [2,3], [-3,2]] }
    { layout: FORMATION_ENEMY_DOUBLE_LINE, hint: "enemy double line",
      spots: [[0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]] }
    { layout: FORMATION_ENEMY_WIDE_COLUMN, hint: "enemy wide column",
      spots: [[0,0], [2,0], [0,2], [2,2], [-2,0], [-2,2], [0,-2], [2,-2], [-2,-2], [4,-2], [4,0], [4,2], [0,4], [2,4], [-2,4], [4,4]] }
    { layout: FORMATION_ENEMY12, hint: "enemy 12",
      spots: [[0,0], [1,0], [0,1], [1,1], [2,0], [2,1], [1,2], [0,2], [2,2], [3,0], [3,1], [3,2], [1,3], [2,3], [0,3], [3,3]] }
    { layout: FORMATION_UNUSED_13, hint: "unused",
      spots: [[0,0], [1,0], [0,1], [1,1], [-1,0], [-1,1], [0,-1], [1,-1], [-1,-1], [2,-1], [2,0], [2,1], [0,2], [1,2], [-1,2], [2,2]] }
    { layout: FORMATION_UNUSED_14, hint: "unused",
      spots: [[0,0], [1,0], [0,1], [1,1], [-1,0], [-1,1], [0,-1], [1,-1], [-1,-1], [2,-1], [2,0], [2,1], [0,2], [1,2], [-1,2], [2,2]] }
    { layout: FORMATION_CHARGE, hint: "after a charge, column spacing",
      spots: [[0,0], [1,0], [0,1], [1,1], [-1,0], [-1,1], [0,-1], [1,-1], [-1,-1], [2,-1], [2,0], [2,1], [0,2], [1,2], [-1,2], [2,2]] }
]

figure_ostrich {
	herd_size : 7
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:156, max_frames:12 }
		death { id:157, max_frames:8, duration:3, loop:false }
		attack { id:158, max_frames:7 }
		eating { id:159, max_frames:8 }
		idle { id:160, max_frames:8 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_OSTRICH }
	}

	category: figure_category_animal
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	scared_ticks: 128
	rest_base_ticks: 150
	rest_random_ticks: 150
	no_tile_wait_ticks: 100
	dying_ticks: 500
	alert_ticks: 20
}

figure_hyena {
	herd_size : 7
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:161, max_frames:12 }
		attack { id:162, max_frames:6 }
		death { id:163, max_frames:8, duration:3, loop:false }
		idle { id:164, max_frames:6 }
		eating { id:165, max_frames:6 } // OG HYENA_REST
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HYENA }
	}

	category: figure_category_hostile
	max_damage: 100
	attack_value: 6
	missile_defense_value: 0
	terrain_usage : TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	// wild_predators hyena + climate desert_predator_0 hunt.
	rest_base_ticks: 150
	rest_random_ticks: 100
	no_tile_wait_ticks: 100
	dying_ticks: 500
	hunt_delay: 16
	hunt_radius: 10
	chase_ticks_per_ring: 18
	prowl_speed_factor: 2
	forbidden_prey: [
		FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
}

figure_asp {
	// OG scenario_climate.c CENTRAL_PREDATOR_1: max_figures 6
	herd_size : 6
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:0, max_frames:12 } // OG IMAGE_GROUP_FIGURE_ASP
		attack { pack:PACK_EXPANSION_SPR, id:1, max_frames:6 } // OG IMAGE_GROUP_FIGURE_ASP_ATTACK
		death { pack:PACK_EXPANSION_SPR, id:3, max_frames:6, loop:false } // OG IMAGE_GROUP_FIGURE_ASP_DEATH
		idle { pack:PACK_EXPANSION_SPR, id:4, max_frames:6 } // OG IMAGE_GROUP_FIGURE_ASP_REST
		choose { pack:PACK_EXPANSION_SPR, id:0, max_frames:1 }
		return { pack:PACK_EXPANSION_SPR, id:0, max_frames:1 }
		look { pack:PACK_EXPANSION_SPR, id:4, max_frames:1 }
		spawned { pack:PACK_EXPANSION_SPR, id:0, max_frames:8 }
		big_image { pack:PACK_EXPANSION, id:1, offset:4 }
	}

	// OG Figure_model row 102: category 7 (predator), hit points 10, attack 5, armor 0, speed 7
	category: figure_category_hostile
	is_predator: true
	max_damage: 10
	attack_value: 5
	defense_value: 0
	missile_defense_value: 0
	terrain_usage: TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	// OG figure_movement_move_ticks walk ticks per call, cycled: speed 7 and PROWL speed 14
	move_cycle: [1, 1, 1, 2]
	prowl_cycle: [2, 2, 3]

	reset_frame_on_walk: true
	death_has_directions: false

	rest_base_ticks: 50
	rest_random_ticks: 100
	arrival_rest_base_ticks: 0
	no_tile_wait_ticks: 0
	no_tile_wait_random_ticks: 100
	dying_ticks: 500
	chase_ticks_per_ring: 18
	// OG climate record: hunt_delay, hunt_radius
	hunt_delay: 30
	hunt_radius: 6
	forbidden_prey: [
		FIGURE_FISHING_BOAT, FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
	// OG effect.c figure_binds group 3: variant 2 (attack), variant 3 (death)
	attack_sound: "Wavs/asp_r.wav"
	die_sound: "Wavs/aspdie.wav"

	// OG herds.c update_predators with the climate record: spawn_delay 16, move_delay 30, roam_radius 2
	herd_spawn_delay: 16
	herd_move_delay: 30
	herd_roam_radius: 2
	herd_spawn_only_when_present: false
	// OG animals_wild.c: HERD_SPAWN_WAIT_RANGE 25, PREDATOR_SPAWN_WAIT_FACTOR 4; herds.h HERD_SPAWNED_WAIT_TICKS 10
	herd_spawn_wait_range: 25
	herd_spawn_wait_factor: 4
	herd_new_animal_wait: 10
	herd_allowed_terrain: []
	herd_blocked_terrain: [
		TERRAIN_ROCK, TERRAIN_GARDEN, TERRAIN_RUBBLE, TERRAIN_WALL, TERRAIN_GATEHOUSE, TERRAIN_DIKE,
		TERRAIN_ORE, TERRAIN_UNK_02, TERRAIN_ROCK_NEAR_MONUMENT
	]
	herd_special_terrain: [
		TERRAIN_TREE, TERRAIN_ROCK, TERRAIN_WATER, TERRAIN_SHRUB, TERRAIN_GARDEN, TERRAIN_ROAD,
		TERRAIN_ELEVATION, TERRAIN_RUBBLE, TERRAIN_FLOODPLAIN, TERRAIN_MARSHLAND, TERRAIN_ORE,
		TERRAIN_UNK_02, TERRAIN_DUNE, TERRAIN_DEEPWATER, TERRAIN_ROCK_NEAR_MONUMENT
	]

	// Seth curse raid (gameplay_seth_asp_raid), not in OG
	raid_hunt_distance: 40
	raid_chase_speed_mult: 2
	raid_non_targets: [
		FIGURE_ASP, FIGURE_SCORPION, FIGURE_LION, FIGURE_HYENA, FIGURE_HIPPO, FIGURE_CROCODILE,
		FIGURE_ANTELOPE, FIGURE_OSTRICH, FIGURE_FROG, FIGURE_LOCUST, FIGURE_BIRDS, FIGURE_EXPLOSION,
		FIGURE_STANDARD_BEARER, FIGURE_TRADE_SHIP, FIGURE_FISHING_BOAT, FIGURE_MAP_FLAG, FIGURE_FLOTSAM,
		FIGURE_BUBBLES, FIGURE_SHIPWRECK, FIGURE_INDIGENOUS_NATIVE, FIGURE_TOWER_SENTRY, FIGURE_NATIVE_TRADER,
		FIGURE_ARROW, FIGURE_JAVELIN, FIGURE_BOLT, FIGURE_BALLISTA, FIGURE_CREATURE
	]
}

figure_lion {
	herd_size : 4
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:5, max_frames:11 }
		attack { pack:PACK_EXPANSION_SPR, id:6, max_frames:11 }
		death { pack:PACK_EXPANSION_SPR, id:7, max_frames:6, loop:false }
		rest { pack:PACK_EXPANSION_SPR, id:8, max_frames:10 }
		idle { pack:PACK_EXPANSION_SPR, id:9, max_frames:4, duration:2 }
		choose { pack:PACK_EXPANSION_SPR, id:5, max_frames:1 }
		arrival_idle { pack:PACK_EXPANSION_SPR, id:9, max_frames:4 }
		big_image { pack:PACK_EXPANSION, id:1, offset:5 }
	}

	category: figure_category_hostile
	is_predator: true
	max_damage: 12
	attack_value: 10
	defense_value: 0
	missile_defense_value: 0
	terrain_usage: TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	move_cycle: [1, 1, 1, 2]
	prowl_cycle: [2, 2, 3]

	reset_frame_on_walk: false
	death_has_directions: true

	rest_base_ticks: 150
	rest_random_ticks: 200
	arrival_rest_base_ticks: 150
	no_tile_wait_ticks: 200
	no_tile_wait_random_ticks: 0
	dying_ticks: 500
	chase_ticks_per_ring: 18
	hunt_delay: 18
	hunt_radius: 14
	forbidden_prey: [
		FIGURE_FISHING_BOAT, FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
	attack_sound: "Wavs/lion_r.wav"
	die_sound: "Wavs/liondie.wav"

	herd_spawn_delay: 12
	herd_move_delay: 18
	herd_roam_radius: 10
	herd_spawn_only_when_present: true
	herd_spawn_wait_range: 25
	herd_spawn_wait_factor: 4
	herd_new_animal_wait: 10
	herd_allowed_terrain: []
	herd_blocked_terrain: [
		TERRAIN_ROCK, TERRAIN_GARDEN, TERRAIN_RUBBLE, TERRAIN_WALL, TERRAIN_GATEHOUSE, TERRAIN_DIKE,
		TERRAIN_ORE, TERRAIN_UNK_02, TERRAIN_ROCK_NEAR_MONUMENT
	]
	herd_special_terrain: [
		TERRAIN_TREE, TERRAIN_ROCK, TERRAIN_WATER, TERRAIN_SHRUB, TERRAIN_GARDEN, TERRAIN_ROAD,
		TERRAIN_ELEVATION, TERRAIN_RUBBLE, TERRAIN_FLOODPLAIN, TERRAIN_MARSHLAND, TERRAIN_ORE,
		TERRAIN_UNK_02, TERRAIN_DUNE, TERRAIN_DEEPWATER, TERRAIN_ROCK_NEAR_MONUMENT
	]

	raid_hunt_distance: 40
	raid_chase_speed_mult: 2
	raid_non_targets: [
		FIGURE_ASP, FIGURE_SCORPION, FIGURE_LION, FIGURE_HYENA, FIGURE_HIPPO, FIGURE_CROCODILE,
		FIGURE_ANTELOPE, FIGURE_OSTRICH, FIGURE_FROG, FIGURE_LOCUST, FIGURE_BIRDS, FIGURE_EXPLOSION,
		FIGURE_STANDARD_BEARER, FIGURE_TRADE_SHIP, FIGURE_FISHING_BOAT, FIGURE_MAP_FLAG, FIGURE_FLOTSAM,
		FIGURE_BUBBLES, FIGURE_SHIPWRECK, FIGURE_INDIGENOUS_NATIVE, FIGURE_TOWER_SENTRY, FIGURE_NATIVE_TRADER,
		FIGURE_ARROW, FIGURE_JAVELIN, FIGURE_BOLT, FIGURE_BALLISTA, FIGURE_CREATURE
	]
}

figure_scorpion {
	herd_size : 2
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:10, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:11, max_frames:6 }
		death { pack:PACK_EXPANSION_SPR, id:13, max_frames:6, loop:false }
		idle { pack:PACK_EXPANSION_SPR, id:14, max_frames:6 }
		choose { pack:PACK_EXPANSION_SPR, id:10, max_frames:1 }
		return { pack:PACK_EXPANSION_SPR, id:10, max_frames:1 }
		look { pack:PACK_EXPANSION_SPR, id:14, max_frames:1 }
		spawned { pack:PACK_EXPANSION_SPR, id:10, max_frames:8 }
		big_image { pack:PACK_EXPANSION, id:1, offset:2 }
	}

	category: figure_category_hostile
	is_predator: true
	max_damage: 7
	attack_value: 4
	defense_value: 0
	missile_defense_value: 0
	terrain_usage: TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	move_cycle: [1]
	prowl_cycle: [2]

	reset_frame_on_walk: true
	death_has_directions: false

	rest_base_ticks: 0
	rest_random_ticks: 100
	arrival_rest_base_ticks: 0
	no_tile_wait_ticks: 0
	no_tile_wait_random_ticks: 100
	dying_ticks: 500
	chase_ticks_per_ring: 18
	hunt_delay: 20
	hunt_radius: 6
	forbidden_prey: [
		FIGURE_FISHING_BOAT, FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
	attack_sound: "Wavs/scorpion_r.wav"
	die_sound: "Wavs/scorpiondie.wav"

	herd_spawn_delay: 20
	herd_move_delay: 20
	herd_roam_radius: 7
	herd_spawn_only_when_present: false
	herd_spawn_wait_range: 25
	herd_spawn_wait_factor: 4
	herd_new_animal_wait: 10
	herd_allowed_terrain: []
	herd_blocked_terrain: [
		TERRAIN_ROCK, TERRAIN_GARDEN, TERRAIN_RUBBLE, TERRAIN_WALL, TERRAIN_GATEHOUSE, TERRAIN_DIKE,
		TERRAIN_ORE, TERRAIN_UNK_02, TERRAIN_ROCK_NEAR_MONUMENT
	]
	herd_special_terrain: [
		TERRAIN_TREE, TERRAIN_ROCK, TERRAIN_WATER, TERRAIN_SHRUB, TERRAIN_GARDEN, TERRAIN_ROAD,
		TERRAIN_ELEVATION, TERRAIN_RUBBLE, TERRAIN_FLOODPLAIN, TERRAIN_MARSHLAND, TERRAIN_ORE,
		TERRAIN_UNK_02, TERRAIN_DUNE, TERRAIN_DEEPWATER, TERRAIN_ROCK_NEAR_MONUMENT
	]

	raid_hunt_distance: 40
	raid_chase_speed_mult: 2
	raid_non_targets: [
		FIGURE_ASP, FIGURE_SCORPION, FIGURE_LION, FIGURE_HYENA, FIGURE_HIPPO, FIGURE_CROCODILE,
		FIGURE_ANTELOPE, FIGURE_OSTRICH, FIGURE_FROG, FIGURE_LOCUST, FIGURE_BIRDS, FIGURE_EXPLOSION,
		FIGURE_STANDARD_BEARER, FIGURE_TRADE_SHIP, FIGURE_FISHING_BOAT, FIGURE_MAP_FLAG, FIGURE_FLOTSAM,
		FIGURE_BUBBLES, FIGURE_SHIPWRECK, FIGURE_INDIGENOUS_NATIVE, FIGURE_TOWER_SENTRY, FIGURE_NATIVE_TRADER,
		FIGURE_ARROW, FIGURE_JAVELIN, FIGURE_BOLT, FIGURE_BALLISTA, FIGURE_CREATURE
	]
}

figure_antelope {
	herd_size : 7
	// OG ANTELOPE…FLEE (SprAmbient 30–35); flee uses run; rest=idle, graze=eating.
	animations {
		_pack { pack:PACK_SPR_AMBIENT }
		walk { id:30, max_frames:12 }
		death { id:31, max_frames:8, duration:3, loop:false }
		attack { id:32, max_frames:7 }
		eating { id:33, max_frames:8 }
		idle { id:34, max_frames:8 }
		run { id:35, max_frames:8 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ANTELOPE }
	}

	category: figure_category_animal
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	scared_ticks: 128
	rest_base_ticks: 150
	rest_random_ticks: 150
	no_tile_wait_ticks: 100
	dying_ticks: 500
	alert_ticks: 20
}

figure_horses = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:113, max_frames:12 }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

// OG military.c figure_ballista_action (FIG_BALLISTA).
ballista_rules {
	search_ticks: 20
	aim_ticks: 10
	reload_ticks: 23
}

figure_ballista {
	animations {
		// OG IMAGE_GROUP_FIGURE_BALLISTA / _FIRE (SprAmbient 17 / 19).
		walk { pack:PACK_SPR_AMBIENT, id:17, max_frames:8 }
		fire { pack:PACK_SPR_AMBIENT, id:19, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BALLISTA }
	}

	category: figure_category_inactive
	max_damage: 100
	missile_attack_value: 100
	missile_delay: 100
	missile_range: 15
	terrain_usage : TERRAIN_USAGE_WALLS
}

figure_birds = {
	herd_size : 7
	// OG IMAGE_GROUP_FIGURE_BIRDS/_DEATH (SprMain 114/115); flock is non-directional (frame>>1).
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		death : { pack:PACK_SPR_MAIN, id:115, max_frames:25, loop:false }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BIRDS }
	}

	category: figure_category_animal
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
	speed_mult: 1
	scared_ticks: 128
	rest_base_ticks: 150
	rest_random_ticks: 150
	no_tile_wait_ticks: 100
	dying_ticks: 500
}

figure_crocodile = {
  herd_size : 1
  animations : {
		walk : { pack:PACK_SPR_MAIN, id:23, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:24, max_frames:8, duration:3, loop:false }
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
		attack : { pack:PACK_SPR_MAIN, id:25, max_frames:6 }
		swim : { pack:PACK_SPR_MAIN, id:26, max_frames:11 }
		idle : { pack:PACK_SPR_MAIN, id:23, max_frames:1, loop: false }
		swim_idle : { pack:PACK_SPR_MAIN, id:27, max_frames:11 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_CROCODILE }
	}

	category: figure_category_hostile
	max_damage: 200
	attack_value: 7
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
	speed_mult: 1
	// climate_animals northern_predator_0 + animal_rules predator rests.
	rest_base_ticks: 250
	rest_random_ticks: 100
	no_tile_wait_ticks: 100
	dying_ticks: 500
	hunt_delay: 50
	hunt_radius: 2
	chase_ticks_per_ring: 18
	// animal_choices % for GO_TO_WATER vs REST.
	water_chance_idle: 50
	water_chance_in_water: 90
	water_chance_other: 25
	// OG figure_is_boat skip.
	forbidden_prey: [
		FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
}

figure_hippo = {
  herd_size : 3
  animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:22, max_frames:12 }
		idle : { pack:PACK_SPR_AMBIENT, id:22, max_frames:1 }
		death : { pack:PACK_SPR_AMBIENT, id:23, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_AMBIENT, id:24, max_frames:7 }
		swim : { pack:PACK_SPR_AMBIENT, id:25, max_frames:8 }
		swim_attack : { pack:PACK_SPR_AMBIENT, id:26, max_frames:8 }
		swim_idle : { pack:PACK_SPR_AMBIENT, id:27, max_frames:8 }
		eating : { pack:PACK_SPR_AMBIENT, id:28, max_frames:8 } // OG HIPPO_REST
		dancer : { pack:PACK_SPR_AMBIENT, id:29, max_frames:8 } // OG HIPPO_ANIMATE_IN_WATER
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames:23, duration:1, loop:false }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HIPPO }
	}

	category: figure_category_hostile
	max_damage: 250
	attack_value: 12
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
	speed_mult: 1
	// animal_rules predator + hippo-specific + climate central_predator_0.
	rest_base_ticks: 250
	rest_random_ticks: 100
	no_tile_wait_ticks: 100
	dying_ticks: 500
	hunt_delay: 90
	hunt_radius: 4
	chase_ticks_per_ring: 18
	animate_ticks: 20
	after_hunt_ticks: 200
	// OG animal_choices {water, rest, animate, charge}.
	choice_idle: [50, 50, 0, 0]
	choice_in_water: [75, 5, 20, 0]
	choice_animating: [90, 1, 9, 0]
	choice_other: [29, 70, 0, 1]
	forbidden_prey: [
		FIGURE_TRADE_SHIP, FIGURE_FERRY_BOAT,
		FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP, FIGURE_SHIPWRECK,
		FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP,
		FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP
	]
}

// OG animals.c hunter_spear_action (FIG_HUNTER_SPEAR = 74).
hunter_spear_rules {
	speed: 3
	flight_ticks: 104
	image_directions: 32
	orientation_mult: 4
}

figure_hunter_spear {
	animations {
		// OG SpeAmbient groups 39/40 → remake ambient 44/43 (same as hunter javelin sheet).
		walk { pack:PACK_SPR_AMBIENT, id:44, max_frames:32 }
		shadow { pack:PACK_SPR_AMBIENT, id:43, max_frames:32 }
		// OG SpeMain group 50: central climate frame stick (5 frames, no shadow).
		central { pack:PACK_SPR_MAIN, id:50, max_frames:5 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_SPEAR }
	}

	category: figure_category_inactive
	max_damage : 100
	missile_attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY
}

// Remake-only alias type (179); hunters fire FIGURE_HUNTER_SPEAR like OG.
figure_antelope_hunter_javelin = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:44, max_frames:12 }
		shadow : { pack:PACK_SPR_AMBIENT, id:43, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_SPEAR }
	}

	category: figure_category_inactive
	max_damage : 100
	missile_attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY,
}

// OG missiles.h / missiles.c constants (arrow/bolt/spear flight + spear_set_image).
missile_rules {
    speed: 4
    flight_ticks: 120
    max_defense: 20
    damage_base: 30
    arrow_image_offset: 16
    bolt_image_offset: 32
    image_directions: 16
    spear_image_directions: 32
    spear_orientation_mult: 4
    facing_away_penalty: 4
    single_line_bonus: 4
    mop_up_penalty: 2
    attack_timeout: 6
    docked_warship_bonus: 2
}

figure_arrow = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:0, max_frames:12 }
		shadow : { pack:PACK_SPR_MAIN, id:1, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_ARROW }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 6
    terrain_usage : TERRAIN_USAGE_ANY
}

// OG FIG_ENEMY_MISSILE / figure_spear_action — SprMain 198 + shadow 199, 32 dirs.
figure_spear = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:32 }
		shadow : { pack:PACK_SPR_MAIN, id:199, max_frames:32 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SPEAR }
	}

	category: figure_category_inactive
	max_damage : 100
	missile_attack_value : 20
	terrain_usage : TERRAIN_USAGE_ANY
}

// OG military.c figure_javelin_action (FIG_PLAYER_MISSILE).
javelin_rules {
    speed: 4
    flight_ticks: 120
    max_defense: 20
    damage_base: 20
    image_directions: 32
    orientation_mult: 4
    max_experience: 100
    attack_timeout: 6
}

// OG: javelin draws hunter spear; tower/ballista draws enemy spear (tower anim).
figure_javelin = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:44, max_frames:32 }
		shadow : { pack:PACK_SPR_AMBIENT, id:43, max_frames:32 }
		tower : { pack:PACK_SPR_MAIN, id:198, max_frames:32 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_JAVELIN }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 5
    terrain_usage : TERRAIN_USAGE_ANY
}

// OG FIG_BOLT: game never spawns it in play (only test / create); ballista fires javelin.
figure_bolt = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:0, max_frames:16 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BOLT }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 100
    terrain_usage : TERRAIN_USAGE_ANY
}

figure_standard_bearer {
	animations {
		walk { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		pole { pack:PACK_GENERAL, id:54, offset:0, max_frames:21 }
		flag_infantry { pack:PACK_GENERAL, id:126, offset:0, max_frames:9, duration:6 }
		flag_archers  { pack:PACK_GENERAL, id:126, offset:10, max_frames:9, duration:6 }
		flag_chariots { pack:PACK_GENERAL, id:126, offset:20, max_frames:9, duration:6 }
		sign { pack:PACK_GENERAL, id:3 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_STANDARD_BEARER }
	}

    is_soldier : true
	category: figure_category_armed
    max_damage : 80
	terrain_usage : TERRAIN_USAGE_ANY
}

figure_native = {
	animations : {
		// OG draws from the scenario enemy infantry strip; barbarian infantry is the closest standalone pack.
		walk : { pack:PACK_ENEMY_BARBARIAN, id:3, max_frames:12 }
		death : { pack:PACK_ENEMY_BARBARIAN, id:4, max_frames:8, loop:false }
		attack : { pack:PACK_ENEMY_BARBARIAN, id:5, max_frames:12, loop:false }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_INDIGENOUS_NATIVE }
	}

	category: figure_category_native
	max_damage: 10
	max_roam_length: 800
	terrain_usage: TERRAIN_USAGE_ANY
}

figure_native_trader = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
	}

	category: figure_category_native
	max_damage: 10
}

figure_cart {
	stone: { pack:PACK_SPR_MAIN, id:102  }
	granite: { pack:PACK_SPR_MAIN, id:103 }
	sandstone: { pack:PACK_SPR_MAIN, id:101 }
	limestone: { pack:PACK_SPR_MAIN, id:104 }
	bricks: { pack:PACK_SPR_MAIN, id:89 }
	empty: { pack:PACK_SPR_MAIN, id:77 }
}

figure_locust {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:30, max_frames:6 }
		eating { pack:PACK_EXPANSION_SPR, id:32, max_frames:6 }
		big_image { pack:PACK_EXPANSION, id:1, offset:7 }
	}

	category: figure_category_inactive
	max_damage: 10
	attack_value: 0
	terrain_usage: TERRAIN_USAGE_ANYWHERE

	countdown_after_plague: 2632
	countdown_fly_off: 1000
	months_before_flood: 2
	locusts_per_farm: 9
	square_side: 3
	max_start_delay: 300
	happiness_loss: 15
}

// OG FIG_SHIPWRECK: 36 animation frames then gone; settle to open water once (wait=1000).
figure_shipwreck = {
	animations : {
		// Frame index is animation_frame (0..35); pack id still provisional vs image_shipwreck.
		walk : { pack:PACK_SPR_MAIN, id:226, max_frames:36 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SHIPWRECK }
	}

	category: figure_category_inactive
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY,
}

// OG figure_sled_action / figure_sled_puller_action (laborer.c): image groups minus 39 in SprMain,
// minus 659 in SprMain2. A resource missing from resource_images uses default_image (OG bricks).
figure_sled {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		stone { id:167, max_frames:1 }
		limestone { id:168, max_frames:1 }
		granite { id:169, max_frames:1 }
		marble { id:170, max_frames:1 }
		sandstone { id:171, max_frames:1 }
		bricks { id:172, max_frames:1 }
		stone_ramp { id:174, max_frames:1 }
		limestone_ramp { id:175, max_frames:1 }
		granite_ramp { id:176, max_frames:1 }
		marble_ramp { id:177, max_frames:1 }
		sandstone_ramp { id:178, max_frames:1 }
		bricks_ramp { id:179, max_frames:1 }
		empty { id:173, max_frames:1 }
		copper { pack:PACK_EXPANSION_SPR, id:27, max_frames:1 }
		lamps { pack:PACK_EXPANSION_SPR, id:39, max_frames:1 }
	}

	resource_images [
		{ resource: RESOURCE_STONE, ground: "stone", ramp: "stone_ramp" }
		{ resource: RESOURCE_LIMESTONE, ground: "limestone", ramp: "limestone_ramp" }
		{ resource: RESOURCE_GRANITE, ground: "granite", ramp: "granite_ramp" }
		{ resource: RESOURCE_MARBLE, ground: "marble", ramp: "marble_ramp" }
		{ resource: RESOURCE_SANDSTONE, ground: "sandstone", ramp: "sandstone_ramp" }
		{ resource: RESOURCE_BRICKS, ground: "bricks", ramp: "bricks_ramp" }
		{ resource: RESOURCE_COPPER, ground: "copper", ramp: "bricks_ramp" }
		{ resource: RESOURCE_LAMPS, ground: "lamps", ramp: "bricks_ramp" }
	]
	default_image { ground: "bricks", ramp: "bricks_ramp" }
	empty_image { ground: "empty", ramp: "empty" }

	// OG Figure_model "Pulled Stone": category 0, never fought; enemy.c skips it as a missile target.
	category: figure_category_inactive
	ignored_by_enemy_missiles: true
	no_portrait: true
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_sled_puller = {
	animations : {
		_pack { pack:PACK_SPR_MAIN }
		pulling : { id:121, max_frames:12 }
		front : { id:122, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLED_PULLER }
	}

	category: figure_category_citizen
	max_damage: 100
	// Remake gameplay_change_sled_pullers_flee: an enemy this close makes the pullers drop the sled.
	flee_enemy_distance: 8
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_drunkard {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:203, max_frames:12 }
		back { id:203, max_frames:12 }
		womit { id:204, max_frames:12, duration:4 }
		death { id:205, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DRUNKARD }
	}

	sounds {
		drunkard_need_drink {sound:"drunkard_e01.wav"}
		drunkard_going_to_tavern {sound:"drunkard_e02.wav"}
		drunkard_time_for_beer {sound:"drunkard_e03.wav"}
		drunkard_feeling_dizzy {sound:"drunkard_e04.wav"}
		drunkard_oh_my_stomach {sound:"drunkard_e05.wav"}
		drunkard_going_home {sound:"drunkard_e06.wav"}
	}

	category: figure_category_citizen
	max_damage: 10
	walk_delay : 50
    womit_delay : 50
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

figure_seagulls {
	animations {
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SEAGULLS }
	}

	category: figure_category_inactive
	max_damage: 0
	terrain_usage : TERRAIN_USAGE_ANY
}

figure_fishing_point {
	animations {
		point { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 }
		bubbles { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4}
		big_image { pack:PACK_UNLOADED, id:25, offset:95 } // OG FIG_JUMPING_FISH
	}

	category: figure_category_inactive
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANY,
	render_on_flat_tiles : true
}

figure_explosion = {
	animations : {
		poof : { pack:PACK_SPR_AMBIENT, id:12, max_frames:12 },
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_EXPLOSION }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_map_flag = {
	animations : {
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_MAP_FLAG }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY,
}
