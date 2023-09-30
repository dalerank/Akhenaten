log_info("Ozymandias: mission sounds started")

for (var i = 0; i < 38; i++) {
	sound_system_mission_config(i,
		_format("Voice/Mission/{0}_mission.mp3", (i + 200).toString()),
		_format("Voice/Mission/{0}_victory.mp3", (i + 200).toString())
	)
}
