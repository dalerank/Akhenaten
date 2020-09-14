#ifndef AUGUSTUS_GAME_ENVIRONMENT_H
#define AUGUSTUS_GAME_ENVIRONMENT_H

typedef enum {
    ENGINE_ENV_C3 = 0,
    ENGINE_ENV_PHARAOH = 1,
    ENGINE_ENV_MAX = 2
};

typedef struct engine_sizes {
    int MAX_REQUESTS;
    int MAX_INVASIONS;
    int MAX_DEMAND_CHANGES;
    int MAX_PRICE_CHANGES;

    int MAX_HERD_POINTS;
    int MAX_FISH_POINTS;
    int MAX_INVASION_POINTS;

    int MAX_ALLOWED_BUILDINGS;

    int MAX_PLAYER_NAME;
    int MAX_SCENARIO_NAME;
    int MAX_BRIEF_DESCRIPTION;
    int MAX_BRIEFING;

    int MAX_FORMATIONS;
} engine_sizes;

extern int GAME_ENV;

void init_game_environment(int env);
const char *get_game_title(void);
const char *get_engine_pref_path(void);
engine_sizes env_sizes(void);

#endif //AUGUSTUS_GAME_ENVIRONMENT_H