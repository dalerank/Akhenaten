#include "platform/discord_rpc.h"

#if defined(GAME_PLATFORM_WIN) || defined(GAME_PLATFORM_LINUX)

#include "core/log.h"
#include "core/profiler.h"
#include "core/app.h"
#include "js/js_game.h"

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <ctime>

#ifdef GAME_PLATFORM_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

struct discord_rpc_t::impl {
    char app_id[64] = {};
    bool logged_fail = false;
    int64_t start_timestamp = 0;
    xstring pending_details;
    xstring pending_state;
    uint32_t nonce = 0;

#ifdef GAME_PLATFORM_WIN
    void* pipe_handle = (void*)(intptr_t)(-1);
#else
    int fd = -1;
#endif

    bool is_connected() const;
    bool raw_write(pcstr buf, uint32_t len);
    void close_pipe();
    bool open_pipe();
    bool read_blocking(void* buf, uint32_t len);
    void drain_incoming();
    bool send_packet(uint32_t opcode, pcstr json);
    static void json_escape(pcstr src, pstr dst, size_t dst_cap);
    bool do_handshake();
    bool try_connect();
    void do_send_activity(const xstring& details, const xstring& state);

    void init(pcstr id);
    void shutdown();
    void tick();
    void set_activity(const xstring& details, const xstring& state);
    void clear_activity();
};

#ifdef GAME_PLATFORM_WIN

bool discord_rpc_t::impl::is_connected() const {
    return pipe_handle != (void*)(intptr_t)(-1);
}

bool discord_rpc_t::impl::raw_write(pcstr buf, uint32_t len) {
    DWORD written = 0;
    return WriteFile((HANDLE)pipe_handle, buf, (DWORD)len, &written, nullptr) && written == len;
}

void discord_rpc_t::impl::close_pipe() {
    CloseHandle((HANDLE)pipe_handle);
    pipe_handle = (void*)(intptr_t)(-1);
}

bool discord_rpc_t::impl::open_pipe() {
    for (int i = 0; i <= 9; ++i) {
        wchar_t path[48];
        swprintf(path, 48, L"\\\\.\\pipe\\discord-ipc-%d", i);
        HANDLE h = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (h != INVALID_HANDLE_VALUE) {
            logs::info("discord_rpc: opened pipe discord-ipc-%d", i);
            pipe_handle = (void*)h;
            return true;
        }
    }
    logs::info("discord_rpc: no discord-ipc-N pipe found (Discord not running?)");
    return false;
}

bool discord_rpc_t::impl::read_blocking(void* buf, uint32_t len) {
    char* ptr = (char*)buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        DWORD rb = 0;
        if (!ReadFile((HANDLE)pipe_handle, ptr, remaining, &rb, nullptr) || rb == 0)
            return false;
        ptr += rb;
        remaining -= rb;
    }
    return true;
}

void discord_rpc_t::impl::drain_incoming() {
    DWORD avail = 0;
    while (PeekNamedPipe((HANDLE)pipe_handle, nullptr, 0, nullptr, &avail, nullptr) && avail >= 8) {
        uint8_t hdr[8];
        DWORD rb = 0;
        if (!ReadFile((HANDLE)pipe_handle, hdr, 8, &rb, nullptr) || rb < 8) {
            close_pipe();
            return;
        }
        uint32_t opcode
          = (uint32_t)hdr[0] | ((uint32_t)hdr[1] << 8) | ((uint32_t)hdr[2] << 16) | ((uint32_t)hdr[3] << 24);
        uint32_t plen
          = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 24);
        char payload[1025] = {};
        uint32_t total = 0;
        while (total < plen) {
            DWORD chunk = ((plen - total) < 1024) ? (plen - total) : 1024;
            DWORD r = 0;
            if (!ReadFile((HANDLE)pipe_handle, payload + total, chunk, &r, nullptr) || r == 0) {
                close_pipe();
                return;
            }
            total += r;
        }
        payload[total < 1024 ? total : 1024] = 0;
        logs::info("discord_rpc: incoming opcode=%u: %.512s", opcode, payload);
    }
}

#else // POSIX

bool discord_rpc_t::impl::is_connected() const {
    return fd >= 0;
}

bool discord_rpc_t::impl::raw_write(pcstr buf, uint32_t len) {
    const char* ptr = buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        ssize_t n = write(fd, ptr, remaining);
        if (n <= 0)
            return false;
        ptr += n;
        remaining -= (uint32_t)n;
    }
    return true;
}

void discord_rpc_t::impl::close_pipe() {
    close(fd);
    fd = -1;
}

