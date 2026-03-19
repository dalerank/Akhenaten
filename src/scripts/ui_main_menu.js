log_info("akhenaten: main menu started")

main_menu_screen {
	ui {
		background    : { type:"background", path:"pharaoh_unloaded/title_00001" }

		continue_game : large_button({ pos:mbutton(0), size[256, 25], text[13, 5], onclick: main_menu_continue_game })
		select_player : large_button({ pos:mbutton(1), size[256, 25], text[30, 0], onclick: main_menu_show_window("window_player_selection") })
		show_records  : large_button({ pos:mbutton(2), size[256, 25], text[30, 5], onclick: main_menu_show_window("records_window") })
		show_config   : large_button({ pos:mbutton(3), size[256, 25], text[2,  0], onclick: main_menu_show_window("window_features") })
		show_mods     : large_button({ pos:mbutton(4), size[256, 25], text:"#main_menu_mods", onclick: main_menu_show_window("mods_window") })
		quit_game     : large_button({ pos:mbutton(5), size[256, 25], text[30, 4], onemit: main_menu_quit_game })

		discord 	  : image_button({ pos[sw(-100), sh(-50)], size[48, 48], icon_texture:"!discord", scale:0.75
							           	onclick: function() { __platform_open_url("https://discord.gg/HS4njmBvpb") }
		 							 })

		patreon 	  : image_button({ pos[sw(-50), sh(-50)], size[48, 48], icon_texture:":patreon_48.png", scale:0.75
			                            onclick: function() { __platform_open_url("https://www.patreon.com/imspinner") }
		                             })
		version_number: text({pos[18, sh(-30)], text: game.version, font: FONT_SMALL_PLAIN, color: 0xffb3b3b3})

		update_panel  : outer_panel({ size[20, 27], enabled:false,
			ui {
				update_game : large_button({ pos[32, 16], size[256, 25], text:"update now", enabled: false
					                         onclick: __game_download_latest_version
				                           })
				new_version : text({pos[18, 53], text: game.version, font: FONT_SMALL_PLAIN, enabled: false})
				changelog : text({pos[18, 73], size[560, 300], wrap:px(18), rich:true, text:"Loading changelog...", font: FONT_SMALL_PLAIN, enabled: false, clip_area: true})
			}
		})
	}
}

function main_menu_show_window(window_id) {
	return function() {
		emit event_show_window{ id:window_id }
	}
}

function main_menu_continue_game() {
	var last_save = game_features.gameopt_last_save_filename
    var last_player = game_features.gameopt_last_player
	log_info("main menu show" + last_player + " " + last_save)
    if (last_save && last_player) {
        __game_set_player_name(last_player)
        if (__game_load_savegame(last_save)) {
            ui.window_city_show()
        }
    }
}

function main_menu_quit_game() {
    ui.show_yesno("#popup_dialog_quit", function() {
		emit event_request_exit{ value: true }
	})
}

[es=(main_menu_screen, init)]
function main_menu_on_init(window) {
}

[es=event_totals_commits_loaded]
function main_menu_download_version(window) {
	log_info("main_menu_download_version: " + window.current_commit)
	if (window.current_commit <= 1)
		return

	if (game_features.gameopt_last_game_version == window.current_commit)
		return

	window.update_panel.enabled = true
	window.new_version.enabled = true
	window.update_game.enabled = true
	window.new_version.text = "" + window.current_commit

	game_features.gameopt_last_game_version = window.current_commit
}

[es=event_changelog_loaded]
function main_menu_download_changelog(window) {
	log_info("main_menu_download_changelog: " + window.change_log)
	window.changelog.text = window.change_log
	window.changelog.enabled = true
}