#include "sound_walker.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<std::string, bstring64> g_walker_reaction;

ANK_REGISTER_CONFIG_ITERATOR(config_load_walker_sounds);
void config_load_walker_sounds(archive arch) {
    arch.load_global_array("walker_sounds", [] (archive arch) {
        const char *type = arch.read_string("type");
        const char *path = arch.read_string("sound");
        g_walker_reaction[type] = type;
    });
}

bstring64 snd::get_walker_reaction(pcstr reaction) {
    auto it = g_walker_reaction.find(reaction);

    return (it == g_walker_reaction.end()) ? bstring64() : it->second;
}