#pragma once

#include "building/building.h"
#include "game/resource.h"

constexpr int UNITS_PER_LOAD = 100;

enum e_building_storage {
    BUILDING_STORAGE_DATA
};

enum e_storage_state {
    STORAGE_STATE_PHARAOH_ACCEPT = 0,
    STORAGE_STATE_PHARAOH_REFUSE = 1,
    STORAGE_STATE_PHARAOH_GET = 2,
    STORAGE_STATE_PHARAOH_EMPTY = 3,
};

enum e_bazaar_order {
    BAZAAR_ORDER_STATE_DONT_BUY = 0,
    BAZAAR_ORDER_STATE_BUY = 1,
};

enum e_dock_order {
    DOCK_ORDER_STATE_DONT_TRADE = 0,
    DOCK_ORDER_STATE_TRADE = 1,
};

enum e_old_storage_state {
    OLD_STORAGE_STATE_ACCEPTING = 0,
    OLD_STORAGE_STATE_NOT_ACCEPTING = 1,
    OLD_STORAGE_STATE_GETTING = 2,
    OLD_STORAGE_STATE_ACCEPTING_HALF = 3,
    OLD_STORAGE_STATE_ACCEPTING_QUARTER = 4,
    OLD_STORAGE_STATE_GETTING_HALF = 5,
    OLD_STORAGE_STATE_GETTING_QUARTER = 6,
    OLD_STORAGE_STATE_GETTING_3QUARTERS = 7,
    OLD_STORAGE_STATE_ACCEPTING_3QUARTERS = 8,
};

enum e_building_storage_permission {
    BUILDING_STORAGE_PERMISSION_MARKET = 0,
    BUILDING_STORAGE_PERMISSION_TRADERS = 1,
    BUILDING_STORAGE_PERMISSION_DOCK = 2,
};

struct storage_t {
    int empty_all;
    int resource_state[RESOURCES_MAX];
    int resource_max_accept[RESOURCES_MAX];
    int resource_max_get[RESOURCES_MAX];
    int permissions;
} ;

void building_storage_clear_all();
int building_storage_create(int building_type);

int building_storage_restore(int storage_id);
void building_storage_delete(int storage_id);
bool building_storage_has_unsaved_changes();

const storage_t* building_storage_get(int storage_id);

void backup_storage_settings(int storage_id);
void storage_settings_backup_check();
void storage_settings_backup_reset();

void building_storage_cycle_resource_state(int storage_id, int resource_id, bool backwards);

void building_storage_increase_decrease_resource_state(int storage_id, int resource_id, bool increase);
void building_storage_reset_building_ids(void);

void building_storage_accept_none(int storage_id);
void building_storage_toggle_empty_all(int storage_id);

class building_storage : public building_impl {
public:
    building_storage(building &b) : building_impl(b) {}
    virtual building_storage *dcast_storage() override { return this; }

    const storage_t *storage() const;
    int storage_id() const;
    bool is_empty_all() const;
    bool is_gettable(e_resource resource);
    bool is_emptying(e_resource resource);
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;

    void set_permission(int p);
    bool get_permission(int p);
    int accepting_amount(e_resource resource);

    virtual int remove_resources(resource_list resources, int amount);

    virtual int amount(e_resource resource) const = 0;
    virtual bool is_getting(e_resource resource) = 0;
    virtual int remove_resource(e_resource resource, int amount) = 0;
    virtual int freespace() const = 0;
    virtual int total_stored() const = 0;
    virtual int add_resource(e_resource resource, bool is_produced, int amount, bool force) = 0;

};