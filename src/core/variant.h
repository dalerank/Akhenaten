#pragma once

#include <cstdint>
#include <utility>
#include <variant>
#include <initializer_list>

#include "xstring.h"
#include "core/vec2i.h"
#include "grid/grid_area.h"
#include "grid/point.h"
#include "core/hvector.h"
#include "core/cstring.h"

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

    bvariant();
    ~bvariant() = default;

    bvariant(const bvariant& v);

    explicit bvariant(const bool v);
    explicit bvariant(int8_t v);
    explicit bvariant(int16_t v);
    explicit bvariant(int32_t v);
    explicit bvariant(uint8_t v);
    explicit bvariant(uint16_t v);
    explicit bvariant(uint32_t v);
    explicit bvariant(uint64_t v);
#if defined(__APPLE__) // temporary constructor for macOS to fix ambiguous conversion (remove later)
    explicit bvariant(size_t v);
#endif
    explicit bvariant(float v);
    explicit bvariant(void* v);
    explicit bvariant(const xstring& v);
    explicit bvariant(const cstring& v);
    explicit bvariant(pcstr v);
    explicit bvariant(vec2i v);
    explicit bvariant(tile2i v);
    explicit bvariant(grid_area v);

    bvariant& operator=(const bvariant& v);

    bool operator==(const bvariant& v) const;

    bvariant& operator=(bool v);
    bvariant& operator=(uint16_t v);
    bvariant& operator=(int32_t v);
    bvariant& operator=(uint32_t v);
    bvariant& operator=(uint64_t v);
    bvariant& operator=(float v);
    bvariant& operator=(void* v);
    bvariant& operator=(const xstring& v);
    bvariant& operator=(vec2i v);
    bvariant& operator=(tile2i v);
    bvariant& operator=(grid_area v);

    inline uint8_t value_type() const { return (uint8_t)_value.index(); }

    inline bool is_empty() const { return _value.index() == etype_none; }
    bool is_null() const;

    inline bool is_bool() const { return _value.index() == etype_bool; }
    inline bool is_u16() const { return _value.index() == etype_u16; }
    inline bool is_int32() const { return _value.index() == etype_int32; }
    inline bool is_uint32() const { return _value.index() == etype_uint32; }
    inline bool is_uint64() const { return _value.index() == etype_uint64; }
    inline bool is_float() const { return _value.index() == etype_float; }
    inline bool is_ptr() const { return _value.index() == etype_ptr; }
    inline bool is_str() const { return _value.index() == etype_str; }
    inline bool is_vec2i() const { return _value.index() == etype_vec2i; }
    inline bool is_tile2i() const { return _value.index() == etype_tile2i; }
    inline bool is_grid_area() const { return _value.index() == etype_grid_area; }

    bool as_bool() const;
    uint16_t as_u16() const;
    int32_t as_int32() const;
    uint32_t as_uint32() const;
    uint64_t as_uint64() const;
    float as_float() const;
    void* as_ptr() const;
    const xstring& as_str() const;
    const vec2i& as_vec2i() const;
    const tile2i& as_tile2i() const;
    const grid_area& as_grid_area() const;

    bvariant& as_bool(bool v);
    bvariant& as_u16(uint16_t v);
    bvariant& as_int32(int32_t v);
    bvariant& as_uint32(uint32_t v);
    bvariant& as_uint64(uint64_t v);
    bvariant& as_float(float v);
    bvariant& as_ptr(void* v);
    bvariant& as_str(const xstring& v);
    bvariant& as_vec2i(vec2i v);
    bvariant& as_tile2i(tile2i v);
    bvariant& as_grid_area(grid_area v);

    inline bool bool_or_def(const bool def) const { return is_bool() ? as_bool() : def; }
    inline int32_t int32_or_def(const int32_t def) const { return is_int32() ? as_int32() : def; }
    inline uint32_t uint32_or_def(const uint32_t def) const { return is_uint32() ? as_uint32() : def; }
    inline uint64_t uint64_or_def(const uint64_t def) const { return is_uint64() ? as_uint64() : def; }
    inline float float_or_def(const float def) const { return is_float() ? as_float() : def; }
    inline const xstring& str_or_def(const xstring& def) const { return is_str() ? as_str() : def; }
    inline vec2i vec2i_or_def(const vec2i &def) const { return is_vec2i() ? as_vec2i() : def; }
    inline tile2i tile2i_or_def(const tile2i &def) const { return is_tile2i() ? as_tile2i() : def; }
    inline grid_area grid_area_or_def(const grid_area &def) const { return is_grid_area() ? as_grid_area() : def; }

    void acquire(uint8_t type);
    void release();

    bstring1024 debug_str() const;
    bstring1024 to_str() const;
    bool to_bool() const;

