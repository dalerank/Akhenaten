#pragma once

#include "core/bstring.h"

int platform_sdl_version_at_least(int major, int minor, int patch);

#if (defined(__WIN32__) || defined(_WIN32)) && !defined(_WIN64)
#define GAME_PLATFORM_WIN
#define GAME_PLATFORM_WIN32
#define GAME_PLATFORM_NAME "win32"
#elif defined(WIN64) || defined(_WIN64)
#define GAME_PLATFORM_WIN
#define GAME_PLATFORM_WIN64
#define GAME_PLATFORM_NAME "win64"
#elif defined(__APPLE_CC__) || defined(__APPLE__) || defined(__APPLE_CPP__) || defined(__MACOS_CLASSIC__)
#define GAME_PLATFORM_UNIX
#define GAME_PLATFORM_MACOSX
#define GAME_PLATFORM_NAME "macosx"
#elif defined(__FreeBSD__) || defined(__OpenBSD__)
#define GAME_PLATFORM_UNIX
#define GAME_PLATFORM_XBSD
#define GAME_PLATFORM_NAME "freebsd"
#elif defined(__HAIKU__) || defined(HAIKU)
#define GAME_PLATFORM_BEOS
#define GAME_PLATFORM_HAIKU
#define GAME_PLATFORM_NAME "haiku"
#elif defined(ANDROID) || defined(__ANDROID__)
#define GAME_PLATFORM_UNIX
#define GAME_PLATFORM_ANDROID
#define GAME_PLATFORM_NAME "android"
#elif defined(__EMSCRIPTEN__)
#define GAME_PLATFORM_WEB
#define GAME_PLATFORM_BROWSER
#define GAME_PLATFORM_NAME "emscripten"
#else
#define GAME_PLATFORM_UNIX
#define GAME_PLATFORM_LINUX
#define GAME_PLATFORM_NAME "linux"
#endif

#if defined(__clang__) || defined(__GNUC__)
#		define forceinline	__attribute__((always_inline)) inline
#		define notinline	__attribute__((noinline))
#elif defined(_MSC_VER)
#		define forceinline	__forceinline
#		define notinline	__declspec(noinline)
#else
#error "unknown compiler"
#endif

struct platform_t {
	struct features_t {
		uint32_t _vmx : 1;	// actually VMX or AltiVec
		uint32_t _sse2 : 1;
		uint32_t _avx : 1;
		uint32_t _f16c : 1;
		uint32_t _fma3 : 1;
		uint32_t _avx2 : 1;
		uint32_t _vrs : 1;
		uint32_t _cpucount : 8;
	};

	features_t features;

	uint64_t get_qpc();
    uint64_t get_qpf();

    uint64_t _qpc_per_second;
    uint64_t _qpc_base;

	void init_timers();

    uint64_t qpc_per_second = 0;
    uint64_t qpc_per_milisec = 0;
    uint64_t qpc_per_microsec = 0;

	uint32_t start_time_ms = 0;

	forceinline	uint64_t get_elapsed_ticks() {
		return (get_qpc() - _qpc_base);
	}

	forceinline	uint32_t get_elapsed_ms() {
		return ((uint32_t)(get_elapsed_ticks() * (uint64_t)(1000) / _qpc_per_second));
	}

	inline pcstr name() { return GAME_PLATFORM_NAME; }
	void open_url(pcstr url, pcstr prefix);

	pcstr get_steam_path();

	inline constexpr bool is_android() const {
#ifdef GAME_PLATFORM_ANDROID
		return true;
#else
		return false;
#endif
	}

	inline constexpr bool is_emscripten() const {
#ifdef GAME_PLATFORM_BROWSER
		return true;
#else
		return false;
#endif
	}

	inline constexpr bool is_windows() const {
#ifdef GAME_PLATFORM_WIN
		return true;
#else
		return false;
#endif
	}

	inline constexpr bool is_macos() const {
#ifdef GAME_PLATFORM_MACOSX
		return true;
#else
		return false;
#endif
	}

	int get_key_from_scancode(int scancode);
	bool file_manager_should_case_correct_file();
};

extern platform_t platform;

