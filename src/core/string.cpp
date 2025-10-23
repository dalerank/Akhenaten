#include "core/string.h"

#include <cstring>
#include <ctype.h>

#include <io/gamefiles/lang.h>

uint8_t* string_copy(const uint8_t* src, uint8_t* dst, int maxlength) {
    int length = 0;
    while (length < maxlength && *src) {
        *dst = *src;
        src++;
        dst++;
        length++;
    }
    if (length == maxlength)
        dst--;

    *dst = 0;
    return dst;
}

int string_length(const uint8_t* str) {
    if (!str) {
        return 0;
    }

    int length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}

pcstr string_from_ascii(pcstr str, bool extended) {
    pcstr s = str;
    while (*s) {
        if (*s & 0x80 && !extended)
            return 0;
        s++;
    }
    return str;
}

int string_to_int(const uint8_t* str) {
    static const int multipliers[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
    const uint8_t* ptr = str;
    int negative = 0;
    int num_chars = 0;
    if (*ptr == '-') {
        negative = 1;
        ptr++;
    }
    while (*ptr >= '0' && *ptr <= '9') {
        num_chars++;
        ptr++;
    }

    if (num_chars > 8)
        return 0;

    ptr = str;
    if (*ptr == '-')
        ptr++;

    int result = 0;
    while (num_chars) {
        --num_chars;
        result += multipliers[num_chars] * (*ptr - '0');
        ptr++;
    }
    if (negative)
        result = -result;

    return result;
}
int string_from_int(uint8_t* dst, int value, bool force_plus_sign) {
    int total_chars = 0;
    if (value >= 0) {
        if (force_plus_sign) {
            dst[0] = '+';
            dst++;
            total_chars = 1;
        }
    } else {
        dst[0] = '-';
        dst++;
        value = -value;
        total_chars = 1;
    }
    int num_digits;
    if (value < 10)
        num_digits = 1;
    else if (value < 100)
        num_digits = 2;
    else if (value < 1000)
        num_digits = 3;
    else if (value < 10000)
        num_digits = 4;
    else if (value < 100000)
        num_digits = 5;
    else if (value < 1000000)
        num_digits = 6;
    else if (value < 10000000)
        num_digits = 7;
    else if (value < 100000000)
        num_digits = 8;
    else if (value < 1000000000)
        num_digits = 9;
    else
        num_digits = 10;

    total_chars += num_digits;

    dst[num_digits] = 0;
    while (--num_digits >= 0) {
        dst[num_digits] = (uint8_t)(value % 10 + '0');
        value /= 10;
    }

    return total_chars;
}
int string_compare_case_insensitive(const char* a, const char* b) {
    while (*a && *b) {
        int aa = tolower(*a);
        int bb = tolower(*b);
        if (aa != bb)
            return aa - bb;

        ++a;
        ++b;
    }
    if (*a)
        return 1;

    if (*b)
        return -1;

    return 0;
}
bool string_equals(const uint8_t* a, const uint8_t* b, bool case_sentitive) {
    while (*a && *b && ((case_sentitive == 1 && *a == *b) || (case_sentitive == 0 && tolower(*a) == tolower(*b)))) {
        ++a;
        ++b;
    }
    if (*a == 0 && *b == 0)
        return true;
    else
        return false;
}

int index_of_string(pcstr haystack, pcstr needle, int haystack_length) {
    const size_t needle_length = strlen(needle);
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle[0] && (strncmp(haystack + i, needle, needle_length) == 0)) {
            return i + 1;
        }
    }
    return 0;
}

int index_of(const uint8_t* haystack, uint8_t needle, int haystack_length) {
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle)
            return i + 1;
    }
    return 0;
}

void strncpy_safe(char* dest, const char* src, std::size_t destsz) {
    size_t srcsz = strlen(src); // crash here if not nul-terminated
    if (srcsz > destsz - 1)
        srcsz = destsz - 1;
    memmove(dest, src, srcsz); // memmove is safe if dest and src overlap
    dest[srcsz] = '\0';
}

pcstr strstr_rev(pcstr string, pcstr sub_string) {
    assert(string && sub_string);

    if (!*string || !*sub_string) {
        return nullptr;
    }

    pcstr p1 = string;
    while (*(p1 + 1)) {
        p1++;
    }

    pcstr p2 = sub_string;
    pcstr p1_i = p1;
    while (*(p2 + 1)) { 
        p2++;
        p1_i--;
    }

    pcstr p2_end = p2;

    while (p1_i >= string) {
        pcstr p1_start = p1;
        p2 = p2_end;
        while (p2 >= sub_string && *p1 == *p2) {
            p1--;
            p2--;
        }
        if (p2 < sub_string) {
            return p1 + 1;
        }
        p1 = p1_start - 1;
        p1_i--;
    }

    return nullptr;
}

pcstr textid::c_str_safe(pcstr def) const {
    pcstr text = valid() ? (pcstr)lang_get_string(group, id) : nullptr;

    return text ? text : def;
}

pcstr textid::c_str() const {
    return c_str_safe("undefined");
}
