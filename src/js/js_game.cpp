#include "js_game.h"

#include "content/vfs.h"
#include "core/log.h"

#include "sound/system.h"
#include "sound/sound_mission.h"
#include "sound/sound_building.h"
#include "sound/sound_walker.h"

#include "overlays/city_overlay.h"
#include "graphics/image_desc.h"
#include "figure/figure.h"
#include "figure/image.h"
#include "io/gamefiles/lang.h"
#include "platform/version.hpp"
#include "graphics/screen.h"

#include "js.h"

#include <vector>

g_archive g_config_arch{nullptr};

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

void js_game_set_image(js_State *J) {
    if (js_isobject(J, 1)) {
        archive arch{js_vm_state()};
        int img = arch.r_int("img");
        int pack = arch.r_int("pack");
        int id = arch.r_int("id");
        int offset = arch.r_int("offset");
        set_image_desc(img, pack, id, offset);
        js_pop(J, 1);
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

void js_register_game_objects(js_State *J) {
    js_newobject(J);
    {
        js_pushstring(J, get_version().c_str()); 
        js_setproperty(J, -2, "version");

        js_newobject(J);
            js_pushnumber(J, screen_width()); js_setproperty(J, -2, "w");
            js_pushnumber(J, screen_height()); js_setproperty(J, -2, "h");
        js_setproperty(J, -2, "screen");
    }
    js_setglobal(J, "game");
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_info, "log_info", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_warn, "log_warning", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_set_image, "set_image", 1);
}

namespace config {
    FuncLinkedList *FuncLinkedList::tail = nullptr;
    
    void refresh(archive arch) {
        g_config_arch = {arch.vm};
        for (FuncLinkedList *s = FuncLinkedList::tail; s; s = s->next) {
            s->func();
        }
    }

    archive load(pcstr filename) {
        vfs::path fspath = vfs::content_path(filename);
        js_vm_load_file_and_exec(fspath);
        return {js_vm_state()};
    }
} // config

pcstr archive::r_string(pcstr name) {
    js_getproperty(vm, -1, name);
    const char *result = "";
    if (js_isundefined(vm, -1)) {
        ;
    } else if (js_isstring(vm, -1)) {
        result = js_tostring(vm, -1);
    } else if (js_isobject(vm, -1)) {
        js_getproperty(vm, -1, "group"); int group = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        js_getproperty(vm, -1, "id"); int id = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1); js_pop(vm, 1);
        result = (pcstr)lang_get_string(group, id);
    }
    js_pop(vm, 1);
    return result;
}

std::vector<std::string> archive::r_array_str(pcstr name) {
    js_getproperty(vm, -1, name);
    std::vector<std::string> result;
    if (js_isarray(vm, -1)) {
        int length = js_getlength(vm, -1);

        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);
            std::string v = js_tostring(vm, -1);
            result.push_back(v);
            js_pop(vm, 1);
        }
        js_pop(vm, 1);
    }
    return result;
}

int archive::r_int(pcstr name, int def) {
    js_getproperty(vm, -1, name);
    int result = js_isundefined(vm, -1) ? def : js_tointeger(vm, -1);
    js_pop(vm, 1);
    return result;
}

uint32_t archive::r_uint(pcstr name, uint32_t def) {
    js_getproperty(vm, -1, name);
    uint32_t result = js_isundefined(vm, -1) ? def : js_touint32(vm, -1);
    js_pop(vm, 1);
    return result;
}

e_image_id archive::r_image(pcstr name) { 
    return (e_image_id)r_int(name);
}

bool archive::r_bool(pcstr name, bool def) {
    js_getproperty(vm, -1, name);
    bool result = js_isundefined(vm, -1) ? def : js_toboolean(vm, -1);
    js_pop(vm, 1);
    return result;
}

vec2i archive::r_size2i(pcstr name, pcstr w, pcstr h) {
    return r_vec2i(name, w, h);
}

vec2i archive::r_vec2i(pcstr name, pcstr x, pcstr y) {
    vec2i result(0, 0);
    js_getproperty(vm, -1, name);
    if (js_isobject(vm, -1)) {
        if (js_isarray(vm, -1)) {
            int length = js_getlength(vm, -1);
            if (length > 0) {
                js_getindex(vm, -1, 0); result.x = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
                if (length > 1) {
                    js_getindex(vm, -1, 1); result.y = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
                }
            }
        } else {
            js_getproperty(vm, -1, x); result.x = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
            js_getproperty(vm, -1, y); result.y = !js_isundefined(vm, -1) ? js_tointeger(vm, -1) : 0; js_pop(vm, 1);
        }
    }
    js_pop(vm, 1);

    return result;
}
