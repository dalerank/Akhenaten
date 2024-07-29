#include "figure_librarian.h"

#include "city/labor.h"
#include "figure/service.h"
#include "city/city.h"
#include "city/sentiment.h"
#include "figure/service.h"

#include "js/js_game.h"

figures::model_t<figure_librarian> librarian_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_librarian);
void config_load_figure_librarian() {
    librarian_m.load();
}

int figure_librarian::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building* b, figure *f, int&) {
        b->data.house.library = MAX_COVERAGE;
    });
    return houses_serviced;
}

const animations_t &figure_librarian::anim() const {
    return librarian_m.anim;
}
