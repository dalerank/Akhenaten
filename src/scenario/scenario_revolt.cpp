#include "scenario_revolt.h"

#include "game/game_events.h"
#include "city/city_message.h"
#include "city/city.h"
#include "core/random.h"
#include "game/game.h"
#include "scenario/scenario.h"

struct revolt_t {
    int game_year;
    int month;
    int end_month;
    int state;
};

revolt_t g_revolt;

void scenario_revolt_init() {
    g_revolt.game_year = g_scenario.start_year + g_scenario.gladiator_revolt.year;
    g_revolt.month = 3 + (random_byte() & 3);
    g_revolt.end_month = 3 + g_revolt.month;
    g_revolt.state = e_event_state_initial;
}

void scenario_revolt_process(void) {
    if (!g_scenario.gladiator_revolt.enabled) {
        return;
    }

    if (g_revolt.state == e_event_state_initial) {
        if (game.simtime.year == g_revolt.game_year && game.simtime.month == g_revolt.month) {
            if (g_city.buildings.count_active(BUILDING_CONSERVATORY) > 0) {
                g_revolt.state = e_event_state_in_progress;
                events::emit(event_message{ true, "message_revolt_start", 0, 0 });
            } else {
                g_revolt.state = e_event_state_finished;
            }
        }
    } else if (g_revolt.state == e_event_state_in_progress) {
        if (g_revolt.end_month == game.simtime.month) {
            g_revolt.state = e_event_state_finished;
            events::emit(event_message{ true, "message_revolt_finished_finished", 0, 0 });
        }
    }
}

int scenario_revolt_is_in_progress(void) {
    return g_revolt.state == e_event_state_in_progress;
}

int scenario_revolt_is_finished(void) {
    return g_revolt.state == e_event_state_finished;
}

void scenario_revolt_save_state(buffer* buf) {
    buf->write_i32(g_revolt.game_year);
    buf->write_i32(g_revolt.month);
    buf->write_i32(g_revolt.end_month);
    buf->write_i32(g_revolt.state);
}

void scenario_revolt_load_state(buffer* buf) {
    g_revolt.game_year = buf->read_i32();
    g_revolt.month = buf->read_i32();
    g_revolt.end_month = buf->read_i32();
    g_revolt.state = buf->read_i32();
}
