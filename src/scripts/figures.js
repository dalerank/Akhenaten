log_info("akhenaten: figures info started")

import figure.prototype
import figure.figure_params
import figure.phrase
import figure.festival_guy
import figure.ostrich_hunter
import figure.antelope_hunter
import figure.birds_hunter
import figure.architector
import figure.bricklayer
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
import figure.slave
import figure.soldier
import figure.stonemason
import figure.storageyard_cart
import figure.tax_collector
import figure.teacher
import figure.tomb_artisan
import figure.tomb_robber

figure_water_carrier {
  overlay : OVERLAY_WATER
	animations {
		walk {  pack:PACK_SPR_MAIN, id:59, max_frames:12 }
		death {  pack:PACK_SPR_MAIN, id:60, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_WATER_CARRIER }
  	}

	sounds {
		water_desease_can_start_at_any_moment { sound: "water_g01.wav" }
		water_no_food_in_city { sound: "water_g02.wav" }
		water_city_have_no_army { sound: "water_g03.wav" }
		water_need_workers { sound: "water_g04.wav" }
		water_gods_are_angry { sound: "water_g05.wav" }
		water_city_is_bad { sound: "water_g06.wav" }
		water_much_unemployments { sound: "water_g07.wav" }
		water_low_entertainment { sound: "water_g08.wav" }
		water_city_is_good { sound: "water_g09.wav" }
		water_city_is_amazing { sound: "water_g10.wav" }
	}

  terrain_usage : TERRAIN_USAGE_ROADS
  max_roam_length : 640
  record_path : true
}

figure_festival_guy {
  overlay : OVERLAY_RELIGION
	animations {
		juggler_walk { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		musician_walk { pack:PACK_SPR_MAIN, id:191, max_frames:12 }
		dancer_walk {pack:PACK_SPR_MAIN, id:128, max_frames:12}
		priest_ra_walk { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		priest_osiris_walk {pack:PACK_SPR_MAIN, id:197, max_frames:12}
		priest_ptah_walk {pack:PACK_SPR_MAIN, id:187, max_frames:12}
		priest_seth_walk {pack:PACK_SPR_MAIN, id:193, max_frames:12}
		priest_bast_walk {pack:PACK_SPR_MAIN, id:208, max_frames:12}
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FESTIVAL_GUY }
	}

	sounds {
		osiris_god_love_festival { sound:"priest_osiris_e01.wav", group:230, text:0 }
		ra_god_love_festival { sound:"priest_ra_e01.wav", group:231, text:0 }
		ptah_god_love_festival { sound:"priest_ptah_e01.wav", group:232, text:0 }
		seth_god_love_festival { sound:"priest_seth_e01.wav", group:233, text:0 }
		bast_god_love_festival { sound:"priest_bast_e01.wav", group:234, text:0 }
		juggler_i_like_festivals { sound:"juggler_e01.wav" }
		musician_i_like_festivals { sound:"musician_e01.wav" }
		dancer_i_like_festivals { sound:"dancer_e01.wav" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
	permission : epermission_entertainer
}

figure_tower_sentry {
  overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:54, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:55, max_frames:8, loop:false }
		fire { pack:PACK_SPR_MAIN, id:56, max_frames:12 }
		attack { pack:PACK_SPR_MAIN, id:197, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TOWER_SENTRY }
	}

	sounds {
		tower_sentry_no_enemies_sighted { sound:"guard_e01.wav" }
		tower_sentry_ready_approaching_enemy { sound:"guard_e02.wav" }
		tower_sentry_no_trouble_defeating_army { sound:"guard_e03.wav" }
		tower_sentry_enemy_is_fierce { sound:"guard_e04.wav" }
	}

	category: figure_category_armed
	max_damage : 40
	attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
	missile_delay : 40
}

figure_ostrich {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:156, max_frames:12 }
		death { id:157, max_frames:8, duration:3, loop:false }
		eating { id:159, max_frames:7 }
		idle { id:160, max_frames:7 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_OSTRICH }
	}

	category: figure_category_animal
	max_damage: 100
	corpse_time_delay: 300
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
}

