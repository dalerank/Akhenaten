#include "figuretype/festival_guy.h"

#include "core/random.h"
#include "city/city.h"
#include "city/buildings.h"

figure_festival_guy::static_params festival_guy_m;

void figure_festival_guy::update_animation() {
    building* temple = home();
    xstring animkey = {};
    switch (temple->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        animkey = "priest_osiris_walk";
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        animkey = "priest_ra_walk";
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        animkey = "priest_ptah_walk";
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        animkey = "priest_seth_walk";
        break;

    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        animkey = "priest_bast_walk";
        break;

    case BUILDING_JUGGLER_SCHOOL:
        animkey = "juggler_walk";
        break;
    case BUILDING_CONSERVATORY:
        animkey = "musician_walk";
        break;
    case BUILDING_DANCE_SCHOOL:
        animkey = "dancer_walk";

    default:
        assert(false);
    }

    image_set_animation(animkey);
}

void figure_festival_guy::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_10_FESTIVAL_GUY_CREATED:
        base.animctx.frame = 0;
        if (--base.wait_ticks <= 0) {
            advance_action(FIGURE_ACTION_11_FESTIVAL_GUY_GOTO_SQUARE);
        }
        break;

    case FIGURE_ACTION_11_FESTIVAL_GUY_GOTO_SQUARE:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_12_FESTIVAL_GUY_DANCE)) {
            base.wait_ticks = rand() % 20;
        }
        break;

    case FIGURE_ACTION_12_FESTIVAL_GUY_DANCE:
        if (--base.wait_ticks <= 0) {
            advance_action(FIGURE_ACTION_13_FESTIVAL_GUY_GOTO_HOME);
        }
        break;

    case FIGURE_ACTION_13_FESTIVAL_GUY_GOTO_HOME:
        do_gotobuilding(home());
        break;
    }
}

void figure_festival_guy::before_poof() {
    ; //
}