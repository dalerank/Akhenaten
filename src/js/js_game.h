#pragma once

struct js_State;
void js_register_game_functions(struct js_State *J);
void js_config_load_building_sounds(js_State *J);
void js_config_load_mission_sounds(js_State *arch);
void js_config_load_walker_sounds(js_State *arch);
void js_config_load_city_sounds(js_State *arch);