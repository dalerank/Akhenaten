log_info("akhenaten: figure festival_priest started")

[es=(figure_festival_priest, setup_phrase)]
function figure_festival_priest_setup_phrase(ev) {
    var f = city.get_figure(ev.fid)
    if (!f || !f.valid) {
        return
    }

    var home = f.home
    if (!home || !home.valid) {
        figure_apply_phrase(f, "empty")
        return
    }

    switch (home.type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        figure_apply_phrase(f, "osiris_god_love_festival")
        break
    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        figure_apply_phrase(f, "ra_god_love_festival")
        break
    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        figure_apply_phrase(f, "ptah_god_love_festival")
        break
    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        figure_apply_phrase(f, "seth_god_love_festival")
        break
    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        figure_apply_phrase(f, "bast_god_love_festival")
        break
    case BUILDING_JUGGLER_SCHOOL:
        figure_apply_phrase(f, "juggler_i_like_festivals")
        break
    case BUILDING_CONSERVATORY:
        figure_apply_phrase(f, "musician_i_like_festivals")
        break
    case BUILDING_DANCE_SCHOOL:
        figure_apply_phrase(f, "dancer_i_like_festivals")
        break
    default:
        figure_apply_phrase(f, "empty")
        break
    }
}
