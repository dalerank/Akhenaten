#pragma once

#include <ctime>
#include <stdint.h>
#include "grid/point.h"

constexpr int MAX_RANDOM = 100;

// N.B.: carefulness required as random_data is already defined on Linux systems
// in the GNU C standard library files (/usr/include/stdlib.h:424:8)!
// TODO: clean this up eventually, maybe with a namespace or singleton
struct random_data_t {
    uint32_t iv1;
    uint32_t iv2;
    int8_t random1_3bit;
    int8_t random1_7bit;
    int16_t random1_15bit;
    int8_t random2_3bit;
    int8_t random2_7bit;
    int16_t random2_15bit;
    int pool_index;
    int32_t pool[MAX_RANDOM];
    time_t last_seed;
} ;

const random_data_t* random_data_struct();

void random_init(void);
void random_generate_next(void);
void random_generate_pool(void);
void random_TEMP_SET_DEBUG(uint32_t iv1, uint32_t iv2);
int8_t random_byte(void);
int8_t random_byte_alt(void);
int16_t random_short(void);
int32_t random_from_pool(int index);

void randomize_event_fields(int16_t field[4], int32_t* seed);

tile2i random_around_point(tile2i tile, tile2i src, int step, int bias, int max_dist);
bool random_bool_lerp_scalar_int(int minimum, int maximum, int v);

uint16_t anti_scum_random_15bit(bool update = true);
bool anti_scum_random_bool();
void anti_scum_srand(uint32_t seed);
// OG animals.c reseeds crt_rand from the wall clock; integral tests turn this off so runs stay reproducible.
void anti_scum_reseed_from_clock(uint32_t millis);
void anti_scum_set_clock_reseed(bool enabled);

int random_int();
int random_int_between(int min, int max);
double random_fractional();

enum e_random_hash_salt : uint32_t {
    RANDOM_SALT_FESTIVAL_DANCE = 0x1001,
    RANDOM_SALT_PAVILION_PLAY = 0x1002,
    RANDOM_SALT_BOOTH_PLAY = 0x1003,
    RANDOM_SALT_STATUE_OFFSET = 0x1004,
    RANDOM_SALT_ANIMAL_HUNGRY = 0x1005,
    RANDOM_SALT_EMPIRE_ROUTE_JITTER = 0x1006,
    RANDOM_SALT_EMPIRE_ROUTE_REMOVE = 0x1007,
    RANDOM_SALT_EMPIRE_TRADER_DELAY = 0x1008,
    RANDOM_SALT_EMPIRE_CITY = 0x1009,
    RANDOM_SALT_KINGDOME_TRADER_CAPACITY = 0x100a,
    RANDOM_SALT_HUNTER_LOOK = 0x100b,
    RANDOM_SALT_DISTANT_BATTLE_TAG = 0x100c,
};

// Stateless mix for non-OG sim choices: must not touch the LFSR or the crt (anti_scum) stream.
inline uint32_t random_hash(uint32_t a, uint32_t b, uint32_t c) {
    uint32_t h = a * 0x9E3779B1u;
    h ^= b + 0x85EBCA77u + (h << 6) + (h >> 2);
    h ^= c + 0xC2B2AE3Du + (h << 6) + (h >> 2);
    h ^= h >> 16;
    h *= 0x85EBCA6Bu;
    h ^= h >> 13;
    h *= 0xC2B2AE35u;
    h ^= h >> 16;
    return h;
}
