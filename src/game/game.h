#pragma once

#include "graphics/painter.h"
#include "graphics/animation.h"
#include "overlays/city_overlay_fwd.h"
#include "core/xstring.h"
#include "core/threading.h"
#include "game/simulation_time.h"
#include "game/game_events.h"
#include "core/system_time.h"
#include "core/inplace_function.h"
#include "core/hvector.h"

enum game_option {
    game_opt_none = 0,
    game_opt_sound = 1,
};

using game_opts = uint32_t;

bool game_init(game_opts opts);

bool game_init_editor();

void game_reload_language();

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
struct event_game_scripts_was_reloaded {};

struct game_t {
    using serial_event_t = inplace_function<void()>;

    enum {
        MAX_ANIM_TIMERS = 51
    };

    uint16_t scroll_speed;
    bool monthly_autosave;
    bool paused = false;
    bool save_debug_texture = false;
    bool animation = false;
    bool debug_console = false;
    bool debug_properties = false;
    bool debug_perfmon = false;
    uint16_t game_speed;
    uint32_t frame = 0;
    uint16_t last_frame_tick = 0;
    color *frame_pixels = nullptr;
    bool write_video = false;
    bool system_language_changed = false;
    uint8_t pending_load_type = 0;
    uint8_t pending_save_type = 0;

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

    void increase_scroll_speed();
    void decrease_scroll_speed();

    void reload_language();
    void add_frame_end_event(serial_event_t ev);
    void execute_frame_end_events();

    threading::thread_pool mtrpc;
    threading::thread_pool mt;

    std::mutex frame_end_events_mutex;
    hvector<serial_event_t, 16> frame_end_events;

    ::painter painter();
};
ANK_CONFIG_PROPERTY(game_t,
    game_speed, scroll_speed, monthly_autosave, pending_load_type, pending_save_type)

extern game_t game;
