#ifndef AUGUSTUS_GAME_ENVIRONMENT_H
#define AUGUSTUS_GAME_ENVIRONMENT_H

typedef enum {
    ENGINE_ENV_C3,
    ENGINE_ENV_PHARAOH,
    ENGINE_ENV_MAX
} engine_environment;

void init_game_environment(engine_environment env);
int is_engine_env(engine_environment env);
engine_environment get_engine_environment(void);
const char *get_game_title(void);
const char *get_engine_pref_path(void);

#endif //AUGUSTUS_GAME_ENVIRONMENT_H