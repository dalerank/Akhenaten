log_info("Ozymandias: mission sounds started")

for (var i = 0; i < 38; i++) {
	mission_sounds[i] = {
		mission: i,
		briefing: _format("Voice/Mission/{0}_mission.mp3", (i + 200).toString()),
		victory: _format("Voice/Mission/{0}_victory.mp3", (i + 200).toString())
	}
}
