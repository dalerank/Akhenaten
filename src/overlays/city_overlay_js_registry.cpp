#include "city_overlay.h"

#include "core/log.h"
#include "js/js_game.h"
#include "js/js_struct.h"

#include <memory>

hvector<std::unique_ptr<city_overlay>, 16> js_city_overlays;

void clear_es_city_overlay() {
    logs::info("JS City Overlay Registry: Clearing %d registered overlays", (int)js_city_overlays.size());
    for (auto &o : js_city_overlays) {
        if (o && o->id > OVERLAY_NONE && o->id < OVERLAY_SIZE) {
            city_overlay::overlays()[o->id] = nullptr;
        }
    }
    js_city_overlays.clear();
}

void register_es_city_overlay(pcstr name) {
    e_overlay id = OVERLAY_NONE;
    g_config_arch.r_section(name, [&] (archive arch) {
        id = arch.r_type<e_overlay>("id");
    });

    if (id <= OVERLAY_NONE || id >= OVERLAY_SIZE) {
        logs::info("JS City Overlay Registry: Unknown overlay id in '%s', skipping", name);
        return;
    }

    if (city_overlay::get(id)) {
        logs::info("JS City Overlay Registry: Overlay slot %d already registered, skipping '%s'", (int)id, name);
        return;
    }

    logs::info("JS City Overlay Registry: Registering overlay '%s' (id=%d)", name, (int)id);

    auto overlay = std::make_unique<city_overlay>(id);

    g_config_arch.r_section(name, [&] (archive arch) {
        arch.r(*overlay);
        const xstring title_cfg = arch.r_string("title");
        if (!title_cfg.empty()) {
            overlay->title_text = title_cfg;
        }
    });

    overlay->es_name = name;
    js_city_overlays.push_back(std::move(overlay));
}

ANK_REGISTER_ES_ITERATOR(city_overlay, register_es_city_overlay, clear_es_city_overlay);
