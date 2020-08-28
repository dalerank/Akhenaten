#include "game_environment.h"

#include "SDL.h"

#include <assert.h>

struct game_environment_collection {
    engine_environment env;
    char *game_name;
    char *pref_filename;
} game_environment = {.env = ENGINE_ENV_MAX};

void init_game_environment(engine_environment env)
{
    game_environment.env = env;
    switch (env)
    {
        case ENGINE_ENV_C3:
            game_environment.game_name = "Caesar 3";
            game_environment.pref_filename = "data_dir_c3.txt";
            break;
        case ENGINE_ENV_PHARAOH:
            game_environment.game_name = "Pharaoh";
            game_environment.pref_filename = "data_dir_pharaoh.txt";
            break;
    }
    SDL_Log("Engine set to %s", game_environment.game_name);
}
void assert_env_init(void)
{
    assert(game_environment.env < ENGINE_ENV_MAX);
}
int is_game_env(engine_environment env)
{
    return (int)(game_environment.env == env);
}
engine_environment get_engine_environment(void)
{
    return game_environment.env;
}

const char *get_game_title(void)
{
    assert_env_init();
    return game_environment.game_name;
}
const char *get_engine_pref_path(void)
{
    assert_env_init();
    return game_environment.pref_filename;
}
