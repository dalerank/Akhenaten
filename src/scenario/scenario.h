#ifndef SCENARIO_SCENARIO_H
#define SCENARIO_SCENARIO_H

#include "core/buffer.h"

typedef struct scenario_data_buffers {
    buffer *mission_index = nullptr;
    buffer *map_name = nullptr;
    buffer *map_settings = nullptr;
    buffer *is_custom = nullptr;
    buffer *player_name = nullptr;

    buffer *header = nullptr;
    buffer *info1 = nullptr;
    buffer *info2 = nullptr;
    buffer *info3 = nullptr;
    buffer *events = nullptr;
    buffer *win_criteria = nullptr;
    buffer *map_points = nullptr;
    buffer *river_points = nullptr;
    buffer *empire = nullptr;
    buffer *wheat = nullptr;
    buffer *climate_id = nullptr;

    buffer *requests = nullptr;
    buffer *invasions = nullptr;
    buffer *invasion_points = nullptr;
    buffer *request_comply_dialogs = nullptr;
    buffer *herds = nullptr;
    buffer *demands = nullptr;
    buffer *price_changes = nullptr;
    buffer *fishing_points = nullptr;
    buffer *request_extra = nullptr;
    buffer *allowed_builds = nullptr;

    buffer *events_ph = nullptr;

    buffer *monuments = nullptr;

} scenario_data_buffers;

bool scenario_is_saved(void);
void scenario_settings_init(void);
void scenario_settings_init_mission(void);
void scenario_fix_patch_trade(int mission_id);

void scenario_save_state(scenario_data_buffers *SCENARIO);
void scenario_load_state(scenario_data_buffers *SCENARIO);

//void scenario_settings_save_state(buffer *campaign_mission, buffer *scenario_settings, buffer *is_custom, buffer *player_name, buffer *scenario_name);
//void scenario_settings_load_state(buffer *campaign_mission, buffer *scenario_settings, buffer *is_custom, buffer *player_name, buffer *scenario_name);

#endif // SCENARIO_SCENARIO_H
