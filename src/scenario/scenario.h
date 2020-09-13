#ifndef SCENARIO_SCENARIO_H
#define SCENARIO_SCENARIO_H

#include "core/buffer.h"

typedef struct scenario_data_buffers {
    buffer *header = new buffer;
    buffer *info1 = new buffer;
    buffer *info2 = new buffer;
    buffer *info3 = new buffer;
    buffer *events = new buffer;
    buffer *win_criteria = new buffer;
    buffer *map_points = new buffer;
    buffer *river_points = new buffer;
    buffer *empire = new buffer;
    buffer *wheat = new buffer;

    buffer *requests = new buffer;
    buffer *invasions = new buffer;
    buffer *invasion_points = new buffer;
    buffer *request_comply_dialogs = new buffer;
    buffer *herds = new buffer;
    buffer *demands = new buffer;
    buffer *price_changes = new buffer;
    buffer *fishing_points = new buffer;
    buffer *request_extra = new buffer;
    buffer *allowed_builds = new buffer;

    buffer *monuments = new buffer;

} scenario_data_buffers;

int scenario_is_saved(void);
void scenario_settings_init(void);
void scenario_settings_init_mission(void);
void scenario_fix_patch_trade(int mission_id);

void scenario_save_state(scenario_data_buffers *scenario_data);
void scenario_load_state(scenario_data_buffers *scenario_data);

void scenario_settings_save_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name);
void scenario_settings_load_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name);

#endif // SCENARIO_SCENARIO_H
