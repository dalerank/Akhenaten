#include "figure_priest.h"

#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "figure/service.h"
#include "figuretype/figure_plagued_citizen.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_priest);

void figure_priest::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_priest::figure_action() {

}

int figure_priest::provide_service() {
    int houses_serviced = 0;
    switch (home()->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_osiris = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_ra = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_ptah = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_seth = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_BAST:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_bast = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_COMPLEX_BAST: {
        // Isis altar on Bast complex: clear infected houses + remove plagued walkers.
        building *main = home()->main();
        auto *complex = main ? main->dcast_temple_complex() : nullptr;
        const bool isis_altar = complex && complex->has_upgrade(etc_upgrade_altar);
        houses_serviced = figure_provide_service(tile(), &base, [isis_altar] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_bast = MAX_COVERAGE;
            }
            if (isis_altar && house) {
                building *main = &house->main()->base;
                if (main->has_plague) {
                    main->has_plague = false;
                    main->disease_days = 0;
                }
            }
        });
        if (isis_altar) {
            figure_plagued_citizen::cure_nearby(tile(), 1);
        }
        break;
    }

    default:
        break;
    }

    return houses_serviced;
}

e_overlay figure_priest::get_overlay() const {
    switch (home()->type) {
    case BUILDING_SHRINE_OSIRIS: case BUILDING_TEMPLE_OSIRIS: case BUILDING_TEMPLE_COMPLEX_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_SHRINE_RA: case BUILDING_TEMPLE_RA: case BUILDING_TEMPLE_COMPLEX_RA: return OVERLAY_RELIGION_RA;
    case BUILDING_SHRINE_PTAH: case BUILDING_TEMPLE_PTAH: case BUILDING_TEMPLE_COMPLEX_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_SHRINE_SETH: case BUILDING_TEMPLE_SETH: case BUILDING_TEMPLE_COMPLEX_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_SHRINE_BAST: case BUILDING_TEMPLE_BAST: case BUILDING_TEMPLE_COMPLEX_BAST: return OVERLAY_RELIGION_BAST;

    default:
        return OVERLAY_NONE;
    }
}

void figure_priest::update_animation() {
    building* temple = home();
    if (!temple->is_valid()) {
        return;
    }

    xstring animkey = {};
    switch (temple->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        animkey = "osiris_walk";
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        animkey = "ra_walk";
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        animkey = "ptah_walk";
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        animkey = "seth_walk";
        break;

    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        animkey = "bast_walk";
        break;

    default:
        return;
    }

    image_set_animation(animkey);
}

