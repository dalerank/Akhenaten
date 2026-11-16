log_info("akhenaten: speech started")
log_info("[test-marker] akh_test_mod speech.js override")

// Fixture: the same file as src/scripts/speech.js plus this global, so the override is visible.
akh_test_mod_speech = "mod"

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
