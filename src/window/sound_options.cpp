#include "sound_options.h"

#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "sound/sound_city.h"
#include "sound/effect.h"
#include "sound/music.h"
#include "sound/sound.h"

static void button_toggle(int type, int param2);
static void button_ok(int param1, int param2);
static void button_cancel(int param1, int param2);

static void arrow_button_music(int is_down, int param2);
static void arrow_button_speech(int is_down, int param2);
static void arrow_button_effects(int is_down, int param2);
static void arrow_button_city(int is_down, int param2);

static generic_button buttons[] = {
  {64, 162, 224, 20, button_toggle, button_none, SOUND_MUSIC, 0},
  {64, 192, 224, 20, button_toggle, button_none, SOUND_SPEECH, 0},
  {64, 222, 224, 20, button_toggle, button_none, SOUND_EFFECTS, 0},
  {64, 252, 224, 20, button_toggle, button_none, SOUND_CITY, 0},
  {144, 296, 192, 20, button_ok, button_none, 1, 0},
  {144, 326, 192, 20, button_cancel, button_none, 1, 0},
};

static arrow_button arrow_buttons[] = {
  {112, 100, 17, 24, arrow_button_music, 1, 0},
  {136, 100, 15, 24, arrow_button_music, 0, 0},
  {112, 130, 17, 24, arrow_button_speech, 1, 0},
  {136, 130, 15, 24, arrow_button_speech, 0, 0},
  {112, 160, 17, 24, arrow_button_effects, 1, 0},
  {136, 160, 15, 24, arrow_button_effects, 0, 0},
  {112, 190, 17, 24, arrow_button_city, 1, 0},
  {136, 190, 15, 24, arrow_button_city, 0, 0},
};

struct sound_options_data_t {
    int focus_button_id;
    void (*close_callback)(void);

    sound_settings original_effects;
    sound_settings original_music;
    sound_settings original_speech;
    sound_settings original_city;
};

sound_options_data_t g_sound_options;

static void init(void (*close_callback)()) {
    auto &data = g_sound_options;
    data.focus_button_id = 0;
    data.close_callback = close_callback;

    data.original_effects = *g_settings.get_sound(SOUND_EFFECTS);
    data.original_music = *g_settings.get_sound(SOUND_MUSIC);
    data.original_speech = *g_settings.get_sound(SOUND_SPEECH);
    data.original_city = *g_settings.get_sound(SOUND_CITY);
}

