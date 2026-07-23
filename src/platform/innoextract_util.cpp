#include "platform/innoextract_util.h"

#include "core/log.h"
#include "platform/platform.h"

#include <SDL.h>

#include <atomic>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace fs = std::filesystem;

namespace {

void parse_progress_chunk(std::string &acc, const char *data, size_t n, std::atomic<float> *progress) {
    if (!progress || !data || n == 0) {
        return;
    }
    acc.append(data, n);
    for (;;) {
        const size_t nl = acc.find('\n');
        if (nl == std::string::npos) {
            break;
        }
        std::string line = acc.substr(0, nl);
        acc.erase(0, nl + 1);
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        float value = 0.f;
        if (std::sscanf(line.c_str(), "PROGRESS %f", &value) == 1) {
            progress->store(std::clamp(value, 0.f, 1.f), std::memory_order_relaxed);
        }
    }
}

#if defined(_WIN32)
bool spawn_and_wait(const std::wstring &cmdline, pcstr tool_label, xstring *error_out,
  std::atomic<float> *progress = nullptr) {
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE stderr_read = nullptr;
    HANDLE stderr_write = nullptr;
    if (progress) {
        if (!CreatePipe(&stderr_read, &stderr_write, &sa, 0)) {
            if (error_out) {
                *error_out = xstring((std::string("Failed to create pipe for ") + tool_label).c_str());
            }
            return false;
        }
        SetHandleInformation(stderr_read, HANDLE_FLAG_INHERIT, 0);
    }

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (progress) {
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        si.hStdError = stderr_write;
    }

    std::wstring mutable_cmd = cmdline;
    if (!CreateProcessW(nullptr, mutable_cmd.data(), nullptr, nullptr, progress ? TRUE : FALSE, CREATE_NO_WINDOW,
          nullptr, nullptr, &si, &pi)) {
        if (stderr_read) {
            CloseHandle(stderr_read);
        }
        if (stderr_write) {
            CloseHandle(stderr_write);
        }
        if (error_out) {
            *error_out = xstring((std::string("Failed to start ") + tool_label + " process").c_str());
        }
        logs::error("%s: CreateProcess failed (%lu)", tool_label, GetLastError());
        return false;
    }

    if (stderr_write) {
        CloseHandle(stderr_write);
        stderr_write = nullptr;
    }

    std::string line_acc;
    char buf[512];
    for (;;) {
        const DWORD wait = WaitForSingleObject(pi.hProcess, progress ? 50 : INFINITE);
        if (progress && stderr_read) {
            for (;;) {
                DWORD avail = 0;
                if (!PeekNamedPipe(stderr_read, nullptr, 0, nullptr, &avail, nullptr) || avail == 0) {
                    break;
                }
                DWORD nread = 0;
                const DWORD to_read = (std::min)(avail, static_cast<DWORD>(sizeof(buf)));
                if (!ReadFile(stderr_read, buf, to_read, &nread, nullptr) || nread == 0) {
                    break;
                }
                parse_progress_chunk(line_acc, buf, nread, progress);
            }
        }
        if (wait == WAIT_OBJECT_0) {
            break;
        }
    }

    if (stderr_read) {
        DWORD nread = 0;
        while (ReadFile(stderr_read, buf, sizeof(buf), &nread, nullptr) && nread > 0) {
            parse_progress_chunk(line_acc, buf, nread, progress);
        }
        CloseHandle(stderr_read);
    }

    DWORD exit_code = 1;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exit_code != 0) {
        if (error_out) {
            *error_out = xstring((std::string(tool_label) + " exited with an error").c_str());
        }
        logs::error("%s: process exited with code %lu", tool_label, exit_code);
        return false;
    }
    return true;
}
#else
bool spawn_argv_and_wait(char *const argv[], pcstr tool_label, xstring *error_out,
  std::atomic<float> *progress = nullptr) {
    int pipefd[2] = {-1, -1};
    if (progress) {
        if (pipe(pipefd) != 0) {
            if (error_out) {
                *error_out = xstring((std::string("Failed to create pipe for ") + tool_label).c_str());
            }
            return false;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        if (pipefd[0] >= 0) {
            close(pipefd[0]);
            close(pipefd[1]);
        }
        if (error_out) {
            *error_out = xstring((std::string("Failed to fork ") + tool_label + " process").c_str());
        }
        return false;
    }
    if (pid == 0) {
        if (progress) {
            close(pipefd[0]);
            dup2(pipefd[1], STDERR_FILENO);
            close(pipefd[1]);
        }
        execv(argv[0], argv);
        _exit(127);
    }

    if (progress) {
        close(pipefd[1]);
        fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
        std::string line_acc;
        char buf[512];
        for (;;) {
            const ssize_t n = read(pipefd[0], buf, sizeof(buf));
            if (n > 0) {
                parse_progress_chunk(line_acc, buf, static_cast<size_t>(n), progress);
                continue;
            }
            int status = 0;
            const pid_t r = waitpid(pid, &status, WNOHANG);
            if (r == pid) {
                // Drain remaining (blocking briefly).
                fcntl(pipefd[0], F_SETFL, 0);
                for (;;) {
                    const ssize_t m = read(pipefd[0], buf, sizeof(buf));
                    if (m <= 0) {
                        break;
                    }
                    parse_progress_chunk(line_acc, buf, static_cast<size_t>(m), progress);
                }
                close(pipefd[0]);
                if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                    if (error_out) {
                        *error_out = xstring((std::string(tool_label) + " exited with an error").c_str());
                    }
                    logs::error("%s: process exited with status %d", tool_label, status);
                    return false;
                }
                return true;
            }
            usleep(50000);
        }
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        if (error_out) {
            *error_out = xstring((std::string("Failed waiting for ") + tool_label).c_str());
        }
        return false;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (error_out) {
            *error_out = xstring((std::string(tool_label) + " exited with an error").c_str());
        }
        logs::error("%s: process exited with status %d", tool_label, status);
        return false;
    }
    return true;
}
#endif

