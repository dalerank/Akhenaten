#pragma once

#include "building/building_type.h"
#include "city/constants.h"
#include "city/city_religion.h"
#include "core/bstring.h"
#include "graphics/animation.h"

enum e_resource : uint8_t;

struct event_building_menu_update { xstring stage; };

struct building_menu_item {
    int type = -1;
    bool enabled = false;
};

struct building_menu_group {
    enum {
        ITEM_MAX = 30,
    };
    using items_t = svector<building_menu_item, ITEM_MAX>;

    building_menu_item &operator[](int type) {
        auto it = std::find_if(items.begin(), items.end(), [type] (auto &item) { return item.type == type; });
        return (it != items.end()) ? *it : dummy();
    }

    void set_all(bool enabled) {
        for (auto &it : items) {
            it.enabled = enabled;
        }
    }

    inline bool enabled(int type) { return (*this)[type].enabled; }
    static building_menu_item &dummy();

    items_t::iterator begin() { return items.begin(); }
    items_t::iterator end() { return items.end(); }

    void clear() {
        items.clear();
    }

    animation_t anim;

    int type;
    items_t items;
};

struct building_menu_ctrl_t {
    svector<building_menu_group, 30> groups;
    building_menu_group &group(int type) {
        static building_menu_group building_menu_group_dummy;
        auto it = std::find_if(groups.begin(), groups.end(), [type] (auto &it) { return it.type == type; });
        return (it != groups.end()) ? *it : building_menu_group_dummy;
    }

    void set(int type, bool enabled) {
        for (auto &group : groups) {
            auto &item = group[type];
            if (item.type == type) {
                item.enabled = enabled;
            }
        }
    }

    building_menu_item &get(int type) {
        for (auto &group : groups) {
            auto &item = group[type];
            if (item.type == type) {
                return item;
            }
        }

        assert(false && "should be exist type");
        return building_menu_group::dummy();
    }

    bool is_enabled(int type) {
        const building_menu_item &item = get(type);
        return (item.type == type) ? item.enabled : false;
    }

    e_building_type type(int submenu, int index) {
        auto &gr = group(submenu);
        return (e_building_type)(index < gr.items.size() ? gr.items[index].type : 0);
    }

    void set_all(bool enabled) {
        for (auto &group : groups) {
            group.set_all(enabled);
        }
    }

    void clear() {
        for (auto &gr : groups) {
            gr.clear();
        }
    }

    bool is_submenu(int submenu) const;
    void toggle_building(int type, bool enabled = true);
    const animation_t &anim(int submenu);

    void update(const xstring stage_name);
    int count_items(int submenu);
    int next_index(int submenu, int current_index);
    bool has_changed();

    void enable_if_allowed(int type);
    int disable_raw_if_unavailable(int type, e_resource resource);

    void update_if(bool expr, const xstring stage) {
        if (expr) {
            update(stage);
        }
    }

    void invalidate() { changed = true; }
    void update_temple_complexes();
    void update_gods_available(e_god god, bool available);
    void disable_resources();
    void setup_mission();
    void enable_correct_palace_tier();
    void enable_common_beautifications();
    void enable_common_municipal(int level);
    void enable_common_health();
    void enable_entertainment(int level);

    static void register_callbacks();

    bool changed = true;
};

extern building_menu_ctrl_t g_building_menu_ctrl;

void building_menu_update_monuments();