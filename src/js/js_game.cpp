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

void js_config_load_building_sounds(archive arch) {
    arch.load_global_array("building_sounds", [] (archive arch) {
        const char *type = arch.read_string("type");
        const char *path = arch.read_string("sound");
        snd::set_building_info_sound(type, path);
    });
}

void js_config_load_mission_sounds(archive arch) {
    arch.load_global_array("mission_sounds", [] (archive arch) {
        const int mission = arch.read_integer("mission");
        const char *inter = arch.read_string("briefing");
        const char *won = arch.read_string("victory");
        snd::set_mission_config(mission, inter, won);
    });
}

void js_config_load_city_sounds(archive arch) {
    arch.load_global_array("city_sounds", [] (archive arch) {
        const int channel = arch.read_integer("c");
        const char *path = arch.read_string("p");
        sound_system_update_channel(channel, path);
    });
}

void js_config_load_images_info(archive arch) {
    arch.load_global_array("images", [] (archive arch) {
        int type = arch.read_integer("img");
        int pack = arch.read_integer("pack");
        int id = arch.read_integer("id");
        int offset = arch.read_integer("offset");
        set_image_desc((e_image_id)type, pack, id, offset);
    });
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_info, "log_info", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_log_warn, "log_warning", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
}

namespace config {
    FuncLinkedList *FuncLinkedList::tail = nullptr;
    
    void refresh(archive arch) {
        for (FuncLinkedList *s = FuncLinkedList::tail; s; s = s->next) {
            s->func(arch);
        }
    }
} // config