log_info("akhenaten: music started")

music = {
	menu_track: "setup"
	combat_long: "combat_long"
	combat_short: "combat_short"

	soundtracks : [
		{ key: "none", file:"" },
		{ key: "setup", file:"AUDIO/Music/Setup.mp3" },
		{ key: "combat_short", file:"AUDIO/Music/Battle.mp3" },
		{ key: "combat_long", file:"AUDIO/Music/Battle.mp3" },
		{ key: "city_0", file:"AUDIO/Music/Agbj.mp3" },
		{ key: "city_1", file:"AUDIO/Music/SPS.mp3" },
		{ key: "city_2", file:"AUDIO/Music/sthA.mp3" },
		{ key: "city_3", file:"AUDIO/Music/mAa-jb.mp3" },
		{ key: "city_4", file:"AUDIO/Music/Hapj-aA.mp3" },
		{ key: "city_5", file:"AUDIO/Music/SSTJ.mp3"} , 
		{ key: "city_6", file:"AUDIO/Music/DUST.mp3" },
		{ key: "city_7", file:"AUDIO/Music/Smr.mp3" },
		{ key: "city_8", file:"AUDIO/Music/ADVENT.mp3" },
		{ key: "city_9", file:"AUDIO/Music/ANKH.mp3" },
		{ key: "city_10", file:"AUDIO/Music/jAkb.mp3" },
		{ key: "city_11", file:"AUDIO/Music/rwD.mp3" },
		{ key: "city_12", file:"AUDIO/Music/M-TWR.mp3" },
		{ key: "city_13", file:"AUDIO/Music/JA.mp3" },
		{ key: "city_14", file:"AUDIO/Music/jrj-Hb-sd.mp3" },
		{ key: "city_15", file:"AUDIO/Music/M-SRF.mp3" },
		{ key: "city_16", file:"AUDIO/Music/WATJ.mp3" },
		{ key: "city_17", file:"AUDIO/Music/WAJ.mp3" },
		{ key: "city_18", file:"AUDIO/Music/OFFERING.mp3" },
		{ key: "city_19", file:"AUDIO/Music/RAIN.mp3" },
		{ key: "city_20", file:"AUDIO/Music/KHU.mp3" },
		{ key: "city_21", file:"AUDIO/Music/KHET.mp3" },
		{ key: "city_22", file:"AUDIO/Music/REKHIT.mp3" },
		{ key: "city_23", file:"AUDIO/Music/AMBER.mp3" },
		{ key: "city_24", file:"AUDIO/Music/Dd-m-ann.mp3" },
		{ key: "city_25", file:"AUDIO/Music/Daq.mp3" },
		{ key: "city_26", file:"AUDIO/Music/rwDt.mp3" },
		{ key: "city_28", file:"AUDIO/Music/LONGING.mp3" },
		{ key: "city_29", file:"AUDIO/Music/BENNU.mp3" },
		{ key: "city_30", file:"AUDIO/Music/NEFER.mp3" },
		{ key: "city_31", file:"AUDIO/Music/AMAKH.mp3" },
		{ key: "city_32", file:"AUDIO/Music/Geb.mp3" },
		{ key: "city_33", file:"AUDIO/Music/Khepera.mp3" },
		{ key: "city_34", file:"AUDIO/Music/Isis.mp3" },
		{ key: "city_35", file:"AUDIO/Music/Anquet.mp3" },
		{ key: "city_36", file:"AUDIO/Music/Sekhmet.mp3" },
		{ key: "city_37", file:"AUDIO/Music/Ra.mp3" },
		// Cleopatra major-plague ambients (AUDIO/Ambient/)
		{ key: "plague_locusts", file:"AUDIO/Ambient/Locusts.mp3" },
		{ key: "plague_frogs", file:"AUDIO/Ambient/Frogs.mp3" },
		{ key: "plague_hailstorm", file:"AUDIO/Ambient/Hailstorm.mp3" },
	]

	// City music by population tier. `pop` is the tier's lower bound; the first
	// tier also covers everything below it. On mission start / save load the game
	// picks a random track from the tier that differs from the current one.
	// Pools follow the tracks the original music.txt uses most for these ranges.
	music_populations : [
		{ pop:0,    tracks:["city_1", "city_2", "city_7", "city_20", "city_21", "city_37"] },
		{ pop:500,  tracks:["city_3", "city_11", "city_20", "city_21", "city_25", "city_32"] },
		{ pop:1000, tracks:["city_2", "city_11", "city_21", "city_22", "city_25", "city_32"] },
		{ pop:1500, tracks:["city_3", "city_7", "city_11", "city_12", "city_14", "city_22"] },
		{ pop:2000, tracks:["city_11", "city_12", "city_14", "city_29", "city_30", "city_31"] },
	]
}