#pragma once

#include <cstdint>
#include <cmath>
#include <memory>
#include <utility>
#include <algorithm>
#include <variant>

#include "xstring.h"
#include "core/vec2i.h"
#include "grid/grid_area.h"
#include "grid/point.h"
#include "core/hvector.h"

class bvariant {
public:
    enum {
        etype_none = 0,

        etype_bool,
        etype_int32,
        etype_uint32,
        etype_uint64,
        etype_float,
        etype_ptr,
        etype_str,
        etype_u16,
        etype_vec2i,
        etype_tile2i,
        etype_grid_area,
        etype_size,
    };

    inline bvariant() : _value(std::monostate{}) {}
    inline ~bvariant() = default;

    inline bvariant(const bvariant &v) : _value(v._value) {}

    inline explicit bvariant(const bool v) : _value(v) {}
    inline explicit bvariant(int8_t v) : _value(int32_t(v)) {}
    inline explicit bvariant(int16_t v) : _value(int32_t(v)) {}
    inline explicit bvariant(int32_t v) : _value(v) {}
    inline explicit bvariant(uint8_t v) : _value(uint32_t(v)) {}
    inline explicit bvariant(uint16_t v) : _value(v) {}
    inline explicit bvariant(uint32_t v) : _value(v) {}
    inline explicit bvariant(uint64_t v) : _value(v) {}
#if defined(__APPLE__) // temporary constructor for macOS to fix ambiguous conversion (remove later)
    inline explicit bvariant(size_t v) : _value(v) {}
#endif
    inline explicit bvariant(float v) : _value(v) {}
    inline explicit bvariant(void *v) : _value(v) {}
    inline explicit bvariant(const xstring &v) : _value(v) {}
    inline explicit bvariant(pcstr v) : _value(xstring(v)) {}
    inline explicit bvariant(vec2i v) : _value(v) {}
    inline explicit bvariant(tile2i v) : _value(v) {}
    inline explicit bvariant(grid_area v) : _value(v) {}

    inline bvariant &operator=(const bvariant &v) {
        if (this != &v) {
            _value = v._value;
        }
        return *this;
    }

    inline bool operator==(const bvariant &v) const {
        if (_value.index() != v._value.index()) {
            return false;
        }
        if (std::holds_alternative<std::monostate>(_value)) {
            return true;
        }
        switch (_value.index()) {
        case etype_str: return (std::get<xstring>(_value) == std::get<xstring>(v._value));
        case etype_bool: return (std::get<bool>(_value) == std::get<bool>(v._value));
        case etype_int32: return (std::get<int32_t>(_value) == std::get<int32_t>(v._value));
        case etype_uint32: return (std::get<uint32_t>(_value) == std::get<uint32_t>(v._value));
        case etype_uint64: return (std::get<uint64_t>(_value) == std::get<uint64_t>(v._value));
        case etype_float: return (std::fabs(std::get<float>(_value) - std::get<float>(v._value)) < 1e-6f);
        case etype_u16: return (std::get<uint16_t>(_value) == std::get<uint16_t>(v._value));
        case etype_vec2i: return (std::get<vec2i>(_value) == std::get<vec2i>(v._value));
        case etype_tile2i: return (std::get<tile2i>(_value) == std::get<tile2i>(v._value));
        case etype_grid_area: {
            const grid_area &a = std::get<grid_area>(_value), &b = std::get<grid_area>(v._value);
            return (a.tmin_x == b.tmin_x && a.tmin_y == b.tmin_y && a.tmax_x == b.tmax_x && a.tmax_y == b.tmax_y);
        }
        case etype_ptr: return (std::get<void*>(_value) == std::get<void*>(v._value));
        default: return true;
        }
    }

    inline bvariant &operator=(bool v) { return assign(v, etype_bool); }
    inline bvariant &operator=(uint16_t v) { return assign(v, etype_u16); }
    inline bvariant &operator=(int32_t v) { return assign(v, etype_int32); }
    inline bvariant &operator=(uint32_t v) { return assign(v, etype_uint32); }
    inline bvariant &operator=(uint64_t v) { return assign(v, etype_uint64); }
    inline bvariant &operator=(float v) { return assign(v, etype_float); }
    inline bvariant &operator=(void *v) { return assign(v, etype_ptr); }
    inline bvariant &operator=(const xstring &v) { return assign(v, etype_str); }
    inline bvariant &operator=(vec2i v) { return assign(v, etype_vec2i); }
    inline bvariant &operator=(tile2i v) { return assign(v, etype_tile2i); }
    inline bvariant &operator=(grid_area v) { return assign(v, etype_grid_area); }

