#include "js_game.h"

#include "js/js_defines.h"

#include "content/vfs.h"
#include "core/log.h"
#include "mujs/mujs.h"

#include "sound/system.h"
#include "sound/sound_mission.h"
#include "sound/sound_building.h"
#include "sound/sound_walker.h"

#include "overlays/city_overlay.h"
#include "figure/figure.h"

#include <vector>

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
    size_t bytes = fread(text, 1, fsize, ftext);
    fclose(ftext);

    text[fsize] = 0;
    js_pushstring(J, text);
    free(text);
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

template<typename Arch>
inline int read_integer(Arch arch, pcstr name) {
    js_getproperty(arch, -1, name);
    int result = js_tointeger(arch, -1);
    js_pop(arch, 1);
    return result;
}

template<typename T = int, typename Arch>
inline std::vector<T> read_integer_array(Arch arch, pcstr name) {
    js_getproperty(arch, -1, name);
    std::vector<T> result;
    if (js_isarray(arch, -1)) {
        int length = js_getlength(arch, -1);

        for (int i = 0; i < length; ++i) {
            js_getindex(arch, -1, i);
            int v = js_tointeger(arch, -1);
            result.push_back((T)v);
            js_pop(arch, 1);
        }
        js_pop(arch, 1);
    }
    return result;
}

void js_config_load_building_sounds(js_State *arch) {
    js_config_load_global_array(arch, "building_sounds", [] (auto arch) {
        const char *type = read_string(arch, "type");
        const char *path = read_string(arch, "sound");
        snd::set_building_info_sound(type, path);
    });
}

void js_config_load_mission_sounds(js_State *arch) {
    js_config_load_global_array(arch, "mission_sounds", [] (auto arch) {
        const int mission = read_integer(arch, "mission");
        const char *inter = read_string(arch, "briefing");
        const char *won = read_string(arch, "victory");
        snd::set_mission_config(mission, inter, won);
    });
}

void js_config_load_walker_sounds(js_State *arch) {
    js_config_load_global_array(arch, "walker_sounds", [] (auto arch) {
        const char *type = read_string(arch, "type");
        const char *path = read_string(arch, "sound");
        snd::set_walker_reaction(type, path);
    });
}

void js_config_load_city_sounds(js_State *arch) {
    js_config_load_global_array(arch, "city_sounds", [] (auto arch) {
        const int channel = read_integer(arch, "c");
        const char *path = read_string(arch, "p");
        sound_system_update_channel(channel, path);
    });
}

void js_config_load_city_overlays(js_State *arch) {
    js_config_load_global_array(arch, "overlays", [] (auto arch) {
        const int e_v = read_integer(arch, "id");
        const char *caption = read_string(arch, "caption");
        auto walkers = read_integer_array<e_figure_type>(arch, "walkers");
        auto buildings = read_integer_array<e_building_type>(arch, "buildings");
        int tooltip_base = read_integer(arch, "tooltip_base");
        auto tooltips = read_integer_array(arch, "tooltips");
        auto overlay = get_city_overlay((e_overlay)e_v);

        if (overlay) {
            if (tooltip_base) { overlay->tooltip_base = tooltip_base; }
            if (buildings.size()) { overlay->buildings = buildings; }
            if (*caption) { overlay->caption = caption; }
            if (tooltips.size()) { overlay->tooltips = tooltips; }
            if (walkers.size()) { overlay->walkers = walkers; }
        }
    });
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_info, "log_info", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_warn, "log_warning", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
}