figure_hyena {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:161, max_frames:12 }
		attack { id:162, max_frames:6 }
		death { id:163, max_frames:8, duration:3, loop:false }
		idle { id:164, max_frames:6 }
		eating { id:165, max_frames:6 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HYENA }
	}

	category: figure_category_animal
	max_damage: 100
	attack_value: 6
	terrain_usage : TERRAIN_USAGE_ANIMAL
	max_hungry : 30
	max_hunting_distance : 12
	chase_speed_mult : 2
}

figure_asp {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:0, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:1, max_frames:12 }
		idle { pack:PACK_EXPANSION_SPR, id:2, max_frames:12 }
		death { pack:PACK_EXPANSION_SPR, id:3, max_frames:6, loop:false }
		eating { pack:PACK_EXPANSION_SPR, id:4, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ASP }
	}

	category: figure_category_animal
	max_damage: 60
	attack_value: 4
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 10
	chase_speed_mult: 2
}

figure_lion {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:5, max_frames:11 }
		attack { pack:PACK_EXPANSION_SPR, id:6, max_frames:11 }
		idle { pack:PACK_EXPANSION_SPR, id:7, max_frames:6 }
		eating { pack:PACK_EXPANSION_SPR, id:8, max_frames:10 }
		death { pack:PACK_EXPANSION_SPR, id:9, max_frames:4 } // sit/rest frames (not corpse)
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LION }
	}

	category: figure_category_animal
	max_damage: 150
	attack_value: 8
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 12
	chase_speed_mult: 2
}

figure_scorpion {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:10, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:11, max_frames:6 }
		idle { pack:PACK_EXPANSION_SPR, id:12, max_frames:6 }
		eating { pack:PACK_EXPANSION_SPR, id:14, max_frames:6 }
		death { pack:PACK_EXPANSION_SPR, id:13, max_frames:6, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SCORPION }
	}

	category: figure_category_animal
	max_damage: 80
	attack_value: 5
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 10
	chase_speed_mult: 2
}

figure_antelope {
	animations {
		_pack { pack:PACK_SPR_AMBIENT }
		walk { id:30, max_frames: 12 }
		death { id:31, max_frames:8, duration:3, loop:false }
		eating { id:33, max_frames:7 }
		idle { id:33, max_frames:8 }
		run { id:34, max_frames:8 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ANTELOPE }
	}

	category: figure_category_animal
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
	corpse_time_delay: 300
}

figure_horses = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:113, max_frames:12 }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_ballista {
	animations {
		flying { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		eating { pack:PACK_SPR_MAIN, id:115, max_frames:25 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BIRDS }
	}

	category: figure_category_inactive
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
}

figure_birds = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		idle : { pack:PACK_SPR_MAIN, id:114, max_frames:1, loop:false }
		eating : { pack:PACK_SPR_MAIN, id:115, max_frames:25 }
		death : { pack:PACK_SPR_MAIN, id:115, max_frames:25, loop:false }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BIRDS }
	}

	category: figure_category_animal
	max_damage: 100
	corpse_time_delay: 300
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
}

figure_crocodile = {
  animations : {
		walk : { pack:PACK_SPR_MAIN, id:23, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:24, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_MAIN, id:25, max_frames:6 }
		swim : { pack:PACK_SPR_MAIN, id:26, max_frames:11 }
		idle : { pack:PACK_SPR_MAIN, id:23, max_frames:1, loop: false }
		swim_idle : { pack:PACK_SPR_MAIN, id:27, max_frames:11 }
		eating : { pack:PACK_SPR_MAIN, id:25, max_frames:6 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_CROCODILE }
	}

	category: figure_category_hostile
	max_damage: 200
	attack_value: 7
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
	max_hungry : 25
	max_hunting_distance : 10
	chase_speed_mult : 2
}

