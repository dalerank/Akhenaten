#pragma once

#include <cstdint>

#include "xstring.h"
#include "core/vec2i.h"

template <uint32_t size = 16>
class variant_t {
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
        etype_size,
    };

    inline variant_t() { _value_type = etype_none; }
    inline ~variant_t() { release(); }
           
    inline variant_t(const variant_t &v) { _value_type = etype_none; this->operator=(v); }

    inline explicit variant_t(const bool v) { _value_type = etype_none; assign(v, etype_bool); }
    inline explicit variant_t(int8_t v) { _value_type = etype_none; assign(int32_t(v), etype_int32); }
    inline explicit variant_t(int16_t v) { _value_type = etype_none; assign(int32_t(v), etype_int32); }
    inline explicit variant_t(int32_t v) { _value_type = etype_none; assign(v, etype_int32); }
    inline explicit variant_t(uint8_t v) { _value_type = etype_none; assign(uint32_t(v), etype_uint32); }
    inline explicit variant_t(uint16_t v) { _value_type = etype_none; assign(v, etype_u16); }
    inline explicit variant_t(uint32_t v) { _value_type = etype_none; assign(v, etype_uint32); }
    inline explicit variant_t(uint64_t v) { _value_type = etype_none; assign(v, etype_uint64); }
    inline explicit variant_t(float v) { _value_type = etype_none; assign(v, etype_float); }
    inline explicit variant_t(void *v) { _value_type = etype_none; assign(v, etype_ptr); }
    inline explicit variant_t(const xstring &v) { _value_type = etype_none; assign(v, etype_str); }
    inline explicit variant_t(pcstr v) { _value_type = etype_none; assign(xstring(v), etype_str); }
    inline explicit variant_t(vec2i v) { _value_type = etype_none; assign(v, etype_vec2i); }

    inline variant_t &operator=(const variant_t &v) {
        if (this == &v) {
            return (*this);
        }

        uint8_t value_type = v._value_type;
        release();
        acquire(value_type);

        switch (value_type) {
        case (etype_str): *cast<xstring>() = *v.cast<xstring>(); break;
        case (etype_vec2i): *cast<vec2i>() = *v.cast<vec2i>(); break;
        default:
            if (&_value != &v._value) {
                memcpy(&_value, &v._value, sizeof(_value));
            }
        }

        return (*this);
    }

    inline bool operator==(const variant_t &v) const {
        if (_value_type != v._value_type) {
            return (false);
        }
        if (etype_none == _value_type) {
            return (true);
        }

        switch (_value_type) {
        case (etype_str): return (*cast<xstring>() == *v.cast<xstring>());
        case (etype_bool): return (_value.bool_value == v._value.bool_value);
        case (etype_int32):
        case (etype_uint32):
            return (_value.uint32_value == v._value.uint32_value);
        case (etype_uint64):
            return (_value.uint64_value == v._value.uint64_value);
        case (etype_float): return (fp_similar(_value.float_value, v._value.float_value));
        case (etype_u16): return (_value.u16_value == v._value.u16_value);
        case (etype_vec2i): return (*cast<vec2i>() == *v.cast<vec2i>());

        default:
            return (!memcmp(&_value, &v._value, sizeof(_value)));
        }
    }

    inline variant_t &operator=(bool v) { return assign(v, etype_bool); }
    inline variant_t &operator=(uint16_t v) { return assign(v, etype_u16); }
    inline variant_t &operator=(int32_t v) { return assign(v, etype_int32); }
    inline variant_t &operator=(uint32_t v) { return assign(v, etype_uint32); }
    inline variant_t &operator=(uint64_t v) { return assign(v, etype_uint64); }
    inline variant_t &operator=(float v) { return assign(v, etype_float); }
    inline variant_t &operator=(void *v) { return assign(v, etype_ptr); }
    inline variant_t &operator=(const xstring &v) { return assign(v, etype_str); }
    inline variant_t &operator=(vec2i v) { return assign(v, etype_vec2i); }

    inline bool is_empty() const { return (etype_none == _value_type); }
    inline bool is_null() const {
        switch (_value_type) {
        case etype_none: return (true);
        case etype_str: return (!as_str());
        case etype_int32:
        case etype_uint32:
            return (!_value.int32_value);
        case etype_uint64:
            return (!_value.uint64_value);
        default:
            return (!_value.ptr_value);
        }
    };

    inline bool is_bool() const { return (etype_bool == _value_type); }
    inline bool is_u16() const { return (etype_u16 == _value_type); }
    inline bool is_int32() const { return (etype_int32 == _value_type); }
    inline bool is_uint32() const { return (etype_uint32 == _value_type); }
    inline bool is_uint64() const { return (etype_uint64 == _value_type); }
    inline bool is_float() const { return (etype_float == _value_type); }
    inline bool is_ptr() const { return (etype_ptr == _value_type); }
    inline bool is_str() const { return (etype_str == _value_type); }
    inline bool is_vec2i() const { return (etype_vec2i == _value_type); }
    
    inline bool	as_bool() const { verify_no_crash(etype_bool == _value_type); return _value.bool_value; }
    inline uint16_t as_u16() const { verify_no_crash(this->is_u16()); return _value.u16_value; }
    inline int32_t as_int32() const { verify_no_crash(etype_int32 == _value_type); return _value.int32_value; }
    inline uint32_t as_uint32() const { verify_no_crash(etype_uint32 == _value_type); return _value.uint32_value; }
    inline uint64_t as_uint64() const { verify_no_crash(etype_uint64 == _value_type); return _value.uint64_value; }
    inline float as_float() const { verify_no_crash(etype_float == _value_type); return _value.float_value; }
    inline void *as_ptr() const { verify_no_crash(etype_ptr == _value_type); return _value.ptr_value; }
    inline const xstring &as_str() const { verify_no_crash(etype_str == _value_type); return *cast<xstring>(); }
    inline const vec2i &as_vec2i() const { verify_no_crash(etype_vec2i == _value_type); return *cast<vec2i>(); }

    inline variant_t &as_bool(bool v) { return assign(v, etype_bool); }
    inline variant_t &as_u16(uint16_t v) { assign(v, etype_u16); return *this; }
    inline variant_t &as_int32(int32_t v) { return assign(v, etype_int32); }
    inline variant_t &as_uint32(uint32_t v) { return assign(v, etype_uint32); }
    inline variant_t &as_uint64(uint64_t v) { return assign(v, etype_uint64); }
    inline variant_t &as_float(float v) { return assign(v, etype_float); }
    inline variant_t &as_ptr(void *v) { return assign(v, etype_ptr); }
    inline variant_t &as_str(const xstring &v) { return assign(v, etype_str); }
    inline variant_t &as_vec2i(vec2i v) { return assign(v, etype_vec2i); }

    inline bool bool_or_def(const bool def) const { return is_bool() ? as_bool() : def; }
    inline int32_t int32_or_def(const int32_t def) const { return is_int32() ? as_int32() : def; }
    inline uint32_t uint32_or_def(const uint32_t def) const { return is_uint32() ? as_uint32() : def; }
    inline uint64_t uint64_or_def(const uint64_t def) const { return is_uint64() ? as_uint64() : def; }
    inline float float_or_def(const float def) const { return is_float() ? as_float() : def; }
    inline const xstring &str_or_def(const xstring &def)	const { return is_str() ? as_str() : def; }
    inline vec2i vec2i_or_def(const vec2i &def) const { return is_vec2i() ? as_vec2i() : def; }
    inline uint8_t value_type() const { return _value_type; }

    using pvoid = void *;
    inline void acquire(const uint8_t type) {
        verify_no_crash(etype_none == _value_type);
        _value_type = type;

        switch (_value_type) {
        case (etype_bool): new (cast<bool>()) bool(); break;
        case (etype_u16): new (cast<uint16_t>()) uint16_t(); break;
        case (etype_int32): new (cast<int32_t>()) int32_t(); break;
        case (etype_uint32): new (cast<uint32_t>()) uint32_t(); break;
        case (etype_uint64): new (cast<uint64_t>()) uint64_t(); break;
        case (etype_float): new (cast<float>()) float(); break;
        case (etype_ptr): new (cast<pvoid>()) pvoid(); break;
        case (etype_str): new (cast<xstring>()) xstring(); break;
        case (etype_vec2i): new (cast<vec2i>()) vec2i(); break;
        }
    }

    inline void	release() {
        switch (_value_type) {
        case (etype_str): cast<xstring>()->~xstring(); break;
        case (etype_vec2i): cast<vec2i>()->~vec2i(); break;
        };

        _value_type = etype_none;
    };

    inline bstring1024 debug_str() const {
        bstring1024 result;

        switch (_value_type) {
        case (etype_none): result = "none"; break;
        case (etype_bool): result.printf("bool[%s]", _value.bool_value ? "TRUE" : "FALSE"); break;
        case (etype_u16): result.printf("u16[%d]", uint32_t(_value.u16_value)); break;
        case (etype_int32): result.printf("int32[%d]", _value.int32_value); break;
        case (etype_uint32): result.printf("uint32[%d]", uint32_t(_value.uint32_value)); break;
        case (etype_uint64): result.printf("uint64[%llu]", (unsigned long long)_value.uint64_value); break;
        case (etype_float): result.printf("float[%f]", _value.float_value); break;
        case (etype_ptr): result.printf("ptr[%p]", _value.ptr_value); break;
        case (etype_str): result.printf("str[%s]", as_str().c_str()); break;
        case (etype_vec2i): {
            const vec2i &v = as_vec2i();
            result.printf("vec2i[%d,%d]", v.x, v.y);
            break;
        }
        default:
            verify_no_crash(false);
        };

        return result;
    }

    inline bstring1024 to_str() const {
        bstring1024 result;

        switch (_value_type) {
        case (etype_none): result = "none"; break;
        case (etype_bool): result.printf("%s", _value.bool_value ? "true" : "false"); break;
        case (etype_u16): result.printf("%d", uint32_t(_value.u16_value)); break;
        case (etype_int32): result.printf("%d", _value.int32_value); break;
        case (etype_uint32): result.printf("%u", _value.uint32_value); break;
        case (etype_uint64): result.printf("%llu", (unsigned long long)_value.uint64_value); break;
        case (etype_float): result.printf("%f", _value.float_value); break;
        case (etype_ptr): result.printf("%p", _value.ptr_value); break;
        case (etype_str): result.printf("%s", as_str().c_str()); break;
        case (etype_vec2i): {
            const vec2i &v = as_vec2i();
            result.printf("%d,%d", v.x, v.y);
            break;
        }
        default:
            verify_no_crash(false);
        };

        return result;
    }

