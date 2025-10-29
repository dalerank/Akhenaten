#include "farao_change.h"

#include "city/city_message.h"
#include "city/city.h"
#include "core/random.h"
#include "game/game.h"
#include "game/game_config.h"
#include "scenario/scenario.h"

struct scenario_kingdome_change_t {
    int game_year;
    int month;
    int state;
};

scenario_kingdome_change_t g_scenario_kingdome_change;

void scenario_kingdome_change_init() {
    auto &data = g_scenario_kingdome_change;
    data.game_year = g_scenario.start_year + g_scenario.emperor_change.year;
    data.month = 1 + (random_byte() & 7);
    data.state = 0;
}

void scenario_kingdome_change_process() {
    auto &data = g_scenario_kingdome_change;
    if (!g_scenario.emperor_change.enabled) {
        return;
    }

    if (data.state == 0) {
        if (game.simtime.year == data.game_year && game.simtime.month == data.month) {
            data.state = 1; // done
            if (!!game_features::gameplay_fix_editor_events) {
                g_city.kingdome.reset();
            }

            messages::popup("message_kingdome_change", 0, 0);
        }
    }
}

void scenario_kingdome_change_save_state(buffer* time, buffer* state) {
    auto &data = g_scenario_kingdome_change;
    time->write_i32(data.game_year);
    time->write_i32(data.month);
    state->write_i32(data.state);
}

void scenario_kingdome_change_load_state(buffer* time, buffer* state) {
    auto &data = g_scenario_kingdome_change;
    data.game_year = time->read_i32();
    data.month = time->read_i32();
    data.state = state->read_i32();
}
