#include "building/monument_caesareum.h"

#include "building/monuments.h"
#include "city/city.h"
#include "game/resource.h"
#include "graphics/elements/ui.h"
#include "grid/grid.h"
#include "grid/routing/routing_grids.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <cstring>
#include <iterator>
#include <string>

struct info_window_caesareum : building_info_window_t<info_window_caesareum> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override { return !!c.building_get()->dcast_caesareum(); }
};

info_window_caesareum caesareum_infow;

namespace {
    constexpr int k_lang_monuments = 178;
    constexpr int k_lang_amounts = 8;
    constexpr int k_text_caesareum_clearing = 122;
    // OG CAESAREUM_MARBLE_STOCK / MATERIAL_LOADS_PER_BLOCK and the granite share of the last stage.
    constexpr int k_marble_stock = 800;
    constexpr int k_loads_per_block = 400;
    constexpr int k_units_per_block = 100;
    constexpr int k_granite_blocks = 8;
    constexpr int k_granite_loads = 2;

    bool built(e_building_type type) {
        return g_city.buildings.count_total(type) > 0;
    }

    bool working(e_building_type type) {
        return g_city.buildings.count_active(type) > 0;
    }

    // OG monument_blocked.
    bool monument_blocked(building &b) {
        const tile2i road = b.road_access;
        if (road.valid() && map_grid_get(routing_land_citizen, road.grid_offset()) < 0) {
            return true;
        }
        return b.distance_from_entry == 0;
    }

    // OG monument_resource_available: true means the yards cannot cover the waiting masons.
    bool resource_short(e_resource r, int amount) {
        if (amount > g_city.resource.yards_stored(r)) {
            return true;
        }
        if (amount <= 0) {
            return false;
        }
        return g_city.resource.is_stockpiled(r) != 0;
    }

    textid material_shortage_text(e_resource r) {
        const bool stockpiled = g_city.resource.is_stockpiled(r) != 0;
        if (r == RESOURCE_GRANITE) {
            return {k_lang_monuments, (uint16_t)(stockpiled ? 102 : 25)};
        }
        return {k_lang_monuments, (uint16_t)(stockpiled ? 101 : 26)};
    }

    int guild_text(bool masons_wanted, bool carpenters_wanted, int masons, int carpenters) {
        if (masons_wanted) {
            if (!built(BUILDING_STONEMASONS_GUILD)) {
                return 14;
            }
            if (!working(BUILDING_STONEMASONS_GUILD) && masons == 0) {
                return 18;
            }
        }
        if (carpenters_wanted) {
            if (!built(BUILDING_CARPENTERS_GUILD)) {
                return 16;
            }
            if (!working(BUILDING_CARPENTERS_GUILD) && carpenters == 0) {
                return 20;
            }
        }
        return 0;
    }

    int work_camp_text(int laborers) {
        if (!built(BUILDING_WORK_CAMP)) {
            return 13;
        }
        if (!working(BUILDING_WORK_CAMP) && laborers == 0) {
            return 17;
        }
        return 0;
    }

    int stage_text(int stage) {
        if (stage < 0) {
            return k_text_caesareum_clearing;
        }
        if (stage == 0) {
            return k_text_caesareum_clearing + 1;
        }
        static const int stage_ends[] = {6, 9, 12, 14, 17};
        for (int i = 0; i < (int)std::size(stage_ends); i++) {
            if (stage < stage_ends[i]) {
                return k_text_caesareum_clearing + 2 + i;
            }
        }
        if (stage == 17) {
            return k_text_caesareum_clearing + 7;
        }
        return stage == 18 ? k_text_caesareum_clearing + 8 : k_text_caesareum_clearing + 9;
    }

    void replace_token(std::string &s, const char *token, const std::string &value) {
        const size_t at = s.find(token);
        if (at != std::string::npos) {
            s.replace(at, strlen(token), value);
        }
    }

    std::string amount_text(int amount, int resource_text) {
        return std::to_string(amount) + " " + ui::str(k_lang_monuments, resource_text);
    }

    std::string loads_text(int count) {
        return std::to_string(count) + " " + ui::str(k_lang_amounts, count != 1 ? 55 : 54);
    }

    xstring percent_line(int percent) {
        std::string s = ui::str(k_lang_monuments, 61);
        replace_token(s, "[monument_name]", ui::str(k_lang_monuments, 87));
        replace_token(s, "[percent_complete]", std::to_string(percent) + "%");
        return xstring(s.c_str());
    }

    xstring remainder_line(int amount, int loads, int resource_text) {
        std::string s = ui::str(k_lang_monuments, 68);
        replace_token(s, "[monument_name]", ui::str(k_lang_monuments, 87));
        replace_token(s, "[quantity_needed_remainder_main]", amount_text(amount, resource_text));
        replace_token(s, "[number_loads_remainder_main]", loads_text(loads));
        return xstring(s.c_str());
    }
} // namespace

// OG window_building_draw_caesareum.
void info_window_caesareum::init(object_info &c) {
    building_info_window::init(c);

    auto *part = c.building_get()->dcast_caesareum();
    auto *cae = part ? part->main_caesareum() : nullptr;
    if (!cae) {
        return;
    }

    caesareum_progress p;
    cae->get_progress(&p);
    const int stage = p.stage;
    const bool carpenter_spot = cae->has_free_spot(FIGURE_CARPENTER);
    const bool mason_spot = cae->has_free_spot(FIGURE_STONEMASON);
    const e_resource material = stage < building_caesareum::STAGE_GRANITE ? RESOURCE_MARBLE : RESOURCE_GRANITE;
    const bool short_of_material = stage < building_caesareum::STAGE_COMPLETE
                                   && resource_short(material, p.stonemasons_waiting * k_loads_per_block);

    textid text;
    if (monument_blocked(cae->base)) {
        text = {k_lang_monuments, 149};
    } else if (p.stonemasons_waiting != 0 && short_of_material && p.material != 0) {
        text = material_shortage_text(material);
    } else {
        int id = work_camp_text(p.laborers);
        if (id == 0) {
            id = guild_text(mason_spot, carpenter_spot, p.stonemasons, p.carpenters);
        }
        if (id == 0) {
            id = stage_text(stage);
        }
        text = {k_lang_monuments, (uint16_t)id};
    }
    ui["warning_text"] = text;

    ui["percent_text"] = "";
    ui["marble_text"] = "";
    ui["granite_text"] = "";
    if (p.percent >= 100) {
        return;
    }

    ui["percent_text"] = percent_line(p.percent);
    if (p.material > k_marble_stock) {
        ui["marble_text"] = remainder_line(p.material / k_units_per_block, p.material / k_loads_per_block, 95);
    }
    if (p.material != 0) {
        const bool more = p.material > k_marble_stock;
        const int amount = more ? k_granite_blocks : p.material / k_units_per_block;
        const int loads = more ? k_granite_loads : p.material / k_loads_per_block;
        ui["granite_text"] = remainder_line(amount, loads, 92);
    }
}