figure_hippo = {
  animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:22, max_frames:12 }
		idle : { pack:PACK_SPR_AMBIENT, id:22, max_frames:1 }
		death : { pack:PACK_SPR_AMBIENT, id:23, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_AMBIENT, id:24, max_frames:7 }
		swim : { pack:PACK_SPR_AMBIENT, id:25, max_frames:8 }
		swim_attack : { pack:PACK_SPR_AMBIENT, id:26, max_frames:8 }
		swim_idle : { pack:PACK_SPR_AMBIENT, id:27, max_frames:8 }
		eating : { pack:PACK_SPR_AMBIENT, id:28, max_frames:8 }
		dance : { pack:PACK_SPR_AMBIENT, id:29, max_frames:8 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HIPPO }
	}

	category: figure_category_animal
	max_damage: 250
	attack_value: 12
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
}

figure_hunter_arrow {
	animations {
		walk { pack:PACK_SPR_MAIN, id:0, max_frames:12 }
		shadow { pack:PACK_SPR_MAIN, id:1, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_ARROW }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 6
    terrain_usage : TERRAIN_USAGE_ANY
}

figure_antelope_hunter_javelin = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:44, max_frames:12 }
		shadow : { pack:PACK_SPR_AMBIENT, id:43, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_ARROW }
	}

	category: figure_category_inactive
	max_damage : 100
	missile_attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY,
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

figure_spear = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 }
	}

	category: figure_category_inactive
  max_damage : 100
  missile_attack_value : 20
  terrain_usage : TERRAIN_USAGE_ANY,
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SPEAR }
}

figure_javelin = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:4 }
	}

	category: figure_category_hostile
  max_damage : 70
  attack_value : 5
  missile_attack_value : 5
  missile_delay : 70
  terrain_usage : TERRAIN_USAGE_ANY
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_JAVELIN }
}

figure_bolt = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 }
	}

	category: figure_category_inactive
  max_damage : 100
  missile_attack_value : 100
  terrain_usage : TERRAIN_USAGE_ANY,
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BOLT }
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
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
	}

	category: figure_category_native
	max_damage: 10
}

figure_native_trader = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
	}

	category: figure_category_native
	max_damage: 10
}

