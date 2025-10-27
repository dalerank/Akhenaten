#include "js_game.h"

#include "content/vfs.h"
#include "core/log.h"

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
#include "game/game.h"

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

//void js_game_set_image(js_State *J) {
//    if (js_isobject(J, 1)) {
//        archive arch{js_vm_state()};
//        int img = arch.r_int("img");
//        int pack = arch.r_int("pack");
//        int id = arch.r_int("id");
//        int offset = arch.r_int("offset");
//        set_image_desc(img, pack, id, offset);
//        js_pop(J, 1);
//    }
//
//    js_pushundefined(J);
//}

void js_game_load_text(js_State *J) {
    const char *path = js_tostring(J, 1);
    char *text = 0;

    vfs::reader ftext = vfs::file_open(path, "rt");
    if (!ftext) {
        return;
    }
    
    js_pushstring(J, ftext->begin());
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
}

void js_unref_function(xstring onclick_ref) {
    js_State *J = js_vm_state();
    assert(J);
    if (!onclick_ref.empty()) {
        js_unref(J, onclick_ref .c_str());
    }
}

void js_call_function(xstring js_ref) {
    if (js_ref.empty()) {
        return;
    }

    js_State *J = js_vm_state();
    assert(J);

    // Get the function from registry using the reference
    js_getregistry(J, js_ref.c_str());
    if (js_iscallable(J, -1)) {
        js_pushnull(J);  // 'this' context
        int result = js_pcall(J, 0);
        if (result != 0) {
            logs::error("JS onclick callback error: %s", js_tostring(J, -1));
            js_pop(J, 1);
        }
    } else {
        js_pop(J, 1);
    }
}

void config::refresh(archive arch) {
    g_config_arch = {arch.state};
    animation_t::global_hashtime = game.frame;
    for (ArchiveIterator *s = ArchiveIterator::tail; s; s = s->next) {
        s->func();
    }
}

archive config::load(pcstr filename) {
    vfs::path fspath = vfs::content_path(filename);
    js_vm_load_file_and_exec(fspath);
    return {js_vm_state()};
}
