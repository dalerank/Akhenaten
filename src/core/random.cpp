#include "core/random.h"

#include <string.h>
//#include <cmath>

#define MAX_RANDOM 100

static struct {
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
} data;

void random_init(void) {
    memset(&data, 0, sizeof(data));
    data.iv1 = 0x54657687;
    data.iv2 = 0x72641663;
}

void random_generate_next(void) {
    data.pool[data.pool_index++] = data.random1_7bit;
    if (data.pool_index >= MAX_RANDOM)
        data.pool_index = 0;

    for (int i = 0; i < 31; i++) {
        unsigned int r1 = (((data.iv1 & 0x10) >> 4) ^ data.iv1) & 1;
        unsigned int r2 = (((data.iv2 & 0x10) >> 4) ^ data.iv2) & 1;
        data.iv1 = data.iv1 >> 1;
        data.iv2 = data.iv2 >> 1;
        if (r1)
            data.iv1 |= 0x40000000;
        if (r2)
            data.iv2 |= 0x40000000;
    }
    data.random1_3bit = data.iv1 & 0x7;
    data.random1_7bit = data.iv1 & 0x7f;
    data.random1_15bit = data.iv1 & 0x7fff;
    data.random2_3bit = data.iv2 & 0x7;
    data.random2_7bit = data.iv2 & 0x7f;
    data.random2_15bit = data.iv2 & 0x7fff;
}

void random_generate_pool(void) {
    data.pool_index = 0;
    for (int i = 0; i < MAX_RANDOM; i++) {
        random_generate_next();
    }
}

int8_t random_byte(void) {
    return data.random1_7bit;
}
int8_t random_byte_alt(void) {
    return data.random2_7bit;
}
int16_t random_short(void) {
    return data.random1_15bit;
}
int32_t random_from_pool(int index) {
    return data.pool[(data.pool_index + index) % MAX_RANDOM];
}

int32_t random_within_composite_field_bounds(int16_t *field_composite, int32_t last) {
    long long lVar1;
    unsigned long long uVar2;
//    int in_EAX;
//    uint32_t uVar3;
//    uint32_t uVar4;
//    uint32_t uVar5;
//    uint32_t uVar6;

    // first operation (check)
    int16_t field_fixed = field_composite[1];
    if (field_fixed == -1) {
        if ((field_composite[2] > -1) && (field_composite[3] > -1)) { //&&
//            (last = ((int)field_composite[3] - (int)field_composite[2]) + 1, last == 1))
//            goto LAB_004488d5;
            int next = ((int)field_composite[3] - (int)field_composite[2]) + 1;
            if (next == 1) {
                *field_composite = field_fixed;
                return last;
            }
        }
    }
    else {
        if (field_composite[2] == -1) goto LAB_004488d5;
    }

    // random shuffle
//    (&DAT_00d3a1b8)[DAT_00d3a1b4] = DAT_00d3a364;
//    DAT_00d3a1b4 = DAT_00d3a1b4 + 1;
//    if (99 < DAT_00d3a1b4) {
//        DAT_00d3a1b4 = 0;
//    }
//    iVar3 = 31;
//    do {
//        uVar3 = DAT_00d3a374 >> 4;
//        uVar5 = DAT_00d3a374 & 1;
//        uVar6 = DAT_00d3a370 >> 4;
//        uVar4 = DAT_00d3a370 & 1;
//        DAT_00d3a374 = DAT_00d3a374 >> 1;
//        DAT_00d3a370 = DAT_00d3a370 >> 1;
//        if ((uVar3 & 1) != uVar5) {
//            DAT_00d3a374 = DAT_00d3a374 | 0x40000000;
//        }
//        if ((uVar6 & 1) != uVar4) {
//            DAT_00d3a370 = DAT_00d3a370 | 0x40000000;
//        }
//        iVar3--;
//    } while (iVar3 != 0);
//
//    R_DAT_00d3a368 = DAT_00d3a374 & 7;
//    DAT_00d3a364 = DAT_00d3a374 & 0x7f;
//    _DAT_00d3a360 = DAT_00d3a374 & 0x7fff;
//    R_DAT_00d3a35c = DAT_00d3a370 & 7;
//    _DAT_00d3a358 = DAT_00d3a370 & 0x7f;
//    _DAT_00d3a354 = DAT_00d3a370 & 0x7fff;
    random_generate_next();

    // second operation
    int iVar3;
    field_fixed = field_composite[1];
    if (field_fixed < 0) {
        lVar1 = (long long)((int)field_composite[3] - (int)field_composite[2]);
        uVar2 = (unsigned long long)data.random1_15bit; //_DAT_00d3a360
        *field_composite = (short)((long long)uVar2 % lVar1) + field_composite[2];
        return (uint32_t)((unsigned long long)uVar2 / lVar1);
    }
    if (field_composite[2] < 0)
        iVar3 = 1;
    else
        iVar3 = (-1 < field_composite[3]) + 2;

    // final composition
    last = (int32_t)((unsigned long long)data.random1_15bit / (unsigned long long)(long long)iVar3); //_DAT_00d3a360
    iVar3 = (int32_t)((unsigned long long)data.random1_15bit % (unsigned long long)(long long)iVar3); //_DAT_00d3a360
    if (iVar3 != 0) {
        if (iVar3 == 1) {
            *field_composite = field_composite[2];
            return last;
        }
        *field_composite = field_composite[3];
        return (int32_t)(uint16_t)field_composite[3];
    }
    LAB_004488d5:
    *field_composite = field_fixed;
    return last;
}

void random_around_point(int x_home, int y_home, int x, int y, int *dest_x, int *dest_y, int step, int bias, int max_dist) {
    random_generate_next();
    int det = 64/step;
    int rand_x = random_byte() / det - step;
    int rand_y = random_byte_alt() / det - step;
    *dest_x = x + rand_x;
    *dest_y = y + rand_y;
    int dist_x = (x_home - *dest_x);
    int dist_y = (y_home - *dest_y);
    if (bias <= 1)
        bias = 1;
    *dest_x += dist_x / bias;
    *dest_y += dist_y / bias;
    if (max_dist > 0) {
        dist_x = (x_home - *dest_x);
        dist_y = (y_home - *dest_y);
        if (dist_x > max_dist)
            *dest_x = x_home + max_dist;
        if (dist_x < -max_dist)
            *dest_x = x_home - max_dist;
        if (dist_y > max_dist)
            *dest_y = y_home + max_dist;
        if (dist_y < -max_dist)
            *dest_y = y_home - max_dist;
    }
}

// please email me if you have a better name for this
int random_bool_lerp_scalar_int(int minimum, int maximum, int v) {

    // let's not make our life harder.
    v -= minimum;
    maximum -= minimum;
    minimum = 0;

    if (v <= minimum)
        return 0;
    if (v >= maximum)
        return 1;

    int length = maximum - minimum;
    int max_length = uint16_t(-1);
    float det = (float)max_length / (float)length;

    random_generate_next();
    uint16_t rand_short = (uint16_t)random_short();
    rand_short = rand_short / det;

    if (v < rand_short)
        return 0;
    else
        return 1;
}

void random_load_state(buffer *buf) {
    data.iv1 = buf->read_u32();
    data.iv2 = buf->read_u32();
}

void random_save_state(buffer *buf) {
    buf->write_u32(data.iv1);
    buf->write_u32(data.iv2);
}
