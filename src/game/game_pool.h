#pragma once

#include <vector>
#include "core/pool.h"
#include "game/game.h"
#include "game/game_events.h"

template<typename T, size_t N>
class mission_permanent_memory_pool : public pool<T, N> {
public:
    mission_permanent_memory_pool() {
        events::subscribe_permanent([this](event_game_mission_pre_load) {
            this->release_all();
        });
    }
};

template<typename T>
class mission_permanent_memory_pool_ext : public pool_ext<T> {
private:
    std::vector<typename generic_pool_ext<sizeof(T), std::alignment_of<T>::value>::element> buffer;
public:
    mission_permanent_memory_pool_ext(size_t init_size) 
        : buffer(init_size), pool_ext<T>(buffer.data(), init_size) {
        events::subscribe_permanent([this] (event_game_mission_pre_load) {
            this->release_all();
        });
    }
};

template<typename T, size_t N>
class game_permanent_memory_pool : public pool<T, N> {
public:
    game_permanent_memory_pool() {
    }
};

template<typename T>
class game_permanent_memory_pool_ext : public pool_ext<T> {
private:
    std::vector<typename generic_pool_ext<sizeof(T), std::alignment_of<T>::value>::element> buffer;
public:
    game_permanent_memory_pool_ext(size_t init_size) 
        : buffer(init_size), pool_ext<T>(buffer.data(), init_size) {
    }
};