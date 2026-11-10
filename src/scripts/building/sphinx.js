log_info("akhenaten: building sphinx started")

building_sphinx {
    animations {
      s1a1 { pack:PACK_SPHINX_1_A, id:1 }
      s1a2 { pack:PACK_SPHINX_1_A, id:1, offset:1 }
      s1b1 { pack:PACK_SPHINX_1_B, id:1 }
      s1b2 { pack:PACK_SPHINX_1_B, id:1, offset:1 }
      s1c1 { pack:PACK_SPHINX_1_C, id:1 }
      s1c2 { pack:PACK_SPHINX_1_C, id:1, offset:1 }
      s2a1 { pack:PACK_SPHINX_2_A, id:1 }
      s2a2 { pack:PACK_SPHINX_2_A, id:1, offset:1 }
      s2b1 { pack:PACK_SPHINX_2_B, id:1 }
      s2b2 { pack:PACK_SPHINX_2_B, id:1, offset:1 }
      s2c1 { pack:PACK_SPHINX_2_C, id:1 }
      s2c2 { pack:PACK_SPHINX_2_C, id:1, offset:1 }
      s3a1 { pack:PACK_SPHINX_3_A, id:1 }
      s3a2 { pack:PACK_SPHINX_3_A, id:1, offset:1 }
      s3b1 { pack:PACK_SPHINX_3_B, id:1 }
      s3b2 { pack:PACK_SPHINX_3_B, id:1, offset:1 }
      s3c1 { pack:PACK_SPHINX_3_C, id:1 }
      s3c2 { pack:PACK_SPHINX_3_C, id:1, offset:1 }
      s4a1 { pack:PACK_SPHINX_4_A, id:1 }
      s4a2 { pack:PACK_SPHINX_4_A, id:1, offset:1 }
      s4b1 { pack:PACK_SPHINX_4_B, id:1 }
      s4b2 { pack:PACK_SPHINX_4_B, id:1, offset:1 }
      s4c1 { pack:PACK_SPHINX_4_C, id:1 }
      s4c2 { pack:PACK_SPHINX_4_C, id:1, offset:1 }
      s5a1 { pack:PACK_SPHINX_5_A, id:1 }
      s5a2 { pack:PACK_SPHINX_5_A, id:1, offset:1 }
      s5b1 { pack:PACK_SPHINX_5_B, id:1 }
      s5b2 { pack:PACK_SPHINX_5_B, id:1, offset:1 }
      s5c1 { pack:PACK_SPHINX_5_C, id:1 }
      s5c2 { pack:PACK_SPHINX_5_C, id:1, offset:1 }
      s6a1 { pack:PACK_SPHINX_6_A, id:1 }
      s6a2 { pack:PACK_SPHINX_6_A, id:1, offset:1 }
      s6b1 { pack:PACK_SPHINX_6_B, id:1 }
      s6b2 { pack:PACK_SPHINX_6_B, id:1, offset:1 }
      s6c1 { pack:PACK_SPHINX_6_C, id:1 }
      s6c2 { pack:PACK_SPHINX_6_C, id:1, offset:1 }
      preview { pack:PACK_SPHINX_1_A, id:1 }
      // OG work-spot walker groups (OG image group = id + 39)
      worker_carpenter_walk { pack:PACK_SPR_MAIN, id:145 }
      worker_carpenter_death { pack:PACK_SPR_MAIN, id:146 }
      worker_carpenter_work { pack:PACK_SPR_MAIN, id:147 }
      worker_carpenter_work2 { pack:PACK_SPR_MAIN, id:148 }
      worker_carpenter_climb { pack:PACK_SPR_MAIN, id:149 }
      worker_mason_walk { pack:PACK_SPR_MAIN, id:150 }
      worker_mason_death { pack:PACK_SPR_MAIN, id:151 }
      worker_mason_work { pack:PACK_SPR_MAIN, id:152 }
      worker_mason_work2 { pack:PACK_SPR_MAIN, id:153 }
      worker_mason_climb { pack:PACK_SPR_MAIN, id:154 }
      worker_mason_block { pack:PACK_SPR_MAIN, id:155 }
    }
    building_size : 6
    // OG sphinx_work_spots: spots 0-7 live on the first part, 8-15 on the second, 16-21 on the third.
    // A stage advances once every spot of that stage is worked down (1 work per worker per tick).
    spots [
        {
            stage: 1
            figure: FIGURE_CARPENTER
            work: 500
            script: 0
        }
        {
            stage: 2
            figure: FIGURE_CARPENTER
            work: 700
            script: 1
        }
        {
            stage: 3
            figure: FIGURE_CARPENTER
            work: 400
            script: 2
        }
        {
            stage: 4
            figure: FIGURE_STONEMASON
            work: 600
            script: 4
        }
        {
            stage: 4
            figure: FIGURE_STONEMASON
            work: 800
            script: 5
        }
        {
            stage: 4
            figure: FIGURE_STONEMASON
            work: 400
            script: 3
        }
        {
            stage: 5
            figure: FIGURE_STONEMASON
            work: 600
            script: 4
        }
        {
            stage: 5
            figure: FIGURE_STONEMASON
            work: 800
            script: 5
        }
        {
            stage: 5
            figure: FIGURE_STONEMASON
            work: 1200
            script: 7
        }
        {
            stage: 6
            figure: FIGURE_STONEMASON
            work: 800
            script: 5
        }
        {
            stage: 7
            figure: FIGURE_STONEMASON
            work: 1200
            script: 7
        }
        {
            stage: 7
            figure: FIGURE_STONEMASON
            work: 650
            script: 8
        }
        {
            stage: 7
            figure: FIGURE_CARPENTER
            work: 600
            script: 6
        }
        {
            stage: 8
            figure: FIGURE_STONEMASON
            work: 650
            script: 8
        }
        {
            stage: 8
            figure: FIGURE_STONEMASON
            work: 1200
            script: 7
        }
        {
            stage: 9
            figure: FIGURE_STONEMASON
            work: 650
            script: 8
        }
        {
            stage: 10
            figure: FIGURE_STONEMASON
            work: 650
            script: 9
        }
        {
            stage: 11
            figure: FIGURE_STONEMASON
            work: 900
            script: 10
        }
        {
            stage: 12
            figure: FIGURE_STONEMASON
            work: 500
            script: 11
        }
        {
            stage: 13
            figure: FIGURE_STONEMASON
            work: 400
            script: 12
        }
        {
            stage: 14
            figure: FIGURE_CARPENTER
            work: 540
            script: 13
        }
        {
            stage: 15
            figure: FIGURE_STONEMASON
            work: 450
            script: 14
        }
    ]
    // OG monument_anim_images, in ANIM_IMAGES_* order (the work-spot sequences index this list).
    worker_images [
        {
            // CARPENTER_WALK
            anim: "worker_carpenter_walk"
            offset: 0
            frames: 12
            step: 8
        }
        {
            // CARPENTER_WORK
            anim: "worker_carpenter_work"
            offset: 0
            frames: 7
            step: 8
        }
        {
            // CARPENTER_WORK_2
            anim: "worker_carpenter_work2"
            offset: 0
            frames: 7
            step: 8
        }
        {
            // CARPENTER_SLIDE_DOWN
            anim: "worker_carpenter_death"
            offset: 0
            frames: 8
            step: 1
        }
        {
            // CARPENTER_SLIDE_DOWN_END
            anim: "worker_carpenter_death"
            offset: 7
            frames: 1
            step: 1
        }
        {
            // CARPENTER_STAND
            anim: "worker_carpenter_walk"
            offset: 10
            frames: 1
            step: 1
        }
        {
            // CARPENTER_CLIMB_UP
            anim: "worker_carpenter_climb"
            offset: 0
            frames: 12
            step: 2
        }
        {
            // STONEMASON_WALK
            anim: "worker_mason_walk"
            offset: 0
            frames: 12
            step: 8
        }
        {
            // STONEMASON_WORK
            anim: "worker_mason_work"
            offset: 0
            frames: 7
            step: 8
        }
        {
            // STONEMASON_SLIDE_DOWN
            anim: "worker_mason_death"
            offset: 0
            frames: 8
            step: 1
        }
        {
            // STONEMASON_SLIDE_DOWN_END
            anim: "worker_mason_death"
            offset: 7
            frames: 1
            step: 1
        }
        {
            // STONEMASON_BLOCK
            anim: "worker_mason_block"
            offset: 0
            frames: 12
            step: 8
        }
        {
            // STONEMASON_WORK_2
            anim: "worker_mason_work2"
            offset: 0
            frames: 7
            step: 8
        }
        {
            // STONEMASON_CLIMB_UP
            anim: "worker_mason_climb"
            offset: 0
            frames: 12
            step: 2
        }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 21]
    meta { text_id: 178, help_link:"message_building_sphinx" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    planner_update_rule {
        unique_building: true
    }
    flags {
        is_monument: true
        non_deletable: true
    }
}
