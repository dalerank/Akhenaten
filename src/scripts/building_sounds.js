log_info("Ozymandias: building sounds started")

var g_building_sounds = [
  { type: "tax_collector", 						sound: "wavs/taxfarm.wav"},
  { type: "palace", 									sound: "wavs/palace.wav"},
  { type: "garden",										sound: "wavs/park1.wav"},
  { type: "plaza", 										sound: "wavs/FANFARE1.wav"},
  { type: "statue", 									sound: "wavs/statue1.wav"},
  { type: "barley_farm", 							sound: "wavs/barleyfarm.wav"},
  { type: "flax_farm", 								sound: "wavs/flaxfarm.wav"},
  { type: "grain_farm",								sound: "wavs/farm1.wav"},
  { type: "lettuce_farm",							sound: "wavs/lettucefarm.wav"},
  { type: "pomegranades_farm",				sound: "wavs/pomfarm.wav"},
	{ type: "chickpeas_farm",						sound: "wavs/chickfarm.wav"},
	{ type: "figs_farm",								sound: "wavs/figs_farm.wav"},
	{ type: "henna_farm",								sound: "wavs/farm2.wav"},
]

for (var i in g_building_sounds) {
  var conf = g_building_sounds[i]
	sound_system_building_info(conf.type, conf.sound)
}