bool discord_rpc_t::impl::open_pipe() {
    const char* dirs[3] = {getenv("XDG_RUNTIME_DIR"), getenv("TMPDIR"), "/tmp"};

    for (int di = 0; di < 3; ++di) {
        if (!dirs[di] || !dirs[di][0])
            continue;
        for (int i = 0; i <= 9; ++i) {
            int sock = socket(AF_UNIX, SOCK_STREAM, 0);
            if (sock < 0)
                return false;

            struct sockaddr_un addr;
            memset(&addr, 0, sizeof(addr));
            addr.sun_family = AF_UNIX;
            snprintf(addr.sun_path, sizeof(addr.sun_path), "%s/discord-ipc-%d", dirs[di], i);

            if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
                fd = sock;
                return true;
            }
            close(sock);
        }
    }
    return false;
}

bool discord_rpc_t::impl::read_blocking(void* buf, uint32_t len) {
    char* ptr = (char*)buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        struct timeval tv = {2, 0};
        if (select(fd + 1, &rfds, nullptr, nullptr, &tv) <= 0)
            return false;
        ssize_t n = read(fd, ptr, remaining);
        if (n <= 0)
            return false;
        ptr += n;
        remaining -= (uint32_t)n;
    }
    return true;
}

void discord_rpc_t::impl::drain_incoming() {
    char buf[512];
    while (true) {
        ssize_t n = recv(fd, buf, sizeof(buf), MSG_DONTWAIT);
        if (n <= 0) {
            if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
                return;
            close_pipe();
            return;
        }
    }
}

#endif // GAME_PLATFORM_WIN

bool discord_rpc_t::impl::send_packet(uint32_t opcode, pcstr json) {
    uint32_t len = (uint32_t)strlen(json);
    uint8_t hdr[8] = {
      (uint8_t)(opcode),
      (uint8_t)(opcode >> 8),
      (uint8_t)(opcode >> 16),
      (uint8_t)(opcode >> 24),
      (uint8_t)(len),
      (uint8_t)(len >> 8),
      (uint8_t)(len >> 16),
      (uint8_t)(len >> 24),
    };
    return raw_write((pcstr)hdr, 8) && raw_write(json, len);
}

void discord_rpc_t::impl::json_escape(pcstr src, pstr dst, size_t dst_cap) {
    size_t i = 0;
    if (!src) {
        dst[0] = 0;
        return;
    }
    while (*src && i + 2 < dst_cap) {
        unsigned char c = (unsigned char)*src++;
        if (c == '"' || c == '\\') {
            dst[i++] = '\\';
            dst[i++] = c;
        } else if (c >= 0x20) {
            dst[i++] = c;
        }
    }
    dst[i] = 0;
}

bool discord_rpc_t::impl::do_handshake() {
    char json[128];
    snprintf(json, sizeof(json), "{\"v\":1,\"client_id\":\"%s\"}", app_id);
    logs::info("discord_rpc: handshake -> %s", json);
    if (!send_packet(0, json)) {
        logs::warn("discord_rpc: handshake write failed");
        return false;
    }

    uint8_t hdr[8];
    if (!read_blocking(hdr, 8)) {
        logs::warn("discord_rpc: handshake read header failed");
        return false;
    }

    uint32_t opcode = (uint32_t)hdr[0] | ((uint32_t)hdr[1] << 8) | ((uint32_t)hdr[2] << 16) | ((uint32_t)hdr[3] << 24);
    uint32_t plen = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 24);
    logs::info("discord_rpc: handshake response opcode=%u payload_len=%u", opcode, plen);
    if (plen > 8192) {
        logs::warn("discord_rpc: handshake payload too large (%u), aborting", plen);
        return false;
    }

    // read and log the READY payload
    char ready_buf[8193] = {};
    uint32_t total = 0;
    while (total < plen) {
        uint32_t chunk = (plen - total < 256) ? (plen - total) : 256;
        if (!read_blocking(ready_buf + total, chunk)) {
            logs::warn("discord_rpc: handshake payload read failed at byte %u", total);
            return false;
        }
        total += chunk;
    }
    ready_buf[total] = 0;
    logs::info("discord_rpc: READY payload: %.256s", ready_buf);
    return true;
}

bool discord_rpc_t::impl::try_connect() {
    if (!open_pipe())
        return false;
    if (!do_handshake()) {
        close_pipe();
        return false;
    }
    return true;
}

