#include "settings.h"
#include <core/encoding.h>

#include "city/constants.h"
#include "core/buffer.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "core/string.h"
#include "io/io.h"

#define INF_SIZE 564
#define MAX_PERSONAL_SAVINGS 100
// #define MAX_PLAYER_NAME 32

struct settings_data_t {
    // display settings
    bool fullscreen;
    int window_width;
    int window_height;
    // sound settings
    set_sound sound_effects;
    set_sound sound_music;
    set_sound sound_speech;
    set_sound sound_city;
    // speed settings
    int game_speed;
    int scroll_speed;
    // misc settings
    int difficulty;
    int tooltips;
    int monthly_autosave;
    bool warnings;
    bool gods_enabled;
    bool victory_video;
    // pharaoh settings
    int popup_messages;
    int city_names_style;
    bool pyramid_speedup;
    // persistent game state
    int last_advisor;
    uint8_t player_name[MAX_PLAYER_NAME] = {0};
    char player_name_utf8[MAX_PLAYER_NAME] = {0};
    // personal savings
    int personal_savings[MAX_PERSONAL_SAVINGS] = {0};
    // file data
    buffer* inf_file = new buffer(INF_SIZE);
};

settings_data_t& settings_data() {
    static settings_data_t inst;
    return inst;
}

static void load_default_settings(void) {
    auto& data = settings_data();
    data.fullscreen = true;
    data.window_width = 800;
    data.window_height = 600;

    data.sound_effects.enabled = true;
    data.sound_effects.volume = 100;
    data.sound_music.enabled = true;
    data.sound_music.volume = 80;
    data.sound_speech.enabled = true;
    data.sound_speech.volume = 100;
    data.sound_city.enabled = true;
    data.sound_city.volume = 100;

    data.game_speed = 90;
    data.scroll_speed = 70;

    data.difficulty = DIFFICULTY_HARD;
    data.tooltips = TOOLTIPS_FULL;
    data.warnings = true;
    data.gods_enabled = true;
    data.victory_video = false;
    data.last_advisor = ADVISOR_LABOR;

    data.popup_messages = 0;
    data.city_names_style = CITIES_OLD_NAMES;
    data.pyramid_speedup = false;

    setting_clear_personal_savings();
}
static void load_settings(buffer* buf) {
    auto& data = settings_data();
    buf->skip(4);
    data.fullscreen = buf->read_i32();
    buf->skip(3);
    data.sound_effects.enabled = buf->read_u8();
    data.sound_music.enabled = buf->read_u8();
    data.sound_speech.enabled = buf->read_u8();
    buf->skip(6);
    data.game_speed = buf->read_i32();
    data.game_speed = 80; // todo: fix settings
    data.scroll_speed = buf->read_i32();
    buf->read_raw(data.player_name, MAX_PLAYER_NAME);
    buf->skip(16);
    data.last_advisor = buf->read_i32();
    data.last_advisor = ADVISOR_TRADE; // debug
    buf->skip(4);                      // int save_game_mission_id;
    data.tooltips = buf->read_i32();
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    data.sound_city.enabled = buf->read_u8();
    data.warnings = buf->read_u8();
    data.monthly_autosave = buf->read_u8();
    buf->skip(1); // unsigned char autoclear_enabled;
    data.sound_effects.volume = buf->read_i32();
    data.sound_music.volume = buf->read_i32();
    data.sound_speech.volume = buf->read_i32();
    data.sound_city.volume = buf->read_i32();
    buf->skip(8); // ram
    data.window_width = buf->read_i32();
    data.window_width = 0;
    data.window_height = buf->read_i32();
    data.window_height = 0;
    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        data.personal_savings[i] = buf->read_i32();
    }
    data.victory_video = buf->read_i32();

    if (buf->at_end()) {
        // Settings file is from unpatched C3, use default values
        data.difficulty = DIFFICULTY_HARD;
        data.gods_enabled = 1;
    } else {
        data.difficulty = buf->read_i32();
        data.gods_enabled = buf->read_i32();
    }
}

