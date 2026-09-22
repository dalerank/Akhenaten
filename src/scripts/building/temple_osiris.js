log_info("akhenaten: building_temple_osiris started")

building_temple_osiris {
    animations {
      preview { pack:PACK_GENERAL, id:25 }
      base { pack:PACK_GENERAL, id:25 }
      work { pos[80, -125], pack:PACK_GENERAL, id:25, offset:1, max_frames:8 }
    }

    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    overlay : OVERLAY_RELIGION_OSIRIS
    sound_channel : SOUND_CHANNEL_CITY_TEMPLE_OSIRIS
    building_size : 3
    meta { text_id: 92, help_link:"message_building_shrine_and_temple" }
    info_sound : "Wavs/tem_osiris_l.wav"
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
      keeps_visitor_paths: true
    }
}

[es=(building_temple_osiris, draw_usable_paths)]
function building_temple_osiris_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
