#pragma once

#include <cstdint>

#include "core/archive.h"
#include "city/military.h"

struct city_military_t {
    uint8_t total_batalions;
    uint8_t total_soldiers;
    uint8_t kingdome_service_batalions;
    int32_t infantry_batalions;
    int32_t native_attack_duration;
    int32_t tower_sentry_request;

    void clear_infantry_batalions();
    void add_infantry_batalion();
    bool has_infantry_batalions();
    void clear_kingdome_service_batalions();
    void update_totals();
    bool is_native_attack_active();
    void start_native_attack();
    void decrease_native_attack_duration();
    void request_tower_sentry();
    void decay_tower_sentry_request();
    bool has_tower_sentry_request() const;
    void reset();
};
ANK_CONFIG_PROPERTY(city_military_t,
    total_batalions,
    total_soldiers,
    kingdome_service_batalions,
    infantry_batalions,
    native_attack_duration);

city_military_t& city_military();

int city_military_distant_battle_kingdome_months_traveled();