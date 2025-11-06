#include "settings.h"

#include "core/encoding.h"
#include "city/constants.h"
#include "core/buffer.h"
#include "core/calc.h"
#include "game/game_environment.h"
#include "core/string.h"
#include "io/io.h"

#include <array>

#define INF_SIZE 564

game_settings g_settings;

game_settings::game_settings() {
    inf_file = new buffer(INF_SIZE);
}

void game_settings::load_default_settings() {
    fullscreen = true;
    cli_fullscreen = false;
    display_size = {800, 600};

    sound_effects.enabled = true;
    sound_effects.volume = 100;
    sound_music.enabled = true;
    sound_music.volume = 80;
    sound_speech.enabled = true;
    sound_speech.volume = 100;
    sound_city.enabled = true;
    sound_city.volume = 100;

    scroll_speed = 70;

    difficulty.set(DIFFICULTY_HARD);
    tooltips = e_tooltip_show_full;
    warnings = true;
    gods_enabled = true;
    victory_video = false;
    last_advisor = ADVISOR_LABOR;

    popup_messages = 0;
    pyramid_speedup = false;

    g_settings.clear_personal_savings();
}

void game_settings::load_settings(buffer* buf) {
    buf->skip(4);
    fullscreen = buf->read_i32();
    buf->skip(3);
    sound_effects.enabled = buf->read_u8();
    sound_music.enabled = buf->read_u8();
    sound_speech.enabled = buf->read_u8();
    buf->skip(6);
    buf->skip(4);
    scroll_speed = buf->read_i32();
    buf->read_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    last_advisor = buf->read_i32();
    last_advisor = ADVISOR_TRADE; // debug
    buf->skip(4);                      // int save_game_mission_id;
    tooltips = buf->read_i32();
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    sound_city.enabled = buf->read_u8();
    warnings = buf->read_u8();
    monthly_autosave = buf->read_u8();
    buf->skip(1); // unsigned char autoclear_enabled;
    sound_effects.volume = buf->read_i32();
    sound_music.volume = buf->read_i32();
    sound_speech.volume = buf->read_i32();
    sound_city.volume = buf->read_i32();
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
    buf->write_u8(sound_effects.enabled);
    buf->write_u8(sound_music.enabled);
    buf->write_u8(sound_speech.enabled);
    buf->skip(6);
    buf->skip(4);
    buf->write_i32(scroll_speed);
    buf->write_raw(player_name.data(), player_name.capacity);
    buf->skip(16);
    buf->write_i32(last_advisor);
    buf->skip(4); // int save_game_mission_id;
    buf->write_i32(tooltips);
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->write_u8(sound_city.enabled);
    buf->write_u8(warnings);
    buf->write_u8(monthly_autosave);
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->write_i32(sound_effects.volume);
    buf->write_i32(sound_music.volume);
    buf->write_i32(sound_speech.volume);
    buf->write_i32(sound_city.volume);
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

sound_settings* game_settings::get_sound(int type) {
    auto& data = g_settings;
    switch (type) {
    case SOUND_MUSIC:
        return &data.sound_music;
    case SOUND_EFFECTS:
        return &data.sound_effects;
    case SOUND_SPEECH:
        return &data.sound_speech;
    case SOUND_CITY:
        return &data.sound_city;
    default:
        return 0;
    }
}

void game_settings::toggle_tooltips() {
    auto& data = g_settings;
    data.tooltips = (data.tooltips + 1) % e_tooltip_count;
}

void game_settings::set_player_name(const uint8_t* name) {
    player_name = (pcstr)name;
    encoding_to_utf8(name, player_name_utf8, MAX_PLAYER_NAME, 0);
}

void game_settings::clear_personal_savings() {
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        personal_savings[i] = 0;
    }
}
