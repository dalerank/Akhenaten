#include "city_religion_ptah.h"

#include "city/city.h"
#include "city/city_message.h"
#include "core/random.h"
#include "game/game_events.h"

god_ptah_t god_ptah;

bool god_ptah_t::perform_industry_destruction() {
    return g_city.religion.PTAH_industry_destruction();
}

void god_ptah_t::perform_frogs() {
    // TODO: implement frogs
    // PTAH_frogs();
}

void god_ptah_t::perform_major_curse() {
    if (anti_scum_random_bool()) {
        // destroys some industrial buildings
        bool success = perform_industry_destruction();
        if (success) {
            messages::popup("message_wrath_of_ptah", 0, 0);
        } else {
            // no yard found
            messages::popup("message_wrath_of_ptah_no_effect", 0, 0);
        }
    } else {
        // frogs
        perform_frogs();
        messages::popup("message_wrath_of_ptah_2", 0, 0);
    }
}

bool god_ptah_t::perform_warehouse_destruction() {
    return g_city.religion.PTAH_warehouse_destruction();
}

void god_ptah_t::perform_minor_curse() {
    // destroys random storage yard
    bool success = perform_warehouse_destruction();
    if (success) {
        events::emit(event_message_god{ GOD_PTAH, "message_ptah_is_upset" });
    } else { // no yard found 
        events::emit(event_message_god{ GOD_PTAH, "message_curse_ptah_noeffect" });
    }
}

