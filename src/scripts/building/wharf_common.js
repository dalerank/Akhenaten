log_info("akhenaten: loading building_wharf_common")

function building_wharf_orient_suffix(image, base) {
    if (image == base) return "_n"
    if (image == base + 1) return "_w"
    if (image == base + 2) return "_s"
    return "_e"
}

function building_wharf_set_orient_animation(building, prefix) {
    var base = building.params.first_img("base")
    var image = __map_image_at(building.tile)
    building.set_animation(prefix + building_wharf_orient_suffix(image, base))
}

function building_wharf_update_graphic_moored(building, moored) {
    if (!building.play_animation) {
        building.set_animation("none")
        return
    }
    building_wharf_set_orient_animation(building, moored ? "work" : "wait")
}
