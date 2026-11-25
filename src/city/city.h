#pragma once

#include "core/variant.h"
#include "core/xstring.h"
#include "game/player_record.h"

void city_init();
void city_reload_objects();
void city_on_post_load();
void city_before_start_simulation();
void city_init_custom_map();
void city_init_campaign_mission();

pcstr city_player_name();
void city_set_player_name(xstring name);
// Snapshot of what the city achieved, handed to the player profile when a mission is won.
mission_result_t city_make_mission_result(int scenario_id);
void city_restore_campaign_player_name();
bvariant city_get_property(xstring domain, xstring name);