    inline uint8_t value_type() const { return (uint8_t)_value.index(); }

    inline bool is_empty() const { return std::holds_alternative<std::monostate>(_value); }
    inline bool is_null() const {
        switch (_value.index()) {
        case etype_none: return true;
        case etype_str: return as_str().empty();
        case etype_int32: return (std::get<int32_t>(_value) == 0);
        case etype_uint32: return (std::get<uint32_t>(_value) == 0);
        case etype_uint64: return (std::get<uint64_t>(_value) == 0);
        case etype_ptr: return (std::get<void*>(_value) == nullptr);
        default: return false;
        }
    }

    inline bool is_bool() const { return std::holds_alternative<bool>(_value); }
    inline bool is_u16() const { return std::holds_alternative<uint16_t>(_value); }
    inline bool is_int32() const { return std::holds_alternative<int32_t>(_value); }
    inline bool is_uint32() const { return std::holds_alternative<uint32_t>(_value); }
    inline bool is_uint64() const { return std::holds_alternative<uint64_t>(_value); }
    inline bool is_float() const { return std::holds_alternative<float>(_value); }
    inline bool is_ptr() const { return std::holds_alternative<void*>(_value); }
    inline bool is_str() const { return std::holds_alternative<xstring>(_value); }
    inline bool is_vec2i() const { return std::holds_alternative<vec2i>(_value); }
    inline bool is_tile2i() const { return std::holds_alternative<tile2i>(_value); }
    inline bool is_grid_area() const { return std::holds_alternative<grid_area>(_value); }

    inline bool as_bool() const { verify_no_crash(is_bool()); return std::get<bool>(_value); }
    inline uint16_t as_u16() const { verify_no_crash(is_u16()); return std::get<uint16_t>(_value); }
    inline int32_t as_int32() const { verify_no_crash(is_int32()); return std::get<int32_t>(_value); }
    inline uint32_t as_uint32() const { verify_no_crash(is_uint32()); return std::get<uint32_t>(_value); }
    inline uint64_t as_uint64() const { verify_no_crash(is_uint64()); return std::get<uint64_t>(_value); }
    inline float as_float() const { verify_no_crash(is_float()); return std::get<float>(_value); }
    inline void *as_ptr() const { verify_no_crash(is_ptr()); return std::get<void*>(_value); }
    inline const xstring &as_str() const { verify_no_crash(is_str()); return std::get<xstring>(_value); }
    inline const vec2i &as_vec2i() const { verify_no_crash(is_vec2i()); return std::get<vec2i>(_value); }
    inline const tile2i &as_tile2i() const { verify_no_crash(is_tile2i()); return std::get<tile2i>(_value); }
    inline const grid_area &as_grid_area() const { verify_no_crash(is_grid_area()); return std::get<grid_area>(_value); }

    inline bvariant &as_bool(bool v) { return assign(v, etype_bool); }
    inline bvariant &as_u16(uint16_t v) { assign(v, etype_u16); return *this; }
    inline bvariant &as_int32(int32_t v) { return assign(v, etype_int32); }
    inline bvariant &as_uint32(uint32_t v) { return assign(v, etype_uint32); }
    inline bvariant &as_uint64(uint64_t v) { return assign(v, etype_uint64); }
    inline bvariant &as_float(float v) { return assign(v, etype_float); }
    inline bvariant &as_ptr(void *v) { return assign(v, etype_ptr); }
    inline bvariant &as_str(const xstring &v) { return assign(v, etype_str); }
    inline bvariant &as_vec2i(vec2i v) { return assign(v, etype_vec2i); }
    inline bvariant &as_tile2i(tile2i v) { return assign(v, etype_tile2i); }
    inline bvariant &as_grid_area(grid_area v) { return assign(v, etype_grid_area); }

    inline bool bool_or_def(const bool def) const { return is_bool() ? as_bool() : def; }
    inline int32_t int32_or_def(const int32_t def) const { return is_int32() ? as_int32() : def; }
    inline uint32_t uint32_or_def(const uint32_t def) const { return is_uint32() ? as_uint32() : def; }
    inline uint64_t uint64_or_def(const uint64_t def) const { return is_uint64() ? as_uint64() : def; }
    inline float float_or_def(const float def) const { return is_float() ? as_float() : def; }
    inline const xstring &str_or_def(const xstring &def)	const { return is_str() ? as_str() : def; }
    inline vec2i vec2i_or_def(const vec2i &def) const { return is_vec2i() ? as_vec2i() : def; }
    inline tile2i tile2i_or_def(const tile2i &def) const { return is_tile2i() ? as_tile2i() : def; }
    inline grid_area grid_area_or_def(const grid_area &def) const { return is_grid_area() ? as_grid_area() : def; }

