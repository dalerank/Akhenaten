#ifndef BUILDING_STORAGE_H
#define BUILDING_STORAGE_H

#include "building/building.h"
#include "core/buffer.h"
#include "game/resource.h"

/**
 * @file
 * Building storage functions
 */

enum {
    BUILDING_STORAGE_DATA
};

/**
 * Storage state
 */
enum {
    STORAGE_STATE_PHARAOH_ACCEPT = 0,
    STORAGE_STATE_PHARAOH_REFUSE = 1,
    STORAGE_STATE_PHARAOH_GET = 2,
    STORAGE_STATE_PHARAOH_EMPTY = 3,
};

enum {
    BAZAAR_ORDER_STATE_DONT_BUY = 0,
    BAZAAR_ORDER_STATE_BUY = 1,
};

enum {
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

enum {
    BUILDING_STORAGE_PERMISSION_MARKET = 0,
    BUILDING_STORAGE_PERMISSION_TRADERS = 1,
    BUILDING_STORAGE_PERMISSION_DOCK = 2,
};


/**
 * Building storage struct
 */
typedef struct {
    int empty_all;
    int resource_state[36];
    int resource_max_accept[36];
    int resource_max_get[36];
    int permissions;
} building_storage;

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
const building_storage *building_storage_get(int storage_id);

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

/**
 * Save data
 * @param buf Buffer to read from
 */
void building_storage_save_state(buffer *buf);

/**
 * Load data
 * @param buf Buffer to read from
 */
void building_storage_load_state(buffer *buf);


void building_storage_set_permission(int p, building *b);
int building_storage_get_permission(int p, building *b);


#endif // BUILDING_STORAGE_H
