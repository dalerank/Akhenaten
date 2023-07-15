#ifndef SCENARIO_SCENARIO_H
#define SCENARIO_SCENARIO_H

#include "core/buffer.h"

struct scenario_data_buffers {
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
    buffer *invasion_points_land = nullptr;
    buffer *request_comply_dialogs = nullptr;
    buffer *herds = nullptr;
    buffer *demands = nullptr;
    buffer *price_changes = nullptr;
    buffer *fishing_points = nullptr;
    buffer *request_extra = nullptr;
    buffer *allowed_builds = nullptr;

    buffer *events_ph = nullptr;

    buffer *monuments = nullptr;
};

bool scenario_is_saved(void);
void scenario_settings_init(void);
void scenario_settings_init_mission(void);

#endif // SCENARIO_SCENARIO_H
