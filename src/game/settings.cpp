#include "settings.h"

#include "core/encoding.h"
#include "city/constants.h"
#include "core/buffer.h"
#include "core/calc.h"
#include "game/game_config.h"
#include "game/game_environment.h"
#include "game/game.h"
#include "js/js_game.h"
#include "core/string.h"
#include "io/io.h"

#include <array>

#define INF_SIZE 564

namespace {
constexpr int INF_PERSONAL_SAVINGS_SLOTS = 100;
}

game_settings g_settings;

game_settings::game_settings() {
    inf_file = new buffer(INF_SIZE);
}

void game_settings::load_default_settings() {}

void game_settings::load_settings(buffer* buf) {
    buf->skip(4);
    buf->read_i32(); // fullscreen - moved to game_features::gameopt_fullscreen
    buf->skip(3);
    buf->read_u8();
    buf->read_u8();
    buf->read_u8();
    buf->skip(6);
    buf->skip(4);
    buf->read_i32();
    buf->read_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    buf->read_i32();
    buf->skip(4);                      // int save_game_mission_id;
    buf->read_i32();
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->read_u8();
    buf->read_u8(); // warnings - moved to game_features::gameopt_warnings
    buf->read_u8();
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->read_i32();
    buf->read_i32();
    buf->read_i32();
    buf->read_i32();
    buf->skip(8); // ram
    buf->read_i32();
    buf->read_i32();

    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < INF_PERSONAL_SAVINGS_SLOTS; i++) {
        buf->read_i32(); // legacy personal_savings[i] from original inf layout
    }
    buf->read_i32(); // victory_video - moved to game_features::gameopt_victory_video

    assert(!buf->at_end());
    buf->read_i32();
    buf->read_i32(); // gods_enabled - moved to game_features::gameopt_gods_enabled
}

void game_settings::load() {
    load_default_settings();

    // TODO: load <Pharaoh.inf>
    int size = io_read_file_into_buffer("pharaoh.inf", NOT_LOCALIZED, inf_file, INF_SIZE);
    if (!size) {
        return;
    }

    load_settings(inf_file);
}

void game_settings::save() {
    buffer* buf = inf_file;
    buf->reset_offset();

    buf->skip(4);
    buf->write_i32(false); // fullscreen - moved to game_features::gameopt_fullscreen
    buf->skip(3);
    buf->write_u8(false);
    buf->write_u8(false);
    buf->write_u8(false);
    buf->skip(6);
    buf->skip(4);
    buf->write_i32(0);
    buf->write_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    buf->write_i32(0);
    buf->skip(4); // int save_game_mission_id;
    buf->write_i32(0);
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->write_u8(false);
    buf->write_u8(false); // warnings - moved to game_features::gameopt_warnings
    buf->write_u8(0);
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->skip(8); // ram
    buf->write_i32(0);
    buf->write_i32(0);
    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < INF_PERSONAL_SAVINGS_SLOTS; i++) {
        buf->write_i32(0); // legacy slots — unused
    }
    buf->write_i32(false); // victory_video - moved to game_features::gameopt_victory_video
    buf->write_u8(0);
    buf->skip(3);
    buf->write_i32(false); // gods_enabled - moved to game_features::gameopt_gods_enabled

    io_write_buffer_to_file("pharaoh.inf", inf_file, INF_SIZE);
}

void game_settings::set_player_name(const uint8_t* name) {
    player_name = (pcstr)name;
    encoding_to_utf8(name, player_name_utf8, MAX_PLAYER_NAME, 0);
}

void game_settings::set_player_name_utf8(pcstr name_utf8) {
    bstring32 encoded;
    encoding_from_utf8(name_utf8 ? name_utf8 : "", encoded, MAX_PLAYER_NAME);
    set_player_name(encoded);
}

