#include "entertainment.h"

#include "building/building_entertainment.h"
#include "city/city.h"
#include "city/entertainment_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"

city_entertainment_t& city_entertainment() {
    return xvalue<city_entertainment_t>::ref();
}

class entertainment_system : public sim_system {
public:
    const char* name() const override { return "entertainment"; }
    void on_reset() override { city_entertainment().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= 203) {
            g_chunk_io.push_chunk<city_entertainment_chunk>(city_entertainment_chunk::size, false);
        }
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_entertainment_system) {
    static entertainment_system system;
    g_simulation.register_system(&system);
}

void city_entertainment_t::reset() {
    *this = {};
}

void city_entertainment_t::calculate_shows() {
    booth_shows = 0;
    booth_no_shows_weighted = 0;
    bandstand_shows = 0;
    bandstand_no_shows_weighted = 0;
    pavilion_shows = 0;
    pavilion_no_shows_weighted = 0;
    senet_house_plays = 0;
    senet_house_no_shows_weighted = 0;
    zoo_shows = 0;
    zoo_no_shows_weighted = 0;
    venue_needing_shows = 0;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID) {
            continue;
        }

        auto ent = b->dcast_entertainment();
        if (!ent) {
            continue;
        }

        auto &d = ent->runtime_data();
        switch (b->type) {
        case BUILDING_BOOTH: // booth
            if (d.juggler_visited) booth_shows++;
            else booth_no_shows_weighted++;
            break;

        case BUILDING_BANDSTAND: // bandstand
            if (d.juggler_visited) booth_shows++;
            else booth_no_shows_weighted++;

            if (d.musician_visited) bandstand_shows++;
            else bandstand_no_shows_weighted++;
            break
                ;
        case BUILDING_PAVILLION: // pavillion
            if (d.juggler_visited) booth_shows++;
            else booth_no_shows_weighted++;

            if (d.musician_visited) bandstand_shows++;
            else bandstand_no_shows_weighted++;

            if (d.dancer_visited) pavilion_shows++;
            else pavilion_no_shows_weighted++;
            break;

        case BUILDING_SENET_HOUSE:
            if (d.juggler_visited) senet_house_plays++;
            else senet_house_no_shows_weighted += 100;

            break;

        case BUILDING_ZOO:
            if (d.juggler_visited) zoo_shows++;
            else zoo_no_shows_weighted += 100;
            break;
        }
    }

    int worst_shows = 0;
    if (booth_no_shows_weighted > worst_shows) {
        worst_shows = booth_no_shows_weighted;
        venue_needing_shows = 1;
    }

    if (bandstand_no_shows_weighted > worst_shows) {
        worst_shows = bandstand_no_shows_weighted;
        venue_needing_shows = 2;
    }

    if (pavilion_no_shows_weighted > worst_shows) {
        worst_shows = pavilion_no_shows_weighted;
        venue_needing_shows = 3;
    }

    if (senet_house_no_shows_weighted > worst_shows) {
        worst_shows = senet_house_no_shows_weighted;
        venue_needing_shows = 4;
    }

    if (zoo_no_shows_weighted > worst_shows) {
        venue_needing_shows = 5;
    }
}

int city_entertainment_t::show_message_pavilion() {
    if (!pavilion_message_shown) {
        pavilion_message_shown = 1;
        return 1;
    } else {
        return 0;
    }
}

int city_entertainment_t::show_message_senet_house() {
    if (!senet_house_message_shown) {
        senet_house_message_shown = 1;
        return 1;
    } else {
        return 0;
    }
}
