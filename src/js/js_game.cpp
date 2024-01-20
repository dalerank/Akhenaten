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
        int img = arch.read_integer("img");
        int pack = arch.read_integer("pack");
        int id = arch.read_integer("id");
        int offset = arch.read_integer("offset");
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
            s->func(arch);
        }
    }

    archive load(pcstr filename) {
        vfs::path fspath = vfs::content_path(filename);
        js_vm_load_file_and_exec(fspath);
        return {js_vm_state()};
    }
} // config