log_info("akhenaten: city sounds started")

city_sounds = [
  { id: "house_slum", p: "Ambient/HOUSING1.MP3" }
  { id: "house_poor", p: "Ambient/HOUSING2.MP3" }
  { id: "house_medium", p: "Ambient/HOUSING3.MP3" }
  { id: "house_good", p: "Ambient/HOUSING4.MP3" }
  { id: "house_posh", p: "Ambient/HOUSING5.MP3" }
  { id: "booth", p: "Wavs/JUGGLER.WAV" }
  { id: "bandstand", p: "Wavs/DANCE.WAV" }
  { id: "pavilion" }
  { id: "senet_house" }
  { id: "juggler_school", p: "Wavs/juggler_school.wav" }
  { id: "dance_school", p: "Wavs/dance_school.wav" }
  { id: "conservatory", p: "Wavs/MUSIC.WAV" }
  { id: "garden" }
  { id: "apothecary", p: "Wavs/DOCTOR.WAV" }
  { id: "physician", p: "Wavs/DOCTOR.WAV" }
  { id: "mortuary", p: "Wavs/EMBALM.WAV" }
  { id: "dentist", p: "Wavs/DOCTOR.WAV" }
  { id: "fireman" }
  { id: "tower" }
  { id: "temple_osiris", p: "Wavs/tem_osiris_l.wav" }
  { id: "temple_ra", p: "Wavs/TEM_RA_L.WAV" }
  { id: "temple_ptah", p: "Wavs/tem_ptah_l.wav" }
  { id: "temple_seth", p: "Wavs/tem_seth_l.wav" }
  { id: "temple_bast", p: "Wavs/tem_bast_l.wav" }
  { id: "shrine_osiris", p: "Wavs/shr_osiris.wav" }
  { id: "shrine_ra", p: "Wavs/SHR_RA.WAV" }
  { id: "shrine_ptah", p: "Wavs/SHR_PTAH.WAV" }
  { id: "shrine_seth", p: "Wavs/SHR_SETH.WAV" }
  { id: "shrine_bast", p: "Wavs/SHR_BAST.WAV" }
  { id: "market", p: "Wavs/MARKET.WAV" }
  { id: "granary", p: "Wavs/GRANARY1.WAV" }
  { id: "storage_yard", p: "Wavs/warehouse1.wav" }
  { id: "shipyard", p: "Wavs/SHIPYRD.WAV" }
  { id: "dock", p: "Wavs/DOCK1.WAV" }
  { id: "wharf" }
  { id: "palace", p: "Wavs/palace.wav" }
  { id: "engineers_post", p: "Wavs/ENG.WAV" }
  { id: "forum" }
  { id: "water_supply" }
  { id: "well", p: "Wavs/WELL.WAV" }
  { id: "burning_ruin", p: "Wavs/FIRE.WAV" }
  { id: "grain_farm", p: "Wavs/wheatfarm.wav" }
  { id: "fig_farm", p: "Wavs/FIGFARM.WAV" }
  { id: "quarry" }
  { id: "gold_mine", p: "Wavs/GOLD.WAV" }
  { id: "timber_yard" }
  { id: "clay_pit", p: "Wavs/CLAY.WAV" }
  { id: "weapons_workshop", p: "Wavs/weapon.wav" }
  { id: "pottery_workshop", p: "Wavs/POTTERY.WAV" }
  { id: "brewery_workshop", p: "Wavs/brewery.wav" }
  { id: "empty_land" }
  { id: "river" }
  { id: "hunter_lodge", p: "Wavs/LO_HUNT.WAV" }
  { id: "police", p: "Wavs/POLICE.WAV" }
  { id: "rock", p: "Ambient/ROCK.MP3" }
  { id: "statue", p: "Wavs/STATUE1.WAV" }
  { id: "tax_collector", p: "Wavs/TAXFARM.WAV" }
  { id: "mansion" }
  { id: "tree" }
  { id: "water", p: "Wavs/WATER1.WAV" }
  { id: "shrub" }
  { id: "canal", p: "Wavs/WATER1.WAV" }
  { id: "meadow", p: "Ambient/MEADOW.MP3" }
  { id: "floodplain", p: "Ambient/floodplain.mp3" }
  { id: "marshland", p: "Ambient/vegetation.mp3" }
  { id: "chickfarm", p: "Wavs/chickfarm.wav" }
  { id: "cowfarm", p: "Wavs/cowfarm_r.wav" }
  { id: "lettuce_farm", p: "Wavs/lettucefarm.wav" }
  { id: "weaver_workshop", p: "Wavs/weaver.wav" }
  { id: "jewels_workshop", p: "Wavs/jewelry.wav" }
  { id: "chariots_workshop", p: "Wavs/chariot.wav" }
  { id: "zoo", p: "Wavs/zoo_r.wav" }
  { id: "lamp_workshop", p: "Wavs/lampmaker_r.wav" }
  { id: "paint_workshop", p: "Wavs/paintmaker_r.wav" }
  { id: "artisans_guild", p: "Wavs/artisans_r.wav" }
  { id: "water_lift", p: "Wavs/waterwheel.wav" }
  { id: "reed_gatherer", p: "Wavs/reedfarm.wav" }
]

