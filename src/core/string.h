#pragma once

#include <cstddef>
#include <stdint.h>
#include <string>

#include "bstring.h"
#include "core/vec2i.h"

struct textid {
    uint16_t group = 0;
    uint16_t id = 0;
    bool valid() const { return group > 0; }
    pcstr c_str() const;
    pcstr c_str_safe(pcstr def) const;
    textid &operator=(std::initializer_list<int> v) {
        if (v.size() > 0) group = *v.begin();
        if (v.size() > 1) id = *(v.begin() + 1);
        return *this;
    }
    textid &operator=(vec2i v) { group = v.x; id = v.y; return *this; }
};

struct metainfo {
    uint16_t help_id;
    uint16_t text_id;
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

pcstr strstr_rev(pcstr string, pcstr sub_string);

inline int string_item_count(pcstr src, char separator) {
    int cnt = 0;
    if (src && *src) {
        pcstr	res = src;
        pcstr	last_res = res;
        while (0 != (res = strchr(res, separator))) {
            res++;
            last_res = res;
            cnt++;
        }

        if (strlen(last_res)) {
            cnt++;
        }
    }
    return		cnt;
}

inline pcstr string_item_pos(pcstr src, uint32_t pos, char separator) {
    pcstr res = src;

    uint32_t p = 0;
    while ((p < pos) && (0 != (res = strchr(res, separator)))) { res++; p++; }

    return res;
}

template<typename string_t>
inline pcstr string_copy_first(pcstr src, string_t &dst, char separator = ',') {
    pcstr p;
    ptrdiff_t n;

    p = strchr(src, separator);
    n = (p != 0) ? (p - src) : strlen(src);
    dst = src;
    dst.resize(n);

    return dst.c_str();
}

inline pstr	string_trim_left(pstr str) {
    pstr p = str;
    while (*p && (uint8_t(*p) <= uint8_t(' '))) p++;
    if (p != str) {
        pstr t = str;
        for (; *p; t++, p++) *t = *p;
        *t = 0;
    }
    return str;
}

inline pstr	string_trim_right(pstr src) {
    pstr p = src + strlen(src);
    while ((p != src) && (uint8_t(*p) <= uint8_t(' '))) p--;
    *(++p) = 0;

    return src;
}

inline pstr	string_trim(pstr src) {
    string_trim_left(src);
    string_trim_right(src);
    return src;
}

template<typename string_t>
inline pcstr string_item(pcstr src, int index, string_t &dst, char separator = ',', pcstr def = "") {
    pcstr ptr;
    ptr = string_item_pos(src, index, separator);
    if (ptr) {
        string_copy_first(ptr, dst, separator);
    } else {
        dst = def;
    }
    
    return dst.c_str();
}

template<typename arr_t>
inline void string_to_array_t(arr_t &lst, pcstr src, char separator) {
    int t_cnt = string_item_count(src, separator);
    lst.clear();
    if (!src || !*src) {
        return;
    }

    lst.resize(t_cnt);
    typename arr_t::value_type tmp;
    for (int i = 0; i < t_cnt; i++) {
        string_item(src, i, tmp, separator, nullptr);
        string_trim(tmp.data());
        lst[i] = tmp;
    }
}
