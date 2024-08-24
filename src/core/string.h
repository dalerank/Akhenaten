#pragma once

#include <cstddef>
#include <stdint.h>

#include "bstring.h"

struct textid {
    uint16_t group = 0;
    uint8_t id = 0;
    bool valid() const { return group > 0 && id > 0; }
    pcstr c_str() const;
    pcstr c_str_safe(pcstr def) const;
};

uint8_t* string_copy(const uint8_t* src, uint8_t* dst, int maxlength);
int string_length(const uint8_t* str);
const uint8_t* string_from_ascii(const char* str, bool extended = false);
int string_to_int(const uint8_t* str);
int string_from_int(uint8_t* dst, int value, bool force_plus_sign = false);
int string_compare_case_insensitive(const char* a, const char* b);
bool string_equals(const uint8_t* a, const uint8_t* b, bool case_sentitive);

bool string_needle_equals(const uint8_t* a, const uint8_t* b, int len);
int index_of_string(const uint8_t* haystack, const uint8_t* needle, int haystack_length);
int index_of(const uint8_t* haystack, uint8_t needle, int haystack_length);

// Also called: "why the fuck does the standard library not have this already?"
// TODO: eventually convert the entire engine to std::string
void strncpy_safe(char* dest, const char* src, std::size_t destsz);