void settings_load(void) {
    auto& data = settings_data();
    load_default_settings();

    // TODO: load <Pharaoh.inf>
    int size = io_read_file_into_buffer("pharaoh.inf", NOT_LOCALIZED, data.inf_file, INF_SIZE);
    if (!size)
        return;
    load_settings(data.inf_file);

    if (data.window_width + data.window_height < 500) {
        // most likely migration from Caesar 3
        data.window_width = 800;
        data.window_height = 600;
    }
}
void settings_save(void) {
    auto& data = settings_data();
    buffer* buf = data.inf_file;

    buf->skip(4);
    buf->write_i32(data.fullscreen);
    buf->skip(3);
    buf->write_u8(data.sound_effects.enabled);
    buf->write_u8(data.sound_music.enabled);
    buf->write_u8(data.sound_speech.enabled);
    buf->skip(6);
    buf->write_i32(data.game_speed);
    buf->write_i32(data.scroll_speed);
    buf->write_raw(data.player_name, MAX_PLAYER_NAME);
    buf->skip(16);
    buf->write_i32(data.last_advisor);
    buf->skip(4); // int save_game_mission_id;
    buf->write_i32(data.tooltips);
    buf->skip(4); // int starting_kingdom;
    buf->skip(4); // int personal_savings_last_mission;
    buf->skip(4); // int current_mission_id;
    buf->skip(4); // int is_custom_scenario;
    buf->write_u8(data.sound_city.enabled);
    buf->write_u8(data.warnings);
    buf->write_u8(data.monthly_autosave);
    buf->skip(1); // unsigned char autoclear_enabled;
    buf->write_i32(data.sound_effects.volume);
    buf->write_i32(data.sound_music.volume);
    buf->write_i32(data.sound_speech.volume);
    buf->write_i32(data.sound_city.volume);
    buf->skip(8); // ram
    buf->write_i32(data.window_width);
    buf->write_i32(data.window_height);
    buf->skip(8); // int max_confirmed_resolution;
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        buf->write_i32(data.personal_savings[i]);
    }
    buf->write_i32(data.victory_video);
    buf->write_i32(data.difficulty);
    buf->write_i32(data.gods_enabled);

    io_write_buffer_to_file("c3.inf", data.inf_file, INF_SIZE);
}
int setting_fullscreen(void) {
    auto& data = settings_data();
    return data.fullscreen;
}
display_size setting_display_size() {
    auto& data = settings_data();
    return {data.window_width, data.window_height};
}
void setting_set_fullscreen(int fullscreen) {
    auto& data = settings_data();
    data.fullscreen = fullscreen;
}
void setting_set_display(int width, int height) {
    auto& data = settings_data();
    data.window_width = width;
    data.window_height = height;
}

