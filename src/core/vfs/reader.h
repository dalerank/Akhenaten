#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "core/core.h"
#include "core/bstring.h"

namespace vfs {

struct reader_base {
    inline reader_base() : __data(nullptr), __pos(0), __size(0) {}
    inline reader_base(pcstr _debug_info, const void *data, int size)
        : __data((const uint8_t *)data), __pos(0), __size(size) {
        __debug_info = _debug_info;
    }

    inline int elapsed() const { return __size - __pos; };
    inline bool eof() const { return elapsed() <= 0; };
    inline int tell() const { return __pos; };
    inline bool seek(int64_t ptr) {
        if (ptr < 0 || ptr > __size) {
            __failed = true;
            return false;
        }
        __pos = (int)ptr;
        return true;
    };
    inline bool failed() const { return __failed; }
    inline char *begin() { return (char*)__data; }
    inline char *end() { return (char*)(__data + __size); }
    inline const char *begin() const { return (const char*)__data; }
    inline const char *end() const { return (const char*)(__data + __size); }
    inline int length() const { return __size; };
    inline int size() const { return __size; }
    inline void *data() const { return (void *)__data; };
    inline void *current_pointer() const { return (void *)(__data + __pos); };
    inline bool advance(int64_t cnt) { return seek((int64_t)__pos + cnt); };
    inline void rewind() { seek(0); }

    inline bool r(void* p, int64_t c) {
        if (c < 0 || c > elapsed()) {
            __failed = true;
            if (c > 0) {
                memset(p, 0, (size_t)c);
            }
            return false;
        }
        memcpy(p, current_pointer(), (size_t)c);
        __pos += (int)c;
        return true;
    }

    char *readline(char *buf, int n) {
        size_t len = __size - __pos;
        char *s, *p;

        if (len <= 0 || n <= 0) {       /* sanity check */
            return (NULL);
        }

        s = buf;
        p = (char *)(__data + __pos);
        n--;			/* leave space for NUL */
        if (n > 0) {
            if ((int)len > n)
                len = n;
            char *t = (char *)memchr((void *)p, '\n', len);
            if (t != NULL) {
                len = ++t - p;
                memcpy((void *)s, (const void *)p, len);
                advance(len);
                s[len] = '\0';
                return (buf);
            }
            (void)memcpy((void *)s, (void *)p, len);
            advance(len);
            s += len;
        }
        *s = '\0';
        return (buf);
    }

    inline uint64_t r_uint64_t() {
        uint64_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline uint32_t r_uint32_t() {
        uint32_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline uint16_t r_uint16_t() {
        uint16_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline uint8_t r_uint8_t() {
        uint8_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline int64_t r_int64_t() {
        int64_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline int32_t r_int32_t() {
        int32_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline int16_t r_int16_t() {
        int16_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline int8_t r_int8_t() {
        int8_t t = 0;
        r(&t, sizeof(t));
        return t;
    }
    inline float r_float() {
        float t = 0.f;
        r(&t, sizeof(t));
        return t;
    }

public:
    inline void init(const reader_base &from) {
        this->init(from.debug_info(), (void *)from.__data, from.__size, from.__pos);
    };

protected:
    inline void init(pcstr _debug_info, void *data, int size, int pos = 0) {
        __data = (const uint8_t *)data;
        __size = size;
        __pos = pos;
        __failed = false;
        __debug_info = _debug_info;
    }

private:
    bstring256 __debug_info;

public:
    pcstr debug_info() const {
        return __debug_info.c_str();
    }

protected:
    const uint8_t *__data;
    int __pos;
    int __size;
    bool __failed = false;
};

class data_reader : public reader_base {
public:
    inline data_reader(pcstr _debug_info, void *data, int size) : reader_base(_debug_info, data, size) {}
    virtual ~data_reader() { free((void *)__data); __data = nullptr; };

    inline void release(const void *&data, int &size) {
        data = __data;
        size = __size;

        __data = nullptr;
        __pos = 0;
        __size = 0;
    }
};

using reader = std::shared_ptr<data_reader>;

} // vfs