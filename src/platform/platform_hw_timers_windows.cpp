#include "platform.h"
#include "windows.h"

#if defined(GAME_PLATFORM_WIN)

uint64_t platform_t::get_qpc() {
    uint64_t _dest;
    QueryPerformanceCounter((PLARGE_INTEGER)&_dest);
    return _dest;
}

void platform_t::init_timers() {
    uint64_t qwTimeFreq;
    QueryPerformanceFrequency((PLARGE_INTEGER)&qwTimeFreq);
    qpc_per_second = qwTimeFreq;
    qpc_per_milisec = qwTimeFreq / uint64_t(1000);
    qpc_per_microsec = qwTimeFreq / uint64_t(1000000);

    start_time_ms = platform.get_elapsed_ms();
}

uint64_t platform_t::get_qpf() {
    uint64_t _dest;
    QueryPerformanceFrequency((PLARGE_INTEGER)&_dest);
    return _dest;
}

#endif