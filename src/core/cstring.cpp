#include "core/cstring.h"
#include "core/string.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>

cstring::cstring(const cstring_allocator &allocator)
    : _str(allocator) {
}

cstring::cstring(const char *s)
    : _str(s ? s : "", cstring_allocator()) {
}

cstring::cstring(const unsigned char *s)
    : _str(reinterpret_cast<const char *>(s), cstring_allocator()) {
}

cstring::cstring(const char *szNonTerminatedString, int nLength)
    : _str(szNonTerminatedString, static_cast<size_t>(nLength), cstring_allocator()) {
}

cstring::cstring(const unsigned char *szNonTerminatedString, int nLength)
    : _str(reinterpret_cast<const char *>(szNonTerminatedString), static_cast<size_t>(nLength), cstring_allocator()) {
}

cstring::cstring(const std::string_view &view)
    : _str(view.data(), view.size(), cstring_allocator()) {
}

cstring &cstring::operator=(const std::string_view &view) {
    _str.assign(view.data(), view.size());
    return *this;
}

cstring &cstring::operator=(std::initializer_list<char> List) {
    _str = List;
    return *this;
}

void cstring::operator=(const char *other) {
    _str = BaseStringType(other ? other : "", cstring_allocator());
}

void cstring::swap(cstring &Other) {
    _str.swap(Other._str);
}

void cstring::reserve(uint32_t size) {
    _str.reserve(size);
}

char &cstring::operator[](uint32_t index) {
    return _str[index];
}

const char &cstring::operator[](uint32_t index) const {
    return _str[index];
}

char &cstring::operator[](int32_t index) {
    return _str[static_cast<size_t>(index)];
}

const char &cstring::operator[](int32_t index) const {
    return _str[static_cast<size_t>(index)];
}

bool cstring::operator<(const cstring &other) const {
    return _str < other._str;
}

bool cstring::operator<=(const cstring &other) const {
    return _str <= other._str;
}

bool cstring::operator>(const cstring &other) const {
    return _str > other._str;
}

bool cstring::operator>=(const cstring &other) const {
    return _str >= other._str;
}

cstring &cstring::operator+=(const cstring &other) {
    _str += other._str;
    return *this;
}

cstring &cstring::operator+=(const std::string_view &other) {
    _str.append(other.data(), other.size());
    return *this;
}

cstring &cstring::operator+=(const char *other) {
    if (other) {
        _str += other;
    }
    return *this;
}

cstring &cstring::operator+=(char other) {
    _str += other;
    return *this;
}

bool cstring::operator==(const std::string_view &other) const {
    return other == std::string_view(_str.data(), _str.size());
}

bool cstring::operator!=(const std::string_view &other) const {
    return other != std::string_view(_str.data(), _str.size());
}

int32_t cstring::find(char ch, int32_t nStartPos) const {
    size_t pos = _str.find(ch, static_cast<size_t>(nStartPos));
    return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

int32_t cstring::find(const cstring &String, int32_t nStartPos) const {
    size_t pos = _str.find(String._str, static_cast<size_t>(nStartPos));
    return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

int32_t cstring::findLast(char ch, int32_t nStartPos) const {
    if (nStartPos >= 0) {
        return substr(0, nStartPos).findLast(ch);
    }

    size_t pos = _str.find_last_of(ch);
    return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

int32_t cstring::findLast(const char *szString) const {
    size_t pos = _str.find_last_of(szString);
    return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

cstring cstring::get_trimmed() const {
    const size_t nStart = _str.find_first_not_of("\n\t\r ");
    const size_t nEnd = _str.find_last_not_of("\n\t\r ");

    if (std::string::npos == nStart || std::string::npos == nEnd) {
        return "";
    }

    return substr(static_cast<int32_t>(nStart), static_cast<int32_t>(nEnd) + 1);
}

void cstring::trim() {
    *this = this->get_trimmed();
}

cstring cstring::substr(int32_t nStartPos, int32_t nEndPos) const {
    if (nStartPos < 0) {
        nStartPos = 0;
    }
    if (nEndPos > size()) {
        nEndPos = size();
    }
    if (nEndPos < nStartPos) {
        nEndPos = nStartPos;
    }

    cstring Ret(_str.get_allocator());
    Ret = _str.substr(static_cast<unsigned int>(nStartPos), static_cast<unsigned int>(nEndPos - nStartPos)).c_str();
    return Ret;
}

bool cstring::replace(const cstring &From, const cstring &To) {
    size_t pos = _str.find(From._str);
    if (pos == std::string::npos)
        return false;
    _str.replace(pos, From._str.size(), To._str);
    return true;
}

void cstring::replaceAll(const char *replaceWhat, const char *replaceWithWhat) {
    const size_t str_len = strlen(replaceWhat);
    const size_t str_len_replace = strlen(replaceWithWhat);
    size_t pos = 0;
    for (;;) {
        pos = _str.find(replaceWhat, pos);
        if (pos == std::string::npos)
            break;

        _str.replace(pos, str_len, replaceWithWhat);
        pos += str_len_replace;
    }
}

void cstring::removeAt(int32_t nPos) {
    _str.erase(static_cast<size_t>(nPos), 1);
}

void cstring::toLower() {
    std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
}

void cstring::toUpper() {
    std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
}

bool cstring::isLower() const {
    return std::all_of(_str.begin(), _str.end(), [] (char c) { return ::islower(c) || !::isalpha(c); });
}

void cstring::clear() {
    _str.clear();
}

bool cstring::startsWith(const cstring &other) const {
    return _str.find(other.c_str(), 0) == 0;
}

bool cstring::endsWith(const cstring &other) const {
    if (size() < other.size()) {
        return false;
    }

    return _str.compare(size() - other.size(), other.size(), other._str) == 0;
}

void cstring::AddSpacingIfNeeded() {
    int32_t nSize = size();
    if (nSize == 0) {
        return;
    }

    if (data()[nSize - 1] == '\n' || data()[nSize - 1] == ' ') {
        return;
    }

    *this += " ";
}

void cstring::AddNewlinesIfNeeded(int32_t nAmountToAdd) {
    int32_t nSize = size();
    if (nSize == 0) {
        return;
    }

    if (data()[nSize - 1] == '\n') {
        nAmountToAdd--;
    }
    for (int32_t i = 0; i < nAmountToAdd; i++) {
        *this += "\n";
    }
}