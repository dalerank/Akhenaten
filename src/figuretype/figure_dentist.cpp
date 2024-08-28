#include "figuretype/figure_dentist.h"

#include "figure/service.h"
#include "js/js_game.h"

figures::model_t<figure_dentist> fdentist_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_dentist);
void config_load_figure_dentist() {
    fdentist_m.load();
}

void figure_dentist::figure_action() {
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

void figure_dentist::figure_before_action() {
    auto b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_dentist::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building* b, figure *f, int&) {
        b->data.house.dentist = MAX_COVERAGE;
    });
    return 0;
}

const animations_t &figure_dentist::anim() const {
    return fdentist_m.anim;
}
