log_info("akhenaten: ui terrain info started")

[es=event_classify_terrain_info]
function classify_terrain_info(ev) {
    var oi = city.object_info
    var tile = __map_tile_at_grid_offset(oi.grid_offset)
    var bid = oi.bid

    if (!bid && __map_is_bridge(tile)) {
        oi.terrain_type = terrain_info_bridge
    } else if (terrain.is_plaza_or_earthquake(tile)) {
        if (terrain.is(tile, TERRAIN_ROAD)) {
            oi.terrain_type = terrain_info_plaza
        }
        if (terrain.is(tile, TERRAIN_ROCK)) {
            oi.terrain_type = terrain_info_earthquake
        }
    } else if (terrain.is(tile, TERRAIN_TREE)) {
        oi.terrain_type = terrain_info_tree
    } else if (terrain.is(tile, TERRAIN_DIKE)) {
        oi.terrain_type = terrain_info_dike
    } else if (!bid && terrain.is(tile, TERRAIN_FLOODPLAIN)) {
        if (terrain.is(tile, TERRAIN_WATER)) {
            oi.terrain_type = terrain_info_floodplain_submerged
        } else if (terrain.is(tile, TERRAIN_ROAD)) {
            oi.terrain_type = terrain_info_road
        } else {
            oi.terrain_type = terrain_info_floodplain
        }
    } else if (terrain.is(tile, TERRAIN_MARSHLAND)) {
        oi.terrain_type = terrain_info_marshland
    } else if (terrain.is(tile, TERRAIN_DUNE)) {
        oi.terrain_type = terrain_info_dunes
    } else if (terrain.is(tile, TERRAIN_ROCK)) {
        if (oi.grid_offset === __city_map_entry_flag_offset()) {
            oi.terrain_type = terrain_info_entry_flag
        } else if (oi.grid_offset === __city_map_exit_flag_offset()) {
            oi.terrain_type = terrain_info_exit_flag
        } else if (terrain.is(tile, TERRAIN_ORE)) {
            oi.terrain_type = terrain_info_ore_rock
        } else {
            oi.terrain_type = terrain_info_rock
        }
    } else if (terrain.is(tile, TERRAIN_WATER) && !terrain.is(tile, TERRAIN_BUILDING)) {
        oi.terrain_type = terrain_info_water
    } else if (terrain.is(tile, TERRAIN_SHRUB)) {
        oi.terrain_type = terrain_info_shrub
    } else if (terrain.is(tile, TERRAIN_GARDEN)) {
        oi.terrain_type = terrain_info_garden
    } else if (terrain.is(tile, TERRAIN_ROAD) && !terrain.is(tile, TERRAIN_BUILDING)) {
        oi.terrain_type = terrain_info_road
    } else if (terrain.is(tile, TERRAIN_CANAL)) {
        oi.terrain_type = terrain_info_canal
    } else if (terrain.is(tile, TERRAIN_WALL)) {
        oi.terrain_type = (terrain.wall_material(tile) === WALL_MATERIAL_BRICK)
            ? terrain_info_brick_wall
            : terrain_info_mud_wall
    } else if (!bid && terrain.is(tile, TERRAIN_RUBBLE)) {
        oi.terrain_type = terrain_info_rubble
    } else {
        oi.terrain_type = terrain_info_empty
    }
}

terrain_info_window = {
    ui : {
        background    : outer_panel({size: [29, 20]}),
        title         : text({pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })

        button_help   : help_button({})
        button_close  : close_button({})
    }
}

[es=terrain_info_window]
terrain_info_empty {
    related_terrain [terrain_info_empty]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 20], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 42], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_road {
    related_terrain [terrain_info_road]
    help_id           : "message_game_concept_roads"
	ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[28, 5], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 42], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_road, init)]
function terrain_info_road_on_init(window) {
}