terrain_sounds = [
  { terrain: TERRAIN_TREE, sound: "tree" }
  { terrain: TERRAIN_ROCK, sound: "rock" }
  { terrain: TERRAIN_WATER, sound: "water" }
  { terrain: TERRAIN_SHRUB, sound: "shrub" }
  { terrain: TERRAIN_GARDEN, sound: "garden" }
  { terrain: TERRAIN_CANAL, sound: "canal" }
  { terrain: TERRAIN_MEADOW, sound: "meadow" }
  { terrain: TERRAIN_FLOODPLAIN, sound: "floodplain" }
  { terrain: TERRAIN_MARSHLAND, sound: "marshland" }
]

// Enhanced city ambience (gameplay_enhanced_city_ambient): the samples above become positional voices.
zoo_ambient_bands = [
  { min_population: 0,    sound: "house_slum" }
  { min_population: 500,  sound: "house_poor" }
  { min_population: 2000, sound: "house_medium" }
  { min_population: 5000, sound: "house_good" }
  { min_population: 8000, sound: "house_posh" }
]

city_ambient = {
  max_voices: 4       // samples playing at once, loudest first
  min_gain_pct: 5     // quieter candidates are dropped
  crossfade_ms: 600   // fade time when a voice joins or leaves
  duck_pct: 35        // level while the camera moves
  duck_ms: 300
  gap_min_ms: 400     // random pause before a voice replays its sample
  gap_max_ms: 2500
  full_tiles: 16      // drawn tiles of a sample at which its gain is no longer reduced
}

