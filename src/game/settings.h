#pragma once

#include <stdint.h>
#include "core/tokenum.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "core/calc.h"
#include "game/game_config.h"

class buffer;

enum e_tooltip_mode {
    e_tooltip_mode_none = 0,
    e_tooltip_mode_some = 1,
    e_tooltip_mode_full = 2,
    e_tooltip_count,
};
using etooltip_flag = uint32_t;

enum e_setting_flag {
    e_setting_none = 0,
    e_setting_cli = 1,
};
using esetting_flag = uint32_t;

enum e_difficulty {
    DIFFICULTY_VERY_EASY = 0,
    DIFFICULTY_EASY = 1,
    DIFFICULTY_NORMAL = 2,
    DIFFICULTY_HARD = 3,
    DIFFICULTY_VERY_HARD = 4
};
uint8_t game_difficulty();

enum e_sound_type {
    SOUND_NONE = 0,
    SOUND_MUSIC = 1,
    SOUND_SPEECH = 2,
    SOUND_EFFECTS = 3,
    SOUND_CITY = 4,

    SOUND_COUNT
};
using e_sound_type_tokens_t = token_holder<e_sound_type, SOUND_NONE, SOUND_COUNT>;

enum {
    CITIES_OLD_NAMES = 0,
    CITIES_NEW_NAMES = 1
};

struct game_settings {
    static constexpr uint8_t MAX_PERSONAL_SAVINGS = 100;
    static constexpr uint8_t MAX_DIFFICULTY_LEVEL = 4;
    // display settings
    vec2i display_size;

    e_tooltip_mode tooltips_mode;
    bool warnings;
    bool gods_enabled;
    bool victory_video;
    // pharaoh settings
    int popup_messages;
    bool pyramid_speedup;
    // persistent game state
    int last_advisor;
    bstring32 player_name;
    bstring32 player_name_utf8;
    // personal savings
    int personal_savings[MAX_PERSONAL_SAVINGS] = {0};
    // file data
    buffer *inf_file = nullptr;

    struct difficulty_t {
        void increase() { _state = std::clamp<e_difficulty>((e_difficulty)(_state + 1), DIFFICULTY_VERY_EASY, DIFFICULTY_VERY_HARD); }
        void decrease() { _state = std::clamp<e_difficulty>((e_difficulty)(_state - 1), DIFFICULTY_VERY_EASY, DIFFICULTY_VERY_HARD); }

        inline e_difficulty operator()() const { return _state; }
        void set(e_difficulty v) { _state = std::clamp<e_difficulty>(v, DIFFICULTY_VERY_EASY, DIFFICULTY_VERY_HARD); }

    private:
        e_difficulty _state;
    } difficulty;

    game_settings();

    void load_default_settings();
    void load();
    void save();
    inline bool is_fullscreen(esetting_flag opt = e_setting_cli) { return fullscreen && ((opt == e_setting_cli) ? cli_fullscreen : true); }

    void set_cli_fullscreen(bool v) { cli_fullscreen = v; }
    void set_fullscreen(bool v) { fullscreen = v; }

    void reset_sound(int type, int enabled, int volume) {
        if (type == SOUND_MUSIC) {
            game_features::gameopt_sound_music_enabled.set(!!enabled);
            game_features::gameopt_sound_music_volume.set((float)calc_bound(volume, 0, 100));
            return;
        }
        if (type == SOUND_EFFECTS) {
            game_features::gameopt_sound_effects_enabled.set(!!enabled);
            game_features::gameopt_sound_effects_volume.set((float)calc_bound(volume, 0, 100));
            return;
        }
        if (type == SOUND_SPEECH) {
            game_features::gameopt_sound_speech_enabled.set(!!enabled);
            game_features::gameopt_sound_speech_volume.set((float)calc_bound(volume, 0, 100));
            return;
        }
        if (type == SOUND_CITY) {
            game_features::gameopt_sound_city_enabled.set(!!enabled);
            game_features::gameopt_sound_city_volume.set((float)calc_bound(volume, 0, 100));
            return;
        }
    }

    void toggle_warnings() { warnings = !warnings; }
    void toggle_pyramid_speedup() { pyramid_speedup = !pyramid_speedup; }
    void toggle_popup_messages(int flag) { popup_messages ^= flag; }
    void toggle_gods_enabled() { gods_enabled = !gods_enabled; }

    bool show_victory_video() { victory_video = !victory_video; return victory_video; }
    void set_player_name(const uint8_t* player_name);
    void set_player_name_utf8(pcstr name_utf8);

    int personal_savings_for_mission(int mission_id) { return personal_savings[mission_id]; }
    void set_personal_savings_for_mission(int mission_id, int savings) { personal_savings[mission_id] = savings; }

    void clear_personal_savings(void);

private:
    void load_settings(buffer *buf);

    bool fullscreen;
    bool cli_fullscreen;
};

extern game_settings g_settings;