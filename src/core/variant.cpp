#include "core/variant.h"

#include "game/game_pool.h"

#include <algorithm>
#include <cmath>

game_permanent_memory_pool<bvariant_map, 16> g_bvariant_map_pool;

bvariant::bvariant() : _value(std::monostate{}) {
}

bvariant::bvariant(const bvariant& v) : _value(v._value) {
}

bvariant::bvariant(const bool v) : _value(v) {
}
bvariant::bvariant(int8_t v) : _value(int32_t(v)) {
}
bvariant::bvariant(int16_t v) : _value(int32_t(v)) {
}
bvariant::bvariant(int32_t v) : _value(v) {
}
bvariant::bvariant(uint8_t v) : _value(uint32_t(v)) {
}
bvariant::bvariant(uint16_t v) : _value(v) {
}
bvariant::bvariant(uint32_t v) : _value(v) {
}
bvariant::bvariant(uint64_t v) : _value(v) {
}
#if defined(__APPLE__)
bvariant::bvariant(size_t v) : _value(v) {
}
#endif
bvariant::bvariant(float v) : _value(v) {
}
bvariant::bvariant(void* v) : _value(v) {
}
bvariant::bvariant(const xstring& v) : _value(v) {
}
bvariant::bvariant(const cstring& v) : _value(v.data()) {
}
bvariant::bvariant(pcstr v) : _value(xstring(v)) {
}
bvariant::bvariant(vec2i v) : _value(v) {
}
bvariant::bvariant(tile2i v) : _value(v) {
}
bvariant::bvariant(grid_area v) : _value(v) {
}

bvariant& bvariant::operator=(const bvariant& v) {
    if (this != &v) {
        _value = v._value;
    }
    return *this;
}

bool bvariant::operator==(const bvariant& v) const {
    if (_value.index() != v._value.index()) {
        return false;
    }
    if (std::holds_alternative<std::monostate>(_value)) {
        return true;
    }
    switch (_value.index()) {
    case etype_str:
        return (std::get<xstring>(_value) == std::get<xstring>(v._value));
    case etype_bool:
        return (std::get<bool>(_value) == std::get<bool>(v._value));
    case etype_int32:
        return (std::get<int32_t>(_value) == std::get<int32_t>(v._value));
    case etype_uint32:
        return (std::get<uint32_t>(_value) == std::get<uint32_t>(v._value));
    case etype_uint64:
        return (std::get<uint64_t>(_value) == std::get<uint64_t>(v._value));
    case etype_float:
        return (std::fabs(std::get<float>(_value) - std::get<float>(v._value)) < 1e-6f);
    case etype_u16:
        return (std::get<uint16_t>(_value) == std::get<uint16_t>(v._value));
    case etype_vec2i:
        return (std::get<vec2i>(_value) == std::get<vec2i>(v._value));
    case etype_tile2i:
        return (std::get<tile2i>(_value) == std::get<tile2i>(v._value));
    case etype_grid_area: {
        const grid_area &a = std::get<grid_area>(_value), &b = std::get<grid_area>(v._value);
        return (a.tmin_x == b.tmin_x && a.tmin_y == b.tmin_y && a.tmax_x == b.tmax_x && a.tmax_y == b.tmax_y);
    }
    case etype_ptr:
        return (std::get<void*>(_value) == std::get<void*>(v._value));
    default:
        return true;
    }
}