sound_effect_files = [
  { effect: SOUND_EFFECT_ICON, p: "Wavs/button.wav" }
  { effect: SOUND_EFFECT_SIDEBAR, p: "Wavs/menu.wav" }
  { effect: SOUND_EFFECT_BUILD, p: "Wavs/build.wav" }
  { effect: SOUND_EFFECT_EXPLOSION, p: "Wavs/crash.wav" }
  { effect: SOUND_EFFECT_FANFARE, p: "Wavs/fanfare1.wav" }
  { effect: SOUND_EFFECT_FANFARE_URGENT, p: "Wavs/fanfare1.wav" }
  { effect: SOUND_EFFECT_ARROW, p: "Wavs/arch_atk.wav" }
  { effect: SOUND_EFFECT_AXE, p: "Wavs/sword_atk.wav" }
  { effect: SOUND_EFFECT_CLUB, p: "Wavs/sword_atk.wav" }
  { effect: SOUND_EFFECT_HORSE2, p: "Wavs/chariot_die.wav" }
  { effect: SOUND_EFFECT_JAVELIN, p: "Wavs/ship_arrow.wav" }
  { effect: SOUND_EFFECT_LION_ATTACK, p: "Wavs/lion_r.wav" }
  { effect: SOUND_EFFECT_LION_DIE, p: "Wavs/liondie.wav" }
  { effect: SOUND_EFFECT_SWORD, p: "Wavs/spear_atk.wav" }
  { effect: SOUND_EFFECT_SWORD_SWING, p: "Wavs/chariot_atk.wav" }
  { effect: SOUND_EFFECT_LIGHT_SWORD, p: "Wavs/arch_atk.wav" }
  { effect: SOUND_EFFECT_SPEAR, p: "Wavs/spear_atk.wav" }
  { effect: SOUND_EFFECT_OSTRICH_DIE, p: "Wavs/ostrichdie.wav" }
  { effect: SOUND_EFFECT_SOLDIER_DIE, p: "Wavs/die1.wav" }
  { effect: SOUND_EFFECT_SOLDIER_DIE_2, p: "Wavs/die2.wav" }
  { effect: SOUND_EFFECT_SOLDIER_DIE_3, p: "Wavs/die3.wav" }
  { effect: SOUND_EFFECT_SOLDIER_DIE_4, p: "Wavs/die4.wav" }
  { effect: SOUND_EFFECT_CITIZEN_DIE, p: "Wavs/die5.wav" }
  { effect: SOUND_EFFECT_CITIZEN_DIE_2, p: "Wavs/die6.wav" }
  { effect: SOUND_EFFECT_CITIZEN_DIE_3, p: "Wavs/die7.wav" }
  { effect: SOUND_EFFECT_CITIZEN_DIE_4, p: "Wavs/die8.wav" }
  { effect: SOUND_EFFECT_SHEEP_DIE, p: "Wavs/birddie.wav" }
  { effect: SOUND_EFFECT_ZEBRA_DIE, p: "Wavs/antelopdie.wav" }
  { effect: SOUND_EFFECT_FIRE_SPLASH, p: "Wavs/fire.wav" }
  { effect: SOUND_EFFECT_POLICE_ATTACK, p: "Wavs/police_atk.wav" }
  { effect: SOUND_EFFECT_SHIP_COLLISION_BEAM, p: "Wavs/ship_collision_beam.wav" }
  { effect: SOUND_EFFECT_SHIP_COLLISION_FORE_QUARTER, p: "Wavs/ship_collision_fore_quarter.wav" }
  { effect: SOUND_EFFECT_SHIP_COLLISION_AFT_QUARTER, p: "Wavs/ship_collision_aft_quarter.wav" }
  { effect: SOUND_EFFECT_SHIP_COLLISION_BOW, p: "Wavs/ship_collision_bow.wav" }
  { effect: SOUND_EFFECT_SHIP_COLLISION_STERN, p: "Wavs/ship_collision_stern.wav" }
]

