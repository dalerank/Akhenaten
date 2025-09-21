log_info("akhenaten: music started")

soundtracks = {
	none: { file:"" },
	setup: { file:"AUDIO/Music/Setup.mp3"},
	combat_short: { file:"AUDIO/Music/Battle.mp3"},
	combat_long: { file:"AUDIO/Music/Battle.mp3"},
	city_0: { file:"AUDIO/Music/Agbj.mp3"},
	city_1: { file:"AUDIO/Music/SPS.mp3"},
	city_2: { file:"AUDIO/Music/sthA.mp3"},
	city_3: { file:"AUDIO/Music/mAa-jb.mp3"},
	city_4: { file:"AUDIO/Music/Hapj-aA.mp3"},
	city_5: { file:"AUDIO/Music/SSTJ.mp3"}, 
	city_6: { file:"AUDIO/Music/DUST.mp3"},
	city_7: { file:"AUDIO/Music/Smr.mp3"},
	city_8: { file:"AUDIO/Music/ADVENT.mp3"},
	city_9: { file:"AUDIO/Music/ANKH.mp3"},
	city_10: { file:"AUDIO/Music/jAkb.mp3"},
	city_11: { file:"AUDIO/Music/rwD.mp3"},
	city_12: { file:"AUDIO/Music/M-TWR.mp3"},
	city_13: { file:"AUDIO/Music/JA.mp3"},
	city_14: { file:"AUDIO/Music/jrj-Hb-sd.mp3"},
	city_15: { file:"AUDIO/Music/M-SRF.mp3"},
	city_16: { file:"AUDIO/Music/WATJ.mp3"},
	city_17: { file:"AUDIO/Music/WAJ.mp3"},
	city_18: { file:"AUDIO/Music/OFFERING.mp3"},
	city_19: { file:"AUDIO/Music/RAIN.mp3"},
	city_20: { file:"AUDIO/Music/KHU.mp3"},
	city_21: { file:"AUDIO/Music/KHET.mp3"},
	city_22: { file:"AUDIO/Music/REKHIT.mp3"},
	city_23: { file:"AUDIO/Music/AMBER.mp3"},
	city_24: { file:"AUDIO/Music/Dd-m-ann.mp3"},
	city_25: { file:"AUDIO/Music/Daq.mp3"},
	city_26: { file:"AUDIO/Music/rwDt.mp3"},
	city_28: { file:"AUDIO/Music/LONGING.mp3"},
	city_29: { file:"AUDIO/Music/BENNU.mp3"},
	city_30: { file:"AUDIO/Music/NEFER.mp3"},
	city_31: { file:"AUDIO/Music/AMAKH.mp3"},
	city_32: { file:"AUDIO/Music/Geb.mp3"},
	city_33: { file:"AUDIO/Music/Khepera.mp3"},
	city_34: { file:"AUDIO/Music/Isis.mp3"},
	city_35: { file:"AUDIO/Music/Anquet.mp3"},
	city_36: { file:"AUDIO/Music/Sekhmet.mp3"},
	city_37: { file:"AUDIO/Music/Ra.mp3" },
}

music = {
	menu_track: "setup"
	combat_long: "combat_long"
	combat_short: "combat_short"
}

music_populations = [
	{ pop:1000, track:"city_1" },
	{ pop:2000, track:"city_2" },
	{ pop:5000, track:"city_3" },
	{ pop:7000, track:"city_4" },
	{ pop:99000, track:"city_5" },
]
