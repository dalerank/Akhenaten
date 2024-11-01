#include "stacktrace.h"

#include "core/log.h"
#include "platform/platform.h"
#include "platform/screen.h"

#include "SDL.h"

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

#if defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(ANDROID_BUILD)

#include <signal.h>

#include <execinfo.h>

static void backtrace_print(void) {
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

void crashhandler_install(void) {
    signal(SIGSEGV, crash_handler);
}

#elif defined(GAME_PLATFORM_WIN64)

#include <windows.h>

#include <imagehlp.h>
#include <shlwapi.h>
#include <stdio.h>

#define log_info_sprintf(...)                                                                                          \
    snprintf(crash_info, 256, __VA_ARGS__);                                                                            \
    logs::info(crash_info)

static const char* print_exception_name(DWORD exception_code) {
    switch (exception_code) {
    case EXCEPTION_ACCESS_VIOLATION:
        return "Access violation";
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        return "Datatype misalignment";
    case EXCEPTION_BREAKPOINT:
        return "Breakpoint";
    case EXCEPTION_SINGLE_STEP:
        return "Single step";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        return "Array bounds exceeded";
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        return "Float denormal operand";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        return "Float divide by zero";
    case EXCEPTION_FLT_INEXACT_RESULT:
        return "Float inexact result";
    case EXCEPTION_FLT_INVALID_OPERATION:
        return "Float invalid operation";
    case EXCEPTION_FLT_OVERFLOW:
        return "Float overflow";
    case EXCEPTION_FLT_STACK_CHECK:
        return "Float stack check";
    case EXCEPTION_FLT_UNDERFLOW:
        return "Float underflow";
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        return "Integer divide by zero";
    case EXCEPTION_INT_OVERFLOW:
        return "Integer overflow";
    case EXCEPTION_PRIV_INSTRUCTION:
        return "Privileged instruction";
    case EXCEPTION_IN_PAGE_ERROR:
        return "In page error";
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        return "Illegal instruction";
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        return "Noncontinuable exception";
    case EXCEPTION_STACK_OVERFLOW:
        return "Stack overflow";
    case EXCEPTION_INVALID_DISPOSITION:
        return "Invalid disposition";
    case EXCEPTION_GUARD_PAGE:
        return "Guard page";
    case EXCEPTION_INVALID_HANDLE:
        return "Invalid handle";
    }
    return "Unknown exception";
}

static void print_stacktrace(LPEXCEPTION_POINTERS e) {
    void* stack[100];
    char crash_info[256];
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    char modname[MAX_PATH];

    PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;
    DWORD displacement;
    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    // Record exception info
    log_info_sprintf("Exception: %s (0x%08x)",
                     print_exception_name(e->ExceptionRecord->ExceptionCode),
                     (unsigned int)e->ExceptionRecord->ExceptionCode);
    log_info_sprintf("Exception Address: 0x%p", e->ExceptionRecord->ExceptionAddress);

    // Record stacktrace
    log_info_sprintf("Stacktrace:");

    int frames = CaptureStackBackTrace(0, 100, stack, NULL);

    for (int frame = 0; frame < frames; frame++) {
        if (SymFromAddr(GetCurrentProcess(), (DWORD64)stack[frame], 0, symbol)) {
            int has_line = SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)stack[frame], &displacement, &line);
            // This is the code path taken on VC if debugging syms are found
            log_info_sprintf("(%d) %s L:%lu(%s+%#0lx) [0x%08lX]\n",
                             frame,
                             has_line ? line.FileName : "UNKNOWN FILE",
                             has_line ? line.LineNumber : 0,
                             symbol->Name,
                             displacement,
                             (unsigned long)(DWORD64)stack[frame]);
        } else {
            DWORD64 mod_base = SymGetModuleBase64(GetCurrentProcess(), (DWORD64)stack[frame]);
            if (mod_base) {
                GetModuleFileName((HINSTANCE)mod_base, modname, MAX_PATH);
            } else {
                strcpy(modname, "Unknown");
            }
            // This is the code path taken on MinGW, and VC if no debugging syms are found.
            log_info_sprintf("(%d) %s [0x%08lX]\n", frame, modname, (unsigned long)(DWORD64)stack[frame]);
        }
    }
}

/** Called by windows if an exception happens. */
static LONG CALLBACK exception_handler(LPEXCEPTION_POINTERS e) {
    // Prologue.
    logs::error("Oops, crashed :(", 0, 0);

#ifdef _M_X64
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(0, path, MAX_PATH);
    PathRemoveFileSpecW(path);
    SetEnvironmentVariableW(L"_NT_SYMBOL_PATH", path);

    // Initialize IMAGEHLP.DLL.
    SymInitialize(GetCurrentProcess(), 0, TRUE);

    print_stacktrace(e);

    // Unintialize IMAGEHLP.DLL
    SymCleanup(GetCurrentProcess());

#else
    logs::info("No stack trace available");
#endif

    // Inform user
    display_crash_message();

    // this seems to silently close the application
    return EXCEPTION_EXECUTE_HANDLER;
}

void crashhandler_install() {
    SetUnhandledExceptionFilter(exception_handler);
}

#else
void crashhandler_install() {
    logs::error("Oops, crashed with signal :(");
}
#endif


