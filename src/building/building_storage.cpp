#include "building_storage.h"
#include "core/xvalue.h"

#include "building/building.h"
#include "building/rotation.h"
#include "core/object_property.h"
#include "city/city.h"

#include "io/io_buffer.h"

#include <cstring>

e_storage_state_tokens_t ANK_CONFIG_ENUM(storage_state_tokens);

static building_storages_t& storages_data() {
    return xvalue<building_storages_t>::ref();
}

void building_storage_set(int storage_id, int building_id, bool in_use, const storage_t &storage) {
    if (storage_id < 0 || storage_id >= MAX_STORAGES) {
        return;
    }
    storages_data().slots[storage_id].building_id = building_id;
    storages_data().slots[storage_id].in_use = in_use;
    storages_data().slots[storage_id].storage = storage;
}

static void building_storage_clear_empty_all_backup(int storage_id) {
    if (storage_id <= 0 || storage_id >= MAX_STORAGES) {
        return;
    }
    memset(&storages_data().empty_all_backups[storage_id], 0, sizeof(storages_data().empty_all_backups[storage_id]));
}

void building_storage_clear_all(void) {
    memset(storages_data().slots, 0, sizeof(storages_data().slots));
    memset(storages_data().empty_all_backups, 0, sizeof(storages_data().empty_all_backups));
}

void building_storage_reset_building_ids(void) {
    for (int i = 1; i < MAX_STORAGES; i++) {
        storages_data().slots[i].building_id = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_UNUSED)
            continue;

        if (b->type == BUILDING_GRANARY || b->type == BUILDING_STORAGE_YARD || b->type == BUILDING_FOOD_MILL) {
            if (b->storage_id) {
                if (storages_data().slots[b->storage_id].building_id) {
                    // storage is already connected to a building: corrupt, create new
                    b->storage_id = building_storage_create(b->type, i);
                } else {
                    storages_data().slots[b->storage_id].building_id = i;
                }
            }
        }
    }
}

int building_storage_create(int building_type, int building_id) {
    for (int i = 1; i < MAX_STORAGES; i++) {
        if (!storages_data().slots[i].in_use) {
            memset(&storages_data().slots[i], 0, sizeof(storages_data().slots[i]));
            memset(&storages_data().empty_all_backups[i], 0, sizeof(storages_data().empty_all_backups[i]));
            storages_data().slots[i].in_use = 1;
            storages_data().slots[i].building_id = building_id;

            // default settings for Pharaoh
            for (int r = 0; r < 36; r++) {
                storages_data().slots[i].storage.resource_state[r] = STORAGE_STATE_REFUSE;
                storages_data().slots[i].storage.resource_max_accept[r] = 3200;
                storages_data().slots[i].storage.resource_max_get[r] = 3200;
            }
            const resource_list &resources = g_city.resource.available();
            for (const auto &r: resources) {
                e_resource resource = r.type;
                switch (building_type) {
                case BUILDING_STORAGE_YARD:
                case BUILDING_STORAGE_ROOM:
                    if (resource < 9)
                        storages_data().slots[i].storage.resource_state[resource] = STORAGE_STATE_REFUSE;
                    else
                        storages_data().slots[i].storage.resource_state[resource] = STORAGE_STATE_ACCEPT;
                    break;

                case BUILDING_GRANARY:
                case BUILDING_FOOD_MILL:
                    if (resource < 9)
                        storages_data().slots[i].storage.resource_state[resource] = STORAGE_STATE_ACCEPT;
                    else
                        storages_data().slots[i].storage.resource_state[resource] = STORAGE_STATE_REFUSE;
                    break;
                }
            }
            return i;
        }
    }
    return 0;
}

int building_storage_restore(int storage_id) {
    if (storages_data().slots[storage_id].in_use) {
        return 0;
    }
    storages_data().slots[storage_id].in_use = 1;
    return storage_id;
}

void building_storage_delete(int storage_id) {
    storages_data().slots[storage_id].in_use = 0;
}

const storage_t* building_storage_get(int storage_id) {
    return &storages_data().slots[storage_id].storage;
}

void building_storage_toggle_empty_all(int storage_id) {
    if (storage_id <= 0 || storage_id >= MAX_STORAGES) {
        return;
    }

    auto& slot = storages_data().slots[storage_id];
    auto &storage = slot.storage;

    auto& backup = storages_data().empty_all_backups[storage_id];

    if (!storage.empty_all) {
        // START: snapshot current orders, then empty everything.
        for (int r = 0; r < RESOURCES_MAX; r++) {
            backup.resource_state[r] = (uint8_t)storage.resource_state[r];
        }
        backup.has_flag = 1;
        storage.empty_all = 1;
        for (auto &resource_state : storage.resource_state) {
            resource_state = STORAGE_STATE_EMPTY;
        }
        return;
    }

    // STOP: restore snapshot (or Accept-all fallback for old mid-empty saves).
    storage.empty_all = 0;
    if (backup.has_flag) {
        for (int r = 0; r < RESOURCES_MAX; r++) {
            storage.resource_state[r] = backup.resource_state[r];
        }
        building_storage_clear_empty_all_backup(storage_id);
    } else {
        for (auto &resource_state : storage.resource_state) {
            resource_state = STORAGE_STATE_ACCEPT;
        }
    }
}

