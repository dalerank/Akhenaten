log_info("akhenaten: building statue common started")

function statue_get_image(variants, orientation, variant) {
    var size = variants.length
    if (!size) {
        return 0
    }

    while (orientation < 0) { orientation += 4 }
    while (orientation > 3) { orientation -= 4 }

    while (variant < 0) { variant += 4 }
    while (variant > (size - 1)) { variant -= size }
    variant = variant % size

    var desc = variants[variant]
    var img = get_image({ pack: desc.pack, id: desc.id, offset: desc.offset + orientation })
    return img ? img.tid : 0
}

function statue_is_type(type) {
    return type == BUILDING_SMALL_STATUE || type == BUILDING_MEDIUM_STATUE || type == BUILDING_LARGE_STATUE
}

function statue_og_mode() {
    return !game_features.gameplay_change_statue_variants
}

// OG construction_ghost_statue: R steps one counter 0..15 from 0; its low two bits pick the image set
// (variant 0..3) and the rest the facing, so the planner's rotation is counter / 4.
function statue_og_advance() {
    var n = (city_planner.global_rotation * 4 + (city_planner.building_variant % 4) + 1) % 16
    city_planner.custom_building_variant = n % 4
    city_planner.global_rotation = Math.floor(n / 4)
}

function statue_setup_building_variant(variants) {
    if (statue_og_mode()) {
        city_planner.custom_building_variant = city_planner.building_variant % 4
        return
    }
    city_planner.custom_building_variant = Math.floor(Math.random() * variants.length)
}

function statue_next_building_variant(ev, variants) {
    if (statue_og_mode()) {
        statue_og_advance()
        return
    }
    var size = variants.length
    if (ev.variant < 0) {
        city_planner.custom_building_variant = 0
        return
    }
    if (!size) {
        city_planner.custom_building_variant = ev.variant
        return
    }
    city_planner.custom_building_variant = (ev.variant + 1) % size
}

// OG construction_ghost_statue: no floodplain, no figures, and (outside the editor) at least three tiles
// from the map edge.
function statue_ghost_allow_tile(ev) {
    var t = ev.tile
    var allowed = !terrain.is(t, TERRAIN_FLOODPLAIN) && !__map_has_figure_at(t)
    if (allowed && !game.editor_is_active()) {
        var w = __scenario_map.width
        var h = __scenario_map.height
        allowed = t.x >= 3 && t.y >= 3 && t.x < w - 3 && t.y < h - 3
    }
    city_planner.preview_allow_result = allowed
}

[es=(building_small_statue, ghost_allow_tile), es=(building_medium_statue, ghost_allow_tile), es=(building_large_statue, ghost_allow_tile)]
function statue_ghost_allow_tile_es(ev) {
    statue_ghost_allow_tile(ev)
}
