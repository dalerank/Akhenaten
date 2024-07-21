#include <iostream>
#include <typeinfo>
//#include <cxxabi.h>
#include <string.h>
#include <memory>
#include <array>

using u32 = uint32_t;
using s32 = int;

using u32 = uint32_t;
using s32 = int;

// The string_literal class holds a compile-time constant string and provides both substring and character finding operations.
template <unsigned long long length>
class								string_literal final {
    const char string[length];

public:
    // Compile-time string construction from a string array and an integer_sequence to index it.
    template<unsigned long long... indexes>
    constexpr string_literal		(const char(&raw_string)[sizeof...(indexes)], std::integer_sequence<unsigned long long, indexes...> index_sequence) : string{ raw_string[indexes]... } {
        static_cast<void>(index_sequence);
    }

    // Get a pointer to the string data.
    constexpr const char* c_str		() const { return this->string; }

    // Create a substring from this string by providing a template start position, length, and integer_sequence of indexes.
    template<unsigned long long substring_start, unsigned long long substring_length, unsigned long long... substring_indexes>
    constexpr string_literal<substring_length + 1> substr(std::integer_sequence<unsigned long long, substring_indexes...> substring_index_sequence) const {
        static_cast<void>(substring_index_sequence);
        return string_literal<substring_length + 1>({ this->string[substring_start + substring_indexes]..., '\0' }, std::make_integer_sequence<unsigned long long, substring_length + 1>{});
    }

    // Search for a given character within this string.
    constexpr unsigned long long find(const char character, const unsigned long long starting_index = 0) const {
        return						((starting_index >= length)
                                     ? 0xFFFFFFFFFFFFFFFF
                                     : ((this->string[starting_index] == character)
                                     ? starting_index
                                     : this->find(character, starting_index + 1)));
    }

    // Search for a given character within this string in reverse order starting from the end.
    constexpr unsigned long long rfind(const char character, const unsigned long long starting_index = length - 1) const {
        return						((starting_index == 0) 
                                     ? ((this->string[starting_index] == character)
                                     ? starting_index
                                     : 0xFFFFFFFFFFFFFFFF)
                                     : ((this->string[starting_index] == character)
                                     ? starting_index
                                     : this->rfind(character, starting_index - 1)));
    }
};

// The u_enum_name class provides a name function for a given enum type and value.
template<typename enum_type, enum_type enum_value>
class enum_name final {
private:
    // Template struct that holds a sequence of integers, derived from http://stackoverflow.com/a/32223343.
    template <typename integer_type, integer_type... indexes>
    struct integer_sequence {
        using sequence_type = integer_sequence;
    };

    // Template struct declaration that combines two sequences into one.
    template <typename integer_type, typename lhs_sequence, typename rhs_sequence>
    struct merge_sequences;

    // Template struct definition and partial specialisation for merging two interger_sequences.
    template <typename integer_type, integer_type... lhs_indexes, integer_type... rhs_indexes>
    struct merge_sequences< integer_type,
        integer_sequence<integer_type, lhs_indexes...>,
        integer_sequence<integer_type, rhs_indexes...> >
        : integer_sequence<integer_type, lhs_indexes..., (sizeof...(lhs_indexes) + rhs_indexes)...> {};

    // Template struct to create an integer_sequence from zero to the given length.
    template <typename integer_type, unsigned long long length>
    struct make_integer_sequence final : merge_sequences<integer_type,
        typename std::make_integer_sequence<integer_type, length / 2>::sequence_type,
        typename std::make_integer_sequence<integer_type, length - length / 2>::sequence_type> {};

    // Template struct partial specialisation of make_integer_sequence for an integer_sequence of length zero.
    template<typename integer_type>
    struct make_integer_sequence<integer_type, 0> final : integer_sequence<integer_type> {};