bvariant& bvariant::operator=(bool v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(uint16_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(int32_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(uint32_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(uint64_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(float v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(void* v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(const xstring& v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(vec2i v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(tile2i v) {
    _value = v;
    return *this;
}
bvariant& bvariant::operator=(grid_area v) {
    _value = v;
    return *this;
}

bool bvariant::is_null() const {
    switch (_value.index()) {
    case etype_none:
        return true;
    case etype_str:
        return as_str().empty();
    case etype_int32:
        return (std::get<int32_t>(_value) == 0);
    case etype_uint32:
        return (std::get<uint32_t>(_value) == 0);
    case etype_uint64:
        return (std::get<uint64_t>(_value) == 0);
    case etype_ptr:
        return (std::get<void*>(_value) == nullptr);
    default:
        return false;
    }
}

bool bvariant::as_bool() const {
    verify_no_crash(is_bool());
    return std::get<bool>(_value);
}
uint16_t bvariant::as_u16() const {
    verify_no_crash(is_u16());
    return std::get<uint16_t>(_value);
}
int32_t bvariant::as_int32() const {
    verify_no_crash(is_int32());
    return std::get<int32_t>(_value);
}
uint32_t bvariant::as_uint32() const {
    verify_no_crash(is_uint32());
    return std::get<uint32_t>(_value);
}
uint64_t bvariant::as_uint64() const {
    verify_no_crash(is_uint64());
    return std::get<uint64_t>(_value);
}
float bvariant::as_float() const {
    verify_no_crash(is_float());
    return std::get<float>(_value);
}
void* bvariant::as_ptr() const {
    verify_no_crash(is_ptr());
    return std::get<void*>(_value);
}
const xstring& bvariant::as_str() const {
    verify_no_crash(is_str());
    return std::get<xstring>(_value);
}
const vec2i& bvariant::as_vec2i() const {
    verify_no_crash(is_vec2i());
    return std::get<vec2i>(_value);
}
const tile2i& bvariant::as_tile2i() const {
    verify_no_crash(is_tile2i());
    return std::get<tile2i>(_value);
}
const grid_area& bvariant::as_grid_area() const {
    verify_no_crash(is_grid_area());
    return std::get<grid_area>(_value);
}

bvariant& bvariant::as_bool(bool v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_u16(uint16_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_int32(int32_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_uint32(uint32_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_uint64(uint64_t v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_float(float v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_ptr(void* v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_str(const xstring& v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_vec2i(vec2i v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_tile2i(tile2i v) {
    _value = v;
    return *this;
}
bvariant& bvariant::as_grid_area(grid_area v) {
    _value = v;
    return *this;
}

void bvariant::acquire(uint8_t type) {
    verify_no_crash(is_empty());
    switch (type) {
    case etype_bool:
        _value = bool();
        break;
    case etype_int32:
        _value = int32_t();
        break;
    case etype_uint32:
        _value = uint32_t();
        break;
    case etype_uint64:
        _value = uint64_t();
        break;
    case etype_float:
        _value = float();
        break;
    case etype_ptr:
        _value = (void*)nullptr;
        break;
    case etype_str:
        _value = xstring();
        break;
    case etype_u16:
        _value = uint16_t();
        break;
    case etype_vec2i:
        _value = vec2i();
        break;
    case etype_tile2i:
        _value = tile2i();
        break;
    case etype_grid_area:
        _value = grid_area();
        break;
    default:
        verify_no_crash(false);
    }
}

void bvariant::release() {
    _value = std::monostate{};
}

bstring1024 bvariant::debug_str() const {
    bstring1024 result;
    switch (_value.index()) {
    case etype_none:
        result = "none";
        break;
    case etype_bool:
        result.printf("bool[%s]", std::get<bool>(_value) ? "TRUE" : "FALSE");
        break;
    case etype_u16:
        result.printf("u16[%d]", uint32_t(std::get<uint16_t>(_value)));
        break;
    case etype_int32:
        result.printf("int32[%d]", std::get<int32_t>(_value));
        break;
    case etype_uint32:
        result.printf("uint32[%d]", uint32_t(std::get<uint32_t>(_value)));
        break;
    case etype_uint64:
        result.printf("uint64[%llu]", (unsigned long long)std::get<uint64_t>(_value));
        break;
    case etype_float:
        result.printf("float[%f]", std::get<float>(_value));
        break;
    case etype_ptr:
        result.printf("ptr[%p]", std::get<void*>(_value));
        break;
    case etype_str:
        result.printf("str[%s]", std::get<xstring>(_value).c_str());
        break;
    case etype_vec2i: {
        const vec2i& v = std::get<vec2i>(_value);
        result.printf("vec2i[%d,%d]", v.x, v.y);
        break;
    }
    case etype_tile2i: {
        const tile2i& v = std::get<tile2i>(_value);
        result.printf("tile2i[%d,%d]", v.x(), v.y());
        break;
    }
    case etype_grid_area: {
        const grid_area& a = std::get<grid_area>(_value);
        result.printf("grid_area[%d,%d,%d,%d]", a.tmin_x, a.tmin_y, a.tmax_x, a.tmax_y);
        break;
    }
    default:
        verify_no_crash(false);
    }
    return result;
}

bstring1024 bvariant::to_str() const {
    bstring1024 result;
    switch (_value.index()) {
    case etype_none:
        result = "none";
        break;
    case etype_bool:
        result.printf("%s", std::get<bool>(_value) ? "true" : "false");
        break;
    case etype_u16:
        result.printf("%d", uint32_t(std::get<uint16_t>(_value)));
        break;
    case etype_int32:
        result.printf("%d", std::get<int32_t>(_value));
        break;
    case etype_uint32:
        result.printf("%u", std::get<uint32_t>(_value));
        break;
    case etype_uint64:
        result.printf("%llu", (unsigned long long)std::get<uint64_t>(_value));
        break;
    case etype_float:
        result.printf("%f", std::get<float>(_value));
        break;
    case etype_ptr:
        result.printf("%p", std::get<void*>(_value));
        break;
    case etype_str:
        result.printf("%s", std::get<xstring>(_value).c_str());
        break;
    case etype_vec2i: {
        const vec2i& v = std::get<vec2i>(_value);
        result.printf("%d,%d", v.x, v.y);
        break;
    }
    case etype_tile2i: {
        const tile2i& v = std::get<tile2i>(_value);
        result.printf("%d,%d", v.x(), v.y());
        break;
    }
    case etype_grid_area: {
        const grid_area& a = std::get<grid_area>(_value);
        result.printf("%d,%d,%d,%d", a.tmin_x, a.tmin_y, a.tmax_x, a.tmax_y);
        break;
    }
    default:
        verify_no_crash(false);
    }
    return result;
}

bool bvariant::to_bool() const {
    switch (_value.index()) {
    case etype_none:
        return false;
    case etype_bool:
        return as_bool();
    case etype_int32:
        return as_int32() != 0;
    case etype_uint32:
        return as_uint32() != 0;
    case etype_uint64:
        return as_uint64() != 0;
    case etype_u16:
        return as_u16() != 0;
    case etype_float:
        return std::fabs(as_float()) > 0.f;
    default:
        verify_no_crash("js_call_result_to_bool: string value");
    }
    return false;
}

bvariant_map::bvariant_map() = default;
bvariant_map::~bvariant_map() = default;
bvariant_map::bvariant_map(const bvariant_map& o) = default;
bvariant_map::bvariant_map(bvariant_map&& o) = default;
bvariant_map& bvariant_map::operator=(const bvariant_map& o) = default;
bvariant_map& bvariant_map::operator=(bvariant_map&& o) = default;

bvariant_map::bvariant_map(std::initializer_list<std::pair<xstring, bvariant_map_val>> init) {
    for (const auto& p : init) {
        values.emplace_back(p.first, p.second.v);
    }
}

const bvariant& bvariant_map::def() const {
    static bvariant dummy;
    return dummy;
}

const bvariant& bvariant_map::value(const xstring& name) const {
    auto it = find(name);
    return (it != values.end()) ? it->second : def();
}

bvariant_map* bvariant_map::acquire_from_pool() {
    return g_bvariant_map_pool.create();
}

void bvariant_map::return_to_pool(bvariant_map *p) {
    g_bvariant_map_pool.destroy(p);
}

float bvariant_map::n(const xstring& name) const {
    const auto& v = value(name);
    switch (v.value_type()) {
    case bvariant::etype_bool:
        return (v.as_bool() ? 1.f : 0.f);
    case bvariant::etype_u16:
        return v.as_u16();
    case bvariant::etype_int32:
        return v.as_int32();
    case bvariant::etype_uint32:
        return v.as_uint32();
    case bvariant::etype_uint64:
        return v.as_uint64();
    case bvariant::etype_float:
        return v.as_float();
    }

    return 0.f;
}

bool bvariant_map::bool_or_def(const xstring& name, const bool def) const {
    return value(name).bool_or_def(def);
}

int32_t bvariant_map::int32_or_def(const xstring& name, const int32_t def) const {
    return value(name).int32_or_def(def);
}

uint32_t bvariant_map::uint32_or_def(const xstring& name, const uint32_t def) const {
    return value(name).uint32_or_def(def);
}

uint64_t bvariant_map::uint64_or_def(const xstring& name, const uint64_t def) const {
    return value(name).uint64_or_def(def);
}

float bvariant_map::float_or_def(const xstring& name, const float def) const {
    return value(name).float_or_def(def);
}

const xstring& bvariant_map::str_or_def(const xstring& name, const xstring& def) const {
    return value(name).str_or_def(def);
}

vec2i bvariant_map::vec2i_or_def(const xstring& name, const vec2i& def) const {
    return value(name).vec2i_or_def(def);
}

tile2i bvariant_map::tile2i_or_def(const xstring& name, const tile2i& def) const {
    return value(name).tile2i_or_def(def);
}

const bvariant& bvariant_map::operator[](const xstring& name) const {
    return value(name);
}

bvariant& bvariant_map::operator[](const xstring& name) {
    auto it = find(name);
    if (it != values.end()) {
        return it->second;
    }
    values.emplace_back(name, bvariant());
    return values.back().second;
}

bvariant_map::ValuesT::iterator bvariant_map::find(const xstring& name) {
    return std::find_if(values.begin(), values.end(), [&name](const PairT& p) { return p.first == name; });
}

bvariant_map::ValuesT::const_iterator bvariant_map::find(const xstring& name) const {
    return std::find_if(values.begin(), values.end(), [&name](const PairT& p) { return p.first == name; });
}
