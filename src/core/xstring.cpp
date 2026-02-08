#include "xstring.h"

#include "log.h"
#include "crc32.h"
#include "core/core.h"

#include <mutex>
#include <unordered_map>
#include <memory_resource>
#include <vector>
#include <memory>

static std::mutex xstring_container_m;

// Custom memory resource that allocates large buffers and manages them manually
// This avoids using standard new/delete for buffer allocation
class buffer_memory_resource : public std::pmr::memory_resource {
private:
    static constexpr size_t BUFFER_SIZE = 1024 * 1024; // 256KB per buffer

    struct buffer {
        void* data;
        size_t size;

        buffer(size_t sz) : size(sz) {
            data = ::operator new(sz);
        }

        ~buffer() {
            ::operator delete(data);
        }

        // Non-copyable
        buffer(const buffer&) = delete;
        buffer& operator=(const buffer&) = delete;
    };

    std::vector<std::unique_ptr<buffer>> buffers;
protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        // Allocate a new buffer for each request
        // monotonic_buffer_resource will manage the buffer internally
        auto new_buf = std::make_unique<buffer>(std::max(bytes, BUFFER_SIZE));
        void* ptr = new_buf->data;
        buffers.push_back(std::move(new_buf));
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        // No-op: monotonic_buffer_resource doesn't deallocate individual blocks
        // All buffers will be freed when buffers vector is destroyed
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

// Linear allocator wrapper for xstring_value objects using pmr::monotonic_buffer_resource
class linear_allocator {
private:
    static constexpr size_t INITIAL_BUFFER_SIZE = 256 * 1024; // 256KB initial buffer

    buffer_memory_resource buffer_resource_impl;
    std::pmr::monotonic_buffer_resource buffer_resource;

public:
    linear_allocator()
        : buffer_resource_impl()
        , buffer_resource(INITIAL_BUFFER_SIZE, &buffer_resource_impl)
    {}

    ~linear_allocator() {
        // Note: Destructors should be called explicitly for objects that are still in use
        // This is done in xstring_container::clean() before the allocator is destroyed
    }

    xstring_value* allocate() {
        constexpr size_t obj_size = sizeof(xstring_value);
        constexpr size_t alignment = alignof(xstring_value);

        // Allocate memory with proper alignment
        void* ptr = buffer_resource.allocate(obj_size, alignment);

        // Construct object using placement new
        return new(ptr) xstring_value();
    }
};

struct xstring_container {
    std::unordered_map<uint32_t, xstring_value *> data;
    linear_allocator allocator;

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
#ifdef XSTRING_USE_REFERENCE_COUNTING
        fprintf(f, "ref[%4u]-len[%3u]-crc[%8X] : %s\n", it.second->reference, it.second->length, it.second->crc, it.second->value.c_str());
#else
        fprintf(f, "len[%3u]-crc[%8X] : %s\n", it.second->length, it.second->crc, it.second->value.c_str());
#endif
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
    verify_no_crash(sizeof(xstring_value) + s_len_with_zero < (3 * 4096));

    // setup find structure
    uint16_t length = static_cast<uint32_t>(s_len);
    uint32_t crc = crc32(value, uint32_t(s_len));

    // search
    auto it = g_xstring->data.find(crc);

    // it may be the case, string is not found or has "non-exact" match
    if (it == g_xstring->data.end()) {
        xstring_value *new_xstr = g_xstring->allocator.allocate();
#ifdef XSTRING_USE_REFERENCE_COUNTING
        new_xstr->reference = 0;
#endif
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
    // Call destructors for all xstring_value objects
    // (they are allocated in linear allocator, so we just need to destruct them)
    for (const auto &it : data) {
        it.second->~xstring_value();
    }
    data.clear();
    // Linear allocator will free all buffers in its destructor
}

xstring_value *xstring::_dock(pcstr value) {
    return xstring_container::dock(value);
}