figure_sounds = {
  out_of_view_figures: [
    FIGURE_ARCHER, FIGURE_INFANTRY, FIGURE_FCHARIOTEER, FIGURE_BEDOUIN,
    FIGURE_TRANSPORT_SHIP, FIGURE_WARSHIP,
    FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_WARSHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP, FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP,
    FIGURE_ENEMY_EGYPTIAN_GALERA,
    FIGURE_ENEMY_EGYPTIAN_ARCHER, FIGURE_ENEMY_EGYPTIAN_CHARIOT,
    FIGURE_ENEMY_KINGDOME_JAVELIN, FIGURE_ENEMY_KINGDOME_INFANTRY, FIGURE_ENEMY_KINGDOME_MOUNTED,
    FIGURE_ENEMY_BARBARIAN_ARCHER, FIGURE_ENEMY_BARBARIAN_SWORD,
    FIGURE_ENEMY_EGYPTIAN_SPEAR, FIGURE_ENEMY_EGYPTIAN_SWORD, FIGURE_ENEMY_EGYPTIAN_FAST_SWORD,
    FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD, FIGURE_ENEMY_EGYPTIAN_AXE,
    FIGURE_ENEMY_ASSYRIAN_ARCHER, FIGURE_ENEMY_CANAANITE_ARCHER, FIGURE_ENEMY_HITTITE_ARCHER, FIGURE_ENEMY_HYKSOS_ARCHER,
    FIGURE_ENEMY_LIBIAN_ARCHER, FIGURE_ENEMY_NUBIAN_ARCHER, FIGURE_ENEMY_PERSIAN_ARCHER, FIGURE_ENEMY_ROMAN_ARCHER,
    FIGURE_ENEMY_SEAPEOPLE_ARCHER,
    FIGURE_ENEMY_ASSYRIAN_SWORD, FIGURE_ENEMY_CANAANITE_SWORD, FIGURE_ENEMY_HYKSOS_SWORDMAN, FIGURE_ENEMY_KUSHITE_AXEMAN,
    FIGURE_ENEMY_LIBIAN_SWORDMAN, FIGURE_ENEMY_NUBIAN_AXEMAN, FIGURE_ENEMY_PHOENICIAN_SWORDMAN, FIGURE_ENEMY_ROMAN_LEGIONER,
    FIGURE_ENEMY_SEAPEOPLE_SWORDMAN, FIGURE_ENEMY_HITTITE_SPEARMAN, FIGURE_ENEMY_KUSHITE_SPEARMAN,
    FIGURE_ENEMY_PERSIAN_SPEARMAN, FIGURE_ENEMY_PHOENICIAN_SPEARMAN,
    FIGURE_ENEMY_ASSYRIAN_CHARIOT, FIGURE_ENEMY_CANAANITE_CHARIOT, FIGURE_ENEMY_HITTITE_CHARIOT, FIGURE_ENEMY_HYKSOS_CHARIOT,
    FIGURE_ENEMY_KUSHITE_CHARIOT, FIGURE_ENEMY_LIBIAN_CHARIOT, FIGURE_ENEMY_NUBIAN_CHARIOT, FIGURE_ENEMY_PERSIAN_CHARIOT,
    FIGURE_ENEMY_PHOENICIAN_CHARIOT, FIGURE_ENEMY_ROMAN_CHARIOT, FIGURE_ENEMY_SEAPEOPLE_CHARIOT,
    FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP, FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP, FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP,
    FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP, FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP, FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP,
    FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP, FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP, FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP,
    FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP, FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP, FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP,
    FIGURE_ENEMY_ASSYRIAN_WAR_SHIP, FIGURE_ENEMY_CANAANITE_WAR_SHIP, FIGURE_ENEMY_HITTITE_WAR_SHIP,
    FIGURE_ENEMY_HYKSOS_WAR_SHIP, FIGURE_ENEMY_KUSHITE_WAR_SHIP, FIGURE_ENEMY_LIBIAN_WAR_SHIP,
    FIGURE_ENEMY_NUBIAN_WAR_SHIP, FIGURE_ENEMY_PERSIAN_WAR_SHIP, FIGURE_ENEMY_PHOENICIAN_WAR_SHIP,
    FIGURE_ENEMY_ROMAN_WAR_SHIP, FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP
  ]

  runs: [
    { first: FIGURE_SOUND_CITIZEN_1, count: 8 }
    { first: FIGURE_SOUND_MARKET_TRADER_1, count: 4 }
  ]

  groups: [
    { group: FIGURE_SOUND_HYENA, idle: "Wavs/hyena_r.wav", roam: "Wavs/hyenaroam.wav", attack: "Wavs/hyenaatk.wav", die: "Wavs/hyenadie.wav" }
    { group: FIGURE_SOUND_LION, idle: "Wavs/lion_r.wav", roam: "Wavs/lion_r.wav", attack: "Wavs/lion_r.wav", die: "Wavs/liondie.wav" }
    { group: FIGURE_SOUND_SCORPION, idle: "Wavs/scorpion_r.wav", roam: "Wavs/scorpion_r.wav", attack: "Wavs/scorpion_r.wav", die: "Wavs/scorpiondie.wav" }
    { group: FIGURE_SOUND_ASP, idle: "Wavs/asp_r.wav", roam: "Wavs/asp_r.wav", attack: "Wavs/asp_r.wav", die: "Wavs/aspdie.wav" }
    { group: FIGURE_SOUND_OSTRICH, idle: "Wavs/ostrich_r.wav", roam: "Wavs/ostrichroam.wav", die: "Wavs/ostrichdie.wav", run: "Wavs/ostrichrun.wav" }
    { group: FIGURE_SOUND_ANTELOPE, idle: "Wavs/antelop_r.wav", roam: "Wavs/anteloproam.wav", die: "Wavs/antelopdie.wav", run: "Wavs/anteloprun.wav" }
    { group: FIGURE_SOUND_HIPPO, idle: "Wavs/hippo_r.wav", attack: "Wavs/hippoatk.wav", die: "Wavs/hippodie.wav" }
    { group: FIGURE_SOUND_CROCODILE, idle: "Wavs/croc_r.wav", attack: "Wavs/crocatk.wav", die: "Wavs/crocdie.wav" }
    { group: FIGURE_SOUND_BIRDS, idle: "Wavs/bird_r.wav", roam: "Wavs/birdroam.wav", die: "Wavs/birddie.wav" }
    { group: FIGURE_SOUND_TOWER_SENTRY, attack: "Wavs/sentry_atk.wav" }
    { group: FIGURE_SOUND_POLICE, attack: "Wavs/police_atk.wav" }
    { group: FIGURE_SOUND_ARCHER, attack: "Wavs/arch_atk.wav" }
    { group: FIGURE_SOUND_INFANTRY, attack: "Wavs/spear_atk.wav" }
    { group: FIGURE_SOUND_CHARIOT, attack: "Wavs/chariot_atk.wav", die: "Wavs/chariot_die.wav" }
    { group: FIGURE_SOUND_HUNTER_ANTELOPE, attack: "Wavs/hunt_ant_atk.wav" }
    { group: FIGURE_SOUND_HUNTER_OSTRICH, attack: "Wavs/hunt_ost_atk.wav" }
    { group: FIGURE_SOUND_HUNTER_BIRDS, attack: "Wavs/hunt_bird_atk.wav" }
    { group: FIGURE_SOUND_SHIP, attack: "Wavs/ship_arrow.wav", die: "Wavs/ship_die.wav" }
    { group: FIGURE_SOUND_ENEMY_ARCHER, attack: "Wavs/arch_atk.wav" }
    { group: FIGURE_SOUND_ENEMY_SWORD, attack: "Wavs/sword_atk.wav" }
    { group: FIGURE_SOUND_ENEMY_SPEAR, attack: "Wavs/spear_atk.wav" }
    { group: FIGURE_SOUND_CITIZEN_1, die: "Wavs/die1.wav" }
    { group: FIGURE_SOUND_CITIZEN_2, die: "Wavs/die2.wav" }
    { group: FIGURE_SOUND_CITIZEN_3, die: "Wavs/die3.wav" }
    { group: FIGURE_SOUND_CITIZEN_4, die: "Wavs/die4.wav" }
    { group: FIGURE_SOUND_CITIZEN_5, die: "Wavs/die5.wav" }
    { group: FIGURE_SOUND_CITIZEN_6, die: "Wavs/die6.wav" }
    { group: FIGURE_SOUND_CITIZEN_7, die: "Wavs/die7.wav" }
    { group: FIGURE_SOUND_CITIZEN_8, die: "Wavs/die8.wav" }
    { group: FIGURE_SOUND_MARKET_TRADER_1, die: "Wavs/dieg1.wav" }
    { group: FIGURE_SOUND_MARKET_TRADER_2, die: "Wavs/dieg2.wav" }
    { group: FIGURE_SOUND_MARKET_TRADER_3, die: "Wavs/dieg3.wav" }
    { group: FIGURE_SOUND_MARKET_TRADER_4, die: "Wavs/dieg4.wav" }
  ]
}

