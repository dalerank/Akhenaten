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
