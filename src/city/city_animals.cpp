#include "city_animals.h"

#include "core/random.h"
#include "figuretype/figure_animal.h"
#include "dev/debug.h"

void city_animals_t::create_herd(tile2i tile) {
    e_figure_type herd_type;
    int num_animals;
    switch (scenario_property_climate()) {
    case CLIMATE_CENTRAL:
        herd_type = FIGURE_ANTELOPE;
        num_animals = 10;
        break;

    case CLIMATE_NORTHERN:
        herd_type = FIGURE_CROCODILE;
        num_animals = 8;
        break;

    case CLIMATE_DESERT:
        herd_type = FIGURE_OSTRICH;
        num_animals = 12;
        break;

    default:
        return;
    }

    int formation_id = formation_create_herd(herd_type, tile, num_animals);
    if (formation_id > 0) {
        for (int fig = 0; fig < num_animals; fig++) {
            random_generate_next();

            figure *f = figure_create(herd_type, tile, DIR_0_TOP_RIGHT);
            f->formation_id = formation_id;
            f->wait_ticks = f->id & 0x1f;

            auto fanimal = f->dcast_animal();

            if (fanimal) {
                fanimal->herd_rest();
            }
        }
    }
}

void city_animals_t::create_herds() {
    scenario_map_foreach_herd_point([this] (tile2i p) {
        this->create_herd(p);
    });
}