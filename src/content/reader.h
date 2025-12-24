#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "core/core.h"
#include "core/bstring.h"

namespace vfs {

struct reader_base {
    inline reader_base() : __data(nullptr), __pos(0) { __debug_info = nullptr; }
    inline reader_base(pcstr _debug_info, const void *data, int size)
        : __data((const uint8_t *)data), __pos(0), __size(size) {
        __debug_info = _debug_info;
        assert(__debug_info.size() > 0u);
    }

    inline int elapsed() const { return __size - __pos; };
    inline bool eof() const { return elapsed() <= 0; };
    inline int tell() const { return __pos; };
    inline void seek(int ptr) {
        __pos = ptr;
        verify_no_crash((__pos <= __size) && (__pos >= 0));
    };
    inline char *begin() { return (char*)__data; }
    inline char *end() { return (char*)(__data + __size); }
    inline const char *begin() const { return (const char*)__data; }
    inline const char *end() const { return (const char*)(__data + __size); }
    inline int length() const { return __size; };
    inline int size() const { return __size; }
    inline void *data() const { return (void *)__data; };
    inline void *current_pointer() const { return (void *)(__data + __pos); };
    inline void advance(size_t cnt) {
        __pos += (int)cnt;
        verify_no_crash((__pos <= __size) && (__pos >= 0));
    };
    inline void rewind() { seek(0); }

    inline void r(void *p, int c) {
        verify_no_crash(__pos + c <= __size);
        memcpy(p, current_pointer(), c);
        advance(c);
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
        uint64_t *t = (uint64_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline uint32_t r_uint32_t() {
        uint32_t *t = (uint32_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline uint16_t r_uint16_t() {
        uint16_t *t = (uint16_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline uint8_t r_uint8_t() {
        uint8_t *t = (uint8_t *)current_pointer();
        advance(sizeof(*t));
        return *t;
    }
    inline int64_t r_int64_t() {
        int64_t *t = (int64_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline int32_t r_int32_t() {
        int32_t *t = (int32_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline int16_t r_int16_t() {
        int16_t *t = (int16_t *)current_pointer();
        advance(sizeof(*t));
        return (*t);
    }
    inline int8_t r_int8_t() {
        int8_t *t = (int8_t *)current_pointer();
        advance(sizeof(*t));
        return *t;
    }
    inline float r_float() {
        float t;
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
        __debug_info = _debug_info;
        verify_no_crash(__debug_info.size() > 0u);
    }

private:
    std::string __debug_info;

public:
    pcstr debug_info() const {
        verify_no_crash(__debug_info.size() > 0);
        return __debug_info.c_str();
        return nullptr;
    }

protected:
    const uint8_t *__data;
    int __pos;
    int __size;
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