#if defined(_WIN32)
std::wstring utf8_to_wide(const std::string &utf8) {
    if (utf8.empty()) {
        return {};
    }
    const int n = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    if (n <= 0) {
        return {};
    }
    std::wstring wide(static_cast<size_t>(n - 1), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wide.data(), n);
    return wide;
}
#endif

bool path_is_executable(const fs::path &p) {
    std::error_code ec;
    return fs::is_regular_file(p, ec);
}

xstring binary_directory_impl() {
    char *base = SDL_GetBasePath();
    if (!base) {
        return {};
    }
    xstring result(base);
    SDL_free(base);
    return result;
}

// Prefer the process cwd (launch directory), then the directory of akhenaten.exe.
void bootstrap_search_bases(fs::path *out_a, fs::path *out_b) {
    out_a->clear();
    out_b->clear();

    std::error_code ec;
    fs::path cwd = fs::current_path(ec);
    if (!ec) {
        *out_a = std::move(cwd);
    }

    if (xstring bin = binary_directory_impl(); !bin.empty()) {
        fs::path exe_dir(bin.c_str());
        if (out_a->empty() || exe_dir != *out_a) {
            *out_b = std::move(exe_dir);
        }
    }
}

xstring find_tool_next_to_game(pcstr name_win, pcstr name_unix) {
    xstring base = binary_directory_impl();
    if (base.empty()) {
        return {};
    }
    fs::path candidate = fs::path(base.c_str())
#if defined(_WIN32)
                           / name_win;
#else
                           / name_unix;
#endif
    if (path_is_executable(candidate)) {
        return xstring(candidate.string().c_str());
    }
    return {};
}

xstring find_tool_on_path(pcstr name) {
#if defined(_WIN32)
    char *path_env = nullptr;
    size_t len = 0;
    if (_dupenv_s(&path_env, &len, "PATH") == 0 && path_env) {
        std::string path(path_env);
        free(path_env);
        size_t start = 0;
        while (start < path.size()) {
            size_t end = path.find(';', start);
            if (end == std::string::npos) {
                end = path.size();
            }
            fs::path candidate = fs::path(path.substr(start, end - start)) / name;
            if (path_is_executable(candidate)) {
                return xstring(candidate.string().c_str());
            }
            start = end + 1;
        }
    }
#else
    if (const char *path_env = std::getenv("PATH")) {
        std::string path(path_env);
        size_t start = 0;
        while (start < path.size()) {
            size_t end = path.find(':', start);
            if (end == std::string::npos) {
                end = path.size();
            }
            fs::path candidate = fs::path(path.substr(start, end - start)) / name;
            if (path_is_executable(candidate)) {
                return xstring(candidate.string().c_str());
            }
            start = end + 1;
        }
    }
#endif
    return {};
}

