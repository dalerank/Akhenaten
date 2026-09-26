#include "stacktrace.h"

#include "core/log.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_WIN)

#include <Windows.h>

void debug_break_if_debugger_present() {
    if (IsDebuggerPresent()) {
        __debugbreak();
    }
}

#if defined(GAME_PLATFORM_WIN64)

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

#endif // GAME_PLATFORM_WIN64
#endif // GAME_PLATFORM_WIN
