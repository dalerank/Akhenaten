#pragma once

#include <functional>
#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <cstring>
#include <cctype>
#include <algorithm>

#include "core/cstring_allocator.h"
#include "core/crc32.h"

// Base string type using custom allocator
typedef std::basic_string<char, std::char_traits<char>, cstring_allocator> BaseStringType;

/**
 * @class cstring
 * @brief String class adapted for Akhenaten project
 *
 * This is a wrapper around std::basic_string with custom allocator that provides
 * additional utility methods and maintains compatibility with the original CString interface.
 * Supports both common (heap) and frame-based allocation strategies.
 */
class cstring {
public:
    cstring() = default;

    // Constructor with custom allocator (supports both common and frame allocation)
    explicit cstring(const cstring_allocator &allocator);
    cstring(const char *s);
    cstring(const unsigned char *s);

    cstring(cstring &&) = default;
    cstring &operator=(cstring &&) = default;

    cstring(const char *szNonTerminatedString, int nLength);
    cstring(const unsigned char *szNonTerminatedString, int nLength);

    cstring(const cstring &other) {
        _str = other._str.c_str();
    }

    cstring &operator=(const cstring &other) = default;

    explicit cstring(const std::string_view &view);

    cstring &operator=(const std::string_view &view);
    cstring &operator=(std::initializer_list<char> List);
    void operator=(const char *other);

    void swap(cstring &Other);

    void reserve(uint32_t size);

    inline const char *c_str() const { return _str.c_str(); }
    inline const char *data() const { return _str.data(); }

    inline int32_t size() const { return _str.size(); }

    inline bool empty() const { return _str.empty(); }

    void clear();

    // Return index to first instance found or -1 if not found
    int32_t find(char ch, int32_t nStartPos = 0) const;
    int32_t find(const cstring &String, int32_t nStartPos = 0) const;

    // Return index to last instance found or -1 if not found
    int32_t findLast(char ch, int32_t nStartPos = -1) const;
    int32_t findLast(const char *szString) const;

    template <typename... Args>
    cstring &Concat(Args&&... args) {
        ((*this += std::forward<Args>(args)), ...);
        return *this;
    }

    template <typename TArr>
    void SplitEmplace(TArr &Result, char Separator) const {
        Result.clear();

        int nCurrPos = 0;
        int nNextPos = 0;
        while (nNextPos != -1) {
            nNextPos = find(Separator, nCurrPos);
            if (nNextPos != -1) {
                Result.push_back(this->substr(nCurrPos, nNextPos));
            } else {
                Result.push_back(this->substr(nCurrPos, size()));
            }
            nCurrPos = nNextPos + 1;
        }
    }

    std::vector<cstring> Split(char Separator = ';') const {
        std::vector<cstring> Result;
        SplitEmplace(Result, Separator);
        return Result;
    }

    // Returns a copy of the string with all leading and trailing whitespaces removed
    cstring get_trimmed() const;
    void trim();

    cstring substr(int32_t nStartPos, int32_t nEndPos) const;
    bool replace(const cstring &From, const cstring &To);
    void replaceAll(const char *replaceWhat, const char *replaceWithWhat);

    // Remove all characters satisfying Pred. returns true if string has changed
    template <class PRED>
    bool RemoveIf(const PRED &Pred) {
        auto end = std::remove_if(_str.begin(), _str.end(), Pred);
        size_t before = _str.length();
        _str.erase(end, _str.end());
        return before != _str.length();
    }

    void removeAt(int32_t nPos);

    char &operator[](uint32_t index);
    const char &operator[](uint32_t index) const;
    char &operator[](int32_t index);
    const char &operator[](int32_t index) const;

    bool operator==(const cstring &other) const { return _str == other._str; }
    bool operator==(const std::string_view &other) const;
    bool operator==(const char *other) const { return strcmp(c_str(), other) == 0; }

    bool operator!=(const cstring &other) const { return _str != other._str; }
    bool operator!=(const std::string_view &other) const;
    bool operator!=(const char *other) const { return strcmp(c_str(), other) != 0; }

    bool operator<(const cstring &other) const;
    bool operator<=(const cstring &other) const;
    bool operator>=(const cstring &other) const;
    bool operator>(const cstring &other) const;
    cstring &operator+=(const cstring &other);
    cstring &operator+=(const std::string_view &other);
    cstring &operator+=(const char *other);
    cstring &operator+=(char other);

    void toLower();
    void toUpper();
    bool isLower() const;

    bool startsWith(const cstring &other) const;
    bool endsWith(const cstring &other) const;

    void AddSpacing() { *this += " "; }
    void AddSpacingIfNeeded();
    void AddNewline() { *this += "\n"; }
    void AddDoubleNewline() { *this += "\n\n"; }
    void AddNewlineIfNeeded() { AddNewlinesIfNeeded(1); }
    void AddDoubleNewlineIfNeeded() { AddNewlinesIfNeeded(2); }
    void AddNewlinesIfNeeded(int32_t nAmountToAdd);

    void IndentLine() { *this += "   "; }

    const BaseStringType &get_string() const { return _str; }
    BaseStringType &access() { return _str; }

    operator std::string_view() const noexcept { return std::string_view(c_str(), size()); }

private:
    BaseStringType _str;
};

// Non-member operators
inline cstring operator+(const cstring &lhs, const cstring &rhs) {
    auto tmp = lhs;
    tmp += rhs;
    return tmp;
}

inline cstring operator+(const cstring &lhs, const char *str) {
    auto tmp = lhs;
    tmp += str;
    return tmp;
}

inline cstring operator+(const cstring &lhs, char c) {
    auto tmp = lhs;
    tmp += c;
    return tmp;
}

inline cstring operator+(const cstring &lhs, cstring &&rhs) {
    auto tmp = lhs;
    tmp += std::move(rhs);
    return tmp;
}

inline cstring operator+(cstring &&lhs, const cstring &rhs) {
    cstring tmp = std::move(lhs);
    tmp += rhs;
    return tmp;
}

inline cstring operator+(cstring &&lhs, const char *str) {
    cstring tmp = std::move(lhs);
    tmp += str;
    return tmp;
}

inline cstring operator+(cstring &&lhs, char c) {
    cstring tmp = std::move(lhs);
    tmp += c;
    return tmp;
}

inline cstring operator+(cstring &&lhs, cstring &&rhs) {
    cstring tmp = std::move(lhs);
    tmp += std::move(rhs);
    return tmp;
}

inline cstring operator+(const char *s1, const cstring &s2) {
    cstring str(s1);
    str += s2;
    return str;
}

inline cstring operator+(const char *s1, cstring &&s2) {
    cstring str(s1);
    str += std::move(s2);
    return str;
}

// Hash support for std::unordered_map
template <>
struct std::hash<cstring> {
    size_t operator()(const cstring &String) const noexcept { return crc32_str(String.c_str()); }
};

/**
 * @brief User-defined literal to create CFrameString from a string literal.
 * @example "GFX_topbar_"_framestr + EnumToString( eView ) + "_button"
 */
inline cstring operator"" _framestr(const char *str, std::size_t len) {
    cstring Ret(frameAlloc());
    Ret += std::string_view(str, static_cast<size_t>(len));
    return Ret;
}
