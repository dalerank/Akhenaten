#pragma once

#include <stdint.h>
#include "core/bstring.h"

class buffer;

enum { 
    TOOLTIPS_NONE = 0,
    TOOLTIPS_SOME = 1,
    TOOLTIPS_FULL = 2
};

enum e_difficulty {
    DIFFICULTY_VERY_EASY = 0,
    DIFFICULTY_EASY = 1,
    DIFFICULTY_NORMAL = 2,
    DIFFICULTY_HARD = 3,
    DIFFICULTY_VERY_HARD = 4
};

enum e_sound_type {
    SOUND_MUSIC = 1,
    SOUND_SPEECH = 2,
    SOUND_EFFECTS = 3,
    SOUND_CITY = 4,
};

enum {
    CITIES_OLD_NAMES = 0,
    CITIES_NEW_NAMES = 1
};

struct set_sound {
    bool enabled;
    int volume;
};

struct display_size {
    int w, h;
};

struct game_settings {
    static constexpr int MAX_PERSONAL_SAVINGS = 100;
    // display settings
    bool fullscreen;
    bool cli_fullscreen;
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
    e_difficulty difficulty;
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
    bstring32 player_name;
    bstring32 player_name_utf8;
    // personal savings
    int personal_savings[MAX_PERSONAL_SAVINGS] = {0};
    // file data
    buffer *inf_file = nullptr;

    game_settings();
};

extern game_settings g_settings;

void settings_load();
void settings_save();

int setting_fullscreen();
display_size setting_display_size();
void setting_set_fullscreen(bool fullscreen);
void setting_set_cli_fullscreen(bool fullscreen);
void setting_set_display(int width, int height);

const set_sound* setting_sound(int type);

bool setting_sound_is_enabled(int type);
void setting_toggle_sound_enabled(int type);
void setting_increase_sound_volume(int type);
void setting_decrease_sound_volume(int type);
void setting_reset_sound(int type, int enabled, int volume);

int setting_game_speed(void);
void setting_increase_game_speed(void);
void setting_decrease_game_speed(void);

int setting_scroll_speed(void);
void setting_increase_scroll_speed(void);
void setting_decrease_scroll_speed(void);
void setting_reset_speeds(int game_speed, int scroll_speed);

int setting_tooltips(void);
void setting_cycle_tooltips(void);

int setting_warnings(void);
void setting_toggle_warnings(void);

int setting_monthly_autosave(void);
void setting_toggle_monthly_autosave(void);

int setting_city_names_style(void);
void setting_toggle_city_names_style(void);

int setting_pyramid_speedup(void);
void setting_toggle_pyramid_speedup(void);

int setting_popup_messages(void);
void setting_toggle_popup_messages(int flag);

bool setting_gods_enabled(void);
void setting_toggle_gods_enabled(void);

int setting_difficulty(void);
void setting_increase_difficulty(void);
void setting_decrease_difficulty(void);

int setting_victory_video(void);

int setting_last_advisor(void);
void setting_set_last_advisor(int advisor);

const uint8_t* setting_player_name(void);
const char* setting_player_name_utf8(void);
void setting_set_player_name(const uint8_t* player_name);

int setting_personal_savings_for_mission(int mission_id);
void setting_set_personal_savings_for_mission(int mission_id, int savings);
void setting_clear_personal_savings(void);
