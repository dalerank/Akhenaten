#include "settings.h"

#include "core/encoding.h"
#include "city/constants.h"
#include "core/buffer.h"
#include "core/calc.h"
#include "game/game_config.h"
#include "game/game_environment.h"
#include "js/js_game.h"
#include "core/string.h"
#include "io/io.h"

#include <array>

#define INF_SIZE 564

game_settings g_settings;
const e_sound_type_tokens_t ANK_CONFIG_ENUM(e_sound_type_tokens);

game_settings::game_settings() {
    inf_file = new buffer(INF_SIZE);
}

uint8_t game_difficulty() {
    return g_settings.difficulty();
}

void game_settings::load_default_settings() {
    fullscreen = true;
    cli_fullscreen = false;
    display_size = {800, 600};

    difficulty.set(DIFFICULTY_HARD);
    tooltips_mode = e_tooltip_mode_full;
    warnings = true;
    gods_enabled = true;
    victory_video = false;
    last_advisor = ADVISOR_NONE;

    popup_messages = 0;
    pyramid_speedup = false;

    clear_personal_savings();
}

void game_settings::load_settings(buffer* buf) {
    buf->skip(4);
    fullscreen = buf->read_i32();
    buf->skip(3);
    buf->read_u8();
    buf->read_u8();
    buf->read_u8();
    buf->skip(6);
    buf->skip(4);
    int tmp = buf->read_i32();
    buf->read_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    last_advisor = buf->read_i32();
    //last_advisor = ADVISOR_TRADE; // debug
    buf->skip(4);                      // int save_game_mission_id;
    tooltips_mode = (e_tooltip_mode)buf->read_i32();
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->read_u8();
    warnings = buf->read_u8();
    tmp = buf->read_u8();
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->read_i32();
    buf->read_i32();
    buf->read_i32();
    buf->read_i32();
    buf->skip(8); // ram
    display_size.x = buf->read_i32();
    display_size.y = buf->read_i32();
    display_size = {0, 0};

    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        personal_savings[i] = buf->read_i32();
    }
    victory_video = buf->read_i32();

    assert(!buf->at_end());
    e_difficulty difficulty_value = (e_difficulty)buf->read_i32();
    difficulty.set(difficulty_value);
    gods_enabled = buf->read_i32();
}

void game_settings::load() {
    load_default_settings();

    // TODO: load <Pharaoh.inf>
    int size = io_read_file_into_buffer("pharaoh.inf", NOT_LOCALIZED, inf_file, INF_SIZE);
    if (!size) {
        return;
    }

    load_settings(inf_file);

    if (display_size.x + display_size.y < 500) {
        // most likely migration from Caesar 3
        display_size = {800, 600};
    }
}

void game_settings::save() {
    buffer* buf = inf_file;
    buf->reset_offset();

    buf->skip(4);
    buf->write_i32(fullscreen);
    buf->skip(3);
    buf->write_u8(false);
    buf->write_u8(false);
    buf->write_u8(false);
    buf->skip(6);
    buf->skip(4);
    buf->write_i32(0);
    buf->write_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    buf->write_i32(last_advisor);
    buf->skip(4); // int save_game_mission_id;
    buf->write_i32(tooltips_mode);
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->write_u8(false);
    buf->write_u8(warnings);
    buf->write_u8(0);
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->skip(8); // ram
    buf->write_i32(display_size.x);
    buf->write_i32(display_size.y);
    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        buf->write_i32(personal_savings[i]);
    }
    buf->write_i32(victory_video);
    buf->write_u8(difficulty());
    buf->skip(3);
    buf->write_i32(gods_enabled);

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

void game_settings::clear_personal_savings() {
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        personal_savings[i] = 0;
    }
}
