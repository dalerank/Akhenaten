#include "entertainment.h"

#include "building/building.h"
#include "city/city.h"

void city_entertainment_t::calculate_shows() {
    theater_shows = 0;
    theater_no_shows_weighted = 0;
    amphitheater_shows = 0;
    amphitheater_no_shows_weighted = 0;
    colosseum_shows = 0;
    colosseum_no_shows_weighted = 0;
    hippodrome_shows = 0;
    hippodrome_no_shows_weighted = 0;
    venue_needing_shows = 0;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        switch (b->type) {
        case BUILDING_BOOTH: // booth
            if (b->data.entertainment.days1)
                theater_shows++;
            else
                theater_no_shows_weighted++;
            break;
        case BUILDING_BANDSTAND: // bandstand
            if (b->data.entertainment.days1)
                theater_shows++;
            else
                theater_no_shows_weighted++;
            if (b->data.entertainment.days2)
                amphitheater_shows++;
            else
                amphitheater_no_shows_weighted++;
            break;
        case BUILDING_PAVILLION: // pavillion
            if (b->data.entertainment.days1)
                theater_shows++;
            else
                theater_no_shows_weighted++;
            if (b->data.entertainment.days2)
                amphitheater_shows++;
            else
                amphitheater_no_shows_weighted++;
            if (b->data.entertainment.days3_or_play)
                colosseum_shows++;
            else
                colosseum_no_shows_weighted++;
            break;
        case BUILDING_SENET_HOUSE:
            if (b->data.entertainment.days1)
                hippodrome_shows++;
            else
                hippodrome_no_shows_weighted += 100;
            break;
        }
    }
    int worst_shows = 0;
    if (theater_no_shows_weighted > worst_shows) {
        worst_shows = theater_no_shows_weighted;
        venue_needing_shows = 1;
    }
    if (amphitheater_no_shows_weighted > worst_shows) {
        worst_shows = amphitheater_no_shows_weighted;
        venue_needing_shows = 2;
    }
    if (colosseum_no_shows_weighted > worst_shows) {
        worst_shows = colosseum_no_shows_weighted;
        venue_needing_shows = 3;
    }
    if (hippodrome_no_shows_weighted > worst_shows)
        venue_needing_shows = 4;
}

int city_entertainment_t::show_message_colosseum() {
    if (!colosseum_message_shown) {
        colosseum_message_shown = 1;
        return 1;
    } else {
        return 0;
    }
}

int city_entertainment_t::show_message_hippodrome() {
    if (!hippodrome_message_shown) {
        hippodrome_message_shown = 1;
        return 1;
    } else {
        return 0;
    }
}
