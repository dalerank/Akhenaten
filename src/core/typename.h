#pragma once

#include <string_view>

namespace detail {
    template <size_t...Idxs>
    constexpr auto substring_as_array(std::string_view str, std::index_sequence<Idxs...>) {
        return std::array{ str[Idxs]..., '\0' };
    }

    template <typename T>
    constexpr auto type_name_array() {
#if defined(__clang__)
        constexpr auto prefix = std::string_view{ "[T = " };
        constexpr auto suffix = std::string_view{ "]" };
        constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(__GNUC__)
        constexpr auto prefix = std::string_view{ "with T = " };
        constexpr auto suffix = std::string_view{ "]" };
        constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
        constexpr auto prefix = std::string_view{ "type_name_array<" };
        constexpr auto suffix = std::string_view{ ">(void)" };
        constexpr auto function = std::string_view{ __FUNCSIG__ };
#else
# error Unsupported compiler
#endif

        constexpr auto start = function.find(prefix) + prefix.size();
        constexpr auto end = function.rfind(suffix);

        static_assert(start < end);

        constexpr auto name = function.substr(start, (end - start));
        return substring_as_array(name, std::make_index_sequence<name.size()>{});
    }

} // detail

template <typename T>
struct type_name_holder {
    static inline constexpr auto value = detail::type_name_array<T>();
};

template <typename T>
constexpr std::string_view type_name() {
    constexpr auto &value = type_name_holder<T>::value;
    return std::string_view{ value.data(), value.size() };
}

inline const char* type_simplified_name(const char* data) {
    return strstr(data, "::") ? strstr(data, "::") + strlen("::")
        : strstr(data, "struct ") ? strstr(data, "struct ") + strlen("struct ")
        : strstr(data, "class ") ? strstr(data, "class ") + strlen("class ")
        : data;
}

// Given a type name of a local struct, extracts the name of the enclosing function.
// e.g. "building_impl::on_place_checks::place_checks" -> "on_place_checks"
//      "building_impl::on_place_checks()::place_checks" -> "on_place_checks" (GCC/Clang)
template<size_t N = 64>
inline bstring<N> type_enclosing_function_name(pcstr data) {
    const char* simplified = type_simplified_name(data);
    // Find the last "::" — everything before it is the function name
    const char* last_sep = nullptr;
    for (const char* p = simplified; *p; p++) {
        if (p[0] == ':' && p[1] == ':') last_sep = p;
    }

    const char* end = last_sep ? last_sep : (simplified + strlen(simplified));
    // Strip trailing "()" added by GCC/Clang: "on_place_checks()"
    if (end > simplified + 1 && end[-1] == ')' && end[-2] == '(') {
        end -= 2;
    }

    int len = (int)(end - simplified);
    if (len >= N) {
        len = N - 1;
    }

    bstring<N> buf;
    if (len > 0) {
        memcpy(buf.data(), simplified, len);
    }

    buf[len] = '\0';
    return buf;
}
