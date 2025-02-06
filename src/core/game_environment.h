#pragma once

enum { ENGINE_MODE_RELEASE = 0, ENGINE_MODE_DEBUG = 1, ENGINE_MODE_MAX = 2 };

#define MAX_REQUESTS 20
#define MAX_INVASIONS 20
#define MAX_DEMAND_CHANGES 20
#define MAX_PRICE_CHANGES 20

constexpr int MAX_FISH_POINTS = 8;
#define MAX_PREDATOR_HERD_POINTS 4
#define MAX_PREY_HERD_POINTS 4
#define MAX_DISEMBARK_POINTS 3
#define MAX_INVASION_POINTS_LAND 8
#define MAX_INVASION_POINTS_SEA 8
#define MAX_FORMATIONS 50

#define MAX_PLAYER_NAME 32
#define MAX_SCENARIO_NAME 65
#define MAX_SUBTITLE 64
#define MAX_BRIEF_DESCRIPTION 522

void init_game_environment(int env);
const char* get_game_title();
const char* get_engine_pref_path();