#ifndef AUGUSTUS_GAME_ENVIRONMENT_H
#define AUGUSTUS_GAME_ENVIRONMENT_H

enum {
    ENGINE_ENV_C3 = 0,
    ENGINE_ENV_PHARAOH = 1,
    ENGINE_ENV_MAX = 2
};

enum {
    ENGINE_MODE_RELEASE = 0,
    ENGINE_MODE_DEBUG = 1,
    ENGINE_MODE_MAX = 2
};

const int MAX_REQUESTS[2] = {
        20,
        20
};
const int MAX_INVASIONS[2] = {
        20,
        20
};
const int MAX_DEMAND_CHANGES[2] = {
        20,
        20
};
const int MAX_PRICE_CHANGES[2] = {
        20,
        20
};

const int MAX_HERD_POINTS[2] = {
        4,
        4
};
const int MAX_FISH_POINTS[2] = {
        8,
        8
};
const int MAX_INVASION_POINTS[2] = {
        8,
        8
};

const int MAX_ALLOWED_BUILDINGS[2] = {
        50,
        114
};

const int MAX_PLAYER_NAME = 32;
const int MAX_SCENARIO_NAME = 65;
const int MAX_BRIEF_DESCRIPTION = 64;
const int MAX_BRIEFING = 522;

const int MAX_FORMATIONS[2] = {
        250,
        50
};

extern int GAME_ENV;
extern int DEBUG_MODE;

void init_game_environment(int env, int mode);
const char *get_game_title(void);
const char *get_engine_pref_path(void);

#endif //AUGUSTUS_GAME_ENVIRONMENT_H