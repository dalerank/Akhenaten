#pragma once

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

int random_int();
int random_int_between(int min, int max);
double random_fractional();
