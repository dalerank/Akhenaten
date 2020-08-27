#ifndef AUGUSTUS_GAME_ENVIRONMENT_H
#define AUGUSTUS_GAME_ENVIRONMENT_H

typedef enum {
    ENGINE_ENV_NULL,
    ENGINE_ENV_C3,
    ENGINE_ENV_PHARAOH,
    ENGINE_ENV_MAX
} engine_environment;

static struct game_environment_collection {
    engine_environment env;
    char *game_name;
    char *pref_filename;
} game_environment = {
        ENGINE_ENV_NULL,
        "",
        ""
};

void init_game_environment(engine_environment env);
int is_engine_env(engine_environment env);
engine_environment get_engine_environment(void);
const char *get_game_title(void);

#endif //AUGUSTUS_GAME_ENVIRONMENT_H