xstring find_named_tool(pcstr name_win, pcstr name_unix, pcstr log_label) {
    if (xstring local = find_tool_next_to_game(name_win, name_unix); !local.empty()) {
        logs::info("%s: using %s", log_label, local.c_str());
        return local;
    }
#if defined(_WIN32)
    if (xstring from_path = find_tool_on_path(name_win); !from_path.empty()) {
        logs::info("%s: using PATH %s", log_label, from_path.c_str());
        return from_path;
    }
#else
    if (xstring from_path = find_tool_on_path(name_unix); !from_path.empty()) {
        logs::info("%s: using PATH %s", log_label, from_path.c_str());
        return from_path;
    }
#endif
    logs::warn("%s: binary not found next to game or on PATH", log_label);
    return {};
}

xstring find_7z_binary() {
    if (xstring local = find_tool_next_to_game("7z.exe", "7z"); !local.empty()) {
        logs::info("7z: using %s", local.c_str());
        return local;
    }
    if (xstring local = find_tool_next_to_game("7za.exe", "7za"); !local.empty()) {
        logs::info("7z: using %s", local.c_str());
        return local;
    }
#if defined(_WIN32)
    if (xstring from_path = find_tool_on_path("7z.exe"); !from_path.empty()) {
        logs::info("7z: using PATH %s", from_path.c_str());
        return from_path;
    }
    if (xstring from_path = find_tool_on_path("7za.exe"); !from_path.empty()) {
        logs::info("7z: using PATH %s", from_path.c_str());
        return from_path;
    }
    const char *candidates[] = {
      "C:\\Program Files\\7-Zip\\7z.exe",
      "C:\\Program Files (x86)\\7-Zip\\7z.exe",
      "D:\\devtools\\7z.exe",
    };
    for (pcstr c : candidates) {
        if (path_is_executable(fs::path(c))) {
            logs::info("7z: using %s", c);
            return xstring(c);
        }
    }
#else
    if (xstring from_path = find_tool_on_path("7z"); !from_path.empty()) {
        logs::info("7z: using PATH %s", from_path.c_str());
        return from_path;
    }
    if (xstring from_path = find_tool_on_path("7za"); !from_path.empty()) {
        logs::info("7z: using PATH %s", from_path.c_str());
        return from_path;
    }
#endif
    logs::warn("7z: binary not found (needed for InstallShield outer CAB)");
    return {};
}

xstring find_campaign_dir(const fs::path &root, int depth = 0) {
    if (depth > 4) {
        return {};
    }
    std::error_code ec;
    const fs::path campaign = root / "campaign.txt";
    if (fs::is_regular_file(campaign, ec)) {
        return xstring(root.string().c_str());
    }
    if (!fs::is_directory(root, ec)) {
        return {};
    }
    for (const auto &entry : fs::directory_iterator(root, ec)) {
        if (ec) {
            break;
        }
        if (!entry.is_directory()) {
            continue;
        }
        xstring found = find_campaign_dir(entry.path(), depth + 1);
        if (!found.empty()) {
            return found;
        }
    }
    return {};
}

xstring find_cab_file(const fs::path &root, pcstr filename, int depth = 0) {
    if (depth > 3) {
        return {};
    }
    std::error_code ec;
    if (!fs::is_directory(root, ec)) {
        return {};
    }
    for (const auto &entry : fs::directory_iterator(root, ec)) {
        if (ec) {
            break;
        }
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            for (char &c : name) {
                if (c >= 'A' && c <= 'Z') {
                    c = static_cast<char>(c - 'A' + 'a');
                }
            }
            std::string want(filename);
            for (char &c : want) {
                if (c >= 'A' && c <= 'Z') {
                    c = static_cast<char>(c - 'A' + 'a');
                }
            }
            if (name == want) {
                return xstring(entry.path().string().c_str());
            }
        } else if (entry.is_directory()) {
            xstring found = find_cab_file(entry.path(), filename, depth + 1);
            if (!found.empty()) {
                return found;
            }
        }
    }
    return {};
}

