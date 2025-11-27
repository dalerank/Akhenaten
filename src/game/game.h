#pragma once

#include "graphics/painter.h"
#include "graphics/animation.h"
#include "overlays/city_overlay_fwd.h"
#include "core/xstring.h"
#include "core/threading.h"
#include "game/simulation_time.h"
#include "game/game_events.h"
#include "core/system_time.h"

enum game_option {
    game_opt_none = 0,
    game_opt_sound = 1,
};

using game_opts = uint32_t;

bool game_init(game_opts opts);

bool game_init_editor();

int game_reload_language();

void game_exit_editor();

struct fps_data_t {
    int frame_count;
    int last_fps;
    uint32_t last_update_time;
};

enum e_session_type {
    e_session_none = -1,
    e_session_mission = 0,
    e_session_save = 1,
    e_session_custom_map = 2
};

class MovieWriter;
struct event_game_mission_pre_load {};

struct game_t {
    enum {
        MAX_ANIM_TIMERS = 51
    };

    bool paused = false;
    bool save_debug_texture = false;
    bool animation = false;
    bool debug_console = false;
    bool debug_properties = false;
    uint16_t game_speed;
    uint32_t frame = 0;
    uint16_t last_frame_tick = 0;
    color *frame_pixels = nullptr;
    bool write_video = false;
    bool system_language_changed = false;

    MovieWriter *mvwriter = nullptr;
    simulation_time_t simtime;

    struct {
        xstring last_loaded_mission;
        e_session_type last_loaded = e_session_none;
        bool active = false;
    } session;

    fps_data_t fps = {0, 0, 0};
    animation_timer animation_timers[MAX_ANIM_TIMERS];

    void animation_timers_init();
    void animation_timers_update();
    bool animation_should_advance(uint32_t speed);
    void write_frame();
    void reload_objects();

    void set_write_video(bool v);
    bool get_write_video() const { return write_video; }

    void update();
    void update_tick(int simtick);

    void advance_day();
    void advance_week();
    void advance_month();
    void advance_year();

    void shutdown();
    bool check_valid();

    void exit();

    void frame_begin();
    void frame_end();

    void time_init(int year);

    void sound_frame_begin();
    void before_start_simulation();
    void handle_input_frame();

    void increase_game_speed();
    void decrease_game_speed();

    threading::thread_pool mtrpc;
    threading::thread_pool mt;

    ::painter painter();
};

extern game_t game;
