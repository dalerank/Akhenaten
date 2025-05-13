#include "core/runtime_item.h"

#include "js/js_game.h"
#include <mutex>

using runtime_items = std::vector<config::runtime*>;
runtime_items* g_runtime_items = nullptr;

runtime_items& runtime_registry() {
    if (!g_runtime_items) {
        static std::mutex registry_locker;

        std::scoped_lock _(registry_locker);
        if (!g_runtime_items) {
            g_runtime_items = new std::vector<config::runtime*>;
        }
    }

    return *g_runtime_items;
}

config::runtime::runtime(pcstr s) : _section(s) {
    runtime_registry().push_back(this);
}

ANK_REGISTER_CONFIG_ITERATOR(config_load_runtime_items);
void config_load_runtime_items() {
    for (auto& item : runtime_registry()) {
        item->reset();
        g_config_arch.r_section(item->_section, [item] (archive arch) {
            item->load(arch);
        });
        item->init();
    }
}