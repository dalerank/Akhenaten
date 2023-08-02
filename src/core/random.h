#ifndef CORE_RANDOM_H
#define CORE_RANDOM_H

#include <stdint.h>

#include "core/buffer.h"

constexpr int MAX_RANDOM = 100;

// N.B.: carefulness required as random_data is already defined on Linux systems
// in the GNU C standard library files (/usr/include/stdlib.h:424:8)!
// TODO: clean this up eventually, maybe with a namespace or singleton
typedef struct {
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
} random_data_t;

const random_data_t* random_data_struct();

/**
 * @file
 * Random number generation.
 */

/**
 * Initializes the pseudo-random number generator
 */
void random_init(void);

/**
 * Generates the next pseudo-random random_byte
 */
void random_generate_next(void);

/**
 * Generates the pool of random bytes
 */
void random_generate_pool(void);

void random_TEMP_SET_DEBUG(uint32_t iv1, uint32_t iv2);

/**
 * Gets the current random 7-bit byte
 * @return Random 7-bit byte
 */
int8_t random_byte(void);

/**
 * Gets the current alternative random 7-bit byte
 * @return Alternative random 7-bits byte
 */
int8_t random_byte_alt(void);

/**
 * Gets the current random 15-bit short
 * @return Random 15-bits short
 */
int16_t random_short(void);

/**
 * Gets a random integer from the pool at the specified index
 * @param index Index to use
 * @return Random integer from the pool
 */
int32_t random_from_pool(int index);

void randomize_event_fields(int16_t field[4], int32_t* seed);

void random_around_point(int x_home,
                         int y_home,
                         int x,
                         int y,
                         int* dest_x,
                         int* dest_y,
                         int step,
                         int bias,
                         int max_dist);

bool random_bool_lerp_scalar_int(int minimum, int maximum, int v);

/////

uint16_t anti_scum_random_15bit(bool update = true);
bool anti_scum_random_bool();

#endif // CORE_RANDOM_H
