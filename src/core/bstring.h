#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using pcstr = const char *;
using pstr = char *;

template <size_t _size>
class bstring {
    using ref = bstring<_size>&;
    using const_ref = const bstring<_size>&;

protected:
    char _data[_size];

public:
    enum {
        capacity = _size,
    };

public:
    explicit inline bstring(int n) {
        ::snprintf(_data, _size, "%d", n);
    }
    inline pcstr c_str() const {
        return _data;
    }
    inline char* data() {
        return _data;
    }
    inline bstring() {
        _data[0] = 0;
    }
    inline bstring(const_ref other) {
        ::strncpy(_data, other._data, _size);
    }

    inline bstring(pcstr s1) { concat(s1); }
    inline bstring(pcstr s1, int v, pcstr fmt = nullptr) { snprintf(_data, _size, fmt ? fmt : "%s%d", s1, v); }
    inline bstring(pcstr s1, pcstr s2) { concat(s1, s2); }
    inline bstring(pcstr s1, pcstr s2, pcstr s3) { concat(s1, s2, s3); }
    inline bstring(pcstr s1, pcstr s2, pcstr s3, pcstr s4) { concat(s1, s2, s3, s4); }
    inline bstring(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5) { concat(s1, s2, s3, s4, s5); }
    inline bstring(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5, pcstr s6) { concat(s1, s2, s3, s4, s5, s6); }
    inline bstring(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5, pcstr s6, pcstr s7) { concat(s1, s2, s3, s4, s5, s6, s7); }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-truncation"
#endif

