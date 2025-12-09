#include "city_religion_osiris.h"

#include "city/city.h"
#include "city/city_message.h"
#include "city_floods.h"
#include "core/random.h"
#include "game/game_events.h"

god_osiris_t god_osiris;

void god_osiris_t::perform_worse_flood() {
    g_floods.adjust_next_quality((-2 - anti_scum_random_15bit() % 3) * 10);
    messages::popup("message_wrath_of_osiris", 0, 0);
}

bool god_osiris_t::create_shipwreck_flotsam() {
    if (sank_ships) {
        sank_ships = 0;
        return true;
    } else {
        return false;
    }
}


void god_osiris_t::perform_locusts() {
    // TODO: implement locusts
    messages::popup("message_wrath_of_osiris_2", 0, 0);
}

void god_osiris_t::perform_major_curse() {
    if (anti_scum_random_bool()) {
        // worse flood quality
        perform_worse_flood();
    } else {
        // locusts
        perform_locusts();
    }
}

void god_osiris_t::perform_flood_will_destroy_farms() {
    g_city.religion.osiris_flood_will_destroy_active = 1;
    events::emit(event_message_god{ GOD_OSIRIS, "message_small_curse_osiris" });
}

void god_osiris_t::perform_lower_flood_quality() {
    int randm = anti_scum_random_15bit();
    randm = randm & 0x80000003;
    if ((int)randm < 0) {
        randm = (randm - 1 | 0xfffffffc) + 1;
    }
    g_floods.adjust_next_quality((-1 - randm) * 5);
    events::emit(event_message_god{ GOD_OSIRIS, "message_small_curse_osiris" });
}

void god_osiris_t::perform_minor_curse() {
    if (anti_scum_random_bool()) {
        // next flood will destroys farms
        perform_flood_will_destroy_farms();
    } else {
        // lower quality flood
        perform_lower_flood_quality();
    }
}

