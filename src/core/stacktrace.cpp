#include "stacktrace.h"

#include "core/log.h"
#include "platform/platform.h"
#include "platform/screen.h"

#include "SDL.h"

#if defined(GAME_PLATFORM_WIN)
#include <Windows.h>
#include <crtdbg.h>
#endif

static void display_crash_message() {
    platform_screen_show_error_message_box(
      "Ozzy has crashed :(",
      "There was an unrecoverable error, which will now close.\n"
      "The piece of code that caused the crash has been saved to akhenaten-log.txt.\n"
      "If you can, please create an issue by going to:\n"
      "https://github.com/dalerank/akhenaten/issues/new \n"
      "Please attach log.txt and your city save to the issue report.\n"
      "Also, please describe what you were doing when the game crashed.\n"
      "With your help, we can avoid this crash in the future.\n"
      "Copy this message press Ctrl + C.\n"
      "Thanks!\n");
}

namespace debug {
    void va_backend(pcstr msg, pcstr FILE, int line, pcstr F, va_list arg) {
        bstring<4096> reason;
        bstring<4096> buffer;
        _vsnprintf(buffer, sizeof(buffer) - 1, F, arg);
        buffer[sizeof(buffer) - 1] = 0;

        buffer[4000] = 0; // if longer than can fit in reason
        reason.printf("%s:%d|%s\n%s", FILE, line, msg, buffer.c_str());

#ifdef GAME_PLATFORM_WIN
        if (IsDebuggerPresent()) {
            __debugbreak();
        }
#endif
        logs::critical("%s", reason);
    }

    void critical(const char *FILE, int line, const char* F, ...) {
        va_list		args;
        va_start(args, F);
        va_backend("", FILE, line, F, args);
        va_end(args);
    }
}

#if defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(ANDROID_BUILD)

#include <signal.h>

#include <execinfo.h>

static void backtrace_print() {
    void* array[100];
    int size = backtrace(array, 100);

    char** stack = backtrace_symbols(array, size);

    for (int i = 0; i < size; i++) {
        logs::info(stack[i]);
    }
}

static void crash_handler(int sig) {
    logs::error("Oops, crashed with signal %d :(", sig);
    backtrace_print();
    display_crash_message();
    exit(1);
}

void crashhandler_install() {
    signal(SIGSEGV, crash_handler);
}

#elif defined(GAME_PLATFORM_WIN64)

#include "platform/arguments.h"
#include "Windows.h"
#include <Psapi.h>
#include <dbghelp.h>
#include <signal.h>
#include <eh.h>
#include <new.h>
#include <shlwapi.h>
#include "BugTrap.h"

#pragma comment(lib, "shlwapi.lib")

static bool g_bugtrap_available = false;

static bool check_bugtrap_dll_available() {
    // Получаем путь к исполняемому файлу
    char exe_path[MAX_PATH];
    if (GetModuleFileNameA(NULL, exe_path, MAX_PATH) == 0) {
        return false;
    }

    // Получаем директорию, где находится exe
    char exe_dir[MAX_PATH];
    strncpy_s(exe_dir, exe_path, MAX_PATH);
    PathRemoveFileSpecA(exe_dir);

    // Формируем путь к DLL
    char dll_path[MAX_PATH];
    PathCombineA(dll_path, exe_dir, "BugTrap-x64.dll");

    // Проверяем существование файла
    DWORD dwAttrib = GetFileAttributesA(dll_path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
            !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void crashhandler_install() {
    static bool is_bugtrap_inited = false;

    if (is_bugtrap_inited) {
        return;
    }
    is_bugtrap_inited = true;


    g_bugtrap_available = check_bugtrap_dll_available();

    if (!g_bugtrap_available) {
        logs::warn("BugTrap-x64.dll not found, crash reporting will be disabled");
        return;
    }

    BT_SetAppName("Akhenaten");
    BT_SetSupportEMail("dalerankn8@gmail.com");
    BT_SetSupportURL("www.akhenaten.game");
    BT_SetFlags(BTF_DETAILEDMODE | BTF_ATTACHREPORT | BTF_EDITMAIL | BTF_SHOWADVANCEDUI | BTF_SCREENCAPTURE | BTF_INTERCEPTSUEF);
    BT_SetReportFormat(BTRF_TEXT);
    BT_SetSupportServer("localhost", 9999);

    BT_InstallSehFilter();
    BT_SetTerminate(); // set_terminate() must be called from every thread

}

LONG CALLBACK debug_sehgilter(PEXCEPTION_POINTERS pExceptionPointers) {
    if (IsDebuggerPresent()) {
        return 0;
    }

    if (!g_bugtrap_available) {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    return BT_SehFilter((PEXCEPTION_POINTERS)pExceptionPointers);
}

#else
void crashhandler_install() {
    logs::error("Oops, crashed with signal :(");
}
#endif


