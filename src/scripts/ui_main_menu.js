log_info("akhenaten: main menu started")

function main_menu_local_build_number() {
	var v = game.version
	var marker = " b"
	var i = v.indexOf(marker)
	if (i < 0) {
		return 0
	}
	return parseInt(v.substring(i + marker.length)) || 0
}

function main_menu_dismiss_update(window) {
	window.update_panel.enabled = false
	window.update_game.enabled = false
	window.new_version.enabled = false
	window.recent_commits.enabled = false
	window.update_later.enabled = false
	window.update_status.enabled = false
}

function main_menu_update_now(window) {
	if (window.update_game.readonly) {
		return
	}
	if (__platform_can_auto_update()) {
		window.update_status.text = "Downloading update..."
	} else {
		window.update_status.text = "Opening download page..."
	}
	window.update_status.enabled = true
	// Empty URL → C++ picks the platform nightly artifact (Win/Linux/macOS).
	__game_download_latest_version("")
}

[es=window]
window_main_menu {
	ui {
		background    : { type:"background", path:"pharaoh_unloaded/title_00001" }

		continue_game : large_button({ pos:mbutton(0), size[256, 25], text[13, 5] })
		select_player : large_button({ pos:mbutton(1), size[256, 25], text[30, 0] })
		show_records  : large_button({ pos:mbutton(2), size[256, 25], text[30, 5] })
		show_config   : large_button({ pos:mbutton(3), size[256, 25], text[2,  0] })
		show_mods     : large_button({ pos:mbutton(4), size[256, 25], text:"#main_menu_mods" })
		show_editor   : large_button({ pos:mbutton(5), size[256, 25], text:"#main_menu_editor" })
		quit_game     : large_button({ pos:mbutton(6), size[256, 25], text[30, 4] })

		discord 	  : image_button({ pos[sw(-100), sh(-50)], size[48, 48], icon_texture:"!discord", scale:0.75 })

		patreon 	  : image_button({ pos[sw(-50), sh(-50)], size[48, 48], icon_texture:":patreon_48.png", scale:0.75 })
		version_number: text({pos[18, sh(-30)], text: game.version, font: FONT_SMALL_PLAIN, color: 0xffb3b3b3})

		update_panel  : outer_panel({ size[20, 27], enabled:false,
			ui {
				update_game : large_button({ pos[32, 16], size[256, 25], text:"update now", enabled: false })
				update_later : large_button({ pos[32, 48], size[256, 25], text:"later", enabled: false })
				new_version : text({pos[18, 84], text: game.version, font: FONT_SMALL_PLAIN, enabled: false})
				update_status : text({pos[18, 104], size[280, 20], text:"", font: FONT_SMALL_PLAIN, enabled: false})
				recent_commits : text({pos[18, 124], size[280, 280], wrap:px(17), rich:true, text:"Loading recent commits...", font: FONT_SMALL_PLAIN, enabled: false, clip_area: true})
			}
		})
	}
}

function main_menu_can_continue() {
	var last_save = normalize_savegame_path_for_load(game_features.gameopt_last_save_filename)
	var last_player = game_features.gameopt_last_player
	if (!last_save || !last_player) {
		return false
	}
	return __game_file_exists(last_save)
}

[es=(window_main_menu, continue_game)]
function main_menu_continue_game(window) {
	var last_save = normalize_savegame_path_for_load(game_features.gameopt_last_save_filename)
    var last_player = game_features.gameopt_last_player
    if (last_save && last_player) {
        game_features.gameopt_player_name = last_player
        if (__game_load_savegame(last_save)) {
            ui.window_city_show()
        }
    }
}

[es=(window_main_menu, quit_game)]
function main_menu_quit_game(window) {
    ui.show_yesno("#popup_dialog_quit", function() {
		emit event_request_exit{ value: true }
	})
}

[es=(window_main_menu, show_editor)]
function main_menu_start_editor(window) {
    game.init_editor()
}

[es=event_show_main_menu]
function main_menu_on_show(ev) {
    if (ev.play_intro) {
        __game_sound.play_intro()
    }

    game_mission_options_locked = false
    window_show_by_id("window_main_menu")
}

[es=(window_main_menu, select_player)]
function main_menu_on_select_player(window) {
	emit event_show_window{ id: "window_player_selection" }
}

[es=(window_main_menu, show_records)]
function main_menu_on_show_records(window) {
	emit event_show_window{ id: "records_window" }
}

[es=(window_main_menu, show_config)]
function main_menu_on_show_config(window) {
	emit event_show_window{ id: "window_features" }
}

[es=(window_main_menu, show_mods)]
function main_menu_on_show_mods(window) {
	emit event_show_window{ id: "mods_window" }
}

[es=(window_main_menu, discord)]
function main_menu_on_discord(window) {
	__platform_open_url("https://discord.gg/HS4njmBvpb")
}

[es=(window_main_menu, patreon)]
function main_menu_on_patreon(window) {
	__platform_open_url("https://www.patreon.com/imspinner")
}

[es=(window_main_menu, update_game)]
function main_menu_on_update_game(window) {
	main_menu_update_now(window_main_menu)
}

[es=(window_main_menu, update_later)]
function main_menu_on_update_later(window) {
	main_menu_dismiss_update(window_main_menu)
}

[es=(window_main_menu, init)]
function main_menu_on_init(window) {
    log_info("[test-marker] main_menu_shown")

    __sound_city_stop()
    __sound_city_init()

    window.continue_game.readonly = !main_menu_can_continue()

	if (!game.is_integral_tests && github_is_active()) {
		github_get_recent_commits_async("dalerank", "Akhenaten")
		github_get_total_commits_async("dalerank", "Akhenaten")
	}
}

[es=(window_main_menu, update_recent_commits)]
function main_menu_on_update_recent_commits(window) {
	window.recent_commits.text = window.commits
	window.recent_commits.enabled = true
}

[es=(window_main_menu, update_version)]
function main_menu_on_update_version(window) {
	log_info("main_menu_download_version: " + window.current_commit)
	if (window.current_commit <= 1)
		return

	var local_build = main_menu_local_build_number()
	var update_available = window.current_commit > local_build

	if (update_available && game_features.gameopt_last_game_version == window.current_commit)
		return

	window.update_panel.enabled = true
	window.new_version.enabled = true
	window.update_game.enabled = true
	window.recent_commits.enabled = true

	if (update_available) {
		window.update_game.readonly = false
		window.update_game.text = "update now"
		window.update_later.enabled = true
		window.new_version.text = "New build: " + window.current_commit + " (you have " + local_build + ")"
		game_features.gameopt_last_game_version = window.current_commit
	} else {
		window.update_game.readonly = true
		window.update_game.text = "Updated"
		window.update_later.enabled = false
		window.new_version.text = "Build " + local_build + " (up to date)"
	}
}

[es=event_github_totals_commits_loaded]
function main_menu_download_version(ev) {
	emit window_main_menu.update_version{ current_commit: ev.current_commit }
}

[es=event_github_recent_commits_loaded]
function main_menu_download_recent_commits(ev) {
	log_info("main_menu_download_recent_commits")
	emit window_main_menu.update_recent_commits{ commits: ev.commits }
}