static void draw_foreground(int) {
    auto &data = g_sound_options;
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{ 48, 80 }, 24, 18);

    // on/off labels
    small_panel_draw({ 64, 162 }, 14, data.focus_button_id == 1 ? 1 : 2);
    small_panel_draw({ 64, 192 }, 14, data.focus_button_id == 2 ? 1 : 2);
    small_panel_draw({ 64, 222 }, 14, data.focus_button_id == 3 ? 1 : 2);
    small_panel_draw({ 64, 252 }, 14, data.focus_button_id == 4 ? 1 : 2);
    // ok/cancel labels
    small_panel_draw({ 144, 296 }, 12, data.focus_button_id == 5 ? 1 : 2);
    small_panel_draw({ 144, 326 }, 12, data.focus_button_id == 6 ? 1 : 2);

    // title
    lang_text_draw_centered(46, 0, 96, 92, 288, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw_centered(46, 12, 128, 300, 224, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(46, 9, 128, 330, 224, FONT_NORMAL_BLACK_ON_DARK);

    lang_text_draw(46, 10, 112, 142, FONT_SMALL_PLAIN);
    lang_text_draw(46, 11, 336, 142, FONT_SMALL_PLAIN);

    const auto* music = g_settings.get_sound(SOUND_MUSIC);
    lang_text_draw_centered(46, music->enabled ? 2 : 1, 64, 166, 224, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_percentage(music->volume, 374, 166, FONT_SMALL_PLAIN);

    const auto* speech = g_settings.get_sound(SOUND_SPEECH);
    lang_text_draw_centered(46, speech->enabled ? 4 : 3, 64, 196, 224, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_percentage(speech->volume, 374, 196, FONT_SMALL_PLAIN);

    const auto* effects = g_settings.get_sound(SOUND_EFFECTS);
    lang_text_draw_centered(46, effects->enabled ? 6 : 5, 64, 226, 224, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_percentage(effects->volume, 374, 226, FONT_SMALL_PLAIN);

    const auto* city = g_settings.get_sound(SOUND_CITY);
    lang_text_draw_centered(46, city->enabled ? 8 : 7, 64, 256, 224, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_percentage(city->volume, 374, 256, FONT_SMALL_PLAIN);

    arrow_buttons_draw(/*{208, 60},*/ arrow_buttons, 8);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_sound_options;
    const mouse* m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, {0, 0}, buttons, 6, &data.focus_button_id)
        || arrow_buttons_handle_mouse(m_dialog, /*{208, 60}*/ arrow_buttons, 8, 0))
        return;

    if (input_go_back_requested(m, h)) {
        data.close_callback();
    }
}

static void button_toggle(int type, int param2) {
    auto &data = g_sound_options;
    g_settings.toggle_sound_enabled(type);
    if (type == SOUND_MUSIC) {
        if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
            g_sound.music_update(true);
        } else {
            g_sound.music_stop();
        }
    } else if (type == SOUND_SPEECH) {
        if (!g_settings.get_sound(SOUND_SPEECH)->enabled)
            g_sound.speech_stop();
    }
}

static void button_ok(int param1, int param2) {
    auto &data = g_sound_options;
    data.close_callback();
}

static void button_cancel(int param1, int param2) {
    auto &data = g_sound_options;
    g_settings.reset_sound(SOUND_EFFECTS, data.original_effects.enabled, data.original_effects.volume);
    g_settings.reset_sound(SOUND_MUSIC, data.original_music.enabled, data.original_music.volume);
    g_settings.reset_sound(SOUND_SPEECH, data.original_speech.enabled, data.original_speech.volume);
    g_settings.reset_sound(SOUND_CITY, data.original_city.enabled, data.original_city.volume);
    if (data.original_music.enabled) {
        if (g_settings.sound_is_enabled(SOUND_MUSIC) != data.original_music.enabled) {
            g_sound.music_update(true);
        }
    } else {
        g_sound.music_stop();
    }

    g_sound.music_set_volume(data.original_music.volume);
    g_sound.speech_set_volume(data.original_speech.volume);
    g_sound.set_volume(SOUND_CHANNEL_EFFECTS_MIN, SOUND_CHANNEL_EFFECTS_MAX, data.original_effects.volume);
    g_sound.set_volume(SOUND_CHANNEL_CITY_MIN, SOUND_CHANNEL_CITY_MAX, data.original_city.volume);

    data.close_callback();
}

static void update_volume(int type, int is_decrease) {
    if (is_decrease) {
        g_settings.decrease_sound_volume(type);
    } else {
        g_settings.increase_sound_volume(type);
    }
}

static void arrow_button_music(int is_down, int param2) {
    update_volume(SOUND_MUSIC, is_down);
    g_sound.music_set_volume(g_settings.get_sound(SOUND_MUSIC)->volume);
}

static void arrow_button_speech(int is_down, int param2) {
    update_volume(SOUND_SPEECH, is_down);
    g_sound.speech_set_volume(g_settings.get_sound(SOUND_SPEECH)->volume);
}

static void arrow_button_effects(int is_down, int param2) {
    update_volume(SOUND_EFFECTS, is_down);
    g_sound.set_volume(SOUND_CHANNEL_EFFECTS_MIN, SOUND_CHANNEL_EFFECTS_MAX, g_settings.get_sound(SOUND_EFFECTS)->volume);
}

static void arrow_button_city(int is_down, int param2) {
    update_volume(SOUND_CITY, is_down);
    g_sound.set_volume(SOUND_CHANNEL_CITY_MIN, SOUND_CHANNEL_CITY_MAX, g_settings.get_sound(SOUND_CITY)->volume);
}

void window_sound_options_show(void (*close_callback)(void)) {
    static window_type window = {
      WINDOW_SOUND_OPTIONS,
      window_draw_underlying_window,
      draw_foreground,
      handle_input,
    };
    init(close_callback);
    window_show(&window);
}