    // Template struct partial specialisation of make_integer_sequence for an integer_sequence of length one.
    template<typename integer_type>
    struct make_integer_sequence<integer_type, 1> final : integer_sequence<integer_type, 0> {};

public:
    // Helper function that directly takes an enum_type value template parameter to get the name of the classes template enum type value as a string.
    template <enum_type value>
    constexpr static const char* helper_type() {
        // Clang compiler format:   __PRETTY_FUNCTION__ = static const char *u_enum_name<ENUM_TYPE_NAME, ENUM_TYPE_NAME::ENUM_VALUE_NAME>::helper_type() [enum_type = ENUM_TYPE_NAME, enum_value = ENUM_TYPE_NAME::ENUM_VALUE_NAME, value = ENUM_TYPE_NAME::ENUM_VALUE_NAME]
        // MSVC compiler format:    __FUNCSIG__         = const char *__cdecl u_enum_name<enum ENUM_TYPE_NAME,ENUM_VALUE>::helper_type<ENUM_TYPE_NAME::ENUM_VALUE_NAME>(void)

#if defined(__clang__)
        constexpr static const unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr static const string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind('=') + 2;
        constexpr static const unsigned long long type_name_end    = function_name.rfind(':') - 1;
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__GNUC__)
        constexpr unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr u_string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr unsigned long long type_name_start  = function_name.rfind('=') + 2;
        constexpr unsigned long long type_name_end    = function_name.rfind(':') - 1;
        constexpr unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr u_string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
        constexpr static const unsigned long long function_name_length = sizeof(__FUNCSIG__);
        constexpr static const string_literal<function_name_length> function_name(__FUNCSIG__, gtl::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind('<') + 1;
        constexpr static const unsigned long long type_name_end    = function_name.rfind(':') - 1;
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#else
#error "Unsupported compiler."
#endif
    }

    // Helper function that directly takes an enum_type value template parameter to get the name of the classes template enum type value as a string.
    template <enum_type value>
    constexpr static const char* helper_value() {
        // Clang compiler format:   __PRETTY_FUNCTION__ = static const char *u_enum_name<ENUM_TYPE_NAME, ENUM_TYPE_NAME::ENUM_VALUE_NAME>::helper_value() [enum_type = ENUM_TYPE_NAME, enum_value = ENUM_TYPE_NAME::ENUM_VALUE_NAME, value = ENUM_TYPE_NAME::ENUM_VALUE_NAME]
        // MSVC compiler format:    __FUNCSIG__         = const char *__cdecl u_enum_name<enum ENUM_TYPE_NAME,ENUM_VALUE>::helper_value<ENUM_TYPE_NAME::ENUM_VALUE_NAME>(void)

#if defined(__clang__)
        constexpr static const unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr static const string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind(':') + 1;
        constexpr static const unsigned long long type_name_end    = function_name_length - 2;
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__GNUC__)
        constexpr unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr unsigned long long type_name_start  = function_name.rfind(':') + 1;
        constexpr unsigned long long type_name_end    = function_name_length - 2;
        constexpr unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
        constexpr static const unsigned long long function_name_length = sizeof(__FUNCSIG__);
        constexpr static const string_literal<function_name_length> function_name(__FUNCSIG__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind(':') + 1;
        constexpr static const unsigned long long type_name_end    = function_name.rfind('>');
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#else
#error "Unsupported compiler."
#endif
    }

