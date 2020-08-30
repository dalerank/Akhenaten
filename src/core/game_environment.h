#ifndef AUGUSTUS_GAME_ENVIRONMENT_H
#define AUGUSTUS_GAME_ENVIRONMENT_H


typedef enum {
    ENGINE_ENV_C3,
    ENGINE_ENV_PHARAOH,
    ENGINE_ENV_MAX
} engine_environment;

engine_environment GAME_ENV;

void init_game_environment(engine_environment env);
const char *get_game_title(void);
const char *get_engine_pref_path(void);

#endif //AUGUSTUS_GAME_ENVIRONMENT_H