void discord_rpc_t::impl::do_send_activity(const xstring& details, const xstring& state) {
    char esc_details[128], esc_state[128];
    json_escape(details.c_str(), esc_details, sizeof(esc_details));
    json_escape(state.c_str(), esc_state, sizeof(esc_state));

    int pid =
#ifdef GAME_PLATFORM_WIN
      (int)GetCurrentProcessId();
#else
      (int)getpid();
#endif

    char json[512];
    snprintf(json, sizeof(json),
      "{\"cmd\":\"SET_ACTIVITY\","
      "\"args\":{"
      "\"pid\":%d,"
      "\"activity\":{"
      "\"details\":\"%s\","
      "\"state\":\"%s\","
      "\"timestamps\":{\"start\":%lld},"
      "\"assets\":{\"large_image\":\"icon\",\"large_text\":\"Akhenaten\"}"
      "}},"
      "\"nonce\":\"%u\"}",
      pid, esc_details, esc_state, (long long)start_timestamp, ++nonce);

    logs::info("discord_rpc: SET_ACTIVITY details='%s' state='%s'", esc_details, esc_state);
    if (!send_packet(1, json)) {
        logs::warn("discord_rpc: SET_ACTIVITY send failed, disconnecting");
        close_pipe();
    }
}

void discord_rpc_t::impl::init(pcstr id) {
    strncpy(app_id, id, sizeof(app_id) - 1);
    app_id[sizeof(app_id) - 1] = 0;
    start_timestamp = (int64_t)time(nullptr);
    logged_fail = false;

    if (!try_connect()) {
        logs::info("discord_rpc: Discord not running, Rich Presence disabled");
        logged_fail = true;
    } else {
        logs::info("discord_rpc: connected to Discord IPC");
        do_send_activity(xstring("Akhenaten"), xstring("In menus"));
    }
}

void discord_rpc_t::impl::shutdown() {
    if (is_connected()) {
        send_packet(2, "{}");
        close_pipe();
    }
}

void discord_rpc_t::impl::tick() {
    if (!is_connected()) {
        if (logged_fail) {
            return;
        }

        if (!try_connect()) {
            return;
        }
        logs::info("discord_rpc: reconnected to Discord IPC");
        logged_fail = false;
        do_send_activity(
            pending_details.empty() ? xstring("Akhenaten") : pending_details,
            pending_state.empty()   ? xstring("In menus")  : pending_state);
        return;
    }
    drain_incoming();
}

void discord_rpc_t::impl::set_activity(const xstring& details, const xstring& state) {
    pending_details = details;
    pending_state = state;
    if (!is_connected())
        return;
    do_send_activity(details, state);
}

void discord_rpc_t::impl::clear_activity() {
    pending_details = xstring();
    pending_state = xstring();
    if (!is_connected())
        return;

    int pid =
#ifdef GAME_PLATFORM_WIN
      (int)GetCurrentProcessId();
#else
      (int)getpid();
#endif
    char json[128];
    snprintf(json, sizeof(json), "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":%d,\"activity\":null},\"nonce\":\"%u\"}",
      pid, ++nonce);

    if (!send_packet(1, json)) {
        close_pipe();
    }
}

// -----------------------------------------------------------------------
// discord_rpc_t (facade)
// -----------------------------------------------------------------------

discord_rpc_t::discord_rpc_t() : d(std::make_unique<impl>()) {
}

void discord_rpc_t::init(pcstr app_id) {
    d->init(app_id);
}

void discord_rpc_t::shutdown() {
    d->shutdown();
}

void discord_rpc_t::tick() {
    d->tick();
}

void discord_rpc_t::set_activity(const xstring& details, const xstring& state) {
    d->set_activity(details, state);
}

void discord_rpc_t::clear_activity() {
    d->clear_activity();
}

discord_rpc_t g_discord_rpc;

void ANK_REGISTER_APPLICATION_MODULE(discord_rpc_module) {
    g_discord_rpc.init("1501648147682693140");
}

void __discord_rpc_set_activity(xstring details, xstring state) {
    g_discord_rpc.set_activity(details, state);
    g_discord_rpc.tick();
}
ANK_FUNCTION_2(__discord_rpc_set_activity)

void __discord_rpc_clear_activity() {
    g_discord_rpc.clear_activity();
    g_discord_rpc.tick();
}
ANK_FUNCTION(__discord_rpc_clear_activity)

#else // defined(GAME_PLATFORM_ANDROID) || defined(GAME_PLATFORM_BROWSER)

#include "core/profiler.h"
#include "js/js_game.h"

void __discord_rpc_set_activity(xstring details, xstring state) {} ANK_FUNCTION_2(__discord_rpc_set_activity)
void __discord_rpc_clear_activity() {} ANK_FUNCTION(__discord_rpc_clear_activity)

#endif // !GAME_PLATFORM_ANDROID && !GAME_PLATFORM_BROWSER
