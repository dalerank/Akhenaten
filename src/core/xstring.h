#pragma once

#include "bstring.h"

#include <cstdint>
#include <cstdarg>

struct xstring_value {
    uint32_t reference;
    uint32_t length;
    uint32_t crc;
    xstring_value* next;
    char *value;
};

class xstring {
    xstring_value* _p;

protected:
    // ref-counting
    void _dec() {
        if (0 == _p)
            return;

        _p->reference--;
        if (0 == _p->reference)
            _p = 0;
    }

public:
    xstring_value *_dock(pcstr value);
    void _set(pcstr rhs) {
        xstring_value* v = _dock(rhs);
        if (0 != v) {
            v->reference++;
        }
        _dec();
        _p = v;
    }

    void _set(xstring const& rhs) {
        xstring_value* v = rhs._p;
        if (0 != v) {
            v->reference++;
        }
        _dec();
        _p = v;
    }

    [[nodiscard]]
    const xstring_value* _get() const { return _p; }

public:
    // construction
    xstring() { _p = nullptr; }
    xstring(pcstr rhs) { _p = nullptr; _set(rhs); }
    xstring(xstring const& rhs) { _p = 0; _set(rhs); }
    ~xstring() { _dec(); }

    xstring& operator=(pcstr rhs) { _set(rhs); return (xstring&)*this; }
    xstring& operator=(xstring const& rhs) { _set(rhs); return (xstring&)*this; }

    [[nodiscard]]
    pcstr operator*() const { return _p ? _p->value : nullptr; }

    [[nodiscard]]
    bool operator!() const { return _p == nullptr; }

    [[nodiscard]]
    char operator[](size_t id) { return _p->value[id]; }

    [[nodiscard]]
    char operator[](size_t id) const { return _p->value[id]; }

    [[nodiscard]]
    pcstr c_str() const { return _p ? _p->value : nullptr; }

    [[nodiscard]]
    size_t size() const { return _p ? _p->length : 0; }

    [[nodiscard]]
    bool empty() const { return size() == 0; }

    void swap(xstring& rhs) noexcept { xstring_value* tmp = _p; _p = rhs._p; rhs._p = tmp; }

    [[nodiscard]]
    bool equal(const xstring& rhs) const { return (_p == rhs._p); }

    xstring& printf(const char* format, ...) {
        bstring<4096> buf;
        va_list p;
        va_start(p, format);
        int vs_sz = vsnprintf(buf, sizeof(buf) - 1, format, p);
        buf[sizeof(buf) - 1] = 0;
        va_end(p);
        if (vs_sz) {
            _set(buf);
        }
        return (xstring&)*this;
    }
};

template<>
struct std::hash<xstring>
{
    [[nodiscard]] size_t operator()(const xstring& str) const noexcept {
        const auto str_val = str._get();
        return std::hash<pcstr>{}(str_val ? str_val->value : nullptr);
    }
};

inline bool operator==(xstring const& a, xstring const& b) { return a._get() == b._get(); }
inline bool operator!=(xstring const& a, xstring const& b) { return a._get() != b._get(); }
inline bool operator<(xstring const& a, xstring const& b) { return a._get() < b._get(); }
inline bool operator>(xstring const& a, xstring const& b) { return a._get() > b._get(); }
inline void swap(xstring& lhs, xstring& rhs) noexcept { lhs.swap(rhs); }