    inline void acquire(uint8_t type) {
        verify_no_crash(is_empty());
        switch (type) {
        case etype_bool: _value = bool(); break;
        case etype_int32: _value = int32_t(); break;
        case etype_uint32: _value = uint32_t(); break;
        case etype_uint64: _value = uint64_t(); break;
        case etype_float: _value = float(); break;
        case etype_ptr: _value = (void*)nullptr; break;
        case etype_str: _value = xstring(); break;
        case etype_u16: _value = uint16_t(); break;
        case etype_vec2i: _value = vec2i(); break;
        case etype_tile2i: _value = tile2i(); break;
        case etype_grid_area: _value = grid_area(); break;
        default: verify_no_crash(false);
        }
    }

    inline void release() {
        _value = std::monostate{};
    }

    inline bstring1024 debug_str() const {
        bstring1024 result;
        switch (_value.index()) {
        case etype_none: result = "none"; break;
        case etype_bool: result.printf("bool[%s]", std::get<bool>(_value) ? "TRUE" : "FALSE"); break;
        case etype_u16: result.printf("u16[%d]", uint32_t(std::get<uint16_t>(_value))); break;
        case etype_int32: result.printf("int32[%d]", std::get<int32_t>(_value)); break;
        case etype_uint32: result.printf("uint32[%d]", uint32_t(std::get<uint32_t>(_value))); break;
        case etype_uint64: result.printf("uint64[%llu]", (unsigned long long)std::get<uint64_t>(_value)); break;
        case etype_float: result.printf("float[%f]", std::get<float>(_value)); break;
        case etype_ptr: result.printf("ptr[%p]", std::get<void*>(_value)); break;
        case etype_str: result.printf("str[%s]", std::get<xstring>(_value).c_str()); break;
        case etype_vec2i: { const vec2i &v = std::get<vec2i>(_value); result.printf("vec2i[%d,%d]", v.x, v.y); break; }
        case etype_tile2i: { const tile2i &v = std::get<tile2i>(_value); result.printf("tile2i[%d,%d]", v.x(), v.y()); break; }
        case etype_grid_area: {
            const grid_area &a = std::get<grid_area>(_value);
            result.printf("grid_area[%d,%d,%d,%d]", a.tmin_x, a.tmin_y, a.tmax_x, a.tmax_y);
            break;
        }
        default: verify_no_crash(false);
        }
        return result;
    }

    inline bstring1024 to_str() const {
        bstring1024 result;
        switch (_value.index()) {
        case etype_none: result = "none"; break;
        case etype_bool: result.printf("%s", std::get<bool>(_value) ? "true" : "false"); break;
        case etype_u16: result.printf("%d", uint32_t(std::get<uint16_t>(_value))); break;
        case etype_int32: result.printf("%d", std::get<int32_t>(_value)); break;
        case etype_uint32: result.printf("%u", std::get<uint32_t>(_value)); break;
        case etype_uint64: result.printf("%llu", (unsigned long long)std::get<uint64_t>(_value)); break;
        case etype_float: result.printf("%f", std::get<float>(_value)); break;
        case etype_ptr: result.printf("%p", std::get<void*>(_value)); break;
        case etype_str: result.printf("%s", std::get<xstring>(_value).c_str()); break;
        case etype_vec2i: { const vec2i &v = std::get<vec2i>(_value); result.printf("%d,%d", v.x, v.y); break; }
        case etype_tile2i: { const tile2i &v = std::get<tile2i>(_value); result.printf("%d,%d", v.x(), v.y()); break; }
        case etype_grid_area: {
            const grid_area &a = std::get<grid_area>(_value);
            result.printf("%d,%d,%d,%d", a.tmin_x, a.tmin_y, a.tmax_x, a.tmax_y);
            break;
        }
        default: verify_no_crash(false);
        }
        return result;
    }

protected:
    // Order must match etype_ enum: none, bool, int32, uint32, uint64, float, ptr, str, u16, vec2i, tile2i, grid_area
    using value_variant = std::variant<std::monostate, bool, int32_t, uint32_t, uint64_t, float, void*, xstring, uint16_t, vec2i, tile2i, grid_area>;
    value_variant _value;

    template <typename T>
    inline bvariant &assign(const T &v, uint8_t) { _value = v; return *this; }
};

