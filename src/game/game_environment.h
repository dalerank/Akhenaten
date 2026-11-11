#pragma once

#include <cstdint>

enum {
    ENGINE_MODE_RELEASE = 0,
    ENGINE_MODE_DEBUG = 1,
    ENGINE_MODE_MAX = 2
};

constexpr int MAX_REQUESTS = 20;
constexpr int MAX_INVASIONS = 20;
constexpr int MAX_DEMAND_CHANGES = 20;
constexpr int MAX_PRICE_CHANGES = 20;

constexpr uint8_t MAX_FISH_POINTS = 8;
constexpr int MAX_PREDATOR_HERD_POINTS = 4;
constexpr int MAX_PREY_HERD_POINTS = 4;
constexpr int MAX_DISEMBARK_POINTS = 3;
constexpr int MAX_INVASION_POINTS_LAND = 8;
constexpr int MAX_INVASION_POINTS_SEA = 8;
constexpr uint8_t MAX_FORMATIONS = 50;

constexpr int MAX_PLAYER_NAME = 32;
constexpr int MAX_SCENARIO_NAME = 65;
constexpr int MAX_SUBTITLE = 64;
constexpr int MAX_BRIEF_DESCRIPTION = 522;