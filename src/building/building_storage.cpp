#include "building_storage.h"

#include "building/building.h"
#include "building/rotation.h"
#include "core/object_property.h"
#include "city/city_resource.h"

#include "io/io_buffer.h"
#include "window/window_city.h"
#include "window/popup_dialog.h"

#include <string.h>

constexpr int MAX_STORAGES = 200;

struct city_storage_t {
    int in_use;
    int building_id;
    storage_t storage;
};

city_storage_t g_storages[MAX_STORAGES];

void building_storage_clear_all(void) {
    memset(g_storages, 0, MAX_STORAGES * sizeof(storage_t));
}

void building_storage_reset_building_ids(void) {
    for (int i = 1; i < MAX_STORAGES; i++) {
        g_storages[i].building_id = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_UNUSED)
            continue;

        if (b->type == BUILDING_GRANARY || b->type == BUILDING_STORAGE_YARD) {
            if (b->storage_id) {
                if (g_storages[b->storage_id].building_id) {
                    // storage is already connected to a building: corrupt, create new
                    b->storage_id = building_storage_create(b->type);
                } else {
                    g_storages[b->storage_id].building_id = i;
                }
            }
        }
    }
}

int building_storage_create(int building_type) {
    for (int i = 1; i < MAX_STORAGES; i++) {
        if (!g_storages[i].in_use) {
            memset(&g_storages[i], 0, sizeof(storage_t));
            g_storages[i].in_use = 1;

            // default settings for Pharaoh
            for (int r = 0; r < 36; r++) {
                g_storages[i].storage.resource_state[r] = STORAGE_STATE_PHARAOH_REFUSE;
                g_storages[i].storage.resource_max_accept[r] = 3200;
                g_storages[i].storage.resource_max_get[r] = 3200;
            }
            const resource_list &resources = city_resource_get_available();
            for (const auto &r: resources) {
                e_resource resource = r.type;
                switch (building_type) {
                case BUILDING_STORAGE_YARD:
                case BUILDING_STORAGE_ROOM:
                    if (resource < 9)
                        g_storages[i].storage.resource_state[resource] = STORAGE_STATE_PHARAOH_REFUSE;
                    else
                        g_storages[i].storage.resource_state[resource] = STORAGE_STATE_PHARAOH_ACCEPT;
                    break;

                case BUILDING_GRANARY:
                    if (resource < 9)
                        g_storages[i].storage.resource_state[resource] = STORAGE_STATE_PHARAOH_ACCEPT;
                    else
                        g_storages[i].storage.resource_state[resource] = STORAGE_STATE_PHARAOH_REFUSE;
                    break;
                }
            }
            return i;
        }
    }
    return 0;
}

int building_storage_restore(int storage_id) {
    if (g_storages[storage_id].in_use) {
        return 0;
    }
    g_storages[storage_id].in_use = 1;
    return storage_id;
}

void building_storage_delete(int storage_id) {
    g_storages[storage_id].in_use = 0;
}

storage_t backup_settings;
static int backup_storage_id = -1;

void backup_storage_settings(int storage_id) {
    if (backup_storage_id != -1)
        return;

    backup_storage_id = storage_id;
    backup_settings = g_storages[storage_id].storage;
}

bool building_storage_has_unsaved_changes() {
    return memcmp(&backup_settings, &g_storages[backup_storage_id].storage, sizeof(backup_settings)) != 0;
 }

void storage_settings_backup_check() {
    if (building_storage_has_unsaved_changes()) {
        window_popup_dialog_show_confirmation("#exit_without_saving", [] (bool do_forget_changes) {
            if (!do_forget_changes) {
                return;
            }

            if (backup_storage_id == -1) {
                return;
            }

            g_storages[backup_storage_id].storage = backup_settings;
            storage_settings_backup_reset();
            window_city_show();
        });
    } else {
        storage_settings_backup_reset();
        window_city_show();
    }
}

void storage_settings_backup_reset() {
    backup_storage_id = -1;
}

const storage_t* building_storage_get(int storage_id) {
    return &g_storages[storage_id].storage;
}

void building_storage_toggle_empty_all(int storage_id) {
    g_storages[storage_id].storage.empty_all = 1 - g_storages[storage_id].storage.empty_all;

    auto &storage = g_storages[storage_id].storage;
    for (auto &state : storage.resource_state) {
        state = STORAGE_STATE_PHARAOH_EMPTY;
    }
}

