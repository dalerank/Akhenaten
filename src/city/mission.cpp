#include "mission.h"

#include "city/city.h"

static auto &city_data = g_city;
void city_mission_reset_save_start(void) {
    city_data.mission.start_saved_game_written = 0;
}

int city_mission_should_save_start(void) {
    if (!city_data.mission.start_saved_game_written) {
        city_data.mission.start_saved_game_written = 1;
        return 1;
    } else
        return 0;
}

void city_mission_tutorial_add_senate(void) {
    city_data.mission.tutorial_senate_built++;
}

int city_mission_tutorial_has_senate(void) {
    return city_data.mission.tutorial_senate_built > 0;
}