protected:
    // Order must match etype_ enum: none, bool, int32, uint32, uint64, float, ptr, str, u16, vec2i, tile2i, grid_area
    using value_variant = std::variant<std::monostate, bool, int32_t, uint32_t, uint64_t, float, void*, xstring, uint16_t, vec2i, tile2i, grid_area>;
    value_variant _value;
};

/// Helper for bvariant_map initializer list: values convert implicitly to bvariant.
struct bvariant_map_val {
    bvariant v;
    bvariant_map_val() = default;
    bvariant_map_val(pcstr s) : v(bvariant(s)) {}
    bvariant_map_val(const xstring &s) : v(bvariant(s)) {}
    bvariant_map_val(const cstring &s) : v(bvariant(s.data())) {}
    bvariant_map_val(bool b) : v(bvariant(b)) {}
    bvariant_map_val(int32_t i) : v(bvariant(i)) {}
    bvariant_map_val(uint32_t u) : v(bvariant(u)) {}
    bvariant_map_val(uint64_t u) : v(bvariant(u)) {}
    bvariant_map_val(float f) : v(bvariant(f)) {}
    bvariant_map_val(vec2i p) : v(bvariant(p)) {}
    bvariant_map_val(tile2i t) : v(bvariant(t)) {}
    bvariant_map_val(grid_area a) : v(bvariant(a)) {}
};

struct bvariant_map {
    using PairT = std::pair<xstring, bvariant>;
    using ValuesT = hvector<PairT, 64>;

    bvariant_map();
    ~bvariant_map();
    bvariant_map(const bvariant_map& o);
    bvariant_map(bvariant_map&& o);
    bvariant_map& operator=(const bvariant_map& o);
    bvariant_map& operator=(bvariant_map&& o);

    bvariant_map(std::initializer_list<std::pair<xstring, bvariant_map_val>> init);

    const bvariant& def() const;
    const bvariant& value(const xstring& name) const;

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

    float n(const xstring& name) const;

    bool bool_or_def(const xstring& name, const bool def) const;
    int32_t int32_or_def(const xstring& name, const int32_t def) const;
    inline int32_t i32(const xstring& name, const int32_t def = 0) const { return int32_or_def(name, def); }

    uint32_t uint32_or_def(const xstring& name, const uint32_t def) const;
    inline uint32_t u32(const xstring& name, const uint32_t def = 0) const { return uint32_or_def(name, def); }

    uint64_t uint64_or_def(const xstring& name, const uint64_t def) const;
    inline uint64_t u64(const xstring& name, const uint64_t def = 0) const { return uint64_or_def(name, def); }

    float float_or_def(const xstring& name, const float def) const;
    inline float f(const xstring& name, const float def = 0.0f) const { return float_or_def(name, def); }

    const xstring& str_or_def(const xstring& name, const xstring& def) const;
    inline const xstring& s(const xstring& name, const xstring& def = xstring()) const { return str_or_def(name, def); }

    vec2i vec2i_or_def(const xstring& name, const vec2i& def) const;
    tile2i tile2i_or_def(const xstring& name, const tile2i& def) const;

    inline uint8_t value_type(const xstring& name) const { return value(name).value_type(); }

    const bvariant& operator[](const xstring& name) const;
    bvariant& operator[](const xstring& name);

    ValuesT::iterator find(const xstring& name);
    ValuesT::const_iterator find(const xstring& name) const;

    ValuesT::iterator begin() { return values.begin(); }
    ValuesT::const_iterator begin() const { return values.begin(); }
    ValuesT::const_iterator cbegin() const { return values.cbegin(); }

    ValuesT::iterator end() { return values.end(); }
    ValuesT::const_iterator end() const { return values.end(); }
    ValuesT::const_iterator cend() const { return values.cend(); }

    ValuesT values;
};
