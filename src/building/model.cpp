#include "building/model.h"

#include "core/string.h"
#include "core/log.h"
#include "io/io.h"

#include <game/settings.h>
#include <stdlib.h>
#include <string.h>

#define TMP_BUFFER_SIZE 100000

static const uint8_t ALL_BUILDINGS[] = {'A', 'L', 'L', ' ', 'B', 'U', 'I', 'L', 'D', 'I', 'N', 'G', 'S', 0};
static const uint8_t ALL_HOUSES[] = {'A', 'L', 'L', ' ', 'H', 'O', 'U', 'S', 'E', 'S', 0};

struct model_data_t {
    model_house houses[5][20];
};

model_data_t g_model_data;

static const uint8_t* skip_non_digits(const uint8_t* str) {
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
static const uint8_t* get_value(const uint8_t* ptr, const uint8_t* end_ptr, int* value) {
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    ptr += index_of(ptr, ',', (int)(end_ptr - ptr));
    return ptr;
}

bool model_load_file(const char* filepath,
                     int NUM_BUILDINGS,
                     int NUM_HOUSES,
                     model_house* houses) {
    buffer buf(TMP_BUFFER_SIZE);
    int filesize = 0;
    filesize = io_read_file_into_buffer(filepath, NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        logs::error("Model file not found");
        return false;
    }

    // go through the file to assert number of buildings
    int num_lines = 0;
    int guard = NUM_BUILDINGS + NUM_HOUSES;
    int brace_index;
    const uint8_t* haystack = buf.get_data();
    const uint8_t* ptr = &haystack[index_of_string((pcstr)haystack, (pcstr)ALL_BUILDINGS, filesize)];
    do {
        guard--;
        brace_index = index_of(ptr, '{', filesize);
        if (brace_index) {
            ptr += brace_index;
            num_lines++;
        }
    } while (brace_index && guard > 0);
    if (num_lines != NUM_BUILDINGS + NUM_HOUSES) {
        logs::error("Model has incorrect no of lines %u ", num_lines + 1);
        return false;
    }

    // parse buildings data
    ptr = &haystack[index_of_string((pcstr)haystack, (pcstr)ALL_BUILDINGS, filesize)];
    const uint8_t* end_ptr = &haystack[filesize];
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        ptr += index_of(ptr, '{', filesize);

        int tmp;
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
        ptr = get_value(ptr, end_ptr, &tmp);
    }

    // parse houses data
    ptr = &haystack[index_of_string((pcstr)haystack, (pcstr)ALL_HOUSES, filesize)];
    for (int i = 0; i < NUM_HOUSES; i++) {
        ptr += index_of(ptr, '{', filesize);

        ptr = get_value(ptr, end_ptr, &houses[i].devolve_desirability);
        ptr = get_value(ptr, end_ptr, &houses[i].evolve_desirability);
        ptr = get_value(ptr, end_ptr, &houses[i].entertainment);
        ptr = get_value(ptr, end_ptr, &houses[i].water);
        ptr = get_value(ptr, end_ptr, &houses[i].religion);
        ptr = get_value(ptr, end_ptr, &houses[i].education);
        ptr = get_value(ptr, end_ptr, &houses[i].food);
        ptr = get_value(ptr, end_ptr, &houses[i].dentist);
        ptr = get_value(ptr, end_ptr, &houses[i].physician);
        ptr = get_value(ptr, end_ptr, &houses[i].health);
        ptr = get_value(ptr, end_ptr, &houses[i].food_types);
        ptr = get_value(ptr, end_ptr, &houses[i].pottery);
        ptr = get_value(ptr, end_ptr, &houses[i].linen);
        ptr = get_value(ptr, end_ptr, &houses[i].jewelry);
        ptr = get_value(ptr, end_ptr, &houses[i].beer);
        ptr = get_value(ptr, end_ptr, &houses[i].crime_risk);
        ptr = get_value(ptr, end_ptr, &houses[i].crime_risk_base);
        ptr = get_value(ptr, end_ptr, &houses[i].prosperity);
        ptr = get_value(ptr, end_ptr, &houses[i].max_people);
        ptr = get_value(ptr, end_ptr, &houses[i].tax_multiplier);
        ptr = get_value(ptr, end_ptr, &houses[i].malaria_risk);
        ptr = get_value(ptr, end_ptr, &houses[i].disease_risk);
    }

    logs::info("Model loaded");
    return true;
}

bool model_load(void) {
    auto& data = g_model_data;

    if (!model_load_file("Pharaoh_Model_VeryEasy.txt", 237, 20, data.houses[0])) {
        return false;
    }
    if (!model_load_file("Pharaoh_Model_Easy.txt", 237, 20, data.houses[1])) {
        return false;
    }
    if (!model_load_file("Pharaoh_Model_Normal.txt", 237, 20, data.houses[2])) {
        return false;
    }
    if (!model_load_file("Pharaoh_Model_Hard.txt", 237, 20, data.houses[3])) {
        return false;
    }
    if (!model_load_file("Pharaoh_Model_Impossible.txt", 237, 20, data.houses[4])) {
        return false;
    }

    return true;
}

const model_house& model_get_house(int level) {
    return g_model_data.houses[g_settings.difficulty()][level];
}