figure_academy_scriber {
  overlay : OVERLAY_SCRIBAL_SCHOOL
	animations {
		walk { pack:PACK_SPR_MAIN, id:199, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:200, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SCRIBER }
	}

	sounds {
		scriber_dicease_can_start { sound: "scribe_e01.wav" } 
		scriber_plague_could_break_out { sound: "scribe_g01.wav" } 
		scriber_no_food_in_city { sound: "scribe_g02.wav" } 
		scriber_defenses_are_weak { sound: "scribe_g03.wav" } 
		scriber_need_more_workers { sound: "scribe_g04.wav" } 
		scriber_gods_are_angry { sound: "scribe_g05.wav" } 
		scriber_reputation_is_low { sound: "scribe_g06.wav" } 
		scriber_high_unemployment { sound: "scribe_g07.wav" } 
		scriber_low_entertainment { sound: "scribe_g08.wav" } 
		scriber_city_is_ok { sound: "scribe_g09.wav" } 
		scriber_city_is_amazing { sound: "scribe_g10.wav" } 
	}

	category : figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

figure_worker {
  overlay : OVERLAY_LABOR
	animations {
		walk { pack:PACK_SPR_MAIN, id:116, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:117, max_frames:8, loop:false }
		work { pack:PACK_SPR_MAIN, id:118, max_frames:12 }
	}

	sounds {
		worker_going_to_workplace {sound:"worker_e02.wav", group:212, text:0}
		worker_farm_is_flooded {sound:"worker_e03.wav", group:212, text:1}
		worker_desease_can_start_at_any_moment {sound:"worker_g01.wav", group:212, text:2}
		worker_no_food_in_city {sound:"worker_g02.wav", group:212, text:3}
		worker_enemies_in_city {sound:"worker_g03.wav", group:212, text:4}
		worker_need_workers {sound:"worker_g04.wav", group:212, text:5}
		worker_gods_are_angry {sound:"worker_g05.wav", group:212, text:6}
		worker_city_is_bad {sound:"worker_g06.wav", group:212, text:7}
		worker_much_unemployments {sound:"worker_g07.wav", group:212, text:8}
		worker_low_entertainment {sound:"worker_g08.wav", group:212, text:9}
		worker_city_is_good {sound:"worker_g09.wav", group:212, text:10}
		worker_city_is_amazing {sound:"worker_g10.wav", group:212, text:11}
	}

	category: figure_category_citizen
	max_damage : 10
	record_path : true
}

figure_cart {
	stone: { pack:PACK_SPR_MAIN, id:102  }
	granite: { pack:PACK_SPR_MAIN, id:103 }
	sandstone: { pack:PACK_SPR_MAIN, id:101 }
	limestone: { pack:PACK_SPR_MAIN, id:104 }
	bricks: { pack:PACK_SPR_MAIN, id:89 }
	empty: { pack:PACK_SPR_MAIN, id:77 }
}

figure_zookeeper {
  overlay : OVERLAY_ZOO
	animations {
		// Cleopatra SprMain2: bmp "zookeeper", group 35 starts at entry 1616 (SprMain2_01616).
		walk { pack:PACK_EXPANSION_SPR, id:35, max_frames:12 }
		death { pack:PACK_EXPANSION_SPR, id:36, max_frames:7, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ZOOKEEPER }
	}

	sounds {
		zookeeper_danger_of_plague : { sound: "zookeeper_e01.wav"},
		zookeeper_no_food_in_city : { sound: "zookeeper_e02.wav"},
		zookeeper_defenses_are_weak : { sound: "zookeeper_e03.wav"},
		zookeeper_need_more_workers : { sound: "zookeeper_e04.wav"},
		zookeeper_gods_are_angry : { sound: "zookeeper_e05.wav"},
		zookeeper_reputation_is_low : { sound: "zookeeper_e06.wav"},
		zookeeper_high_unemployment : { sound: "zookeeper_e07.wav"},
		zookeeper_low_entertainment : { sound: "zookeeper_e08.wav"},
		zookeeper_city_is_ok : { sound: "zookeeper_e09.wav"},
		zookeeper_city_is_amazing : { sound: "zookeeper_e10.wav"}
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length: 640
	permission : epermission_entertainer
}

// Locust swarm — Cleopatra SprMain2 bmp "locust":
// groups 30–34 = 6-frame cloud strips (non-8-dir). Runtime picks variant 0–4.
// Walk JS id=30 is timing only; main_image_update remaps to g30+variant.
// Must override main_image_update (no dir+8*frame) — see figure_locust.cpp.
// big_image: Cleopatra Unloaded pack 25 slot FIGURE_LOCUST (107).
// Tunables: swarm_days matches building_curse_farms(big); happiness Major Plague TEMP.
figure_locust {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:30, max_frames:6 }
		idle { pack:PACK_EXPANSION_SPR, id:30, max_frames:6 }
		death { pack:PACK_EXPANSION_SPR, id:30, max_frames:6, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LOCUST }
	}

	category: figure_category_inactive
	max_damage: 1
	attack_value: 0
	terrain_usage: TERRAIN_USAGE_ANY
	max_roam_length: 320

	default_swarm: 8
	max_amount: 16
	swarm_days: 48
	happiness_hit: -10
	float_height: 20
}

