#include "game_environment.h"

#include "SDL.h"

#include <assert.h>

int GAME_ENV = ENGINE_ENV_MAX;
int DEBUG_MODE = ENGINE_MODE_MAX;
const char *game_name;
const char *pref_filename;

void init_game_environment(int env, int mode) {
    assert(env != ENGINE_ENV_MAX);
    GAME_ENV = env;
    switch (env) {
        case ENGINE_ENV_C3:
            game_name = "Caesar 3";
            pref_filename = "data_dir_c3.txt";
            break;
        case ENGINE_ENV_PHARAOH:
            game_name = "Pharaoh";
            pref_filename = "data_dir_pharaoh.txt";
            break;
    }
    SDL_Log("Engine set to %s", game_name);
    DEBUG_MODE = mode;
}
void assert_env_init(void) {
    assert(GAME_ENV < ENGINE_ENV_MAX);
}

const char *get_game_title(void) {
    assert_env_init();
    return game_name;
}
const char *get_engine_pref_path(void) {
    assert_env_init();
    return pref_filename;
}
engine_sizes env_sizes(void) {
    assert_env_init();
    switch (GAME_ENV) {
        case ENGINE_ENV_C3: {
            engine_sizes s = {
                    20,
                    20,
                    20,
                    20,

                    4,
                    8,
                    8,

                    50,

                    32,
                    65,
                    64,
                    522,

                    250
            };
            return s;
        }
        case ENGINE_ENV_PHARAOH: {
            engine_sizes s = {
                    20,
                    20,
                    20,
                    20,

                    4,
                    8,
                    8,

                    114,

                    32,
                    65,
                    64,
                    522,

                    50
            };
            return s;
        }
    }
}