[es=terrain_info_window]
terrain_info_wall = {
    related_terrain [terrain_info_wall]
    help_id           : "message_building_defensive_structures"
    open_sounds       : [ "Wavs/ROCK1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[139, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[139, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_wall, init)]
function terrain_info_wall_on_init(window) {
}

[es=terrain_info_window]
terrain_info_mud_wall = {
    related_terrain [terrain_info_mud_wall]
    help_id           : "message_building_defensive_structures"
    open_sounds       : [ "Wavs/ROCK1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[139, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[139, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_mud_wall, init)]
function terrain_info_mud_wall_on_init(window) {
}

[es=terrain_info_window]
terrain_info_brick_wall = {
    related_terrain [terrain_info_brick_wall]
    help_id           : "message_building_defensive_structures"
    open_sounds       : [ "Wavs/ROCK1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[28, 168], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 59], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_brick_wall, init)]
function terrain_info_brick_wall_on_init(window) {
}

[es=terrain_info_window]
terrain_info_plaza = {
    related_terrain [terrain_info_plaza]
    help_id           : "message_building_garden_plaze_statue"
    open_sounds       : [ ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[137, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[137, 1], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_plaza, init)]
function terrain_info_plaza_on_init(window) {
}

[es=terrain_info_window]
terrain_info_ore_rock = {
    related_terrain [terrain_info_ore_rock]
    help_id           : "message_history_gold_and_gold_mining"
    open_sounds       : [  "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 26], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_ore_rock, init)]
function terrain_info_ore_rock_on_init(window) {
}

[es=terrain_info_window]
terrain_info_rock = {
    related_terrain [terrain_info_rock]
    help_id           : "message_history_gold_and_gold_mining"
    open_sounds       : [ "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 12], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 38], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_rock, init)]
function terrain_info_rock_on_init(window) {
}

[es=terrain_info_window]
terrain_info_floodplain {
    related_terrain [terrain_info_floodplain]
    help_id           : "message_tutorial_food_and_farming"
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 29], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
        basin_status  : text({pos: [30, 170], size: [px(26), 80], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_floodplain, init)]
function terrain_info_floodplain_on_init(window) {
    // 177:3 — river has subsided (dry floodplain). Submerged init overrides to 177:4.
    window.describe.text = __loc(177, 3)
    window.basin_status.text = terrain_info_format_basin_status_at_tile(
        __map_tile_at_grid_offset(window.grid_offset), true)

    if (floods_ui_enhanced_active()) {
        var extra = floods_ui_format_phase() + "\n" + floods_ui_format_next_line()
        if (window.basin_status.text && window.basin_status.text.length > 0) {
            window.basin_status.text = window.basin_status.text + "\n" + extra
        } else {
            window.basin_status.text = extra
        }
    }
}

// Same UI/init as dry floodplain — used while the tile is under water.
[es=terrain_info_window]
terrain_info_floodplain_submerged {
    related_terrain [terrain_info_floodplain_submerged]
    help_id           : "message_tutorial_food_and_farming"
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 29], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
        basin_status  : text({pos: [30, 170], size: [px(26), 80], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_floodplain_submerged, init)]
function terrain_info_floodplain_submerged_on_init(window) {
    terrain_info_floodplain_on_init(window)
    // 177:4 — will be fertile once the river subsides (tile currently under water).
    window.describe.text = __loc(177, 4)
}

[es=terrain_info_window]
terrain_info_water = {
    related_terrain [terrain_info_water]
    help_id           : "message_tutorial_food_and_farming"
    open_sounds       : [ "Wavs/WATER1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 13], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 39], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_water, init)]
function terrain_info_water_on_init(window) {
}

[es=terrain_info_window]
terrain_info_bridge {
    related_terrain [terrain_info_bridge]
    help_id           : "message_game_concept_water_crossings"
    open_sounds       : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 21], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 47], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_bridge, init)]
function terrain_info_bridge_on_init(window) {
}

[es=terrain_info_window]
terrain_info_tree = {
    related_terrain [terrain_info_tree]
    help_id           : "message_drinking_water"
    open_sounds       : [ ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[70, 11], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:[70, 43], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_tree, init)]
function terrain_info_tree_on_init(window) {
}

[es=terrain_info_window]
terrain_info_rubble {
    related_terrain [terrain_info_rubble]
    open_sounds [ "wavs/fire.wav" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], text:"${140.0}", size: [px(29), 20], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        warning_text  : text({debug_tag:1, pos: [0, 46], text:"no_text", size: [px(29), 20], wrap:px(29), align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT })
        subtitle      : text({pos: [30, 76], text:"${140.1}", size: [px(26), -1], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=(terrain_info_rubble, init)]
function terrain_info_rubble_on_init(window) {
    var rubble_type = __map_rubble_building_type_at_grid(window.grid_offset)
    window.warning_text.text = __loc(41, rubble_type)
}

[es=terrain_info_window]
terrain_info_canal {
    related_terrain [terrain_info_canal]
    help_id           : "message_game_concept_irrigation"
    open_sounds       : [ "Wavs/WATER1.WAV" ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:[141, 0], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=(terrain_info_canal, init)]
function terrain_info_canal_on_init(window) {
    var tile = __map_tile_at_grid_offset(window.grid_offset)
    // Dry canal images are begin+IMAGE_FULL_OFFSET(48)+…; wet are begin+0..47.
    var has_water = __map_canal_at(tile) && ((__map_image_at(tile) - terrain.canal_image_begin()) < 48)
    window.describe.text = __loc(141, has_water ? 1 : 2)
}

[es=terrain_info_window]
terrain_info_dike {
    related_terrain [terrain_info_dike]
    help_id           : "message_game_concept_irrigation"
    open_sounds       : [ ]
    ui : baseui(terrain_info_window, {
        title         : text({pos: [0, 16], size: [px(29), 13], text:"#building_dike", font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe      : text({pos: [30, 78], text:"#building_dike_info", font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
        basin_status  : text({pos: [30, 160], size: [px(26), 50], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

function terrain_info_format_basin_status_at_tile(tile, from_interior) {
    if (game_features.get('gameplay_enhanced_flood_basins') !== true) {
        return ""
    }

    var id = from_interior ? terrain.basin_id(tile) : terrain.basin_adjacent_id(tile)
    if (!id) {
        return from_interior ? "" : __loc("#terrain_dike_breached")
    }

    var area = __map_basin_area(id)
    var farms = __map_basin_farm_count(id)
    return __loc("#terrain_dike_sealed") + " — " + area + " " + __loc("#terrain_dike_tiles")
        + ", " + farms + " " + __loc("#terrain_dike_farms") + ". "
        + __loc("#terrain_dike_bonus_hint")
}

[es=(terrain_info_dike, init)]
function terrain_info_dike_on_init(window) {
    var tile = __map_tile_at_grid_offset(window.grid_offset)
    window.basin_status.text = terrain_info_format_basin_status_at_tile(tile, false)
}

[es=terrain_info_window]
terrain_info_marshland {
    related_terrain [terrain_info_marshland]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 31], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 57], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_dunes {
    related_terrain [terrain_info_dunes]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 32], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 58], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_shrub {
    related_terrain [terrain_info_shrub]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 14], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 40], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_entry_flag {
    related_terrain [terrain_info_entry_flag]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 24], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 50], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_exit_flag {
    related_terrain [terrain_info_exit_flag]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 25], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 51], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}

[es=terrain_info_window]
terrain_info_earthquake {
    related_terrain [terrain_info_earthquake]
    open_sounds     : [ "Wavs/DESERT1.WAV" ]
    ui : baseui(terrain_info_window, {
        title    : text({pos: [0, 16], size: [px(29), 13], text:[70, 15], font:FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe : text({pos: [30, 78], text:[70, 41], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(26) })
    })
}
