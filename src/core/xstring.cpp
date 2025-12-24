#include "xstring.h"

#include "log.h"
#include "crc32.h"
#include "core/core.h"

#include <mutex>
#include <unordered_map>

static std::mutex xstring_container_m;

struct xstring_container {
    std::unordered_map<uint32_t, xstring_value *> data;
    void verify();
    void dump(FILE *f) const;
    static xstring_value *dock(pcstr value);
    void dump();
    void clean();

    ~xstring_container() {
        clean();
    }
};

xstring_container *g_xstring = nullptr;

void xstring_container::verify() {
    std::scoped_lock _(xstring_container_m);
    logs::info("strings verify started");
    for (const auto &it: data) {
        const auto crc = crc32(it.second->value.c_str(), it.second->length);
        bstring32 crc_str;
        verify_no_crash(crc == it.second->crc);// , "error: read-only memory corruption (shared_strings)"); // itoa(value->dwCRC, crc_str, 16));
        verify_no_crash(it.second->length == it.second->value.length());// , "error: read-only memory corruption (shared_strings, internal structures)");// , value->value);
    }
    logs::info("strings verify completed");
}

void xstring_container::dump(FILE *f) const {
    for (const auto &it: data) {
        fprintf(f, "ref[%4u]-len[%3u]-crc[%8X] : %s\n", it.second->reference, it.second->length, it.second->crc, it.second->value.c_str());
    }
}

xstring_value *xstring_container::dock(pcstr value) {
    if (nullptr == value) {
        return nullptr;
    }

    std::scoped_lock _(xstring_container_m);

    if (!g_xstring) {
        g_xstring = new xstring_container();
        g_xstring->data.reserve(4096);
    }

    // calc len
    const size_t s_len = strlen(value);
    const size_t s_len_with_zero = s_len + 1;
    verify_no_crash(sizeof(xstring_value) + s_len_with_zero < (2 * 4096 + 2048));

    // setup find structure
    uint16_t length = static_cast<uint32_t>(s_len);
    uint32_t crc = crc32(value, uint32_t(s_len));

    // search
    auto it = g_xstring->data.find(crc);

    // it may be the case, string is not found or has "non-exact" match
    if (it == g_xstring->data.end()) {
        xstring_value *new_xstr = new xstring_value;
        new_xstr->reference = 0;
        new_xstr->length = length;
        new_xstr->crc = crc;
        new_xstr->value = value;

        g_xstring->data.insert({crc, new_xstr});
        return new_xstr;
    }

    return it->second;
}

void xstring_container::dump() {
    std::scoped_lock _(xstring_container_m);
    FILE* F = fopen("c:\\$str_dump$.txt", "w");
    dump(F);
    fclose(F);
}

void xstring_container::clean() {
    for (const auto &it : data) {
        delete it.second;
    }
    data.clear();
}

xstring_value *xstring::_dock(pcstr value) {
    return xstring_container::dock(value);
}