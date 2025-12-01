#include "platform.h"

#if defined(GAME_PLATFORM_ANDROID) || defined(GAME_PLATFORM_LINUX) || defined(GAME_PLATFORM_MACOSX) || defined(GAME_PLATFORM_WEB)

#include <ctime>

uint64_t platform_t::get_qpc() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + ts.tv_nsec;
}

void platform_t::init_timers() {
    timespec res;
    if (clock_getres(CLOCK_MONOTONIC, &res) == 0) {
        uint64_t nanoseconds_per_second = 1000000000;
        uint64_t nanoseconds_per_millisecond = 1000000;
        uint64_t nanoseconds_per_microsecond = 1000;

        qpc_per_second = nanoseconds_per_second;
        qpc_per_milisec = nanoseconds_per_second / nanoseconds_per_millisecond;
        qpc_per_microsec = nanoseconds_per_second / nanoseconds_per_microsecond;
    }

    start_time_ms = platform.get_elapsed_ms();

    _qpc_per_second = get_qpf();
    _qpc_base = get_qpc();
}

uint64_t platform_t::get_qpf() {
    struct timespec res;
    if (clock_getres(CLOCK_MONOTONIC, &res) != 0) {
        return 0;
    }
    return static_cast<uint64_t>(1e9) / (static_cast<uint64_t>(res.tv_sec) * 1e9 + res.tv_nsec);
}

#endif