void building_storage_accept_none(int storage_id) {
    if (storage_id <= 0 || storage_id >= MAX_STORAGES) {
        return;
    }

    auto& slot = storages_data().slots[storage_id];
    if (slot.storage.empty_all) {
        slot.storage.empty_all = 0;
        building_storage_clear_empty_all_backup(storage_id);
    }

    for (auto &state : slot.storage.resource_state) {
        state = STORAGE_STATE_REFUSE;
    }
}

void building_storage_cycle_resource_state(int storage_id, int resource_id, bool backwards) {
    if (storage_id <= 0 || storage_id >= MAX_STORAGES) {
        return;
    }

    auto& slot = storages_data().slots[storage_id];
    if (slot.storage.empty_all) {
        slot.storage.empty_all = 0;
        building_storage_clear_empty_all_backup(storage_id);
    }

    int state = slot.storage.resource_state[resource_id];
    if (!backwards) {
        if (state == STORAGE_STATE_ACCEPT)
            state = STORAGE_STATE_GET;
        else if (state == STORAGE_STATE_GET)
            state = STORAGE_STATE_EMPTY;
        else if (state == STORAGE_STATE_EMPTY)
            state = STORAGE_STATE_REFUSE;
        else
            state = STORAGE_STATE_ACCEPT;
    } else {
        if (state == STORAGE_STATE_ACCEPT)
            state = STORAGE_STATE_REFUSE;
        else if (state == STORAGE_STATE_REFUSE)
            state = STORAGE_STATE_EMPTY;
        else if (state == STORAGE_STATE_EMPTY)
            state = STORAGE_STATE_GET;
        else
            state = STORAGE_STATE_ACCEPT;
    }

    slot.storage.resource_state[resource_id] = state;
}

void building_storage::set_permission(int p) {
    auto& data = storages_data().slots;

    const storage_t* s = storage();
    int permission_bit = 1 << p;
    int perms = s->permissions;
    perms ^= permission_bit;
    storages_data().slots[base.storage_id].storage.permissions = perms;
}

bool building_storage::get_permission(int p) {
    const storage_t* s = storage();
    int permission_bit = 1 << p;
    return !(s->permissions & permission_bit);
}

void building_storage_increase_decrease_resource_state(int storage_id, int resource_id, bool increase) {
    int state = storages_data().slots[storage_id].storage.resource_state[resource_id];
    if (state == STORAGE_STATE_ACCEPT) {
        int max_accept = storages_data().slots[storage_id].storage.resource_max_accept[resource_id];
        if (increase) {
            if (max_accept == 2400)
                max_accept = 3200;
            else if (max_accept == 1600)
                max_accept = 2400;
            else if (max_accept == 800)
                max_accept = 1600;
        } else {
            if (max_accept == 3200)
                max_accept = 2400;
            else if (max_accept == 2400)
                max_accept = 1600;
            else if (max_accept == 1600)
                max_accept = 800;
        }
        storages_data().slots[storage_id].storage.resource_max_accept[resource_id] = max_accept;
    } else if (state == STORAGE_STATE_GET) {
        int max_get = storages_data().slots[storage_id].storage.resource_max_get[resource_id];
        if (increase) {
            if (max_get == 2400)
                max_get = 3200;
            else if (max_get == 1600)
                max_get = 2400;
            else if (max_get == 800)
                max_get = 1600;
        } else {
            if (max_get == 3200)
                max_get = 2400;
            else if (max_get == 2400)
                max_get = 1600;
            else if (max_get == 1600)
                max_get = 800;
        }

        storages_data().slots[storage_id].storage.resource_max_get[resource_id] = max_get;
    }
}

void building_storage_load_state(buffer* buf) {
}

const storage_t *building_storage::storage() const {
    return building_storage_get(base.storage_id);
}

int building_storage::storage_id() const {
    return base.storage_id;
}

bool building_storage::is_empty_all() const {
    return storage()->empty_all;
}

bool building_storage::is_gettable(e_resource resource) {
    const storage_t *s = storage();
    return (s->resource_state[resource] == STORAGE_STATE_GET);
}

bool building_storage::is_emptying(e_resource resource) {
    const storage_t *s = storage();
    return (s->resource_state[resource] == STORAGE_STATE_EMPTY);
}

int building_storage::accepting_amount(e_resource resource) {
    const storage_t* s = storage();

    switch (s->resource_state[resource]) {
    case STORAGE_STATE_ACCEPT: return s->resource_max_accept[resource];
    case STORAGE_STATE_GET: return s->resource_max_get[resource];
    default: return 0;
    }
}

int building_storage::remove_resources(resource_list resources, int amount) {
    for (const auto &r: resources) {
        amount = remove_resource(r.type, amount);
    }

    return amount;
}

struct sproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(const building_storage &, const xstring &)> handler;
};

bvariant building_storage::get_property(const xstring &domain, const xstring &name) const {
    static const sproperty sproperties[] = {
        { tags().building, tags().total_stored, [] (const building_storage &b, const xstring &) { return bvariant(b.total_stored()); }},
        { tags().building, tags().free_space, [] (const building_storage &b, const xstring &) { return bvariant(b.freespace()); }},
    };

    for (const auto &prop : sproperties) {
        if (prop.domain == domain && prop.name == name) {
            return prop.handler(*this, name);
        }
    }

    return building_impl::get_property(domain, name);
}