void building_storage_cycle_resource_state(int storage_id, int resource_id, bool backwards) {
    int state = g_storages[storage_id].storage.resource_state[resource_id];
    if (!backwards) {
        if (state == STORAGE_STATE_PHARAOH_ACCEPT)
            state = STORAGE_STATE_PHARAOH_GET;
        else if (state == STORAGE_STATE_PHARAOH_GET)
            state = STORAGE_STATE_PHARAOH_EMPTY;
        else if (state == STORAGE_STATE_PHARAOH_EMPTY)
            state = STORAGE_STATE_PHARAOH_REFUSE;
        else
            state = STORAGE_STATE_PHARAOH_ACCEPT;
    } else {
        if (state == STORAGE_STATE_PHARAOH_ACCEPT)
            state = STORAGE_STATE_PHARAOH_REFUSE;
        else if (state == STORAGE_STATE_PHARAOH_REFUSE)
            state = STORAGE_STATE_PHARAOH_EMPTY;
        else if (state == STORAGE_STATE_PHARAOH_EMPTY)
            state = STORAGE_STATE_PHARAOH_GET;
        else
            state = STORAGE_STATE_PHARAOH_ACCEPT;
    }

    g_storages[storage_id].storage.resource_state[resource_id] = state;
}

void building_storage::set_permission(int p) {
    auto& data = g_storages;

    const storage_t* s = storage();
    int permission_bit = 1 << p;
    int perms = s->permissions;
    perms ^= permission_bit;
    g_storages[base.storage_id].storage.permissions = perms;
}

bool building_storage::get_permission(int p) {
    const storage_t* s = storage();
    int permission_bit = 1 << p;
    return !(s->permissions & permission_bit);
}

void building_storage_increase_decrease_resource_state(int storage_id, int resource_id, bool increase) {
    int state = g_storages[storage_id].storage.resource_state[resource_id];
    if (state == STORAGE_STATE_PHARAOH_ACCEPT) {
        int max_accept = g_storages[storage_id].storage.resource_max_accept[resource_id];
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
        g_storages[storage_id].storage.resource_max_accept[resource_id] = max_accept;
    } else if (state == STORAGE_STATE_PHARAOH_GET) {
        int max_get = g_storages[storage_id].storage.resource_max_get[resource_id];
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

        g_storages[storage_id].storage.resource_max_get[resource_id] = max_get;
    }
}

void building_storage_accept_none(int storage_id) {
    auto &storage = g_storages[storage_id].storage;
    for (auto &state: storage.resource_state) {
        state = STORAGE_STATE_PHARAOH_REFUSE;
    }
}

void building_storage_load_state(buffer* buf) {
}

io_buffer* iob_building_storages = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < MAX_STORAGES; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &g_storages[i].storage.permissions); // Originally unused
        iob->bind(BIND_SIGNATURE_INT32, &g_storages[i].building_id);
        iob->bind(BIND_SIGNATURE_UINT8, &g_storages[i].in_use);
        iob->bind(BIND_SIGNATURE_UINT8, &g_storages[i].storage.empty_all);
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &g_storages[i].storage.resource_state[r]);
        }

        iob->bind____skip(6); // unused resource states
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT16, &g_storages[i].storage.resource_max_accept[r]);
        }

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT16, &g_storages[i].storage.resource_max_get[r]);
        }
        //        iob->bind____skip(144); // ?????
    }
});

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
    return (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET);
}

bool building_storage::is_emptying(e_resource resource) {
    const storage_t *s = storage();
    return (s->resource_state[resource] == STORAGE_STATE_PHARAOH_EMPTY);
}

int building_storage::accepting_amount(e_resource resource) {
    const storage_t* s = storage();

    switch (s->resource_state[resource]) {
    case STORAGE_STATE_PHARAOH_ACCEPT: return s->resource_max_accept[resource];
    case STORAGE_STATE_PHARAOH_GET: return s->resource_max_get[resource];
    default: return 0;
    }
}

struct sproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(const building_storage &, const xstring &)> handler;
};

const sproperty sproperties[] = {
    { tags().building, tags().total_stored, [] (const building_storage &b, const xstring &) { return bvariant(b.total_stored()); }},
};

bvariant building_storage::get_property(const xstring &domain, const xstring &name) const {
    for (const auto &prop : sproperties) {
        if (prop.domain == domain && prop.name == name) {
            return prop.handler(*this, name);
        }
    }

    return building_impl::get_property(domain, name);
}