    inline ref concat(pcstr s1) { snprintf(_data, _size-1, "%s", s1); return *this; }
    inline ref concat(pcstr s1, pcstr s2) { snprintf(_data, _size-1, "%s%s", s1, s2); return *this; }
    inline ref concat(pcstr s1, pcstr s2, pcstr s3) { snprintf(_data, _size-1, "%s%s%s", s1, s2, s3); return *this; }
    inline ref concat(pcstr s1, pcstr s2, pcstr s3, pcstr s4) { snprintf(_data, _size-1, "%s%s%s%s", s1, s2, s3, s4); return *this; }
    inline ref concat(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5) { snprintf(_data, _size-1, "%s%s%s%s%s", s1, s2, s3, s4, s5); return *this; }
    inline ref concat(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5, pcstr s6) { snprintf(_data, _size-1, "%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6); return *this; }
    inline ref concat(pcstr s1, pcstr s2, pcstr s3, pcstr s4, pcstr s5, pcstr s6, pcstr s7) { snprintf(_data, _size-1, "%s%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6, s7); return *this; }

#ifdef __clang__
#pragma clang diagnostic pop
#endif

    inline ref cat(pcstr s) { snprintf(_data, _size, "%s%s", _data, s); return *this; }
    inline ref cat(pcstr s1, pcstr s2) { snprintf(_data, _size, "%s%s%s", _data, s1, s2); return *this; }
    inline ref cat(pcstr s1,pcstr s2, pcstr s3) { snprintf(_data, _size, "%s%s%s%s", _data, s1, s2, s3); return *this; }
    inline ref cat(pcstr s1,pcstr s2, pcstr s3, pcstr s4) { snprintf(_data, _size, "%s%s%s%s%s", _data, s1, s2, s3, s4); return *this; }
    inline ref cat(pcstr*s1,pcstr s2, pcstr s3, pcstr s4, pcstr s5) { snprintf(_data, _size, "%s%s%s%s%s%s", _data, s1, s2, s3, s4, s5); return *this; }

    inline ref ncat(pcstr s, size_t cnt) { ::strncat(_data, s, cnt); return *this; }
    inline bool operator!() const { return empty(); }

    template <typename... Args>
    inline ref append_fmt(pcstr fmt, Args&&... args) {
        size_t size = this->len();
        char* dest = _data + size;
        size_t remain = _size - size;
        if (remain > 0) {
            snprintf(dest, remain, fmt, std::forward<Args>(args)...);
        }
        return *this;
    }

    inline ref append(pcstr str) {
        size_t size = this->len();
        char* dest = _data + size;
        size_t remain = _size - size;
        if (remain > 0) {
            snprintf(dest, remain, "%s", str);
        }
        return *this;
    }

    inline ref append(char s) {
        size_t size = this->len();
        char* dest = _data + size;
        size_t remain = _size - size;
        if (remain > 0) {
            *dest = s;
            *(dest + 1) = '\0';
        }

        return *this;
    }

    inline ref itoa(int n) { ::snprintf(_data, _size, "%d", n); return *this; }
    inline int atoi() { return ::atoi(_data); }
    inline float atof() { return ::atof(_data); }
    inline int64_t atoi64() { return ::strtoll(_data); }

    template <typename... Args>
    inline ref printf(pcstr fmt, Args&&... args) {
        snprintf(_data, _size - 1, fmt, std::forward<Args>(args)...);
        _data[_size - 1] = 0;
        return *this;
    }

    inline ref tolower() {
        pstr str = _data;
        while (*str) {
            *str = std::tolower(*str);
            ++str;
        }
        return *this;
    }

    inline ref toupper() {
        pstr str = _data;
        while (*str) {
            *str = std::toupper(*str);
            ++str;
        }
        return *this;
    }

    inline ref trim() {
        pstr end = std::remove_if(_data, _data + len(), ::isspace);
        *end = '\0';

        return *this;
    }

    inline bool starts_with(pcstr s) const {
        return !empty() && (strncmp(_data, s, strlen(s)) == 0);
    }

    inline bool ends_with(pcstr s) const {
        int slen = (s && *s) ? strlen(s) : 0;
        if (!slen) {
            return false;
        }
        int mylen = len();
        if (empty() || (mylen <= slen)) {
            return false;
        }
        pcstr ptr = ::strstr((pcstr)_data, s);
        return (ptr && (ptr == (_data + (mylen - slen) )));
    }

    inline char back() const { return empty() ? 0 : (_data[len() - 1]); }
    inline size_t find(char t) {
        pcstr p = ::strchr(_data, t);
        return (p ? (p - _data) : -1);
    }

    inline ref replace(const char x, const char y) {
        std::replace_if(_data, _data + len(), [x](char c) { return c == x; }, y);
        return *this;
    }

    inline ref replace_str(pcstr subst, pcstr repl) {
        size_t _len = len();
        const size_t subst_len = ::strlen(subst);
        const size_t repl_len = ::strlen(repl);

        char* found_pos = std::search(_data, _data + len(), subst, subst + subst_len);

        while (found_pos != _data + _len) {
            std::ptrdiff_t sizeDiff = repl_len - subst_len;
            ::memmove(found_pos + repl_len, found_pos + subst_len, _data + _len - (found_pos + subst_len) + 1);
            ::memcpy(found_pos, repl, repl_len);
            _len = len();
            found_pos = std::search(found_pos + repl_len, _data + _len, subst, subst + subst_len);
        }
        return *this;
    }

    inline size_t len() const { return ::strlen(_data); }
    inline void resize(size_t s) { assert(s < _size); _data[s] = '\0'; }
    inline bool empty() const { return !_data[0]; }
    inline void clear() { _data[0] = 0; }
    inline bool equals(const_ref other) const { return ::strncmp(_data, other._data, _size) == 0; }
    inline bool equals(pcstr s) const { assert(s); return ::strncmp(_data, s, _size) == 0; }
    inline void operator=(const_ref other) { ::strncpy(_data, other._data, _size); }
    inline void operator=(pcstr s) { ::snprintf(_data, _size, "%s", s ? s : ""); }
    inline void operator=(const uint8_t* s) { ::snprintf(_data, _size, "%s",  s ? (pcstr)s : ""); }
    inline bool operator==(const_ref other) const { return ::strncmp(_data, other._data, _size) == 0; }
    inline operator const uint8_t *() const { return (const uint8_t *)_data; }
    inline operator uint8_t *() { return (uint8_t *)_data; }
    inline bool operator==(pcstr s) const { assert(s); return ::strncmp(_data, s, _size) == 0; }

    inline bool operator!=(const_ref other) const { return !equals(other); }
    inline bool operator!=(pcstr s) const { assert(s); return ::strncmp(_data, s, _size) != 0; }
    inline char operator[](int i) const { return _data[i]; }
    inline char &operator[](int i) { return _data[i]; }

    inline operator char*() { return _data; }
    inline operator const char*() const { return _data; }

    inline pcstr strstr(const_ref sub_str) const { return ::strstr(_data, sub_str._data); }
    inline pcstr strstr(const_ref sub_str) { return ::strstr(_data, sub_str._data); }
    inline int cmp(const_ref other) const { return strcmp(_data, other._data); }
    inline int icmp(const_ref other) const { return stricmp(_data, other._data); }
    inline int ncmp(const_ref other, unsigned int count) const { return ::strncmp(_data, other._data, count); }

    inline pcstr strstr(pcstr sub_str) const { return ::strstr(_data, sub_str); }
    inline pcstr strstr(pcstr sub_str) { return ::strstr(_data, sub_str); }
    inline pcstr strchr(char v) { return ::strchr(_data, v); }
    inline int cmp(pcstr str) const { return strcmp(_data, str); }
    inline int icmp(pcstr str) const { return stricmp(_data, str); }
    inline int ncmp(pcstr str, unsigned int count) const { return ::strncmp(_data, str, count); }

    inline size_t hash() {
        constexpr size_t p = 31;
        constexpr size_t m = 1e9 + 9;
        size_t hash_value = 0;
        size_t p_pow = 1;
        for (const char *c = _data; *c != 0; ++c) {
            hash_value = (hash_value + (*c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }
};

using bstring16 = bstring<16>;
using bstring32 = bstring<32>;
using bstring64 = bstring<64>;
using bstring128 = bstring<128>;
using bstring256 = bstring<256>;
using bstring512 = bstring<512>;
using bstring1024 = bstring<1024>;