figure_trade_ship = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:123, max_frames:4, duration:4 }
		death : { pack:PACK_SPR_MAIN, id:124, max_frames:8 }
		idle : { pack:PACK_SPR_MAIN, id:125, max_frames:1, offset:0 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRADE_SHIP }
	}

	sounds : {
		barge_have_no_place_for_dock : {sound:"barge_e01.wav", group: 224, text:0}
		barge_docked_wait_for_dockpushers : {sound:"barge_e02.wav", group: 224, text:1}
		barge_city_not_trades : {sound:"barge_e03.wav", group: 224, text:2}
		barge_i_like_to_trage : {sound:"barge_e04.wav", group: 224, text:3}
		barge_amazing_trades : {sound:"barge_e05.wav", group: 224, text:4}
	}

	category: figure_category_citizen
	max_damage : 250
	terrain_usage : TERRAIN_USAGE_ANY
	max_capacity : 1200
}

figure_shipwreck = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:226, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SHIPWRECK }
	}

	category: figure_category_inactive
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_sled {
	animations {
		empty { pack:PACK_SPR_MAIN, id:166, max_frames:1 }
		stone { pack:PACK_SPR_MAIN, id:167, max_frames:1 }
		sandstone { pack:PACK_SPR_MAIN, id:168, max_frames:1 }
		granite { pack:PACK_SPR_MAIN, id:169, max_frames:1 }
		limestone { pack:PACK_SPR_MAIN, id:170, max_frames:1 }
		clay { pack:PACK_SPR_MAIN, id:171, max_frames:1 }
		bricks { pack:PACK_SPR_MAIN, id:172, max_frames:1 }
		marble { pack:PACK_SPR_MAIN, id:170, max_frames:1 }
		copper { pack:PACK_SPR_MAIN, id:167, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLED }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_sled_puller = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:121, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLED_PULLER }
	}

	category: figure_category_citizen
	max_damage: 10
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

figure_fishing_point {
	animations {
		point { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 }
		bubbles { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4}
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FISHING_POINT }
	}

	category: figure_category_inactive
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANY,
	render_on_flat_tiles : true
}

figure_fishing_spot = {
	animations : {
		point : { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 }
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4}
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_FISHING_SPOT }
	}

	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_warship {
	animations {
		walk {pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 }
		swim {pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 }
		death {pack:PACK_SPR_MAIN, id:142, max_frames:8, loop:false }
		attack {pack:PACK_SPR_MAIN, id:143, max_frames:6, duration:5 }
		idle {pack:PACK_SPR_MAIN, id:143, offset:3, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_WARSHIP }
	}

	orders_info {
		goto_wharf { id: 1, text: 17 }
		engage_nearby { id: 2, text: 11 }
		hold_position { id: 3, text: 9 }
		seek_and_destroy { id: 4, text: 13 }
		repair { id: 5, text: 15 }
	}

	sounds {
		warship_well_fight_to_the_death { sound: "warship_e01.wav" }
		warship_enemy_is_too_much_for_us { sound: "warship_e02.wav" }
		warship_enemies_coming_this_way { sound: "warship_e03.wav" }
		warship_ready_to_attack_invaders { sound: "warship_e04.wav" }
		warship_ready_if_foes_come { sound: "warship_e05.wav" }
	}

	category: figure_category_armed
	max_damage: 250
	attack_value : 12
	missile_attack_value : 6
	missile_delay : 200

	meta { text_id: 184, help_link:"message_building_warship" }
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_transport_ship = {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:34, max_frames:4, duration:10 }
		swim { id:34, max_frames:4, duration:10 }
		death { id:35, max_frames:8, loop:false }
		idle { id:35, offset:8, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRANSPORT_SHIP }
	}

	sounds {
		transport_must_protect_our_ship { sound: "transport_e01.wav" }
		transport_enemy_is_here { sound: "transport_e02.wav" }
		transport_were_prepared { sound: "transport_e03.wav" }
		transport_ready_if_need_arises { sound: "transport_e04.wav" }
	}

	category: figure_category_citizen
	max_damage: 250
	terrain_usage : TERRAIN_USAGE_ANY
	meta { text_id: 184, help_link:"message_figure_transport_ship" }
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
