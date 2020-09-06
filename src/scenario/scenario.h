#ifndef SCENARIO_SCENARIO_H
#define SCENARIO_SCENARIO_H

#include "core/buffer.h"

typedef struct scenario_data_buffers {
    buffer *header;
    buffer *info1;
    buffer *info2;
    buffer *info3;
    buffer *events;
    buffer *win_criteria;
    buffer *map_points;
    buffer *river_points;
    buffer *empire;
    buffer *wheat;

    buffer *requests;
    buffer *invasions;
    buffer *invasion_points;
    buffer *request_comply_dialogs;
    buffer *herds;
    buffer *demands;
    buffer *price_changes;
    buffer *fishing_points;
    buffer *request_extra;
    buffer *allowed_builds;

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
