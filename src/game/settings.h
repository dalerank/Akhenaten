#pragma once

#include <stdint.h>
#include "core/bstring.h"
#include "core/vec2i.h"
#include "core/calc.h"

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

struct sound_settings {
    bool enabled;
    int volume;
};

struct game_settings {
    static constexpr int MAX_PERSONAL_SAVINGS = 100;
    // display settings
    vec2i display_size;
    // sound settings
    sound_settings sound_effects;
    sound_settings sound_music;
    sound_settings sound_speech;
    sound_settings sound_city;
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

    void load_default_settings();
    void load();
    void save();
    inline bool is_fullscreen() { return fullscreen && cli_fullscreen; }

    void set_cli_fullscreen(bool fullscreen) { cli_fullscreen = fullscreen; }
    void set_fullscreen(bool fullscreen) { fullscreen = fullscreen; }
    bool sound_is_enabled(int type) { return get_sound(type)->enabled; }
    sound_settings *get_sound(int type);

    void toggle_sound_enabled(int type) {
        auto sound = get_sound(type);
        sound->enabled = sound->enabled ? 0 : 1;
    }

    void increase_sound_volume(int type) {
        auto sound = get_sound(type);
        sound->volume = calc_bound(sound->volume + 1, 0, 100);
    }

    void decrease_sound_volume(int type) {
        auto* sound = get_sound(type);
        sound->volume = calc_bound(sound->volume - 1, 0, 100);
    }

    void reset_sound(int type, int enabled, int volume) {
        auto* sound = get_sound(type);
        sound->enabled = enabled;
        sound->volume = calc_bound(volume, 0, 100);
    }

    void increase_game_speed();
    void decrease_game_speed();

    void increase_scroll_speed() { scroll_speed = calc_bound(scroll_speed + 10, 0, 100); }
    void decrease_scroll_speed() { scroll_speed = calc_bound(scroll_speed - 10, 0, 100); }

    void toggle_tooltips();
    void toggle_warnings() { warnings = !warnings; }
    void toggle_monthly_autosave() { monthly_autosave = !monthly_autosave; }
    void toggle_city_names_style() { city_names_style = !city_names_style; }

private:
    void load_settings(buffer *buf);

    bool fullscreen;
    bool cli_fullscreen;
};

extern game_settings g_settings;

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
