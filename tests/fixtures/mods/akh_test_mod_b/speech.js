log_info("akhenaten: speech started")
log_info("[test-marker] akh_test_mod_b speech.js override")

// Fixture for tests/331_mods_order.js: clashes with akh_test_mod/speech.js; this mod sorts later, so it wins.
akh_test_mod_speech = "mod_b"

speech = {
	// Paths under AUDIO/ accepted as-is by speech_play. Bare filenames fall
	// back to walker_dir (figure click phrases).
	dirs: [
		"Wavs/",
		"Voice/Mission/",
		"Voice/Walker/",
	]
	walker_dir: "Voice/Walker/"
}
