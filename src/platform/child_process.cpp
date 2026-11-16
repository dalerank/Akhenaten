#include "child_process.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static std::wstring widen(const std::string& s) {
    if (s.empty()) {
        return {};
    }
    const int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
    return w;
}

static void append_quoted(std::wstring& cmd, const std::wstring& arg) {
    if (!cmd.empty()) {
        cmd += L' ';
    }
    if (!arg.empty() && arg.find_first_of(L" \t\"") == std::wstring::npos) {
        cmd += arg;
        return;
    }
    cmd += L'"';
    size_t backslashes = 0;
    for (wchar_t c : arg) {
        if (c == L'\\') {
            ++backslashes;
            continue;
        }
        if (c == L'"') {
            cmd.append(backslashes * 2 + 1, L'\\');
        } else {
            cmd.append(backslashes, L'\\');
        }
        backslashes = 0;
        cmd += c;
    }
    cmd.append(backslashes * 2, L'\\');
    cmd += L'"';
}

bool child_process_start(const std::vector<std::string>& argv, child_process& out) {
    if (argv.empty()) {
        return false;
    }
    std::wstring cmd;
    for (const std::string& arg : argv) {
        append_quoted(cmd, widen(arg));
    }

    SECURITY_ATTRIBUTES sa = {};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    HANDLE nul = CreateFileW(L"NUL", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
      OPEN_EXISTING, 0, nullptr);
    const bool redirect = nul != INVALID_HANDLE_VALUE;

    STARTUPINFOW si = {};
    si.cb = sizeof(si);
    if (redirect) {
        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdInput = nul;
        si.hStdOutput = nul;
        si.hStdError = nul;
    }
    PROCESS_INFORMATION pi = {};
    const BOOL started = CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, redirect, 0, nullptr, nullptr, &si, &pi);
    if (redirect) {
        CloseHandle(nul);
    }
    if (!started) {
        return false;
    }
    CloseHandle(pi.hThread);
    out.handle = pi.hProcess;
    out.pid = (int)pi.dwProcessId;
    return true;
}

int child_process_wait(child_process& process) {
    if (!process.handle) {
        return -1;
    }
    WaitForSingleObject((HANDLE)process.handle, INFINITE);
    DWORD code = 1;
    GetExitCodeProcess((HANDLE)process.handle, &code);
    CloseHandle((HANDLE)process.handle);
    process.handle = nullptr;
    return (int)code;
}

#else
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

bool child_process_start(const std::vector<std::string>& argv, child_process& out) {
    if (argv.empty()) {
        return false;
    }
    std::vector<char*> args;
    for (const std::string& arg : argv) {
        args.push_back(const_cast<char*>(arg.c_str()));
    }
    args.push_back(nullptr);

    const pid_t pid = fork();
    if (pid < 0) {
        return false;
    }
    if (pid == 0) {
        const int devnull = open("/dev/null", O_RDWR);
        if (devnull >= 0) {
            dup2(devnull, STDIN_FILENO);
            dup2(devnull, STDOUT_FILENO);
            dup2(devnull, STDERR_FILENO);
            if (devnull > STDERR_FILENO) {
                close(devnull);
            }
        }
        execvp(args[0], args.data());
        _exit(127);
    }
    out.pid = (int)pid;
    return true;
}

int child_process_wait(child_process& process) {
    if (process.pid <= 0) {
        return -1;
    }
    int status = 0;
    if (waitpid((pid_t)process.pid, &status, 0) < 0) {
        return -1;
    }
    process.pid = -1;
    return WIFEXITED(status) ? WEXITSTATUS(status) : 128 + (WIFSIGNALED(status) ? WTERMSIG(status) : 0);
}
#endif
