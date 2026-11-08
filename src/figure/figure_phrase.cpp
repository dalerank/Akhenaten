#include "figure_phrase.h"

#include "io/gamefiles/lang.h"
#include "content/content.h"
#include "core/bstring.h"
#include "core/log.h"
#include "figure/figure.h"
#include "game/game_events.h"
#include "js/js_events.h"
#include "js/js_struct.h"
#include "city/city_figures.h"
#include "platform/platform.h"
#include "sound/sound.h"

#include <filesystem>
#include "graphics/elements/lang_text.h"

ANK_SCRIPT_EVENT(event_synthesize_figure_phrase, id, path, text)

void ANK_PERMANENT_CALLBACK(event_synthesize_figure_phrase, ev) {
    logs::info("Run akhenaten-tts...");

    figure *f = figure_get(ev.id);
    if (!f || !f->is_valid()) {
        return;
    }

    xstring base_path = vfs::platform_file_manager_get_base_path();
    xstring tts_base_path;
    tts_base_path.printf("%s/akh-tts/", base_path.c_str());

    const pcstr tts_exe_name = platform.is_windows() ? "akhenaten-tts.exe" : "akhenaten-tts";
    xstring tts_path;
    tts_path.printf("%s%s", tts_base_path.c_str(), tts_exe_name);
    if (!std::filesystem::exists(tts_path.c_str())) {
        logs::info("%s not found", tts_path.c_str());
        return;
    }

    xstring original_path = std::filesystem::current_path().string().c_str();
    std::filesystem::current_path(tts_base_path.c_str());

    bstring32 prefix = f->params().name;
    prefix.replace_str("figure_", "");

    auto reaction = f->dcast()->get_sound_reaction(f->phrase_key);
    xstring phrase_text = ev.text;
    if (!phrase_text) {
        phrase_text = reaction.text;
    }
    if (!phrase_text) {
        phrase_text = lang_get_string(reaction.group, reaction.id);
    }
    if (!phrase_text) {
        phrase_text.printf("#%s", reaction.key.c_str());
    }

    xstring out_rel;
    out_rel.printf("../AUDIO/%s", ev.path.c_str());
    std::filesystem::create_directories(std::filesystem::path(out_rel.c_str()).parent_path());

    // Windows: bare "akhenaten-tts.exe". Unix: "./akhenaten-tts".
    const pcstr tts_cmd_exe = platform.is_windows() ? "akhenaten-tts.exe" : "./akhenaten-tts";
    xstring cmd;
    cmd.printf("%s -l en -p \"%s\" -f %s -o \"%s\"",
        tts_cmd_exe, lang_text_from_key(phrase_text.c_str()), prefix.c_str(), out_rel.c_str());

    if (std::system(cmd.c_str()) == 0) {
        logs::info("Create file: %s", ev.path.c_str());
        g_sound.speech_play_file(ev.path, 255);
    } else {
        logs::info("akhenaten-tts failed with cmd: %s", cmd.c_str());
    }

    std::filesystem::current_path(original_path.c_str());
}
