log_info("akhenaten: building_temple_ra started")

building_temple_ra {
    animations {
      preview { pack:PACK_GENERAL, id:21 }
      base { pack:PACK_GENERAL, id:21 }
      work { pos[80, -123], pack:PACK_GENERAL, id:21, offset:1, max_frames:11 }
    }

    min_houses_coverage : 50
    labor_category : LABOR_CATEGORY_RELIGION
    overlay : OVERLAY_RELIGION_RA
    sound_channel : SOUND_CHANNEL_CITY_TEMPLE_RA
    building_size : 3
    meta { text_id: 93, help_link:"message_building_shrine_and_temple" }
    info_sound : "Wavs/tem_RA_L.wav"
    cost [ 30, 50, 80, 150, 300 ]
    desirability { value[6], step[2], step_size[-2], range[6] }
    laborers[8]
    fire_risk[0]
    damage_risk[2]

    flags {
      is_temple: true
      is_religion: true
      keeps_visitor_paths: true
      draw_normal_anim: true
      work_anim: true
    }
}

[es=(building_temple_ra, spawn_figure)]
function building_temple_ra_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    if (!b.is_main) {
        return
    }
    b.common_spawn_roamer(FIGURE_PRIEST, b.params.min_houses_coverage, ACTION_125_ROAMER_ROAMING)
}

[es=(building_temple_ra, draw_usable_paths)]
function building_temple_ra_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
