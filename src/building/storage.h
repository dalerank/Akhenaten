#pragma once

#include "building/building.h"
#include "core/buffer.h"
#include "game/resource.h"

enum e_building_storage { BUILDING_STORAGE_DATA };

/**
 * Storage state
 */
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

/**
 * Building storage struct
 */
struct building_storage {
    int empty_all;
    int resource_state[RESOURCES_MAX];
    int resource_max_accept[RESOURCES_MAX];
    int resource_max_get[RESOURCES_MAX];
    int permissions;
} ;

/**
 * Clear and reset all building storages
 */
void building_storage_clear_all(void);

/**
 * Creates a building storage
 * @return storage id, 0 when creation failed
 */
int building_storage_create(int building_type);

/**
 * Restores a building storage after undoing destruction.
 * @param storage_id Storage id
 * @return storage id, 0 when storage already used.
 */
int building_storage_restore(int storage_id);

/**
 * Deletes a building storage
 * @param storage_id Storage id
 */
void building_storage_delete(int storage_id);

/**
 * Gets a read-only building storage
 * @param storage_id Storage id
 * @return Read-only storage
 */
const building_storage* building_storage_get(int storage_id);

void backup_storage_settings(int storage_id);
void restore_storage_settings(bool do_forget_changes);
void storage_settings_backup_check();
void storage_settings_backup_reset();

/**
 * Cycles the resource state for the storage
 * @param storage_id Storage id
 * @param resource_id Resource id
 */
void building_storage_cycle_resource_state(int storage_id, int resource_id, bool backwards);

void building_storage_increase_decrease_resource_state(int storage_id, int resource_id, bool increase);
/**
 * Sets all goods to 'not accepting'
 * @param storage_id Storage id
 */
void building_storage_accept_none(int storage_id);

/**
 * Toggles the empty all flag for the storage
 * @param storage_id Storage id
 */
void building_storage_toggle_empty_all(int storage_id);

/**
 * Resets building id's for all storages
 */
void building_storage_reset_building_ids(void);

void building_storage_set_permission(int p, building* b);
bool building_storage_get_permission(int p, building* b);
