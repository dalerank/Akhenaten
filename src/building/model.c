#include "building/model.h"

#include "core/io.h"
#include "core/log.h"
#include "core/string.h"
#include "core/game_environment.h"

#include <stdlib.h>
#include <string.h>

#define TMP_BUFFER_SIZE 100000

int NUM_BUILDINGS = 0;
int NUM_HOUSES = 0;

static const uint8_t ALL_BUILDINGS[] = {'A', 'L', 'L', ' ', 'B', 'U', 'I', 'L', 'D', 'I', 'N', 'G', 'S', 0};
static const uint8_t ALL_HOUSES[] = {'A', 'L', 'L', ' ', 'H', 'O', 'U', 'S', 'E', 'S', 0};

static model_building buildings[400]; // 130 in C3, more in Pharaoh, can't be bothered to make this dynamic
static model_house houses[20];

static int strings_equal(const uint8_t *a, const uint8_t *b, int len)
{
    for (int i = 0; i < len; i++, a++, b++) {
        if (*a != *b)
            return 0;

    }
    return 1;
}
static int index_of_string(const uint8_t *haystack, const uint8_t *needle, int haystack_length)
{
    int needle_length = string_length(needle);
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle[0] && strings_equal(&haystack[i], needle, needle_length))
            return i + 1;

    }
    return 0;
}
static int index_of(const uint8_t *haystack, uint8_t needle, int haystack_length)
{
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle)
            return i + 1;

    }
    return 0;
}

static const uint8_t *skip_non_digits(const uint8_t *str)
{
    int safeguard = 0;
    while (1) {
        if (++safeguard >= 1000)
            break;

        if ((*str >= '0' && *str <= '9') || *str == '-')
            break;

        str++;
    }
    return str;
}
static const uint8_t *get_value(const uint8_t *ptr, const uint8_t *end_ptr, int *value)
{
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    ptr += index_of(ptr, ',', (int) (end_ptr - ptr));
    return ptr;
}

int model_load(void)
{
    // allocate buffer for file data & read file into it
//    uint8_t *buffer = (uint8_t *) malloc(TMP_BUFFER_SIZE);
//    if (!buffer) {
//        log_error("No memory for model", 0, 0);
//        return 0;
//    }
//    memset(buffer, 0, TMP_BUFFER_SIZE);
    buffer *buf = new buffer(TMP_BUFFER_SIZE);
    int filesize = 0;
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            NUM_BUILDINGS = 130;
            NUM_HOUSES = 20;
            filesize = io_read_file_into_buffer("c3_model.txt", NOT_LOCALIZED, buf, TMP_BUFFER_SIZE);
            break;
        case ENGINE_ENV_PHARAOH:
            NUM_BUILDINGS = 237;
            NUM_HOUSES = 20;
            filesize = io_read_file_into_buffer("Pharaoh_Model_Easy.txt", NOT_LOCALIZED, buf, TMP_BUFFER_SIZE);
            break;
    }
    if (filesize == 0) {
        log_error("Model file not found", 0, 0);
        delete buf;
        return 0;
    }

    // go through the file to assert number of buildings
    int num_lines = 0;
    int guard = NUM_BUILDINGS + NUM_HOUSES;
    int brace_index;
    const uint8_t *haystack = (uint8_t*) buf->data_const();
    const uint8_t *ptr = &haystack[index_of_string(haystack, ALL_BUILDINGS, filesize)];
    do {
        guard--;
        brace_index = index_of(ptr, '{', filesize);
        if (brace_index) {
            ptr += brace_index;
            num_lines++;
        }
    } while (brace_index && guard > 0);
    if (num_lines != NUM_BUILDINGS + NUM_HOUSES) {
        log_error("Model has incorrect no of lines ", 0, num_lines + 1);
        delete buf;
        return 0;
    }

    // parse buildings data
    int dummy;
    ptr = &haystack[index_of_string(haystack, ALL_BUILDINGS, filesize)];
    const uint8_t *end_ptr = &haystack[filesize];
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        ptr += index_of(ptr, '{', filesize);

        ptr = get_value(ptr, end_ptr, &buildings[i].cost);
        ptr = get_value(ptr, end_ptr, &buildings[i].desirability_value);
        ptr = get_value(ptr, end_ptr, &buildings[i].desirability_step);
        ptr = get_value(ptr, end_ptr, &buildings[i].desirability_step_size);
        ptr = get_value(ptr, end_ptr, &buildings[i].desirability_range);
        ptr = get_value(ptr, end_ptr, &buildings[i].laborers);
        ptr = get_value(ptr, end_ptr, &dummy);
        ptr = get_value(ptr, end_ptr, &dummy);
    }

    // parse houses data
    ptr = &haystack[index_of_string(haystack, ALL_HOUSES, filesize)];
    for (int i = 0; i < NUM_HOUSES; i++) {
        ptr += index_of(ptr, '{', filesize);

        ptr = get_value(ptr, end_ptr, &houses[i].devolve_desirability);
        ptr = get_value(ptr, end_ptr, &houses[i].evolve_desirability);
        ptr = get_value(ptr, end_ptr, &houses[i].entertainment);
        ptr = get_value(ptr, end_ptr, &houses[i].water);
        ptr = get_value(ptr, end_ptr, &houses[i].religion);
        ptr = get_value(ptr, end_ptr, &houses[i].education);
        ptr = get_value(ptr, end_ptr, &houses[i].food);
        ptr = get_value(ptr, end_ptr, &houses[i].barber);
        ptr = get_value(ptr, end_ptr, &houses[i].bathhouse);
        ptr = get_value(ptr, end_ptr, &houses[i].health);
        ptr = get_value(ptr, end_ptr, &houses[i].food_types);
        ptr = get_value(ptr, end_ptr, &houses[i].pottery);
        ptr = get_value(ptr, end_ptr, &houses[i].oil);
        ptr = get_value(ptr, end_ptr, &houses[i].furniture);
        ptr = get_value(ptr, end_ptr, &houses[i].wine);
        ptr = get_value(ptr, end_ptr, &dummy);
        ptr = get_value(ptr, end_ptr, &dummy);
        ptr = get_value(ptr, end_ptr, &houses[i].prosperity);
        ptr = get_value(ptr, end_ptr, &houses[i].max_people);
        ptr = get_value(ptr, end_ptr, &houses[i].tax_multiplier);
    }

    log_info("Model loaded", 0, 0);
    delete buf;
    return 1;
}

const model_building MODEL_ROADBLOCK = {40,0,0,0,0};
const model_building *model_get_building(int type)
{
    if(type == BUILDING_ROADBLOCK) {
        return &MODEL_ROADBLOCK;
    }
    return &buildings[type];
}
const model_house *model_get_house(int level)
{
    return &houses[level];
}