protected:
    union {
        bool bool_value;
        uint16_t u16_value;
        int32_t int32_value;
        uint32_t uint32_value;
        uint64_t uint64_value;
        float float_value;
        void *ptr_value;
    } _value;

    uint8_t _value_type;

    template <typename T>
    inline variant_t &assign(const T &v, uint8_t type) { release(); acquire(type); *cast<T>() = v; return *this; }

    template <typename T>
    inline T *cast() const { return (T *)(&_value); }
};

using bvariant = variant_t<8>;

struct bvariant_map {
    using ValuesT = std::unordered_map<xstring, bvariant>;

    const bvariant& def() const {
        static bvariant dummy;
        return dummy;
    }

    const bvariant& value(const xstring &name) const {
        auto it = values.find(name);
        return (it != values.end()) ? it->second : def();
    }

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

    inline uint8_t value_type(const xstring &name) const { 
        return value(name).value_type();
    }

    const bvariant& operator[](const xstring& name) const {
        auto it = values.find(name);
        return (it != values.end()) ? it->second : def();
    }

    bvariant &operator[](const xstring &name) {
        return values[name];
    }

    ValuesT::iterator find(const xstring &name) { return values.find(name); }
    ValuesT::const_iterator find(const xstring &name) const { return values.find(name); }

    ValuesT::iterator begin() { return values.begin(); }
    ValuesT::const_iterator begin() const { return values.begin(); }
    ValuesT::const_iterator cbegin() const { return values.cbegin(); }

    ValuesT::iterator end() { return values.end(); }
    ValuesT::const_iterator end() const { return values.end(); }
    ValuesT::const_iterator cend() const { return values.cend(); }

    ValuesT values;
};