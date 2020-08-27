#include "game_environment.h"

#include "SDL.h"

#include <assert.h>

void assert_env_init(void)
{
    assert(game_environment.env > ENGINE_ENV_NULL && game_environment.env < ENGINE_ENV_MAX);
}
int is_engine_env(engine_environment env)
{
    return (int)(game_environment.env == env);
}
engine_environment get_engine_environment(void)
{
    return game_environment.env;
}
void init_game_environment(engine_environment env)
{
    game_environment.env = env;
    switch (env)
    {
        case ENGINE_ENV_C3:
            game_environment.game_name = "Caesar 3";
            game_environment.pref_filename = "data_dir_c3.txt";
            return;
        case ENGINE_ENV_PHARAOH:
            game_environment.game_name = "Pharaoh";
            game_environment.pref_filename = "data_dir_pharaoh.txt";
            return;
    }
}
const char *get_game_title(void)
{
    assert_env_init();
    return game_environment.game_name;
}