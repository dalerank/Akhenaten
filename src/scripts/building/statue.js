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

function statue_next_building_variant(ev, variants) {
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
