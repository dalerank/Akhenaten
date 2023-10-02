#include "js_game.h"

#include "js/js_defines.h"

#include "content/vfs.h"
#include "core/log.h"
#include "mujs/mujs.h"

#include "sound/system.h"
#include "sound/sound_mission.h"
#include "sound/sound_building.h"
#include "sound/sound_walker.h"

void js_game_log_info(js_State *J) {
    if (js_isundefined(J, 1)) {
        logs::info("log() Try to print undefined object", 0, 0);
    } else {
        logs::info("%s", js_tostring(J, 1));
    }

    js_pushundefined(J);
}

void js_game_log_warn(js_State *J) {
    if (js_isundefined(J, 1)) {
        logs::info("warning() Try to print undefined object", 0, 0);
    } else {
        logs::info("WARN: ", js_tostring(J, 1), 0);
    }

    js_pushundefined(J);
}

void js_game_load_text(js_State *J) {
    const char *path = js_tostring(J, 1);
    char *text = 0;

    FILE *ftext = vfs::file_open(path, "rb");
    fseek(ftext, 0, SEEK_END);
    long fsize = ftell(ftext);
    fseek(ftext, 0, SEEK_SET);  /* same as rewind(f); */

    text = (char *)malloc(fsize + 1);
    int bytes = fread(text, 1, fsize, ftext);
    fclose(ftext);

    text[fsize] = 0;
    js_pushstring(J, text);
    free(text);
}

void js_sound_system_update_channel(js_State *J) {
    const int channel = js_tointeger(J, 1);
    const char *path = js_tostring(J, 2);

    sound_system_update_channel(channel, path);
}

void js_sound_system_mission_config(js_State *J) {
    const int mission = js_tointeger(J, 1);
    const char *inter = js_tostring(J, 2);
    const char *won = js_tostring(J, 3);

    snd::set_mission_config(mission, inter, won);
}

void js_sound_system_walker_reaction(js_State *J) {
    const char *type = js_tostring(J, 1);
    const char *path = js_tostring(J, 2);

    snd::set_walker_reaction(type, path);
}

template<typename Arch, typename T>
inline void js_config_load_global_array(Arch arch, pcstr name, T read_func) {
    js_getglobal(arch, name);
    if (js_isarray(arch, -1)) {
        int length = js_getlength(arch, -1);

        for (int i = 0; i < length; ++i) {
            js_getindex(arch, -1, i);

            if (js_isobject(arch, -1)) {
                read_func(arch);
            }

            js_pop(arch, 1);
        }
        js_pop(arch, 1);
    }
}

template<typename Arch>
inline pcstr read_string(Arch arch, pcstr name) {
    js_getproperty(arch, -1, name);
    const char *result = js_tostring(arch, -1);
    js_pop(arch, 1);
    return result;
}

void js_config_load_building_sounds(js_State *arch) {
    js_config_load_global_array(arch, "building_sounds", [] (auto arch) {
        const char *type = read_string(arch, "type");
        const char *path = read_string(arch, "sound");
        snd::set_building_info_sound(type, path);
    });
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_info, "log_info", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_warn, "log_warning", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_sound_system_update_channel, "sound_system_update_channel", 2);
    REGISTER_GLOBAL_FUNCTION(J, js_sound_system_mission_config, "sound_system_mission_config", 3);
    REGISTER_GLOBAL_FUNCTION(J, js_sound_system_walker_reaction, "sound_system_walker_reaction", 2);
}