#pragma once

/**
 * Low-level interlocked primitives (C4 uCore threading.h-style).
 * Volatile scalars only — safe to embed in memset-cleared structs; no std::atomic.
 *
 * Windows: MSVC intrinsics (threading.h PC branch ~68–103).
 * Other:    __atomic_* (semantic match for __sync_* / __sync_swap from PROSPERO 22–50).
 */

#include <cstdint>

#include "platform/platform.h"

namespace threading {

std::int32_t inc(volatile std::int32_t *v);
std::int64_t inc(volatile std::int64_t *v);
std::int32_t dec(volatile std::int32_t *v);
std::int64_t dec(volatile std::int64_t *v);

bool xchgadd(volatile bool *v, bool add);
std::int8_t xchgadd(volatile std::int8_t *v, std::int8_t add);
std::int32_t xchgadd(volatile std::int32_t *v, std::int32_t add);
std::int64_t xchgadd(volatile std::int64_t *v, std::int64_t add);
std::uint8_t xchgadd(volatile std::uint8_t *v, std::uint8_t add);
std::uint32_t xchgadd(volatile std::uint32_t *v, std::uint32_t add);
std::uint64_t xchgadd(volatile std::uint64_t *v, std::uint64_t add);

bool xchg(volatile bool *v, bool x);
std::int8_t xchg(volatile std::int8_t *v, std::int8_t x);
std::int16_t xchg(volatile std::int16_t *v, std::int16_t x);
std::int32_t xchg(volatile std::int32_t *v, std::int32_t x);
std::int64_t xchg(volatile std::int64_t *v, std::int64_t x);
std::uint8_t xchg(volatile std::uint8_t *v, std::uint8_t x);
std::uint16_t xchg(volatile std::uint16_t *v, std::uint16_t x);
std::uint32_t xchg(volatile std::uint32_t *v, std::uint32_t x);
std::uint64_t xchg(volatile std::uint64_t *v, std::uint64_t x);

std::int32_t cmpxchg(volatile std::int32_t *v, std::int32_t xchg_val, std::int32_t cmp);
std::int8_t cmpxchg(volatile std::int8_t *v, std::int8_t xchg_val, std::int8_t cmp);
std::int64_t cmpxchg(volatile std::int64_t *v, std::int64_t xchg_val, std::int64_t cmp);

std::uint32_t or32(volatile std::uint32_t *v, std::uint32_t mask);
std::uint64_t or64(volatile std::uint64_t *v, std::uint64_t mask);
std::uint64_t xor64(volatile std::uint64_t *v, std::uint64_t mask);
std::uint32_t and32(volatile std::uint32_t *v, std::uint32_t mask);
std::uint64_t and64(volatile std::uint64_t *v, std::uint64_t mask);

} // namespace threading


