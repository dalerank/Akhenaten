#include "core/interlocked.h"


#if defined(GAME_PLATFORM_WIN)

#include <intrin.h>
#include <windows.h>

namespace threading {

    std::int32_t inc(volatile std::int32_t *v) { return _InterlockedIncrement(reinterpret_cast<volatile LONG *>(v)); }
    std::int64_t inc(volatile std::int64_t *v) { return _InterlockedIncrement64(reinterpret_cast<volatile LONG64 *>(v)); }
    std::int32_t dec(volatile std::int32_t *v) { return _InterlockedDecrement(reinterpret_cast<volatile LONG *>(v)); }
    std::int64_t dec(volatile std::int64_t *v) { return _InterlockedDecrement64(reinterpret_cast<volatile LONG64 *>(v)); }

    bool xchgadd(volatile bool *v, bool add) { return static_cast<bool>(_InterlockedExchangeAdd8(reinterpret_cast<volatile char *>(v), static_cast<char>(add))); }
    std::int8_t xchgadd(volatile std::int8_t *v, std::int8_t add) { return static_cast<std::int8_t>(_InterlockedExchangeAdd8(reinterpret_cast<volatile char *>(v), add)); }
    std::int32_t xchgadd(volatile std::int32_t *v, std::int32_t add) { return static_cast<std::int32_t>(_InterlockedExchangeAdd(reinterpret_cast<volatile LONG *>(v), add)); }
    std::int64_t xchgadd(volatile std::int64_t *v, std::int64_t add) { return static_cast<std::int64_t>(_InterlockedExchangeAdd64(reinterpret_cast<volatile LONG64 *>(v), add)); }
    std::uint8_t xchgadd(volatile std::uint8_t *v, std::uint8_t add) { return static_cast<std::uint8_t>(_InterlockedExchangeAdd8(reinterpret_cast<volatile char *>(v), static_cast<char>(add))); }
    std::uint32_t xchgadd(volatile std::uint32_t *v, std::uint32_t add) { return static_cast<std::uint32_t>(_InterlockedExchangeAdd(reinterpret_cast<volatile LONG *>(v), static_cast<LONG>(add))); }
    std::uint64_t xchgadd(volatile std::uint64_t *v, std::uint64_t add) { return static_cast<std::uint64_t>(_InterlockedExchangeAdd64(reinterpret_cast<volatile LONG64 *>(v), static_cast<LONG64>(add))); }

    bool xchg(volatile bool *v, bool x) { return static_cast<bool>(_InterlockedExchange8(reinterpret_cast<volatile char *>(v), static_cast<char>(x))); }
    std::int8_t xchg(volatile std::int8_t *v, std::int8_t x) { return static_cast<std::int8_t>(_InterlockedExchange8(reinterpret_cast<volatile char *>(v), x)); }
    std::int16_t xchg(volatile std::int16_t *v, std::int16_t x) { return static_cast<std::int16_t>(_InterlockedExchange16(reinterpret_cast<volatile SHORT *>(v), x)); }
    std::int32_t xchg(volatile std::int32_t *v, std::int32_t x) { return static_cast<std::int32_t>(_InterlockedExchange(reinterpret_cast<volatile LONG *>(v), x)); }
    std::int64_t xchg(volatile std::int64_t *v, std::int64_t x) { return static_cast<std::int64_t>(_InterlockedExchange64(reinterpret_cast<volatile LONG64 *>(v), x)); }
    std::uint8_t xchg(volatile std::uint8_t *v, std::uint8_t x) { return static_cast<std::uint8_t>(_InterlockedExchange8(reinterpret_cast<volatile char *>(v), static_cast<char>(x))); }
    std::uint16_t xchg(volatile std::uint16_t *v, std::uint16_t x) { return static_cast<std::uint16_t>(_InterlockedExchange16(reinterpret_cast<volatile SHORT *>(v), static_cast<SHORT>(x))); }
    std::uint32_t xchg(volatile std::uint32_t *v, std::uint32_t x) { return static_cast<std::uint32_t>(_InterlockedExchange(reinterpret_cast<volatile LONG *>(v), static_cast<LONG>(x))); }
    std::uint64_t xchg(volatile std::uint64_t *v, std::uint64_t x) { return static_cast<std::uint64_t>(_InterlockedExchange64(reinterpret_cast<volatile LONG64 *>(v), static_cast<LONG64>(x))); }

    std::int32_t cmpxchg(volatile std::int32_t *v, std::int32_t xchg_val, std::int32_t cmp) { return static_cast<std::int32_t>(_InterlockedCompareExchange(reinterpret_cast<volatile LONG *>(v), xchg_val, cmp)); }
    std::int8_t cmpxchg(volatile std::int8_t *v, std::int8_t xchg_val, std::int8_t cmp) { return static_cast<std::int8_t>(_InterlockedCompareExchange8(reinterpret_cast<volatile char *>(v), xchg_val, cmp)); }
    std::int64_t cmpxchg(volatile std::int64_t *v, std::int64_t xchg_val, std::int64_t cmp) { return static_cast<std::int64_t>(_InterlockedCompareExchange64(reinterpret_cast<volatile LONG64 *>(v), xchg_val, cmp)); }

