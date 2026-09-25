log_info("akhenaten: speech started")

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
