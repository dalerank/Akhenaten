#include "intermezzo.h"

#include "content/vfs.h"
#include "core/game_environment.h"
#include "core/time.h"
#include "core/log.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/screen.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "sound/music.h"
#include "sound/sound.h"
#include "sound/sound_mission.h"
#include "game/game.h"

#include <map>

#define DISPLAY_TIME_MILLIS 1200

static pcstr SOUND_FILE_LOSE = "Wavs/lose_game.wav";

struct intermezzo_data_t {
    intermezzo_type type;
    void (*callback)(void);
    time_millis start_time;
};

intermezzo_data_t g_intermezzo_data;

static void init(intermezzo_type type, void (*callback)(void)) {
    g_intermezzo_data.type = type;
    g_intermezzo_data.callback = callback;
    g_intermezzo_data.start_time = time_get_millis();
    sound_music_stop();
    g_sound.speech_stop();

    // play briefing sound by mission number
    if (g_intermezzo_data.type == INTERMEZZO_FIRED) {
        g_sound.speech_play_file(SOUND_FILE_LOSE, 255);
    } else if (!scenario_is_custom()) {
        int mission = scenario_campaign_scenario_id();

        auto conf = snd::get_mission_config(mission);
        if (conf.briefing.empty()) {
            logs::info("Intermezzo: can't found sound for mission %u", mission);
            return;
        }

        vfs::path file2play = conf.briefing;
        if (g_intermezzo_data.type == INTERMEZZO_WON) {
            file2play = conf.won;
        }

        g_sound.speech_play_file(file2play, 255);
    }
}

static void draw_background(int) {
    graphics_clear_screen();
    graphics_reset_dialog();
    vec2i offset = vec2i{screen_width() - 1024, screen_height() - 768} / 2;

    // draw background by mission
    int mission = scenario_campaign_scenario_id();
    int image_base = image_id_from_group(GROUP_INTERMEZZO_BACKGROUND);
    painter ctx = game.painter();
    if (g_intermezzo_data.type == INTERMEZZO_MISSION_BRIEFING) {
        ImageDraw::img_generic(ctx, scenario_is_custom() ? image_base + 1 : image_base + 1 + (mission >= 20), offset);

    } else if (g_intermezzo_data.type == INTERMEZZO_FIRED) {
        ImageDraw::img_generic(ctx, image_base, offset);

    } else if (g_intermezzo_data.type == INTERMEZZO_WON) {
        ImageDraw::img_generic(ctx, scenario_is_custom() ? image_base + 2 : image_base, offset);
    }
}

static void handle_input(const mouse* m, const hotkeys* h) {
    time_millis current_time = time_get_millis();
    if (m->right.went_up || (m->is_touch && m->left.double_click)
        || current_time - g_intermezzo_data.start_time > DISPLAY_TIME_MILLIS) {
        g_intermezzo_data.callback();
    }
}

void window_intermezzo_show(intermezzo_type type, void (*callback)()) {
    window_type window = {
        WINDOW_INTERMEZZO,
        draw_background,
        nullptr,
        handle_input
    };
    init(type, callback);
    window_show(&window);
}
