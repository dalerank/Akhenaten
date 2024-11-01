#pragma once

#include "core/bstring.h"

int platform_sdl_version_at_least(int major, int minor, int patch);
void platform_open_url(pcstr url, pcstr prefix);

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
#elif defined(ANDROID)
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

inline pcstr platform_name() { return GAME_PLATFORM_NAME; }
