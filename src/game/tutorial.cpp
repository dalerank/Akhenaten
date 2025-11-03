#include "tutorial.h"

#include "building/building_granary.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "city/city_building_menu_ctrl.h"
#include "empire/empire_city.h"
#include "game/resource.h"
#include "io/io_buffer.h"
#include "platform/arguments.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "io/gamefiles/lang.h"

#include <algorithm>
#include "dev/debug.h"
#include <iostream>

tutorial_flags_t g_tutorials_flags;
const tutorial_stage_t tutorial_stage;

declare_console_command_p(runstage) {
    std::string args;
    is >> args;
    tutorial_update_step(args.c_str());
}

declare_console_command_p(startmessage) {
    std::string args;
    is >> args;
    xstring messageid = args.empty() ? g_scenario.meta.start_message : lang_get_message_id(std::stoi(args));
    messages::popup(messageid, 0, 0);
}

tutorial_t::tutorial_t() {
    list().push_back(this);
}

tutorial_t::tutorial_list &tutorial_t::list() {
    static tutorial_list list;
    return list;
}

static void set_all_tut_flags_null() {
    for (auto t: tutorial_t::list()) {
        t->reset();
    }
    
    //
    g_tutorials_flags.pharaoh.tut7_start = 0;
    g_tutorials_flags.pharaoh.tut8_start = 0;

    for (int i = 0; i < 41; i++) {
        g_tutorials_flags.pharaoh.flags[i] = 0;
    }
}

template<class T>
void memset_if(bool ok, char v, T &t) {
    if (ok) {
        memset(&t, 1, sizeof(t));
    }
}

bool tutorial_init(bool clear_all_flags, bool custom) {
    if (clear_all_flags) {
        set_all_tut_flags_null();
    }

    if (custom) {
        return false;
    }

    int scenario_id = g_scenario.campaign_scenario_id();
    memset_if(0 < scenario_id, 1, g_tutorials_flags.tutorial_1);
    memset_if(1 < scenario_id, 1, g_tutorials_flags.tutorial_2);
    memset_if(2 < scenario_id, 1, g_tutorials_flags.tutorial_3);
    memset_if(3 < scenario_id, 1, g_tutorials_flags.tutorial_4);
    memset_if(4 < scenario_id, 1, g_tutorials_flags.tutorial_5);
    memset_if(5 < scenario_id, 1, g_tutorials_flags.tutorial_6);

    for (auto t : tutorial_t::list()) {
        if (t->missionid() == (scenario_id + 1)) {
            t->init();
            return true;
        }
    }

    return false;
}
e_availability mission_empire_availability(int mission) {
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
    if (is_custom_map) {
        return NOT_AVAILABLE;
    }

    if (mission < 5) {
        return NOT_AVAILABLE;
    }

    if (mission == 5) {
        return (g_tutorials_flags.tutorial_5.papyrus_made)
                    ? AVAILABLE
                    : NOT_AVAILABLE;
    }

    return AVAILABLE;
}

void tutorial_map_update(int tut) {
    if (tut == 1) {
        g_scenario.env.has_animals = true;
    } else if (tut == 2) {
        g_scenario.env.has_animals = true;
    }
}

xstring tutorial_get_immediate_goal_text() {
    for (auto tut : tutorial_t::list()) {
        const int missionid = tut->missionid();
        if (g_scenario.is_scenario_id(missionid)) {
            return tut->goal_text();
        }
    }

    return "#unknown_tutoral_goal";
}

void tutorial_flags_t::on_crime() {
    if (!g_tutorials_flags.pharaoh.crime) {
        g_tutorials_flags.pharaoh.crime = 1;
        events::emit( event_building_menu_update{ tutorial_stage.tutorial_crime });
    }
}

void tutorial_update_step(xstring s) {
    for (auto tut : tutorial_t::list()) {
        const int missionid = tut->missionid();
        if (g_scenario.is_scenario_id(missionid)) {
            return tut->update_step(s);
        }
    }
}

void tutorial_flags_t::update_starting_message() {
    if (!g_scenario.meta.start_message_shown) {
        if (!g_scenario.meta.start_message.empty()) {
            messages::popup(g_scenario.meta.start_message, 0, 0);
        }
        g_scenario.meta.start_message_shown = true;
    }

    if (g_scenario.is_scenario_id(1) && !g_tutorials_flags.tutorial_1.started) {
        g_tutorials_flags.tutorial_1.started = 1;
    }
    if (g_scenario.is_scenario_id(2) && !g_tutorials_flags.tutorial_2.started) {
        g_tutorials_flags.tutorial_2.started = 1;
    }
    if (g_scenario.is_scenario_id(3) && !g_tutorials_flags.tutorial_3.started) {
        g_tutorials_flags.tutorial_3.started = 1;
    }
    if (g_scenario.is_scenario_id(4) && !g_tutorials_flags.tutorial_4.started) {
        messages::popup("message_developing_culture", 0, 0);
        g_tutorials_flags.tutorial_4.started = 1;
    }
    if (g_scenario.is_scenario_id(5) && !g_tutorials_flags.tutorial_5.started) {
        messages::popup("message_getting_started", 0, 0);
        g_tutorials_flags.tutorial_5.started = 1;
    }
    if (g_scenario.is_scenario_id(6) && !g_tutorials_flags.tutorial_6.started) {
        g_tutorials_flags.tutorial_6.started = 1;
    }

    if (g_scenario.is_scenario_id(7) && !g_tutorials_flags.pharaoh.tut7_start) {
        if (g_scenario.campaign_scenario_id() == 6)
            messages::popup("message_trade_on_the_water", 0, 0);
        else
            messages::popup("message_at_the_waters_edge", 0, 0);
        g_tutorials_flags.pharaoh.tut7_start = 1;
    }

    if (g_scenario.is_scenario_id(8) && !g_tutorials_flags.pharaoh.tut8_start) {
        messages::popup("message_the_finer_things", 0, 0);
        g_tutorials_flags.pharaoh.tut8_start = 1;
    }
}

io_buffer* iob_tutorial_flags = new io_buffer([](io_buffer* iob, size_t version) {
    uint16_t tmp;
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    // tut 1
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.granary_opened);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.gamemeat_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.building_collapsed);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.architector_built);
    // tut 2
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.gold_mined);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.temples_built);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.crime); 
    // tut 3
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.figs_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.pottery_made_1);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.pottery_made_2);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.disease);
    // tut 4
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.beer_made);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.tax_collector_built);
    // tut 5
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.spacious_apartment);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.papyrus_made);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.bricks_bought);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[14]);

    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_6.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut7_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut8_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[23]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[24]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[25]);

    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[26]); // goal: bazaar
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[27]); // goal: pottery
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[28]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[29]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[30]); // tut4 ???
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[31]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[32]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[33]); // goal: water supply
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[34]); // tut4 ???
});