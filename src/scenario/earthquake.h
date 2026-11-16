#pragma once

struct event_ph_t;

// EVENT_TYPE_EARTHQUAKE events, processed every sim tick (OG tick.c).
bool scenario_earthquake_event_process(event_ph_t& e);
void scenario_earthquake_process(void);
int scenario_earthquake_is_in_progress(void);

void map_tiles_update_all_earthquake(void);
void map_tiles_set_earthquake(int x, int y);