bool extract_with_innoextract(pcstr setup_exe, pcstr out_dir, xstring *error_out, std::atomic<float> *progress) {
    xstring bin = find_named_tool("innoextract.exe", "innoextract", "innoextract");
    if (bin.empty()) {
        if (error_out) {
            *error_out = "innoextract not found";
        }
        return false;
    }

    logs::info("innoextract: extracting \"%s\" -> \"%s\"", setup_exe, out_dir);

#if defined(_WIN32)
    std::wstring cmd = L"\"" + utf8_to_wide(bin.c_str()) + L"\" -e";
    if (progress) {
        cmd += L" --progress-machine";
    }
    cmd += L" -d \"" + utf8_to_wide(out_dir) + L"\" \"" + utf8_to_wide(setup_exe) + L"\"";
    return spawn_and_wait(cmd, "innoextract", error_out, progress);
#else
    if (progress) {
        char *argv[] = {const_cast<char *>(bin.c_str()), const_cast<char *>("-e"),
          const_cast<char *>("--progress-machine"), const_cast<char *>("-d"), const_cast<char *>(out_dir),
          const_cast<char *>(setup_exe), nullptr};
        return spawn_argv_and_wait(argv, "innoextract", error_out, progress);
    }
    char *argv[] = {const_cast<char *>(bin.c_str()), const_cast<char *>("-e"), const_cast<char *>("-d"),
      const_cast<char *>(out_dir), const_cast<char *>(setup_exe), nullptr};
    return spawn_argv_and_wait(argv, "innoextract", error_out, nullptr);
#endif
}

bool extract_with_installshield(pcstr setup_exe, pcstr out_dir, xstring *error_out, std::atomic<float> *progress) {
    xstring seven_z = find_7z_binary();
    if (seven_z.empty()) {
        if (error_out) {
            *error_out = "7z not found (needed to unpack InstallShield outer archive)";
        }
        return false;
    }
    xstring unshield = find_named_tool("unshield.exe", "unshield", "unshield");
    if (unshield.empty()) {
        if (error_out) {
            *error_out = "unshield not found (place unshield next to akhenaten or on PATH)";
        }
        return false;
    }

    std::error_code ec;
    const fs::path stage = fs::path(out_dir) / "_stage";
    fs::remove_all(stage, ec);
    fs::create_directories(stage, ec);

    logs::info("installshield: peeling outer archive \"%s\" -> \"%s\"", setup_exe, stage.string().c_str());
    if (progress) {
        progress->store(0.15f, std::memory_order_relaxed);
    }

#if defined(_WIN32)
    {
        std::wstring cmd = L"\"" + utf8_to_wide(seven_z.c_str()) + L"\" x -y -o\"" + utf8_to_wide(stage.string())
                           + L"\" \"" + utf8_to_wide(setup_exe) + L"\"";
        if (!spawn_and_wait(cmd, "7z", error_out)) {
            fs::remove_all(stage, ec);
            return false;
        }
    }
#else
    {
        std::string stage_s = stage.string();
        std::string out_opt = std::string("-o") + stage_s;
        char *argv[] = {const_cast<char *>(seven_z.c_str()), const_cast<char *>("x"), const_cast<char *>("-y"),
          const_cast<char *>(out_opt.c_str()), const_cast<char *>(setup_exe), nullptr};
        if (!spawn_argv_and_wait(argv, "7z", error_out)) {
            fs::remove_all(stage, ec);
            return false;
        }
    }
#endif

    if (progress) {
        progress->store(0.55f, std::memory_order_relaxed);
    }

    xstring cab = find_cab_file(stage, "data1.cab");
    if (cab.empty()) {
        if (error_out) {
            *error_out = "InstallShield data1.cab not found after outer extract";
        }
        logs::error("installshield: data1.cab missing under %s", stage.string().c_str());
        fs::remove_all(stage, ec);
        return false;
    }

    logs::info("installshield: unshield \"%s\" -> \"%s\"", cab.c_str(), out_dir);

#if defined(_WIN32)
    {
        std::wstring cmd = L"\"" + utf8_to_wide(unshield.c_str()) + L"\" -d \"" + utf8_to_wide(out_dir) + L"\" x \""
                           + utf8_to_wide(cab.c_str()) + L"\"";
        if (!spawn_and_wait(cmd, "unshield", error_out)) {
            fs::remove_all(stage, ec);
            return false;
        }
    }
#else
    {
        char *argv[] = {const_cast<char *>(unshield.c_str()), const_cast<char *>("-d"), const_cast<char *>(out_dir),
          const_cast<char *>("x"), const_cast<char *>(cab.c_str()), nullptr};
        if (!spawn_argv_and_wait(argv, "unshield", error_out)) {
            fs::remove_all(stage, ec);
            return false;
        }
    }
#endif

    if (progress) {
        progress->store(0.95f, std::memory_order_relaxed);
    }

    fs::remove_all(stage, ec);
    return true;
}

