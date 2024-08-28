#include "figuretype/figure_scriber.h"

#include "figure/service.h"
#include "js/js_game.h"

figures::model_t<figure_scriber> scriber_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_scriber);
void config_load_figure_scriber() {
    scriber_m.load();
}

void figure_scriber::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_125_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            advance_action(FIGURE_ACTION_126_ROAMER_RETURNING);
        }

        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
        ; // nothing here
        break;

    }
}

void academy_coverage(building* b, figure *f, int&) {
    b->data.house.academy = MAX_COVERAGE;
}

int figure_scriber::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, academy_coverage);
    return houses_serviced;
}

const animations_t &figure_scriber::anim() const {
    return scriber_m.anim;
}