struct bvariant_map {
    using PairT = std::pair<xstring, bvariant>;
    using ValuesT = hvector<PairT, 32>;

    const bvariant& def() const {
        static bvariant dummy;
        return dummy;
    }

    const bvariant& value(const xstring &name) const {
        auto it = find(name);
        return (it != values.end()) ? it->second : def();
    }

    static bvariant_map* acquire_from_pool();
    static void return_to_pool(bvariant_map *);

    struct scoped {
        scoped() : _ptr(bvariant_map::acquire_from_pool()) {}
        ~scoped() { bvariant_map::return_to_pool(_ptr); }

        scoped(const scoped &) = delete;
        scoped &operator=(const scoped &) = delete;

        bvariant_map &operator*() { return *_ptr; }
        bvariant_map *operator->() { return _ptr; }

    private:
        bvariant_map *_ptr;
    };

    inline float n(const xstring &name) const {
        const auto &v = value(name);
        switch (v.value_type()) {
        case bvariant::etype_bool: return (v.as_bool() ? 1.f : 0.f);
        case bvariant::etype_u16: return v.as_u16();
        case bvariant::etype_int32: return v.as_int32();
        case bvariant::etype_uint32: return v.as_uint32();
        case bvariant::etype_uint64: return v.as_uint64();
        case bvariant::etype_float: return v.as_float();
        }

        return 0.f;
    }

    inline bool bool_or_def(const xstring &name, const bool def) const { 
        const auto &v = value(name);
        return v.is_bool() ? v.as_bool() : def; 
    }

    inline int32_t int32_or_def(const xstring &name, const int32_t def) const {
        const auto &v = value(name);
        return v.is_int32() ? v.as_int32() : def; 
    }
    inline int32_t i32(const xstring &name, const int32_t def = 0) const {
        return int32_or_def(name, def);
    }

    inline uint32_t uint32_or_def(const xstring &name, const uint32_t def) const { 
        const auto &v = value(name);
        return v.is_uint32() ? v.as_uint32() : def; 
    }

    inline uint32_t u32(const xstring &name, const uint32_t def = 0) const {
        return uint32_or_def(name, def);
    }

    inline uint64_t uint64_or_def(const xstring &name, const uint64_t def) const { 
        const auto &v = value(name);
        return v.is_uint64() ? v.as_uint64() : def;
    }

    inline uint64_t u64(const xstring &name, const uint64_t def = 0) const {
        return uint64_or_def(name, def);
    }

    inline float float_or_def(const xstring& name, const float def) const { 
        const auto &v = value(name);
        return v.is_float() ? v.as_float() : def; 
    }

    inline float f(const xstring &name, const float def = 0.0f) const {
        return float_or_def(name, def);
    }

    inline const xstring &str_or_def(const xstring &name, const xstring &def) const {
        const auto &v = value(name);
        return v.is_str() ? v.as_str() : def; 
    }

    inline const xstring &s(const xstring &name, const xstring &def = xstring()) const {
        return str_or_def(name, def);
    }

    inline vec2i vec2i_or_def(const xstring &name, const vec2i &def) const { 
        const auto &v = value(name);
        return v.is_vec2i() ? v.as_vec2i() : def; 
    }

    inline tile2i tile2i_or_def(const xstring &name, const tile2i &def) const {
        const auto &v = value(name);
        return v.is_tile2i() ? v.as_tile2i() : def;
    }

    inline uint8_t value_type(const xstring &name) const { 
        return value(name).value_type();
    }

    const bvariant& operator[](const xstring& name) const {
        auto it = find(name);
        return (it != values.end()) ? it->second : def();
    }

    bvariant &operator[](const xstring &name) {
        auto it = find(name);
        if (it != values.end()) {
            return it->second;
        }
        // Создаем новый элемент
        values.emplace_back(name, bvariant());
        return values.back().second;
    }

    ValuesT::iterator find(const xstring &name) {
        return std::find_if(values.begin(), values.end(), 
            [&name](const PairT &p) { return p.first == name; });
    }
    
    ValuesT::const_iterator find(const xstring &name) const {
        return std::find_if(values.begin(), values.end(), 
            [&name](const PairT &p) { return p.first == name; });
    }

    ValuesT::iterator begin() { return values.begin(); }
    ValuesT::const_iterator begin() const { return values.begin(); }
    ValuesT::const_iterator cbegin() const { return values.cbegin(); }

    ValuesT::iterator end() { return values.end(); }
    ValuesT::const_iterator end() const { return values.end(); }
    ValuesT::const_iterator cend() const { return values.cend(); }

    ValuesT values;
};