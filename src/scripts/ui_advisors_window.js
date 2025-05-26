log_info("akhenaten: ui advisors window started")

advisors_window = {
    ui : {
        background      : { type : "image", pack:PACK_UNLOADED, id:11, pos : {x:sw(-1024)/2, y:sh(-768)/2}  },
        layout          : { type : "image", pack:PACK_GENERAL, id:160, pos : {x:sw(-640)/2, y:sh(400)/2}    },
        labor_btn       : { type : "image_button", pos: {x:sw(-640)/2 + 12, y:sh(418)/2}, size:[33, 32], pack:PACK_GENERAL, id:159, offset:0, tooltip:[68, 71] },
        military_btn    : { type : "image_button", pos: {x:sw(-640)/2 + 52, y:sh(418)/2}, size:[39, 32], pack:PACK_GENERAL, id:159, offset:4, tooltip:[68, 72] },
        imperial_btn    : { type : "image_button", pos: {x:sw(-640)/2 + 96, y:sh(418)/2}, size:[34, 32], pack:PACK_GENERAL, id:159, offset:8, tooltip:[68, 73] },
        ratings_btn     : { type : "image_button", pos: {x:sw(-640)/2 + 135, y:sh(418)/2}, size:[38, 32], pack:PACK_GENERAL, id:159, offset:12, tooltip:[68, 74] },
        trade_btn       : { type : "image_button", pos: {x:sw(-640)/2 + 178, y:sh(418)/2}, size:[46, 32], pack:PACK_GENERAL, id:159, offset:16, tooltip:[68, 75] },
        population_btn  : { type : "image_button", pos: {x:sw(-640)/2 + 229, y:sh(418)/2}, size:[48, 32], pack:PACK_GENERAL, id:159, offset:20, tooltip:[68, 76] },
        health_btn      : { type : "image_button", pos: {x:sw(-640)/2 + 282, y:sh(418)/2}, size:[35, 32], pack:PACK_GENERAL, id:159, offset:24, tooltip:[68, 77] },
        education_btn   : { type : "image_button", pos: {x:sw(-640)/2 + 322, y:sh(418)/2}, size:[38, 32], pack:PACK_GENERAL, id:159, offset:28, tooltip:[68, 78] },
        entertainment_btn: { type : "image_button", pos: {x:sw(-640)/2 + 363, y:sh(418)/2}, size:[39, 32], pack:PACK_GENERAL, id:159, offset:32, tooltip:[68, 79] },
        religion_btn    : { type : "image_button", pos: {x:sw(-640)/2 + 406, y:sh(418)/2}, size:[35, 32], pack:PACK_GENERAL, id:159, offset:36, tooltip:[68, 80] },
        financial_btn   : { type : "image_button", pos: {x:sw(-640)/2 + 445, y:sh(418)/2}, size:[40, 32], pack:PACK_GENERAL, id:159, offset:40, tooltip:[68, 81] },
        chief_btn       : { type : "image_button", pos: {x:sw(-640)/2 + 490, y:sh(418)/2}, size:[46, 32], pack:PACK_GENERAL, id:159, offset:44, tooltip:[68, 82] },
        monuments_btn   : { type : "image_button", pos: {x:sw(-640)/2 + 542, y:sh(418)/2}, size:[40, 32], pack:PACK_GENERAL, id:159, offset:48, tooltip:[68, 83] },
        back_btn        : { type : "image_button", pos: {x:sw(-640)/2 + 588, y:sh(418)/2}, size:[40, 32], pack:PACK_GENERAL, id:159, offset:52, tooltip:[68, 84] },
    }
}