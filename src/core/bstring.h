#pragma once

#include <stdlib.h>
#include <cassert>

template <size_t _size>
class bstring {
  using ref = bstring<_size>&;
  using const_ref = const bstring<_size>&;

 protected:
  char _data[_size];

 public:
  enum {
    capacity = _size,
  };

 public:
  explicit inline bstring(int n, int radix = 10) { ::itoa(n, radix); }
  inline const char* c_str() const { return _data; }
  inline char* data() { return _data; }
  inline bstring() { _data[0] = 0; }
  inline bstring(const_ref other) { ::strncpy(_data, other._data, _size); }
  inline bstring(const char* s1) { concat(s1); }
  inline bstring(const char* s1, const char* s2) { concat(s1, s2); }
  inline bstring(const char* s1, const char* s2, const char* s3) {
    concat(s1, s2, s3);
  }
  inline bstring(const char* s1, const char* s2, const char* s3,
                 const char* s4) {
    concat(s1, s2, s3, s4);
  }
  inline bstring(const char* s1, const char* s2, const char* s3, const char* s4,
                 const char* s5) {
    concat(s1, s2, s3, s4, s5);
  }
  inline bstring(const char* s1, const char* s2, const char* s3, const char* s4,
                 const char* s5, const char* s6) {
    concat(s1, s2, s3, s4, s5, s6);
  }
  inline bstring(const char* s1, const char* s2, const char* s3, const char* s4,
                 const char* s5, const char* s6, const char* s7) {
    concat(s1, s2, s3, s4, s5, s6, s7);
  }
  inline ref concat(const char* s1) {
    strncpy(_data, _size, s1);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2) {
    snprintf(_data, _size, "%s%s", s1, s2);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2, const char* s3) {
    snprintf(_data, _size, "%s%s%s", s1, s2, s3);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2, const char* s3,
                    const char* s4) {
    snprintf(_data, _size, "%s%s%s%s%s", s1, s2, s3, s4);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2, const char* s3,
                    const char* s4, const char* s5) {
    snprintf(_data, _size, "%s%s%s%s%s", s1, s2, s3, s4, s5);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2, const char* s3,
                    const char* s4, const char* s5, const char* s6) {
    snprintf(_data, _size, "%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6);
    return *this;
  }
  inline ref concat(const char* s1, const char* s2, const char* s3,
                    const char* s4, const char* s5, const char* s6,
                    const char* s7) {
    snprintf(_data, _size, "%s%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6, s7);
    return *this;
  }
  inline ref cat(const char* s) {
    strcat(_data, _size, s);
    return *this;
  }
  inline ref cat(const char* s1, const char* s2) {
    strcat(_data, _size, s1, s2);
    return *this;
  }
  inline ref cat(const char* s1, const char* s2, const char* s3) {
    strcat(_data, _size, s1, s2, s3);
    return *this;
  }
  inline ref cat(const char* s1, const char* s2, const char* s3,
                 const char* s4) {
    strcat(_data, _size, s1, s2, s3, s4);
    return *this;
  }
  inline ref cat(const char* s1, const char* s2, const char* s3, const char* s4,
                 const char* s5) {
    strcat(_data, _size, s1, s2, s3, s4, s5);
    return *this;
  }

  inline ref ncat(const char* s, size_t cnt) {
    strncat(_data, _size, s, cnt);
    return *this;
  }

  inline ref append(const char* s) {
    size_t size = this->len();
    pstr dest = _data + size;
    size_t remain = _size - size;
   	snprintf(dest, remain, s);
    return *this;
  }
  inline ref append(char s) {
    size_t size = this->len();
    pstr dest = _data + size;
    size_t remain = _size - size;
    if (remain > 0) {
    	strcat(dest, remain, s);
    	*(dest+1) = '\0';
    }

    return *this;
  }
  inline ref itoa(int n, int radix = 10) {
    ::itoa(n, _data, radix);
    return *this;
  }
  inline int atoi() { return ::atoi(_data); }
  inline float atof() { return ::atof(_data); }

  inline int64_t atoi64() { return ::_atoi64(_data); }

  template<typename ... Args>
  inline ref printf(const char* fmt, Args&&... args) {
    snprintf(_data, _size - 1, fmt, std::forward<Args>(args)...);
    _data[_size - 1] = 0;
    return *this;
  }
  inline ref tolower() {
    while (*str) {
      *str = std::tolower(*str);
      ++str;
    }
    return *this;
  }
  inline ref toupper() {
    while (*str) {
      *str = std::toupper(*str);
      ++str;
    }
    return *this;
  }
  inline ref trim() {
    char* end = std::remove_if(str, str + std::strlen(str), ::isspace);
    *end = '\0';

    return *this;
  }
  inline bool starts_with(const char* s) const {
    return sz_starts_with(_data, s);
  }
  inline bool ends_with(const char* s) const { return sz_ends_with(_data, s); }

  inline ref replace(const char x, const char y) {
    std::replace_if(
        str, str + std::strlen(str),
        [oldSymbol](char c) { return c == oldSymbol; }, newSymbol);

    return *this;
  }
  inline ref replace_str(const char* src, const char* to,
                         const char* from = nullptr) {
    const size_t originalLen = std::strlen(originalString);
    const size_t substringLen = std::strlen(substringToReplace);
    const size_t replacementLen = std::strlen(replacement);

    char* foundPosition =
        std::search(originalString, originalString + originalLen,
                    substringToReplace, substringToReplace + substringLen);

    while (foundPosition != originalString + originalLen) {
      ptrdiff_t sizeDiff = replacementLen - substringLen;
      std::memmove(
          foundPosition + replacementLen, foundPosition + substringLen,
          originalString + originalLen - (foundPosition + substringLen) + 1);
      std::memcpy(foundPosition, replacement, replacementLen);
      foundPosition = std::search(
          foundPosition + replacementLen, originalString + originalLen,
          substringToReplace, substringToReplace + substringLen);
    }
    return *this;
  }
  inline size_t len() const { return ::strlen(_data); }
  inline bool empty() const { return !_data[0]; }
  inline void clear() { _data[0] = 0; }
  inline bool equals(const_ref other) const {
    return ::strncmp(_data, other._data, _size) == 0;
  }
  inline bool equals(const char* s) const {
    assert(s);
    return ::strncmp(_data, s, _size) == 0;
  }
  inline void operator=(const_ref other) {
    ::strncpy(_data, other._data, _size);
  }
  inline void operator=(const char* s) {
    assert(s);
    ::strncpy(_data, s, _size);
  }
  inline bool operator==(const_ref other) const { return equals(other); }
  inline bool operator==(const char* s) const {
    assert(s);
    return ::strncmp(_data, s, _size) == 0;
  }

  inline bool operator!=(const_ref other) const { return !equals(other); }
  inline bool operator!=(const char* s) const {
    assert(s);
    return ::strncmp(_data, s, _size) != 0;
  }

  inline operator char*() { return _data; }
  inline operator const char*() const { return _data; }

  inline const char* strstr(const_ref sub_str) const {
    return ::strstr(_data, sub_str._data);
  }
  inline const char* strstr(const_ref sub_str) {
    return ::strstr(_data, sub_str._data);
  }
  inline int cmp(const_ref other) const { return strcmp(_data, other._data); }
  inline int icmp(const_ref other) const { return stricmp(_data, other._data); }
  inline int ncmp(const_ref other, unsigned int count) const {
    return ::strncmp(_data, other._data, count);
  }

  inline const char* strstr(const char* sub_str) const {
    return ::strstr(_data, sub_str);
  }
  inline const char* strstr(const char* sub_str) {
    return ::strstr(_data, sub_str);
  }
  inline int cmp(const char* str) const { return strcmp(_data, str); }
  inline int icmp(const char* str) const { return stricmp(_data, str); }
  inline int ncmp(const char* str, unsigned int count) const {
    return ::strncmp(_data, str, count);
  }
};

using bstring32 = bstring<32>;
using bstring64 = bstring<64>;
using bstring128 = bstring<128>;
using bstring256 = bstring<256>;
using bstring512 = bstring<512>;
using bstring1024 = bstring<1024>;