    // Helper function that directly takes an enum_type value template parameter to get the name of the classes template enum type value as a string.
    template <enum_type value>
    constexpr static const char* helper_name() {
        // Clang compiler format:   __PRETTY_FUNCTION__ = static const char *u_enum_name<ENUM_TYPE_NAME, ENUM_TYPE_NAME::ENUM_VALUE_NAME>::helper_value() [enum_type = ENUM_TYPE_NAME, enum_value = ENUM_TYPE_NAME::ENUM_VALUE_NAME, value = ENUM_TYPE_NAME::ENUM_VALUE_NAME]
        // MSVC compiler format:    __FUNCSIG__         = const char *__cdecl u_enum_name<enum ENUM_TYPE_NAME,ENUM_VALUE>::helper_value<ENUM_TYPE_NAME::ENUM_VALUE_NAME>(void)

#if defined(__clang__)
        constexpr static const unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr static const u_string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind('=') + 2;
        constexpr static const unsigned long long type_name_end    = function_name_length - 2;
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const u_string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__GNUC__)
        constexpr unsigned long long function_name_length = sizeof(__PRETTY_FUNCTION__);
        constexpr u_string_literal<function_name_length> function_name(__PRETTY_FUNCTION__, detail::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr unsigned long long type_name_start  = function_name.rfind('=') + 2;
        constexpr unsigned long long type_name_end    = function_name_length - 2;
        constexpr unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr u_string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
        constexpr static const unsigned long long function_name_length = sizeof(__FUNCSIG__);
        constexpr static const string_literal<function_name_length> function_name(__FUNCSIG__, std::make_integer_sequence<unsigned long long, function_name_length>{});
        constexpr static const unsigned long long type_name_start  = function_name.rfind('<') + 1;
        constexpr static const unsigned long long type_name_end    = function_name.rfind('>');
        constexpr static const unsigned long long type_name_length = type_name_end - type_name_start;
        constexpr static const string_literal<type_name_length + 1> type_name_string = function_name.template substr<type_name_start, type_name_length>(std::make_integer_sequence<unsigned long long, type_name_length>{});
        return type_name_string.c_str();
#else
#error "Unsupported compiler."
#endif
    }

public:
    constexpr static const char* name_type() { return helper_type<enum_value>(); }			// Get the name of the classes template enum type as a string.
    constexpr static const char* name_value() { return helper_value<enum_value>(); }		// Get the name of the classes template enum type value as a string.
    constexpr static const char* name() { return helper_name<enum_value>(); }				// Get the name of the classes template enum type and value as a string.
};

struct token {
    const char * name;
    s32 id;
};

template<typename enum_type, enum_type begin, enum_type end>
struct token_holder {
    constexpr static inline int count_values(enum_type type) {
        return (type != end)
            ? count_values((enum_type)(s32(type)+1))
            : (s32(type)+1);
    }

    static constexpr u32 N = count_values(begin);
    using tokens = std::array<token, N+1>; // because have {0, 0} in last element

    template<typename e_enum_type, e_enum_type enum_value>
    constexpr token make_name() {
        return { enum_name<e_enum_type, enum_value>().name(), enum_value };
    }

    template<typename e_enum_type, u32... Indices>
    constexpr tokens make_tokens_helper(std::integer_sequence<u32, Indices...>) {
        tokens ts = { make_name<e_enum_type, (e_enum_type)Indices>()... };
        ts[N] = {0, 0};
        return ts;
    }

    template<typename e_enum_type>
    constexpr tokens make_tokens() {
        return make_tokens_helper<e_enum_type>( std::make_integer_sequence<u32, N>{});
    }

    operator const token *() const { return values.unsafe_ptr(); }
    const token *data() const { return values.unsafe_ptr(); }
    constexpr token_holder() : values{make_tokens<enum_type>()} {}

    tokens values;
};

struct token {
    const char * name;
    s32 id;
};

template<typename enum_type, enum_type begin, enum_type end>
struct token_holder {
    constexpr static inline int count_values(enum_type type) {
        return (type != end)
            ? count_values((enum_type)(s32(type)+1))
            : (s32(type)+1);
    }

    static constexpr u32 N = count_values(begin);
    using tokens = std::array<token, N+1>; // because have {0, 0} in last element

    template<typename e_enum_type, e_enum_type enum_value>
    constexpr token make_name() {
        return { enum_name<e_enum_type, enum_value>().name(), enum_value };
    }

    template<typename e_enum_type, u32... Indices>
    constexpr tokens make_tokens_helper(std::integer_sequence<u32, Indices...>) {
        tokens ts = { make_name<e_enum_type, (e_enum_type)Indices>()... };
        ts[N] = {0, 0};
        return ts;
    }

    template<typename e_enum_type>
    constexpr tokens make_tokens() {
        return make_tokens_helper<e_enum_type>( std::make_integer_sequence<u32, N>{});
    }

    operator const token *() const { return values.unsafe_ptr(); }
    const token *data() const { return values.unsafe_ptr(); }
    constexpr token_holder() : values{make_tokens<enum_type>()} {}

    tokens values;
};

#ifdef TOKENNUM_TEST
enum test_enum { te_first, te_second, te_third, te_count };

int main() {
    const token_holder<test_enum, te_first, te_count> test_tokens;

    for (auto &s: test_tokens.values)
        std::cout << "{" << (s.name ? s.name : "null") << ", " << s.id << " }" << std::endl;
    return 0;
}
#endif // TOKENNUM_TEST
