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
    }
    building_size : 6
    // Spots 0-7 are stored on the first part, 8-15 on the second, 16-21 on the third.
    spots [
        { stage: 1, figure: FIGURE_CARPENTER, work: 500, script: "stage_1_carpenter" }
        { stage: 2, figure: FIGURE_CARPENTER, work: 700, script: "stage_2_carpenter" }
        { stage: 3, figure: FIGURE_CARPENTER, work: 400, script: "stage_3_carpenter" }
        { stage: 4, figure: FIGURE_STONEMASON, work: 600, script: "stages_4_5_stonemason" }
        { stage: 4, figure: FIGURE_STONEMASON, work: 800, script: "stages_4_to_6_stonemason" }
        { stage: 4, figure: FIGURE_STONEMASON, work: 400, script: "stage_4_stonemason" }
        { stage: 5, figure: FIGURE_STONEMASON, work: 600, script: "stages_4_5_stonemason" }
        { stage: 5, figure: FIGURE_STONEMASON, work: 800, script: "stages_4_to_6_stonemason" }
        { stage: 5, figure: FIGURE_STONEMASON, work: 1200, script: "stages_5_7_8_stonemason" }
        { stage: 6, figure: FIGURE_STONEMASON, work: 800, script: "stages_4_to_6_stonemason" }
        { stage: 7, figure: FIGURE_STONEMASON, work: 1200, script: "stages_5_7_8_stonemason" }
        { stage: 7, figure: FIGURE_STONEMASON, work: 650, script: "stages_7_to_9_stonemason" }
        { stage: 7, figure: FIGURE_CARPENTER, work: 600, script: "stage_7_carpenter" }
        { stage: 8, figure: FIGURE_STONEMASON, work: 650, script: "stages_7_to_9_stonemason" }
        { stage: 8, figure: FIGURE_STONEMASON, work: 1200, script: "stages_5_7_8_stonemason" }
        { stage: 9, figure: FIGURE_STONEMASON, work: 650, script: "stages_7_to_9_stonemason" }
        { stage: 10, figure: FIGURE_STONEMASON, work: 650, script: "stage_10_stonemason" }
        { stage: 11, figure: FIGURE_STONEMASON, work: 900, script: "stage_11_stonemason" }
        { stage: 12, figure: FIGURE_STONEMASON, work: 500, script: "stage_12_stonemason" }
        { stage: 13, figure: FIGURE_STONEMASON, work: 400, script: "stage_13_stonemason" }
        { stage: 14, figure: FIGURE_CARPENTER, work: 540, script: "stage_14_carpenter" }
        { stage: 15, figure: FIGURE_STONEMASON, work: 450, script: "stage_15_stonemason" }
    ]
    // OG walker image group = id + 39.
    worker_images {
        carpenter_walk { pack: PACK_SPR_MAIN, id: 145, offset: 0, frames: 12, step: 8 }
        carpenter_work { pack: PACK_SPR_MAIN, id: 147, offset: 0, frames: 7, step: 8 }
        carpenter_work_2 { pack: PACK_SPR_MAIN, id: 148, offset: 0, frames: 7, step: 8 }
        carpenter_slide_down { pack: PACK_SPR_MAIN, id: 146, offset: 0, frames: 8, step: 1 }
        carpenter_slide_down_end { pack: PACK_SPR_MAIN, id: 146, offset: 7, frames: 1, step: 1 }
        carpenter_stand { pack: PACK_SPR_MAIN, id: 145, offset: 10, frames: 1, step: 1 }
        carpenter_climb_up { pack: PACK_SPR_MAIN, id: 149, offset: 0, frames: 12, step: 2 }
        stonemason_walk { pack: PACK_SPR_MAIN, id: 150, offset: 0, frames: 12, step: 8 }
        stonemason_work { pack: PACK_SPR_MAIN, id: 152, offset: 0, frames: 7, step: 8 }
        stonemason_slide_down { pack: PACK_SPR_MAIN, id: 151, offset: 0, frames: 8, step: 1 }
        stonemason_slide_down_end { pack: PACK_SPR_MAIN, id: 151, offset: 7, frames: 1, step: 1 }
        stonemason_block { pack: PACK_SPR_MAIN, id: 155, offset: 0, frames: 12, step: 8 }
        stonemason_work_2 { pack: PACK_SPR_MAIN, id: 153, offset: 0, frames: 7, step: 8 }
        stonemason_climb_up { pack: PACK_SPR_MAIN, id: 154, offset: 0, frames: 12, step: 2 }
    }
    // Coordinates are view N (S same, E/W mirror x). Choices are [sequence, reversed]; without next
    // the following sequence plays, without back the animation stops.
    anim_offset [189, 123]
    anim_scripts {
        stage_1_carpenter {
            sequences: [
                { from: [-403, -207], to: [-403, -207], anim: "carpenter_work", frames: 100 }
            ]
        }
        stage_2_carpenter {
            sequences: [
                { from: [-258, -142], to: [-258, -142], anim: "carpenter_work", frames: 50 }
                { from: [-258, -142], to: [-258, -142], anim: "carpenter_work_2", frames: 50 }
                { from: [-258, -142], to: [-238, -133], anim: "carpenter_walk", frames: 50 }
                { from: [-238, -133], to: [-238, -133], anim: "carpenter_work", frames: 50 }
                { from: [-238, -133], to: [-238, -133], anim: "carpenter_work_2", frames: 50 }
                { from: [-238, -133], to: [-221, -144], anim: "carpenter_walk", frames: 50 }
                { from: [-221, -144], to: [-221, -144], anim: "carpenter_work", frames: 50 }
                { from: [-221, -144], to: [-221, -144], anim: "carpenter_work_2", frames: 50 }
                { from: [-221, -144], to: [-197, -169], anim: "carpenter_walk", frames: 50 }
                { from: [-197, -169], to: [-197, -169], anim: "carpenter_work", frames: 50 }
                { from: [-197, -169], to: [-197, -169], anim: "carpenter_work_2", frames: 50 }
                { from: [-197, -169], to: [-175, -191], anim: "carpenter_walk", frames: 50 }
                { from: [-175, -191], to: [-175, -191], anim: "carpenter_work", frames: 50 }
                { from: [-175, -191], to: [-175, -191], anim: "carpenter_work_2", frames: 50 }
            ]
        }
        stage_3_carpenter {
            sequences: [
                { from: [-81, -96], to: [-81, -96], anim: "carpenter_work", frames: 50 }
                { from: [-81, -96], to: [-81, -96], anim: "carpenter_work_2", frames: 50 }
                { from: [-81, -96], to: [-57, -90], anim: "carpenter_walk", frames: 50 }
                { from: [-57, -90], to: [-57, -90], anim: "carpenter_work", frames: 50 }
                { from: [-57, -90], to: [-57, -90], anim: "carpenter_work_2", frames: 50 }
                { from: [-57, -90], to: [-42, -95], anim: "carpenter_walk", frames: 50 }
                { from: [-42, -95], to: [-42, -95], anim: "carpenter_work", frames: 50 }
                { from: [-42, -95], to: [-42, -95], anim: "carpenter_work_2", frames: 50 }
            ]
        }
        stage_4_stonemason {
            sequences: [
                { from: [-403, -207], to: [-403, -299], anim: "stonemason_walk", frames: 100, back: [[0, 0]] }
                { from: [-403, -299], to: [-388, -310], anim: "stonemason_walk", frames: 30, back: [[0, 1]] }
                { from: [-388, -310], to: [-386, -337], anim: "stonemason_walk", frames: 40, back: [[1, 1]] }
                { from: [-386, -337], to: [-363, -352], anim: "stonemason_walk", frames: 30, back: [[2, 1]] }
                { from: [-363, -352], to: [-363, -352], anim: "stonemason_work", frames: 100, next: [[4, 0], [5, 0], [4, 0], [3, 1]] }
                { from: [-363, -352], to: [-342, -338], anim: "stonemason_walk", frames: 50, next: [[5, 1], [6, 0], [5, 1]], back: [[4, 0]] }
                { from: [-342, -338], to: [-349, -227], anim: "stonemason_slide_down", frames: 8 }
                { from: [-349, -227], to: [-349, -227], anim: "stonemason_slide_down_end", frames: 200 }
            ]
        }
        stages_4_5_stonemason {
            sequences: [
                { from: [-250, -138], to: [-249, -228], anim: "stonemason_walk", frames: 100, back: [[7, 0]] }
                { from: [-249, -228], to: [-237, -235], anim: "stonemason_walk", frames: 40, back: [[0, 1]] }
                { from: [-237, -235], to: [-230, -250], anim: "stonemason_walk", frames: 40, back: [[1, 1]] }
                { from: [-230, -250], to: [-213, -266], anim: "stonemason_walk", frames: 40, back: [[2, 1]] }
                { from: [-213, -266], to: [-213, -277], anim: "stonemason_walk", frames: 40, back: [[3, 1]] }
                { from: [-213, -277], to: [-204, -300], anim: "stonemason_walk", frames: 40, back: [[4, 1]] }
                { from: [-204, -300], to: [-175, -283], anim: "stonemason_work", frames: 200, next: [[6, 1], [5, 1], [6, 1], [6, 1]], back: [[6, 0]] }
                { from: [-250, -138], to: [-250, -138], anim: "stonemason_block", frames: 100, stop: true }
            ]
        }
        stages_4_to_6_stonemason {
            sequences: [
                { from: [-71, -93], to: [-69, -126], anim: "stonemason_walk", frames: 100, next: [[1, 0], [5, 1]], back: [[6, 0]] }
                { from: [-69, -126], to: [-64, -142], anim: "stonemason_walk", frames: 100, back: [[0, 0]] }
                { from: [-64, -142], to: [-64, -142], anim: "stonemason_work", frames: 100, next: [[3, 0], [1, 1]] }
                { from: [-64, -142], to: [-41, -129], anim: "stonemason_walk", frames: 100 }
                { from: [-41, -129], to: [-41, -129], anim: "stonemason_work", frames: 100, next: [[3, 1], [5, 0], [3, 1], [3, 1]] }
                { from: [-41, -129], to: [-69, -126], anim: "stonemason_walk", frames: 100, next: [[0, 1]], back: [[4, 0]] }
                { from: [-71, -93], to: [-71, -93], anim: "stonemason_block", frames: 100 }
            ]
        }
        stage_7_carpenter {
            sequences: [
                { from: [-482, -263], to: [-482, -263], anim: "carpenter_work", frames: 50, next: [[1, 0], [11, 1]] }
                { from: [-482, -263], to: [-448, -244], anim: "carpenter_walk", frames: 50, back: [[0, 0]] }
                { from: [-448, -244], to: [-448, -244], anim: "carpenter_work", frames: 50, next: [[1, 1], [3, 0], [12, 0]] }
                { from: [-448, -244], to: [-411, -239], anim: "carpenter_walk", frames: 50, back: [[2, 0]] }
                { from: [-411, -239], to: [-411, -239], anim: "carpenter_work", frames: 50, next: [[3, 1], [5, 0]] }
                { from: [-411, -239], to: [-388, -253], anim: "carpenter_walk", frames: 50, back: [[4, 0]] }
                { from: [-388, -253], to: [-388, -253], anim: "carpenter_work_2", frames: 50, next: [[5, 1], [7, 0]] }
                { from: [-388, -253], to: [-425, -270], anim: "carpenter_walk", frames: 50, back: [[6, 0]] }
                { from: [-425, -270], to: [-425, -270], anim: "carpenter_work_2", frames: 50, next: [[7, 1], [9, 0], [12, 1]] }
                { from: [-425, -270], to: [-453, -289], anim: "carpenter_walk", frames: 50, back: [[8, 0]] }
                { from: [-453, -289], to: [-453, -289], anim: "carpenter_work_2", frames: 50, next: [[9, 1], [11, 0]] }
                { from: [-453, -289], to: [-482, -263], anim: "carpenter_walk", frames: 50, next: [[0, 0]], back: [[10, 0]] }
                { from: [-448, -244], to: [-425, -270], anim: "carpenter_walk", frames: 50, next: [[8, 0]], back: [[2, 0]] }
            ]
        }
        stages_5_7_8_stonemason {
            sequences: [
                { from: [-250, -138], to: [-249, -228], anim: "stonemason_walk", frames: 100 }
                { from: [-249, -228], to: [-237, -235], anim: "stonemason_walk", frames: 40 }
                { from: [-237, -235], to: [-230, -250], anim: "stonemason_walk", frames: 40 }
                { from: [-230, -250], to: [-213, -266], anim: "stonemason_walk", frames: 40 }
                { from: [-213, -266], to: [-213, -277], anim: "stonemason_walk", frames: 40 }
                { from: [-213, -277], to: [-204, -300], anim: "stonemason_walk", frames: 40 }
                { from: [-204, -300], to: [-221, -296], anim: "stonemason_walk", frames: 70, next: [[11, 0]] }
                { from: [-221, -296], to: [-199, -319], anim: "stonemason_walk", frames: 70, next: [[12, 0]], back: [[11, 0]] }
                { from: [-199, -319], to: [-141, -355], anim: "stonemason_walk", frames: 70, next: [[13, 0]], back: [[12, 0]] }
                { from: [-141, -355], to: [-112, -373], anim: "stonemason_walk", frames: 70, next: [[14, 0]], back: [[13, 0]] }
                { from: [-112, -373], to: [-115, -413], anim: "stonemason_walk", frames: 70, next: [[15, 0]] }
                { from: [-221, -296], to: [-221, -296], anim: "stonemason_work", frames: 70, next: [[7, 0]] }
                { from: [-199, -319], to: [-199, -319], anim: "stonemason_work", frames: 70, next: [[7, 1], [8, 0]] }
                { from: [-141, -355], to: [-141, -355], anim: "stonemason_work", frames: 70, next: [[8, 1], [9, 0]] }
                { from: [-112, -373], to: [-112, -373], anim: "stonemason_work", frames: 70, next: [[9, 1], [10, 0]] }
                { from: [-115, -413], to: [-115, -413], anim: "stonemason_work", frames: 70, next: [[10, 1]] }
            ]
        }
        stages_7_to_9_stonemason {
            entry: [[0, 0], [7, 0]]
            sequences: [
                { from: [5, -65], to: [5, -65], anim: "stonemason_work", frames: 50 }
                { from: [5, -65], to: [-42, -101], anim: "stonemason_walk", frames: 35 }
                { from: [-42, -101], to: [-42, -101], anim: "stonemason_work", frames: 35 }
                { from: [-42, -101], to: [-126, -141], anim: "stonemason_walk", frames: 60 }
                { from: [-126, -141], to: [-126, -141], anim: "stonemason_work", frames: 35 }
                { from: [-126, -141], to: [5, -65], anim: "stonemason_walk", frames: 60 }
                { from: [5, -65], to: [65, -100], anim: "stonemason_walk", frames: 50, back: [[0, 0]] }
                { from: [65, -100], to: [65, -100], anim: "stonemason_work", frames: 50 }
                { from: [65, -100], to: [-7, -145], anim: "stonemason_walk", frames: 35 }
                { from: [-7, -145], to: [-7, -145], anim: "stonemason_work", frames: 35 }
                { from: [-7, -145], to: [-74, -194], anim: "stonemason_walk", frames: 60 }
                { from: [-74, -194], to: [-74, -194], anim: "stonemason_work", frames: 35 }
                { from: [-74, -194], to: [65, -100], anim: "stonemason_walk", frames: 60, next: [[13, 0]] }
            ]
        }
        stage_10_stonemason {
            sequences: [
                { from: [-363, -200], to: [-363, -200], anim: "stonemason_work", frames: 35 }
                { from: [-363, -200], to: [-342, -230], anim: "stonemason_walk", frames: 25 }
                { from: [-342, -230], to: [-342, -230], anim: "stonemason_work", frames: 35 }
                { from: [-342, -230], to: [-388, -253], anim: "stonemason_walk", frames: 30 }
                { from: [-388, -253], to: [-390, -306], anim: "stonemason_walk", frames: 50, back: [[10, 0]] }
                { from: [-390, -306], to: [-390, -306], anim: "stonemason_work", frames: 35 }
                { from: [-390, -306], to: [-415, -333], anim: "stonemason_walk", frames: 25, back: [[4, 1], [15, 0], [4, 1]] }
                { from: [-415, -333], to: [-415, -333], anim: "stonemason_work", frames: 35 }
                { from: [-415, -333], to: [-420, -359], anim: "stonemason_walk", frames: 25, back: [[6, 1]] }
                { from: [-420, -359], to: [-420, -359], anim: "stonemason_work", frames: 35, next: [[8, 1]] }
                { from: [-388, -253], to: [-411, -239], anim: "stonemason_walk", frames: 25 }
                { from: [-411, -239], to: [-411, -239], anim: "stonemason_work", frames: 35 }
                { from: [-411, -239], to: [-497, -271], anim: "stonemason_walk", frames: 50 }
                { from: [-497, -271], to: [-497, -271], anim: "stonemason_work", frames: 35 }
                { from: [-497, -271], to: [-363, -200], anim: "stonemason_walk", frames: 70, next: [[0, 0]] }
                { from: [-390, -306], to: [-388, -253], anim: "stonemason_slide_down", frames: 8 }
                { from: [-388, -253], to: [-388, -253], anim: "stonemason_slide_down_end", frames: 50 }
            ]
        }
        stage_11_stonemason {
            unmirrored: true
            sequences: [
                { from: [-260, -179], to: [-260, -179], anim: "stonemason_work", frames: 40 }
                { from: [-260, -179], to: [-201, -151], anim: "stonemason_walk", frames: 50 }
                { from: [-201, -151], to: [-201, -151], anim: "stonemason_work", frames: 40 }
                { from: [-201, -151], to: [-133, -189], anim: "stonemason_walk", frames: 40 }
                { from: [-133, -189], to: [-127, -242], anim: "stonemason_walk", frames: 40 }
                { from: [-127, -242], to: [-127, -242], anim: "stonemason_work", frames: 40 }
                { from: [-127, -242], to: [-155, -291], anim: "stonemason_walk", frames: 40 }
                { from: [-155, -291], to: [-155, -291], anim: "stonemason_work", frames: 40 }
                { from: [-155, -291], to: [-180, -282], anim: "stonemason_walk", frames: 20, next: [[9, 0], [19, 0], [9, 0], [9, 0]] }
                { from: [-180, -282], to: [-180, -282], anim: "stonemason_work", frames: 40, next: [[10, 0], [19, 0], [10, 0]] }
                { from: [-180, -282], to: [-155, -291], anim: "stonemason_walk", frames: 20 }
                { from: [-155, -291], to: [-138, -383], anim: "stonemason_walk", frames: 60, next: [[12, 0], [17, 0], [12, 0]] }
                { from: [-138, -383], to: [-138, -383], anim: "stonemason_work", frames: 40, next: [[13, 0], [17, 0], [13, 0]] }
                { from: [-138, -383], to: [-88, -326], anim: "stonemason_walk", frames: 30, next: [[14, 0], [15, 0], [14, 0], [14, 0]] }
                { from: [-88, -326], to: [-88, -326], anim: "stonemason_work", frames: 40 }
                { from: [-88, -326], to: [-84, -202], anim: "stonemason_slide_down", frames: 8 }
                { from: [-84, -202], to: [-84, -202], anim: "stonemason_slide_down_end", frames: 60, next: [[0, 0]] }
                { from: [-138, -383], to: [-133, -189], anim: "stonemason_slide_down", frames: 8 }
                { from: [-133, -189], to: [-133, -189], anim: "stonemason_slide_down_end", frames: 60, next: [[0, 0]] }
                { from: [-180, -282], to: [-201, -151], anim: "stonemason_slide_down", frames: 8 }
                { from: [-201, -151], to: [-201, -151], anim: "stonemason_slide_down_end", frames: 60 }
            ]
        }
        stage_12_stonemason {
            entry: [[4, 0]]
            sequences: [
                { from: [5, -65], to: [5, -65], anim: "stonemason_work", frames: 50, next: [[5, 0]] }
                { from: [-42, -101], to: [5, -65], anim: "stonemason_walk", frames: 30, next: [[0, 0]] }
                { from: [-42, -101], to: [-42, -101], anim: "stonemason_work", frames: 50, next: [[1, 0]] }
                { from: [-126, -141], to: [-42, -101], anim: "stonemason_walk", frames: 40, next: [[2, 0]] }
                { from: [-126, -141], to: [-126, -141], anim: "stonemason_work", frames: 50, next: [[3, 0]] }
                { from: [5, -65], to: [65, -100], anim: "stonemason_walk", frames: 30 }
                { from: [65, -100], to: [65, -100], anim: "stonemason_work", frames: 50 }
                { from: [65, -100], to: [-33, -160], anim: "stonemason_walk", frames: 40 }
                { from: [-33, -160], to: [-33, -160], anim: "stonemason_work", frames: 50 }
                { from: [-33, -160], to: [-74, -194], anim: "stonemason_walk", frames: 35 }
                { from: [-74, -194], to: [-74, -194], anim: "stonemason_work", frames: 50 }
                { from: [-74, -194], to: [-126, -141], anim: "stonemason_walk", frames: 35, next: [[4, 0]] }
            ]
        }
        stage_13_stonemason {
            sequences: [
                { from: [-501, -260], to: [-501, -260], anim: "stonemason_work", frames: 50 }
                { from: [-501, -260], to: [-463, -241], anim: "stonemason_walk", frames: 30 }
                { from: [-463, -241], to: [-463, -241], anim: "stonemason_work", frames: 50 }
                { from: [-463, -241], to: [-416, -221], anim: "stonemason_walk", frames: 30 }
                { from: [-416, -221], to: [-416, -221], anim: "stonemason_work", frames: 50 }
                { from: [-416, -221], to: [-373, -265], anim: "stonemason_walk", frames: 40 }
                { from: [-373, -265], to: [-373, -265], anim: "stonemason_work", frames: 50 }
                { from: [-373, -265], to: [-460, -303], anim: "stonemason_walk", frames: 50 }
                { from: [-460, -303], to: [-436, -325], anim: "stonemason_walk", frames: 20 }
            ]
        }
        stage_14_carpenter {
            sequences: [
                { from: [-194, -104], to: [-191, -270], anim: "carpenter_walk", frames: 80 }
                { from: [-191, -270], to: [-161, -266], anim: "carpenter_walk", frames: 10 }
                { from: [-161, -266], to: [-161, -266], anim: "carpenter_work_2", frames: 40 }
                { from: [-161, -266], to: [-161, -266], anim: "carpenter_work", frames: 40 }
                { from: [-161, -266], to: [-178, -274], anim: "carpenter_walk", frames: 10 }
                { from: [-178, -274], to: [-178, -274], anim: "carpenter_work", frames: 40 }
                { from: [-178, -274], to: [-178, -274], anim: "carpenter_work_2", frames: 40 }
                { from: [-178, -274], to: [-191, -270], anim: "carpenter_walk", frames: 15 }
                { from: [-84, -174], to: [-84, -174], anim: "carpenter_work_2", frames: 40 }
                { from: [-84, -174], to: [-84, -174], anim: "carpenter_work", frames: 40 }
                { from: [-84, -174], to: [-48, -219], anim: "carpenter_walk", frames: 40 }
                { from: [-48, -219], to: [-57, -271], anim: "carpenter_walk", frames: 50 }
                { from: [-57, -271], to: [-71, -266], anim: "carpenter_walk", frames: 15, next: [[14, 0]] }
                { from: [-71, -266], to: [-71, -266], anim: "carpenter_work", frames: 40, stop: true }
                { from: [-71, -266], to: [-71, -266], anim: "carpenter_work_2", frames: 40 }
            ]
        }
        stage_15_stonemason {
            sequences: [
                { from: [-157, -91], to: [-157, -91], anim: "stonemason_work", frames: 50 }
                { from: [-157, -91], to: [-88, -59], anim: "stonemason_walk", frames: 50 }
                { from: [-88, -59], to: [-88, -59], anim: "stonemason_work", frames: 50 }
                { from: [-88, -59], to: [-7, -76], anim: "stonemason_walk", frames: 50 }
                { from: [-7, -76], to: [24, -110], anim: "stonemason_walk", frames: 40 }
                { from: [24, -110], to: [24, -110], anim: "stonemason_work", frames: 50 }
                { from: [24, -110], to: [16, -141], anim: "stonemason_walk", frames: 40 }
                { from: [16, -141], to: [3, -150], anim: "stonemason_walk", frames: 10 }
                { from: [3, -150], to: [3, -150], anim: "stonemason_work", frames: 80 }
                { from: [3, -150], to: [48, -172], anim: "stonemason_walk", frames: 30 }
            ]
        }
    }
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