figure_sound_kinds = {
  default_die: FIGURE_SOUND_CITIZEN_1
  hunter_shot { central: FIGURE_SOUND_HUNTER_BIRDS, northern: FIGURE_SOUND_HUNTER_ANTELOPE, desert: FIGURE_SOUND_HUNTER_OSTRICH }

  figures: [
    { types: [FIGURE_ARCHER, FIGURE_ENEMY_KUSHITE_SPEARMAN, FIGURE_ENEMY_PHOENICIAN_SPEARMAN, FIGURE_ENEMY_BARBARIAN_ARCHER,
              FIGURE_ENEMY_ASSYRIAN_ARCHER, FIGURE_ENEMY_CANAANITE_ARCHER, FIGURE_ENEMY_HITTITE_ARCHER,
              FIGURE_ENEMY_HYKSOS_ARCHER, FIGURE_ENEMY_LIBIAN_ARCHER, FIGURE_ENEMY_NUBIAN_ARCHER,
              FIGURE_ENEMY_PERSIAN_ARCHER, FIGURE_ENEMY_ROMAN_ARCHER, FIGURE_ENEMY_SEAPEOPLE_ARCHER],
      hit: FIGURE_SOUND_ARCHER }
    { types: [FIGURE_ENEMY_EGYPTIAN_ARCHER, FIGURE_ENEMY_KINGDOME_JAVELIN],
      hit: FIGURE_SOUND_ARCHER, attack: FIGURE_SOUND_ARCHER }
    { types: [FIGURE_INFANTRY], hit: FIGURE_SOUND_INFANTRY }
    { types: [FIGURE_ENEMY_KINGDOME_INFANTRY,
              FIGURE_ENEMY_EGYPTIAN_SPEAR, FIGURE_ENEMY_EGYPTIAN_SWORD, FIGURE_ENEMY_EGYPTIAN_FAST_SWORD,
              FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD, FIGURE_ENEMY_EGYPTIAN_AXE],
      hit: FIGURE_SOUND_INFANTRY, attack: FIGURE_SOUND_INFANTRY }
    { types: [FIGURE_ENEMY_BARBARIAN_SWORD, FIGURE_ENEMY_ASSYRIAN_SWORD, FIGURE_ENEMY_CANAANITE_SWORD, FIGURE_ENEMY_HYKSOS_SWORDMAN,
              FIGURE_ENEMY_KUSHITE_AXEMAN, FIGURE_ENEMY_LIBIAN_SWORDMAN, FIGURE_ENEMY_NUBIAN_AXEMAN,
              FIGURE_ENEMY_PHOENICIAN_SWORDMAN, FIGURE_ENEMY_ROMAN_LEGIONER, FIGURE_ENEMY_SEAPEOPLE_SWORDMAN,
              FIGURE_ENEMY_HITTITE_SPEARMAN, FIGURE_ENEMY_PERSIAN_SPEARMAN],
      hit: FIGURE_SOUND_INFANTRY }
    { types: [FIGURE_ENEMY_EGYPTIAN_CHARIOT, FIGURE_ENEMY_KINGDOME_MOUNTED],
      hit: FIGURE_SOUND_CHARIOT, die: FIGURE_SOUND_CHARIOT, attack: FIGURE_SOUND_CHARIOT }
    { types: [FIGURE_FCHARIOTEER,
              FIGURE_ENEMY_ASSYRIAN_CHARIOT, FIGURE_ENEMY_CANAANITE_CHARIOT, FIGURE_ENEMY_HITTITE_CHARIOT,
              FIGURE_ENEMY_HYKSOS_CHARIOT, FIGURE_ENEMY_KUSHITE_CHARIOT, FIGURE_ENEMY_LIBIAN_CHARIOT,
              FIGURE_ENEMY_NUBIAN_CHARIOT, FIGURE_ENEMY_PERSIAN_CHARIOT, FIGURE_ENEMY_PHOENICIAN_CHARIOT,
              FIGURE_ENEMY_ROMAN_CHARIOT, FIGURE_ENEMY_SEAPEOPLE_CHARIOT],
      hit: FIGURE_SOUND_CHARIOT, die: FIGURE_SOUND_CHARIOT }
    { types: [FIGURE_BEDOUIN], hit: FIGURE_SOUND_CHARIOT, attack: FIGURE_SOUND_POLICE }
    { types: [FIGURE_CONSTABLE], attack: FIGURE_SOUND_POLICE }
    { types: [FIGURE_TOWER_SENTRY], attack: FIGURE_SOUND_TOWER_SENTRY }
    { types: [FIGURE_WARSHIP, FIGURE_ENEMY_WARSHIP, FIGURE_ENEMY_EGYPTIAN_WARSHIP, FIGURE_ENEMY_EGYPTIAN_GALERA,
              FIGURE_ENEMY_ASSYRIAN_WAR_SHIP, FIGURE_ENEMY_CANAANITE_WAR_SHIP, FIGURE_ENEMY_HITTITE_WAR_SHIP,
              FIGURE_ENEMY_HYKSOS_WAR_SHIP, FIGURE_ENEMY_KUSHITE_WAR_SHIP, FIGURE_ENEMY_LIBIAN_WAR_SHIP,
              FIGURE_ENEMY_NUBIAN_WAR_SHIP, FIGURE_ENEMY_PERSIAN_WAR_SHIP, FIGURE_ENEMY_PHOENICIAN_WAR_SHIP,
              FIGURE_ENEMY_ROMAN_WAR_SHIP, FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP],
      hit: FIGURE_SOUND_SHIP, die: FIGURE_SOUND_SHIP }
    { types: [FIGURE_TRANSPORT_SHIP, FIGURE_ENEMY_TRANSPORT, FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP,
              FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP, FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP,
              FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP, FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP,
              FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP, FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP,
              FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP, FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP,
              FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP, FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP,
              FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP, FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP],
      die: FIGURE_SOUND_SHIP }
    { types: [FIGURE_MARKET_TRADER], die: FIGURE_SOUND_MARKET_TRADER_1 }
    { types: [FIGURE_HYENA], die: FIGURE_SOUND_HYENA, attack: FIGURE_SOUND_HYENA, click: FIGURE_SOUND_HYENA }
    { types: [FIGURE_LION], die: FIGURE_SOUND_LION, attack: FIGURE_SOUND_LION, click: FIGURE_SOUND_LION }
    { types: [FIGURE_SCORPION], die: FIGURE_SOUND_SCORPION, attack: FIGURE_SOUND_SCORPION, click: FIGURE_SOUND_SCORPION }
    { types: [FIGURE_ASP], die: FIGURE_SOUND_ASP, attack: FIGURE_SOUND_ASP, click: FIGURE_SOUND_ASP }
    { types: [FIGURE_OSTRICH], die: FIGURE_SOUND_OSTRICH, click: FIGURE_SOUND_OSTRICH }
    { types: [FIGURE_ANTELOPE], die: FIGURE_SOUND_ANTELOPE, click: FIGURE_SOUND_ANTELOPE }
    { types: [FIGURE_HIPPO], die: FIGURE_SOUND_HIPPO, attack: FIGURE_SOUND_HIPPO, click: FIGURE_SOUND_HIPPO }
    { types: [FIGURE_CROCODILE], die: FIGURE_SOUND_CROCODILE, attack: FIGURE_SOUND_CROCODILE, click: FIGURE_SOUND_CROCODILE }
    { types: [FIGURE_BIRDS], die: FIGURE_SOUND_BIRDS, click: FIGURE_SOUND_BIRDS }
  ]
}