static set_sound* get_sound(int type) {
    auto& data = settings_data();
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
const set_sound* setting_sound(int type) {
    return get_sound(type);
}

bool setting_sound_is_enabled(int type) {
    return get_sound(type)->enabled;
}
void setting_toggle_sound_enabled(int type) {
    set_sound* sound = get_sound(type);
    sound->enabled = sound->enabled ? 0 : 1;
}
void setting_increase_sound_volume(int type) {
    set_sound* sound = get_sound(type);
    sound->volume = calc_bound(sound->volume + 1, 0, 100);
}
void setting_decrease_sound_volume(int type) {
    set_sound* sound = get_sound(type);
    sound->volume = calc_bound(sound->volume - 1, 0, 100);
}
void setting_reset_sound(int type, int enabled, int volume) {
    set_sound* sound = get_sound(type);
    sound->enabled = enabled;
    sound->volume = calc_bound(volume, 0, 100);
}
int setting_game_speed(void) {
    auto& data = settings_data();
    return data.game_speed;
}
void setting_increase_game_speed(void) {
    auto& data = settings_data();
    if (data.game_speed >= 100) {
        if (data.game_speed < 1000)
            data.game_speed += 100;
    } else
        data.game_speed = calc_bound(data.game_speed + 10, 10, 100);
}
void setting_decrease_game_speed(void) {
    auto& data = settings_data();
    if (data.game_speed > 100)
        data.game_speed -= 100;
    else
        data.game_speed = calc_bound(data.game_speed - 10, 10, 100);
}

int setting_scroll_speed(void) {
    auto& data = settings_data();
    return data.scroll_speed;
}
void setting_increase_scroll_speed(void) {
    auto& data = settings_data();
    data.scroll_speed = calc_bound(data.scroll_speed + 10, 0, 100);
}
void setting_decrease_scroll_speed(void) {
    auto& data = settings_data();
    data.scroll_speed = calc_bound(data.scroll_speed - 10, 0, 100);
}
void setting_reset_speeds(int game_speed, int scroll_speed) {
    auto& data = settings_data();
    data.game_speed = game_speed;
    data.scroll_speed = scroll_speed;
}

int setting_tooltips(void) {
    auto& data = settings_data();
    return data.tooltips;
}
void setting_cycle_tooltips(void) {
    auto& data = settings_data();
    switch (data.tooltips) {
    case TOOLTIPS_NONE:
        data.tooltips = TOOLTIPS_SOME;
        break;
    case TOOLTIPS_SOME:
        data.tooltips = TOOLTIPS_FULL;
        break;
    default:
        data.tooltips = TOOLTIPS_NONE;
        break;
    }
}

int setting_warnings(void) {
    auto& data = settings_data();
    return data.warnings;
}
void setting_toggle_warnings(void) {
    auto& data = settings_data();
    data.warnings = data.warnings ? 0 : 1;
}

int setting_monthly_autosave(void) {
    auto& data = settings_data();
    return data.monthly_autosave;
}
void setting_toggle_monthly_autosave(void) {
    auto& data = settings_data();
    data.monthly_autosave = data.monthly_autosave ? 0 : 1;
}

int setting_city_names_style(void) {
    auto& data = settings_data();
    return data.city_names_style;
}
void setting_toggle_city_names_style(void) {
    auto& data = settings_data();
    data.city_names_style = data.city_names_style ? 0 : 1;
}

int setting_pyramid_speedup(void) {
    auto& data = settings_data();
    return data.pyramid_speedup;
}
void setting_toggle_pyramid_speedup(void) {
    auto& data = settings_data();
    data.pyramid_speedup = data.pyramid_speedup ? 0 : 1;
}

int setting_popup_messages(void) {
    auto& data = settings_data();
    return data.popup_messages;
}
void setting_toggle_popup_messages(int flag) {
    auto& data = settings_data();
    data.popup_messages ^= flag;
}

bool setting_gods_enabled(void) {
    auto& data = settings_data();
    return data.gods_enabled;
}
void setting_toggle_gods_enabled(void) {
    auto& data = settings_data();
    data.gods_enabled = data.gods_enabled ? 0 : 1;
}

int setting_difficulty(void) {
    auto& data = settings_data();
    return data.difficulty;
}
void setting_increase_difficulty(void) {
    auto& data = settings_data();
    if (data.difficulty >= DIFFICULTY_VERY_HARD)
        data.difficulty = DIFFICULTY_VERY_HARD;
    else {
        data.difficulty++;
    }
}
void setting_decrease_difficulty(void) {
    auto& data = settings_data();
    if (data.difficulty <= DIFFICULTY_VERY_EASY)
        data.difficulty = DIFFICULTY_VERY_EASY;
    else {
        data.difficulty--;
    }
}

int setting_victory_video(void) {
    auto& data = settings_data();
    data.victory_video = data.victory_video ? 0 : 1;
    return data.victory_video;
}

int setting_last_advisor(void) {
    auto& data = settings_data();
    return data.last_advisor;
}
void setting_set_last_advisor(int advisor) {
    auto& data = settings_data();
    data.last_advisor = advisor;
}

const uint8_t* setting_player_name(void) {
    auto& data = settings_data();
    return data.player_name;
}
const char* setting_player_name_utf8(void) {
    auto& data = settings_data();
    return data.player_name_utf8;
}
void setting_set_player_name(const uint8_t* player_name) {
    auto& data = settings_data();
    string_copy(player_name, data.player_name, MAX_PLAYER_NAME);
    encoding_to_utf8(player_name, data.player_name_utf8, MAX_PLAYER_NAME, 0);
}

int setting_personal_savings_for_mission(int mission_id) {
    auto& data = settings_data();
    return data.personal_savings[mission_id];
}
void setting_set_personal_savings_for_mission(int mission_id, int savings) {
    auto& data = settings_data();
    data.personal_savings[mission_id] = savings;
}
void setting_clear_personal_savings(void) {
    auto& data = settings_data();
    for (int i = 0; i < MAX_PERSONAL_SAVINGS; i++) {
        data.personal_savings[i] = 0;
    }
}
