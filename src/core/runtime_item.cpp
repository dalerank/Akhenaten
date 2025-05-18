#include "core/runtime_item.h"

#include "js/js_game.h"
#include <mutex>

using runtime_items = std::vector<config::static_params *>;
runtime_items* g_runtime_items = nullptr;

runtime_items& runtime_registry() {
    if (!g_runtime_items) {
        static std::mutex registry_locker;

        std::scoped_lock _(registry_locker);
        if (!g_runtime_items) {
            g_runtime_items = new std::vector<config::static_params*>;
        }
    }

    return *g_runtime_items;
}

config::static_params::static_params() {
    runtime_registry().push_back(this);
}

void config::static_params::archive_load() {
    pcstr s = this->archive_section();
    g_config_arch.r_section(s, [this] (archive arch) {
        archive_load(arch);
    });
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_runtime_items) {
    for (auto& item : runtime_registry()) {
        item->archive_unload();
        item->archive_load();
        item->archive_init();
    }
}