    std::uint32_t or32(volatile std::uint32_t *v, std::uint32_t mask) { return static_cast<std::uint32_t>(_InterlockedOr(reinterpret_cast<volatile LONG *>(v), static_cast<LONG>(mask))); }
    std::uint64_t or64(volatile std::uint64_t *v, std::uint64_t mask) { return static_cast<std::uint64_t>(_InterlockedOr64(reinterpret_cast<volatile LONG64 *>(v), static_cast<LONG64>(mask))); }
    std::uint64_t xor64(volatile std::uint64_t *v, std::uint64_t mask) { return static_cast<std::uint64_t>(_InterlockedXor64(reinterpret_cast<volatile LONG64 *>(v), static_cast<LONG64>(mask))); }
    std::uint32_t and32(volatile std::uint32_t *v, std::uint32_t mask) { return static_cast<std::uint32_t>(_InterlockedAnd(reinterpret_cast<volatile LONG *>(v), static_cast<LONG>(mask))); }
    std::uint64_t and64(volatile std::uint64_t *v, std::uint64_t mask) { return static_cast<std::uint64_t>(_InterlockedAnd64(reinterpret_cast<volatile LONG64 *>(v), static_cast<LONG64>(mask))); }

}

#else
namespace threading {

    std::int32_t inc(volatile std::int32_t *v) { return __atomic_add_fetch(v, 1, __ATOMIC_ACQ_REL); }
    std::int64_t inc(volatile std::int64_t *v) { return __atomic_add_fetch(v, 1, __ATOMIC_ACQ_REL); }
    std::int32_t dec(volatile std::int32_t *v) { return __atomic_sub_fetch(v, 1, __ATOMIC_ACQ_REL); }
    std::int64_t dec(volatile std::int64_t *v) { return __atomic_sub_fetch(v, 1, __ATOMIC_ACQ_REL); }

    bool xchgadd(volatile bool *v, bool add) { return static_cast<bool>(__atomic_fetch_add(reinterpret_cast<volatile char *>(v), static_cast<char>(add), __ATOMIC_ACQ_REL)); }
    std::int8_t xchgadd(volatile std::int8_t *v, std::int8_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }
    std::int32_t xchgadd(volatile std::int32_t *v, std::int32_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }
    std::int64_t xchgadd(volatile std::int64_t *v, std::int64_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }
    std::uint8_t xchgadd(volatile std::uint8_t *v, std::uint8_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }
    std::uint32_t xchgadd(volatile std::uint32_t *v, std::uint32_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }
    std::uint64_t xchgadd(volatile std::uint64_t *v, std::uint64_t add) { return __atomic_fetch_add(v, add, __ATOMIC_ACQ_REL); }

    std::int32_t cmpxchg(volatile std::int32_t *v, std::int32_t xchg_val, std::int32_t cmp) {
        std::int32_t expected = cmp;
        (void)__atomic_compare_exchange_n(v, &expected, xchg_val, false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
        return expected;
    }

    std::int8_t cmpxchg(volatile std::int8_t *v, std::int8_t xchg_val, std::int8_t cmp) {
        std::int8_t expected = cmp;
        (void)__atomic_compare_exchange_n(v, &expected, xchg_val, false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
        return expected;
    }
    std::int64_t cmpxchg(volatile std::int64_t *v, std::int64_t xchg_val, std::int64_t cmp) {
        std::int64_t expected = cmp;
        (void)__atomic_compare_exchange_n(v, &expected, xchg_val, false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
        return expected;
    }

    std::uint32_t or32(volatile std::uint32_t *v, std::uint32_t mask) { return __atomic_or_fetch(v, mask, __ATOMIC_ACQ_REL); }
    std::uint64_t or64(volatile std::uint64_t *v, std::uint64_t mask) { return __atomic_or_fetch(v, mask, __ATOMIC_ACQ_REL); }
    std::uint64_t xor64(volatile std::uint64_t *v, std::uint64_t mask) { return __atomic_xor_fetch(v, mask, __ATOMIC_ACQ_REL); }
    std::uint32_t and32(volatile std::uint32_t *v, std::uint32_t mask) { return __atomic_and_fetch(v, mask, __ATOMIC_ACQ_REL); }
    std::uint64_t and64(volatile std::uint64_t *v, std::uint64_t mask) { return __atomic_and_fetch(v, mask, __ATOMIC_ACQ_REL); }

    bool xchg(volatile bool *v, bool x) { return static_cast<bool>(__atomic_exchange_n(reinterpret_cast<volatile char *>(v), static_cast<char>(x), __ATOMIC_ACQ_REL)); }
    std::int8_t xchg(volatile std::int8_t *v, std::int8_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::int16_t xchg(volatile std::int16_t *v, std::int16_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::int32_t xchg(volatile std::int32_t *v, std::int32_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::int64_t xchg(volatile std::int64_t *v, std::int64_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::uint8_t xchg(volatile std::uint8_t *v, std::uint8_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::uint16_t xchg(volatile std::uint16_t *v, std::uint16_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::uint32_t xchg(volatile std::uint32_t *v, std::uint32_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
    std::uint64_t xchg(volatile std::uint64_t *v, std::uint64_t x) { return __atomic_exchange_n(v, x, __ATOMIC_ACQ_REL); }
}

#endif