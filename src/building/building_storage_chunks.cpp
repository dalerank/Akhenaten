#include "building/building_storage_chunks.h"

#include "building/building_storage.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

#include <cstring>

void building_storages_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& slots = xvalue<building_storages_t>::ref().slots;
    for (int i = 0; i < MAX_STORAGES; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &slots[i].storage.permissions); // Originally unused
        iob->bind(BIND_SIGNATURE_INT32, &slots[i].building_id);
        iob->bind(BIND_SIGNATURE_UINT8, &slots[i].in_use);
        iob->bind(BIND_SIGNATURE_UINT8, &slots[i].storage.empty_all);
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &slots[i].storage.resource_state[r]);
        }

        iob->bind____skip(6); // unused resource states
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT16, &slots[i].storage.resource_max_accept[r]);
        }

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT16, &slots[i].storage.resource_max_get[r]);
        }
        //        iob->bind____skip(144); // ?????
    }
}

void building_storages_chunk::reset() {
    building_storage_clear_all();
}

// Empty All order snapshot — appended chunk (save v175+), raw blob.
void storages_empty_all_backup_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& backups = xvalue<building_storages_t>::ref().empty_all_backups;
    iob->bind(BIND_SIGNATURE_RAW, backups, sizeof(backups));
}

void storages_empty_all_backup_chunk::load_defaults(size_t version) {
    // no snapshot in the file means no storage had Empty All pending
    auto& backups = xvalue<building_storages_t>::ref().empty_all_backups;
    memset(backups, 0, sizeof(backups));
}
