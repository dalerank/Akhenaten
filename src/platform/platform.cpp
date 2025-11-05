#include "platform.h"
#include "js/js_game.h"
#include "core/log.h"

#include <SDL.h>
#include <ctime>

#if defined(GAME_PLATFORM_WIN)
    #include <windows.h>
#endif

void __platform_open_url(pcstr url) { platform.open_url(url, ""); }
ANK_FUNCTION_1(__platform_open_url)

int platform_sdl_version_at_least(int major, int minor, int patch) {
    SDL_version v;
    SDL_GetVersion(&v);
    return SDL_VERSIONNUM(v.major, v.minor, v.patch) >= SDL_VERSIONNUM(major, minor, patch);
}

void platform_t::open_url(pcstr url, pcstr prefix) {
#if defined(GAME_PLATFORM_LINUX)
    bstring256 command(prefix, "xdg-open '", url, "'");
    logs::info("%s", command);
    [[maybe_unused]] auto result = ::system( command.c_str() );

#elif defined(GAME_PLATFORM_WIN)
    ShellExecuteA(0, "Open", url, 0, 0 , SW_SHOW );

#elif defined(GAME_PLATFORM_MACOSX)
    bstring256 command("open \"", url, "\" &");
    [[maybe_unused]] auto result = ::system(command.c_str());
    //result;
#endif
}

void platform_t::init_timers() {
#if defined(GAME_PLATFORM_WIN)
    uint64_t qwTimeFreq;
    QueryPerformanceFrequency((PLARGE_INTEGER)&qwTimeFreq);
    qpc_per_second = qwTimeFreq;
    qpc_per_milisec = qwTimeFreq / uint64_t(1000);
    qpc_per_microsec = qwTimeFreq / uint64_t(1000000);
#elif defined(GAME_PLATFORM_UNIX) || defined(GAME_PLATFORM_MACOSX) || defined(GAME_PLATFORM_WEB)
    timespec res;
    if (clock_getres(CLOCK_MONOTONIC, &res) == 0) {
        uint64_t nanoseconds_per_second = 1000000000;
        uint64_t nanoseconds_per_millisecond = 1000000;
        uint64_t nanoseconds_per_microsecond = 1000;

        qpc_per_second = nanoseconds_per_second;
        qpc_per_milisec = nanoseconds_per_second / nanoseconds_per_millisecond;
        qpc_per_microsec = nanoseconds_per_second / nanoseconds_per_microsecond;
    }
#endif
    start_time_ms = platform.get_elapsed_ms();
}

uint64_t platform_t::get_qpc() {
#if defined(GAME_PLATFORM_WIN)
    uint64_t _dest;
    QueryPerformanceCounter((PLARGE_INTEGER)&_dest);
    return _dest;
#elif defined(GAME_PLATFORM_UNIX) || defined(GAME_PLATFORM_MACOSX) || defined(GAME_PLATFORM_WEB)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + ts.tv_nsec;
#else
#error "Unsupported platform"
#endif
}

uint64_t platform_t::get_qpf() {
#if defined(GAME_PLATFORM_WIN)
    uint64_t _dest;
    QueryPerformanceFrequency((PLARGE_INTEGER)&_dest);
    return _dest;
#elif defined(GAME_PLATFORM_UNIX) || defined(GAME_PLATFORM_MACOSX) || defined(GAME_PLATFORM_WEB)
    struct timespec res;
    if (clock_getres(CLOCK_MONOTONIC, &res) != 0) {
        return 0;
    }
    return static_cast<uint64_t>(1e9) / (static_cast<uint64_t>(res.tv_sec) * 1e9 + res.tv_nsec);
#else
#error "Unsupported platform"
#endif
}

platform_t platform;