bool extract_installer_impl(pcstr setup_exe, pcstr out_dir, xstring *error_out, std::atomic<float> *progress) {
    if (!setup_exe || !*setup_exe) {
        if (error_out) {
            *error_out = "Installer path is empty";
        }
        return false;
    }
    if (!out_dir || !*out_dir) {
        if (error_out) {
            *error_out = "Output directory is empty";
        }
        return false;
    }

    std::error_code ec;
    fs::create_directories(out_dir, ec);
    if (ec) {
        logs::warn("extract: create_directories(%s): %s", out_dir, ec.message().c_str());
    }

    // Prefer Inno Setup (GOG). Fall back to InstallShield (Sierra demo / retail).
    xstring inno_err;
    if (extract_with_innoextract(setup_exe, out_dir, &inno_err, progress)) {
        if (!find_campaign_dir(fs::path(out_dir)).empty()) {
            if (progress) {
                progress->store(1.f, std::memory_order_relaxed);
            }
            return true;
        }
        logs::warn("innoextract finished but campaign.txt missing — trying InstallShield path");
    } else {
        logs::info("innoextract failed (%s) — trying InstallShield path", inno_err.c_str());
    }

    xstring ish_err;
    if (extract_with_installshield(setup_exe, out_dir, &ish_err, progress)) {
        if (progress) {
            progress->store(1.f, std::memory_order_relaxed);
        }
        return true;
    }

    if (error_out) {
        if (!ish_err.empty()) {
            *error_out = ish_err;
        } else if (!inno_err.empty()) {
            *error_out = inno_err;
        } else {
            *error_out = "Failed to extract installer (tried innoextract and InstallShield)";
        }
    }
    return false;
}

} // namespace

