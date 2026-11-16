log_info("akhenaten: city sounds started")

city_sounds = [
  {c: SOUND_CHANNEL_CITY_HOUSE_SLUM,    p: "Ambient/HOUSING1.MP3"},
  {c: SOUND_CHANNEL_CITY_HOUSE_POOR,    p: "Ambient/HOUSING2.MP3"},
  {c: SOUND_CHANNEL_CITY_HOUSE_MEDIUM,  p: "Ambient/HOUSING3.MP3"},
  {c: SOUND_CHANNEL_CITY_HOUSE_GOOD,    p: "Ambient/HOUSING4.MP3"},
  {c: SOUND_CHANNEL_CITY_HOUSE_POSH,    p: "Ambient/HOUSING5.MP3"},
  {c: SOUND_CHANNEL_CITY_CLAY_PIT,      p: "Wavs/CLAY.WAV"},
  {c: SOUND_CHANNEL_CITY_BANDSTAND,     p: "Wavs/DANCE.WAV"},
  {c: SOUND_CHANNEL_CITY_DANCE_SCHOOL,  p: "Wavs/dance_school.wav"},
  {c: SOUND_CHANNEL_CITY_DOCK,          p: "Wavs/DOCK1.WAV"},
  {c: SOUND_CHANNEL_CITY_APOTHECARY,    p: "Wavs/DOCTOR.WAV"},
  {c: SOUND_CHANNEL_CITY_PHYSICIAN,     p: "Wavs/DOCTOR.WAV"},
  {c: SOUND_CHANNEL_CITY_DENTIST,      p: "Wavs/DOCTOR.WAV"},
  {c: SOUND_CHANNEL_CITY_MORTUARY,     p: "Wavs/EMBALM.WAV"},
  {c: SOUND_CHANNEL_CITY_ENGINEERS_POST, p: "Wavs/ENG.WAV"},
  {c: SOUND_CHANNEL_CITY_GRAIN_FARM,    p: "Wavs/wheatfarm.wav"},
  {c: SOUND_CHANNEL_CITY_FIG_FARM,      p: "Wavs/FIGFARM.WAV"},
  {c: SOUND_CHANNEL_CITY_GOLD_MINE,     p: "Wavs/GOLD.WAV"},
  {c: SOUND_CHANNEL_CITY_GRANARY,       p: "Wavs/GRANARY1.WAV"},
  {c: SOUND_CHANNEL_CITY_BOOTH,         p: "Wavs/JUGGLER.WAV"},
  {c: SOUND_CHANNEL_CITY_JUGGLER_SCHOOL, p: "Wavs/juggler_school.wav"},
  {c: SOUND_CHANNEL_CITY_HUNTER_LOUDGE, p: "Wavs/LO_HUNT.WAV"},
  {c: SOUND_CHANNEL_CITY_MARKET,        p: "Wavs/MARKET.WAV"},
  {c: SOUND_CHANNEL_CITY_CONSERVATORY,  p: "Wavs/MUSIC.WAV"},
  {c: SOUND_CHANNEL_CITY_PALACE,        p: "Wavs/palace.wav"},
  {c: SOUND_CHANNEL_CITY_POLICE,        p: "Wavs/POLICE.WAV"},
  {c: SOUND_CHANNEL_CITY_POTTERY_WORKSHOP, p: "Wavs/POTTERY.WAV"},
  {c: SOUND_CHANNEL_CITY_WEAPONS_WORKSHOP, p: "Wavs/weapon.wav"},
  {c: SOUND_CHANNEL_CITY_BREWERY_WORKSHOP, p: "Wavs/brewery.wav"},
  {c: SOUND_CHANNEL_CITY_WEAVER_WORKSHOP, p: "Wavs/weaver.wav"},
  {c: SOUND_CHANNEL_CITY_JEWELS_WORKSHOP, p: "Wavs/jewelry.wav"},
  {c: SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP, p: "Wavs/chariot.wav"},
  {c: SOUND_CHANNEL_CITY_ROCK,          p: "Ambient/ROCK.MP3"},
  {c: SOUND_CHANNEL_CITY_SHIPYARD,      p: "Wavs/SHIPYRD.WAV"},
  {c: SOUND_CHANNEL_CITY_SHRINE_BAST,   p: "Wavs/SHR_BAST.WAV"},
  {c: SOUND_CHANNEL_CITY_SHRINE_OSIRIS, p: "Wavs/shr_osiris.wav"},
  {c: SOUND_CHANNEL_CITY_SHRINE_PTAH,   p: "Wavs/SHR_PTAH.WAV"},
  {c: SOUND_CHANNEL_CITY_SHRINE_RA,     p: "Wavs/SHR_RA.WAV"},
  {c: SOUND_CHANNEL_CITY_SHRINE_SETH,   p: "Wavs/SHR_SETH.WAV"},
  {c: SOUND_CHANNEL_CITY_STATUE,        p: "Wavs/STATUE1.WAV"},
  {c: SOUND_CHANNEL_CITY_TAX_COLLECTOR, p: "Wavs/TAXFARM.WAV"},
  {c: SOUND_CHANNEL_CITY_TEMPLE_OSIRIS, p: "Wavs/tem_osiris_l.wav"},
  {c: SOUND_CHANNEL_CITY_TEMPLE_RA,     p: "Wavs/TEM_RA_L.WAV"},
  {c: SOUND_CHANNEL_CITY_TEMPLE_PTAH,   p: "Wavs/tem_ptah_l.wav"},
  {c: SOUND_CHANNEL_CITY_TEMPLE_SETH,   p: "Wavs/tem_seth_l.wav"},
  {c: SOUND_CHANNEL_CITY_TEMPLE_BAST,   p: "Wavs/tem_bast_l.wav"},
  {c: SOUND_CHANNEL_CITY_STORAGE_YARD,  p: "Wavs/warehouse1.wav"},
  {c: SOUND_CHANNEL_CITY_WELL,          p: "Wavs/WELL.WAV"},
  {c: SOUND_CHANNEL_CITY_BURNING_RUIN,  p: "Wavs/FIRE.WAV"},
  {c: SOUND_CHANNEL_CITY_WATER,         p: "Wavs/WATER1.WAV"},
  {c: SOUND_CHANNEL_CITY_CANAL,         p: "Wavs/WATER1.WAV"},
  {c: SOUND_CHANNEL_CITY_MEADOW,        p: "Ambient/MEADOW.MP3"},
  {c: SOUND_CHANNEL_CITY_FLOODPLAIN,    p: "Ambient/floodplain.mp3"},
  {c: SOUND_CHANNEL_CITY_MARSHLAND,     p: "Ambient/vegetation.mp3"},
  {c: SOUND_CHANNEL_CITY_CHICKFARM,     p: "Wavs/chickfarm.wav"},
  {c: SOUND_CHANNEL_CITY_COWFARM,       p: "Wavs/cowfarm_r.wav"},
  {c: SOUND_CHANNEL_CITY_LETTUCE_FARM,  p: "Wavs/lettucefarm.wav"},
  {c: SOUND_CHANNEL_CITY_ZOO,           p: "Wavs/zoo_r.wav"},
  {c: SOUND_CHANNEL_CITY_LAMP_WORKSHOP, p: "Wavs/lampmaker_r.wav"},
  {c: SOUND_CHANNEL_CITY_PAINT_WORKSHOP, p: "Wavs/paintmaker_r.wav"},
  {c: SOUND_CHANNEL_CITY_ARTISANS_GUILD, p: "Wavs/artisans_r.wav"},
]

// Enhanced city ambience (gameplay_enhanced_city_ambient): the samples above become positional voices.
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
