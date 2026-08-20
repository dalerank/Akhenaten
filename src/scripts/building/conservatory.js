log_info("akhenaten: building_conservatory started")

building_conservatory {
  animations {
    preview { pack:PACK_GENERAL, id:51 }
    base { pack:PACK_GENERAL, id:51 }
    work { pos[52, -18], pack:PACK_SPR_AMBIENT, id:10, max_frames:11, duration:4 }
  }

  spawn_interval : 10
  labor_category : LABOR_CATEGORY_ENTERTAINMENT
  overlay : OVERLAY_ENTERTAINMENT
  min_houses_coverage : 50
  meta { text_id:75, help_link:"message_building_trading_centers" }
  info_sound : "Wavs/music_school.wav"
  building_size : 3
  cost [ 20, 50, 90, 150, 200 ]
  desirability { value[-3], step[1], step_size[1], range[3] }
  laborers[8]
  fire_risk[4]
  damage_risk[2]
}
