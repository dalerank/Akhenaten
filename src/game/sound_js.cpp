#include "core/profiler.h"
#include "js/js_defines.h"
#include "js/js_game.h"
#include "sound/sound.h"

static void js_sound_set_volume(js_State *J) {
    g_sound.set_volume(js_tointeger(J, 1), js_tointeger(J, 2), js_tointeger(J, 3));
    J->pushundefined();
}

static void js_sound_music_stop(js_State *J) {
    g_sound.music_stop();
    J->pushundefined();
}

static void js_sound_music_update(js_State *J) {
    g_sound.music_update(!!js_tointeger(J, 1));
    J->pushundefined();
}

static void js_sound_speech_stop(js_State *J) {
    g_sound.speech_stop();
    J->pushundefined();
}

void js_register_sound_object(js_State* J) {
    js_getglobal(J, "__game_sound");
    if (J->isobject(-1)) {
        js_pop(J, 1);
        return;
    }
    js_pop(J, 1);

    js_newobject(J);
    REGISTER_FUNCTION(J, js_sound_set_volume, "set_volume", 3);
    REGISTER_FUNCTION(J, js_sound_music_stop, "music_stop", 0);
    REGISTER_FUNCTION(J, js_sound_music_update, "music_update", 1);
    REGISTER_FUNCTION(J, js_sound_speech_stop, "speech_stop", 0);
    js_setglobal(J, "__game_sound");
}
