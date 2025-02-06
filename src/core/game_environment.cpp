#include "game_environment.h"

#include "core/log.h"

#include <cassert>

const char* game_name;
const char* pref_filename;

void init_game_environment(int env) {
    game_name = "Akhenaten";
    pref_filename = "data_dir_pharaoh.txt";
    logs::info("Engine set to %s", game_name);
}

void assert_env_init() {
}

const char* get_game_title() {
    assert_env_init();
    return game_name;
}
const char* get_engine_pref_path() {
    assert_env_init();
    return pref_filename;
}
