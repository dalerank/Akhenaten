#include "core/profiler.h"
#include "js/js_defines.h"
#include "js/js_game.h"
#include "js/js_mujs_bound_offset.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "sound/channel.h"
#include "sound/sound.h"
#include "sound/sound_city.h"

#include <cstdio>

using sound_channel_t = sound_manager_t::channel_t;

void __sound_city_init() { sound_city_init(); }
ANK_FUNCTION(__sound_city_init)

void __sound_city_stop() { sound_city_stop(); }
ANK_FUNCTION(__sound_city_stop)

int __sound_channel_count() {
    return static_cast<int>(g_sound.channels().size());
}
ANK_FUNCTION(__sound_channel_count)

static js_Object *g_sound_channel_proto = nullptr;

static int sound_channel_this_index(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("index"));
    const int index = static_cast<int>(js_tointeger(J, -1));
    js_pop(J, 1);
    return index;
}

static sound_channel_t *sound_channel_this(js_State *J) {
    const int index = sound_channel_this_index(J);
    const auto channels = g_sound.channels();
    if (index < 0 || index >= static_cast<int>(channels.size())) {
        return nullptr;
    }
    return &channels[index];
}

static void js_push_sound_channel(js_State *J, int index) {
    const auto channels = g_sound.channels();
    if (index < 0 || index >= static_cast<int>(channels.size())) {
        index = 0;
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_sound_channel_proto));
    js_pushnumber(J, static_cast<double>(index));
    js_setproperty(J, -2, js_intern("index"));
    js_register_cobj_ptr_property(J, &channels[index]);
}

static void sound_channel_proto_filename(js_State *J) {
    const sound_channel_t *ch = sound_channel_this(J);
    J->pushstring(ch ? ch->filename.c_str() : "");
}

static void sound_channel_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "SoundChannel(%d)", sound_channel_this_index(J));
    J->pushstring(buf);
}

static void jsB_new_SoundChannel(js_State *J) {
    const int index = js_gettop(J) > 1 ? static_cast<int>(js_tointeger(J, 1)) : 0;
    js_push_sound_channel(J, index);
}

static void js_register_sound_channel_proto(js_State *J) {
    g_sound_channel_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_sound_channel_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, sound_channel_t, left_pan);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, sound_channel_t, right_pan);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, sound_channel_t, volume);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, sound_channel_t, playing);
    jsB_propf(J, js_intern("SoundChannel.prototype.filename"), sound_channel_proto_filename, 0);
    jsB_propf(J, js_intern("SoundChannel.prototype.toString"), sound_channel_proto_toString, 0);
    js_newcconstructor(J, jsB_new_SoundChannel, jsB_new_SoundChannel, js_intern("SoundChannel"), 1);
    js_defglobal(J, js_intern("SoundChannel"), JS_DONTENUM);
}

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

static void js_sound_play_intro(js_State *J) {
    g_sound.play_intro();
    J->pushundefined();
}

void js_register_sound_object(js_State *J) {
    js_register_sound_channel_proto(J);

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
    REGISTER_FUNCTION(J, js_sound_play_intro, "play_intro", 0);
    js_setglobal(J, "__game_sound");
}
