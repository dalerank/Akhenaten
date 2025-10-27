log_info("akhenaten: main menu started")

main_menu_screen {
	ui {
		background    : { type:"background"; pack:PACK_UNLOADED, id:14, offset:0 }
		continue_game : large_button({ pos:mbutton(0), size[256, 25], text[13, 5]})
		select_player : large_button({ pos:mbutton(1), size[256, 25], text[30, 0], onclick: window_player_selection_show })
		show_records  : large_button({ pos:mbutton(2), size[256, 25], text[30, 5]})
		show_config   : large_button({ pos:mbutton(3), size[256, 25], text[2,  0]})
		show_mods     : large_button({ pos:mbutton(4), size[256, 25], text:"#main_menu_mods"})
		quit_game     : large_button({ pos:mbutton(5), size[256, 25], text[30, 4]})
		discord 	  : image_button({ pos[sw(-100), sh(-50)], size[48, 48], icon_texture:"!discord", scale:0.75 })
		patreon 	  : image_button({ pos[sw(-50), sh(-50)], size[48, 48], icon_texture:":patreon_48.png", scale:0.75 })
		version_number: text({pos[18, sh(-30)], text: game.version, font: FONT_SMALL_PLAIN, color: 0xffb3b3b3})

		update_panel  : outer_panel({size[20, 27], enabled:false,
			ui {
				update_game : large_button({ pos[32, 16], size[256, 25], text:"update now", enabled: false})
				new_version : text({pos[18, 53], text: game.version, font: FONT_SMALL_PLAIN, enabled: false})
			}
		})
	}
}