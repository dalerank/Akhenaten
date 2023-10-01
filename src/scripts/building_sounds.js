log_info("Ozymandias: building sounds started")

var g_building_sounds = [
  { type: "tax_collector", 						sound: "wavs/taxfarm.wav"},
  { type: "palace", 									sound: "wavs/palace.wav"},
  { type: "garden",										sound: "wavs/park1.wav"}
]

for (var i in g_building_sounds) {
  var conf = g_building_sounds[i]
	sound_system_building_info(conf.type, conf.sound)
}