namespace innoextract {

xstring binary_directory() {
    return binary_directory_impl();
}

bool has_pharaoh_data(pcstr dir) {
    if (!dir || !*dir) {
        return false;
    }
    return !find_campaign_dir(fs::path(dir)).empty();
}

pcstr required_game_files_help() {
    return "Akhenaten requires a full Pharaoh + Cleopatra installation.\n"
           "The Pharaoh demo (and installs without Cleopatra) are not supported.\n"
           "Needed under the game folder: Data/Expansion.sg3 or Data/SprMain2.sg3.\n"
           "(Missing Pharaoh_Fonts.sg3 falls back to Akhenaten's built-in font.)";
}

bool has_required_game_files(pcstr dir) {
    if (!dir || !*dir) {
        return false;
    }
    xstring root = find_campaign_dir(fs::path(dir));
    if (root.empty()) {
        return false;
    }
    std::error_code ec;
    const fs::path data = fs::path(root.c_str()) / "Data";
    // Pharaoh_Fonts.sg3 is optional — image_load_paks falls back to TTF/GLCD.
    const bool cleopatra = fs::is_regular_file(data / "Expansion.sg3", ec)
                           || fs::is_regular_file(data / "Expansion.SG3", ec)
                           || fs::is_regular_file(data / "SprMain2.sg3", ec)
                           || fs::is_regular_file(data / "SprMain2.SG3", ec);
    if (!cleopatra) {
        logs::warn("install check: missing Cleopatra packs (Expansion/SprMain2) under %s", root.c_str());
        return false;
    }
    return true;
}

xstring find_installer_exe(pcstr installer_dir) {
    if (!installer_dir || !*installer_dir) {
        return {};
    }
    std::error_code ec;
    fs::path dir(installer_dir);
    if (!fs::is_directory(dir, ec)) {
        return {};
    }

    // Prefer the largest .exe (full GOG/setup over a small demo when both are present).
    xstring best;
    std::uintmax_t best_size = 0;
    for (const auto &entry : fs::directory_iterator(dir, ec)) {
        if (ec || !entry.is_regular_file()) {
            continue;
        }
        const auto ext = entry.path().extension().string();
        if (ext != ".exe" && ext != ".EXE") {
            continue;
        }
        const auto sz = entry.file_size(ec);
        if (ec) {
            continue;
        }
        if (best.empty() || sz > best_size) {
            best_size = sz;
            best = xstring(entry.path().string().c_str());
        }
    }
    return best;
}

xstring installer_pending_bootstrap() {
    fs::path bases[2];
    bootstrap_search_bases(&bases[0], &bases[1]);

    for (const fs::path &base : bases) {
        if (base.empty()) {
            continue;
        }
        if (xstring existing = find_campaign_dir(base / "PharaohData"); !existing.empty()) {
            if (has_required_game_files(existing.c_str())) {
                return {};
            }
            // Incomplete tree in this base: do not auto-offer extract over it.
            return {};
        }
    }

    for (const fs::path &base : bases) {
        if (base.empty()) {
            continue;
        }
        xstring setup = find_installer_exe((base / "Installer").string().c_str());
        if (!setup.empty()) {
            logs::info("Pending Pharaoh installer (cwd/exe): %s", setup.c_str());
            return setup;
        }
    }
    return {};
}

xstring try_bootstrap_pharaoh_data(xstring *error_out) {
    fs::path bases[2];
    bootstrap_search_bases(&bases[0], &bases[1]);

    for (const fs::path &base : bases) {
        if (base.empty()) {
            continue;
        }
        if (xstring existing = find_campaign_dir(base / "PharaohData"); !existing.empty()) {
            if (has_required_game_files(existing.c_str())) {
                logs::info("PharaohData: using existing data at %s", existing.c_str());
                return existing;
            }
            logs::warn("PharaohData at %s is incomplete (demo / no Cleopatra)", existing.c_str());
            if (error_out) {
                *error_out = required_game_files_help();
            }
            return {};
        }
    }

    fs::path extract_base;
    xstring setup;
    for (const fs::path &base : bases) {
        if (base.empty()) {
            continue;
        }
        setup = find_installer_exe((base / "Installer").string().c_str());
        if (!setup.empty()) {
            extract_base = base;
            break;
        }
    }
    if (setup.empty() || extract_base.empty()) {
        logs::info("PharaohData has no campaign.txt and no Installer/*.exe in cwd or next to binary");
        return {};
    }

    const fs::path pharaoh_data = extract_base / "PharaohData";
    logs::info("PharaohData missing campaign.txt — extracting %s -> %s", setup.c_str(),
      pharaoh_data.string().c_str());
    xstring err;
    if (!extract_installer(setup.c_str(), pharaoh_data.string().c_str(), &err)) {
        if (error_out) {
            *error_out = err.empty() ? xstring("Failed to extract Installer/*.exe into PharaohData") : err;
        }
        return {};
    }

    xstring root = find_extracted_game_path(pharaoh_data.string().c_str());
    if (root.empty()) {
        if (error_out) {
            *error_out = "Extraction finished but campaign.txt was not found in PharaohData";
        }
        return {};
    }
    if (!has_required_game_files(root.c_str())) {
        if (error_out) {
            *error_out = required_game_files_help();
        }
        return {};
    }
    return root;
}

xstring find_binary() {
    return find_named_tool("innoextract.exe", "innoextract", "innoextract");
}

xstring default_extract_directory() {
#if defined(_WIN32) || defined(_WIN64)
    char *appdata = nullptr;
    size_t len = 0;
    if (_dupenv_s(&appdata, &len, "APPDATA") == 0 && appdata) {
        fs::path dir = fs::path(appdata) / "akhenaten" / "pharaoh-data";
        free(appdata);
        return xstring(dir.string().c_str());
    }
    return xstring("pharaoh-data");
#elif defined(GAME_PLATFORM_MACOSX)
    char *tmp = SDL_GetPrefPath("", "Akhenaten");
    if (tmp) {
        fs::path dir = fs::path(tmp) / "pharaoh-data";
        SDL_free(tmp);
        return xstring(dir.string().c_str());
    }
    return xstring("pharaoh-data");
#else
    if (const char *xdg = std::getenv("XDG_CONFIG_HOME")) {
        fs::path dir = fs::path(xdg) / "akhenaten" / "pharaoh-data";
        return xstring(dir.string().c_str());
    }
    if (const char *home = std::getenv("HOME")) {
        fs::path dir = fs::path(home) / ".config" / "akhenaten" / "pharaoh-data";
        return xstring(dir.string().c_str());
    }
    return xstring("pharaoh-data");
#endif
}

bool extract_installer(pcstr setup_exe, pcstr out_dir, xstring *error_out) {
    return extract_installer_impl(setup_exe, out_dir, error_out, nullptr);
}

xstring pharaoh_data_directory() {
    // Prefer PharaohData next to the pending installer (often the launch cwd).
    if (xstring setup = installer_pending_bootstrap(); !setup.empty()) {
        const fs::path installer_dir = fs::path(setup.c_str()).parent_path();
        return xstring((installer_dir.parent_path() / "PharaohData").string().c_str());
    }

    fs::path bases[2];
    bootstrap_search_bases(&bases[0], &bases[1]);
    for (const fs::path &base : bases) {
        if (!base.empty()) {
            return xstring((base / "PharaohData").string().c_str());
        }
    }
    return {};
}

namespace {

struct ExtractJobState {
    std::atomic<bool> running{false};
    std::atomic<bool> ok{false};
    std::atomic<float> progress{0.f};
    std::mutex error_mutex;
    xstring error;
    std::thread worker;
};

ExtractJobState &extract_job() {
    static ExtractJobState state;
    return state;
}

} // namespace

bool extract_job_start(pcstr setup_exe, pcstr out_dir, xstring *error_out) {
    ExtractJobState &job = extract_job();
    if (job.running.load(std::memory_order_acquire)) {
        if (error_out) {
            *error_out = "Extract already in progress";
        }
        return false;
    }
    if (job.worker.joinable()) {
        job.worker.join();
    }

    if (!setup_exe || !*setup_exe || !out_dir || !*out_dir) {
        if (error_out) {
            *error_out = "Installer path or output directory is empty";
        }
        return false;
    }

    const std::string setup(setup_exe);
    const std::string out(out_dir);
    job.ok.store(false, std::memory_order_relaxed);
    job.progress.store(0.f, std::memory_order_relaxed);
    {
        std::lock_guard<std::mutex> lock(job.error_mutex);
        job.error = {};
    }
    job.running.store(true, std::memory_order_release);

    job.worker = std::thread([setup, out]() {
        ExtractJobState &job = extract_job();
        xstring err;
        const bool ok = extract_installer_impl(setup.c_str(), out.c_str(), &err, &job.progress);
        {
            std::lock_guard<std::mutex> lock(job.error_mutex);
            job.error = err;
        }
        job.ok.store(ok, std::memory_order_relaxed);
        if (ok) {
            job.progress.store(1.f, std::memory_order_relaxed);
        }
        job.running.store(false, std::memory_order_release);
    });
    return true;
}

bool extract_job_running() {
    return extract_job().running.load(std::memory_order_acquire);
}

float extract_job_progress() {
    return extract_job().progress.load(std::memory_order_relaxed);
}

bool extract_job_take_result(xstring *error_out) {
    ExtractJobState &job = extract_job();
    if (job.running.load(std::memory_order_acquire)) {
        return false;
    }
    if (job.worker.joinable()) {
        job.worker.join();
    }
    if (error_out) {
        std::lock_guard<std::mutex> lock(job.error_mutex);
        *error_out = job.error;
    }
    return job.ok.load(std::memory_order_relaxed);
}

xstring find_extracted_game_path(pcstr out_dir) {
    if (!out_dir || !*out_dir) {
        return {};
    }
    xstring found = find_campaign_dir(fs::path(out_dir));
    if (found.empty()) {
        logs::warn("extract: campaign.txt not found under %s", out_dir);
    } else {
        logs::info("extract: game root %s", found.c_str());
    }
    return found;
}

} // namespace innoextract
